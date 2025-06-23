#ifndef PRIVATE_BRST_XREF_H
#define PRIVATE_BRST_XREF_H

#include "brst_xref.h"
#include "brst_types.h"
#include "brst_mmgr.h"
#include "brst_stream.h"
#include "brst_dict.h"

typedef struct _BRST_XrefEntry_Rec {
      char        entry_typ;
      BRST_UINT   byte_offset;
      BRST_UINT16 gen_no;
      void*       obj;
} BRST_XrefEntry_Rec;

typedef struct _BRST_Xref_Rec {
      BRST_MMgr   mmgr;
      BRST_Error  error;
      BRST_UINT32 start_offset;
      BRST_List   entries;
      BRST_UINT   addr;
      BRST_Xref   prev;
      BRST_Dict   trailer;
} BRST_Xref_Rec;

typedef struct _BRST_XrefEntry_Rec* BRST_XrefEntry;

BRST_Xref
BRST_Xref_New(
    BRST_MMgr   mmgr,
    BRST_UINT32 offset
);

void
BRST_Xref_Free(
    BRST_Xref xref
);

BRST_STATUS
BRST_Xref_Add(
    BRST_Xref xref,
    void*     obj
);

BRST_XrefEntry
BRST_Xref_GetEntry(
    BRST_Xref xref,
    BRST_UINT index
);

BRST_STATUS
BRST_Xref_WriteToStream(
    BRST_Xref    xref,
    BRST_Stream  stream,
    BRST_Encrypt e
);

BRST_XrefEntry
BRST_Xref_GetEntryByObjectId(
    BRST_Xref xref,
    BRST_UINT obj_id
);

BRST_Dict
BRST_DictStream_New(
    BRST_MMgr mmgr,
    BRST_Xref xref
);

BRST_List
BRST_Xref_Entries(
    BRST_Xref xref
);


#endif /* PRIVATE_BRST_XREF_H */