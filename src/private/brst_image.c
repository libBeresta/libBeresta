#include "brst_types.h"
#include "brst_encrypt.h"
#include "brst_consts.h"
#include "brst_array.h"
#include "brst_error.h"
#include "brst_mmgr.h"
#include "brst_stream.h"
#include "private/brst_boolean.h"
#include "private/brst_name.h"
#include "brst_xref.h"
#include "brst_dict.h"
#include "private/brst_dict.h"
#include "private/brst_utils.h"
#include "brst_image.h"
#include "private/brst_image.h"

const char* COL_CMYK = "DeviceCMYK";
const char* COL_RGB  = "DeviceRGB";
const char* COL_GRAY = "DeviceGray";

BRST_BOOL
BRST_Image_Validate(BRST_Image image)
{
    BRST_Name subtype;

    BRST_PTRACE(" BRST_Image_Validate\n");

    if (!image)
        return BRST_FALSE;

    if (image->header.obj_class != (BRST_OSUBCLASS_XOBJECT | BRST_OCLASS_DICT)) {
        BRST_Error_Raise(image->error, BRST_INVALID_IMAGE, 0);
        return BRST_FALSE;
    }

    subtype = BRST_Dict_Item(image, "Subtype", BRST_OCLASS_NAME);
    if (!subtype || BRST_StrCmp(BRST_Name_Value(subtype), "Image") != 0) {
        BRST_Error_Raise(image->error, BRST_INVALID_IMAGE, 0);
        return BRST_FALSE;
    }

    return BRST_TRUE;
}

BRST_STATUS
BRST_Image_SetMask(BRST_Image image,
    BRST_BOOL mask)
{
    BRST_Boolean image_mask;

    if (!BRST_Image_Validate(image))
        return BRST_INVALID_IMAGE;

    if (mask && BRST_Image_BitsPerComponent(image) != 1)
        return BRST_Error_Set(image->error, BRST_INVALID_BIT_PER_COMPONENT,
            0);

    image_mask = BRST_Dict_Item(image, "ImageMask", BRST_OCLASS_BOOLEAN);
    if (!image_mask) {
        BRST_STATUS ret;
        image_mask = BRST_Boolean_New(image->mmgr, BRST_FALSE);

        if ((ret = BRST_Dict_Add(image, "ImageMask", image_mask)) != BRST_OK)
            return ret;
    }

    BRST_Boolean_SetValue(image_mask, mask);
    return BRST_OK;
}

BRST_STATUS
BRST_Image_SetColorSpace(BRST_Image image,
    BRST_Array colorspace)
{
    if (!BRST_Image_Validate(image))
        return BRST_INVALID_IMAGE;

    return BRST_Dict_Add(image, "ColorSpace", colorspace);
}

BRST_STATUS
BRST_Image_SetRenderingIntent(BRST_Image image,
    const char* intent)
{
    if (!BRST_Image_Validate(image))
        return BRST_INVALID_IMAGE;

    return BRST_Dict_AddName(image, "Intent", intent);
}
