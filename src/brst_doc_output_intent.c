#include "brst_external.h"
#include "brst_types.h"
#include "brst_mmgr.h"
#include "brst_encrypt.h"
#include "brst_stream.h"
#include "brst_matrix.h"
#include "brst_array.h"
#include "private/brst_array.h"
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
#include "brst_pdfa.h"
#include "brst_doc.h"
#include "private/brst_doc.h"
#include "brst_doc_output_intent.h"
#include "brst_base.h"

BRST_EXPORT(BRST_STATUS)
BRST_Doc_OutputIntent_Add(BRST_Doc pdf,
    BRST_OutputIntent intent)
{
    BRST_Array intents;
    if (!BRST_Doc_Initialized(pdf))
        return BRST_INVALID_DOCUMENT;

    intents = BRST_Dict_Item(pdf->catalog, "OutputIntents", BRST_OCLASS_ARRAY);
    if (intents == NULL) {
        intents = BRST_Array_New(pdf->mmgr);
        if (intents) {
            BRST_STATUS ret = BRST_Dict_Add(pdf->catalog, "OutputIntents", intents);
            if (ret != BRST_OK) {
                BRST_Error_Check(pdf->error);
                return BRST_Error_DetailCode(pdf->error);
            }
        }
    }
    BRST_Array_Add(intents, intent);
    return BRST_Error_DetailCode(pdf->error);
}

/*
 * Create an intent entry
 */
// TODO Выяснить, что за intent
BRST_EXPORT(BRST_OutputIntent)
BRST_Doc_OutputIntent_New(BRST_Doc pdf,
    const char* identifier,
    const char* condition,
    const char* registry,
    const char* info,
    BRST_Array outputprofile)
{
    BRST_OutputIntent intent;
    BRST_STATUS ret = BRST_OK;

    BRST_PTRACE(" BRST_OutputIntent_New\n");

    if (!BRST_Doc_Initialized(pdf))
        return NULL;

    intent = BRST_Dict_New(pdf->mmgr);
    if (!intent)
        return NULL;

    if (BRST_Xref_Add(pdf->xref, intent) != BRST_OK) {
        BRST_Dict_Free(intent);
        return NULL;
    }

    ret += BRST_Dict_AddName(intent, "Type", "OutputIntent");
    ret += BRST_Dict_AddName(intent, "S", "GTS_PDFX");
    ret += BRST_Dict_Add(intent, "OutputConditionIdentifier", BRST_String_New(pdf->mmgr, identifier, NULL));
    ret += BRST_Dict_Add(intent, "OutputCondition", BRST_String_New(pdf->mmgr, condition, NULL));
    ret += BRST_Dict_Add(intent, "RegistryName", BRST_String_New(pdf->mmgr, registry, NULL));

    if (info != NULL) {
        ret += BRST_Dict_Add(intent, "Info", BRST_String_New(pdf->mmgr, info, NULL));
    }

    /* add ICC base stream */
    if (outputprofile != NULL) {
        ret += BRST_Dict_Add(intent, "DestOutputProfile ", outputprofile);
    }

    if (ret != BRST_OK) {
        BRST_Dict_Free(intent);
        return NULL;
    }

    return intent;
}
