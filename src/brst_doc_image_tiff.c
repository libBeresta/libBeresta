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
#include "brst_matrix.h"
#include "brst_array.h"
#include "brst_image.h"
#include "private/brst_image.h"
#include "brst_geometry_defines.h"
#include "private/brst_encrypt_dict.h"
#include "brst_outline.h"
#include "brst_pdfa.h"
#include "brst_page.h"
#include "brst_doc.h"
#include "private/brst_catalog.h"
#include "private/brst_doc.h"
#include "brst_base.h"
#include "brst_doc_image_tiff.h"
#include "private/brst_image_tiff.h"

/*
 * Load image from buffer
 * line_width - width of the line in bytes
 * top_is_first - image orientation:
 *      TRUE if image is oriented TOP-BOTTOM;
 *      FALSE if image is oriented BOTTOM-TOP
 */
BRST_EXPORT(BRST_Image)
BRST_Doc_Image_Raw1Bit_LoadFromMem(BRST_Doc pdf,
    const BRST_BYTE* buf,
    BRST_UINT width,
    BRST_UINT height,
    BRST_UINT line_width,
    BRST_BOOL black_is1,
    BRST_BOOL top_is_first)
{
    BRST_Image image;

    BRST_PTRACE(" BRST_Image_Load1BitImageFromMem\n");

    if (!BRST_Doc_Initialized(pdf))
        return NULL;

    image = BRST_Image_Raw1Bit_LoadFromMem(pdf->mmgr, buf, pdf->xref, width,
        height, line_width, top_is_first);

    if (!image)
        BRST_Error_Check(pdf->error);

    if (pdf->compression_mode & BRST_COMP_IMAGE) {
        image->filter       = BRST_STREAM_FILTER_CCITT_DECODE;
        image->filterParams = BRST_Dict_New(pdf->mmgr);
        if (image->filterParams == NULL) {
            return NULL;
        }

        /* pure 2D encoding, default is 0 */
        BRST_Dict_AddNumber(image->filterParams, "K", -1);
        /* default is 1728 */
        BRST_Dict_AddNumber(image->filterParams, "Columns", width);
        /* default is 0 */
        BRST_Dict_AddNumber(image->filterParams, "Rows", height);
        BRST_Dict_AddBoolean(image->filterParams, "BlackIs1", black_is1);
    }

    return image;
}

BRST_EXPORT(BRST_Image)
BRST_Doc_Image_Raw_LoadFromFile(BRST_Doc pdf,
    const char* filename,
    BRST_UINT width,
    BRST_UINT height,
    BRST_ColorSpace color_space)
{
    BRST_Stream imagedata;
    BRST_Image image;

    BRST_PTRACE(" BRST_Doc_Image_Raw_LoadFromFile\n");

    if (!BRST_Doc_Initialized(pdf))
        return NULL;

    /* create file stream */
    imagedata = BRST_FileReader_New(pdf->mmgr, filename);

    if (BRST_Stream_Validate(imagedata))
        image = BRST_Image_Raw_Load(pdf->mmgr, imagedata, pdf->xref, width,
            height, color_space);
    else
        image = NULL;

    /* destroy file stream */
    BRST_Stream_Free(imagedata);

    if (!image)
        BRST_Error_Check(pdf->error);

    if (image && pdf->compression_mode & BRST_COMP_IMAGE)
        image->filter = BRST_STREAM_FILTER_FLATE_DECODE;

    return image;
}

BRST_EXPORT(BRST_Image)
BRST_Doc_Image_Raw_LoadFromMem(BRST_Doc pdf,
    const BRST_BYTE* buf,
    BRST_UINT width,
    BRST_UINT height,
    BRST_ColorSpace color_space,
    BRST_UINT bits_per_component)
{
    BRST_Image image;

    BRST_PTRACE(" BRST_Doc_Image_Raw_LoadFromMem\n");

    if (!BRST_Doc_Initialized(pdf))
        return NULL;

    /* Use directly BRST_Image_LoadRaw1BitImageFromMem to save B/W images */
    if (color_space == BRST_CS_DEVICE_GRAY && bits_per_component == 1) {
        return BRST_Doc_Image_Raw1Bit_LoadFromMem(pdf, buf, width, height, (width + 7) / 8, BRST_TRUE, BRST_TRUE);
    }

    image = BRST_Image_Raw_LoadFromMem(pdf->mmgr, buf, pdf->xref, width, height, color_space, bits_per_component);

    if (!image)
        BRST_Error_Check(pdf->error);

    if (image && pdf->compression_mode & BRST_COMP_IMAGE) {
        image->filter = BRST_STREAM_FILTER_FLATE_DECODE;
    }

    return image;
}
