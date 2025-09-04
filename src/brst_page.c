#include "brst_external.h"
#include "brst_types.h"
#include "brst_mmgr.h"
#include "brst_encrypt.h"
#include "brst_stream.h"
#include "brst_dict.h"
#include "brst_xref.h"
#include "private/brst_xref.h"
#include "private/brst_defines.h"
#include "brst_error.h"
#include "brst_consts.h"
#include "brst_ext_gstate.h"
#include "brst_text_defines.h"
#include "brst_font.h"
#include "brst_shading.h"
#include "brst_page.h"
#include "brst_destination.h"
#include "private/brst_page.h"
#include "brst_base.h"
#include "private/brst_pages.h"
#include "brst_transmatrix.h"
#include "private/brst_array.h"
#include "private/brst_number.h"
#include "private/brst_gstate.h"
#include "private/brst_page_attr.h"
#include "private/brst_destination.h"
#include "private/brst_utils.h"

BRST_EXPORT(BRST_MMgr)
BRST_Page_MMgr(BRST_Page page)
{
    BRST_PTRACE(" BRST_Page_MMgr\n");

    return page->mmgr;
}

BRST_EXPORT(BRST_STATUS)
BRST_Page_SetWidth(BRST_Page page,
    BRST_REAL value)
{
    BRST_PTRACE(" BRST_Page_SetWidth\n");

    if (value < BRST_MIN_PAGE_MEASURE || value > BRST_MAX_PAGE_MEASURE)
        return BRST_Error_Raise(page->error, BRST_PAGE_INVALID_SIZE, value);

    if (BRST_Page_SetBoxValue(page, "MediaBox", 2, value) != BRST_OK)
        return BRST_Error_Check(page->error);

    return BRST_OK;
}

BRST_EXPORT(BRST_STATUS)
BRST_Page_SetHeight(BRST_Page page,
    BRST_REAL value)
{
    BRST_PTRACE(" BRST_Page_SetWidth\n");

    if (value < BRST_MIN_PAGE_MEASURE || value > BRST_MAX_PAGE_MEASURE)
        return BRST_Error_Raise(page->error, BRST_PAGE_INVALID_SIZE, value);

    if (BRST_Page_SetBoxValue(page, "MediaBox", 3, value) != BRST_OK)
        return BRST_Error_Check(page->error);

    return BRST_OK;
}

BRST_EXPORT(BRST_STATUS)
BRST_Page_SetBoundary(BRST_Page page,
    BRST_PageBoundary boundary,
    BRST_REAL left,
    BRST_REAL bottom,
    BRST_REAL right,
    BRST_REAL top)
{

    char* key;

    switch (boundary) {
    case BRST_PAGE_MEDIABOX:
        key = "MediaBox";
        break;
    case BRST_PAGE_CROPBOX:
        key = "CropBox";
        break;
    case BRST_PAGE_BLEEDBOX:
        key = "BleedBox";
        break;
    case BRST_PAGE_TRIMBOX:
        key = "TrimBox";
        break;
    case BRST_PAGE_ARTBOX:
        key = "ArtBox";
        break;
    default:
        return BRST_Error_Raise(page->error, BRST_PAGE_INVALID_BOUNDARY, 0);
        break;
    }

    return BRST_Dict_Add(page, key, BRST_Box_Array_New(page->mmgr, BRST_ToBox((BRST_INT16)left, (BRST_INT16)bottom, (BRST_INT16)right, (BRST_INT16)top)));
}

BRST_EXPORT(BRST_STATUS)
BRST_Page_SetSize(BRST_Page page,
    BRST_PageSizes size,
    BRST_PageOrientation orientation)
{
    BRST_STATUS ret = BRST_OK;

    BRST_PTRACE(" BRST_Page_SetSize\n");

    if (!BRST_Page_Validate(page))
        return BRST_INVALID_PAGE;

    if (size < 0 || size > BRST_PAGE_SIZE_EOF)
        return BRST_Error_Raise(page->error, BRST_PAGE_INVALID_SIZE, (BRST_STATUS)size);

    if (orientation == BRST_PAGE_ORIENTATION_LANDSCAPE) {
        ret += BRST_Page_SetHeight(page,
            BRST_PREDEFINED_PAGE_SIZES[(BRST_UINT)size].x);
        ret += BRST_Page_SetWidth(page,
            BRST_PREDEFINED_PAGE_SIZES[(BRST_UINT)size].y);
    } else if (orientation == BRST_PAGE_ORIENTATION_PORTRAIT) {
        ret += BRST_Page_SetHeight(page,
            BRST_PREDEFINED_PAGE_SIZES[(BRST_UINT)size].y);
        ret += BRST_Page_SetWidth(page,
            BRST_PREDEFINED_PAGE_SIZES[(BRST_UINT)size].x);
    } else
        ret = BRST_Error_Set(page->error, BRST_PAGE_INVALID_ORIENTATION,
            (BRST_STATUS)orientation);

    if (ret != BRST_OK)
        return BRST_Error_Check(page->error);

    return BRST_OK;
}

BRST_EXPORT(BRST_STATUS)
BRST_Page_SetRotate(BRST_Page page,
    BRST_UINT16 angle)
{
    BRST_Number n;
    BRST_STATUS ret = BRST_OK;

    BRST_PTRACE(" BRST_Page_SetRotate\n");

    if (!BRST_Page_Validate(page))
        return BRST_INVALID_PAGE;

    if (angle % 90 != 0)
        return BRST_Error_Raise(page->error, BRST_PAGE_INVALID_ROTATE_VALUE,
            (BRST_STATUS)angle);

    n = BRST_Page_InheritableItem(page, "Rotate", BRST_OCLASS_NUMBER);

    if (!n)
        ret = BRST_Dict_AddNumber(page, "Rotate", angle);
    else
        BRST_Number_SetValue(n, angle);

    return ret;
}

/*
 *  This function is contributed by Adrian Nelson (adenelson).
 */
BRST_EXPORT(BRST_STATUS)
BRST_Page_SetSlideShow(BRST_Page page,
    BRST_TransitionStyle type,
    BRST_REAL disp_time,
    BRST_REAL trans_time)
{
    BRST_STATUS ret = BRST_OK;
    BRST_Dict dict;

    BRST_PTRACE(" BRST_Page_SetSlideShow\n");

    if (!BRST_Page_Validate(page))
        return BRST_INVALID_PAGE;

    if (disp_time < 0)
        return BRST_Error_Raise(page->error, BRST_PAGE_INVALID_DISPLAY_TIME,
            (BRST_STATUS)disp_time);

    if (trans_time < 0)
        return BRST_Error_Raise(page->error, BRST_PAGE_INVALID_TRANSITION_TIME,
            (BRST_STATUS)trans_time);

    dict = BRST_Dict_New(page->mmgr);

    if (!dict)
        return BRST_Error_Code(page->error);

    if (BRST_Dict_AddName(dict, "Type", "Trans") != BRST_OK)
        goto Fail;

    if (BRST_Dict_AddReal(dict, "D", trans_time) != BRST_OK)
        goto Fail;

    switch (type) {
    case BRST_PAGE_TRANSITION_WIPE_RIGHT:
        ret += BRST_Dict_AddName(dict, "S", "Wipe");
        ret += BRST_Dict_AddNumber(dict, "Di", 0);
        break;
    case BRST_PAGE_TRANSITION_WIPE_UP:
        ret += BRST_Dict_AddName(dict, "S", "Wipe");
        ret += BRST_Dict_AddNumber(dict, "Di", 90);
        break;
    case BRST_PAGE_TRANSITION_WIPE_LEFT:
        ret += BRST_Dict_AddName(dict, "S", "Wipe");
        ret += BRST_Dict_AddNumber(dict, "Di", 180);
        break;
    case BRST_PAGE_TRANSITION_WIPE_DOWN:
        ret += BRST_Dict_AddName(dict, "S", "Wipe");
        ret += BRST_Dict_AddNumber(dict, "Di", 270);
        break;
    case BRST_PAGE_TRANSITION_BARN_DOORS_HORIZONTAL_OUT:
        ret += BRST_Dict_AddName(dict, "S", "Split");
        ret += BRST_Dict_AddName(dict, "Dm", "H");
        ret += BRST_Dict_AddName(dict, "M", "O");
        break;
    case BRST_PAGE_TRANSITION_BARN_DOORS_HORIZONTAL_IN:
        ret += BRST_Dict_AddName(dict, "S", "Split");
        ret += BRST_Dict_AddName(dict, "Dm", "H");
        ret += BRST_Dict_AddName(dict, "M", "I");
        break;
    case BRST_PAGE_TRANSITION_BARN_DOORS_VERTICAL_OUT:
        ret += BRST_Dict_AddName(dict, "S", "Split");
        ret += BRST_Dict_AddName(dict, "Dm", "V");
        ret += BRST_Dict_AddName(dict, "M", "O");
        break;
    case BRST_PAGE_TRANSITION_BARN_DOORS_VERTICAL_IN:
        ret += BRST_Dict_AddName(dict, "S", "Split");
        ret += BRST_Dict_AddName(dict, "Dm", "V");
        ret += BRST_Dict_AddName(dict, "M", "I");
        break;
    case BRST_PAGE_TRANSITION_BOX_OUT:
        ret += BRST_Dict_AddName(dict, "S", "Box");
        ret += BRST_Dict_AddName(dict, "M", "O");
        break;
    case BRST_PAGE_TRANSITION_BOX_IN:
        ret += BRST_Dict_AddName(dict, "S", "Box");
        ret += BRST_Dict_AddName(dict, "M", "I");
        break;
    case BRST_PAGE_TRANSITION_BLINDS_HORIZONTAL:
        ret += BRST_Dict_AddName(dict, "S", "Blinds");
        ret += BRST_Dict_AddName(dict, "Dm", "H");
        break;
    case BRST_PAGE_TRANSITION_BLINDS_VERTICAL:
        ret += BRST_Dict_AddName(dict, "S", "Blinds");
        ret += BRST_Dict_AddName(dict, "Dm", "V");
        break;
    case BRST_PAGE_TRANSITION_DISSOLVE:
        ret += BRST_Dict_AddName(dict, "S", "Dissolve");
        break;
    case BRST_PAGE_TRANSITION_GLITTER_RIGHT:
        ret += BRST_Dict_AddName(dict, "S", "Glitter");
        ret += BRST_Dict_AddNumber(dict, "Di", 0);
        break;
    case BRST_PAGE_TRANSITION_GLITTER_DOWN:
        ret += BRST_Dict_AddName(dict, "S", "Glitter");
        ret += BRST_Dict_AddNumber(dict, "Di", 270);
        break;
    case BRST_PAGE_TRANSITION_GLITTER_TOP_LEFT_TO_BOTTOM_RIGHT:
        ret += BRST_Dict_AddName(dict, "S", "Glitter");
        ret += BRST_Dict_AddNumber(dict, "Di", 315);
        break;
    case BRST_PAGE_TRANSITION_REPLACE:
        ret += BRST_Dict_AddName(dict, "S", "R");
        break;
    default:
        ret += BRST_Error_Set(page->error, BRST_INVALID_PAGE_SLIDESHOW_TYPE, 0);
    }

    if (ret != BRST_OK)
        goto Fail;

    if (BRST_Dict_AddReal(page, "Dur", disp_time) != BRST_OK)
        goto Fail;

    if ((ret = BRST_Dict_Add(page, "Trans", dict)) != BRST_OK)
        return ret;

    return BRST_OK;

Fail:
    BRST_Dict_Free(dict);
    return BRST_Error_Code(page->error);
}

/* Tz */
BRST_EXPORT(BRST_STATUS)
BRST_Page_SetHorizontalScaling(BRST_Page page,
    BRST_REAL value)
{
    BRST_STATUS ret = BRST_Page_CheckState(page, BRST_GMODE_PAGE_DESCRIPTION | BRST_GMODE_TEXT_OBJECT);
    BRST_PageAttr attr;

    BRST_PTRACE(" BRST_Page_SetHorizontalScaling\n");

    if (ret != BRST_OK)
        return ret;

    attr = (BRST_PageAttr)page->attr;

    if (value < BRST_MIN_HORIZONTAL_SCALING || value > BRST_MAX_HORIZONTAL_SCALING)
        return BRST_Error_Raise(page->error, BRST_PAGE_OUT_OF_RANGE, 0);

    if (BRST_Stream_WriteReal(attr->stream, value) != BRST_OK)
        return BRST_Error_Check(page->error);

    if (BRST_Stream_WriteStr(attr->stream, " Tz\012") != BRST_OK)
        return BRST_Error_Check(page->error);

    attr->gstate->h_scaling = value;

    return ret;
}

BRST_EXPORT(BRST_REAL)
BRST_Page_HorizontalScaling(BRST_Page page)
{
    BRST_PTRACE(" BRST_Page_HorizontalScaling\n");

    if (BRST_Page_Validate(page)) {
        BRST_PageAttr attr = (BRST_PageAttr)page->attr;

        return attr->gstate->h_scaling;
    } else
        return BRST_DEF_HSCALING;
}

BRST_EXPORT(BRST_UINT)
BRST_Page_GStateDepth(BRST_Page page)
{
    BRST_PTRACE(" BRST_Page_GStateDepth\n");

    if (BRST_Page_Validate(page)) {
        BRST_PageAttr attr = (BRST_PageAttr)page->attr;

        return attr->gstate->depth;
    } else
        return 0;
}

BRST_EXPORT(BRST_STATUS)
BRST_Page_SetZoom(BRST_Page page,
    BRST_REAL zoom)
{
    BRST_STATUS ret = BRST_OK;

    BRST_PTRACE(" BRST_Page_SetZoom\n");

    if (!BRST_Page_Validate(page)) {
        return BRST_INVALID_PAGE;
    }

    if (zoom < BRST_MIN_MAGNIFICATION_FACTOR || zoom > BRST_MAX_MAGNIFICATION_FACTOR) {
        return BRST_Error_Raise(page->error, BRST_INVALID_PARAMETER, 0);
    }

    ret = BRST_Dict_AddReal(page, "PZ", zoom);
    return ret;
}

BRST_EXPORT(BRST_REAL)
BRST_Page_Width(BRST_Page page)
{
    return BRST_Page_MediaBox(page).right;
}

BRST_EXPORT(BRST_REAL)
BRST_Page_Height(BRST_Page page)
{
    return BRST_Page_MediaBox(page).top;
}

BRST_EXPORT(BRST_UINT16)
BRST_Page_GMode(BRST_Page page)
{
    if (BRST_Page_Validate(page))
        return ((BRST_PageAttr)page->attr)->gmode;

    return 0;
}

BRST_EXPORT(BRST_Point)
BRST_Page_CurrentPos(BRST_Page page)
{
    BRST_Point pos = { 0, 0 };

    BRST_PTRACE(" BRST_Page_CurrentPos\n");

    if (BRST_Page_Validate(page)) {
        BRST_PageAttr attr = (BRST_PageAttr)page->attr;

        if (attr->gmode & BRST_GMODE_PATH_OBJECT)
            pos = attr->cur_pos;
    }

    return pos;
}

BRST_EXPORT(BRST_STATUS)
BRST_Page_CurrentPos2(BRST_Page page,
    BRST_Point* pos)
{
    BRST_PageAttr attr;
    BRST_PTRACE(" BRST_Page_CurrentPos2\n");

    pos->x = 0;
    pos->y = 0;
    if (!BRST_Page_Validate(page))
        return BRST_INVALID_PAGE;

    attr = (BRST_PageAttr)page->attr;

    if (attr->gmode & BRST_GMODE_PATH_OBJECT)
        *pos = attr->cur_pos;

    return BRST_OK;
}

/*
 *  This function is contributed by Finn Arildsen.
 */

BRST_EXPORT(BRST_STATUS)
BRST_Page_New_Content_Stream(BRST_Page page,
    BRST_Dict* new_stream)
{
    /* Call this function to start a new content stream on a page. The
       handle is returned to new_stream.
       new_stream can later be used on other pages as a shared content stream;
       insert using BRST_Page_Insert_Shared_Content_Stream */

    BRST_STATUS ret = BRST_Page_CheckState(page, BRST_GMODE_PAGE_DESCRIPTION | BRST_GMODE_TEXT_OBJECT);
    BRST_PageAttr attr;
    BRST_UINT filter;
    BRST_Array contents_array;

    BRST_PTRACE(" BRST_Page_New_Content_Stream\n");

    attr   = (BRST_PageAttr)page->attr;
    filter = attr->contents->filter;

    /* check if there is already an array of contents */
    contents_array = (BRST_Array)BRST_Dict_Item(page, "Contents", BRST_OCLASS_ARRAY);
    if (!contents_array) {
        BRST_Error_Reset(page->error);
        /* no contents_array already -- create one
           and replace current single contents item */
        contents_array = BRST_Array_New(page->mmgr);
        if (!contents_array)
            return BRST_Error_Code(page->error);
        ret += BRST_Array_Add(contents_array, attr->contents);
        ret += BRST_Dict_Add(page, "Contents", contents_array);
    }

    /* create new contents stream and add it to the page's contents array */
    attr->contents         = BRST_Dict_New_Stream_Init(page->mmgr, attr->xref);
    attr->contents->filter = filter;
    attr->stream           = attr->contents->stream;

    if (!attr->contents)
        return BRST_Error_Code(page->error);

    ret += BRST_Array_Add(contents_array, attr->contents);

    /* return the value of the new stream, so that
       the application can use it as a shared contents stream */
    if (ret == BRST_OK && new_stream != NULL)
        *new_stream = attr->contents;

    return ret;
}

/*
 *  This function is contributed by Finn Arildsen.
 */

BRST_EXPORT(BRST_STATUS)
BRST_Page_Insert_Shared_Content_Stream(BRST_Page page,
    BRST_Dict shared_stream)
{
    /* Call this function to insert a previously (with BRST_New_Content_Stream) created content stream
       as a shared content stream on this page */

    BRST_STATUS ret = BRST_Page_CheckState(page, BRST_GMODE_PAGE_DESCRIPTION | BRST_GMODE_TEXT_OBJECT);
    BRST_Array contents_array;

    BRST_PTRACE(" BRST_Page_Insert_Shared_Content_Stream\n");

    /* check if there is already an array of contents */
    contents_array = (BRST_Array)BRST_Dict_Item(page, "Contents", BRST_OCLASS_ARRAY);
    if (!contents_array) {
        BRST_PageAttr attr;
        BRST_Error_Reset(page->error);
        /* no contents_array already -- create one
           and replace current single contents item */
        contents_array = BRST_Array_New(page->mmgr);
        if (!contents_array)
            return BRST_Error_Code(page->error);
        attr = (BRST_PageAttr)page->attr;
        ret += BRST_Array_Add(contents_array, attr->contents);
        ret += BRST_Dict_Add(page, "Contents", contents_array);
    }

    ret += BRST_Array_Add(contents_array, shared_stream);

    /* Continue with a new stream */
    ret += BRST_Page_New_Content_Stream(page, NULL);

    return ret;
}

BRST_EXPORT(BRST_STATUS)
BRST_Page_RawWrite(BRST_Page page,
    BRST_CSTR data)
{
    if (!BRST_Page_Validate(page))
        return BRST_INVALID_PAGE;

    BRST_PTRACE(" BRST_Page_RawWrite\n");

    BRST_PageAttr attr = (BRST_PageAttr)page->attr;
    BRST_Stream_WriteStr(attr->stream, data);

    return BRST_OK;
}

/* gs */
BRST_EXPORT(BRST_STATUS)
BRST_Page_SetExtGState(BRST_Page page,
    BRST_ExtGState ext_gstate)
{
    BRST_STATUS ret = BRST_Page_CheckState(page, BRST_GMODE_PAGE_DESCRIPTION);
    BRST_PageAttr attr;
    const char* local_name;

    BRST_PTRACE(" BRST_Page_SetExtGState\n");

    if (ret != BRST_OK)
        return ret;

    if (!BRST_ExtGState_Validate(ext_gstate))
        return BRST_Error_Raise(page->error, BRST_INVALID_OBJECT, 0);

    if (page->mmgr != ext_gstate->mmgr)
        return BRST_Error_Raise(page->error, BRST_INVALID_EXT_GSTATE, 0);

    attr       = (BRST_PageAttr)page->attr;
    local_name = BRST_Page_ExtGStateName(page, ext_gstate);

    if (!local_name)
        return BRST_Error_Check(page->error);

    if (BRST_Stream_WriteEscapeName(attr->stream, local_name) != BRST_OK)
        return BRST_Error_Check(page->error);

    if (BRST_Stream_WriteStr(attr->stream, " gs\012") != BRST_OK)
        return BRST_Error_Check(page->error);

    /* change objct class to read only. */
    ext_gstate->header.obj_class = (BRST_OSUBCLASS_EXT_GSTATE_R | BRST_OCLASS_DICT);

    return ret;
}

BRST_EXPORT(BRST_Destination)
BRST_Page_CreateDestination(BRST_Page page)
{
    BRST_PageAttr attr;
    BRST_Destination dst;

    BRST_PTRACE(" BRST_Page_CreateDestination\n");

    if (!BRST_Page_Validate(page))
        return NULL;

    attr = (BRST_PageAttr)page->attr;

    dst = BRST_Destination_New(page->mmgr, page, attr->xref);
    if (!dst)
        BRST_Error_Check(page->error);

    return dst;
}
