#ifndef PRIVATE_BRST_SHADING_H
#define PRIVATE_BRST_SHADING_H

/* Notes for docs:
 * - ShadingType must be BRST_SHADING_FREE_FORM_TRIANGLE_MESH (the only
 *   defined option...)
 * - colorSpace must be BRST_CS_DEVICE_RGB for now.
 */
BRST_Shading
BRST_Shading_New(
    BRST_MMgr        mmgr,
    BRST_Xref        xref
    BRST_ShadingType type,
    BRST_ColorSpace  colorSpace,
    BRST_REAL        xMin,
    BRST_REAL        xMax,
    BRST_REAL        yMin,
    BRST_REAL        yMax
);

BRST_STATUS
BRST_Shading_AddVertexRGB(
    BRST_Shading                              shading,
    BRST_Shading_FreeFormTriangleMeshEdgeFlag edgeFlag,
    BRST_REAL                                 x,
    BRST_REAL                                 y,
    BRST_UINT8                                r,
    BRST_UINT8                                g,
    BRST_UINT8                                b
);

#endif /* PRIVATE_BRST_SHADING_H */