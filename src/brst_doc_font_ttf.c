#include "brst_external.h"
#include "brst_types.h"
#include "brst_mmgr.h"
#include "brst_encrypt.h"
#include "brst_stream.h"
#include "brst_dict.h"
#include "brst_xref.h"
#include "brst_encoder.h"
#include "brst_error.h"
#include "brst_consts.h"
#include "private/brst_utils.h"
#include "brst_page.h"
#include "private/brst_encrypt_dict.h"
#include "brst_outline.h"
#include "brst_pdfa.h"
#include "brst_doc.h"
#include "brst_fontdef.h"
#include "private/brst_defines.h"
#include "private/brst_fontdef_ttf.h"
#include "private/brst_catalog.h"
#include "private/brst_doc.h"
#include "brst_font.h"
#include "private/brst_doc_font.h"
#include "brst_base.h"

BRST_EXPORT(const char*)
BRST_Doc_TTFont_LoadFromFile(BRST_Doc pdf,
    const char* file_name,
    BRST_BOOL embedding)
{
    BRST_Stream font_data;
    const char* ret;

    BRST_PTRACE((" BRST_Doc_TTFont_LoadFromFile\n"));

    if (!BRST_Doc_Initialized(pdf))
        return NULL;

    /* create file stream */
    font_data = BRST_FileReader_New(pdf->mmgr, file_name);

    if (BRST_Stream_Validate(font_data)) {
        ret = LoadTTFontFromStream(pdf, font_data, embedding, file_name);
    } else
        ret = NULL;

    if (!ret)
        BRST_Error_Check(pdf->error);

    return ret;
}

/**
 * @brief Load the specified font from a font collection file.
 * @param[in] file_name Filename of the TrueType Font collection file.
 * @param[in] index Index of the font to load from the font collection.
 * @param[in] embedding Whether to embed the font in the document.
 * @ret The font definition.
 */
BRST_EXPORT(const char*)
BRST_Doc_TTFont_LoadFromFile2(BRST_Doc pdf,
    const char* file_name,
    BRST_UINT index,
    BRST_BOOL embedding)
{
    BRST_Stream font_data;
    const char* ret;

    BRST_PTRACE((" BRST_Doc_TTFont_LoadFromFile2\n"));

    if (!BRST_Doc_Initialized(pdf))
        return NULL;

    /* create file stream */
    font_data = BRST_FileReader_New(pdf->mmgr, file_name);

    if (BRST_Stream_Validate(font_data)) {
        ret = LoadTTFontFromStream2(pdf, font_data, index, embedding, file_name);
    } else
        ret = NULL;

    if (!ret)
        BRST_Error_Check(pdf->error);

    return ret;
}

BRST_EXPORT(const char*)
BRST_LoadTTFontFromMemory(BRST_Doc pdf,
    const BRST_BYTE* buffer,
    BRST_UINT size,
    BRST_BOOL embedding)
{
    BRST_Stream font_data;
    const char* ret;

    BRST_PTRACE((" BRST_LoadTTFontFromMemory\n"));

    if (!BRST_Doc_Initialized(pdf))
        return NULL;

    /* create memory stream */
    font_data = BRST_MemStream_New(pdf->mmgr, size);
    if (!BRST_Stream_Validate(font_data)) {
        BRST_Error_Raise(pdf->error, BRST_INVALID_STREAM, 0);
        return NULL;
    }

    if (BRST_Stream_Write(font_data, buffer, size) != BRST_OK) {
        BRST_Stream_Free(font_data);
        return NULL;
    }

    ret = LoadTTFontFromStream(pdf, font_data, embedding, "");
    if (!ret) {
        BRST_Error_Check(pdf->error);
    }
    return ret;
}
