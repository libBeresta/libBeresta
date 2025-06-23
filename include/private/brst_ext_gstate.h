#ifndef PRIVATE_BRST_EXT_GSTATE_H
#define PRIVATE_BRST_EXT_GSTATE_H

BRST_BOOL
BRST_ExtGState_Validate(
    BRST_ExtGState ext_gstate
);

BRST_Dict
BRST_ExtGState_New(
    BRST_MMgr mmgr, 
    BRST_Xref xref
);

BRST_STATUS
ExtGState_Check(
    BRST_ExtGState ext_gstate
);

#endif /* PRIVATE_BRST_EXT_GSTATE_H */