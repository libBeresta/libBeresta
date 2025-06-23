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
#include "private/brst_catalog.h"
#include "private/brst_pdfa.h"
#include "brst_pdfa.h"
#include "brst_doc.h"
#include "private/brst_doc.h"
#include "brst_doc_info.h"
#include "private/brst_info.h"

BRST_EXPORT(BRST_STATUS)
BRST_Doc_SetInfoAttr(BRST_Doc pdf,
    BRST_InfoType type,
    const char* value)
{
    BRST_STATUS ret;
    BRST_Dict info = GetInfo(pdf);

    BRST_PTRACE((" BRST_Doc_SetInfoAttr\n"));

    if (!info)
        return BRST_Error_Check(pdf->error);

    ret = BRST_Info_SetInfoAttr(info, type, value, pdf->cur_encoder);
    if (ret != BRST_OK)
        return BRST_Error_Check(pdf->error);

    return ret;
}

BRST_EXPORT(const char*)
BRST_Doc_InfoAttr(BRST_Doc pdf,
    BRST_InfoType type)
{
    const char* ret = NULL;
    BRST_Dict info  = GetInfo(pdf);

    BRST_PTRACE((" BRST_Doc_InfoAttr\n"));

    if (info)
        ret = BRST_Info_InfoAttr(info, type);
    else
        BRST_Error_Check(pdf->error);

    return ret;
}

BRST_EXPORT(BRST_STATUS)
BRST_Doc_SetInfoDateAttr(BRST_Doc pdf,
    BRST_InfoType type,
    BRST_Date value)
{
    BRST_STATUS ret;
    BRST_Dict info = GetInfo(pdf);

    BRST_PTRACE((" BRST_Doc_SetInfoDateAttr\n"));

    if (!info)
        return BRST_Error_Check(pdf->error);

    ret = BRST_Info_SetInfoDateAttr(info, type, value);
    if (ret != BRST_OK)
        return BRST_Error_Check(pdf->error);

    return ret;
}
