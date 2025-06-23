#ifndef PRIVATE_BRST_MD5_H
#define PRIVATE_BRST_MD5_H

/*------------------------------------------------------------------------------
 *
 * The code implements MD5 message-digest algorithm is based on the code
 * written by Colin Plumb.
 * The copyright of it is as follows.
 *
 * This code implements the MD5 message-digest algorithm.
 * The algorithm is due to Ron Rivest.  This code was
 * written by Colin Plumb in 1993, no copyright is claimed.
 * This code is in the public domain; do with it what you wish.
 *
 * Equivalent code is available from RSA Data Security, Inc.
 * This code has been tested against that, and is equivalent,
 * except that you don't need to include two pages of legalese
 * with every copy.
 *
 * To compute the message digest of a chunk of bytes, declare an
 * MD5Context structure, pass it to MD5Init, call MD5Update as
 * needed on buffers full of bytes, and then call MD5Final, which
 * will fill a supplied 16-byte array with the digest.
 *
 *---------------------------------------------------------------------------*/

// TODO переместить в internal?
#define BRST_ID_LEN              16
#define BRST_PASSWD_LEN          32
#define BRST_ENCRYPT_KEY_MAX     16
#define BRST_MD5_KEY_LEN         16
#define BRST_PERMISSION_PAD      0xFFFFFFC0
#define BRST_ARC4_BUF_SIZE       256

typedef struct BRST_MD5Context
{
    BRST_UINT32 buf[4];
    BRST_UINT32 bits[2];
    BRST_BYTE in[64];
} BRST_MD5_CTX;

void
BRST_MD5Init(
    // TODO Заменить определение на ссылку
    struct BRST_MD5Context* ctx
);

void
BRST_MD5Update(
    struct BRST_MD5Context* ctx,
    const BRST_BYTE*        buf,
    BRST_UINT32             len
);

void
BRST_MD5Final(
    BRST_BYTE               digest[16],
    struct BRST_MD5Context* ctx
);

#endif /* PRIVATE_BRST_MD5_H */