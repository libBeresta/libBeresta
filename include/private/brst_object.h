#ifndef PRIVATE_BRST_OBJECT_H
#define PRIVATE_BRST_OBJECT_H

#include "brst_types.h"
#include "brst_mmgr.h"

/* if BRST_OTYPE_DIRECT bit is set, the object owned by other container
 * object. if BRST_OTYPE_INDIRECT bit is set, the object managed by xref.
 */

#define  BRST_OTYPE_NONE              0x00000000
#define  BRST_OTYPE_DIRECT            0x80000000
#define  BRST_OTYPE_INDIRECT          0x40000000
#define  BRST_OTYPE_ANY               (BRST_OTYPE_DIRECT | BRST_OTYPE_INDIRECT)
#define  BRST_OTYPE_HIDDEN            0x10000000

#define  BRST_OCLASS_UNKNOWN          0x0001
#define  BRST_OCLASS_NULL             0x0002
#define  BRST_OCLASS_BOOLEAN          0x0003
#define  BRST_OCLASS_NUMBER           0x0004
#define  BRST_OCLASS_REAL             0x0005
#define  BRST_OCLASS_NAME             0x0006
#define  BRST_OCLASS_STRING           0x0007
#define  BRST_OCLASS_BINARY           0x0008
#define  BRST_OCLASS_ARRAY            0x0010
#define  BRST_OCLASS_DICT             0x0011
#define  BRST_OCLASS_PROXY            0x0012
#define  BRST_OCLASS_DIRECT           0x00A0
#define  BRST_OCLASS_ANY              0x00FF

#define  BRST_OSUBCLASS_FONT          0x0100
#define  BRST_OSUBCLASS_CATALOG       0x0200
#define  BRST_OSUBCLASS_PAGES         0x0300
#define  BRST_OSUBCLASS_PAGE          0x0400
#define  BRST_OSUBCLASS_XOBJECT       0x0500
#define  BRST_OSUBCLASS_OUTLINE       0x0600
#define  BRST_OSUBCLASS_DESTINATION   0x0700
#define  BRST_OSUBCLASS_ANNOTATION    0x0800
#define  BRST_OSUBCLASS_ENCRYPT       0x0900
#define  BRST_OSUBCLASS_EXT_GSTATE    0x0A00
#define  BRST_OSUBCLASS_EXT_GSTATE_R  0x0B00  /* read only object */
#define  BRST_OSUBCLASS_NAMEDICT      0x0C00
#define  BRST_OSUBCLASS_NAMETREE      0x0D00
#define  BRST_OSUBCLASS_SHADING       0x0E00
#define  BRST_OSUBCLASS_PATTERN       0x0F00

/*
 *  structure of Object-ID
 *
 *  1       direct-object
 *  2       indirect-object
 *  3       reserved
 *  4       shadow-object
 *  5-8     reserved
 *  9-32    object-id
 *
 *  the real Object-ID is described "obj_id & 0x00FFFFFF"
 */

typedef struct BRST_Obj_Header {
    BRST_UINT32  obj_id;
    BRST_UINT16  gen_no;
    BRST_UINT16  obj_class;
} BRST_Obj_Header;

void
BRST_Obj_Free(
    BRST_MMgr mmgr,
    void* obj
);

void
BRST_Obj_ForceFree(
    BRST_MMgr mmgr,
    void* obj
);

BRST_UINT32
BRST_Obj_ID(
    void* obj
);


// TODO Эта функция нужна только в Outline и Image_png, возможно, лучше заменить ее на SetHidden
void
BRST_Obj_SetID(
    void* obj, 
    BRST_UINT32 id
);

BRST_UINT16
BRST_Obj_Class(
    void* obj
);

void
BRST_Obj_SetClass(
    void* obj, 
    BRST_UINT16 cls
);


#endif /* PRIVATE_BRST_OBJECT_H */