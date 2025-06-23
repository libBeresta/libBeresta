#define BRST_FREE_ENTRY 'f'
#define BRST_IN_USE_ENTRY 'n'

#include "brst_stream.h"
#include "brst_mmgr.h"
#include "brst_dict.h"
#include "brst_xref.h"
#include "brst_encrypt.h"
#include "private/brst_xref.h"
#include "private/brst_stream.h"
#include "private/brst_utils.h"
#include "private/brst_defines.h"
#include "brst_consts.h"
#include "brst_error.h"
#include "private/brst_object_write.h"
#include "private/brst_number.h"

static BRST_STATUS
WriteTrailer(BRST_Xref xref,
    BRST_Stream stream);

BRST_List
BRST_Xref_Entries(BRST_Xref xref)
{
    if (!xref)
        return NULL;
    return xref->entries;
}

BRST_Xref
BRST_Xref_New(BRST_MMgr mmgr,
    BRST_UINT32 offset)
{
    BRST_Xref xref;
    BRST_XrefEntry new_entry;

    BRST_PTRACE((" BRST_Xref_New\n"));

    xref = (BRST_Xref)BRST_GetMem(mmgr, sizeof(BRST_Xref_Rec));
    if (!xref)
        return NULL;

    BRST_MemSet(xref, 0, sizeof(BRST_Xref_Rec));
    xref->mmgr         = mmgr;
    xref->error        = BRST_MMgr_Error(mmgr);
    xref->start_offset = offset;

    xref->entries = BRST_List_New(mmgr, BRST_DEFALUT_XREF_ENTRY_NUM);
    if (!xref->entries)
        goto Fail;

    xref->addr = 0;

    if (xref->start_offset == 0) {
        new_entry = (BRST_XrefEntry)BRST_GetMem(mmgr,
            sizeof(BRST_XrefEntry_Rec));
        if (!new_entry)
            goto Fail;

        if (BRST_List_Add(xref->entries, new_entry) != BRST_OK) {
            BRST_FreeMem(mmgr, new_entry);
            goto Fail;
        }

        /* add first entry which is free entry and whose generation
         * number is 0
         */
        new_entry->entry_typ   = BRST_FREE_ENTRY;
        new_entry->byte_offset = 0;
        new_entry->gen_no      = BRST_MAX_GENERATION_NUM;
        new_entry->obj         = NULL;
    }

    xref->trailer = BRST_Dict_New(mmgr);
    if (!xref->trailer)
        goto Fail;

    return xref;

Fail:
    BRST_PTRACE((" BRST_Xref_New failed\n"));
    BRST_Xref_Free(xref);
    return NULL;
}

void BRST_Xref_Free(BRST_Xref xref)
{
    BRST_UINT i;
    BRST_XrefEntry entry;
    BRST_Xref tmp_xref;

    BRST_PTRACE((" BRST_Xref_Free\n"));

    /* delete xref entries. where prev element is not NULL,
     * delete all xref entries recursively.
     */
    while (xref) {
        /* delete all objects belong to the xref. */

        if (xref->entries) {
            for (i = 0; i < BRST_List_Count(xref->entries); i++) {
                entry = BRST_Xref_GetEntry(xref, i);
                if (entry->obj)
                    BRST_Obj_ForceFree(xref->mmgr, entry->obj);
                BRST_FreeMem(xref->mmgr, entry);
            }

            BRST_List_Free(xref->entries);
        }

        if (xref->trailer)
            BRST_Dict_Free(xref->trailer);

        tmp_xref = xref->prev;
        BRST_FreeMem(xref->mmgr, xref);
        xref = tmp_xref;
    }
}

BRST_STATUS
BRST_Xref_Add(BRST_Xref xref,
    void* obj)
{
    BRST_XrefEntry entry;
    BRST_Obj_Header* header;

    BRST_PTRACE((" BRST_Xref_Add\n"));

    if (!obj) {
        if (BRST_Error_Code(xref->error) == BRST_OK)
            return BRST_Error_Set(xref->error, BRST_INVALID_OBJECT, 0);
        else
            return BRST_INVALID_OBJECT;
    }

    header = (BRST_Obj_Header*)obj;

    if (header->obj_id & BRST_OTYPE_DIRECT || header->obj_id & BRST_OTYPE_INDIRECT)
        return BRST_Error_Set(xref->error, BRST_INVALID_OBJECT, 0);

    if (BRST_List_Count(xref->entries) >= BRST_LIMIT_MAX_XREF_ELEMENT) {
        BRST_Error_Set(xref->error, BRST_XREF_COUNT_ERR, 0);
        goto Fail;
    }

    /* in the following, we have to dispose the object when an error is
     * occurred.
     */

    entry = (BRST_XrefEntry)BRST_GetMem(xref->mmgr,
        sizeof(BRST_XrefEntry_Rec));
    if (entry == NULL)
        goto Fail;

    if (BRST_List_Add(xref->entries, entry) != BRST_OK) {
        BRST_FreeMem(xref->mmgr, entry);
        goto Fail;
    }

    entry->entry_typ   = BRST_IN_USE_ENTRY;
    entry->byte_offset = 0;
    entry->gen_no      = 0;
    entry->obj         = obj;
    header->obj_id     = xref->start_offset + BRST_List_Count(xref->entries) - 1 + BRST_OTYPE_INDIRECT;

    header->gen_no = entry->gen_no;

    return BRST_OK;

Fail:
    BRST_Obj_ForceFree(xref->mmgr, obj);
    return BRST_Error_Code(xref->error);
}

BRST_XrefEntry
BRST_Xref_GetEntry(BRST_Xref xref,
    BRST_UINT index)
{
    BRST_PTRACE((" BRST_Xref_GetEntry\n"));

    return (BRST_XrefEntry)BRST_List_ItemAt(xref->entries, index);
}

BRST_XrefEntry
BRST_Xref_GetEntryByObjectId(BRST_Xref xref,
    BRST_UINT obj_id)
{
    BRST_Xref tmp_xref = xref;

    BRST_PTRACE((" BRST_Xref_GetEntryByObjectId\n"));

    while (tmp_xref) {
        BRST_UINT i;

        if (BRST_List_Count(tmp_xref->entries) + tmp_xref->start_offset > obj_id) {
            BRST_Error_Set(xref->error, BRST_INVALID_OBJ_ID, 0);
            return NULL;
        }

        if (tmp_xref->start_offset < obj_id) {
            for (i = 0; i < BRST_List_Count(tmp_xref->entries); i++) {
                if (tmp_xref->start_offset + i == obj_id) {
                    BRST_XrefEntry entry = BRST_Xref_GetEntry(tmp_xref, i);

                    return entry;
                }
            }
        }

        tmp_xref = tmp_xref->prev;
    }

    return NULL;
}

BRST_STATUS
BRST_Xref_WriteToStream(BRST_Xref xref,
    BRST_Stream stream,
    BRST_Encrypt e)
{
    BRST_STATUS ret;
    BRST_UINT i;
    char buf[BRST_SHORT_BUF_SIZE];
    char* pbuf;
    char* eptr = buf + BRST_SHORT_BUF_SIZE - 1;
    BRST_UINT str_idx;
    BRST_Xref tmp_xref = xref;

    /* write each objects of xref to the specified stream */

    BRST_PTRACE((" BRST_Xref_WriteToStream\n"));

    while (tmp_xref) {
        if (tmp_xref->start_offset == 0)
            str_idx = 1;
        else
            str_idx = 0;

        for (i = str_idx; i < BRST_List_Count(tmp_xref->entries); i++) {
            BRST_XrefEntry entry = (BRST_XrefEntry)BRST_List_ItemAt(tmp_xref->entries, i);
            BRST_UINT obj_id     = tmp_xref->start_offset + i;
            BRST_UINT16 gen_no   = entry->gen_no;

            entry->byte_offset = stream->size;

            pbuf    = buf;
            pbuf    = BRST_IToA(pbuf, obj_id, eptr);
            *pbuf++ = ' ';
            pbuf    = BRST_IToA(pbuf, gen_no, eptr);
            BRST_StrCpy(pbuf, " obj\012", eptr);

            if ((ret = BRST_Stream_WriteStr(stream, buf)) != BRST_OK)
                return ret;

            if (e)
                BRST_Encrypt_InitKey(e, obj_id, gen_no);

            if ((ret = BRST_Obj_WriteValue(entry->obj, stream, e)) != BRST_OK)
                return ret;

            if ((ret = BRST_Stream_WriteStr(stream, "\012endobj\012"))
                != BRST_OK)
                return ret;
        }

        tmp_xref = tmp_xref->prev;
    }

    /* start to write cross-reference table */

    tmp_xref = xref;

    while (tmp_xref) {
        tmp_xref->addr = stream->size;

        pbuf    = buf;
        pbuf    = (char*)BRST_StrCpy(pbuf, "xref\012", eptr);
        pbuf    = BRST_IToA(pbuf, tmp_xref->start_offset, eptr);
        *pbuf++ = ' ';
        pbuf    = BRST_IToA(pbuf, BRST_List_Count(tmp_xref->entries), eptr);
        BRST_StrCpy(pbuf, "\012", eptr);
        ret = BRST_Stream_WriteStr(stream, buf);
        if (ret != BRST_OK)
            return ret;

        for (i = 0; i < BRST_List_Count(tmp_xref->entries); i++) {
            BRST_XrefEntry entry = BRST_Xref_GetEntry(tmp_xref, i);

            pbuf    = buf;
            pbuf    = BRST_IToA2(pbuf, entry->byte_offset, BRST_BYTE_OFFSET_LEN + 1);
            *pbuf++ = ' ';
            pbuf    = BRST_IToA2(pbuf, entry->gen_no, BRST_GEN_NO_LEN + 1);
            *pbuf++ = ' ';
            *pbuf++ = entry->entry_typ;
            BRST_StrCpy(pbuf, "\015\012", eptr); /* Acrobat 8.15 requires both \r and \n here */
            ret = BRST_Stream_WriteStr(stream, buf);
            if (ret != BRST_OK)
                return ret;
        }

        tmp_xref = tmp_xref->prev;
    }

    /* write trailer dictionary */
    ret = WriteTrailer(xref, stream);

    return ret;
}

static BRST_STATUS
WriteTrailer(BRST_Xref xref,
    BRST_Stream stream)
{
    BRST_UINT max_obj_id;
    BRST_STATUS ret;

    if (!xref)
        return BRST_INVALID_OBJECT;

    max_obj_id = BRST_List_Count(xref->entries) + xref->start_offset;

    BRST_PTRACE((" WriteTrailer\n"));

    if ((ret = BRST_Dict_AddNumber(xref->trailer, "Size", max_obj_id))
        != BRST_OK)
        return ret;

    if (xref->prev)
        if ((ret = BRST_Dict_AddNumber(xref->trailer, "Prev",
                 xref->prev->addr))
            != BRST_OK)
            return ret;

    if ((ret = BRST_Stream_WriteStr(stream, "trailer\012")) != BRST_OK)
        return ret;

    if ((ret = BRST_Dict_Write(xref->trailer, stream, NULL)) != BRST_OK)
        return ret;

    if ((ret = BRST_Stream_WriteStr(stream, "\012startxref\012")) != BRST_OK)
        return ret;

    if ((ret = BRST_Stream_WriteUInt(stream, xref->addr)) != BRST_OK)
        return ret;

    if ((ret = BRST_Stream_WriteStr(stream, "\012%%EOF\012")) != BRST_OK)
        return ret;

    return BRST_OK;
}

// TODO Похоже, что эту функцию надо как-то переименовать
BRST_Dict
BRST_DictStream_New(BRST_MMgr mmgr,
    BRST_Xref xref)
{
    BRST_Dict obj;
    BRST_Number length;
    BRST_STATUS ret = 0;

    obj = BRST_Dict_New(mmgr);
    if (!obj)
        return NULL;

    /* only stream object is added to xref automatically */
    ret += BRST_Xref_Add(xref, obj);
    if (ret != BRST_OK)
        return NULL;

    length = BRST_Number_New(mmgr, 0);
    if (!length)
        return NULL;

    ret = BRST_Xref_Add(xref, length);
    if (ret != BRST_OK)
        return NULL;

    ret = BRST_Dict_Add(obj, "Length", length);
    if (ret != BRST_OK)
        return NULL;

    BRST_Stream s = BRST_MemStream_New(mmgr, BRST_STREAM_BUF_SIZE);
    if (!s)
        return NULL;

    BRST_Dict_SetStream(obj, s);
    // TODO Stream
    //    obj->stream =
    //    if (!obj->stream)
    //        return NULL;

    return obj;
}
