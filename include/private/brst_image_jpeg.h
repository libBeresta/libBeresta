#ifndef PRIVATE_BRST_IMAGE_JPEG_H
#define PRIVATE_BRST_IMAGE_JPEG_H

BRST_Image
BRST_Image_Jpeg_Load(
    BRST_MMgr   mmgr,
    BRST_Stream jpeg_data,
    BRST_Xref   xref
);

BRST_Image
BRST_Image_Jpeg_LoadFromMem(
    BRST_MMgr        mmgr,
    const BRST_BYTE* buf,
    BRST_UINT        size,
    BRST_Xref        xref
);

#endif /* PRIVATE_BRST_IMAGE_JPEG_H */