#ifndef PRIVATE_BRST_IMAGE_CCITT_H
#define PRIVATE_BRST_IMAGE_CCITT_H

BRST_STATUS
BRST_Stream_CcittToStream(
    const BRST_BYTE* buf,
    BRST_Stream dst,
    BRST_Encrypt e,
    BRST_UINT width,
    BRST_UINT height,
    BRST_UINT line_width,
    BRST_BOOL top_is_first
);

#endif /* PRIVATE_BRST_IMAGE_CCITT_H */