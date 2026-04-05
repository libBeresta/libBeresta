#include "brst_encrypt.h"
#include "private/brst_encrypt.h"
#include "brst_stream.h"
#include "private/brst_defines.h"
#include "brst_mmgr.h"
#include "private/brst_list.h"
#include "brst_error.h"
#include "brst_dict.h"
#include "brst_types.h"
#include "brst_consts.h"
#include "private/brst_stream.h"
#include "brst_encoder.h"
#include "private/brst_utils.h"
#include "private/brst_c.h"

#include <errno.h>

#ifdef LIBBRST_HAVE_ZLIB
#include <zlib.h>
#include <zconf.h>
#endif /* LIBBRST_HAVE_ZLIB */

BRST_STATUS
BRST_MemStream_WriteFunc(BRST_Stream stream,
    const BRST_BYTE* ptr,
    BRST_UINT size);

BRST_STATUS
BRST_MemStream_SeekFunc(BRST_Stream stream,
    BRST_INT pos,
    BRST_WhenceMode mode);

BRST_STATUS
BRST_MemStream_ReadFunc(BRST_Stream stream,
    BRST_BYTE* buf,
    BRST_UINT* size);

BRST_INT32
BRST_MemStream_TellFunc(BRST_Stream stream);

BRST_UINT32
BRST_MemStream_SizeFunc(BRST_Stream stream);

void BRST_MemStream_FreeFunc(BRST_Stream stream);

BRST_STATUS
BRST_MemStream_InWrite(BRST_Stream stream,
    const BRST_BYTE** ptr,
    BRST_UINT* count);

BRST_STATUS
BRST_FileReader_ReadFunc(BRST_Stream stream,
    BRST_BYTE* ptr,
    BRST_UINT* size);

BRST_STATUS
BRST_FileReader_SeekFunc(BRST_Stream stream,
    BRST_INT pos,
    BRST_WhenceMode mode);

BRST_INT32
BRST_FileStream_TellFunc(BRST_Stream stream);

BRST_UINT32
BRST_FileStream_SizeFunc(BRST_Stream stream);

BRST_STATUS
BRST_FileWriter_WriteFunc(BRST_Stream stream,
    const BRST_BYTE* ptr,
    BRST_UINT size);

void BRST_FileStream_FreeFunc(BRST_Stream stream);

/*
 *  BRST_Stream_Read
 *
 *  stream : Pointer to a BRST_Stream object.
 *  ptr : Pointer to a buffer to copy read data.
 *  size : Pointer to a variable which indicates buffer size.
 *
 *  BRST_Stream_read returns BRST_OK when success. On failure, it returns
 *  error-code returned by reading function of this stream.
 *
 */

BRST_STATUS
BRST_Stream_Read(BRST_Stream stream,
    BRST_BYTE* ptr,
    BRST_UINT* size)
{
    if (!(stream->read_fn))
        return BRST_Error_Set(stream->error, BRST_INVALID_OPERATION, 0);

    /*
    if (BRST_Error_GetCode(stream->error) != BRST_NOERROR)
        return BRST_THIS_FUNC_WAS_SKIPPED;
    */

    return stream->read_fn(stream, ptr, size);
}

/*
 *  BRST_Stream_ReadLn
 *
 *  stream : Pointer to a BRST_Stream object.
 *  s : Pointer to a buffer to copy read data.
 *  size : buffer-size of s.
 *
 *  Read from stream until the buffer is exhausted or line-feed character is
 *  read.
 *
 */
BRST_STATUS
BRST_Stream_ReadLn(BRST_Stream stream,
    char* s,
    BRST_UINT* size)
{
    char buf[BRST_STREAM_BUF_SIZE];
    BRST_UINT r_size    = *size;
    BRST_UINT read_size = BRST_STREAM_BUF_SIZE;

    BRST_PTRACE(" BRST_Stream_ReadLn\n");

    if (!stream)
        return BRST_INVALID_PARAMETER;

    if (!s || *size == 0)
        return BRST_Error_Set(stream->error, BRST_INVALID_PARAMETER, 0);

    if (!(stream->seek_fn) || !(stream->read_fn))
        return BRST_Error_Set(stream->error, BRST_INVALID_OPERATION, 0);

    if (r_size < BRST_STREAM_BUF_SIZE)
        read_size = r_size;

    *size = 0;

    while (r_size > 1) {
        char* pbuf      = buf;
        BRST_STATUS ret = BRST_Stream_Read(stream, (BRST_BYTE*)buf, &read_size);

        if (ret != BRST_OK && read_size == 0)
            return ret;

        r_size -= read_size;

        while (read_size > 0) {
            if (*pbuf == 0x0A || *pbuf == 0x0D) {
                *s = 0;
                read_size--;

                /* handling CR-LF marker */
                if (*pbuf == 0x0D || read_size > 1) {
                    pbuf++;

                    if (*pbuf == 0x0A)
                        read_size--;
                }

                if (read_size > 0)
                    return BRST_Stream_Seek(stream, 0 - read_size,
                        BRST_SEEK_CUR);
                else
                    return BRST_OK;
            }

            *s++ = *pbuf++;
            read_size--;
            (*size)++;
        }

        if (r_size < BRST_STREAM_BUF_SIZE)
            read_size = r_size;
        else
            read_size = BRST_STREAM_BUF_SIZE;

        if (ret == BRST_STREAM_EOF)
            return BRST_STREAM_EOF;
    }

    *s = 0;

    return BRST_STREAM_READLN_CONTINUE;
}

/*
 * BRST_Stream_Write
 *
 *  stream : Pointer to a BRST_Stream object.
 *  ptr : Pointer to a buffer to write.
 *  size : The size of buffer to write.
 *
 *  BRST_Stream_Write returns BRST_OK when success. On failure, it returns
 *  error-code returned by writing function of this stream.
 *
 */
BRST_STATUS
BRST_Stream_Write(BRST_Stream stream,
    const BRST_BYTE* ptr,
    BRST_UINT size)
{
    BRST_STATUS ret;

    BRST_PTRACE(" BRST_Stream_Write\n");

    if (!(stream->write_fn))
        return BRST_Error_Set(stream->error, BRST_INVALID_OPERATION, 0);

    /*
    if (BRST_Error_GetCode(stream->error) != BRST_NOERROR)
        return BRST_THIS_FUNC_WAS_SKIPPED;
    */

    ret = stream->write_fn(stream, ptr, size);

    if (ret != BRST_OK)
        return ret;

    stream->size += size;

    return BRST_OK;
}

BRST_STATUS
BRST_Stream_WriteChar(BRST_Stream stream,
    char value)
{
    return BRST_Stream_Write(stream, (BRST_BYTE*)&value, sizeof(char));
}

BRST_STATUS
BRST_Stream_WriteStr(BRST_Stream stream,
    const char* value)
{
    BRST_UINT len = BRST_StrLen(value, -1);

    return BRST_Stream_Write(stream, (BRST_BYTE*)value, len);
}

BRST_STATUS
BRST_Stream_WriteUChar(BRST_Stream stream,
    BRST_BYTE value)
{
    return BRST_Stream_Write(stream, &value, sizeof(BRST_BYTE));
}

BRST_STATUS
BRST_Stream_WriteInt(BRST_Stream stream,
    BRST_INT value)
{
    char buf[BRST_INT_LEN + 1];

    char* p = BRST_IToA(buf, value, buf + BRST_INT_LEN);

    return BRST_Stream_Write(stream, (BRST_BYTE*)buf, (BRST_UINT)(p - buf));
}

BRST_STATUS
BRST_Stream_WriteUInt(BRST_Stream stream,
    BRST_UINT value)
{
    return BRST_Stream_WriteInt(stream, (BRST_INT)value);
}

BRST_STATUS
BRST_Stream_WriteReal(BRST_Stream stream,
    BRST_REAL value)
{
    char buf[BRST_REAL_LEN + 1];

    char* p = BRST_FToA(buf, value, buf + BRST_REAL_LEN);

    return BRST_Stream_Write(stream, (BRST_BYTE*)buf, (BRST_UINT)(p - buf));
}

void BRST_Stream_Free(BRST_Stream stream)
{
    if (!stream)
        return;

    if (stream->free_fn)
        stream->free_fn(stream);

    stream->sig_bytes = 0;

    BRST_FreeMem(stream->mmgr, stream);
}

BRST_STATUS
BRST_Stream_Seek(BRST_Stream stream,
    BRST_INT pos,
    BRST_WhenceMode mode)
{
    BRST_PTRACE(" BRST_Stream_Seek\n");

    if (!(stream->seek_fn))
        return BRST_Error_Set(stream->error, BRST_INVALID_OPERATION, 0);

    if (BRST_Error_Code(stream->error) != 0)
        return BRST_THIS_FUNC_WAS_SKIPPED;

    return stream->seek_fn(stream, pos, mode);
}

BRST_INT32
BRST_Stream_Tell(BRST_Stream stream)
{
    BRST_PTRACE(" BRST_Stream_Tell\n");

    if (!(stream->tell_fn))
        return BRST_Error_Set(stream->error, BRST_INVALID_OPERATION, 0);

    if (BRST_Error_Code(stream->error) != 0)
        return BRST_THIS_FUNC_WAS_SKIPPED;

    return stream->tell_fn(stream);
}

BRST_UINT32
BRST_Stream_Size(BRST_Stream stream)
{
    BRST_PTRACE(" BRST_Stream_Tell\n");

    if (stream->write_fn)
        return stream->size;

    if (!(stream->size_fn)) {
        BRST_Error_Set(stream->error, BRST_INVALID_OPERATION, 0);
        return 0;
    }

    if (BRST_Error_Code(stream->error) != 0)
        return 0;

    return stream->size_fn(stream);
}

BRST_STATUS
BRST_Stream_WriteEscapeName(BRST_Stream stream,
    const char* value)
{
    char tmp_char[BRST_LIMIT_MAX_NAME_LEN * 3 + 2];
    BRST_UINT len;
    BRST_INT i;
    const BRST_BYTE* pos1;
    char* pos2;

    BRST_PTRACE(" BRST_Stream_WriteEscapeName\n");

    len  = BRST_StrLen(value, BRST_LIMIT_MAX_NAME_LEN);
    pos1 = (BRST_BYTE*)value;
    pos2 = tmp_char;

    *pos2++ = '/';
    for (i = 0; i < (BRST_INT32)len; i++) {
        BRST_BYTE c = *pos1++;
        if (BRST_NEEDS_ESCAPE(c)) {
            *pos2++ = '#';
            *pos2   = (char)(c >> 4);
            if (*pos2 <= 9)
                *pos2 += 0x30;
            else
                *pos2 += 0x41 - 10;
            pos2++;

            *pos2 = (char)(c & 0x0f);
            if (*pos2 <= 9)
                *pos2 += 0x30;
            else
                *pos2 += 0x41 - 10;
            pos2++;
        } else
            *pos2++ = c;
    }
    *pos2 = 0;

    return BRST_Stream_Write(stream, (BRST_BYTE*)tmp_char, BRST_StrLen(tmp_char, -1));
}

BRST_STATUS
BRST_Stream_WriteEscapeText2(BRST_Stream stream,
    const char* text,
    BRST_UINT len)
{
    char buf[BRST_TEXT_DEFAULT_LEN];
    BRST_UINT idx = 0;
    BRST_INT i;
    const char* p = text;
    BRST_STATUS ret;

    BRST_PTRACE(" BRST_Stream_WriteEscapeText2\n");

    /* The following block is commented out because it violates "PDF Spec 7.3.4.2 Literal Strings".
     * It states that the two matching parentheses must still be present to represent an empty
     * string of zero length.
     */
    /*
     if (!len)
         return BRST_OK;
    */

    buf[idx++] = '(';

    for (i = 0; i < (BRST_INT)len; i++) {
        BRST_BYTE c = (BRST_BYTE)*p++;
        if (BRST_NEEDS_ESCAPE(c)) {
            buf[idx++] = '\\';

            buf[idx] = (char)(c >> 6);
            buf[idx] += 0x30;
            idx++;
            buf[idx] = (char)((c & 0x38) >> 3);
            buf[idx] += 0x30;
            idx++;
            buf[idx] = (char)(c & 0x07);
            buf[idx] += 0x30;
            idx++;
        } else
            buf[idx++] = c;

        if (idx > BRST_TEXT_DEFAULT_LEN - 4) {
            ret = BRST_Stream_Write(stream, (BRST_BYTE*)buf, idx);
            if (ret != BRST_OK)
                return ret;
            idx = 0;
        }
    }
    buf[idx++] = ')';

    ret = BRST_Stream_Write(stream, (BRST_BYTE*)buf, idx);

    return ret;
}

BRST_STATUS
BRST_Stream_WriteEscapeText(BRST_Stream stream,
    const char* text)
{
    BRST_UINT len;

    BRST_PTRACE(" BRST_Stream_WriteEscapeText\n");

    len = (text == NULL) ? 0 : BRST_StrLen(text, BRST_LIMIT_MAX_STRING_LEN);

    return BRST_Stream_WriteEscapeText2(stream, text, len);
}

BRST_Stream
BRST_FileReader_New(BRST_MMgr mmgr,
    const char* fname)
{
    BRST_Stream stream;
    BRST_FILEP fp = BRST_FOPEN(fname, "rb");

    BRST_PTRACE(" BRST_FileReader_New\n");

    if (!fp) {
#ifdef UNDER_CE
        BRST_Error_Set(BRST_MMgr_Error(mmgr), BRST_FILE_OPEN_ERROR, GetLastError());
#else
        BRST_Error_Set(BRST_MMgr_Error(mmgr), BRST_FILE_OPEN_ERROR, errno);
#endif
        return NULL;
    }

    stream = (BRST_Stream)BRST_GetMem(mmgr, sizeof(BRST_Stream_Rec));

    if (stream) {
        BRST_MemSet(stream, 0, sizeof(BRST_Stream_Rec));
        stream->sig_bytes = BRST_STREAM_SIG_BYTES;
        stream->type      = BRST_STREAM_FILE;
        stream->error     = BRST_MMgr_Error(mmgr);
        stream->mmgr      = mmgr;
        stream->read_fn   = BRST_FileReader_ReadFunc;
        stream->seek_fn   = BRST_FileReader_SeekFunc;
        stream->tell_fn   = BRST_FileStream_TellFunc;
        stream->size_fn   = BRST_FileStream_SizeFunc;
        stream->free_fn   = BRST_FileStream_FreeFunc;
        stream->attr      = fp;
    }

    return stream;
}

/*
 *  BRST_FileReader_ReadFunc
 *
 *  Reading data function for BRST_FileReader.
 *
 */

BRST_STATUS
BRST_FileReader_ReadFunc(BRST_Stream stream,
    BRST_BYTE* ptr,
    BRST_UINT* size)
{
    BRST_FILEP fp = (BRST_FILEP)stream->attr;
    BRST_UINT rsize;

    BRST_PTRACE(" BRST_FileReader_ReadFunc\n");

    BRST_MemSet(ptr, 0, *size);
    rsize = (BRST_UINT)BRST_FREAD(ptr, 1, *size, fp);

    if (rsize != *size) {
        if (BRST_FEOF(fp)) {

            *size = rsize;

            return BRST_STREAM_EOF;
        }

        return BRST_Error_Set(stream->error, BRST_FILE_IO_ERROR, BRST_FERROR(fp));
    }

    return BRST_OK;
}

/*
 *  BRST_FileReader_SeekFunc
 *
 *  Seeking data function for BRST_FileReader.
 *
 *  stream : Pointer to a BRST_Stream object.
 *  pos : New position of stream object.
 *  BRST_whence_mode : Seeking mode describing below.
 *                     BRST_SEEK_SET : Absolute file position
 *                     BRST_SEEK_CUR : Relative to the current file position
 *                     BRST_SEEK_END : Relative to the current end of file.
 *
 *  BRST_FileReader_seek_fn returns BRST_OK when successful. On failure
 *  the result is BRST_FILE_IO_ERROR and BRST_Error_GetCode2() returns the
 *  error which returned by file seeking function of platform.
 *
 */

BRST_STATUS
BRST_FileReader_SeekFunc(BRST_Stream stream,
    BRST_INT pos,
    BRST_WhenceMode mode)
{
    BRST_FILEP fp = (BRST_FILEP)stream->attr;
    BRST_INT whence;

    BRST_PTRACE(" BRST_FileReader_SeekFunc\n");

    switch (mode) {
    case BRST_SEEK_CUR:
        whence = SEEK_CUR;
        break;
    case BRST_SEEK_END:
        whence = SEEK_END;
        break;
    default:
        whence = SEEK_SET;
    }

    if (BRST_FSEEK(fp, pos, whence) != 0) {
        return BRST_Error_Set(stream->error, BRST_FILE_IO_ERROR, BRST_FERROR(fp));
    }

    return BRST_OK;
}

BRST_INT32
BRST_FileStream_TellFunc(BRST_Stream stream)
{
    BRST_INT32 ret;
    BRST_FILEP fp = (BRST_FILEP)stream->attr;

    BRST_PTRACE(" BRST_FileReader_TellFunc\n");

    if ((ret = BRST_FTELL(fp)) < 0) {
        return BRST_Error_Set(stream->error, BRST_FILE_IO_ERROR,
            BRST_FERROR(fp));
    }

    return ret;
}

BRST_UINT32
BRST_FileStream_SizeFunc(BRST_Stream stream)
{
    BRST_INT size;
    BRST_INT ptr;
    BRST_FILEP fp = (BRST_FILEP)stream->attr;

    BRST_PTRACE(" BRST_FileReader_SizeFunc\n");

    /* save current file-pointer */
    if ((ptr = BRST_FTELL(fp)) < 0) {
        BRST_Error_Set(stream->error, BRST_FILE_IO_ERROR,
            BRST_FERROR(fp));
        return 0;
    }

    /* move file-pointer to the end of the file */
    if (BRST_FSEEK(fp, 0, SEEK_END) < 0) {
        BRST_Error_Set(stream->error, BRST_FILE_IO_ERROR,
            BRST_FERROR(fp));
        return 0;
    }

    /* get the pointer of the end of the file */
    if ((size = BRST_FTELL(fp)) < 0) {
        BRST_Error_Set(stream->error, BRST_FILE_IO_ERROR,
            BRST_FERROR(fp));
        return 0;
    }

    /* restore current file-pointer */
    if (BRST_FSEEK(fp, ptr, SEEK_SET) < 0) {
        BRST_Error_Set(stream->error, BRST_FILE_IO_ERROR,
            BRST_FERROR(fp));
        return 0;
    }

    return (BRST_UINT32)size;
}

BRST_Stream
BRST_FileWriter_New(BRST_MMgr mmgr,
    const char* fname)
{
    BRST_Stream stream;
    BRST_FILEP fp = BRST_FOPEN(fname, "wb");

    BRST_PTRACE(" BRST_FileWriter_New\n");

    if (!fp) {
#ifdef UNDER_CE
        BRST_Error_Set(BRST_MMgr_Error(mmgr), BRST_FILE_OPEN_ERROR, GetLastError());
#else
        BRST_Error_Set(BRST_MMgr_Error(mmgr), BRST_FILE_OPEN_ERROR, errno);
#endif
        return NULL;
    }

    stream = (BRST_Stream)BRST_GetMem(mmgr, sizeof(BRST_Stream_Rec));

    if (stream) {
        BRST_MemSet(stream, 0, sizeof(BRST_Stream_Rec));
        stream->sig_bytes = BRST_STREAM_SIG_BYTES;
        stream->error     = BRST_MMgr_Error(mmgr);
        stream->mmgr      = mmgr;
        stream->write_fn  = BRST_FileWriter_WriteFunc;
        stream->free_fn   = BRST_FileStream_FreeFunc;
        stream->tell_fn   = BRST_FileStream_TellFunc;
        stream->attr      = fp;
        stream->type      = BRST_STREAM_FILE;
    }

    return stream;
}

BRST_STATUS
BRST_FileWriter_WriteFunc(BRST_Stream stream,
    const BRST_BYTE* ptr,
    BRST_UINT size)
{
    BRST_FILEP fp;
    BRST_UINT ret;

    BRST_PTRACE(" BRST_FileWriter_WriteFunc\n");

    fp  = (BRST_FILEP)stream->attr;
    ret = (BRST_UINT)BRST_FWRITE(ptr, 1, size, fp);

    if (ret != size) {
        return BRST_Error_Set(stream->error, BRST_FILE_IO_ERROR, BRST_FERROR(fp));
    }

    return BRST_OK;
}

void BRST_FileStream_FreeFunc(BRST_Stream stream)
{
    BRST_FILEP fp;

    BRST_PTRACE(" BRST_FileStream_FreeFunc\n");

    fp = (BRST_FILEP)stream->attr;

    if (fp)
        BRST_FCLOSE(fp);

    stream->attr = NULL;
}

BRST_STATUS
BRST_MemStream_InWrite(BRST_Stream stream,
    const BRST_BYTE** ptr,
    BRST_UINT* count)
{
    BRST_MemStreamAttr attr = (BRST_MemStreamAttr)stream->attr;
    BRST_UINT rsize         = attr->buf_size - attr->w_pos;

    BRST_PTRACE(" BRST_MemStream_InWrite\n");

    if (*count <= 0)
        return BRST_OK;

    if (rsize >= *count) {
        BRST_MemCopy(attr->w_ptr, *ptr, *count);
        attr->w_ptr += *count;
        attr->w_pos += *count;
        *count = 0;
    } else {
        if (rsize > 0) {
            BRST_MemCopy(attr->w_ptr, *ptr, rsize);
            *ptr += rsize;
            *count -= rsize;
        }
        attr->w_ptr = (BRST_BYTE*)BRST_GetMem(stream->mmgr, attr->buf_size);

        if (attr->w_ptr == NULL)
            return BRST_Error_Code(stream->error);

        if (BRST_List_Add(attr->buf, attr->w_ptr) != BRST_OK) {
            BRST_FreeMem(stream->mmgr, attr->w_ptr);
            attr->w_ptr = NULL;

            return BRST_Error_Code(stream->error);
        }
        attr->w_pos = 0;
    }
    return BRST_OK;
}

BRST_STATUS
BRST_MemStream_WriteFunc(BRST_Stream stream,
    const BRST_BYTE* ptr,
    BRST_UINT size)
{
    BRST_UINT wsize = size;

    BRST_PTRACE(" BRST_MemStream_WriteFunc\n");

    if (BRST_Error_Code(stream->error) != 0)
        return BRST_THIS_FUNC_WAS_SKIPPED;

    while (wsize > 0) {
        BRST_STATUS ret = BRST_MemStream_InWrite(stream, &ptr, &wsize);
        if (ret != BRST_OK)
            return ret;
    }

    return BRST_OK;
}

BRST_INT32
BRST_MemStream_TellFunc(BRST_Stream stream)
{
    BRST_INT32 ret;
    BRST_MemStreamAttr attr = (BRST_MemStreamAttr)stream->attr;

    BRST_PTRACE(" BRST_MemStream_TellFunc\n");

    ret = attr->r_ptr_idx * attr->buf_size;
    ret += attr->r_pos;

    return ret;
}

BRST_UINT32
BRST_MemStream_SizeFunc(BRST_Stream stream)
{
    BRST_PTRACE(" BRST_MemStream_SizeFunc\n");

    return stream->size;
}

BRST_STATUS
BRST_MemStream_SeekFunc(BRST_Stream stream,
    BRST_INT pos,
    BRST_WhenceMode mode)
{
    BRST_MemStreamAttr attr = (BRST_MemStreamAttr)stream->attr;

    BRST_PTRACE(" BRST_MemStream_SeekFunc\n");

    if (mode == BRST_SEEK_CUR) {
        pos += (attr->r_ptr_idx * attr->buf_size);
        pos += attr->r_pos;
    } else if (mode == BRST_SEEK_END)
        pos = stream->size - pos;

    if (pos > (BRST_INT)stream->size) {
        return BRST_Error_Set(stream->error, BRST_STREAM_EOF, 0);
    }

    if (stream->size == 0) {
        return BRST_OK;
    }

    attr->r_ptr_idx = pos / attr->buf_size;
    attr->r_pos     = pos % attr->buf_size;
    attr->r_ptr     = (BRST_BYTE*)BRST_List_ItemAt(attr->buf, attr->r_ptr_idx);
    if (attr->r_ptr != NULL)
        attr->r_ptr += attr->r_pos;

    return BRST_OK;
}

BRST_BYTE*
BRST_MemStream_GetBufPtr(BRST_Stream stream,
    BRST_UINT index,
    BRST_UINT* length)
{
    BRST_BYTE* ret;
    BRST_MemStreamAttr attr;

    BRST_PTRACE(" BRST_MemStream_GetBufPtr\n");

    if (stream->type != BRST_STREAM_MEMORY) {
        BRST_Error_Set(stream->error, BRST_INVALID_OBJECT, 0);
        return NULL;
    }

    attr = (BRST_MemStreamAttr)stream->attr;

    ret = (BRST_BYTE*)BRST_List_ItemAt(attr->buf, index);
    if (ret == NULL) {
        BRST_Error_Set(stream->error, BRST_INVALID_PARAMETER, 0);
        *length = 0;
        return NULL;
    }

    *length = (BRST_List_Count(attr->buf) - 1 == index) ? attr->w_pos : attr->buf_size;
    return ret;
}

void BRST_MemStream_FreeData(BRST_Stream stream)
{
    BRST_MemStreamAttr attr;
    BRST_UINT i;

    BRST_PTRACE(" BRST_MemStream_FreeData\n");

    if (!stream || stream->type != BRST_STREAM_MEMORY)
        return;

    attr = (BRST_MemStreamAttr)stream->attr;

    for (i = 0; i < BRST_List_Count(attr->buf); i++)
        BRST_FreeMem(stream->mmgr, BRST_List_ItemAt(attr->buf, i));

    BRST_List_Clear(attr->buf);

    stream->size    = 0;
    attr->w_pos     = attr->buf_size;
    attr->w_ptr     = NULL;
    attr->r_ptr_idx = 0;
    attr->r_pos     = 0;
}

void BRST_MemStream_FreeFunc(BRST_Stream stream)
{
    BRST_MemStreamAttr attr;

    BRST_PTRACE(" BRST_MemStream_FreeFunc\n");

    attr = (BRST_MemStreamAttr)stream->attr;
    BRST_MemStream_FreeData(stream);
    BRST_List_Free(attr->buf);
    BRST_FreeMem(stream->mmgr, attr);
    stream->attr = NULL;
}

BRST_Stream
BRST_MemStream_New(BRST_MMgr mmgr,
    BRST_UINT buf_size)
{
    BRST_Stream stream;

    BRST_PTRACE(" BRST_MemStream_New\n");

    /* Create new BRST_Stream object. */
    stream = (BRST_Stream)BRST_GetMem(mmgr, sizeof(BRST_Stream_Rec));

    if (stream) {
        /* Create attribute struct. */
        BRST_MemStreamAttr attr = (BRST_MemStreamAttr)BRST_GetMem(mmgr,
            sizeof(BRST_MemStreamAttr_Rec));

        if (!attr) {
            BRST_FreeMem(mmgr, stream);
            return NULL;
        }

        BRST_MemSet(stream, 0, sizeof(BRST_Stream_Rec));
        BRST_MemSet(attr, 0, sizeof(BRST_MemStreamAttr_Rec));

        attr->buf = BRST_List_New(mmgr, BRST_DEF_ITEMS_PER_BLOCK);
        if (!attr->buf) {
            BRST_FreeMem(mmgr, stream);
            BRST_FreeMem(mmgr, attr);
            return NULL;
        }

        stream->sig_bytes = BRST_STREAM_SIG_BYTES;
        stream->type      = BRST_STREAM_MEMORY;
        stream->error     = BRST_MMgr_Error(mmgr);
        stream->mmgr      = mmgr;
        stream->attr      = attr;
        attr->buf_size    = (buf_size > 0) ? buf_size : BRST_STREAM_BUF_SIZE;
        attr->w_pos       = attr->buf_size;

        stream->write_fn = BRST_MemStream_WriteFunc;
        stream->read_fn  = BRST_MemStream_ReadFunc;
        stream->seek_fn  = BRST_MemStream_SeekFunc;
        stream->tell_fn  = BRST_MemStream_TellFunc;
        stream->size_fn  = BRST_MemStream_SizeFunc;
        stream->free_fn  = BRST_MemStream_FreeFunc;
    }

    return stream;
}

BRST_UINT
BRST_MemStream_GetBufSize(BRST_Stream stream)
{
    BRST_MemStreamAttr attr;

    BRST_PTRACE(" BRST_MemStream_GetBufSize\n");

    if (!stream || stream->type != BRST_STREAM_MEMORY)
        return 0;

    attr = (BRST_MemStreamAttr)stream->attr;
    return attr->buf_size;
}

BRST_UINT
BRST_MemStream_GetBufCount(BRST_Stream stream)
{
    BRST_MemStreamAttr attr;

    BRST_PTRACE(" BRST_MemStream_GetBufCount\n");

    if (!stream || stream->type != BRST_STREAM_MEMORY)
        return 0;

    attr = (BRST_MemStreamAttr)stream->attr;
    return BRST_List_Count(attr->buf);
}

BRST_STATUS
BRST_MemStream_ReadFunc(BRST_Stream stream,
    BRST_BYTE* buf,
    BRST_UINT* size)
{
    BRST_MemStreamAttr attr = (BRST_MemStreamAttr)stream->attr;
    BRST_UINT buf_size;
    BRST_UINT rlen = *size;

    BRST_PTRACE(" BRST_MemStream_ReadFunc\n");

    *size = 0;

    while (rlen > 0) {
        BRST_UINT tmp_len;

        if (BRST_List_Count(attr->buf) == 0)
            return BRST_STREAM_EOF;

        if (BRST_List_Count(attr->buf) - 1 > attr->r_ptr_idx)
            tmp_len = attr->buf_size - attr->r_pos;
        else if (BRST_List_Count(attr->buf) - 1 == attr->r_ptr_idx)
            tmp_len = attr->w_pos - attr->r_pos;
        else
            return BRST_STREAM_EOF;

        if (!attr->r_ptr)
            attr->r_ptr = (BRST_BYTE*)BRST_List_ItemAt(attr->buf,
                attr->r_ptr_idx);

        if (tmp_len >= rlen) {
            BRST_MemCopy(buf, attr->r_ptr, rlen);
            attr->r_pos += rlen;
            *size += rlen;
            attr->r_ptr += rlen;
            return BRST_OK;
        } else {
            buf = BRST_MemCopy(buf, attr->r_ptr, tmp_len);
            rlen -= tmp_len;
            *size += tmp_len;

            if (attr->r_ptr_idx == BRST_List_Count(attr->buf) - 1) {
                attr->r_ptr += tmp_len;
                attr->r_pos += tmp_len;
                return BRST_STREAM_EOF;
            }

            attr->r_ptr_idx++;
            attr->r_pos = 0;
            attr->r_ptr = BRST_MemStream_GetBufPtr(stream, attr->r_ptr_idx,
                &buf_size);
        }
    }

    return BRST_OK;
}

BRST_STATUS
BRST_MemStream_Rewrite(BRST_Stream stream,
    BRST_BYTE* buf,
    BRST_UINT size)
{
    BRST_MemStreamAttr attr = (BRST_MemStreamAttr)stream->attr;
    BRST_UINT buf_size;
    BRST_UINT rlen = size;

    BRST_PTRACE(" BRST_MemStream_Rewrite\n");

    while (rlen > 0) {
        BRST_UINT tmp_len;

        if (BRST_List_Count(attr->buf) <= attr->r_ptr_idx) {
            BRST_STATUS ret = BRST_MemStream_WriteFunc(stream, buf, rlen);
            attr->r_ptr_idx = BRST_List_Count(attr->buf);
            attr->r_pos     = attr->w_pos;
            attr->r_ptr     = attr->w_ptr;
            return ret;
        } else if (BRST_List_Count(attr->buf) == attr->r_ptr_idx)
            tmp_len = attr->w_pos - attr->r_pos;
        else
            tmp_len = attr->buf_size - attr->r_pos;

        if (tmp_len >= rlen) {
            BRST_MemCopy(attr->r_ptr, buf, rlen);
            attr->r_pos += rlen;
            attr->r_ptr += rlen;
            return BRST_OK;
        } else {
            BRST_MemCopy(attr->r_ptr, buf, tmp_len);
            buf += tmp_len;
            rlen -= tmp_len;
            attr->r_ptr_idx++;

            if (BRST_List_Count(attr->buf) > attr->r_ptr_idx) {
                attr->r_pos = 0;
                attr->r_ptr = BRST_MemStream_GetBufPtr(stream, attr->r_ptr_idx,
                    &buf_size);
            }
        }
    }
    return BRST_OK;
}

/*
 *  BRST_CallbackReader_new
 *
 *  Constructor for BRST_CallbackReader.
 *
 *  mmgr : Pointer to a BRST_MMgr object.
 *  read_fn : Pointer to a user function for reading data.
 *  seek_fn : Pointer to a user function for seeking data.
 *  data : Pointer to a data which defined by user.
 *
 *  return: If success, It returns pointer to new BRST_Stream object,
 *          otherwise, it returns NULL.
 *
 */

BRST_Stream
BRST_CallbackReader_New(BRST_MMgr mmgr,
    BRST_Stream_Read_Func read_fn,
    BRST_Stream_Seek_Func seek_fn,
    BRST_Stream_Tell_Func tell_fn,
    BRST_Stream_Size_Func size_fn,
    void* data)
{
    BRST_Stream stream;

    BRST_PTRACE(" BRST_CallbackReader_New\n");

    stream = (BRST_Stream)BRST_GetMem(mmgr, sizeof(BRST_Stream_Rec));

    if (stream) {
        BRST_MemSet(stream, 0, sizeof(BRST_Stream_Rec));
        stream->sig_bytes = BRST_STREAM_SIG_BYTES;
        stream->error     = BRST_MMgr_Error(mmgr);
        stream->mmgr      = mmgr;
        stream->read_fn   = read_fn;
        stream->seek_fn   = seek_fn;
        stream->tell_fn   = tell_fn;
        stream->size_fn   = size_fn;
        stream->attr      = data;
        stream->type      = BRST_STREAM_CALLBACK;
    }

    return stream;
}

/*
 *  BRST_CallbackWriter_new
 *
 *  Constructor for BRST_CallbackWriter.
 *
 *  mmgr : Pointer to a BRST_MMgr object.
 *  read_fn : Pointer to a user function for writing data.
 *  data : Pointer to a data which defined by user.
 *
 *  return: If success, It returns pointer to new BRST_Stream object,
 *          otherwise, it returns NULL.
 *
 */

BRST_Stream
BRST_CallbackWriter_New(BRST_MMgr mmgr,
    BRST_Stream_Write_Func write_fn,
    void* data)
{
    BRST_Stream stream;

    BRST_PTRACE(" BRST_CallbackWriter_New\n");

    stream = (BRST_Stream)BRST_GetMem(mmgr, sizeof(BRST_Stream_Rec));

    if (stream) {
        BRST_MemSet(stream, 0, sizeof(BRST_Stream_Rec));
        stream->sig_bytes = BRST_STREAM_SIG_BYTES;
        stream->error     = BRST_MMgr_Error(mmgr);
        stream->mmgr      = mmgr;
        stream->write_fn  = write_fn;
        stream->attr      = data;
        stream->type      = BRST_STREAM_CALLBACK;
    }

    return stream;
}

BRST_STATUS
BRST_Stream_Validate(BRST_Stream stream)
{
    if (!stream || stream->sig_bytes != BRST_STREAM_SIG_BYTES)
        return BRST_FALSE;
    else
        return BRST_TRUE;
}

BRST_STATUS
BRST_Stream_WriteBinary(BRST_Stream stream,
    const BRST_BYTE* data,
    BRST_UINT len,
    BRST_Encrypt e)
{
    char buf[BRST_TEXT_DEFAULT_LEN];
    BRST_BYTE ebuf[BRST_TEXT_DEFAULT_LEN];
    BRST_BYTE* pbuf = NULL;
    BRST_BOOL flg   = BRST_FALSE;
    BRST_UINT idx   = 0;
    BRST_UINT i;
    const BRST_BYTE* p;
    BRST_STATUS ret = BRST_OK;

    BRST_PTRACE(" BRST_Stream_WriteBinary\n");

    if (e) {
        if (len <= BRST_TEXT_DEFAULT_LEN)
            pbuf = ebuf;
        else {
            pbuf = (BRST_BYTE*)BRST_GetMem(stream->mmgr, len);
            flg  = BRST_TRUE;
        }

        BRST_Encrypt_CryptBuf(e, data, pbuf, len);
        p = pbuf;
    } else {
        p = data;
    }

    for (i = 0; i < len; i++, p++) {
        char c = (char)(*p >> 4);

        if (c <= 9)
            c += 0x30;
        else
            c += 0x41 - 10;
        buf[idx++] = c;

        c = (char)(*p & 0x0f);
        if (c <= 9)
            c += 0x30;
        else
            c += 0x41 - 10;
        buf[idx++] = c;

        if (idx > BRST_TEXT_DEFAULT_LEN - 2) {
            ret = BRST_Stream_Write(stream, (BRST_BYTE*)buf, idx);
            if (ret != BRST_OK) {
                if (flg)
                    BRST_FreeMem(stream->mmgr, pbuf);
                return ret;
            }
            idx = 0;
        }
    }

    if (idx > 0) {
        ret = BRST_Stream_Write(stream, (BRST_BYTE*)buf, idx);
    }

    if (flg)
        BRST_FreeMem(stream->mmgr, pbuf);

    return ret;
}
BRST_STATUS
BRST_Stream_WriteToStreamWithDeflate(BRST_Stream src,
    BRST_Stream dst,
    BRST_Encrypt e)
{
#ifdef LIBBRST_HAVE_ZLIB

#define DEFLATE_BUF_SIZE ((BRST_INT)(BRST_STREAM_BUF_SIZE * 1.1) + 13)

    BRST_STATUS ret;
    BRST_BOOL flg;

    z_stream strm;
    Bytef inbuf[BRST_STREAM_BUF_SIZE];
    Bytef otbuf[DEFLATE_BUF_SIZE];
    BRST_BYTE ebuf[DEFLATE_BUF_SIZE];

    BRST_PTRACE(" BRST_Stream_WriteToStreamWithDeflate\n");

    /* initialize input stream */
    ret = BRST_Stream_Seek(src, 0, BRST_SEEK_SET);
    if (ret != BRST_OK)
        return ret;

    /* initialize decompression stream. */
    BRST_MemSet(&strm, 0x00, sizeof(z_stream));
    strm.next_out  = otbuf;
    strm.avail_out = DEFLATE_BUF_SIZE;

    ret = deflateInit_(&strm, Z_DEFAULT_COMPRESSION, ZLIB_VERSION,
        sizeof(z_stream));
    if (ret != Z_OK)
        return BRST_Error_Set(src->error, BRST_ZLIB_ERROR, ret);

    strm.next_in  = inbuf;
    strm.avail_in = 0;

    flg = BRST_FALSE;
    for (;;) {
        BRST_UINT size = BRST_STREAM_BUF_SIZE;

        ret = BRST_Stream_Read(src, inbuf, &size);

        strm.next_in  = inbuf;
        strm.avail_in = size;

        if (ret != BRST_OK) {
            if (ret == BRST_STREAM_EOF) {
                flg = BRST_TRUE;
                if (size == 0)
                    break;
            } else {
                deflateEnd(&strm);
                return ret;
            }
        }

        while (strm.avail_in > 0) {
            ret = deflate(&strm, Z_NO_FLUSH);
            if (ret != Z_OK && ret != Z_STREAM_END) {
                deflateEnd(&strm);
                return BRST_Error_Set(src->error, BRST_ZLIB_ERROR, ret);
            }

            if (strm.avail_out == 0) {
                if (e) {
                    BRST_Encrypt_CryptBuf(e, otbuf, ebuf, DEFLATE_BUF_SIZE);
                    ret = BRST_Stream_Write(dst, ebuf, DEFLATE_BUF_SIZE);
                } else
                    ret = BRST_Stream_Write(dst, otbuf, DEFLATE_BUF_SIZE);

                if (ret != BRST_OK) {
                    deflateEnd(&strm);
                    return BRST_Error_Set(src->error, BRST_ZLIB_ERROR, ret);
                }

                strm.next_out  = otbuf;
                strm.avail_out = DEFLATE_BUF_SIZE;
            }
        }

        if (flg)
            break;
    }

    flg = BRST_FALSE;
    for (;;) {
        ret = deflate(&strm, Z_FINISH);
        if (ret != Z_OK && ret != Z_STREAM_END) {
            deflateEnd(&strm);
            return BRST_Error_Set(src->error, BRST_ZLIB_ERROR, ret);
        }

        if (ret == Z_STREAM_END)
            flg = BRST_TRUE;

        if (strm.avail_out < DEFLATE_BUF_SIZE) {
            BRST_UINT osize = DEFLATE_BUF_SIZE - strm.avail_out;
            if (e) {
                BRST_Encrypt_CryptBuf(e, otbuf, ebuf, osize);
                ret = BRST_Stream_Write(dst, ebuf, osize);
            } else
                ret = BRST_Stream_Write(dst, otbuf, osize);

            if (ret != BRST_OK) {
                deflateEnd(&strm);
                return BRST_Error_Set(src->error, BRST_ZLIB_ERROR, ret);
            }

            strm.next_out  = otbuf;
            strm.avail_out = DEFLATE_BUF_SIZE;
        }

        if (flg)
            break;
    }

    deflateEnd(&strm);
    return BRST_OK;
#else /* LIBBRST_HAVE_ZLIB */
    // TODO Написать тест на отсутствие ZLIB
    BRST_UNUSED(e);
    BRST_UNUSED(dst);
    BRST_UNUSED(src);
    return BRST_UNSUPPORTED_FUNC;
#endif /* LIBBRST_HAVE_ZLIB */
}

BRST_STATUS
BRST_Stream_WriteToStream(BRST_Stream src,
    BRST_Stream dst,
    BRST_UINT filter,
    BRST_Encrypt e)
{
    BRST_STATUS ret;
    BRST_BYTE buf[BRST_STREAM_BUF_SIZE];
    BRST_BYTE ebuf[BRST_STREAM_BUF_SIZE];
    BRST_BOOL flg;

    BRST_PTRACE(" BRST_Stream_WriteToStream\n");
    BRST_UNUSED(filter);

    if (!dst || !(dst->write_fn)) {
        BRST_Error_Set(src->error, BRST_INVALID_OBJECT, 0);
        return BRST_INVALID_OBJECT;
    }

    if (BRST_Error_Code(src->error) != BRST_NOERROR || BRST_Error_Code(dst->error) != BRST_NOERROR)
        return BRST_THIS_FUNC_WAS_SKIPPED;

    /* initialize input stream */
    if (BRST_Stream_Size(src) == 0)
        return BRST_OK;

#ifdef LIBBRST_HAVE_ZLIB
    if (filter & BRST_STREAM_FILTER_FLATE_DECODE)
        return BRST_Stream_WriteToStreamWithDeflate(src, dst, e);
#endif /* LIBBRST_HAVE_ZLIB */

    ret = BRST_Stream_Seek(src, 0, BRST_SEEK_SET);
    if (ret != BRST_OK)
        return ret;

    flg = BRST_FALSE;
    for (;;) {
        BRST_UINT size = BRST_STREAM_BUF_SIZE;

        ret = BRST_Stream_Read(src, buf, &size);

        if (ret != BRST_OK) {
            if (ret == BRST_STREAM_EOF) {
                flg = BRST_TRUE;
                if (size == 0)
                    break;
            } else {
                return ret;
            }
        }

        if (e) {
            BRST_Encrypt_CryptBuf(e, buf, ebuf, size);
            ret = BRST_Stream_Write(dst, ebuf, size);
        } else {
            ret = BRST_Stream_Write(dst, buf, size);
        }

        if (ret != BRST_OK)
            return ret;

        if (flg)
            break;
    }

    return BRST_OK;
}
