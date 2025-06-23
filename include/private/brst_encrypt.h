#ifndef PRIVATE_BRST_ENCRYPT_H
#define PRIVATE_BRST_ENCRYPT_H

#include "brst_types.h"
#include "brst_encrypt.h"

static const BRST_BYTE BRST_PADDING_STRING[] = {
    0x28, 0xBF, 0x4E, 0x5E, 0x4E, 0x75, 0x8A, 0x41,
    0x64, 0x00, 0x4E, 0x56, 0xFF, 0xFA, 0x01, 0x08,
    0x2E, 0x2E, 0x00, 0xB6, 0xD0, 0x68, 0x3E, 0x80,
    0x2F, 0x0C, 0xA9, 0xFE, 0x64, 0x53, 0x69, 0x7A
};

#define BRST_PASSWD_LEN     32
#define BRST_MD5_KEY_LEN    16
#define BRST_ID_LEN         16
#define BRST_ARC4_BUF_SIZE 256

typedef struct _BRST_ARC4_Ctx_Rec {
    BRST_BYTE idx1;
    BRST_BYTE idx2;
    BRST_BYTE state[BRST_ARC4_BUF_SIZE];
} BRST_ARC4_Ctx_Rec;

typedef struct _BRST_Encrypt_Rec {
    BRST_EncryptMode mode;

    /* key_len must be a multiple of 8, and between 40 to 128 */
    BRST_UINT key_len;

    /* owner-password (not encrypted) */
    BRST_BYTE owner_passwd[BRST_PASSWD_LEN];

    /* user-password (not encrypted) */
    BRST_BYTE user_passwd[BRST_PASSWD_LEN];

    /* owner-password (encrypted) */
    BRST_BYTE owner_key[BRST_PASSWD_LEN];

    /* user-password (encrypted) */
    BRST_BYTE user_key[BRST_PASSWD_LEN];

    BRST_INT permission;
    BRST_BYTE encrypt_id[BRST_ID_LEN];
    BRST_BYTE encryption_key[BRST_MD5_KEY_LEN + 5];
    BRST_BYTE md5_encryption_key[BRST_MD5_KEY_LEN];
    BRST_ARC4_Ctx_Rec arc4ctx;
} BRST_Encrypt_Rec;
typedef struct _BRST_Encrypt_Rec* BRST_Encrypt;

void
BRST_PadOrTrancatePasswd(
    const char* pwd,
    BRST_BYTE* new_pwd);

void
BRST_Encrypt_Init(
    BRST_Encrypt attr);

void
BRST_Encrypt_CreateUserKey(
    BRST_Encrypt attr);

void
BRST_Encrypt_CreateOwnerKey(
    BRST_Encrypt attr);

void
BRST_Encrypt_CreateEncryptionKey(
    BRST_Encrypt attr);

void
BRST_Encrypt_InitKey(
    BRST_Encrypt attr,
    BRST_UINT32 object_id,
    BRST_UINT16 gen_no);

void
BRST_Encrypt_Reset(
    BRST_Encrypt attr);

void
BRST_Encrypt_CryptBuf(
    BRST_Encrypt     attr,
    const BRST_BYTE* src,
    BRST_BYTE*       dst,
    BRST_UINT        len);

#endif /* PRIVATE_BRST_ENCRYPT_H */