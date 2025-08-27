#ifndef _MSC_VER
#include <time.h>
#include <sys/time.h>
#else
//    #include <Windows.h>
//    #include <sys/timeb.h>
#endif

#include "brst_external.h"
#include "brst_types.h"
#include "brst_mmgr.h"
#include "brst_base.h"
#include "brst_encrypt.h"
#include "brst_stream.h"
#include "brst_dict.h"
#include "brst_date.h"
#include "brst_consts.h"
#include "brst_error.h"
#include "private/brst_date.h"
#include "private/brst_utils.h"
#include "private/brst_mmgr.h"

BRST_EXPORT(BRST_Date)
BRST_Date_New(
    BRST_Doc pdf,
    BRST_INT year,
    BRST_INT mm,
    BRST_INT dd,
    BRST_INT hh,
    BRST_INT nn,
    BRST_INT ss,
    BRST_UT_Relationship indication,
    BRST_INT ho,
    BRST_INT mo)
{
    BRST_PTRACE(" BRST_Date_New\n");

    BRST_MMgr mmgr = BRST_Doc_MMgr(pdf);
    BRST_Date date = BRST_GetMem(mmgr, sizeof(BRST_Date_Rec));

    if (!date) {
        return date;
    }

    BRST_MemSet(date, 0, sizeof(BRST_Date_Rec));
    date->mmgr = mmgr;

    date->year          = year;
    date->month         = mm;
    date->day           = dd;
    date->hour          = hh;
    date->minute        = nn;
    date->second        = ss;
    date->hour_offset   = ho;
    date->minute_offset = mo;
    date->indication    = indication;

    if (BRST_Date_Validate(date) != BRST_OK) {
        return NULL;
    }

    return date;
}

BRST_EXPORT(BRST_Date)
BRST_Date_Now(BRST_Doc pdf)
{
    BRST_PTRACE(" BRST_Date_Now\n");

#ifndef _MSC_VER
    time_t now;
    struct tm* t;
    now = time(NULL);
    t   = localtime(&now);

    BRST_UT_Relationship ind = BRST_UT_RELATIONSHIP_NONE;
    if (t->tm_gmtoff > 0) {
        ind = BRST_UT_RELATIONSHIP_PLUS;
    } else if (t->tm_gmtoff < 0) {
        ind = BRST_UT_RELATIONSHIP_MINUS;
    } else {
        ind = BRST_UT_RELATIONSHIP_ZERO;
    }

    return BRST_Date_New(
        pdf,
        t->tm_year + 1900,
        t->tm_mon + 1,
        t->tm_mday,
        t->tm_hour,
        t->tm_min,
        t->tm_sec % 60, // TODO исправить, не используется leap second
        ind,
        abs(t->tm_gmtoff / 3600),
        abs(t->tm_gmtoff % 3600));

#else
    // TODO Реализация не для Unix
    return NULL;
#endif
}

BRST_EXPORT(BRST_INT)
BRST_Date_Part(BRST_Date date, BRST_Date_Parts part)
{
    if (!date) {
        return -1;
    }
    switch (part) {
    case BRST_DATE_PART_YEAR:
        return date->year;
    case BRST_DATE_PART_MONTH:
        return date->month;
    case BRST_DATE_PART_DAY:
        return date->day;
    case BRST_DATE_PART_HOUR:
        return date->hour;
    case BRST_DATE_PART_MINUTE:
        return date->minute;
    case BRST_DATE_PART_SECOND:
        return date->second;
    case BRST_DATE_PART_HOUR_OFFSET:
        return date->hour_offset;
    case BRST_DATE_PART_MINUTE_OFFSET:
        return date->minute_offset;
    case BRST_DATE_PART_UT_RELATIONSHIP:
        return (BRST_INT)date->indication;
    default:
        return -2;
    }
    return 0;
}

BRST_BOOL
DateIsValid(
    BRST_INT year,
    BRST_INT mm,
    BRST_INT dd,
    BRST_INT hh,
    BRST_INT nn,
    BRST_INT ss,
    BRST_INT ho,
    BRST_INT mo)
{

    if (dd < 1 || hh < 0 || hh > 23 || nn < 0 || nn > 59 || ss < 0 || ss > 59 || ho < 0 || ho > 23 || mo < 0 || mo > 60) {
        return BRST_FALSE;
    }

    switch (mm) {
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:
        if (dd > 31) {
            return BRST_FALSE;
        }

        break;
    case 4:
    case 6:
    case 9:
    case 11:
        if (dd > 30) {
            return BRST_FALSE;
        }

        break;
    case 2:
        if (dd > 29 || (dd == 29 && (year % 4 != 0 || (year % 100 == 0 && year % 400 != 0)))) {
            return BRST_FALSE;
        }

        break;
    default:
        return BRST_FALSE;
    }
    return BRST_TRUE;
}

BRST_STATUS
BRST_Date_Validate(BRST_Date date)
{
    BRST_PTRACE(" BRST_Date_Validate\n");
    BRST_STATUS fail = BRST_INVALID_DATE_TIME;
    if (!date) {
        return fail;
    }

    if (date->year < 0) {
        return fail;
    }

    if (date->indication < BRST_UT_RELATIONSHIP_NONE || date->indication > BRST_UT_RELATIONSHIP_ZERO) {
        return fail;
    }

    /*
        Дата корректна, если указан год.
        Дальнейшие поля опциональны, но если указаны, должны быть валидны.
        Каждое следующее поле должно быть указано, только если указано предыдущее.
        Считаем, что поле не указано, если оно меньше 0.

    */
    if (date->month < 0) {
        if (date->day < 0 && date->hour < 0 && date->minute < 0 && date->second < 0 && date->hour_offset < 0 && date->minute_offset < 0 && date->indication == BRST_UT_RELATIONSHIP_NONE) {
            if (DateIsValid(date->year, 01, 01, 00, 00, 00, 00, 00)) {
                return BRST_OK;
            };
        }
    }

    if (date->day < 0) {
        if (date->hour < 0 && date->minute < 0 && date->second < 0 && date->hour_offset < 0 && date->minute_offset < 0 && date->indication == BRST_UT_RELATIONSHIP_NONE) {
            if (DateIsValid(date->year, date->month, 01, 00, 00, 00, 00, 00)) {
                return BRST_OK;
            };
        }
    }

    if (date->hour < 0) {
        if (date->minute < 0 && date->second < 0 && date->hour_offset < 0 && date->minute_offset < 0 && date->indication == BRST_UT_RELATIONSHIP_NONE) {
            if (DateIsValid(date->year, date->month, date->day, 00, 00, 00, 00, 00)) {
                return BRST_OK;
            };
        }
    }

    if (date->minute < 0) {
        if (date->second < 0 && date->hour_offset < 0 && date->minute_offset < 0 && date->indication == BRST_UT_RELATIONSHIP_NONE) {
            if (DateIsValid(date->year, date->month, date->day, date->hour, 00, 00, 00, 00)) {
                return BRST_OK;
            };
        }
    }

    if (date->second < 0) {
        if (date->hour_offset < 0 && date->minute_offset < 0 && date->indication == BRST_UT_RELATIONSHIP_NONE) {
            if (DateIsValid(date->year, date->month, date->day, date->hour, date->minute, 00, 00, 00)) {
                return BRST_OK;
            };
        }
    }

    if (date->hour_offset < 0) {
        if (date->minute_offset < 0 && date->indication == BRST_UT_RELATIONSHIP_NONE) {
            if (DateIsValid(date->year, date->month, date->day, date->hour, date->minute, date->second, 00, 00)) {
                return BRST_OK;
            };
        }
    }

    if (date->minute_offset < 0) {
        if (date->indication == BRST_UT_RELATIONSHIP_NONE) {
            if (DateIsValid(date->year, date->month, date->day, date->hour, date->minute, date->second, date->hour_offset, 00)) {
                return BRST_OK;
            };
        }
    }

    if (DateIsValid(date->year, date->month, date->day, date->hour, date->minute, date->second, date->hour_offset, date->minute_offset)) {
        return BRST_OK;
    };

    return fail;
}

void BRST_Date_Free(BRST_Date date)
{
    BRST_PTRACE(" BRST_Date_Free\n");
    if (!date) {
        return;
    }
    BRST_FreeMem(date->mmgr, date);
}
