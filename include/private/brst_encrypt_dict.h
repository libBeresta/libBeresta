#ifndef PRIVATE_BRST_ENCRYPT_DICT_H
#define PRIVATE_BRST_ENCRYPT_DICT_H

#include "brst_dict.h"

typedef BRST_Dict BRST_EncryptDict;

BRST_EncryptDict
BRST_EncryptDict_New(
    BRST_MMgr mmgr,
    BRST_Xref xref
);

void
BRST_EncryptDict_CreateID(
    BRST_EncryptDict dict,
    BRST_Dict        info,
    BRST_Xref        xref
);

void
BRST_EncryptDict_OnFree(
    BRST_Dict obj
);

BRST_STATUS
BRST_EncryptDict_SetPassword(
    BRST_EncryptDict dict,
    const char* owner_passwd,
    const char* user_passwd
);

BRST_BOOL
BRST_EncryptDict_Validate(
    BRST_EncryptDict dict
);

BRST_STATUS
BRST_EncryptDict_Prepare(
    BRST_EncryptDict dict,
    BRST_Dict        info,
    BRST_Xref        xref
);

BRST_Encrypt
BRST_EncryptDict_Attr(
    BRST_EncryptDict dict
);

#endif /* BRST_ENCRYPT_DICT_H */
