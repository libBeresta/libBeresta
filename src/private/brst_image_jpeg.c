#include "brst_types.h"
#include "brst_encrypt.h"
#include "brst_stream.h"
#include "brst_mmgr.h"
#include "private/brst_name.h"
#include "private/brst_number.h"
#include "brst_array.h"
#include "private/brst_array.h"
#include "brst_image.h"
#include "private/brst_image.h"
#include "brst_xref.h"
#include "private/brst_xref.h"
#include "brst_consts.h"
#include "private/brst_utils.h"
#include "private/brst_defines.h"
#include "brst_error.h"

static BRST_STATUS
LoadJpegHeader(BRST_Image image,
    BRST_Stream stream);

/*---------------------------------------------------------------------------*/

static BRST_STATUS
LoadJpegHeader(BRST_Image image,
    BRST_Stream stream)
{
    BRST_UINT16 tag;
    BRST_UINT16 height;
    BRST_UINT16 width;
    BRST_BYTE precision;
    BRST_BYTE num_components;
    const char* color_space_name;
    BRST_UINT len;
    BRST_STATUS ret;
    BRST_Array array;

    BRST_PTRACE((" BRST_Image_LoadJpegHeader\n"));

    len = 2;
    if (BRST_Stream_Read(stream, (BRST_BYTE*)&tag, &len) != BRST_OK)
        return BRST_Error_Code(stream->error);

    BRST_UInt16Swap(&tag);
    if (tag != 0xFFD8)
        return BRST_INVALID_JPEG_DATA;

    /* find SOF record */
    for (;;) {
        BRST_UINT16 size;

        len = 2;
        if (BRST_Stream_Read(stream, (BRST_BYTE*)&tag, &len) != BRST_OK)
            return BRST_Error_Code(stream->error);

        BRST_UInt16Swap(&tag);

        len = 2;
        if (BRST_Stream_Read(stream, (BRST_BYTE*)&size, &len) != BRST_OK)
            return BRST_Error_Code(stream->error);

        BRST_UInt16Swap(&size);

        BRST_PTRACE(("tag=%04X size=%u\n", tag, size));

        if (tag == 0xFFC0 || tag == 0xFFC1 || tag == 0xFFC2 || tag == 0xFFC9) {

            len = 1;
            if (BRST_Stream_Read(stream, (BRST_BYTE*)&precision, &len) != BRST_OK)
                return BRST_Error_Code(stream->error);

            len = 2;
            if (BRST_Stream_Read(stream, (BRST_BYTE*)&height, &len) != BRST_OK)
                return BRST_Error_Code(stream->error);

            BRST_UInt16Swap(&height);

            len = 2;
            if (BRST_Stream_Read(stream, (BRST_BYTE*)&width, &len) != BRST_OK)
                return BRST_Error_Code(stream->error);

            BRST_UInt16Swap(&width);

            len = 1;
            if (BRST_Stream_Read(stream, (BRST_BYTE*)&num_components, &len) != BRST_OK)
                return BRST_Error_Code(stream->error);

            break;
        } else if ((tag | 0x00FF) != 0xFFFF)
            /* lost marker */
            return BRST_Error_Set(image->error, BRST_UNSUPPORTED_JPEG_FORMAT,
                0);

        if (BRST_Stream_Seek(stream, size - 2, BRST_SEEK_CUR) != BRST_OK)
            return BRST_Error_Code(stream->error);
    }

    if (BRST_Dict_AddNumber(image, "Height", height) != BRST_OK)
        return BRST_Error_Code(stream->error);

    if (BRST_Dict_AddNumber(image, "Width", width) != BRST_OK)
        return BRST_Error_Code(stream->error);

    /* classification of RGB and CMYK is less than perfect
     * YCbCr and YCCK are classified into RGB or CMYK.
     *
     * It is necessary to read APP14 data to distinguish colorspace perfectly.

     */
    switch (num_components) {
    case 1:
        color_space_name = COL_GRAY;
        break;
    case 3:
        color_space_name = COL_RGB;
        break;
    case 4:
        array = BRST_Array_New(image->mmgr);
        if (!array)
            return BRST_Error_Code(stream->error);

        ret = BRST_Dict_Add(image, "Decode", array);
        if (ret != BRST_OK)
            return BRST_Error_Code(stream->error);

        ret += BRST_Array_Add(array, BRST_Number_New(image->mmgr, 1));
        ret += BRST_Array_Add(array, BRST_Number_New(image->mmgr, 0));
        ret += BRST_Array_Add(array, BRST_Number_New(image->mmgr, 1));
        ret += BRST_Array_Add(array, BRST_Number_New(image->mmgr, 0));
        ret += BRST_Array_Add(array, BRST_Number_New(image->mmgr, 1));
        ret += BRST_Array_Add(array, BRST_Number_New(image->mmgr, 0));
        ret += BRST_Array_Add(array, BRST_Number_New(image->mmgr, 1));
        ret += BRST_Array_Add(array, BRST_Number_New(image->mmgr, 0));

        if (ret != BRST_OK)
            return BRST_Error_Code(stream->error);

        color_space_name = COL_CMYK;

        break;
    default:
        return BRST_Error_Set(image->error, BRST_UNSUPPORTED_JPEG_FORMAT,
            0);
    }

    if (BRST_Dict_Add(image, "ColorSpace",
            BRST_Name_New(image->mmgr, color_space_name))
        != BRST_OK)
        return BRST_Error_Code(stream->error);

    if (BRST_Dict_Add(image, "BitsPerComponent",
            BRST_Number_New(image->mmgr, precision))
        != BRST_OK)
        return BRST_Error_Code(stream->error);

    return BRST_OK;
}

BRST_Image
BRST_Image_Jpeg_Load(BRST_MMgr mmgr,
    BRST_Stream jpeg_data,
    BRST_Xref xref)
{
    BRST_Dict image;
    BRST_STATUS ret = BRST_OK;

    BRST_PTRACE((" BRST_Image_Jpeg_Load\n"));

    image = BRST_DictStream_New(mmgr, xref);
    if (!image)
        return NULL;

    image->header.obj_class |= BRST_OSUBCLASS_XOBJECT;

    /* add required elements */
    image->filter = BRST_STREAM_FILTER_DCT_DECODE;
    ret += BRST_Dict_AddName(image, "Type", "XObject");
    ret += BRST_Dict_AddName(image, "Subtype", "Image");
    if (ret != BRST_OK)
        return NULL;

    if (LoadJpegHeader(image, jpeg_data) != BRST_OK)
        return NULL;

    if (BRST_Stream_Seek(jpeg_data, 0, BRST_SEEK_SET) != BRST_OK)
        return NULL;

    for (;;) {
        BRST_BYTE buf[BRST_STREAM_BUF_SIZE];
        BRST_UINT len   = BRST_STREAM_BUF_SIZE;
        BRST_STATUS ret = BRST_Stream_Read(jpeg_data, buf,
            &len);

        if (ret != BRST_OK) {
            if (ret == BRST_STREAM_EOF) {
                if (len > 0) {
                    ret = BRST_Stream_Write(image->stream, buf, len);
                    if (ret != BRST_OK)
                        return NULL;
                }
                break;
            } else
                return NULL;
        }

        if (BRST_Stream_Write(image->stream, buf, len) != BRST_OK)
            return NULL;
    }

    return image;
}

BRST_Image
BRST_Image_Jpeg_LoadFromMem(BRST_MMgr mmgr,
    const BRST_BYTE* buf,
    BRST_UINT size,
    BRST_Xref xref)
{
    BRST_Stream jpeg_data;
    BRST_Image image;

    BRST_PTRACE((" BRST_Image_Jpeg_LoadFromMem\n"));

    jpeg_data = BRST_MemStream_New(mmgr, size);
    if (!BRST_Stream_Validate(jpeg_data)) {
        BRST_Error_Raise(BRST_MMgr_Error(mmgr), BRST_INVALID_STREAM, 0);
        return NULL;
    }

    if (BRST_Stream_Write(jpeg_data, buf, size) != BRST_OK) {
        BRST_Stream_Free(jpeg_data);
        return NULL;
    }

    image = BRST_Image_Jpeg_Load(mmgr, jpeg_data, xref);

    /* destroy file stream */
    BRST_Stream_Free(jpeg_data);

    return image;
}
