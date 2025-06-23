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
#include "private/brst_fontdef_cid.h"
#include "private/brst_fontdef_jp.h"
#include "private/brst_catalog.h"
#include "private/brst_doc.h"
#include "private/brst_doc_fontdef.h"
#include "brst_base.h"

BRST_EXPORT(BRST_STATUS)
BRST_Doc_UseJPFonts(BRST_Doc pdf)
{
    BRST_FontDef fontdef;
    BRST_STATUS ret;

    if (!BRST_Doc_Initialized(pdf))
        return BRST_INVALID_DOCUMENT;

    /* MS-Gothic */
    fontdef = BRST_CIDFontDef_New(pdf->mmgr, "MS-Gothic",
        MS_Gothic_Init);

    if ((ret = BRST_Doc_RegisterFontDef(pdf, fontdef)) != BRST_OK)
        return ret;

    fontdef = BRST_CIDFontDef_New(pdf->mmgr, "MS-Gothic,Bold",
        MS_Gothic_Bold_Init);

    if ((ret = BRST_Doc_RegisterFontDef(pdf, fontdef)) != BRST_OK)
        return ret;

    fontdef = BRST_CIDFontDef_New(pdf->mmgr, "MS-Gothic,Italic",
        MS_Gothic_Italic_Init);

    if ((ret = BRST_Doc_RegisterFontDef(pdf, fontdef)) != BRST_OK)
        return ret;

    fontdef = BRST_CIDFontDef_New(pdf->mmgr, "MS-Gothic,BoldItalic",
        MS_Gothic_BoldItalic_Init);

    if ((ret = BRST_Doc_RegisterFontDef(pdf, fontdef)) != BRST_OK)
        return ret;

    /* MS-PGothic */
    fontdef = BRST_CIDFontDef_New(pdf->mmgr, "MS-PGothic",
        MS_PGothic_Init);

    if ((ret = BRST_Doc_RegisterFontDef(pdf, fontdef)) != BRST_OK)
        return ret;

    fontdef = BRST_CIDFontDef_New(pdf->mmgr, "MS-PGothic,Bold",
        MS_PGothic_Bold_Init);

    if ((ret = BRST_Doc_RegisterFontDef(pdf, fontdef)) != BRST_OK)
        return ret;

    fontdef = BRST_CIDFontDef_New(pdf->mmgr, "MS-PGothic,Italic",
        MS_PGothic_Italic_Init);

    if ((ret = BRST_Doc_RegisterFontDef(pdf, fontdef)) != BRST_OK)
        return ret;

    fontdef = BRST_CIDFontDef_New(pdf->mmgr, "MS-PGothic,BoldItalic",
        MS_PGothic_BoldItalic_Init);

    if ((ret = BRST_Doc_RegisterFontDef(pdf, fontdef)) != BRST_OK)
        return ret;

    /* MS-Mincho */
    fontdef = BRST_CIDFontDef_New(pdf->mmgr, "MS-Mincho",
        MS_Mincho_Init);

    if ((ret = BRST_Doc_RegisterFontDef(pdf, fontdef)) != BRST_OK)
        return ret;

    fontdef = BRST_CIDFontDef_New(pdf->mmgr, "MS-Mincho,Bold",
        MS_Mincho_Bold_Init);

    if ((ret = BRST_Doc_RegisterFontDef(pdf, fontdef)) != BRST_OK)
        return ret;

    fontdef = BRST_CIDFontDef_New(pdf->mmgr, "MS-Mincho,Italic",
        MS_Mincho_Italic_Init);

    if ((ret = BRST_Doc_RegisterFontDef(pdf, fontdef)) != BRST_OK)
        return ret;

    fontdef = BRST_CIDFontDef_New(pdf->mmgr, "MS-Mincho,BoldItalic",
        MS_Mincho_BoldItalic_Init);

    if ((ret = BRST_Doc_RegisterFontDef(pdf, fontdef)) != BRST_OK)
        return ret;

    /* MS-PMincho */
    fontdef = BRST_CIDFontDef_New(pdf->mmgr, "MS-PMincho",
        MS_PMincho_Init);

    if ((ret = BRST_Doc_RegisterFontDef(pdf, fontdef)) != BRST_OK)
        return ret;

    fontdef = BRST_CIDFontDef_New(pdf->mmgr, "MS-PMincho,Bold",
        MS_PMincho_Bold_Init);

    if ((ret = BRST_Doc_RegisterFontDef(pdf, fontdef)) != BRST_OK)
        return ret;

    fontdef = BRST_CIDFontDef_New(pdf->mmgr, "MS-PMincho,Italic",
        MS_PMincho_Italic_Init);

    if ((ret = BRST_Doc_RegisterFontDef(pdf, fontdef)) != BRST_OK)
        return ret;

    fontdef = BRST_CIDFontDef_New(pdf->mmgr, "MS-PMincho,BoldItalic",
        MS_PMincho_BoldItalic_Init);

    if ((ret = BRST_Doc_RegisterFontDef(pdf, fontdef)) != BRST_OK)
        return ret;

    return BRST_OK;
}
