#ifndef PRIVATE_BRST_DATE_H
#define PRIVATE_BRST_DATE_H

typedef struct _BRST_Date_Rec {
    BRST_MMgr mmgr;
    /// Year of the date. Does not imply restrictions.
    BRST_INT year;
    /// Month of the date. Value from range 1 to 12 is accepted.
    BRST_INT month;
    /// Day of the date. Values from range 1 to 28, 29, 30, or 31 is accepted (depends on the month)
    BRST_INT day;
    /// Hour of date. Value from range 0 to 23 is accepted.
    BRST_INT hour;
    /// Minutes of date. Value from range 0 to 59 is accepted.
    BRST_INT minute;
    /// Seconds of date. Value from range 0 to 59 is accepted.
    BRST_INT second;
    /// Relationship between local time and Universal time (' ', '+', '−', or 'Z')
    BRST_UT_Relationship indication;
    /// If \c ind is not ' ' (space), value from range 0 to 23 is accepted, otherwise ignored.
    BRST_INT hour_offset;
    /// If \c ind is not ' ' (space), value from range 0 to 59 is accepted, otherwise ignored.
    BRST_INT minute_offset;
} BRST_Date_Rec;

#endif /* PRIVATE_BRST_DATE_H */