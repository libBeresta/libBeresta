#ifndef PRIVATE_BRST_PDFA_H
#define PRIVATE_BRST_PDFA_H

BRST_STATUS
BRST_PDFA_AppendOutputIntents(
    BRST_Doc    pdf,
    BRST_CSTR iccname,
    BRST_Dict   iccdict
);

BRST_STATUS
BRST_PDFA_AddXmpMetadata(
    BRST_Doc pdf
);

BRST_STATUS
BRST_PDFA_AddXmpExtension(
    BRST_Doc    pdf,
    BRST_CSTR xmp_description
);

void
BRST_PDFA_ClearXmpExtensions(
    BRST_Doc pdf
);

BRST_STATUS
BRST_PDFA_GenerateID(
    BRST_Doc
);

#endif /* PRIVATE_BRST_PDFA_H */