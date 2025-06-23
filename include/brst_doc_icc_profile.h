#ifndef BRST_DOC_ICC_PROFILE_H
#define BRST_DOC_ICC_PROFILE_H

BRST_EXPORT(BRST_OutputIntent)
BRST_Doc_IccProfile_LoadFromMem(
    BRST_Doc    pdf,
    BRST_MMgr   mmgr,
    BRST_Stream iccdata,
    BRST_Xref   xref,
    int         numcomponent
);

BRST_EXPORT(BRST_OutputIntent)
BRST_Doc_IccProfile_LoadFromFile(
    BRST_Doc  pdf,
    BRST_CSTR icc_file_name,
    int       numcomponent
);

#endif /* BRST_DOC_ICC_PROFILE_H */