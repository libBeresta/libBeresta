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
#include "brst_pdfa.h"
#include "private/brst_doc.h"
#include "brst_doc.h"
#include "brst_base.h"
#include "private/brst_doc_encryption.h"

BRST_EXPORT(BRST_STATUS)
BRST_Doc_SetPassword(BRST_Doc pdf,
    const char* owner_passwd,
    const char* user_passwd)
{
    BRST_PTRACE((" BRST_Doc_SetPassword\n"));

    if (!BRST_Doc_Initialized(pdf))
        return BRST_DOC_INVALID_OBJECT;

    if (!pdf->encrypt_dict) {
        pdf->encrypt_dict = BRST_EncryptDict_New(pdf->mmgr, pdf->xref);

        if (!pdf->encrypt_dict)
            return BRST_Error_Check(pdf->error);
    }

    if (BRST_EncryptDict_SetPassword(pdf->encrypt_dict, owner_passwd,
            user_passwd)
        != BRST_OK)
        return BRST_Error_Check(pdf->error);

    return BRST_Doc_SetEncryptOn(pdf);
}

BRST_EXPORT(BRST_STATUS)
BRST_Doc_SetEncryptionMode(BRST_Doc pdf,
    BRST_EncryptMode mode,
    BRST_UINT key_len)
{
    BRST_Encrypt e;

    BRST_PTRACE((" BRST_Doc_SetEncryptionMode\n"));

    if (!BRST_Doc_Validate(pdf))
        return BRST_DOC_INVALID_OBJECT;

    e = BRST_EncryptDict_Attr(pdf->encrypt_dict);

    if (!e)
        return BRST_Error_Raise(pdf->error,
            BRST_DOC_ENCRYPTDICT_NOT_FOUND, 0);
    else {
        if (mode == BRST_ENCRYPT_R2)
            e->key_len = 5;
        else {
            /* if encryption mode is specified revision-3, the version of
             * pdf file is set to 1.4
             */
            if (pdf->pdf_version < BRST_VER_14)
                pdf->pdf_version = BRST_VER_14;

            if (key_len >= 5 && key_len <= 16)
                e->key_len = key_len;
            else if (key_len == 0)
                e->key_len = 16;
            else
                return BRST_Error_Raise(pdf->error,
                    BRST_INVALID_ENCRYPT_KEY_LEN, 0);
        }
        e->mode = mode;
    }

    return BRST_OK;
}

BRST_EXPORT(BRST_STATUS)
BRST_Doc_SetPermission(BRST_Doc pdf,
    BRST_UINT permission)
{
    BRST_Encrypt e;

    BRST_PTRACE((" BRST_Doc_SetPermission\n"));

    if (!BRST_Doc_Initialized(pdf))
        return BRST_DOC_INVALID_OBJECT;

    e = BRST_EncryptDict_Attr(pdf->encrypt_dict);

    if (!e)
        return BRST_Error_Raise(pdf->error,
            BRST_DOC_ENCRYPTDICT_NOT_FOUND, 0);
    else
        e->permission = permission;

    return BRST_OK;
}
