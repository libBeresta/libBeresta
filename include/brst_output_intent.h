#ifndef BRST_OUTPUT_INTENT_H
#define BRST_OUTPUT_INTENT_H

#include "brst_dict.h"
#include "brst_doc.h"

typedef BRST_Dict BRST_OutputIntent;

BRST_EXPORT(BRST_OutputIntent)
BRST_OutputIntent_New(BRST_Doc pdf,
    BRST_CSTR  identifier,
    BRST_CSTR  condition,
    BRST_CSTR  registry,
    BRST_CSTR  info,
    BRST_Array outputprofile
);

BRST_EXPORT(BRST_STATUS)
BRST_AddIntent(BRST_Doc pdf,
    BRST_OutputIntent intent
);

#endif /* BRST_OUTPUT_INTENT_H */