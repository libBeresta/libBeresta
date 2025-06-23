#ifndef PRIVATE_BRST_DOC_ENCODER_H
#define PRIVATE_BRST_DOC_ENCODER_H

BRST_STATUS
BRST_Doc_RegisterEncoder(
    BRST_Doc     pdf,
    BRST_Encoder encoder
);

BRST_Encoder
BRST_Doc_FindEncoder(
    BRST_Doc    pdf,
    const char* encoding_name
);

void
FreeEncoderList(
    BRST_Doc pdf
);

#endif /* PRIVATE_BRST_DOC_ENCODER_H */