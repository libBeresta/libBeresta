#ifndef PRIVATE_BRST_IMAGE_TIFF_H
#define PRIVATE_BRST_IMAGE_TIFF_H

BRST_Image
BRST_Image_Raw1Bit_LoadFromMemory(
    BRST_MMgr        mmgr,
    const BRST_BYTE* buf,
    BRST_Xref        xref,
    BRST_UINT        width,
    BRST_UINT        height,
    BRST_UINT        line_width,
    BRST_BOOL        top_is_first
);

BRST_Image
BRST_Image_Raw_Load(
    BRST_MMgr       mmgr,
    BRST_Stream     stream,
    BRST_Xref       xref,
    BRST_UINT       width,
    BRST_UINT       height,
    BRST_ColorSpace color_space
);

BRST_Image
BRST_Image_Raw_LoadFromMemory(
    BRST_MMgr        mmgr,
    const BRST_BYTE* buf,
    BRST_Xref        xref,
    BRST_UINT        width,
    BRST_UINT        height,
    BRST_ColorSpace  color_space,
    BRST_UINT        bits_per_component
);

#endif /* PRIVATE_BRST_IMAGE_TIFF_H */