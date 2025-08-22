#include "brst_types.h"
#include "brst_encrypt.h"
#include "brst_stream.h"
#include "brst_mmgr.h"
#include "brst_array.h"
#include "brst_image.h"
#include "private/brst_image.h"
#include "brst_xref.h"
#include "private/brst_xref.h"
#include "brst_geometry_defines.h"
#include "brst_consts.h"
#include "private/brst_utils.h"
#include "brst_error.h"
#include "brst_dict.h"
#include "private/brst_dict.h"

BRST_Image
BRST_Image_Raw_Load(BRST_MMgr mmgr,
    BRST_Stream raw_data,
    BRST_Xref xref,
    BRST_UINT width,
    BRST_UINT height,
    BRST_ColorSpace color_space)
{
    BRST_Dict image;
    BRST_STATUS ret = BRST_OK;
    BRST_UINT size;

    BRST_PTRACE(" BRST_Image_Raw_Load\n");

    if (color_space != BRST_CS_DEVICE_GRAY && color_space != BRST_CS_DEVICE_RGB && color_space != BRST_CS_DEVICE_CMYK) {
        BRST_Error_Set(BRST_MMgr_Error(mmgr), BRST_INVALID_COLOR_SPACE, 0);
        return NULL;
    }

    image = BRST_Dict_New_Stream_Init(mmgr, xref);
    if (!image)
        return NULL;

    image->header.obj_class |= BRST_OSUBCLASS_XOBJECT;
    ret += BRST_Dict_AddName(image, "Type", "XObject");
    ret += BRST_Dict_AddName(image, "Subtype", "Image");
    if (ret != BRST_OK)
        return NULL;

    if (color_space == BRST_CS_DEVICE_GRAY) {
        size = width * height;
        ret  = BRST_Dict_AddName(image, "ColorSpace", COL_GRAY);
    } else if (color_space == BRST_CS_DEVICE_CMYK) {
        size = width * height * 4;
        ret  = BRST_Dict_AddName(image, "ColorSpace", COL_CMYK);
    } else {
        size = width * height * 3;
        ret  = BRST_Dict_AddName(image, "ColorSpace", COL_RGB);
    }

    if (ret != BRST_OK)
        return NULL;

    if (BRST_Dict_AddNumber(image, "Width", width) != BRST_OK)
        return NULL;

    if (BRST_Dict_AddNumber(image, "Height", height) != BRST_OK)
        return NULL;

    if (BRST_Dict_AddNumber(image, "BitsPerComponent", 8) != BRST_OK)
        return NULL;

    if (BRST_Stream_WriteToStream(raw_data, image->stream, 0, NULL) != BRST_OK)
        return NULL;

    if (image->stream->size != size) {
        BRST_Error_Set(image->error, BRST_INVALID_IMAGE, 0);
        return NULL;
    }

    return image;
}

BRST_Image
BRST_Image_Raw_LoadFromMem(BRST_MMgr mmgr,
    const BRST_BYTE* buf,
    BRST_Xref xref,
    BRST_UINT width,
    BRST_UINT height,
    BRST_ColorSpace color_space,
    BRST_UINT bits_per_component)
{
    BRST_Dict image;
    BRST_STATUS ret = BRST_OK;
    BRST_UINT size  = 0;

    BRST_PTRACE(" BRST_Image_LoadRawImageFromMem\n");

    if (color_space != BRST_CS_DEVICE_GRAY && color_space != BRST_CS_DEVICE_RGB && color_space != BRST_CS_DEVICE_CMYK) {
        BRST_Error_Set(BRST_MMgr_Error(mmgr), BRST_INVALID_COLOR_SPACE, 0);
        return NULL;
    }

    if (bits_per_component != 1 && bits_per_component != 2 && bits_per_component != 4 && bits_per_component != 8) {
        BRST_Error_Set(BRST_MMgr_Error(mmgr), BRST_INVALID_IMAGE, 0);
        return NULL;
    }

    image = BRST_Dict_New_Stream_Init(mmgr, xref);
    if (!image)
        return NULL;

    image->header.obj_class |= BRST_OSUBCLASS_XOBJECT;
    ret += BRST_Dict_AddName(image, "Type", "XObject");
    ret += BRST_Dict_AddName(image, "Subtype", "Image");
    if (ret != BRST_OK)
        return NULL;

    switch (color_space) {
    case BRST_CS_DEVICE_GRAY:
        size = (BRST_UINT)((BRST_DOUBLE)width * height / (8 / bits_per_component) + 0.876);
        ret  = BRST_Dict_AddName(image, "ColorSpace", COL_GRAY);
        break;
    case BRST_CS_DEVICE_RGB:
        size = (BRST_UINT)((BRST_DOUBLE)width * height / (8 / bits_per_component) + 0.876);
        size *= 3;
        ret = BRST_Dict_AddName(image, "ColorSpace", COL_RGB);
        break;
    case BRST_CS_DEVICE_CMYK:
        size = (BRST_UINT)((BRST_DOUBLE)width * height / (8 / bits_per_component) + 0.876);
        size *= 4;
        ret = BRST_Dict_AddName(image, "ColorSpace", COL_CMYK);
        break;
    default:;
    }

    if (ret != BRST_OK)
        return NULL;

    if (BRST_Dict_AddNumber(image, "Width", width) != BRST_OK)
        return NULL;

    if (BRST_Dict_AddNumber(image, "Height", height) != BRST_OK)
        return NULL;

    if (BRST_Dict_AddNumber(image, "BitsPerComponent", bits_per_component)
        != BRST_OK)
        return NULL;

    if (BRST_Stream_Write(image->stream, buf, size) != BRST_OK)
        return NULL;

    return image;
}
