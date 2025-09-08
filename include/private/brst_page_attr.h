#ifndef PRIVATE_BRST_PAGE_ATTR_H
#define PRIVATE_BRST_PAGE_ATTR_H

typedef struct _BRST_PageAttr_Rec {
    BRST_Pages   parent;
    BRST_Dict    fonts;
    BRST_Dict    xobjects;
    BRST_Dict    patterns;
    BRST_Dict    ext_gstates;
    BRST_Dict    shadings;
    BRST_GState  gstate;
    BRST_Point   str_pos;
    BRST_Point   cur_pos;
    BRST_Point   text_pos;
    BRST_Matrix  text_matrix;
    BRST_UINT16  gmode;
    BRST_Dict    contents;
    BRST_Stream  stream;
    BRST_Xref    xref;
    BRST_UINT    compression_mode;
    BRST_PDFVer *ver;
} BRST_PageAttr_Rec;

#endif /* PRIVATE_BRST_PAGE_ATTR_H */