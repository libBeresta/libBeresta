#include "brst_external.h"
#include "brst_types.h"
#include "brst_mmgr.h"
#include "brst_encrypt.h"
#include "brst_stream.h"
#include "brst_dict.h"
#include "private/brst_dict.h"
#include "brst_xref.h"
#include "brst_encoder.h"
#include "brst_error.h"
#include "brst_consts.h"
#include "private/brst_utils.h"
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
#include "private/brst_image_png.h"
#include "private/brst_object.h"

#ifdef LIBBRST_HAVE_LIBPNG
#include <png.h>
#include <string.h>

BRST_EXPORT(BRST_Image)
BRST_Doc_Png_LoadFromMem(BRST_Doc pdf,
    const BRST_BYTE* buffer,
    BRST_UINT size)
{
    BRST_Stream imagedata;
    BRST_Image image;

    BRST_PTRACE((" BRST_Doc_Png_LoadFromMem\n"));

    if (!BRST_Doc_Initialized(pdf)) {
        return NULL;
    }

    /* create file stream */
    imagedata = BRST_MemStream_New(pdf->mmgr, size);

    if (!BRST_Stream_Validate(imagedata)) {
        BRST_Error_Raise(pdf->error, BRST_INVALID_STREAM, 0);
        return NULL;
    }

    if (BRST_Stream_Write(imagedata, buffer, size) != BRST_OK) {
        BRST_Stream_Free(imagedata);
        return NULL;
    }

    image = BRST_Image_Png_LoadFromStream(pdf->mmgr, pdf->xref, pdf->compression_mode, imagedata, BRST_FALSE);

    /* destroy file stream */
    BRST_Stream_Free(imagedata);

    if (!image) {
        BRST_Error_Check(pdf->error);
    }

    return image;
}

BRST_EXPORT(BRST_Image)
BRST_Doc_Png_LoadFromFile(BRST_Doc pdf,
    const char* filename)
{
    BRST_Stream imagedata;
    BRST_Image image;

    BRST_PTRACE((" BRST_Doc_Png_LoadFromFile\n"));

    if (!BRST_Doc_Initialized(pdf))
        return NULL;

    /* create file stream */
    imagedata = BRST_FileReader_New(pdf->mmgr, filename);

    if (BRST_Stream_Validate(imagedata))
        image = BRST_Image_Png_LoadFromStream(pdf->mmgr, pdf->xref, pdf->compression_mode, imagedata, BRST_FALSE);
    else
        image = NULL;

    /* destroy file stream */
    if (imagedata)
        BRST_Stream_Free(imagedata);

    if (!image)
        BRST_Error_Check(pdf->error);

    return image;
}

/* delaied loading version of BRST_LoadPngImageFromFile */
BRST_EXPORT(BRST_Image)
BRST_Doc_Png_LoadFromFile2(BRST_Doc pdf,
    const char* filename)
{
    BRST_Stream imagedata;
    BRST_Image image;
    BRST_String fname;

    BRST_PTRACE((" BRST_Doc_Png_LoadFromFile2\n"));

    if (!BRST_Doc_Initialized(pdf))
        return NULL;

    /* check whether file name is valid or not. */
    imagedata = BRST_FileReader_New(pdf->mmgr, filename);

    if (BRST_Stream_Validate(imagedata))
        image = BRST_Image_Png_LoadFromStream(pdf->mmgr, pdf->xref, pdf->compression_mode, imagedata, BRST_TRUE);
    else
        image = NULL;

    /* destroy file stream */
    if (imagedata)
        BRST_Stream_Free(imagedata);

    if (!image) {
        BRST_Error_Check(pdf->error);
        return NULL;
    }

    /* add file-name to image dictionary as a hidden entry.
     * it is used when the image data is needed.
     */
    fname = BRST_String_New(pdf->mmgr, filename, NULL);
    if (!fname) {
        BRST_Error_Check(pdf->error);
        return NULL;
    }

    // fname->header.obj_id |= BRST_OTYPE_HIDDEN;

    BRST_Obj_SetID(fname, BRST_Obj_ID(fname) | BRST_OTYPE_HIDDEN);

    if ((BRST_Dict_Add(image, "_FILE_NAME", fname)) != BRST_OK) {
        BRST_Error_Check(pdf->error);
        return NULL;
    }

    return image;
}

#endif /* LIBBRST_HAVE_LIBPNG */
