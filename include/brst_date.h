#ifndef BRST_DATE_H
#define BRST_DATE_H

#include "brst_doc.h"

typedef enum _BRST_Date_Parts {
  BRST_DATE_PART_YEAR,
  BRST_DATE_PART_MONTH,
  BRST_DATE_PART_DAY,
  BRST_DATE_PART_HOUR,
  BRST_DATE_PART_MINUTE,
  BRST_DATE_PART_SECOND,
  BRST_DATE_PART_HOUR_OFFSET,
  BRST_DATE_PART_MINUTE_OFFSET,
  BRST_DATE_PART_UT_RELATIONSHIP
} BRST_Date_Parts;

typedef enum _BRST_UT_Relationship {
  BRST_UT_RELATIONSHIP_NONE,
  BRST_UT_RELATIONSHIP_PLUS,
  BRST_UT_RELATIONSHIP_MINUS,
  BRST_UT_RELATIONSHIP_ZERO,
  BRST_UI_RELATIONSHIP_LAST
} BRST_UT_Relationship;

/**
  \brief Date structure

  Represents date values in \c info dictionary of PDF file, embedded files and annotations.

 */

struct _BRST_Date_Rec;
typedef struct _BRST_Date_Rec* BRST_Date;

BRST_EXPORT(BRST_Date)
BRST_Date_New(
  BRST_Doc pdf,
  BRST_INT yyyy,
  BRST_INT mm,
  BRST_INT dd,
  BRST_INT hh,
  BRST_INT nn,
  BRST_INT ss,
  BRST_UT_Relationship indication,
  BRST_INT ho,
  BRST_INT mo
);

BRST_EXPORT(BRST_Date)
BRST_Date_Now(
    BRST_Doc pdf
);

BRST_EXPORT(BRST_INT)
BRST_Date_Part(
    BRST_Date date,
    BRST_Date_Parts part
);

BRST_EXPORT(BRST_STATUS)
BRST_Date_Validate(
    BRST_Date date
);

BRST_EXPORT(void)
BRST_Date_Free(
    BRST_Date date
);

#endif /* BRST_DATE_H */
