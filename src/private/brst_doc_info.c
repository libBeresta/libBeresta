#include "brst_types.h"
#include "brst_mmgr.h"
#include "brst_encrypt.h"
#include "brst_xref.h"
#include "brst_dict.h"
#include "brst_stream.h"
#include "brst_encoder.h"
#include "brst_doc.h"
#include "brst_doc_info.h"
#include "private/brst_info.h"
#include "private/brst_dict.h"
#include "private/brst_string.h"
#include "private/brst_utils.h"
#include "brst_error.h"
#include "private/brst_defines.h"
#include "brst_consts.h"

static const char* const BRST_INFO_ATTR_NAMES[] = {
    "CreationDate",
    "ModDate",
    "Author",
    "Creator",
    "Producer",
    "Title",
    "Subject",
    "Keywords",
    "Trapped",
    "GTS_PDFXVersion",
    NULL
};

static const char*
InfoTypeToName(BRST_InfoType type);

/*---------------------------------------------------------------------------*/

static const char*
InfoTypeToName(BRST_InfoType type)
{
    BRST_UINT idx = (BRST_UINT)type;

    return BRST_INFO_ATTR_NAMES[idx];
}

BRST_STATUS
BRST_Info_SetInfoAttr(BRST_Dict info,
    BRST_InfoType type,
    const char* value,
    BRST_Encoder encoder)
{
    const char* name = InfoTypeToName(type);

    BRST_PTRACE(" BRST_Info_SetInfoAttr\n");

    if (type <= BRST_INFO_MOD_DATE)
        return BRST_Error_Set(info->error, BRST_INVALID_PARAMETER, 0);

    if (type == BRST_INFO_TRAPPED)
        return BRST_Dict_AddName(info, name, value);

    return BRST_Dict_Add(info, name, BRST_String_New(info->mmgr, value, encoder));
}

const char*
BRST_Info_InfoAttr(BRST_Dict info,
    BRST_InfoType type)
{
    const char* name = InfoTypeToName(type);
    BRST_String s;

    BRST_PTRACE(" BRST_Info_InfoAttr\n");

    if (!info)
        return NULL;

    s = BRST_Dict_Item(info, name, BRST_OCLASS_STRING);

    if (!s)
        return NULL;
    else
        return BRST_String_Value(s);
}

BRST_STATUS
BRST_Info_SetInfoDateAttr(BRST_Dict info,
    BRST_InfoType type,
    BRST_Date value)
{
    char tmp[BRST_DATE_TIME_STR_LEN + 1];
    char* ptmp;
    const char* name = InfoTypeToName(type);

    BRST_PTRACE(" BRST_Info_SetInfoDateAttr\n");

    if (type > BRST_INFO_MOD_DATE)
        return BRST_Error_Set(info->error, BRST_INVALID_PARAMETER, 0);

    BRST_MemSet(tmp, 0, BRST_DATE_TIME_STR_LEN + 1);

    if (BRST_Date_Validate(value) != BRST_OK) {
        return BRST_Error_Set(info->error, BRST_INVALID_DATE_TIME, 0);
    }

    ptmp = (char*)BRST_MemCopy((BRST_BYTE*)tmp, (BRST_BYTE*)"D:", 2);
    ptmp = BRST_IToA2(ptmp, BRST_Date_Part(value, BRST_DATE_PART_YEAR), 5);
    ptmp = BRST_IToA2(ptmp, BRST_Date_Part(value, BRST_DATE_PART_MONTH), 3);
    ptmp = BRST_IToA2(ptmp, BRST_Date_Part(value, BRST_DATE_PART_DAY), 3);
    ptmp = BRST_IToA2(ptmp, BRST_Date_Part(value, BRST_DATE_PART_HOUR), 3);
    ptmp = BRST_IToA2(ptmp, BRST_Date_Part(value, BRST_DATE_PART_MINUTE), 3);
    ptmp = BRST_IToA2(ptmp, BRST_Date_Part(value, BRST_DATE_PART_SECOND), 3);
    BRST_UT_Relationship ind = (BRST_UT_Relationship)BRST_Date_Part(value, BRST_DATE_PART_UT_RELATIONSHIP);
    if (ind != BRST_UT_RELATIONSHIP_NONE) {
        char indChar = (ind == BRST_UT_RELATIONSHIP_ZERO) ? 'Z' : ((ind == BRST_UT_RELATIONSHIP_PLUS) ? '+' : '-');
        *ptmp++ = indChar;
        ptmp    = BRST_IToA2(ptmp, BRST_Date_Part(value, BRST_DATE_PART_HOUR_OFFSET), 3);
        *ptmp++ = '\'';
        ptmp    = BRST_IToA2(ptmp, BRST_Date_Part(value, BRST_DATE_PART_MINUTE_OFFSET), 3);
    }
    *ptmp = 0;

    return BRST_Dict_Add(info, name, BRST_String_New(info->mmgr, tmp, NULL));
}
