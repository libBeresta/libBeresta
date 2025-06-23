#include "brst_external.h"
#include "brst_types.h"
#include "brst_mmgr.h"
#include "brst_encrypt.h"
#include "brst_stream.h"
#include "brst_dict.h"
#include "brst_xref.h"
#include "brst_error.h"
#include "brst_consts.h"
#include "brst_page.h"
#include "brst_destination.h"
#include "private/brst_destination.h"
#include "private/brst_array.h"
#include "private/brst_utils.h"

/*----------------------------------------------------------------------------*/
/*----- BRST_Destination -----------------------------------------------------*/

BRST_EXPORT(BRST_STATUS)
BRST_Destination_SetXYZ(BRST_Destination dst,
    BRST_REAL left,
    BRST_REAL top,
    BRST_REAL zoom)
{
    BRST_STATUS ret = BRST_OK;
    BRST_Page target;

    BRST_PTRACE((" BRST_Destination_SetXYZ\n"));

    if (!BRST_Destination_Validate(dst))
        return BRST_INVALID_DESTINATION;

    if (left < 0 || top < 0 || zoom < 0.08 || zoom > 32)
        return BRST_Error_Raise(dst->error, BRST_INVALID_PARAMETER, 0);

    target = (BRST_Page)BRST_Array_Item(dst, 0, BRST_OCLASS_DICT);

    if (BRST_List_Count(dst->list) > 1) {
        BRST_Array_Clear(dst);
        ret += BRST_Array_Add(dst, target);
    }

    ret += BRST_Array_AddName(dst,
        BRST_DESTINATION_TYPE_NAMES[(BRST_INT)BRST_XYZ]);
    ret += BRST_Array_AddReal(dst, left);
    ret += BRST_Array_AddReal(dst, top);
    ret += BRST_Array_AddReal(dst, zoom);

    if (ret != BRST_OK)
        return BRST_Error_Check(dst->error);

    return BRST_OK;
}

BRST_EXPORT(BRST_STATUS)
BRST_Destination_SetFit(BRST_Destination dst)
{
    BRST_STATUS ret = BRST_OK;
    BRST_Page target;

    BRST_PTRACE((" BRST_Destination_SetFit\n"));

    if (!BRST_Destination_Validate(dst))
        return BRST_INVALID_DESTINATION;

    target = (BRST_Page)BRST_Array_Item(dst, 0, BRST_OCLASS_DICT);

    if (BRST_List_Count(dst->list) > 1) {
        BRST_Array_Clear(dst);
        ret += BRST_Array_Add(dst, target);
    }

    ret += BRST_Array_AddName(dst,
        BRST_DESTINATION_TYPE_NAMES[(BRST_INT)BRST_FIT]);

    if (ret != BRST_OK)
        return BRST_Error_Check(dst->error);

    return BRST_OK;
}

BRST_EXPORT(BRST_STATUS)
BRST_Destination_SetFitH(BRST_Destination dst,
    BRST_REAL top)
{
    BRST_STATUS ret = BRST_OK;
    BRST_Page target;

    BRST_PTRACE((" BRST_Destination_SetFitH\n"));

    if (!BRST_Destination_Validate(dst))
        return BRST_INVALID_DESTINATION;

    target = (BRST_Page)BRST_Array_Item(dst, 0, BRST_OCLASS_DICT);

    if (BRST_List_Count(dst->list) > 1) {
        BRST_Array_Clear(dst);
        ret += BRST_Array_Add(dst, target);
    }

    ret += BRST_Array_AddName(dst,
        BRST_DESTINATION_TYPE_NAMES[(BRST_INT)BRST_FIT_H]);
    ret += BRST_Array_AddReal(dst, top);

    if (ret != BRST_OK)
        return BRST_Error_Check(dst->error);

    return BRST_OK;
}

BRST_EXPORT(BRST_STATUS)
BRST_Destination_SetFitV(BRST_Destination dst,
    BRST_REAL left)
{
    BRST_STATUS ret = BRST_OK;
    BRST_Page target;

    BRST_PTRACE((" BRST_Destination_SetFitV\n"));

    if (!BRST_Destination_Validate(dst))
        return BRST_INVALID_DESTINATION;

    target = (BRST_Page)BRST_Array_Item(dst, 0, BRST_OCLASS_DICT);

    if (BRST_List_Count(dst->list) > 1) {
        BRST_Array_Clear(dst);
        ret += BRST_Array_Add(dst, target);
    }

    ret += BRST_Array_AddName(dst,
        BRST_DESTINATION_TYPE_NAMES[(BRST_INT)BRST_FIT_V]);
    ret += BRST_Array_AddReal(dst, left);

    if (ret != BRST_OK)
        return BRST_Error_Check(dst->error);

    return BRST_OK;
}

BRST_EXPORT(BRST_STATUS)
BRST_Destination_SetFitR(BRST_Destination dst,
    BRST_REAL left,
    BRST_REAL bottom,
    BRST_REAL right,
    BRST_REAL top)
{
    BRST_STATUS ret = BRST_OK;
    BRST_Page target;

    BRST_PTRACE((" BRST_Destination_SetFitR\n"));

    if (!BRST_Destination_Validate(dst))
        return BRST_INVALID_DESTINATION;

    target = (BRST_Page)BRST_Array_Item(dst, 0, BRST_OCLASS_DICT);

    if (BRST_List_Count(dst->list) > 1) {
        BRST_Array_Clear(dst);
        ret += BRST_Array_Add(dst, target);
    }

    ret += BRST_Array_AddName(dst,
        BRST_DESTINATION_TYPE_NAMES[(BRST_INT)BRST_FIT_R]);
    ret += BRST_Array_AddReal(dst, left);
    ret += BRST_Array_AddReal(dst, bottom);
    ret += BRST_Array_AddReal(dst, right);
    ret += BRST_Array_AddReal(dst, top);

    if (ret != BRST_OK)
        return BRST_Error_Check(dst->error);

    return BRST_OK;
}

BRST_EXPORT(BRST_STATUS)
BRST_Destination_SetFitB(BRST_Destination dst)
{
    BRST_STATUS ret = BRST_OK;
    BRST_Page target;

    BRST_PTRACE((" BRST_Destination_SetFitB\n"));

    if (!BRST_Destination_Validate(dst))
        return BRST_INVALID_DESTINATION;

    target = (BRST_Page)BRST_Array_Item(dst, 0, BRST_OCLASS_DICT);

    if (BRST_List_Count(dst->list) > 1) {
        BRST_Array_Clear(dst);
        ret += BRST_Array_Add(dst, target);
    }

    ret += BRST_Array_AddName(dst,
        BRST_DESTINATION_TYPE_NAMES[(BRST_INT)BRST_FIT_B]);

    if (ret != BRST_OK)
        return BRST_Error_Check(dst->error);

    return BRST_OK;
}

BRST_EXPORT(BRST_STATUS)
BRST_Destination_SetFitBH(BRST_Destination dst,
    BRST_REAL top)
{
    BRST_STATUS ret = BRST_OK;
    BRST_Page target;

    BRST_PTRACE((" BRST_Destination_SetFitBH\n"));

    if (!BRST_Destination_Validate(dst))
        return BRST_INVALID_DESTINATION;

    target = (BRST_Page)BRST_Array_Item(dst, 0, BRST_OCLASS_DICT);

    if (BRST_List_Count(dst->list) > 1) {
        BRST_Array_Clear(dst);
        ret += BRST_Array_Add(dst, target);
    }

    ret += BRST_Array_AddName(dst,
        BRST_DESTINATION_TYPE_NAMES[(BRST_INT)BRST_FIT_BH]);
    ret += BRST_Array_AddReal(dst, top);

    if (ret != BRST_OK)
        return BRST_Error_Check(dst->error);

    return BRST_OK;
}

BRST_EXPORT(BRST_STATUS)
BRST_Destination_SetFitBV(BRST_Destination dst,
    BRST_REAL left)
{
    BRST_STATUS ret = BRST_OK;
    BRST_Page target;

    BRST_PTRACE((" BRST_Destination_SetFitBV\n"));

    if (!BRST_Destination_Validate(dst))
        return BRST_INVALID_DESTINATION;

    target = (BRST_Page)BRST_Array_Item(dst, 0, BRST_OCLASS_DICT);

    if (BRST_List_Count(dst->list) > 1) {
        BRST_Array_Clear(dst);
        ret += BRST_Array_Add(dst, target);
    }

    ret += BRST_Array_AddName(dst,
        BRST_DESTINATION_TYPE_NAMES[(BRST_INT)BRST_FIT_BV]);
    ret += BRST_Array_AddReal(dst, left);

    if (ret != BRST_OK)
        return BRST_Error_Check(dst->error);

    return BRST_OK;
}
