#include "brst_mmgr.h"
#include "brst_types.h"
#include "brst_stream.h"
#include "brst_dict.h"
#include "private/brst_proxy.h"
#include "private/brst_object.h"
#include "brst_encrypt.h"
#include "private/brst_dict.h"
#include "private/brst_list.h"
#include "brst_consts.h"
#include "private/brst_boolean.h"
#include "private/brst_number.h"
#include "private/brst_real.h"
#include "private/brst_name.h"
#include "private/brst_utils.h"
#include "brst_error.h"
#include "brst_array.h"
#include "private/brst_array.h"
#include "private/brst_defines.h"
#include "private/brst_object_write.h"

typedef struct _BRST_DictElement_Rec {
    char key[BRST_LIMIT_MAX_NAME_LEN + 1];
    void* value;
} BRST_DictElement_Rec;

BRST_DictElement
GetElement(BRST_Dict dict,
    const char* key);

/*--------------------------------------------------------------------------*/

BRST_Dict
BRST_Dict_New(BRST_MMgr mmgr)
{
    BRST_Dict obj;

    obj = (BRST_Dict)BRST_GetMem(mmgr, sizeof(BRST_Dict_Rec));
    if (obj) {
        BRST_MemSet(obj, 0, sizeof(BRST_Dict_Rec));
        obj->header.obj_class = BRST_OCLASS_DICT;
        obj->mmgr             = mmgr;
        obj->error            = BRST_MMgr_Error(mmgr);
        obj->list             = BRST_List_New(mmgr, BRST_DEF_ITEMS_PER_BLOCK);
        obj->filter           = BRST_STREAM_FILTER_NONE;
        if (!obj->list) {
            BRST_FreeMem(mmgr, obj);
            obj = NULL;
        }
    }

    return obj;
}

void BRST_Dict_Free(BRST_Dict dict)
{
    BRST_UINT i;

    if (!dict)
        return;

    if (dict->free_fn)
        dict->free_fn(dict);

    for (i = 0; i < BRST_List_Count(dict->list); i++) {
        BRST_DictElement element = (BRST_DictElement)BRST_List_ItemAt(dict->list, i);

        if (element) {
            BRST_Obj_Free(dict->mmgr, element->value);
            BRST_FreeMem(dict->mmgr, element);
        }
    }

    if (dict->stream)
        BRST_Stream_Free(dict->stream);

    BRST_List_Free(dict->list);

    dict->header.obj_class = 0;

    BRST_FreeMem(dict->mmgr, dict);
}

BRST_STATUS
BRST_Dict_Add_FilterParams(BRST_Dict dict, BRST_Dict filterParam)
{
    BRST_Array paramArray;
    /* prepare params object */
    paramArray = BRST_Dict_Item(dict, "DecodeParms",
        BRST_OCLASS_ARRAY);
    if (paramArray == NULL) {
        paramArray = BRST_Array_New(dict->mmgr);
        if (!paramArray)
            return BRST_Error_Code(dict->error);

        /* add parameters */
        BRST_Dict_Add(dict, "DecodeParms", paramArray);
    }
    BRST_Array_Add(paramArray, filterParam);
    return BRST_OK;
}

BRST_STATUS
BRST_Dict_Write(BRST_Dict dict,
    BRST_Stream stream,
    BRST_Encrypt e)
{
    BRST_UINT i;
    BRST_STATUS ret;

    ret = BRST_Stream_WriteStr(stream, "<<\012");
    if (ret != BRST_OK)
        return ret;

    if (dict->before_write_fn) {
        if ((ret = dict->before_write_fn(dict)) != BRST_OK)
            return ret;
    }

    /* encrypt-dict must not be encrypted. */
    if (dict->header.obj_class == (BRST_OCLASS_DICT | BRST_OSUBCLASS_ENCRYPT))
        e = NULL;

    if (dict->stream) {
        /* set filter element */
        if (dict->filter == BRST_STREAM_FILTER_NONE)
            BRST_Dict_RemoveElement(dict, "Filter");
        else {
            BRST_Array array = BRST_Dict_Item(dict, "Filter",
                BRST_OCLASS_ARRAY);

            if (!array) {
                array = BRST_Array_New(dict->mmgr);
                if (!array)
                    return BRST_Error_Code(dict->error);

                ret = BRST_Dict_Add(dict, "Filter", array);
                if (ret != BRST_OK)
                    return ret;
            }

            BRST_Array_Clear(array);

#ifdef LIBBRST_HAVE_ZLIB
            if (dict->filter & BRST_STREAM_FILTER_FLATE_DECODE)
                BRST_Array_AddName(array, "FlateDecode");
#endif /* LIBBRST_HAVE_ZLIB */

            if (dict->filter & BRST_STREAM_FILTER_DCT_DECODE)
                BRST_Array_AddName(array, "DCTDecode");

            if (dict->filter & BRST_STREAM_FILTER_CCITT_DECODE)
                BRST_Array_AddName(array, "CCITTFaxDecode");

            if (dict->filterParams != NULL) {
                BRST_Dict_Add_FilterParams(dict, dict->filterParams);
            }
        }
    }

    for (i = 0; i < BRST_List_Count(dict->list); i++) {
        BRST_DictElement element = (BRST_DictElement)BRST_List_ItemAt(dict->list, i);
        BRST_Obj_Header* header  = (BRST_Obj_Header*)(element->value);

        if (!element->value)
            return BRST_Error_Set(dict->error, BRST_INVALID_OBJECT, 0);

        if (header->obj_id & BRST_OTYPE_HIDDEN) {
            BRST_PTRACE((" BRST_Dict_Write obj=%p skipped obj_id=0x%08X\n",
                element->value, (BRST_UINT)header->obj_id));
        } else {
            ret = BRST_Stream_WriteEscapeName(stream, element->key);
            if (ret != BRST_OK)
                return ret;

            ret = BRST_Stream_WriteChar(stream, ' ');
            if (ret != BRST_OK)
                return ret;

            ret = BRST_Obj_Write(element->value, stream, e);
            if (ret != BRST_OK)
                return ret;

            ret = BRST_Stream_WriteStr(stream, "\012");
            if (ret != BRST_OK)
                return ret;
        }
    }

    if (dict->write_fn) {
        if ((ret = dict->write_fn(dict, stream)) != BRST_OK)
            return ret;
    }

    if ((ret = BRST_Stream_WriteStr(stream, ">>")) != BRST_OK)
        return ret;

    if (dict->stream) {
        BRST_UINT32 strptr;
        BRST_Number length;

        /* get "length" element */
        length = (BRST_Number)BRST_Dict_Item(dict, "Length",
            BRST_OCLASS_NUMBER);
        if (!length)
            return BRST_Error_Set(dict->error,
                BRST_DICT_STREAM_LENGTH_NOT_FOUND, 0);

        /* "length" element must be indirect-object */
        if (!(BRST_Obj_ID(length) & BRST_OTYPE_INDIRECT)) {
            return BRST_Error_Set(dict->error, BRST_DICT_ITEM_UNEXPECTED_TYPE,
                0);
        }

        if ((ret = BRST_Stream_WriteStr(stream, "\012stream\015\012")) /* Acrobat 8.15 requires both \r and \n here */
            != BRST_OK)
            return ret;

        strptr = stream->size;

        if (e)
            BRST_Encrypt_Reset(e);

        if ((ret = BRST_Stream_WriteToStream(dict->stream, stream,
                 dict->filter, e))
            != BRST_OK)
            return ret;

        BRST_Number_SetValue(length, stream->size - strptr);

        ret = BRST_Stream_WriteStr(stream, "\012endstream");
    }

    /* 2006.08.13 add. */
    if (dict->after_write_fn) {
        if ((ret = dict->after_write_fn(dict)) != BRST_OK)
            return ret;
    }

    return ret;
}

BRST_STATUS
BRST_Dict_Add(BRST_Dict dict,
    const char* key,
    void* obj)
{
    BRST_Obj_Header* header;
    BRST_STATUS ret = BRST_OK;
    BRST_DictElement element;

    if (!obj) {
        if (BRST_Error_Code(dict->error) == BRST_OK)
            return BRST_Error_Set(dict->error, BRST_INVALID_OBJECT, 0);
        else
            return BRST_INVALID_OBJECT;
    }

    header = (BRST_Obj_Header*)obj;

    if (header->obj_id & BRST_OTYPE_DIRECT)
        return BRST_Error_Set(dict->error, BRST_INVALID_OBJECT, 0);

    if (!key) {
        BRST_Obj_Free(dict->mmgr, obj);
        return BRST_Error_Set(dict->error, BRST_INVALID_OBJECT, 0);
    }

    if (BRST_List_Count(dict->list) >= BRST_LIMIT_MAX_DICT_ELEMENT) {
        BRST_PTRACE((" BRST_Dict_Add exceed limitation of dict count(%d)\n",
            BRST_LIMIT_MAX_DICT_ELEMENT));

        BRST_Obj_Free(dict->mmgr, obj);
        return BRST_Error_Set(dict->error, BRST_DICT_COUNT_ERR, 0);
    }

    /* check whether there is an object which has same name */
    element = GetElement(dict, key);

    if (element) {
        BRST_Obj_Free(dict->mmgr, element->value);
        element->value = NULL;
    } else {
        element = (BRST_DictElement)BRST_GetMem(dict->mmgr,
            sizeof(BRST_DictElement_Rec));

        if (!element) {
            /* cannot create element object */
            if (!(header->obj_id & BRST_OTYPE_INDIRECT))
                BRST_Obj_Free(dict->mmgr, obj);

            return BRST_Error_Code(dict->error);
        }

        BRST_StrCpy(element->key, key, element->key + BRST_LIMIT_MAX_NAME_LEN + 1);
        element->value = NULL;

        ret = BRST_List_Add(dict->list, element);
        if (ret != BRST_OK) {
            if (!(header->obj_id & BRST_OTYPE_INDIRECT))
                BRST_Obj_Free(dict->mmgr, obj);

            BRST_FreeMem(dict->mmgr, element);

            return BRST_Error_Code(dict->error);
        }
    }

    if (header->obj_id & BRST_OTYPE_INDIRECT) {
        BRST_Proxy proxy = BRST_Proxy_New(dict->mmgr, obj);

        if (!proxy) {
            BRST_Obj_Free(dict->mmgr, obj);
            return BRST_Error_Code(dict->error);
        }

        element->value = proxy;
        proxy->header.obj_id |= BRST_OTYPE_DIRECT;
    } else {
        element->value = obj;
        header->obj_id |= BRST_OTYPE_DIRECT;
    }

    return ret;
}

BRST_STATUS
BRST_Dict_AddName(BRST_Dict dict,
    const char* key,
    const char* value)
{
    BRST_Name name = BRST_Name_New(dict->mmgr, value);
    if (!name)
        return BRST_Error_Code(dict->error);

    return BRST_Dict_Add(dict, key, name);
}

BRST_STATUS
BRST_Dict_AddNumber(BRST_Dict dict,
    const char* key,
    BRST_INT32 value)
{
    BRST_Number number = BRST_Number_New(dict->mmgr, value);

    if (!number)
        return BRST_Error_Code(dict->error);

    return BRST_Dict_Add(dict, key, number);
}

BRST_STATUS
BRST_Dict_AddReal(BRST_Dict dict,
    const char* key,
    BRST_REAL value)
{
    BRST_Real real = BRST_Real_New(dict->mmgr, value);

    if (!real)
        return BRST_Error_Code(dict->error);

    return BRST_Dict_Add(dict, key, real);
}

BRST_STATUS
BRST_Dict_AddBoolean(BRST_Dict dict,
    const char* key,
    BRST_BOOL value)
{
    BRST_Boolean obj = BRST_Boolean_New(dict->mmgr, value);

    if (!obj)
        return BRST_Error_Code(dict->error);

    return BRST_Dict_Add(dict, key, obj);
}

void* BRST_Dict_Item(BRST_Dict dict,
    const char* key,
    BRST_UINT16 obj_class)
{
    BRST_DictElement element = GetElement(dict, key);
    void* obj;

    if (element && BRST_StrCmp(key, element->key) == 0) {
        BRST_Obj_Header* header = (BRST_Obj_Header*)element->value;

        if (header->obj_class == BRST_OCLASS_PROXY) {
            BRST_Proxy p = element->value;
            header       = (BRST_Obj_Header*)p->obj;
            obj          = p->obj;
        } else
            obj = element->value;

        if ((header->obj_class & BRST_OCLASS_ANY) != obj_class) {
            BRST_PTRACE((" BRST_Dict_Item dict=%p key=%s obj_class=0x%08X\n",
                dict, key, (BRST_UINT)header->obj_class));
            BRST_Error_Set(dict->error, BRST_DICT_ITEM_UNEXPECTED_TYPE, 0);

            return NULL;
        }

        return obj;
    }

    return NULL;
}

BRST_DictElement
GetElement(BRST_Dict dict,
    const char* key)
{
    BRST_UINT i;

    for (i = 0; i < BRST_List_Count(dict->list); i++) {
        BRST_DictElement element = (BRST_DictElement)BRST_List_ItemAt(dict->list, i);

        if (BRST_StrCmp(key, element->key) == 0)
            return element;
    }

    return NULL;
}

BRST_STATUS
BRST_Dict_RemoveElement(BRST_Dict dict,
    const char* key)
{
    BRST_UINT i;

    for (i = 0; i < BRST_List_Count(dict->list); i++) {
        BRST_DictElement element = (BRST_DictElement)BRST_List_ItemAt(dict->list, i);

        if (BRST_StrCmp(key, element->key) == 0) {
            BRST_List_Remove(dict->list, element);

            BRST_Obj_Free(dict->mmgr, element->value);
            BRST_FreeMem(dict->mmgr, element);

            return BRST_OK;
        }
    }

    return BRST_DICT_ITEM_NOT_FOUND;
}

const char*
BRST_Dict_KeyByObj(BRST_Dict dict,
    void* obj)
{
    BRST_UINT i;

    for (i = 0; i < BRST_List_Count(dict->list); i++) {
        BRST_Obj_Header* header;
        BRST_DictElement element = (BRST_DictElement)BRST_List_ItemAt(dict->list, i);

        header = (BRST_Obj_Header*)(element->value);
        if (header->obj_class == BRST_OCLASS_PROXY) {
            BRST_Proxy p = element->value;

            if (p->obj == obj)
                return element->key;
        } else {
            if (element->value == obj)
                return element->key;
        }
    }

    return NULL;
}

BRST_Stream
BRST_Dict_Stream(BRST_Dict dict)
{
    if (!dict)
        return NULL;

    return dict->stream;
}

void BRST_Dict_SetStream(BRST_Dict dict,
    BRST_Stream stream)
{
    if (dict)
        dict->stream = stream;
}
