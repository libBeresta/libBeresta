#include "brst_encrypt.h"
#include "brst_encoder.h"
#include "brst_stream.h"
#include "brst_mmgr.h"
#include "brst_xref.h"
#include "brst_dict.h"
#include "private/brst_dict.h"
#include "private/brst_stream.h"
#include "brst_array.h"
#include "private/brst_real.h"
#include "private/brst_array.h"
#include "private/brst_xref.h"
#include "brst_image.h"
#include "private/brst_image.h"
#include "brst_shading.h"
#include "brst_error.h"
#include "private/brst_utils.h"
#include "brst_geometry_defines.h"
#include "brst_consts.h"

typedef struct _RGBVertex {
    BRST_UINT8 EdgeFlag;
    BRST_UINT32 X;
    BRST_UINT32 Y;
    BRST_UINT8 RGB[3];
} RGBVertex;

// TODO Add shading for these color spaces
// static const char* COL_RGB = "DeviceRGB";
// static const char *COL_CMYK = "DeviceCMYK";
// static const char *COL_GRAY = "DeviceGray";

/* bbox is filled with xMin, xMax, yMin, yMax */
static BRST_BOOL _GetDecodeArrayVertexValues(BRST_Shading shading,
    BRST_REAL* bbox)
{
    BRST_Array decodeArray;
    BRST_Real r;
    int i;

    if (!shading) {
        return BRST_FALSE;
    }

    decodeArray = (BRST_Array)(BRST_Dict_Item(shading, "Decode",
        BRST_OCLASS_ARRAY));
    if (!decodeArray) {
        return BRST_FALSE;
    }

    for (i = 0; i < 4; ++i) {
        r = BRST_Array_Item(decodeArray, i, BRST_OCLASS_REAL);
        if (!r) {
            return BRST_FALSE;
        }

        bbox[i] = BRST_Real_Value(r);
    }

    return BRST_TRUE;
}

static void UINT32Swap(BRST_UINT32* value)
{
    BRST_BYTE b[4];

    BRST_MemCpy(b, (BRST_BYTE*)value, 4);
    *value = (BRST_UINT32)((BRST_UINT32)b[0] << 24 | (BRST_UINT32)b[1] << 16 | (BRST_UINT32)b[2] << 8 | (BRST_UINT32)b[3]);
}

/* Encode a position coordinate for writing */
static BRST_UINT32 _EncodeValue(BRST_REAL x, BRST_REAL xMin, BRST_REAL xMax)
{
    BRST_DOUBLE norm = (x - xMin) / (xMax - xMin);
    BRST_DOUBLE max  = (BRST_DOUBLE)(0xFFFFFFFF);
    BRST_UINT32 enc  = (BRST_UINT32)(norm * max);
    UINT32Swap(&enc);
    return enc;
}

BRST_Shading
BRST_Shading_New(
    BRST_MMgr mmgr,
    BRST_Xref xref,
    BRST_ShadingType type,
    BRST_ColorSpace colorSpace,
    BRST_REAL xMin, BRST_REAL xMax,
    BRST_REAL yMin, BRST_REAL yMax)
{
    BRST_Shading shading;
    BRST_Array decodeArray;
    BRST_STATUS ret = BRST_OK;
    int i;

    BRST_PTRACE(" BRST_Shading_New\n");

    /* Validate shading type: */
    switch (type) {
    case BRST_SHADING_FREE_FORM_TRIANGLE_MESH:
        break;

    default:
        BRST_Error_Set(BRST_MMgr_Error(mmgr), BRST_INVALID_SHADING_TYPE, 0);
        return NULL;
    }

    decodeArray = BRST_Array_New(mmgr);
    if (!decodeArray) {
        return NULL;
    }

    /* X-range */
    ret += BRST_Array_AddReal(decodeArray, xMin);
    ret += BRST_Array_AddReal(decodeArray, xMax);

    /* Y-range */
    ret += BRST_Array_AddReal(decodeArray, yMin);
    ret += BRST_Array_AddReal(decodeArray, yMax);

    const char* colName = NULL;
    switch (colorSpace) {
    case BRST_CS_DEVICE_RGB:
        colName = COL_RGB;
        for (i = 0; i < 3; ++i) {
            ret += BRST_Array_AddReal(decodeArray, 0.0);
            ret += BRST_Array_AddReal(decodeArray, 1.0);
        }
        break;

    default:
        BRST_Error_Set(BRST_MMgr_Error(mmgr), BRST_INVALID_COLOR_SPACE, 0);
        return NULL;
    }

    if (ret != BRST_OK) {
        return NULL;
    }

    shading = BRST_Dict_New_Stream_Init(mmgr, xref);
    if (!shading) {
        return NULL;
    }

    shading->header.obj_class |= BRST_OSUBCLASS_SHADING;
    ret += BRST_Dict_AddNumber(shading, "ShadingType", type);
    ret += BRST_Dict_AddName(shading, "ColorSpace", colName);

    switch (type) {
    case BRST_SHADING_FREE_FORM_TRIANGLE_MESH:
        ret += BRST_Dict_AddNumber(shading, "BitsPerCoordinate", 32);
        ret += BRST_Dict_AddNumber(shading, "BitsPerComponent", 8);
        ret += BRST_Dict_AddNumber(shading, "BitsPerFlag", 8);
        ret += BRST_Dict_Add(shading, "Decode", decodeArray);
        break;

    default:
        BRST_Error_Set(BRST_MMgr_Error(mmgr), BRST_INVALID_SHADING_TYPE, 0);
        return NULL;
    }

    if (ret != BRST_OK) {
        return NULL;
    }

    return shading;
}

BRST_STATUS
BRST_Shading_AddVertexRGB(BRST_Shading shading,
    BRST_Shading_FreeFormTriangleMeshEdgeFlag edgeFlag,
    BRST_REAL x, BRST_REAL y,
    BRST_UINT8 r, BRST_UINT8 g, BRST_UINT8 b)
{
    BRST_STATUS ret = BRST_OK;
    RGBVertex vert;
    float bbox[4];

    BRST_PTRACE(" BRST_Shading_AddVertexRGB\n");

    if (!shading) {
        return BRST_INVALID_OBJECT;
    }

    if (_GetDecodeArrayVertexValues(shading, bbox) != BRST_TRUE) {
        return BRST_Error_Set(shading->error, BRST_INVALID_OBJECT, 0);
    }

    vert.EdgeFlag = (BRST_UINT8)edgeFlag;
    vert.X        = _EncodeValue(x, bbox[0], bbox[1]);
    vert.Y        = _EncodeValue(y, bbox[2], bbox[3]);
    vert.RGB[0]   = r;
    vert.RGB[1]   = g;
    vert.RGB[2]   = b;

    ret = BRST_Stream_Write(shading->stream,
        (BRST_BYTE*)(&vert.EdgeFlag), sizeof(vert.EdgeFlag));
    if (ret != BRST_OK) {
        return ret;
    }

    ret = BRST_Stream_Write(shading->stream,
        (BRST_BYTE*)(&vert.X), sizeof(vert.X));
    if (ret != BRST_OK) {
        return ret;
    }

    ret = BRST_Stream_Write(shading->stream,
        (BRST_BYTE*)(&vert.Y), sizeof(vert.Y));
    if (ret != BRST_OK) {
        return ret;
    }

    ret = BRST_Stream_Write(shading->stream,
        (BRST_BYTE*)(&vert.RGB), sizeof(vert.RGB));

    return ret;
}
