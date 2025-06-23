#ifndef BRST_SHADING_H
#define BRST_SHADING_H

#include "brst_external.h"
#include "brst_types.h"
#include "brst_dict.h"

typedef BRST_Dict BRST_Shading;

/* 8.7.4.3 Shading Dictionaries */
typedef enum _BRST_ShadingType {
    BRST_SHADING_FUNCTION_BASED = 1,
    BRST_SHADING_AXIAL = 2,
    BRST_SHADING_RADIAL = 3,
    BRST_SHADING_FREE_FORM_TRIANGLE_MESH = 4,
    BRST_SHADING_LATTICE_FORM_TRIANGLE_MESH = 5,
    BRST_SHADING_COONS_PATCH_MESH = 6,
    BRST_SHADING_TENSOR_PRODUCT_PATCH_MESH = 7
} BRST_ShadingType;

typedef enum _BRST_Shading_FreeFormTriangleMeshEdgeFlag {
  BRST_FREE_FORM_TRI_MESH_EDGEFLAG_NO_CONNECTION = 0,
  BRST_FREE_FORM_TRI_MESH_EDGEFLAG_BC,
  BRST_FREE_FORM_TRI_MESH_EDGEFLAG_AC
} BRST_Shading_FreeFormTriangleMeshEdgeFlag;

#endif /* BRST_SHADING_H */