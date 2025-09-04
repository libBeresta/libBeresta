#include "brst_types.h"
#include "brst_mmgr.h"
#include "brst_stream.h"
#include "brst_encrypt.h"
#include "brst_encoder.h"
#include "brst_xref.h"
#include "brst_dict.h"
#include "private/brst_dict.h"
#include "brst_annotation.h"
#include "private/brst_xref.h"
#include "brst_array.h"
#include "private/brst_array.h"
#include "private/brst_string.h"
#include "brst_consts.h"
#include "private/brst_name.h"
#include "brst_error.h"
#include "private/brst_utils.h"
#include "brst_destination.h"
#include "brst_transmatrix.h"

const char* const BRST_STAMP_ANNOT_NAME_NAMES[] = {
    "Approved",
    "Experimental",
    "NotApproved",
    "AsIs",
    "Expired",
    "NotForPublicRelease",
    "Confidential",
    "Final",
    "Sold",
    "Departmental",
    "ForComment",
    "TopSecret",
    "Draft",
    "ForPublicRelease"
};

/*
BRST_3DAnnot_New
*/

const char* const BRST_ANNOT_TYPE_NAMES[] = {
    "Text",
    "Link",
    "Sound",
    "FreeText",
    "Stamp",
    "Square",
    "Circle",
    "StrikeOut",
    "Highlight",
    "Underline",
    "Ink",
    "FileAttachment",
    "Popup",
    "3D",
    "Squiggly",
    "Line",
    "Projection",
    "Widget"
};

BRST_Annotation
BRST_Annotation_New(BRST_MMgr mmgr,
    BRST_Xref xref,
    BRST_AnnotType type,
    BRST_Rect rect)
{
    BRST_Annotation annot;
    BRST_Array array;
    BRST_STATUS ret = BRST_OK;
    BRST_REAL tmp;

    BRST_PTRACE(" BRST_Annotation_New\n");

    annot = BRST_Dict_New(mmgr);
    if (!annot)
        return NULL;

    if (BRST_Xref_Add(xref, annot) != BRST_OK)
        return NULL;

    array = BRST_Array_New(mmgr);
    if (!array)
        return NULL;

    if (BRST_Dict_Add(annot, "Rect", array) != BRST_OK)
        return NULL;

    if (rect.top < rect.bottom) {
        tmp         = rect.top;
        rect.top    = rect.bottom;
        rect.bottom = tmp;
    }

    ret += BRST_Array_AddReal(array, rect.left);
    ret += BRST_Array_AddReal(array, rect.bottom);
    ret += BRST_Array_AddReal(array, rect.right);
    ret += BRST_Array_AddReal(array, rect.top);

    ret += BRST_Dict_AddName(annot, "Type", "Annot");
    ret += BRST_Dict_AddName(annot, "Subtype",
        BRST_ANNOT_TYPE_NAMES[(BRST_INT)type]);

    if (ret != BRST_OK)
        return NULL;

    annot->header.obj_class |= BRST_OSUBCLASS_ANNOTATION;

    return annot;
}

BRST_Annotation
BRST_WidgetAnnot_New(BRST_MMgr mmgr,
    BRST_Xref xref,
    BRST_Rect rect)
{
    BRST_Annotation annot;

    BRST_PTRACE(" BRST_WidgetAnnot_New\n");

    annot = BRST_Annotation_New(mmgr, xref, BRST_ANNOT_WIDGET, rect);
    if (!annot)
        return NULL;

    return annot;
}

BRST_Annotation
BRST_LinkAnnot_New(BRST_MMgr mmgr,
    BRST_Xref xref,
    BRST_Rect rect,
    BRST_Destination dst)
{
    BRST_Annotation annot;

    BRST_PTRACE(" BRST_LinkAnnot_New\n");

    annot = BRST_Annotation_New(mmgr, xref, BRST_ANNOT_LINK, rect);
    if (!annot)
        return NULL;

    if (dst) {
        if (BRST_Dict_Add(annot, "Dest", dst) != BRST_OK)
            return NULL;
    }

    return annot;
}

BRST_Annotation
BRST_URILinkAnnot_New(BRST_MMgr mmgr,
    BRST_Xref xref,
    BRST_Rect rect,
    const char* uri)
{
    BRST_Annotation annot;
    BRST_Dict action;
    BRST_STATUS ret;

    BRST_PTRACE(" BRST_URILinkAnnot_New\n");

    annot = BRST_Annotation_New(mmgr, xref, BRST_ANNOT_LINK, rect);
    if (!annot)
        return NULL;

    /* create action dictionary */
    action = BRST_Dict_New(mmgr);
    if (!action)
        return NULL;

    ret = BRST_Dict_Add(annot, "A", action);
    if (ret != BRST_OK)
        return NULL;

    ret += BRST_Dict_AddName(action, "Type", "Action");
    ret += BRST_Dict_AddName(action, "S", "URI");
    ret += BRST_Dict_Add(action, "URI", BRST_String_New(mmgr, uri, NULL));

    if (ret != BRST_OK)
        return NULL;

    return annot;
}

BRST_Annotation
BRST_MarkupAnnot_New(BRST_MMgr mmgr,
    BRST_Xref xref,
    BRST_Rect rect,
    const char* text,
    BRST_Encoder encoder,
    BRST_AnnotType subtype)
{
    BRST_Annotation annot;
    BRST_String s;

    BRST_PTRACE(" BRST_MarkupAnnot_New\n");

    annot = BRST_Annotation_New(mmgr, xref, subtype, rect);
    if (!annot)
        return NULL;

    s = BRST_String_New(mmgr, text, encoder);
    if (!s)
        return NULL;

    if (BRST_Dict_Add(annot, "Contents", s) != BRST_OK)
        return NULL;

    return annot;
}

BRST_Annotation
BRST_PopupAnnot_New(BRST_MMgr mmgr,
    BRST_Xref xref,
    BRST_Rect rect,
    BRST_Annotation parent)
{
    BRST_Annotation annot;

    BRST_PTRACE(" BRST_PopupAnnot_New\n");

    annot = BRST_Annotation_New(mmgr, xref, BRST_ANNOT_POPUP, rect);
    if (!annot)
        return NULL;

    if (BRST_Dict_Add(annot, "Parent", parent) != BRST_OK)
        return NULL;

    return annot;
}

BRST_Annotation
BRST_StampAnnot_New(BRST_MMgr mmgr,
    BRST_Xref xref,
    BRST_Rect rect,
    BRST_StampAnnotName name,
    const char* text,
    BRST_Encoder encoder)
{
    BRST_Annotation annot;
    BRST_String s;
    BRST_PTRACE(" BRST_StampAnnot_New\n");

    annot = BRST_Annotation_New(mmgr, xref, BRST_ANNOT_STAMP, rect);
    if (!annot)
        return NULL;

    if (BRST_Dict_AddName(annot, "Name", BRST_STAMP_ANNOT_NAME_NAMES[name]) != BRST_OK)
        return NULL;

    s = BRST_String_New(mmgr, text, encoder);
    if (!s)
        return NULL;

    if (BRST_Dict_Add(annot, "Contents", s) != BRST_OK)
        return NULL;

    return annot;
}

BRST_Annotation
BRST_ProjectionAnnot_New(BRST_MMgr mmgr,
    BRST_Xref xref,
    BRST_Rect rect,
    const char* text,
    BRST_Encoder encoder)
{
    BRST_Annotation annot;
    BRST_String s;
    BRST_PTRACE(" BRST_StampAnnot_New\n");
    annot = BRST_Annotation_New(mmgr, xref, BRST_ANNOT_PROJECTION, rect);

    if (!annot)
        return NULL;

    s = BRST_String_New(mmgr, text, encoder);
    if (!s)
        return NULL;

    if (BRST_Dict_Add(annot, "Contents", s) != BRST_OK)
        return NULL;

    return annot;
}

BRST_BOOL
BRST_Annotation_Validate(BRST_Annotation annot)
{
    BRST_PTRACE(" BRST_Annotation_Validate\n");

    if (!annot)
        return BRST_FALSE;

    if (annot->header.obj_class != (BRST_OSUBCLASS_ANNOTATION | BRST_OCLASS_DICT))
        return BRST_FALSE;

    return BRST_TRUE;
}

#ifdef LIBBRST_U3D_SUPPORT

BRST_Annotation
BRST_3DAnnot_New(BRST_MMgr mmgr,
    BRST_Xref xref,
    BRST_Rect rect,
    BRST_BOOL tb,
    BRST_BOOL np,
    BRST_U3D u3d,
    BRST_Image ap)
{
    BRST_Annotation annot;
    BRST_Dict action, appearance, stream;
    BRST_STATUS ret;

    BRST_PTRACE(" BRST_3DAnnot_New\n");

    annot = BRST_Annotation_New(mmgr, xref, BRST_ANNOT_3D, rect);
    if (!annot) {
        return NULL;
    }

    // include the flags
    BRST_Dict_AddNumber(annot, "F", 68);
    // Bit 3:Print If set, print the annotation when the page is printed.
    // Bit 7:If set, do not allow the annotation to interact with the user.
    //       The annotation may be displayed or printed (depending on the settings of the NoView and Print flags)
    //       but should not respond to mouse clicks or change its appearance in response to mouse motions.

    BRST_Dict_Add(annot, "Contents", BRST_String_New(mmgr, "3D Model", NULL));

    action = BRST_Dict_New(mmgr);
    if (!action) {
        return NULL;
    }

    ret = BRST_Dict_Add(annot, "3DA", action);
    if (ret != BRST_OK) {
        return NULL;
    }

    // enable visibility on page open
    ret += BRST_Dict_AddName(action, "A", "PO");

    // enable visibility of ToolBar
    ret += BRST_Dict_AddBoolean(action, "TB", tb);

    // enable visibility of Navigation Panel
    ret += BRST_Dict_AddBoolean(action, "NP", np);

    // Set behavior of Annotation on Disabling
    ret += BRST_Dict_AddName(action, "DIS", "U");

    // Set behavior of Annotation upon activation
    ret += BRST_Dict_AddName(action, "AIS", "L");

    if (ret != BRST_OK) {
        return NULL;
    }

    if (BRST_Dict_Add(annot, "3DD", u3d) != BRST_OK) {
        return NULL;
    }

    appearance = BRST_Dict_New(mmgr);
    if (!appearance) {
        return NULL;
    }

    ret = BRST_Dict_Add(annot, "AP", appearance);
    if (ret != BRST_OK) {
        return NULL;
    }

    if (ap) {
        if (BRST_Dict_Add(appearance, "N", ap) != BRST_OK)
            return NULL;
    } else {
        stream = BRST_Dict_New(mmgr);
        if (!stream) {
            return NULL;
        }
        ret = BRST_Dict_Add(appearance, "N", stream);
    }

    if (ret != BRST_OK) {
        return NULL;
    }

    return annot;
}

#endif /* LIBBRST_U3D_SUPPORT */
