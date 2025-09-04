#include "brst_config.h"
#include "brst_types.h"
#include "brst_encrypt.h"
#include "brst_encoder.h"
#include "brst_mmgr.h"
#include "brst_stream.h"
#include "private/brst_stream.h"
#include "brst_xref.h"
#include "brst_dict.h"
#include "private/brst_dict.h"
#include "brst_transmatrix.h"
#include "brst_array.h"
#include "private/brst_array.h"
#include "private/brst_string.h"
#include "private/brst_binary.h"
#include "brst_error.h"
#include "private/brst_utils.h"
#include "brst_image.h"
#include "private/brst_image.h"
#include "private/brst_image_png.h"
#include "private/brst_xref.h"
#include "brst_consts.h"

#ifdef LIBBRST_HAVE_LIBPNG

#include <png.h>
#include <string.h>

BRST_Image
BRST_Image_Png_LoadFromStream(BRST_MMgr mmgr,
    BRST_Xref xref,
    BRST_BOOL compression_mode,
    BRST_Stream imagedata,
    BRST_BOOL delayed_loading)
{
    BRST_Image image;
    BRST_Dict smask;

    BRST_PTRACE(" BRST_Image_LoadPngImage\n");

    image = BRST_Image_Png_Load(mmgr, imagedata, xref,
        delayed_loading);

    if (image && (compression_mode & BRST_COMP_IMAGE)) {
        image->filter = BRST_STREAM_FILTER_FLATE_DECODE;

        // is there an alpha layer? then compress it also
        smask = BRST_Dict_Item(image, "SMask", BRST_OCLASS_DICT);
        if (smask)
            smask->filter = BRST_STREAM_FILTER_FLATE_DECODE;
    }

    return image;
}

static void
PngErrorFunc(png_structp png_ptr,
    const char* msg);

static void
PngReadFunc(png_structp png_ptr,
    png_bytep data,
    png_uint_32 length)
{
    BRST_UINT len      = length;
    BRST_Stream stream = (BRST_Stream)png_get_io_ptr(png_ptr);

    BRST_Stream_Read(stream, data, &len);
}

static BRST_STATUS
LoadPngData(BRST_Dict image,
    BRST_Xref xref,
    BRST_Stream png_data,
    BRST_BOOL delayed_loading);

static void
PngErrorFunc(png_structp png_ptr,
    const char* msg);

static void
PngWarnFunc(png_structp png_ptr,
    const char* msg);

static BRST_STATUS
ReadPngData_Interlaced(BRST_Dict image,
    png_structp png_ptr,
    png_infop info_ptr);

static BRST_STATUS
ReadPngData(BRST_Dict image,
    png_structp png_ptr,
    png_infop info_ptr);

static BRST_STATUS
CreatePallet(BRST_Dict image,
    png_structp png_ptr,
    png_infop info_ptr);

static BRST_STATUS
PngBeforeWrite(BRST_Dict obj);

static BRST_STATUS
PngAfterWrite(BRST_Dict obj);

/*---------------------------------------------------------------------------*/

static void
PngErrorFunc(png_structp png_ptr,
    const char* msg)
{
    char error_number[16];
    BRST_UINT i;
    BRST_STATUS detail_no;
    BRST_Error error;

    /* pick out error-number from error message */
    BRST_MemSet(error_number, 0, 16);

    for (i = 0; i < 15; i++) {
        error_number[i] = *(msg + i);
        if (*(msg + i + 1) == ' ')
            break;
    }

    error     = (BRST_Error)png_get_error_ptr(png_ptr);
    detail_no = (BRST_STATUS)BRST_AToI(error_number);
    BRST_Error_Set(error, BRST_LIBPNG_ERROR, detail_no);
}

static void
PngWarnFunc(png_structp png_ptr,
    const char* msg)
{
    // Warning does not prevent the job to be done
    // So it can be safely ignored.
    // printf("WARNING: %s\n", msg);
}

static BRST_STATUS
ReadPngData_Interlaced(BRST_Dict image,
    png_structp png_ptr,
    png_infop info_ptr)
{
    BRST_UINT len           = (BRST_UINT)png_get_rowbytes(png_ptr, info_ptr);
    png_uint_32 height      = png_get_image_height(png_ptr, info_ptr);
    png_bytep* row_pointers = BRST_GetMem(image->mmgr,
        height * sizeof(png_bytep));

    if (row_pointers) {
        BRST_UINT i;

        BRST_MemSet(row_pointers, 0, height * sizeof(png_bytep));
        for (i = 0; i < (BRST_UINT)height; i++) {
            row_pointers[i] = BRST_GetMem(image->mmgr, len);

            if (BRST_Error_Code(image->error) != BRST_OK)
                break;
        }

        if (BRST_Error_Code(image->error) == BRST_OK) {
            png_read_image(png_ptr, row_pointers);
            if (BRST_Error_Code(image->error) == BRST_OK) { /* add this line */
                for (i = 0; i < (BRST_UINT)height; i++) {
                    if (BRST_Stream_Write(image->stream, row_pointers[i], len) != BRST_OK)
                        break;
                }
            }
        }

        /* clean up */
        for (i = 0; i < (BRST_UINT)height; i++) {
            BRST_FreeMem(image->mmgr, row_pointers[i]);
        }

        BRST_FreeMem(image->mmgr, row_pointers);
    }

    return BRST_Error_Code(image->error);
}

static BRST_STATUS
ReadPngData(BRST_Dict image,
    png_structp png_ptr,
    png_infop info_ptr)
{
    BRST_UINT len      = (BRST_UINT)png_get_rowbytes(png_ptr, info_ptr);
    png_uint_32 height = png_get_image_height(png_ptr, info_ptr);
    png_bytep buf_ptr  = BRST_GetMem(image->mmgr, len);

    if (buf_ptr) {
        BRST_UINT i;

        for (i = 0; i < (BRST_UINT)height; i++) {
            png_read_rows(png_ptr, (png_byte**)&buf_ptr, NULL, 1);
            if (BRST_Error_Code(image->error) != BRST_OK)
                break;

            if (BRST_Stream_Write(image->stream, buf_ptr, len) != BRST_OK)
                break;
        }

        BRST_FreeMem(image->mmgr, buf_ptr);
    }

    return BRST_Error_Code(image->error);
}

static BRST_STATUS
ReadTransparentPaletteData(BRST_Dict image,
    png_structp png_ptr,
    png_infop info_ptr,
    png_bytep smask_data,
    png_bytep trans,
    int num_trans)
{
    BRST_STATUS ret = BRST_OK;
    BRST_UINT i, j;
    png_bytep* row_ptr;
    png_uint_32 height = png_get_image_height(png_ptr, info_ptr);
    png_uint_32 width  = png_get_image_width(png_ptr, info_ptr);

    row_ptr = BRST_GetMem(image->mmgr, height * sizeof(png_bytep));
    if (!row_ptr) {
        return BRST_FAILED_TO_ALLOC_MEM;
    } else {
        BRST_UINT len = (BRST_UINT)png_get_rowbytes(png_ptr, info_ptr);

        for (i = 0; i < (BRST_UINT)height; i++) {
            row_ptr[i] = BRST_GetMem(image->mmgr, len);
            if (!row_ptr[i]) {
                for (; i > 0; i--) {
                    BRST_FreeMem(image->mmgr, row_ptr[i]);
                }
                BRST_FreeMem(image->mmgr, row_ptr);
                return BRST_FAILED_TO_ALLOC_MEM;
            }
        }
    }

    png_read_image(png_ptr, row_ptr);
    if (BRST_Error_Code(image->error) != BRST_OK) {
        ret = BRST_INVALID_PNG_IMAGE;
        goto Error;
    }

    for (j = 0; j < height; j++) {
        for (i = 0; i < width; i++) {
            smask_data[width * j + i] = (row_ptr[j][i] < num_trans) ? trans[row_ptr[j][i]] : 0xFF;
        }

        if (BRST_Stream_Write(image->stream, row_ptr[j], width) != BRST_OK) {
            ret = BRST_FILE_IO_ERROR;
            goto Error;
        }
    }

Error:
    for (i = 0; i < (BRST_UINT)height; i++) {
        BRST_FreeMem(image->mmgr, row_ptr[i]);
    }

    BRST_FreeMem(image->mmgr, row_ptr);
    return ret;
}

static BRST_STATUS
ReadTransparentPngData(BRST_Dict image,
    png_structp png_ptr,
    png_infop info_ptr,
    png_bytep smask_data)
{
    BRST_STATUS ret = BRST_OK;
    BRST_INT row_len;
    BRST_UINT i, j;
    png_bytep *row_ptr, row;
    png_byte color_type;
    png_uint_32 height = png_get_image_height(png_ptr, info_ptr);
    png_uint_32 width  = png_get_image_width(png_ptr, info_ptr);

    color_type = png_get_color_type(png_ptr, info_ptr);

    if (!(color_type & PNG_COLOR_MASK_ALPHA)) {
        return BRST_INVALID_PNG_IMAGE;
    }

    row_ptr = BRST_GetMem(image->mmgr, height * sizeof(png_bytep));
    if (!row_ptr) {
        return BRST_FAILED_TO_ALLOC_MEM;
    } else {
        BRST_UINT len = (BRST_UINT)png_get_rowbytes(png_ptr, info_ptr);

        for (i = 0; i < (BRST_UINT)height; i++) {
            row_ptr[i] = BRST_GetMem(image->mmgr, len);
            if (!row_ptr[i]) {
                for (; i > 0; i--) {
                    BRST_FreeMem(image->mmgr, row_ptr[i]);
                }
                BRST_FreeMem(image->mmgr, row_ptr);
                return BRST_FAILED_TO_ALLOC_MEM;
            }
        }
    }

    png_read_image(png_ptr, row_ptr);
    if (BRST_Error_Code(image->error) != BRST_OK) {
        ret = BRST_INVALID_PNG_IMAGE;
        goto Error;
    }

    switch (color_type) {
    case PNG_COLOR_TYPE_RGB_ALPHA:
        row_len = 3 * width * sizeof(png_byte);
        for (j = 0; j < height; j++) {
            row = row_ptr[j];
            for (i = 0; i < width; i++) {
                memmove(row + (3 * i), row + (4 * i), 3);
                smask_data[width * j + i] = row[4 * i + 3];
            }

            if (BRST_Stream_Write(image->stream, row, row_len) != BRST_OK) {
                ret = BRST_FILE_IO_ERROR;
                goto Error;
            }
        }
        break;
    case PNG_COLOR_TYPE_GRAY_ALPHA:
        row_len = width * sizeof(png_byte);
        for (j = 0; j < height; j++) {
            row = row_ptr[j];
            for (i = 0; i < width; i++) {
                row[i]                    = row[2 * i];
                smask_data[width * j + i] = row[2 * i + 1];
            }

            if (BRST_Stream_Write(image->stream, row, row_len) != BRST_OK) {
                ret = BRST_FILE_IO_ERROR;
                goto Error;
            }
        }
        break;
    default:
        ret = BRST_INVALID_PNG_IMAGE;
        goto Error;
    }

Error:
    for (i = 0; i < (BRST_UINT)height; i++) {
        BRST_FreeMem(image->mmgr, row_ptr[i]);
    }

    BRST_FreeMem(image->mmgr, row_ptr);
    return ret;
}

static BRST_STATUS
CreatePallet(BRST_Dict image,
    png_structp png_ptr,
    png_infop info_ptr)
{
    BRST_INT num_pl   = 0;
    png_color* src_pl = NULL;
    BRST_BYTE* ppallet;
    BRST_BYTE* p;
    BRST_INT i;
    BRST_Array array;

    /* png_get_PLTE does not call PngErrorFunc even if it failed.
     * so we call BRST_Set_Error to set error-code.
     */
    if (png_get_PLTE(png_ptr, info_ptr, (png_color**)&src_pl, &num_pl) != PNG_INFO_PLTE)
        return BRST_Error_Set(image->error, BRST_LIBPNG_ERROR,
            BRST_CANNOT_GET_PALETTE);

    /* make a pallet array for indexed image. */
    ppallet = BRST_GetMem(image->mmgr, num_pl * 3);
    if (!ppallet)
        return BRST_Error_Code(image->error);

    p = ppallet;
    for (i = 0; i < num_pl; i++, src_pl++) {
        *p++ = src_pl->red;
        *p++ = src_pl->green;
        *p++ = src_pl->blue;
    }

    array = BRST_Array_New(image->mmgr);
    if (array) {
        BRST_Binary b;

        BRST_Dict_Add(image, "ColorSpace", array);

        BRST_Array_AddName(array, "Indexed");
        BRST_Array_AddName(array, "DeviceRGB");
        BRST_Array_AddNumber(array, num_pl - 1);

        b = BRST_Binary_New(image->mmgr, ppallet, num_pl * 3);
        if (b)
            BRST_Array_Add(array, b);
    }

    BRST_FreeMem(image->mmgr, ppallet);

    return BRST_Error_Code(image->error);
}

#define BRST_PNG_BYTES_TO_CHECK 8

BRST_Image
BRST_Image_Png_Load(BRST_MMgr mmgr,
    BRST_Stream png_data,
    BRST_Xref xref,
    BRST_BOOL delayed_loading)
{
    BRST_STATUS ret;
    BRST_Dict image;
    png_byte header[BRST_PNG_BYTES_TO_CHECK];
    BRST_UINT len = BRST_PNG_BYTES_TO_CHECK;

    BRST_PTRACE(" BRST_Image_Png_Load\n");

    BRST_MemSet(header, 0x00, BRST_PNG_BYTES_TO_CHECK);
    ret = BRST_Stream_Read(png_data, header, &len);
    if (ret != BRST_OK || png_sig_cmp(header, (png_size_t)0, BRST_PNG_BYTES_TO_CHECK)) {
        BRST_Error_Set(BRST_MMgr_Error(mmgr), BRST_INVALID_PNG_IMAGE, 0);
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

    if (LoadPngData(image, xref, png_data, delayed_loading) != BRST_OK)
        return NULL;

    return image;
}

static BRST_STATUS
LoadPngData(BRST_Dict image,
    BRST_Xref xref,
    BRST_Stream png_data,
    BRST_BOOL delayed_loading)

{
    BRST_STATUS ret = BRST_OK;
    png_uint_32 width, height;
    int bit_depth, color_type;
    png_structp png_ptr = NULL;
    png_infop info_ptr  = NULL;

    BRST_PTRACE(" BRST_Image_LoadPngImage\n");

    /* create read_struct. */
    png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING,
        image->error, PngErrorFunc, PngWarnFunc);

    if (png_ptr == NULL) {
        BRST_Error_Set(image->error, BRST_FAILED_TO_ALLOC_MEM, 0);
        return BRST_FAILED_TO_ALLOC_MEM;
    }

    /* create info-struct */
    info_ptr = png_create_info_struct(png_ptr);

    if (info_ptr == NULL) {
        BRST_Error_Set(image->error, BRST_FAILED_TO_ALLOC_MEM, 0);
        goto Exit;
    }

    png_set_sig_bytes(png_ptr, BRST_PNG_BYTES_TO_CHECK);
    png_set_read_fn(png_ptr, (void*)png_data, (png_rw_ptr)&PngReadFunc);

    /* reading info structure. */
    png_read_info(png_ptr, info_ptr);
    if (BRST_Error_Code(image->error) != BRST_OK) {
        goto Exit;
    }

    png_get_IHDR(png_ptr, info_ptr, &width, &height, &bit_depth, &color_type, NULL, NULL, NULL);

    /* 16bit images are not supported. */
    if (bit_depth == 16) {
        png_set_strip_16(png_ptr);
        bit_depth = 8;
    }

    png_read_update_info(png_ptr, info_ptr);
    if (BRST_Error_Code(image->error) != BRST_OK) {
        goto Exit;
    }

    /* check palette-based images for transparent areas and load them immediately if found */
    if (xref && PNG_COLOR_TYPE_PALETTE & color_type) {
        png_bytep trans;
        int num_trans;
        BRST_Dict smask;
        png_bytep smask_data;

        if (!png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS) || !png_get_tRNS(png_ptr, info_ptr, &trans, &num_trans, NULL)) {
            goto no_transparent_color_in_palette;
        }

        smask = BRST_Dict_New_Stream_Init(image->mmgr, xref);
        if (!smask) {
            ret = BRST_FAILED_TO_ALLOC_MEM;
            goto Exit;
        }

        smask->header.obj_class |= BRST_OSUBCLASS_XOBJECT;
        ret = BRST_Dict_AddName(smask, "Type", "XObject");
        ret += BRST_Dict_AddName(smask, "Subtype", "Image");
        ret += BRST_Dict_AddNumber(smask, "Width", (BRST_UINT)width);
        ret += BRST_Dict_AddNumber(smask, "Height", (BRST_UINT)height);
        ret += BRST_Dict_AddName(smask, "ColorSpace", "DeviceGray");
        ret += BRST_Dict_AddNumber(smask, "BitsPerComponent", (BRST_UINT)bit_depth);

        if (ret != BRST_OK) {
            BRST_Dict_Free(smask);
            ret = BRST_INVALID_PNG_IMAGE;
            goto Exit;
        }

        smask_data = BRST_GetMem(image->mmgr, width * height);
        if (!smask_data) {
            BRST_Dict_Free(smask);
            ret = BRST_FAILED_TO_ALLOC_MEM;
            goto Exit;
        }

        if (ReadTransparentPaletteData(image, png_ptr, info_ptr, smask_data, trans, num_trans) != BRST_OK) {
            BRST_FreeMem(image->mmgr, smask_data);
            BRST_Dict_Free(smask);
            ret = BRST_INVALID_PNG_IMAGE;
            goto Exit;
        }

        if (BRST_Stream_Write(smask->stream, smask_data, width * height) != BRST_OK) {
            BRST_FreeMem(image->mmgr, smask_data);
            BRST_Dict_Free(smask);
            ret = BRST_FILE_IO_ERROR;
            goto Exit;
        }
        BRST_FreeMem(image->mmgr, smask_data);

        ret += CreatePallet(image, png_ptr, info_ptr);
        ret += BRST_Dict_AddNumber(image, "Width", (BRST_UINT)width);
        ret += BRST_Dict_AddNumber(image, "Height", (BRST_UINT)height);
        ret += BRST_Dict_AddNumber(image, "BitsPerComponent", (BRST_UINT)bit_depth);
        ret += BRST_Dict_Add(image, "SMask", smask);

        png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
        return BRST_OK;
    }

no_transparent_color_in_palette:

    /* read images with alpha channel right away
       we have to do this because image transparent mask must be added to the Xref */
    if (xref && PNG_COLOR_MASK_ALPHA & color_type) {
        BRST_Dict smask;
        png_bytep smask_data;

        smask = BRST_Dict_New_Stream_Init(image->mmgr, xref);
        if (!smask) {
            ret = BRST_FAILED_TO_ALLOC_MEM;
            goto Exit;
        }

        smask->filter = image->filter;
        smask->header.obj_class |= BRST_OSUBCLASS_XOBJECT;

        ret = BRST_Dict_AddName(smask, "Type", "XObject");
        ret += BRST_Dict_AddName(smask, "Subtype", "Image");
        ret += BRST_Dict_AddNumber(smask, "Width", (BRST_UINT)width);
        ret += BRST_Dict_AddNumber(smask, "Height", (BRST_UINT)height);
        ret += BRST_Dict_AddName(smask, "ColorSpace", "DeviceGray");
        ret += BRST_Dict_AddNumber(smask, "BitsPerComponent", (BRST_UINT)bit_depth);

        if (ret != BRST_OK) {
            BRST_Dict_Free(smask);
            ret = BRST_INVALID_PNG_IMAGE;
            goto Exit;
        }

        smask_data = BRST_GetMem(image->mmgr, width * height);
        if (!smask_data) {
            BRST_Dict_Free(smask);
            ret = BRST_FAILED_TO_ALLOC_MEM;
            goto Exit;
        }

        if (ReadTransparentPngData(image, png_ptr, info_ptr, smask_data) != BRST_OK) {
            BRST_FreeMem(image->mmgr, smask_data);
            BRST_Dict_Free(smask);
            ret = BRST_INVALID_PNG_IMAGE;
            goto Exit;
        }

        if (BRST_Stream_Write(smask->stream, smask_data, width * height) != BRST_OK) {
            BRST_FreeMem(image->mmgr, smask_data);
            BRST_Dict_Free(smask);
            ret = BRST_FILE_IO_ERROR;
            goto Exit;
        }
        BRST_FreeMem(image->mmgr, smask_data);

        if (color_type == PNG_COLOR_TYPE_GRAY_ALPHA) {
            ret += BRST_Dict_AddName(image, "ColorSpace", "DeviceGray");
        } else {
            ret += BRST_Dict_AddName(image, "ColorSpace", "DeviceRGB");
        }
        ret += BRST_Dict_AddNumber(image, "Width", (BRST_UINT)width);
        ret += BRST_Dict_AddNumber(image, "Height", (BRST_UINT)height);
        ret += BRST_Dict_AddNumber(image, "BitsPerComponent", (BRST_UINT)bit_depth);
        ret += BRST_Dict_Add(image, "SMask", smask);

        png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
        return BRST_OK;
    }

    /* if the image has color palette, copy the pallet of the image to
     * create color map.
     */
    if (color_type == PNG_COLOR_TYPE_PALETTE)
        ret = CreatePallet(image, png_ptr, info_ptr);
    else if (color_type == PNG_COLOR_TYPE_GRAY)
        ret = BRST_Dict_AddName(image, "ColorSpace", "DeviceGray");
    else
        ret = BRST_Dict_AddName(image, "ColorSpace", "DeviceRGB");

    if (ret != BRST_OK)
        goto Exit;

    /* read image-data
     * if the image is interlaced, read whole image at once.
     * if delayed_loading is BRST_TRUE, the data does not load this phase.
     */
    if (delayed_loading) {
        image->before_write_fn = PngBeforeWrite;
        image->after_write_fn  = PngAfterWrite;
    } else {
        if (png_get_interlace_type(png_ptr, info_ptr) != PNG_INTERLACE_NONE)
            ret = ReadPngData_Interlaced(image, png_ptr, info_ptr);
        else
            ret = ReadPngData(image, png_ptr, info_ptr);

        if (ret != BRST_OK)
            goto Exit;
    }

    /* setting the info of the image. */
    if (BRST_Dict_AddNumber(image, "Width", (BRST_UINT)width)
        != BRST_OK)
        goto Exit;

    if (BRST_Dict_AddNumber(image, "Height", (BRST_UINT)height)
        != BRST_OK)
        goto Exit;

    if (BRST_Dict_AddNumber(image, "BitsPerComponent",
            (BRST_UINT)bit_depth)
        != BRST_OK)
        goto Exit;

    /* clean up */
    png_destroy_read_struct(&png_ptr, &info_ptr, NULL);

    return BRST_OK;

Exit:
    png_destroy_read_struct(&png_ptr, &info_ptr, NULL);

    if (ret != BRST_OK) {
        return ret;
    }
    return BRST_Error_Code(image->error);
}

static BRST_STATUS
PngBeforeWrite(BRST_Dict obj)
{
    BRST_STATUS ret;
    png_byte header[BRST_PNG_BYTES_TO_CHECK];
    BRST_UINT len = BRST_PNG_BYTES_TO_CHECK;
    BRST_Stream png_data;
    BRST_String s;

    BRST_PTRACE(" PngBeforeWrite\n");

    BRST_MemStream_FreeData(obj->stream);

    s = BRST_Dict_Item(obj, "_FILE_NAME", BRST_OCLASS_STRING);
    if (!s)
        return BRST_Error_Set(obj->error, BRST_MISSING_FILE_NAME_ENTRY, 0);

    png_data = BRST_FileReader_New(obj->mmgr, BRST_String_Value(s));
    if (!BRST_Stream_Validate(png_data))
        return BRST_Error_Code(obj->error);

    BRST_MemSet(header, 0x00, BRST_PNG_BYTES_TO_CHECK);
    ret = BRST_Stream_Read(png_data, header, &len);
    if (ret != BRST_OK || png_sig_cmp(header, (png_size_t)0, BRST_PNG_BYTES_TO_CHECK)) {
        BRST_Stream_Free(png_data);
        return BRST_Error_Set(obj->error, BRST_INVALID_PNG_IMAGE, 0);
    }

    if ((ret = LoadPngData(obj, NULL, png_data, BRST_FALSE)) != BRST_OK) {
        BRST_Stream_Free(png_data);
        return ret;
    }

    BRST_Stream_Free(png_data);

    return BRST_OK;
}

static BRST_STATUS
PngAfterWrite(BRST_Dict obj)
{
    BRST_PTRACE(" PngAfterWrite\n");

    BRST_MemStream_FreeData(obj->stream);

    return BRST_OK;
}

#endif /* LIBBRST_HAVE_LIBPNG */
