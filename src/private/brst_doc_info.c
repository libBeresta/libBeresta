#include "brst_types.h"
#include "brst_mmgr.h"
#include "brst_encrypt.h"
#include "brst_dict.h"
#include "brst_stream.h"
#include "brst_encoder.h"
#include "brst_doc.h"
#include "brst_doc_info.h"
#include "private/brst_info.h"
#include "private/brst_dict.h"
#include "private/brst_string.h"
#include "private/brst_utils.h"
#include "brst_error.h"
#include "private/brst_defines.h"

static const char* const BRST_INFO_ATTR_NAMES[] = {
    "CreationDate",
    "ModDate",
    "Author",
    "Creator",
    "Producer",
    "Title",
    "Subject",
    "Keywords",
    "Trapped",
    "GTS_PDFXVersion",
    NULL
};

static const char*
InfoTypeToName(BRST_InfoType type);

/*---------------------------------------------------------------------------*/

static const char*
InfoTypeToName(BRST_InfoType type)
{
    BRST_UINT idx = (BRST_UINT)type;

    return BRST_INFO_ATTR_NAMES[idx];
}

BRST_STATUS
BRST_Info_SetInfoAttr(BRST_Dict info,
    BRST_InfoType type,
    const char* value,
    BRST_Encoder encoder)
{
    const char* name = InfoTypeToName(type);

    BRST_PTRACE((" BRST_Info_SetInfoAttr\n"));

    if (type <= BRST_INFO_MOD_DATE)
        return BRST_Error_Set(info->error, BRST_INVALID_PARAMETER, 0);

    if (type == BRST_INFO_TRAPPED)
        return BRST_Dict_AddName(info, name, value);

    return BRST_Dict_Add(info, name, BRST_String_New(info->mmgr, value, encoder));
}

const char*
BRST_Info_InfoAttr(BRST_Dict info,
    BRST_InfoType type)
{
    const char* name = InfoTypeToName(type);
    BRST_String s;

    BRST_PTRACE((" BRST_Info_InfoAttr\n"));

    if (!info)
        return NULL;

    s = BRST_Dict_Item(info, name, BRST_OCLASS_STRING);

    if (!s)
        return NULL;
    else
        return BRST_String_Value(s);
}

BRST_STATUS
BRST_Info_SetInfoDateAttr(BRST_Dict info,
    BRST_InfoType type,
    BRST_Date value)
{
    char tmp[BRST_DATE_TIME_STR_LEN + 1];
    char* ptmp;
    const char* name = InfoTypeToName(type);

    BRST_PTRACE((" BRST_Info_SetInfoDateAttr\n"));

    if (type > BRST_INFO_MOD_DATE)
        return BRST_Error_Set(info->error, BRST_INVALID_PARAMETER, 0);

    BRST_MemSet(tmp, 0, BRST_DATE_TIME_STR_LEN + 1);
    if (value.month < 1 || 12 < value.month || value.day < 1 || 23 < value.hour || 59 < value.minutes || 59 < value.seconds || (value.ind != '+' && value.ind != '-' && value.ind != 'Z' && value.ind != ' ') || 23 < value.off_hour || 59 < value.off_minutes) {
        return BRST_Error_Set(info->error, BRST_INVALID_DATE_TIME, 0);
    }

    switch (value.month) {
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:
        if (value.day > 31)
            return BRST_Error_Set(info->error, BRST_INVALID_DATE_TIME, 0);

        break;
    case 4:
    case 6:
    case 9:
    case 11:
        if (value.day > 30)
            return BRST_Error_Set(info->error, BRST_INVALID_DATE_TIME, 0);

        break;
    case 2:
        if (value.day > 29 || (value.day == 29 && (value.year % 4 != 0 || (value.year % 100 == 0 && value.year % 400 != 0))))
            return BRST_Error_Set(info->error, BRST_INVALID_DATE_TIME, 0);

        break;
    default:
        return BRST_Error_Set(info->error, BRST_INVALID_DATE_TIME, 0);
    }

    ptmp = (char*)BRST_MemCpy((BRST_BYTE*)tmp, (BRST_BYTE*)"D:", 2);
    ptmp = BRST_IToA2(ptmp, value.year, 5);
    ptmp = BRST_IToA2(ptmp, value.month, 3);
    ptmp = BRST_IToA2(ptmp, value.day, 3);
    ptmp = BRST_IToA2(ptmp, value.hour, 3);
    ptmp = BRST_IToA2(ptmp, value.minutes, 3);
    ptmp = BRST_IToA2(ptmp, value.seconds, 3);
    if (value.ind != ' ') {
        *ptmp++ = value.ind;
        ptmp    = BRST_IToA2(ptmp, value.off_hour, 3);
        *ptmp++ = '\'';
        ptmp    = BRST_IToA2(ptmp, value.off_minutes, 3);
        *ptmp++ = '\'';
    }
    *ptmp = 0;

    return BRST_Dict_Add(info, name, BRST_String_New(info->mmgr, tmp, NULL));
}
