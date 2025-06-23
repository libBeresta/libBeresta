#include "brst_mmgr.h"
#include "brst_dict.h"
#include "brst_stream.h"
#include "brst_xref.h"
#include "brst_encrypt.h"
#include "brst_encoder.h"
#include "brst_doc_info.h"
#include "private/brst_info.h"
#include "private/brst_encrypt_dict.h"
#include "private/brst_utils.h"
#include "private/brst_xref.h"
#include "brst_consts.h"
#include "brst_error.h"
#include "private/brst_binary.h"
#include "private/brst_md5.h"
#include "private/brst_c.h"

#include <time.h>

BRST_EncryptDict
BRST_EncryptDict_New(BRST_MMgr mmgr,
    BRST_Xref xref)
{
    BRST_Encrypt attr;
    BRST_EncryptDict dict;

    BRST_PTRACE((" BRST_EncryptDict_New\n"));

    dict = BRST_Dict_New(mmgr);
    if (!dict)
        return NULL;

    dict->header.obj_class |= BRST_OSUBCLASS_ENCRYPT;
    dict->free_fn = BRST_EncryptDict_OnFree;

    attr = BRST_GetMem(dict->mmgr, sizeof(BRST_Encrypt_Rec));
    if (!attr) {
        BRST_Dict_Free(dict);
        return NULL;
    }

    dict->attr = attr;
    BRST_Encrypt_Init(attr);

    if (BRST_Xref_Add(xref, dict) != BRST_OK)
        return NULL;

    return dict;
}

void BRST_EncryptDict_CreateID(BRST_EncryptDict dict,
    BRST_Dict info,
    BRST_Xref xref)
{
    BRST_MD5_CTX ctx;
    BRST_Encrypt attr = (BRST_Encrypt)dict->attr;

    /* use the result of 'time' function to get random value.
     * when debugging, 'time' value is ignored.
     */
#ifndef LIBBRST_DEBUG
    time_t t = BRST_TIME(NULL);
#endif /* LIBBRST_DEBUG */

    BRST_MD5Init(&ctx);
    BRST_UNUSED(xref);
    BRST_UNUSED(info);

#ifndef LIBBRST_DEBUG
    BRST_MD5Update(&ctx, (BRST_BYTE*)&t, sizeof(t));

    /* create File Identifier from elements of Into dictionary. */
    if (info) {
        const char* s;
        BRST_UINT len;

        /* Author */
        s = BRST_Info_InfoAttr(info, BRST_INFO_AUTHOR);
        if ((len = BRST_StrLen(s, -1)) > 0)
            BRST_MD5Update(&ctx, (const BRST_BYTE*)s, len);

        /* Creator */
        s = BRST_Info_InfoAttr(info, BRST_INFO_CREATOR);
        if ((len = BRST_StrLen(s, -1)) > 0)
            BRST_MD5Update(&ctx, (const BRST_BYTE*)s, len);

        /* Producer */
        s = BRST_Info_InfoAttr(info, BRST_INFO_PRODUCER);
        if ((len = BRST_StrLen(s, -1)) > 0)
            BRST_MD5Update(&ctx, (const BRST_BYTE*)s, len);

        /* Title */
        s = BRST_Info_InfoAttr(info, BRST_INFO_TITLE);
        if ((len = BRST_StrLen(s, -1)) > 0)
            BRST_MD5Update(&ctx, (const BRST_BYTE*)s, len);

        /* Subject */
        s = BRST_Info_InfoAttr(info, BRST_INFO_SUBJECT);
        if ((len = BRST_StrLen(s, -1)) > 0)
            BRST_MD5Update(&ctx, (const BRST_BYTE*)s, len);

        /* Keywords */
        s = BRST_Info_InfoAttr(info, BRST_INFO_KEYWORDS);
        if ((len = BRST_StrLen(s, -1)) > 0)
            BRST_MD5Update(&ctx, (const BRST_BYTE*)s, len);

        BRST_UINT cnt = BRST_List_Count(BRST_Xref_Entries(xref));
        BRST_MD5Update(&ctx, (const BRST_BYTE*)&(cnt),
            sizeof(BRST_UINT32));
    }
#endif
    BRST_MD5Final(attr->encrypt_id, &ctx);
}

BRST_STATUS
BRST_EncryptDict_Prepare(BRST_EncryptDict dict,
    BRST_Dict info,
    BRST_Xref xref)
{
    BRST_STATUS ret;
    BRST_Encrypt attr = (BRST_Encrypt)dict->attr;
    BRST_Binary user_key;
    BRST_Binary owner_key;

    BRST_PTRACE((" BRST_EncryptDict_Prepare\n"));

    BRST_EncryptDict_CreateID(dict, info, xref);
    BRST_Encrypt_CreateOwnerKey(attr);
    BRST_Encrypt_CreateEncryptionKey(attr);
    BRST_Encrypt_CreateUserKey(attr);

    owner_key = BRST_Binary_New(dict->mmgr, attr->owner_key, BRST_PASSWD_LEN);
    if (!owner_key)
        return BRST_Error_Code(dict->error);

    if ((ret = BRST_Dict_Add(dict, "O", owner_key)) != BRST_OK)
        return ret;

    user_key = BRST_Binary_New(dict->mmgr, attr->user_key, BRST_PASSWD_LEN);
    if (!user_key)
        return BRST_Error_Code(dict->error);

    if ((ret = BRST_Dict_Add(dict, "U", user_key)) != BRST_OK)
        return ret;

    ret += BRST_Dict_AddName(dict, "Filter", "Standard");

    if (attr->mode == BRST_ENCRYPT_R2) {
        ret += BRST_Dict_AddNumber(dict, "V", 1);
        ret += BRST_Dict_AddNumber(dict, "R", 2);
    } else if (attr->mode == BRST_ENCRYPT_R3) {
        ret += BRST_Dict_AddNumber(dict, "V", 2);
        ret += BRST_Dict_AddNumber(dict, "R", 3);
        ret += BRST_Dict_AddNumber(dict, "Length", attr->key_len * 8);
    }

    ret += BRST_Dict_AddNumber(dict, "P", attr->permission);

    if (ret != BRST_OK)
        return BRST_Error_Code(dict->error);

    return BRST_OK;
}

void BRST_EncryptDict_OnFree(BRST_Dict obj)
{
    BRST_Encrypt attr = (BRST_Encrypt)obj->attr;

    BRST_PTRACE((" BRST_EncryptDict_OnFree\n"));

    if (attr)
        BRST_FreeMem(obj->mmgr, attr);
}

void BRST_PadOrTruncatePasswd(const char* pwd,
    BRST_BYTE* new_pwd)
{
    BRST_UINT len = BRST_StrLen(pwd, BRST_PASSWD_LEN + 1);

    BRST_PTRACE((" BRST_PadOrTruncatePasswd\n"));

    BRST_MemSet(new_pwd, 0x00, BRST_PASSWD_LEN);

    if (len >= BRST_PASSWD_LEN) {
        BRST_MemCpy(new_pwd, (BRST_BYTE*)pwd, BRST_PASSWD_LEN);
    } else {
        if (len > 0) {
            BRST_MemCpy(new_pwd, (BRST_BYTE*)pwd, len);
        }
        BRST_MemCpy(new_pwd + len, BRST_PADDING_STRING, BRST_PASSWD_LEN - len);
    }
}

BRST_STATUS
BRST_EncryptDict_SetPassword(BRST_EncryptDict dict,
    const char* owner_passwd,
    const char* user_passwd)
{
    BRST_Encrypt attr = (BRST_Encrypt)dict->attr;

    BRST_PTRACE((" BRST_EncryptDict_SetPassword\n"));

    if (BRST_StrLen(owner_passwd, 2) == 0)
        return BRST_Error_Set(dict->error, BRST_ENCRYPT_INVALID_PASSWORD, 0);

    if (owner_passwd && user_passwd && BRST_StrCmp(owner_passwd, user_passwd) == 0)
        return BRST_Error_Set(dict->error, BRST_ENCRYPT_INVALID_PASSWORD, 0);

    BRST_PadOrTruncatePasswd(owner_passwd, attr->owner_passwd);
    BRST_PadOrTruncatePasswd(user_passwd, attr->user_passwd);

    return BRST_OK;
}

BRST_BOOL
BRST_EncryptDict_Validate(BRST_EncryptDict dict)
{
    BRST_Obj_Header* header = (BRST_Obj_Header*)dict;

    BRST_PTRACE((" BRST_EncryptDict_Validate\n"));

    if (!dict || !dict->attr)
        return BRST_FALSE;

    if (header->obj_class != (BRST_OCLASS_DICT | BRST_OSUBCLASS_ENCRYPT))
        return BRST_FALSE;

    return BRST_TRUE;
}

BRST_Encrypt
BRST_EncryptDict_Attr(BRST_EncryptDict dict)
{
    BRST_Obj_Header* header = (BRST_Obj_Header*)dict;

    BRST_PTRACE((" BRST_EncryptDict_Attr\n"));

    if (dict && dict->attr && (header->obj_class == (BRST_OCLASS_DICT | BRST_OSUBCLASS_ENCRYPT)))
        return (BRST_Encrypt)dict->attr;

    return NULL;
}
