#include "brst_mmgr.h"
#include "brst_types.h"
#include "brst_stream.h"
#include "brst_encrypt.h"
#include "brst_transmatrix.h"
#include "brst_array.h"
#include "brst_xref.h"
#include "brst_dict.h"
#include "private/brst_encrypt.h"
#include "private/brst_object.h"
#include "private/brst_object_write.h"
#include "private/brst_utils.h"
#include "private/brst_defines.h"
#include "brst_consts.h"
#include "brst_error.h"
#include "brst_encoder.h"
#include "private/brst_proxy.h"
#include "private/brst_real.h"
#include "private/brst_number.h"
#include "private/brst_binary.h"
#include "private/brst_string.h"
#include "private/brst_name.h"
#include "private/brst_boolean.h"
#include "private/brst_direct.h"
#include "private/brst_array.h"
#include "private/brst_dict.h"

BRST_STATUS
BRST_Obj_Write(void* obj,
    BRST_Stream stream,
    BRST_Encrypt e)
{
    BRST_Obj_Header* header = (BRST_Obj_Header*)obj;

    BRST_PTRACE(" BRST_Obj_Write\n");

    if (header->obj_id & BRST_OTYPE_HIDDEN) {
        BRST_PTRACE("#BRST_Obj_Write obj=0x%p skipped\n", (void*)obj);
        return BRST_OK;
    }

    if (header->obj_class == BRST_OCLASS_PROXY) {
        char buf[BRST_SHORT_BUF_SIZE];
        char* pbuf   = buf;
        char* eptr   = buf + BRST_SHORT_BUF_SIZE - 1;
        BRST_Proxy p = obj;

        header = (BRST_Obj_Header*)p->obj;

        pbuf    = BRST_IToA(pbuf, header->obj_id & 0x00FFFFFF, eptr);
        *pbuf++ = ' ';
        pbuf    = BRST_IToA(pbuf, header->gen_no, eptr);
        BRST_StrCpy(pbuf, " R", eptr);

        return BRST_Stream_WriteStr(stream, buf);
    }

    return BRST_Obj_WriteValue(obj, stream, e);
}

BRST_STATUS
BRST_Obj_WriteValue(void* obj,
    BRST_Stream stream,
    BRST_Encrypt e)
{
    BRST_Obj_Header* header;
    BRST_STATUS ret;

    BRST_PTRACE(" BRST_Obj_WriteValue\n");

    header = (BRST_Obj_Header*)obj;

    BRST_PTRACE(" BRST_Obj_WriteValue obj=0x%p obj_class=0x%04X\n",
        (void*)obj, (BRST_UINT)header->obj_class);

    switch (header->obj_class & BRST_OCLASS_ANY) {
    case BRST_OCLASS_NAME:
        ret = BRST_Name_Write(obj, stream);
        break;
    case BRST_OCLASS_NUMBER:
        ret = BRST_Number_Write(obj, stream);
        break;
    case BRST_OCLASS_REAL:
        ret = BRST_Real_Write(obj, stream);
        break;
    case BRST_OCLASS_STRING:
        ret = BRST_String_Write(obj, stream, e);
        break;
    case BRST_OCLASS_BINARY:
        ret = BRST_Binary_Write(obj, stream, e);
        break;
    case BRST_OCLASS_ARRAY:
        ret = BRST_Array_Write(obj, stream, e);
        break;
    case BRST_OCLASS_DICT:
        ret = BRST_Dict_Write(obj, stream, e);
        break;
    case BRST_OCLASS_BOOLEAN:
        ret = BRST_Boolean_Write(obj, stream);
        break;
    case BRST_OCLASS_DIRECT:
        ret = BRST_Direct_Write(obj, stream);
        break;
    case BRST_OCLASS_NULL:
        ret = BRST_Stream_WriteStr(stream, "null");
        break;
    default:
        ret = BRST_ERR_UNKNOWN_CLASS;
    }

    return ret;
}
