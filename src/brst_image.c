#include "brst_external.h"
#include "brst_types.h"
#include "brst_mmgr.h"
#include "brst_encrypt.h"
#include "brst_stream.h"
#include "brst_xref.h"
#include "brst_dict.h"
#include "private/brst_dict.h"
#include "brst_encoder.h"
#include "brst_error.h"
#include "brst_consts.h"
#include "private/brst_utils.h"
#include "brst_array.h"
#include "brst_image.h"
#include "brst_matrix.h"
#include "private/brst_image.h"
#include "private/brst_number.h"
#include "private/brst_name.h"

BRST_EXPORT(BRST_Point)
BRST_Image_Size(BRST_Image image)
{
    BRST_Number width;
    BRST_Number height;
    BRST_Point ret = { 0, 0 };

    BRST_PTRACE(" BRST_Image_GetSize\n");

    if (!BRST_Image_Validate(image))
        return ret;

    width  = BRST_Dict_Item(image, "Width", BRST_OCLASS_NUMBER);
    height = BRST_Dict_Item(image, "Height", BRST_OCLASS_NUMBER);

    if (width && height) {
        ret.x = (BRST_REAL)BRST_Number_Value(width);
        ret.y = (BRST_REAL)BRST_Number_Value(height);
    }

    return ret;
}

BRST_EXPORT(BRST_STATUS)
BRST_Image_Size2(BRST_Image image, BRST_Point* size)
{
    BRST_Number width;
    BRST_Number height;
    size->x = 0;
    size->y = 0;

    BRST_PTRACE(" BRST_Image_GetSize\n");

    if (!BRST_Image_Validate(image))
        return BRST_INVALID_IMAGE;

    width  = BRST_Dict_Item(image, "Width", BRST_OCLASS_NUMBER);
    height = BRST_Dict_Item(image, "Height", BRST_OCLASS_NUMBER);

    if (width && height) {
        size->x = (BRST_REAL)BRST_Number_Value(width);
        size->y = (BRST_REAL)BRST_Number_Value(height);
    }

    return BRST_OK;
}

BRST_EXPORT(BRST_UINT)
BRST_Image_BitsPerComponent(BRST_Image image)
{
    BRST_Number n;

    BRST_PTRACE(" BRST_Image_GetBitsPerComponent\n");

    if (!BRST_Image_Validate(image))
        return 0;

    n = BRST_Dict_Item(image, "BitsPerComponent", BRST_OCLASS_NUMBER);

    if (!n)
        return 0;

    return BRST_Number_Value(n);
}

BRST_EXPORT(const char*)
BRST_Image_ColorSpace(BRST_Image image)
{
    BRST_Name n;

    BRST_PTRACE(" BRST_Image_GetColorSpace\n");

    n = BRST_Dict_Item(image, "ColorSpace", BRST_OCLASS_NAME);

    if (!n) {
        BRST_Array a;

        BRST_Error_Reset(image->error);

        a = BRST_Dict_Item(image, "ColorSpace", BRST_OCLASS_ARRAY);

        if (a) {
            n = BRST_Array_Item(a, 0, BRST_OCLASS_NAME);
        }
    }

    if (!n) {
        BRST_Error_Check(image->error);
        return NULL;
    }

    return BRST_Name_Value(n);
}

BRST_EXPORT(BRST_UINT)
BRST_Image_Width(BRST_Image image)
{
    return (BRST_UINT)BRST_Image_Size(image).x;
}

BRST_EXPORT(BRST_UINT)
BRST_Image_Height(BRST_Image image)
{
    return (BRST_UINT)BRST_Image_Size(image).y;
}

BRST_EXPORT(BRST_STATUS)
BRST_Image_SetMaskImage(BRST_Image image,
    BRST_Image mask_image)
{
    if (!BRST_Image_Validate(image))
        return BRST_INVALID_IMAGE;

    if (!BRST_Image_Validate(mask_image))
        return BRST_INVALID_IMAGE;

    if (BRST_Image_SetMask(mask_image, BRST_TRUE) != BRST_OK)
        return BRST_Error_Check(image->error);

    return BRST_Dict_Add(image, "Mask", mask_image);
}

BRST_EXPORT(BRST_STATUS)
BRST_Image_SetColorMask(BRST_Image image,
    BRST_UINT rmin,
    BRST_UINT rmax,
    BRST_UINT gmin,
    BRST_UINT gmax,
    BRST_UINT bmin,
    BRST_UINT bmax)
{
    BRST_Array array;
    const char* name;
    BRST_STATUS ret = BRST_OK;

    if (!BRST_Image_Validate(image))
        return BRST_INVALID_IMAGE;

    if (BRST_Dict_Item(image, "ImageMask", BRST_OCLASS_BOOLEAN))
        return BRST_Error_Raise(image->error, BRST_INVALID_OPERATION, 0);

    if (BRST_Image_BitsPerComponent(image) != 8)
        return BRST_Error_Raise(image->error, BRST_INVALID_BIT_PER_COMPONENT,
            0);

    name = BRST_Image_ColorSpace(image);
    if (!name || BRST_StrCmp(COL_RGB, name) != 0)
        return BRST_Error_Raise(image->error, BRST_INVALID_COLOR_SPACE, 0);

    /* Each integer must be in the range 0 to 2^BitsPerComponent - 1 */
    if (rmax > 255 || gmax > 255 || bmax > 255)
        return BRST_Error_Raise(image->error, BRST_INVALID_PARAMETER, 0);

    array = BRST_Array_New(image->mmgr);
    if (!array)
        return BRST_Error_Check(image->error);

    ret += BRST_Dict_Add(image, "Mask", array);
    ret += BRST_Array_AddNumber(array, rmin);
    ret += BRST_Array_AddNumber(array, rmax);
    ret += BRST_Array_AddNumber(array, gmin);
    ret += BRST_Array_AddNumber(array, gmax);
    ret += BRST_Array_AddNumber(array, bmin);
    ret += BRST_Array_AddNumber(array, bmax);

    if (ret != BRST_OK)
        return BRST_Error_Check(image->error);

    return BRST_OK;
}

BRST_EXPORT(BRST_STATUS)
BRST_Image_AddSMask(BRST_Image image,
    BRST_Image smask)
{

    const char* name;

    if (!BRST_Image_Validate(image))
        return BRST_INVALID_IMAGE;
    if (!BRST_Image_Validate(smask))
        return BRST_INVALID_IMAGE;

    if (BRST_Dict_Item(image, "SMask", BRST_OCLASS_BOOLEAN))
        return BRST_Error_Raise(image->error, BRST_INVALID_OPERATION, 0);

    name = BRST_Image_ColorSpace(smask);
    if (!name || BRST_StrCmp(COL_GRAY, name) != 0)
        return BRST_Error_Raise(smask->error, BRST_INVALID_COLOR_SPACE, 0);

    return BRST_Dict_Add(image, "SMask", smask);
}
