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
#include "brst_transmatrix.h"
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
#include "private/brst_image_jpeg.h"

BRST_EXPORT(BRST_Image)
BRST_Doc_Image_Jpeg_LoadFromFile(BRST_Doc pdf,
    const char* filename)
{
    BRST_Stream imagedata;
    BRST_Image image;

    BRST_PTRACE(" BRST_Doc_Image_Jpeg_LoadFromFile\n");

    if (!BRST_Doc_Initialized(pdf))
        return NULL;

    /* create file stream */
    imagedata = BRST_FileReader_New(pdf->mmgr, filename);

    if (BRST_Stream_Validate(imagedata))
        image = BRST_Image_Jpeg_Load(pdf->mmgr, imagedata, pdf->xref);
    else
        image = NULL;

    /* destroy file stream */
    BRST_Stream_Free(imagedata);

    if (!image)
        BRST_Error_Check(pdf->error);

    return image;
}

BRST_EXPORT(BRST_Image)
BRST_Doc_Image_Jpeg_LoadFromMem(BRST_Doc pdf,
    const BRST_BYTE* buffer,
    BRST_UINT size)
{
    BRST_Image image;

    BRST_PTRACE(" BRST_Doc_Image_Jpeg_LoadFromMem\n");

    if (!BRST_Doc_Initialized(pdf)) {
        return NULL;
    }

    image = BRST_Image_Jpeg_LoadFromMem(pdf->mmgr, buffer, size, pdf->xref);

    if (!image) {
        BRST_Error_Check(pdf->error);
    }

    return image;
}
