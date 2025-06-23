#ifndef PRIVATE_BRST_IMAGE_H
#define PRIVATE_BRST_IMAGE_H

#include "brst_mmgr.h"
#include "brst_encrypt.h"
#include "brst_array.h"

extern const char* COL_CMYK;
extern const char* COL_RGB;
extern const char* COL_GRAY;

BRST_BOOL
BRST_Image_Validate(
    BRST_Image image
);

BRST_STATUS
BRST_Image_SetMask(
    BRST_Image image,
    BRST_BOOL  mask
);

BRST_STATUS
BRST_Image_SetColorSpace(
    BRST_Image image,
    BRST_Array colorspace
);

BRST_STATUS
BRST_Image_SetRenderingIntent(
    BRST_Image  image,
    const char* intent
);

#endif /* PRIVATE_BRST_IMAGE_H */
