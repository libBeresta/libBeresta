#ifndef PRIVATE_BRST_INFO_H
#define PRIVATE_BRST_INFO_H

#include "brst_dict.h"
#include "private/brst_dict.h"
#include "brst_mmgr.h"

BRST_STATUS
BRST_Info_SetInfoAttr(
    BRST_Dict     info,
    BRST_InfoType type,
    const char*   value,
    BRST_Encoder  encoder
);

const char*
BRST_Info_InfoAttr(
    BRST_Dict     info,
    BRST_InfoType type
);

BRST_STATUS
BRST_Info_SetInfoDateAttr(
    BRST_Dict     info,
    BRST_InfoType type,
    BRST_Date     value
);
#endif /* PRIVATE_BRST_INFO_H */