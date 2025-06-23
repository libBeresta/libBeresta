#ifndef PRIVATE_BRST_IMAGE_PNG_H
#define PRIVATE_BRST_IMAGE_PNG_H

BRST_Image
BRST_Image_Png_Load(
    BRST_MMgr   mmgr,
    BRST_Stream png_data,
    BRST_Xref   xref,
    BRST_BOOL   delayed_loading
);

BRST_Image
BRST_Image_Png_LoadFromStream(
    BRST_MMgr mmgr,
    BRST_Xref xref,
    BRST_BOOL compression_mode,
    BRST_Stream imagedata,
    BRST_BOOL delayed_loading
);

#endif /* PRIVATE_BRST_IMAGE_PNG_H */