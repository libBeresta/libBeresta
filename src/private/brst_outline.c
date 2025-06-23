#include "brst_types.h"
#include "brst_encrypt.h"
#include "brst_encoder.h"
#include "brst_stream.h"
#include "brst_mmgr.h"
#include "brst_dict.h"
#include "private/brst_dict.h"
#include "brst_xref.h"
#include "private/brst_xref.h"
#include "private/brst_number.h"
#include "private/brst_string.h"
#include "brst_outline.h"
#include "private/brst_utils.h"
#include "brst_consts.h"

static BRST_STATUS
AddChild(BRST_Outline parent,
    BRST_Outline item);

static BRST_STATUS
BeforeWrite(BRST_Dict obj);

static BRST_UINT
CountChild(BRST_Outline outline);

/*----------------------------------------------------------------------------*/
/*----- BRST_Outline ---------------------------------------------------------*/

BRST_Outline
BRST_OutlineRoot_New(BRST_MMgr mmgr,
    BRST_Xref xref)
{
    BRST_Outline outline;
    BRST_STATUS ret = BRST_OK;
    BRST_Number open_flg;

    BRST_PTRACE((" BRST_OutlineRoot_New\n"));

    outline = BRST_Dict_New(mmgr);
    if (!outline)
        return NULL;

    outline->before_write_fn = BeforeWrite;

    if (BRST_Xref_Add(xref, outline) != BRST_OK)
        return NULL;

    open_flg = BRST_Number_New(mmgr, BRST_OUTLINE_OPENED);
    if (!open_flg)
        return NULL;

    BRST_Obj_SetID(open_flg, BRST_Obj_ID(open_flg) | BRST_OTYPE_HIDDEN);

    ret += BRST_Dict_Add(outline, "_OPENED", open_flg);
    ret += BRST_Dict_AddName(outline, "Type", "Outlines");

    if (ret != BRST_OK)
        return NULL;

    outline->header.obj_class |= BRST_OSUBCLASS_OUTLINE;

    return outline;
}

BRST_Outline
BRST_Outline_New(BRST_MMgr mmgr,
    BRST_Outline parent,
    const char* title,
    BRST_Encoder encoder,
    BRST_Xref xref)
{
    BRST_Outline outline;
    BRST_String s;
    BRST_STATUS ret = BRST_OK;
    BRST_Number open_flg;

    BRST_PTRACE((" BRST_Outline_New\n"));

    if (!mmgr || !parent || !xref)
        return NULL;

    outline = BRST_Dict_New(mmgr);
    if (!outline)
        return NULL;

    outline->before_write_fn = BeforeWrite;

    if (BRST_Xref_Add(xref, outline) != BRST_OK)
        return NULL;

    s = BRST_String_New(mmgr, title, encoder);
    if (!s)
        return NULL;
    else
        ret += BRST_Dict_Add(outline, "Title", s);

    open_flg = BRST_Number_New(mmgr, BRST_OUTLINE_OPENED);
    if (!open_flg)
        return NULL;

    BRST_Obj_SetID(open_flg, BRST_Obj_ID(open_flg) | BRST_OTYPE_HIDDEN);
    ret += BRST_Dict_Add(outline, "_OPENED", open_flg);

    ret += BRST_Dict_AddName(outline, "Type", "Outlines");
    ret += AddChild(parent, outline);

    if (ret != BRST_OK)
        return NULL;

    outline->header.obj_class |= BRST_OSUBCLASS_OUTLINE;

    return outline;
}

static BRST_STATUS
AddChild(BRST_Outline parent,
    BRST_Outline item)
{
    BRST_Outline first = (BRST_Outline)BRST_Dict_Item(parent, "First",
        BRST_OCLASS_DICT);
    BRST_Outline last  = (BRST_Outline)BRST_Dict_Item(parent, "Last",
         BRST_OCLASS_DICT);
    BRST_STATUS ret    = 0;

    BRST_PTRACE((" AddChild\n"));

    if (!first)
        ret += BRST_Dict_Add(parent, "First", item);

    if (last) {
        ret += BRST_Dict_Add(last, "Next", item);
        ret += BRST_Dict_Add(item, "Prev", last);
    }

    ret += BRST_Dict_Add(parent, "Last", item);
    ret += BRST_Dict_Add(item, "Parent", parent);

    if (ret != BRST_OK)
        return BRST_Error_Code(item->error);

    return BRST_OK;
}

BRST_BOOL
BRST_Outline_Opened(BRST_Outline outline)
{
    BRST_Number n = (BRST_Number)BRST_Dict_Item(outline, "_OPENED",
        BRST_OCLASS_NUMBER);

    BRST_PTRACE((" BRST_Outline_Opened\n"));

    if (!n)
        return BRST_FALSE;

    return BRST_Number_Value(n);
}

BRST_Outline
BRST_Outline_First(BRST_Outline outline)
{
    BRST_PTRACE((" BRST_Outline_First\n"));

    return (BRST_Outline)BRST_Dict_Item(outline, "First",
        BRST_OCLASS_DICT);
}

BRST_Outline
BRST_Outline_Last(BRST_Outline outline)
{
    BRST_PTRACE((" BRST_Outline_Last\n"));

    return (BRST_Outline)BRST_Dict_Item(outline, "Last", BRST_OCLASS_DICT);
}

BRST_Outline
BRST_Outline_Prev(BRST_Outline outline)
{
    BRST_PTRACE((" BRST_Outline_Prev\n"));

    return (BRST_Outline)BRST_Dict_Item(outline, "Prev", BRST_OCLASS_DICT);
}

BRST_Outline
BRST_Outline_Next(BRST_Outline outline)
{
    BRST_PTRACE((" BRST_Outline_Next\n"));

    return (BRST_Outline)BRST_Dict_Item(outline, "Next", BRST_OCLASS_DICT);
}

BRST_Outline
BRST_Outline_Parent(BRST_Outline outline)
{
    BRST_PTRACE((" BRST_Outline_Parent\n"));

    return (BRST_Outline)BRST_Dict_Item(outline, "Parent",
        BRST_OCLASS_DICT);
}

static BRST_STATUS
BeforeWrite(BRST_Dict obj)
{
    BRST_Number n   = (BRST_Number)BRST_Dict_Item(obj, "Count",
          BRST_OCLASS_NUMBER);
    BRST_UINT count = CountChild((BRST_Outline)obj);

    BRST_PTRACE((" BeforeWrite\n"));

    if (count == 0 && n)
        return BRST_Dict_RemoveElement(obj, "Count");

    if (!BRST_Outline_Opened((BRST_Outline)obj))
        count = count * -1;

    if (n)
        BRST_Number_SetValue(n, count);
    else if (count)
        return BRST_Dict_AddNumber(obj, "Count", count);

    return BRST_OK;
}

static BRST_UINT
CountChild(BRST_Outline outline)
{
    BRST_Outline child = BRST_Outline_First(outline);
    BRST_UINT count    = 0;

    BRST_PTRACE((" CountChild\n"));

    while (child) {
        count++;

        if (BRST_Outline_Opened(child))
            count += CountChild(child);

        child = BRST_Outline_Next(child);
    }

    return count;
}

BRST_BOOL
BRST_Outline_Validate(BRST_Outline outline)
{
    if (!outline)
        return BRST_FALSE;

    BRST_PTRACE((" BRST_Outline_Validate\n"));

    if (outline->header.obj_class != (BRST_OSUBCLASS_OUTLINE | BRST_OCLASS_DICT))
        return BRST_FALSE;

    return BRST_TRUE;
}
