#include "brst_types.h"
#include "private/brst_utils.h"
#include "brst_encrypt.h"
#include "brst_consts.h"
#include "private/brst_md5.h"
#include "private/brst_defines.h"
#include "private/brst_encrypt.h"

#define BRST_ENCRYPT_KEY_MAX 16
#define BRST_PERMISSION_PAD 0xFFFFFFC0

/*----- encrypt-obj ---------------------------------------------------------*/

static void
ARC4Init(BRST_ARC4_Ctx_Rec* ctx,
    const BRST_BYTE* key,
    BRST_UINT key_len);

static void
ARC4CryptBuf(BRST_ARC4_Ctx_Rec* ctx,
    const BRST_BYTE* in,
    BRST_BYTE* out,
    BRST_UINT len);

/*---------------------------------------------------------------------------*/

void BRST_Encrypt_Init(BRST_Encrypt attr)
{
    BRST_MemSet(attr, 0, sizeof(BRST_Encrypt_Rec));
    attr->mode    = BRST_ENCRYPT_R2;
    attr->key_len = 5;
    BRST_MemCpy(attr->owner_passwd, BRST_PADDING_STRING, BRST_PASSWD_LEN);
    BRST_MemCpy(attr->user_passwd, BRST_PADDING_STRING, BRST_PASSWD_LEN);
    attr->permission = BRST_ENABLE_PRINT | BRST_ENABLE_EDIT_ALL | BRST_ENABLE_COPY | BRST_ENABLE_EDIT | BRST_PERMISSION_PAD;
}

void BRST_Encrypt_CreateOwnerKey(BRST_Encrypt attr)
{
    BRST_ARC4_Ctx_Rec rc4_ctx;
    BRST_MD5_CTX md5_ctx;
    BRST_BYTE digest[BRST_MD5_KEY_LEN];
    BRST_BYTE tmppwd[BRST_PASSWD_LEN];

    BRST_PTRACE(" BRST_Encrypt_CreateOwnerKey\n");

    /* create md5-digest using the value of owner_passwd */

    /* Algorithm 3.3 step 2 */
    BRST_MD5Init(&md5_ctx);
    BRST_MD5Update(&md5_ctx, attr->owner_passwd, BRST_PASSWD_LEN);

    BRST_PTRACE("@ Algorithm 3.3 step 2\n");

    BRST_MD5Final(digest, &md5_ctx);

    /* Algorithm 3.3 step 3 (Revision 3 only) */
    if (attr->mode == BRST_ENCRYPT_R3) {
        BRST_UINT i;

        for (i = 0; i < 50; i++) {
            BRST_MD5Init(&md5_ctx);

            /* BRST_MD5Update (&md5_ctx, digest, BRST_MD5_KEY_LEN); */
            BRST_MD5Update(&md5_ctx, digest, attr->key_len);
            BRST_MD5Final(digest, &md5_ctx);

            BRST_PTRACE("@ Algorithm 3.3 step 3 loop %u\n", i);
        }
    }

    /* Algorithm 3.3 step 4 */
    BRST_PTRACE("@ Algorithm 3.3 step 7 loop 0\n");

    ARC4Init(&rc4_ctx, digest, attr->key_len);

    BRST_PTRACE("@ Algorithm 3.3 step 5\n");

    /* Algorithm 3.3 step 6 */
    BRST_PTRACE("@ Algorithm 3.3 step 6\n");
    ARC4CryptBuf(&rc4_ctx, attr->user_passwd, tmppwd, BRST_PASSWD_LEN);

    /* Algorithm 3.3 step 7 */
    BRST_PTRACE("@ Algorithm 3.3 step 7\n");
    if (attr->mode == BRST_ENCRYPT_R3) {
        BRST_BYTE tmppwd2[BRST_PASSWD_LEN];
        BRST_UINT i;

        for (i = 1; i <= 19; i++) {
            BRST_UINT j;
            BRST_BYTE new_key[BRST_MD5_KEY_LEN];

            for (j = 0; j < attr->key_len; j++)
                new_key[j] = (BRST_BYTE)(digest[j] ^ i);

            BRST_PTRACE("@ Algorithm 3.3 step 7 loop %u\n", i);

            BRST_MemCpy(tmppwd2, tmppwd, BRST_PASSWD_LEN);
            ARC4Init(&rc4_ctx, new_key, attr->key_len);
            ARC4CryptBuf(&rc4_ctx, tmppwd2, tmppwd, BRST_PASSWD_LEN);
        }
    }

    /* Algorithm 3.3 step 8 */
    BRST_PTRACE("@ Algorithm 3.3 step 8\n");
    BRST_MemCpy(attr->owner_key, tmppwd, BRST_PASSWD_LEN);
}

void BRST_Encrypt_CreateEncryptionKey(BRST_Encrypt attr)
{
    BRST_MD5_CTX md5_ctx;
    BRST_BYTE tmp_flg[4];

    BRST_PTRACE(" BRST_Encrypt_CreateEncryptionKey\n");

    /* Algorithm3.2 step2 */
    BRST_MD5Init(&md5_ctx);
    BRST_MD5Update(&md5_ctx, attr->user_passwd, BRST_PASSWD_LEN);

    /* Algorithm3.2 step3 */
    BRST_MD5Update(&md5_ctx, attr->owner_key, BRST_PASSWD_LEN);

    /* Algorithm3.2 step4 */
    BRST_PTRACE("@@@ permission =%d\n", attr->permission);
    tmp_flg[0] = (BRST_BYTE)(attr->permission);
    tmp_flg[1] = (BRST_BYTE)(attr->permission >> 8);
    tmp_flg[2] = (BRST_BYTE)(attr->permission >> 16);
    tmp_flg[3] = (BRST_BYTE)(attr->permission >> 24);

    BRST_MD5Update(&md5_ctx, tmp_flg, 4);

    /* Algorithm3.2 step5 */
    BRST_PTRACE("@ Algorithm 3.2 step 5\n");

    BRST_MD5Update(&md5_ctx, attr->encrypt_id, BRST_ID_LEN);
    BRST_MD5Final(attr->encryption_key, &md5_ctx);

    /* Algorithm 3.2 step6 (Revision 3 only) */
    if (attr->mode == BRST_ENCRYPT_R3) {
        BRST_UINT i;

        for (i = 0; i < 50; i++) {
            BRST_PTRACE("@ Algorithm 3.3 step 6 loop %u\n", i);
            BRST_MD5Init(&md5_ctx);
            BRST_MD5Update(&md5_ctx, attr->encryption_key, attr->key_len);
            BRST_MD5Final(attr->encryption_key, &md5_ctx);
        }
    }
}

void BRST_Encrypt_CreateUserKey(BRST_Encrypt attr)
{
    BRST_ARC4_Ctx_Rec ctx;

    BRST_PTRACE(" BRST_Encrypt_CreateUserKey\n");

    /* Algorithm 3.4/5 step1 */

    /* Algorithm 3.4 step2 */
    ARC4Init(&ctx, attr->encryption_key, attr->key_len);
    ARC4CryptBuf(&ctx, BRST_PADDING_STRING, attr->user_key, BRST_PASSWD_LEN);

    if (attr->mode == BRST_ENCRYPT_R3) {
        BRST_MD5_CTX md5_ctx;
        BRST_BYTE digest[BRST_MD5_KEY_LEN];
        BRST_BYTE digest2[BRST_MD5_KEY_LEN];
        BRST_UINT i;

        /* Algorithm 3.5 step2 (same as Algorithm3.2 step2) */
        BRST_MD5Init(&md5_ctx);
        BRST_MD5Update(&md5_ctx, BRST_PADDING_STRING, BRST_PASSWD_LEN);

        /* Algorithm 3.5 step3 */
        BRST_MD5Update(&md5_ctx, attr->encrypt_id, BRST_ID_LEN);
        BRST_MD5Final(digest, &md5_ctx);

        BRST_PTRACE("@ Algorithm 3.5 step 3\n");

        /* Algorithm 3.5 step4 */
        ARC4Init(&ctx, attr->encryption_key, attr->key_len);
        ARC4CryptBuf(&ctx, digest, digest2, BRST_MD5_KEY_LEN);

        BRST_PTRACE("@ Algorithm 3.5 step 4\n");

        /* Algorithm 3.5 step5 */
        for (i = 1; i <= 19; i++) {
            BRST_UINT j;
            BRST_BYTE new_key[BRST_MD5_KEY_LEN];

            BRST_PTRACE("@ Algorithm 3.5 step 5 loop %u\n", i);

            for (j = 0; j < attr->key_len; j++)
                new_key[j] = (BRST_BYTE)(attr->encryption_key[j] ^ i);

            BRST_MemCpy(digest, digest2, BRST_MD5_KEY_LEN);

            ARC4Init(&ctx, new_key, attr->key_len);
            ARC4CryptBuf(&ctx, digest, digest2, BRST_MD5_KEY_LEN);
        }

        /* use the result of Algorithm 3.4 as 'arbitrary padding' */
        BRST_MemSet(attr->user_key, 0, BRST_PASSWD_LEN);
        BRST_MemCpy(attr->user_key, digest2, BRST_MD5_KEY_LEN);
    }
}

void ARC4Init(BRST_ARC4_Ctx_Rec* ctx,
    const BRST_BYTE* key,
    BRST_UINT key_len)
{
    BRST_BYTE tmp_array[BRST_ARC4_BUF_SIZE];
    BRST_UINT i;
    BRST_UINT j = 0;

    BRST_PTRACE(" ARC4Init\n");

    for (i = 0; i < BRST_ARC4_BUF_SIZE; i++)
        ctx->state[i] = (BRST_BYTE)i;

    for (i = 0; i < BRST_ARC4_BUF_SIZE; i++)
        tmp_array[i] = key[i % key_len];

    for (i = 0; i < BRST_ARC4_BUF_SIZE; i++) {
        BRST_BYTE tmp;

        j = (j + ctx->state[i] + tmp_array[i]) % BRST_ARC4_BUF_SIZE;

        tmp           = ctx->state[i];
        ctx->state[i] = ctx->state[j];
        ctx->state[j] = tmp;
    }

    ctx->idx1 = 0;
    ctx->idx2 = 0;
}

void ARC4CryptBuf(BRST_ARC4_Ctx_Rec* ctx,
    const BRST_BYTE* in,
    BRST_BYTE* out,
    BRST_UINT len)
{
    BRST_UINT i;
    BRST_UINT t;
    BRST_BYTE K;

    BRST_PTRACE(" ARC4CryptBuf\n");

    for (i = 0; i < len; i++) {
        BRST_BYTE tmp;

        ctx->idx1 = (BRST_BYTE)((ctx->idx1 + 1) % 256);
        ctx->idx2 = (BRST_BYTE)((ctx->idx2 + ctx->state[ctx->idx1]) % 256);

        tmp                   = ctx->state[ctx->idx1];
        ctx->state[ctx->idx1] = ctx->state[ctx->idx2];
        ctx->state[ctx->idx2] = tmp;

        t = (ctx->state[ctx->idx1] + ctx->state[ctx->idx2]) % 256;
        K = ctx->state[t];

        out[i] = (BRST_BYTE)(in[i] ^ K);
    }
}

void BRST_Encrypt_InitKey(BRST_Encrypt attr,
    BRST_UINT32 object_id,
    BRST_UINT16 gen_no)
{
    BRST_MD5_CTX ctx;
    BRST_UINT key_len;

    BRST_PTRACE(" BRST_Encrypt_Init\n");

    attr->encryption_key[attr->key_len]     = (BRST_BYTE)object_id;
    attr->encryption_key[attr->key_len + 1] = (BRST_BYTE)(object_id >> 8);
    attr->encryption_key[attr->key_len + 2] = (BRST_BYTE)(object_id >> 16);
    attr->encryption_key[attr->key_len + 3] = (BRST_BYTE)gen_no;
    attr->encryption_key[attr->key_len + 4] = (BRST_BYTE)(gen_no >> 8);

    BRST_PTRACE("@@@ OID=%u, gen_no=%u\n", (BRST_INT)object_id, gen_no);

    BRST_MD5Init(&ctx);
    BRST_MD5Update(&ctx, attr->encryption_key, attr->key_len + 5);
    BRST_MD5Final(attr->md5_encryption_key, &ctx);

    key_len = (attr->key_len + 5 > BRST_ENCRYPT_KEY_MAX) ? BRST_ENCRYPT_KEY_MAX : attr->key_len + 5;

    ARC4Init(&attr->arc4ctx, attr->md5_encryption_key, key_len);
}

void BRST_Encrypt_Reset(BRST_Encrypt attr)
{
    BRST_UINT key_len = (attr->key_len + 5 > BRST_ENCRYPT_KEY_MAX) ? BRST_ENCRYPT_KEY_MAX : attr->key_len + 5;

    BRST_PTRACE(" BRST_Encrypt_Reset\n");

    ARC4Init(&attr->arc4ctx, attr->md5_encryption_key, key_len);
}

void BRST_Encrypt_CryptBuf(BRST_Encrypt attr,
    const BRST_BYTE* src,
    BRST_BYTE* dst,
    BRST_UINT len)
{
    ARC4CryptBuf(&attr->arc4ctx, src, dst, len);
}
