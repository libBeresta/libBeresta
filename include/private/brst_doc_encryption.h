#ifndef PRIVATE_BRST_DOC_ENCRYPTION_H
#define PRIVATE_BRST_DOC_ENCRYPTION_H

BRST_STATUS
BRST_Doc_SetEncryptOn(
    BRST_Doc pdf
);

BRST_STATUS
BRST_Doc_SetEncryptOff(
    BRST_Doc pdf
);

BRST_STATUS
BRST_Doc_PrepareEncryption(
    BRST_Doc pdf
);

#endif /* PRIVATE_BRST_DOC_ENCRYPTION_H */