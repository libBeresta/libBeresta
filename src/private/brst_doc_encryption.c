#include "brst_types.h"
#include "brst_mmgr.h"
#include "brst_encrypt.h"
#include "brst_stream.h"
#include "brst_dict.h"
#include "private/brst_dict.h"
#include "brst_array.h"
#include "private/brst_array.h"
#include "brst_xref.h"
#include "private/brst_xref.h"
#include "brst_encoder.h"
#include "brst_page.h"
#include "brst_destination.h"
#include "brst_outline.h"
#include "private/brst_encrypt_dict.h"
#include "private/brst_catalog.h"
#include "brst_pdfa.h"
#include "brst_doc.h"
#include "private/brst_doc.h"
#include "private/brst_utils.h"
#include "brst_consts.h"
#include "brst_error.h"
#include "private/brst_null.h"
#include "private/brst_binary.h"

BRST_STATUS
BRST_Doc_SetEncryptOff(BRST_Doc pdf)
{
    BRST_PTRACE((" BRST_Doc_SetEncryptOff\n"));

    if (!pdf->encrypt_on)
        return BRST_OK;

    /* if encrypt-dict object is registered to cross-reference-table,
     * replace it to null-object.
     * additionally remove encrypt-dict object from trailer-object.
     */
    if (pdf->encrypt_dict) {
        BRST_UINT obj_id = pdf->encrypt_dict->header.obj_id;

        if (obj_id & BRST_OTYPE_INDIRECT) {
            BRST_XrefEntry entry;
            BRST_Null null_obj;

            BRST_Dict_RemoveElement(pdf->trailer, "Encrypt");

            entry = BRST_Xref_GetEntryByObjectId(pdf->xref,
                obj_id & 0x00FFFFFF);

            if (!entry) {
                return BRST_Error_Set(pdf->error,
                    BRST_DOC_ENCRYPTDICT_NOT_FOUND, 0);
            }

            null_obj = BRST_Null_New(pdf->mmgr);
            if (!null_obj)
                return BRST_Error_Code(pdf->error);

            entry->obj = null_obj;
            BRST_Obj_SetID(null_obj, obj_id | BRST_OTYPE_INDIRECT);

            pdf->encrypt_dict->header.obj_id = BRST_OTYPE_NONE;
        }
    }

    pdf->encrypt_on = BRST_FALSE;
    return BRST_OK;
}

BRST_STATUS
BRST_Doc_PrepareEncryption(BRST_Doc pdf)
{
    BRST_Encrypt e = BRST_EncryptDict_Attr(pdf->encrypt_dict);
    BRST_Dict info = GetInfo(pdf);
    BRST_Array id;

    if (!e)
        return BRST_DOC_ENCRYPTDICT_NOT_FOUND;

    if (!info)
        return BRST_Error_Code(pdf->error);

    if (BRST_EncryptDict_Prepare(pdf->encrypt_dict, info, pdf->xref) != BRST_OK)
        return BRST_Error_Code(pdf->error);

    /* reset 'ID' to trailer-dictionary */
    id = BRST_Dict_Item(pdf->trailer, "ID", BRST_OCLASS_ARRAY);
    if (!id) {
        id = BRST_Array_New(pdf->mmgr);

        if (!id || BRST_Dict_Add(pdf->trailer, "ID", id) != BRST_OK)
            return BRST_Error_Code(pdf->error);
    } else
        BRST_Array_Clear(id);

    if (BRST_Array_Add(id, BRST_Binary_New(pdf->mmgr, e->encrypt_id, BRST_ID_LEN)) != BRST_OK)
        return BRST_Error_Code(pdf->error);

    if (BRST_Array_Add(id, BRST_Binary_New(pdf->mmgr, e->encrypt_id, BRST_ID_LEN)) != BRST_OK)
        return BRST_Error_Code(pdf->error);

    return BRST_OK;
}

BRST_STATUS
BRST_Doc_SetEncryptOn(BRST_Doc pdf)
{
    BRST_PTRACE((" BRST_Doc_SetEncryptOn\n"));

    if (pdf->encrypt_on)
        return BRST_OK;

    if (!pdf->encrypt_dict)
        return BRST_Error_Set(pdf->error, BRST_DOC_ENCRYPTDICT_NOT_FOUND,
            0);

    if (pdf->encrypt_dict->header.obj_id == BRST_OTYPE_NONE)
        if (BRST_Xref_Add(pdf->xref, pdf->encrypt_dict) != BRST_OK)
            return BRST_Error_Code(pdf->error);

    if (BRST_Dict_Add(pdf->trailer, "Encrypt", pdf->encrypt_dict) != BRST_OK)
        return BRST_Error_Code(pdf->error);

    pdf->encrypt_on = BRST_TRUE;

    return BRST_OK;
}
