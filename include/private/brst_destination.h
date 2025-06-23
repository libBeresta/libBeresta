#ifndef PRIVATE_BRST_DESTINATION_H
#define PRIVATE_BRST_DESTINATION_H

extern const char* const BRST_DESTINATION_TYPE_NAMES[];
typedef enum _BRST_DestinationType {
    BRST_XYZ = 0,
    BRST_FIT,
    BRST_FIT_H,
    BRST_FIT_V,
    BRST_FIT_R,
    BRST_FIT_B,
    BRST_FIT_BH,
    BRST_FIT_BV,
    BRST_DST_EOF
} BRST_DestinationType;

BRST_Destination
BRST_Destination_New(
    BRST_MMgr mgr,
    BRST_Page target,
    BRST_Xref xref
);

BRST_BOOL
BRST_Destination_Validate(
    BRST_Destination dst
);
#endif /* PRIVATE_BRST_DESTINATION_H */