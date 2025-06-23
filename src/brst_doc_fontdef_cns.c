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
#include "private/brst_fontdef_cns.h"
#include "private/brst_catalog.h"
#include "private/brst_doc.h"
#include "private/brst_doc_fontdef.h"
#include "brst_base.h"

BRST_EXPORT(BRST_STATUS)
BRST_Doc_UseCNSFonts(BRST_Doc pdf)
{
    BRST_FontDef fontdef;
    BRST_STATUS ret;

    if (!BRST_Doc_Initialized(pdf))
        return BRST_INVALID_DOCUMENT;

    /* SimSun */
    fontdef = BRST_CIDFontDef_New(pdf->mmgr, "SimSun",
        SimSun_Init);

    if ((ret = BRST_Doc_RegisterFontDef(pdf, fontdef)) != BRST_OK)
        return ret;

    fontdef = BRST_CIDFontDef_New(pdf->mmgr, "SimSun,Bold",
        SimSun_Bold_Init);

    if ((ret = BRST_Doc_RegisterFontDef(pdf, fontdef)) != BRST_OK)
        return ret;

    fontdef = BRST_CIDFontDef_New(pdf->mmgr, "SimSun,Italic",
        SimSun_Italic_Init);

    if ((ret = BRST_Doc_RegisterFontDef(pdf, fontdef)) != BRST_OK)
        return ret;

    fontdef = BRST_CIDFontDef_New(pdf->mmgr, "SimSun,BoldItalic",
        SimSun_BoldItalic_Init);

    if ((ret = BRST_Doc_RegisterFontDef(pdf, fontdef)) != BRST_OK)
        return ret;

    /* SimHei */
    fontdef = BRST_CIDFontDef_New(pdf->mmgr, "SimHei",
        SimHei_Init);

    if ((ret = BRST_Doc_RegisterFontDef(pdf, fontdef)) != BRST_OK)
        return ret;

    fontdef = BRST_CIDFontDef_New(pdf->mmgr, "SimHei,Bold",
        SimHei_Bold_Init);

    if ((ret = BRST_Doc_RegisterFontDef(pdf, fontdef)) != BRST_OK)
        return ret;

    fontdef = BRST_CIDFontDef_New(pdf->mmgr, "SimHei,Italic",
        SimHei_Italic_Init);

    if ((ret = BRST_Doc_RegisterFontDef(pdf, fontdef)) != BRST_OK)
        return ret;

    fontdef = BRST_CIDFontDef_New(pdf->mmgr, "SimHei,BoldItalic",
        SimHei_BoldItalic_Init);

    if ((ret = BRST_Doc_RegisterFontDef(pdf, fontdef)) != BRST_OK)
        return ret;

    return BRST_OK;
}
