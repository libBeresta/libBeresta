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

// TODO А эта функция точно должна быть экспортирована?
/*
BRST_EXPORT(BRST_FontDef)
BRST_GetTTFontDefFromFile(
    BRST_Doc    pdf,
    const char* filename,
    BRST_BOOL   embedding
);
*/


BRST_EXPORT(BRST_FontDef)
BRST_GetTTFontDefFromFile(BRST_Doc pdf,
    const char* file_name,
    BRST_BOOL embedding)
{
    BRST_Stream font_data;
    BRST_FontDef def;

    BRST_PTRACE((" BRST_GetTTFontDefFromFile\n"));

    /* create file stream */
    font_data = BRST_FileReader_New(pdf->mmgr, file_name);

    if (BRST_Stream_Validate(font_data)) {
        def = BRST_TTFontDef_Load(pdf->mmgr, font_data, embedding);
    } else {
        BRST_Error_Check(pdf->error);
        return NULL;
    }

    return def;
}
