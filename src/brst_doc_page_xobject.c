#include "brst_external.h"
#include "brst_types.h"
#include "brst_mmgr.h"
#include "brst_encrypt.h"
#include "brst_stream.h"
#include "private/brst_stream.h"
#include "brst_dict.h"
#include "private/brst_dict.h"
#include "brst_xref.h"
#include "brst_encoder.h"
#include "private/brst_encoder.h"
#include "brst_error.h"
#include "brst_consts.h"
#include "brst_ext_gstate.h"
#include "brst_font.h"
#include "brst_shading.h"
#include "brst_doc.h"
#include "brst_pdfa.h"
#include "brst_page.h"
#include "brst_destination.h"
#include "private/brst_catalog.h"
#include "brst_outline.h"
#include "private/brst_encrypt_dict.h"
#include "private/brst_doc.h"
#include "private/brst_page.h"
#include "brst_base.h"
#include "brst_image.h"
#include "private/brst_gstate.h"
#include "private/brst_page_attr.h"
#include "private/brst_array.h"
#include "private/brst_name.h"
#include "brst_doc_page_xobject.h"

BRST_EXPORT(BRST_XObject)
BRST_Doc_Page_XObject_CreateFromImage(BRST_Doc pdf,
    BRST_Page page,
    BRST_Rect rect,
    BRST_Image image,
    BRST_BOOL zoom)
{
    BRST_Dict resource;
    BRST_Dict fromxobject;
    BRST_Dict xobject;
    BRST_STATUS ret;
    BRST_Array procset;
    BRST_REAL tmp;
    BRST_Array array1;
    BRST_Array array2;

    BRST_PTRACE((" BRST_Doc_Page_XObject_CreateFromImage\n"));

    fromxobject = BRST_DictStream_New(pdf->mmgr, pdf->xref);
    if (!fromxobject)
        return NULL;

    fromxobject->header.obj_class |= BRST_OSUBCLASS_XOBJECT;

    /* add required elements */
    fromxobject->filter = BRST_STREAM_FILTER_FLATE_DECODE;

    resource = BRST_Dict_New(page->mmgr);
    if (!resource)
        return NULL;

    /* Although ProcSet entry is obsolete, add it to resource
     * for compatibility.
     */

    ret = BRST_Dict_Add(fromxobject, "Resources", resource);

    procset = BRST_Array_New(page->mmgr);
    if (!procset)
        return NULL;

    ret += BRST_Dict_Add(resource, "ProcSet", procset);
    ret += BRST_Array_Add(procset, BRST_Name_New(page->mmgr, "PDF"));
    ret += BRST_Array_Add(procset, BRST_Name_New(page->mmgr, "ImageC"));

    if (ret != BRST_OK)
        return NULL;

    xobject = BRST_Dict_New(page->mmgr);
    if (!xobject)
        return NULL;

    if (BRST_Dict_Add(resource, "XObject", xobject) != BRST_OK)
        return NULL;

    if (BRST_Dict_Add(xobject, "Im1", image) != BRST_OK)
        return NULL;

    array1 = BRST_Array_New(page->mmgr);
    if (!array1)
        return NULL;

    if (BRST_Dict_Add(fromxobject, "BBox", array1) != BRST_OK)
        return NULL;

    if (rect.top < rect.bottom) {
        tmp         = rect.top;
        rect.top    = rect.bottom;
        rect.bottom = tmp;
    }

    ret += BRST_Array_AddReal(array1, rect.left);
    ret += BRST_Array_AddReal(array1, rect.bottom);
    ret += BRST_Array_AddReal(array1, rect.right);
    ret += BRST_Array_AddReal(array1, rect.top);

    array2 = BRST_Array_New(page->mmgr);
    if (!array2)
        return NULL;

    if (BRST_Dict_Add(fromxobject, "Matrix", array2) != BRST_OK)
        return NULL;

    ret += BRST_Array_AddReal(array2, 1.0);
    ret += BRST_Array_AddReal(array2, 0.0);
    ret += BRST_Array_AddReal(array2, 0.0);
    ret += BRST_Array_AddReal(array2, 1.0);
    ret += BRST_Array_AddReal(array2, 0.0);
    ret += BRST_Array_AddReal(array2, 0.0);

    if (BRST_Dict_AddNumber(fromxobject, "FormType", 1) != BRST_OK)
        return NULL;

    if (BRST_Dict_AddName(fromxobject, "Subtype", "Form") != BRST_OK)
        return NULL;

    if (BRST_Dict_AddName(fromxobject, "Type", "XObject") != BRST_OK)
        return NULL;

    if (BRST_Stream_WriteStr(fromxobject->stream, "q") != BRST_OK)
        return NULL;
    if (BRST_Stream_WriteChar(fromxobject->stream, 0x0A) != BRST_OK)
        return NULL;

    if (zoom) {
        if (BRST_Stream_WriteReal(fromxobject->stream, rect.right - rect.left) != BRST_OK)
            return NULL;
        if (BRST_Stream_WriteStr(fromxobject->stream, " 0 0 ") != BRST_OK)
            return NULL;
        if (BRST_Stream_WriteReal(fromxobject->stream, rect.top - rect.bottom) != BRST_OK)
            return NULL;
        if (BRST_Stream_WriteStr(fromxobject->stream, " 0 0 cm") != BRST_OK)
            return NULL;
    } else {
        if (BRST_Stream_WriteStr(fromxobject->stream, "1.0 0 0 1.0 0 0 cm") != BRST_OK)
            return NULL;
    }

    if (BRST_Stream_WriteChar(fromxobject->stream, 0x0A) != BRST_OK)
        return NULL;
    if (BRST_Stream_WriteStr(fromxobject->stream, "/Im1 Do") != BRST_OK)
        return NULL;
    if (BRST_Stream_WriteChar(fromxobject->stream, 0x0A) != BRST_OK)
        return NULL;
    if (BRST_Stream_WriteStr(fromxobject->stream, "Q") != BRST_OK)
        return NULL;

    return fromxobject;
}

BRST_EXPORT(BRST_XObject)
BRST_Doc_Page_XObject_CreateAsWhiteRect(BRST_Doc pdf,
    BRST_Page page,
    BRST_Rect rect)
{

    BRST_Dict resource;
    BRST_Dict fromxobject;
    BRST_Dict xobject;
    BRST_STATUS ret;
    BRST_Array procset;
    BRST_REAL tmp;
    BRST_Array array1;
    BRST_Array array2;

    BRST_PTRACE((" BRST_Doc_Page_XObject_CreateAsWhiteRect\n"));

    fromxobject = BRST_DictStream_New(pdf->mmgr, pdf->xref);
    if (!fromxobject)
        return NULL;

    fromxobject->header.obj_class |= BRST_OSUBCLASS_XOBJECT;

    /* add required elements */
    fromxobject->filter = BRST_STREAM_FILTER_FLATE_DECODE;

    resource = BRST_Dict_New(page->mmgr);
    if (!resource)
        return NULL;

    /* Although ProcSet entry is obsolete, add it to resource
     * for compatibility
     */

    ret = BRST_Dict_Add(fromxobject, "Resources", resource);

    procset = BRST_Array_New(page->mmgr);
    if (!procset)
        return NULL;

    ret += BRST_Dict_Add(resource, "ProcSet", procset);
    ret += BRST_Array_Add(procset, BRST_Name_New(page->mmgr, "PDF"));
    ret += BRST_Array_Add(procset, BRST_Name_New(page->mmgr, "ImageC"));

    if (ret != BRST_OK)
        return NULL;

    xobject = BRST_Dict_New(page->mmgr);
    if (!xobject)
        return NULL;

    if (BRST_Dict_Add(resource, "XObject", xobject) != BRST_OK)
        return NULL;

    array1 = BRST_Array_New(page->mmgr);
    if (!array1)
        return NULL;

    if (BRST_Dict_Add(fromxobject, "BBox", array1) != BRST_OK)
        return NULL;

    if (rect.top < rect.bottom) {
        tmp         = rect.top;
        rect.top    = rect.bottom;
        rect.bottom = tmp;
    }

    ret += BRST_Array_AddReal(array1, 0.0);
    ret += BRST_Array_AddReal(array1, 0.0);
    ret += BRST_Array_AddReal(array1, rect.right - rect.left);
    ret += BRST_Array_AddReal(array1, rect.top - rect.bottom);

    array2 = BRST_Array_New(page->mmgr);
    if (!array2)
        return NULL;

    if (BRST_Dict_Add(fromxobject, "Matrix", array2) != BRST_OK)
        return NULL;

    ret += BRST_Array_AddReal(array2, 1.0);
    ret += BRST_Array_AddReal(array2, 0.0);
    ret += BRST_Array_AddReal(array2, 0.0);
    ret += BRST_Array_AddReal(array2, 1.0);
    ret += BRST_Array_AddReal(array2, 0.0);
    ret += BRST_Array_AddReal(array2, 0.0);

    if (BRST_Dict_AddNumber(fromxobject, "FormType", 1) != BRST_OK)
        return NULL;

    if (BRST_Dict_AddName(fromxobject, "Subtype", "Form") != BRST_OK)
        return NULL;

    if (BRST_Dict_AddName(fromxobject, "Type", "XObject") != BRST_OK)
        return NULL;

    if (BRST_Stream_WriteStr(fromxobject->stream, "1 g") != BRST_OK)
        return NULL;
    if (BRST_Stream_WriteChar(fromxobject->stream, 0x0A) != BRST_OK)
        return NULL;
    if (BRST_Stream_WriteStr(fromxobject->stream, "0 0 ") != BRST_OK)
        return NULL;

    if (BRST_Stream_WriteReal(fromxobject->stream, rect.right - rect.left) != BRST_OK)
        return NULL;
    if (BRST_Stream_WriteStr(fromxobject->stream, " ") != BRST_OK)
        return NULL;
    if (BRST_Stream_WriteReal(fromxobject->stream, rect.top - rect.bottom) != BRST_OK)
        return NULL;
    if (BRST_Stream_WriteStr(fromxobject->stream, " re") != BRST_OK)
        return NULL;

    if (BRST_Stream_WriteChar(fromxobject->stream, 0x0A) != BRST_OK)
        return NULL;
    if (BRST_Stream_WriteStr(fromxobject->stream, "f") != BRST_OK)
        return NULL;

    return fromxobject;
}
