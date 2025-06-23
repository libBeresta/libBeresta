#ifndef PRIVATE_BRST_ANNOTATION_H
#define PRIVATE_BRST_ANNOTATION_H

extern const char* const BRST_STAMP_ANNOT_NAME_NAMES[];
extern const char* const BRST_ANNOT_TYPE_NAMES[];

BRST_Annotation
BRST_Annotation_New(
    BRST_MMgr      mmgr,
    BRST_Xref      xref,
    BRST_AnnotType type,
    BRST_Rect      rect
);

BRST_Annotation
BRST_WidgetAnnot_New(
    BRST_MMgr mmgr,
    BRST_Xref xref,
    BRST_Rect rect
);

BRST_Annotation
BRST_LinkAnnot_New(
    BRST_MMgr        mmgr,
    BRST_Xref        xref,
    BRST_Rect        rect,
    BRST_Destination dst
);

BRST_Annotation
BRST_URILinkAnnot_New(
    BRST_MMgr   mmgr,
    BRST_Xref   xref,
    BRST_Rect   rect,
    const char* uri
);

BRST_Annotation
BRST_MarkupAnnot_New(
    BRST_MMgr      mmgr,
	BRST_Xref      xref,
	BRST_Rect      rect,
	const char*    text,
	BRST_Encoder   encoder,
	BRST_AnnotType subtype
);

BRST_Annotation
BRST_PopupAnnot_New(
    BRST_MMgr       mmgr,
    BRST_Xref       xref,
    BRST_Rect       rect,
	BRST_Annotation parent
);

BRST_Annotation
BRST_StampAnnot_New(
    BRST_MMgr           mmgr,
    BRST_Xref           xref,
    BRST_Rect           rect,
	BRST_StampAnnotName name,
	const char*	        text,
	BRST_Encoder	    encoder
);

BRST_Annotation
BRST_ProjectionAnnot_New(
    BRST_MMgr    mmgr,
	BRST_Xref    xref,
	BRST_Rect    rect,
	const char*  text,
	BRST_Encoder encoder
);

BRST_BOOL
BRST_Annotation_Validate(
    BRST_Annotation annot
);

#ifdef LIBBRST_U3D_SUPPORT

BRST_Annotation
BRST_3DAnnot_New(
    BRST_MMgr  mmgr,
    BRST_Xref  xref,
    BRST_Rect  rect,
    BRST_BOOL  tb,
    BRST_BOOL  np,
    BRST_U3D   u3d,
    BRST_Image ap
);

#endif /* LIBBRST_U3D_SUPPORT */

#endif /* PRIVATE_BRST_ANNOTATION_H */
