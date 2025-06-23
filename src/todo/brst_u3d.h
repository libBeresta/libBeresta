#ifndef BRST_U3D_H
#define BRST_U3D_H
// TODO Перенести функции JavaScript и U3D
/*---------------------------------------------------------------------------*/
/*----- BRST_3DMatrix struct ------------------------------------------------*/

typedef struct _BRST_3DMatrix {
    BRST_REAL a;
    BRST_REAL b;
    BRST_REAL c;
    BRST_REAL d;
    BRST_REAL e;
    BRST_REAL f;
    BRST_REAL g;
    BRST_REAL h;
    BRST_REAL i;
    BRST_REAL tx;
    BRST_REAL ty;
    BRST_REAL tz;
} BRST_3DMatrix;

/*--------------------------------------------------------------------------*/
/*----- 3D View ------------------------------------------------------------*/

BRST_EXPORT(BRST_Dict)
BRST_Page_Create3DView(
    BRST_Page       page,
    BRST_U3D        u3d,
    BRST_Annotation annot3d,
    BRST_CSTR       name
);

BRST_EXPORT(BRST_STATUS)
BRST_3DView_Add3DC3DMeasure(
    BRST_Dict      view,
    BRST_3DMeasure measure
);

BRST_EXPORT(BRST_JavaScript) 
BRST_CreateJavaScript(
    BRST_Doc  pdf, 
    BRST_CSTR code
);

BRST_EXPORT(BRST_JavaScript) 
BRST_LoadJSFromFile(
    BRST_Doc  pdf, 
    BRST_CSTR filename
);

BRST_EXPORT(BRST_Image)
BRST_LoadU3DFromFile(
    BRST_Doc  pdf,
    BRST_CSTR filename
);

BRST_EXPORT(BRST_Image)
BRST_LoadU3DFromMem(
    BRST_Doc         pdf,
    const BRST_BYTE* buffer,
    BRST_UINT        size
);

BRST_EXPORT(BRST_U3D) 
BRST_LoadU3DFromFile(
    BRST_Doc  pdf, 
    BRST_CSTR filename
);

BRST_EXPORT(BRST_Image) 
BRST_LoadU3DFromMem(
    BRST_Doc         pdf, 
    const BRST_BYTE* buffer, 
    BRST_UINT        size
);

BRST_EXPORT(BRST_Dict) 
BRST_Create3DView(
    BRST_MMgr mmgr, 
    BRST_CSTR name
);

BRST_EXPORT(BRST_STATUS) 
BRST_U3D_Add3DView(
    BRST_U3D u3d, 
    BRST_Dict view
);

BRST_EXPORT(BRST_STATUS)
BRST_U3D_SetDefault3DView(
    BRST_U3D  u3d, 
    BRST_CSTR name
);

BRST_EXPORT(BRST_STATUS) 
BRST_U3D_AddOnInstanciate(
    BRST_U3D        u3d,
    BRST_JavaScript javaScript
);

BRST_EXPORT(BRST_Dict)
BRST_3DView_CreateNode(
    BRST_Dict view,
    BRST_CSTR name
);

BRST_EXPORT(BRST_STATUS)
BRST_3DViewNode_SetOpacity(
    BRST_Dict node, 
    BRST_REAL opacity
);

BRST_EXPORT(BRST_STATUS)
BRST_3DViewNode_SetVisibility(
    BRST_Dict node,
    BRST_BOOL visible
);

BRST_EXPORT(BRST_STATUS)
BRST_3DViewNode_SetMatrix(
    BRST_Dict     node,
    BRST_3DMatrix Mat3D
);

BRST_EXPORT(BRST_STATUS)
BRST_3DView_AddNode(
    BRST_Dict view,
    BRST_Dict node
);

BRST_EXPORT(BRST_STATUS)
BRST_3DView_SetLighting(
    BRST_Dict view,
    BRST_CSTR scheme
);

BRST_EXPORT(BRST_STATUS) 
BRST_3DView_SetBackgroundColor(
    BRST_Dict view, 
    BRST_REAL r,
    BRST_REAL g, 
    BRST_REAL b
);

BRST_EXPORT(BRST_STATUS) 
BRST_3DView_SetPerspectiveProjection(
    BRST_Dict view, 
    BRST_REAL fov
);

BRST_EXPORT(BRST_STATUS) 
BRST_3DView_SetOrthogonalProjection(
    BRST_Dict view, 
    BRST_REAL mag
);

BRST_EXPORT(BRST_STATUS)
BRST_3DView_SetCamera(
    BRST_Dict view,
    BRST_REAL coox,
    BRST_REAL cooy,
    BRST_REAL cooz,
    BRST_REAL c2cx,
    BRST_REAL c2cy,
    BRST_REAL c2cz,
    BRST_REAL roo,
    BRST_REAL roll
);

BRST_EXPORT(BRST_STATUS)
BRST_3DView_SetCameraByMatrix(
    BRST_Dict view, 
    BRST_3DMatrix Mat3D,
    BRST_REAL co
);

BRST_EXPORT(BRST_STATUS)
BRST_3DView_SetCrossSectionOn(
    BRST_Dict    view,
    BRST_Point3D center,
    BRST_REAL    roll,
    BRST_REAL    pitch,
    BRST_REAL    opacity,
    BRST_BOOL    showintersection
);

BRST_EXPORT(BRST_STATUS) 
BRST_3DView_SetCrossSectionOff(
    BRST_Dict view
);

BRST_Dict
BRST_3DView_New(
    BRST_MMgr mmgr,
    BRST_Xref xref,
    BRST_U3D  u3d,
    BRST_CSTR name
);

#define /* BRST_U3D_H */