#include "brst_types.h"
#include "brst_mmgr.h"
#include "brst_encoder.h"
#include "brst_encrypt.h"
#include "brst_stream.h"
#include "private/brst_stream.h"
#include "brst_mmgr.h"
#include "brst_dict.h"
#include "brst_error.h"
#include "private/brst_error.h"
#include "private/brst_list.h"
#include "private/brst_defines.h"
#include "brst_fontdef.h"
#include "private/brst_fontdef.h"
#include "private/brst_fontdef_ttf.h"
#include "private/brst_utils.h"
#include "brst_consts.h"

#define BRST_TTF_MAX_MEM_SIZE 10000

#define BRST_REQUIRED_TAGS_COUNT 13

static const char* const REQUIRED_TAGS[BRST_REQUIRED_TAGS_COUNT] = {
    "OS/2",
    "cmap",
    "cvt ",
    "fpgm",
    "glyf",
    "head",
    "hhea",
    "hmtx",
    "loca",
    "maxp",
    "name",
    "post",
    "prep"
};

static void
FreeFunc(BRST_FontDef fontdef);

static BRST_STATUS
LoadFontData(BRST_FontDef fontdef,
    BRST_Stream stream,
    BRST_BOOL embedding,
    BRST_UINT offset);

static BRST_STATUS
LoadFontData2(BRST_FontDef fontdef,
    BRST_Stream stream,
    BRST_UINT index,
    BRST_BOOL embedding);

static void
InitAttr(BRST_FontDef fontdef);

static BRST_STATUS
GetUINT32(BRST_Stream stream,
    BRST_UINT32* value);

static BRST_STATUS
GetUINT16(BRST_Stream stream,
    BRST_UINT16* value);

static BRST_STATUS
GetINT16(BRST_Stream stream,
    BRST_INT16* value);

static BRST_STATUS
WriteUINT32(BRST_Stream stream,
    BRST_UINT32 value);

static BRST_STATUS
WriteUINT16(BRST_Stream stream,
    BRST_UINT16 value);

static BRST_STATUS
WriteINT16(BRST_Stream stream,
    BRST_INT16 value);

static void
UINT32Swap(BRST_UINT32* value);

static void
UINT16Swap(BRST_UINT16* value);

static void
INT16Swap(BRST_INT16* value);

static BRST_STATUS
LoadTTFTable(BRST_FontDef fontdef);

static BRST_STATUS
ParseHead(BRST_FontDef fontdef);

static BRST_STATUS
ParseMaxp(BRST_FontDef fontdef);

static BRST_STATUS
ParseHhea(BRST_FontDef fontdef);

static BRST_STATUS
ParseCMap(BRST_FontDef fontdef);

static BRST_STATUS
ParseCMAP_format0(BRST_FontDef fontdef,
    BRST_UINT32 offset);

static BRST_STATUS
ParseCMAP_format4(BRST_FontDef fontdef,
    BRST_UINT32 offset);

static BRST_STATUS
ParseHmtx(BRST_FontDef fontdef);

static BRST_STATUS
ParseLoca(BRST_FontDef fontdef);

static BRST_STATUS
LoadUnicodeName(BRST_Stream stream,
    BRST_UINT offset,
    BRST_UINT len,
    char* buf);

static BRST_STATUS
ParseName(BRST_FontDef fontdef);

static BRST_STATUS
ParseOS2(BRST_FontDef fontdef);

static BRST_TTF_Table*
FindTable(BRST_FontDef fontdef,
    const char* tag);

static void
CleanFunc(BRST_FontDef fontdef);

static BRST_STATUS
CheckCompositeGlyph(BRST_FontDef fontdef,
    BRST_UINT16 gid);

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

static void
FreeFunc(BRST_FontDef fontdef)
{
    BRST_TTFontDefAttr attr = (BRST_TTFontDefAttr)fontdef->attr;

    BRST_PTRACE(" BRST_TTFontDef_FreeFunc\n");

    if (attr) {
        InitAttr(fontdef);

        BRST_FreeMem(fontdef->mmgr, attr);
    }
}

static void
CleanFunc(BRST_FontDef fontdef)
{
    BRST_TTFontDefAttr attr = (BRST_TTFontDefAttr)fontdef->attr;
    BRST_MemSet(attr->glyph_tbl.flgs, 0,
        sizeof(BRST_BYTE) * attr->num_glyphs);
    attr->glyph_tbl.flgs[0] = 1;
}

static void
InitAttr(BRST_FontDef fontdef)
{
    BRST_TTFontDefAttr attr = (BRST_TTFontDefAttr)fontdef->attr;

    if (attr) {
        if (attr->char_set)
            BRST_FreeMem(fontdef->mmgr, attr->char_set);

        if (attr->h_metric)
            BRST_FreeMem(fontdef->mmgr, attr->h_metric);

        if (attr->name_tbl.name_records)
            BRST_FreeMem(fontdef->mmgr, attr->name_tbl.name_records);

        if (attr->cmap.end_count)
            BRST_FreeMem(fontdef->mmgr, attr->cmap.end_count);

        if (attr->cmap.start_count)
            BRST_FreeMem(fontdef->mmgr, attr->cmap.start_count);

        if (attr->cmap.id_delta)
            BRST_FreeMem(fontdef->mmgr, attr->cmap.id_delta);

        if (attr->cmap.id_range_offset)
            BRST_FreeMem(fontdef->mmgr, attr->cmap.id_range_offset);

        if (attr->cmap.glyph_id_array)
            BRST_FreeMem(fontdef->mmgr, attr->cmap.glyph_id_array);

        if (attr->offset_tbl.table)
            BRST_FreeMem(fontdef->mmgr, attr->offset_tbl.table);

        if (attr->glyph_tbl.flgs)
            BRST_FreeMem(fontdef->mmgr, attr->glyph_tbl.flgs);

        if (attr->glyph_tbl.offsets)
            BRST_FreeMem(fontdef->mmgr, attr->glyph_tbl.offsets);

        if (attr->stream)
            BRST_Stream_Free(attr->stream);
    }
}

BRST_FontDef
BRST_TTFontDef_New(BRST_MMgr mmgr)
{
    BRST_FontDef fontdef;
    BRST_TTFontDefAttr fontdef_attr;

    BRST_PTRACE(" BRST_TTFontDef_New\n");

    if (!mmgr)
        return NULL;

    fontdef = BRST_GetMem(mmgr, sizeof(BRST_FontDef_Rec));
    if (!fontdef)
        return NULL;

    BRST_MemSet(fontdef, 0, sizeof(BRST_FontDef_Rec));
    fontdef->sig_bytes = BRST_FONTDEF_SIG_BYTES;
    fontdef->mmgr      = mmgr;
    fontdef->error     = BRST_MMgr_Error(mmgr);
    fontdef->type      = BRST_FONTDEF_TYPE_TRUETYPE;
    fontdef->clean_fn  = CleanFunc;
    fontdef->free_fn   = FreeFunc;

    fontdef_attr = BRST_GetMem(mmgr, sizeof(BRST_TTFontDefAttr_Rec));
    if (!fontdef_attr) {
        BRST_FreeMem(fontdef->mmgr, fontdef);
        return NULL;
    }

    fontdef->attr = fontdef_attr;
    BRST_MemSet((BRST_BYTE*)fontdef_attr, 0, sizeof(BRST_TTFontDefAttr_Rec));
    fontdef->flags = BRST_FONT_STD_CHARSET;

    return fontdef;
}

BRST_FontDef
BRST_TTFontDef_Load(BRST_MMgr mmgr,
    BRST_Stream stream,
    BRST_BOOL embedding)
{
    BRST_STATUS ret;
    BRST_FontDef fontdef;

    BRST_PTRACE(" BRST_TTFontDef_Load\n");

    fontdef = BRST_TTFontDef_New(mmgr);

    if (!fontdef) {
        BRST_Stream_Free(stream);
        return NULL;
    }

    ret = LoadFontData(fontdef, stream, embedding, 0);
    if (ret != BRST_OK) {
        BRST_FontDef_Free(fontdef);
        return NULL;
    }

    return fontdef;
}

BRST_FontDef
BRST_TTFontDef_Load2(BRST_MMgr mmgr,
    BRST_Stream stream,
    BRST_UINT index,
    BRST_BOOL embedding)
{
    BRST_STATUS ret;
    BRST_FontDef fontdef;

    BRST_PTRACE(" BRST_TTFontDef_Load\n");

    fontdef = BRST_TTFontDef_New(mmgr);

    if (!fontdef) {
        BRST_Stream_Free(stream);
        return NULL;
    }

    ret = LoadFontData2(fontdef, stream, index, embedding);
    if (ret != BRST_OK) {
        BRST_FontDef_Free(fontdef);
        return NULL;
    }

    return fontdef;
}

#ifdef BRST_TTF_DEBUG
static void
DumpTable(BRST_FontDef fontdef)
{
    BRST_TTFontDefAttr attr = (BRST_TTFontDefAttr)fontdef->attr;
    BRST_Stream stream;
    BRST_UINT i;

    for (i = 0; i < BRST_REQUIRED_TAGS_COUNT; i++) {
        char fname[9];
        BRST_TTF_Table* tbl = FindTable(fontdef, REQUIRED_TAGS[i]);

        if (!tbl) {
            BRST_PTRACE(" ERR: cannot seek %s\n", fname);
            return;
        }

        BRST_MemSet(fname, 0, 9);
        BRST_MemCopy(fname, REQUIRED_TAGS[i], 4);
        BRST_MemCopy(fname + 4, ".dat", 4);
        BRST_PTRACE(" %s open\n", fname);

        if (BRST_MemCmp(fname, "OS/2", 4) == 0)
            fname[2] = '_';

        stream = BRST_FileWriter_New(fontdef->mmgr, fname);

        if (!stream) {
            BRST_PTRACE(" ERR: cannot open %s\n", fname);
        } else {
            BRST_STATUS ret;
            BRST_UINT tbl_len = tbl->length;

            ret = BRST_Stream_Seek(attr->stream, tbl->offset, BRST_SEEK_SET);
            if (ret != BRST_OK) {
                BRST_PTRACE(" ERR: cannot seek \n");
                BRST_Stream_Free(stream);
                return;
            }

            for (;;) {
                BRST_BYTE buf[BRST_STREAM_BUF_SIZE];
                BRST_UINT len = BRST_STREAM_BUF_SIZE;

                if (len > tbl_len)
                    len = tbl_len;

                BRST_Stream_Read(attr->stream, buf, &len);
                if (len <= 0)
                    break;

                ret = BRST_Stream_Write(stream, buf, len);
                if (ret != BRST_OK) {
                    BRST_PTRACE(" ERR: cannot write\n");
                    break;
                }

                tbl_len -= len;
                if (tbl_len == 0)
                    break;
            }

            BRST_Stream_Free(stream);
        }
    }
}
#endif

static BRST_STATUS
LoadFontData(BRST_FontDef fontdef,
    BRST_Stream stream,
    BRST_BOOL embedding,
    BRST_UINT offset)
{
    BRST_TTFontDefAttr attr = (BRST_TTFontDefAttr)fontdef->attr;
    BRST_STATUS ret;
    BRST_TTF_Table* tbl;

    BRST_PTRACE(" BRST_TTFontDef_LoadFontData\n");

    attr->stream    = stream;
    attr->embedding = embedding;

    if ((ret = BRST_Stream_Seek(stream, offset, BRST_SEEK_SET)) != BRST_OK)
        return ret;

    if ((ret = LoadTTFTable(fontdef)) != BRST_OK)
        return ret;

#ifdef BRST_DUMP_FONTDATA
    DumpTable(fontdef);
#endif /* BRST_DUMP_FONTDATA */

    if ((ret = ParseHead(fontdef)) != BRST_OK)
        return ret;

    if ((ret = ParseMaxp(fontdef)) != BRST_OK)
        return ret;

    if ((ret = ParseHhea(fontdef)) != BRST_OK)
        return ret;

    if ((ret = ParseCMap(fontdef)) != BRST_OK)
        return ret;

    if ((ret = ParseHmtx(fontdef)) != BRST_OK)
        return ret;

    if ((ret = ParseLoca(fontdef)) != BRST_OK)
        return ret;

    if ((ret = ParseName(fontdef)) != BRST_OK)
        return ret;

    if ((ret = ParseOS2(fontdef)) != BRST_OK)
        return ret;

    tbl = FindTable(fontdef, "glyf");
    if (!tbl)
        return BRST_Error_Set(fontdef->error, BRST_TTF_MISSING_TABLE, 4);

    attr->glyph_tbl.base_offset = tbl->offset;
    fontdef->cap_height         = (BRST_UINT16)BRST_TTFontDef_CharBBox(fontdef, (BRST_UINT16)'H').top;
    fontdef->x_height           = (BRST_UINT16)BRST_TTFontDef_CharBBox(fontdef, (BRST_UINT16)'x').top;
    fontdef->missing_width      = (BRST_INT16)((BRST_UINT32)attr->h_metric[0].advance_width * 1000 / attr->header.units_per_em);

    BRST_PTRACE(" fontdef->cap_height=%d\n", fontdef->cap_height);
    BRST_PTRACE(" fontdef->x_height=%d\n", fontdef->x_height);
    BRST_PTRACE(" fontdef->missing_width=%d\n", fontdef->missing_width);

    if (!embedding) {
        BRST_Stream_Free(attr->stream);
        attr->stream = NULL;
    }

    return BRST_OK;
}

static BRST_STATUS
LoadFontData2(BRST_FontDef fontdef,
    BRST_Stream stream,
    BRST_UINT index,
    BRST_BOOL embedding)
{
    BRST_TTFontDefAttr attr = (BRST_TTFontDefAttr)fontdef->attr;
    BRST_STATUS ret;
    BRST_BYTE tag[4];
    BRST_UINT32 num_fonts;
    BRST_UINT32 offset;
    BRST_UINT size;

    BRST_PTRACE(" BRST_TTFontDef_LoadFontData2\n");

    attr->stream    = stream;
    attr->embedding = embedding;

    ret = BRST_Stream_Seek(stream, 0, BRST_SEEK_SET);
    if (ret != BRST_OK)
        return ret;

    size = 4;
    if ((ret = BRST_Stream_Read(stream, tag, &size)) != BRST_OK)
        return ret;

    if (BRST_MemCmp(tag, (BRST_BYTE*)"ttcf", 4) != 0)
        return BRST_Error_Set(fontdef->error, BRST_INVALID_TTC_FILE, 0);

    if ((ret = BRST_Stream_Seek(stream, 8, BRST_SEEK_SET)) != BRST_OK)
        return ret;

    if ((ret = GetUINT32(stream, &num_fonts)) != BRST_OK)
        return ret;

    BRST_PTRACE(" BRST_TTFontDef_LoadFontData2 num_fonts=%u\n",
        (BRST_UINT)num_fonts);

    if (index >= num_fonts)
        return BRST_Error_Set(fontdef->error, BRST_INVALID_TTC_INDEX, 0);

    /* read offset table for target font and set stream positioning to offset
     * value.
     */
    if ((ret = BRST_Stream_Seek(stream, 12 + index * 4, BRST_SEEK_SET)) != BRST_OK)
        return ret;

    if ((ret = GetUINT32(stream, &offset)) != BRST_OK)
        return ret;

    return LoadFontData(fontdef, stream, embedding, offset);
}

BRST_Box
BRST_TTFontDef_CharBBox(BRST_FontDef fontdef,
    BRST_UINT16 unicode)
{
    BRST_TTFontDefAttr attr = (BRST_TTFontDefAttr)fontdef->attr;
    BRST_UINT16 gid         = BRST_TTFontDef_Glyphid(fontdef, unicode);
    BRST_STATUS ret;
    BRST_Box bbox = BRST_ToBox(0, 0, 0, 0);
    BRST_INT16 i;
    BRST_INT m;

    if (gid == 0) {
        BRST_PTRACE(" GetCharHeight cannot get gid char=0x%04x\n", unicode);
        return bbox;
    }

    if (attr->header.index_to_loc_format == 0)
        m = 2;
    else
        m = 1;

    ret = BRST_Stream_Seek(attr->stream, attr->glyph_tbl.base_offset + attr->glyph_tbl.offsets[gid] * m + 2, BRST_SEEK_SET);

    if (ret != BRST_OK)
        return bbox;

    ret += GetINT16(attr->stream, &i);
    bbox.left = (BRST_REAL)((BRST_INT32)i * 1000 / attr->header.units_per_em);

    ret += GetINT16(attr->stream, &i);
    bbox.bottom = (BRST_REAL)((BRST_INT32)i * 1000 / attr->header.units_per_em);

    ret += GetINT16(attr->stream, &i);
    bbox.right = (BRST_REAL)((BRST_INT32)i * 1000 / attr->header.units_per_em);

    ret += GetINT16(attr->stream, &i);
    bbox.top = (BRST_REAL)((BRST_INT32)i * 1000 / attr->header.units_per_em);

    if (ret != BRST_OK)
        return BRST_ToBox(0, 0, 0, 0);

//    BRST_PTRACE(" BRST_TTFontDef_CharBBox char=0x%04X, "
//                 "box=[%f,%f,%f,%f]\n",
//        unicode, bbox.left, bbox.bottom, bbox.right,
//        bbox.top));

    return bbox;
}

static BRST_STATUS
GetUINT32(BRST_Stream stream,
    BRST_UINT32* value)
{
    BRST_STATUS ret;
    BRST_UINT size = sizeof(BRST_UINT32);

    ret = BRST_Stream_Read(stream, (BRST_BYTE*)value, &size);
    if (ret != BRST_OK) {
        *value = 0;
        return ret;
    }

    UINT32Swap(value);

    return BRST_OK;
}

static BRST_STATUS
GetUINT16(BRST_Stream stream,
    BRST_UINT16* value)
{
    BRST_STATUS ret;
    BRST_UINT size = sizeof(BRST_UINT16);

    ret = BRST_Stream_Read(stream, (BRST_BYTE*)value, &size);
    if (ret != BRST_OK) {
        *value = 0;
        return ret;
    }

    UINT16Swap(value);

    return BRST_OK;
}

static BRST_STATUS
GetINT16(BRST_Stream stream,
    BRST_INT16* value)
{
    BRST_STATUS ret;
    BRST_UINT size = sizeof(BRST_INT16);

    ret = BRST_Stream_Read(stream, (BRST_BYTE*)value, &size);
    if (ret != BRST_OK) {
        *value = 0;
        return ret;
    }

    INT16Swap(value);

    return BRST_OK;
}

static BRST_STATUS
WriteUINT32(BRST_Stream stream,
    BRST_UINT32 value)
{
    BRST_STATUS ret;
    BRST_UINT32 tmp = value;

    UINT32Swap(&tmp);

    ret = BRST_Stream_Write(stream, (BRST_BYTE*)&tmp, sizeof(tmp));
    if (ret != BRST_OK)
        return ret;

    return BRST_OK;
}

static BRST_STATUS
WriteUINT16(BRST_Stream stream,
    BRST_UINT16 value)
{
    BRST_STATUS ret;
    BRST_UINT16 tmp = value;

    UINT16Swap(&tmp);

    ret = BRST_Stream_Write(stream, (BRST_BYTE*)&tmp, sizeof(tmp));
    if (ret != BRST_OK)
        return ret;

    return BRST_OK;
}

static BRST_STATUS
WriteINT16(BRST_Stream stream,
    BRST_INT16 value)
{
    BRST_STATUS ret;
    BRST_INT16 tmp = value;

    INT16Swap(&tmp);

    ret = BRST_Stream_Write(stream, (BRST_BYTE*)&tmp, sizeof(tmp));
    if (ret != BRST_OK)
        return ret;

    return BRST_OK;
}

BRST_STATUS
LoadTTFTable(BRST_FontDef fontdef)
{
    BRST_TTFontDefAttr attr = (BRST_TTFontDefAttr)fontdef->attr;
    BRST_STATUS ret         = BRST_OK;
    BRST_INT i;
    BRST_TTF_Table* tbl;

    BRST_PTRACE(" BRST_TTFontDef_LoadTTFTable\n");

    ret += GetUINT32(attr->stream, &attr->offset_tbl.sfnt_version);
    ret += GetUINT16(attr->stream, &attr->offset_tbl.num_tables);
    ret += GetUINT16(attr->stream, &attr->offset_tbl.search_range);
    ret += GetUINT16(attr->stream, &attr->offset_tbl.entry_selector);
    ret += GetUINT16(attr->stream, &attr->offset_tbl.range_shift);

    if (ret != BRST_OK)
        return BRST_Error_Code(fontdef->error);

    if (attr->offset_tbl.num_tables * sizeof(BRST_TTF_Table) > BRST_TTF_MAX_MEM_SIZE)
        return BRST_Error_Set(fontdef->error, BRST_TTF_INVALID_FORMAT, 0);

    attr->offset_tbl.table = BRST_GetMem(fontdef->mmgr,
        sizeof(BRST_TTF_Table) * attr->offset_tbl.num_tables);
    if (!attr->offset_tbl.table)
        return BRST_Error_Code(fontdef->error);

    tbl = attr->offset_tbl.table;
    for (i = 0; i < attr->offset_tbl.num_tables; i++) {
        BRST_UINT size = 4;

        ret += BRST_Stream_Read(attr->stream, (BRST_BYTE*)tbl->tag, &size);
        ret += GetUINT32(attr->stream, &tbl->check_sum);
        ret += GetUINT32(attr->stream, &tbl->offset);
        ret += GetUINT32(attr->stream, &tbl->length);

        BRST_PTRACE(" [%d] tag=[%c%c%c%c] check_sum=%u offset=%u length=%u\n",
            i, tbl->tag[0], tbl->tag[1], tbl->tag[2], tbl->tag[3],
            (BRST_UINT)tbl->check_sum, (BRST_UINT)tbl->offset,
            (BRST_UINT)tbl->length);

        if (ret != BRST_OK)
            return BRST_Error_Code(fontdef->error);
        ;

        tbl++;
    }

    return BRST_OK;
}

static BRST_STATUS
ParseHead(BRST_FontDef fontdef)
{
    BRST_TTFontDefAttr attr = (BRST_TTFontDefAttr)fontdef->attr;
    BRST_TTF_Table* tbl     = FindTable(fontdef, "head");
    BRST_STATUS ret;
    BRST_UINT size;

    BRST_PTRACE(" BRST_TTFontDef_ParseHead\n");

    if (!tbl)
        return BRST_Error_Set(fontdef->error, BRST_TTF_MISSING_TABLE, 5);

    ret = BRST_Stream_Seek(attr->stream, tbl->offset, BRST_SEEK_SET);
    if (ret != BRST_OK)
        return ret;

    size = 4;
    ret += BRST_Stream_Read(attr->stream,
        (BRST_BYTE*)&attr->header.version_number, &size);
    ret += GetUINT32(attr->stream, &attr->header.font_revision);
    ret += GetUINT32(attr->stream, &attr->header.check_sum_adjustment);
    ret += GetUINT32(attr->stream, &attr->header.magic_number);
    ret += GetUINT16(attr->stream, &attr->header.flags);
    ret += GetUINT16(attr->stream, &attr->header.units_per_em);

    size = 8;
    ret += BRST_Stream_Read(attr->stream, attr->header.created, &size);
    size = 8;
    ret += BRST_Stream_Read(attr->stream, attr->header.modified, &size);

    ret += GetINT16(attr->stream, &attr->header.x_min);
    ret += GetINT16(attr->stream, &attr->header.y_min);
    ret += GetINT16(attr->stream, &attr->header.x_max);
    ret += GetINT16(attr->stream, &attr->header.y_max);
    ret += GetUINT16(attr->stream, &attr->header.mac_style);
    ret += GetUINT16(attr->stream, &attr->header.lowest_rec_ppem);
    ret += GetINT16(attr->stream, &attr->header.font_direction_hint);
    ret += GetINT16(attr->stream, &attr->header.index_to_loc_format);
    ret += GetINT16(attr->stream, &attr->header.glyph_data_format);

    if (ret != BRST_OK)
        return BRST_Error_Code(fontdef->error);

    fontdef->font_bbox.left   = (BRST_REAL)((BRST_INT32)attr->header.x_min * 1000 / attr->header.units_per_em);
    fontdef->font_bbox.bottom = (BRST_REAL)((BRST_INT32)attr->header.y_min * 1000 / attr->header.units_per_em);
    fontdef->font_bbox.right  = (BRST_REAL)((BRST_INT32)attr->header.x_max * 1000 / attr->header.units_per_em);
    fontdef->font_bbox.top    = (BRST_REAL)((BRST_INT32)attr->header.y_max * 1000 / attr->header.units_per_em);

    return BRST_OK;
}

static BRST_STATUS
ParseMaxp(BRST_FontDef fontdef)
{
    BRST_TTFontDefAttr attr = (BRST_TTFontDefAttr)fontdef->attr;
    BRST_TTF_Table* tbl     = FindTable(fontdef, "maxp");
    BRST_STATUS ret;

    BRST_PTRACE(" BRST_TTFontDef_ParseMaxp\n");

    if (!tbl)
        return BRST_Error_Set(fontdef->error, BRST_TTF_MISSING_TABLE, 9);

    ret = BRST_Stream_Seek(attr->stream, tbl->offset + 4, BRST_SEEK_SET);
    if (ret != BRST_OK)
        return ret;

    ret = GetUINT16(attr->stream, &attr->num_glyphs);

    BRST_PTRACE(" BRST_TTFontDef_ParseMaxp num_glyphs=%u\n",
        attr->num_glyphs);

    return ret;
}

static BRST_STATUS
ParseHhea(BRST_FontDef fontdef)
{
    BRST_TTFontDefAttr attr = (BRST_TTFontDefAttr)fontdef->attr;
    BRST_TTF_Table* tbl     = FindTable(fontdef, "hhea");
    BRST_STATUS ret;

    BRST_PTRACE(" BRST_TTFontDef_ParseHhea\n");

    if (!tbl)
        return BRST_Error_Set(fontdef->error, BRST_TTF_MISSING_TABLE, 6);

    ret = BRST_Stream_Seek(attr->stream, tbl->offset + 4, BRST_SEEK_SET);
    if (ret != BRST_OK)
        return ret;

    ret += GetINT16(attr->stream, &fontdef->ascent);
    fontdef->ascent = (BRST_INT16)((BRST_INT32)fontdef->ascent * 1000 / attr->header.units_per_em);
    ret += GetINT16(attr->stream, &fontdef->descent);
    fontdef->descent = (BRST_INT16)((BRST_INT32)fontdef->descent * 1000 / attr->header.units_per_em);

    if (ret != BRST_OK)
        return BRST_Error_Code(fontdef->error);

    ret = BRST_Stream_Seek(attr->stream, tbl->offset + 34, BRST_SEEK_SET);
    if (ret != BRST_OK)
        return ret;

    ret = GetUINT16(attr->stream, &attr->num_h_metric);
    if (ret != BRST_OK)
        return BRST_Error_Code(fontdef->error);

    BRST_PTRACE(" BRST_TTFontDef_ParseHhea num_h_metric=%u\n",
        attr->num_h_metric);

    return ret;
}

static BRST_STATUS
ParseCMap(BRST_FontDef fontdef)
{
    BRST_TTFontDefAttr attr = (BRST_TTFontDefAttr)fontdef->attr;
    BRST_TTF_Table* tbl     = FindTable(fontdef, "cmap");
    BRST_STATUS ret;
    BRST_UINT16 version;
    BRST_UINT16 num_cmap;
    BRST_UINT i;
    BRST_UINT32 ms_unicode_encoding_offset = 0;
    BRST_UINT32 byte_encoding_offset       = 0;

    BRST_PTRACE(" BRST_TTFontDef_ParseCMap\n");

    if (!tbl)
        return BRST_Error_Set(fontdef->error, BRST_TTF_MISSING_TABLE, 1);

    ret = BRST_Stream_Seek(attr->stream, tbl->offset, BRST_SEEK_SET);
    if (ret != BRST_OK)
        return ret;

    ret += GetUINT16(attr->stream, &version);
    if (ret != BRST_OK)
        return BRST_Error_Code(fontdef->error);

    if (version != 0)
        return BRST_Error_Set(fontdef->error, BRST_TTF_INVALID_FORMAT, 0);

    ret += GetUINT16(attr->stream, &num_cmap);
    if (ret != BRST_OK)
        return BRST_Error_Code(fontdef->error);

    for (i = 0; i < num_cmap; i++) {
        BRST_UINT16 platformID;
        BRST_UINT16 encodingID;
        BRST_UINT16 format;
        BRST_UINT32 offset;
        BRST_INT32 save_offset;

        ret += GetUINT16(attr->stream, &platformID);
        ret += GetUINT16(attr->stream, &encodingID);
        ret += GetUINT32(attr->stream, &offset);
        if (ret != BRST_OK)
            return BRST_Error_Code(fontdef->error);

        save_offset = BRST_Stream_Tell(attr->stream);
        if (save_offset < 0)
            return BRST_Error_Code(fontdef->error);

        ret = BRST_Stream_Seek(attr->stream, tbl->offset + offset,
            BRST_SEEK_SET);
        if (ret != BRST_OK)
            return ret;

        ret = GetUINT16(attr->stream, &format);
        if (ret != BRST_OK)
            return ret;

        BRST_PTRACE(" BRST_TTFontDef_ParseCMap tables[%d] platformID=%u "
                     "encodingID=%u format=%u offset=%u\n",
            i, platformID,
            encodingID, format, (BRST_UINT)offset);

        /* MS-Unicode-CMAP is used for priority */
        if (platformID == 3 && encodingID == 1 && format == 4) {
            ms_unicode_encoding_offset = offset;
            break;
        }

        /* Apple - see https://github.com/opentypejs/opentype.js/issues/139
           For example: Helvetica.ttc has platformID == 0 and encodingID == 1;
           HelveticaNeue.tcc has platformID == 0 and encodingID == 3 */
        if (platformID == 0 && (encodingID == 1 || encodingID == 3) && format == 4) {
            ms_unicode_encoding_offset = offset;
            break;
        }

        /* Byte-Encoding-CMAP will be used if MS-Unicode-CMAP is not found */
        if (platformID == 1 && encodingID == 0 && format == 1)
            byte_encoding_offset = offset;

        /* Apple - see https://github.com/opentypejs/opentype.js/issues/139
         *  For example: Helvetica.ttc has platformID == 0 and encodingID == 1;
         *  HelveticaNeue.tcc has platformID == 0 and encodingID == 3
         */
        if (platformID == 0 && (encodingID == 1 || encodingID == 3) && format == 4) {
            ms_unicode_encoding_offset = offset;
            break;
        }

        ret = BRST_Stream_Seek(attr->stream, save_offset, BRST_SEEK_SET);
        if (ret != BRST_OK)
            return ret;
    }

    if (ms_unicode_encoding_offset != 0) {
        BRST_PTRACE(" found microsoft unicode cmap.\n");
        ret = ParseCMAP_format4(fontdef, ms_unicode_encoding_offset + tbl->offset);
    } else if (byte_encoding_offset != 0) {
        BRST_PTRACE(" found byte encoding cmap.\n");
        ret = ParseCMAP_format0(fontdef, byte_encoding_offset + tbl->offset);
    } else {
        BRST_PTRACE(" cannot found target cmap.\n");
        return BRST_Error_Set(fontdef->error, BRST_TTF_INVALID_FORMAT, 0);
    }

    return ret;
}

static BRST_STATUS
ParseCMAP_format0(BRST_FontDef fontdef,
    BRST_UINT32 offset)
{
    BRST_TTFontDefAttr attr = (BRST_TTFontDefAttr)fontdef->attr;
    BRST_STATUS ret;
    BRST_BYTE array[256];
    BRST_UINT size;
    BRST_UINT16* parray;
    BRST_UINT i;

    BRST_PTRACE(" ParseCMAP_format0\n");

    ret = BRST_Stream_Seek(attr->stream, offset, BRST_SEEK_SET);
    if (ret != BRST_OK)
        return ret;

    ret += GetUINT16(attr->stream, &attr->cmap.format);
    ret += GetUINT16(attr->stream, &attr->cmap.length);
    ret += GetUINT16(attr->stream, &attr->cmap.language);

    if (ret != BRST_OK)
        return BRST_Error_Code(fontdef->error);

    if (attr->cmap.format != 0)
        return BRST_Error_Set(fontdef->error, BRST_TTF_INVALID_FORMAT, 0);

    size = 256;
    ret  = BRST_Stream_Read(attr->stream, array, &size);
    if (ret != BRST_OK)
        return ret;

    attr->cmap.glyph_id_array_count = 256;
    attr->cmap.glyph_id_array       = BRST_GetMem(fontdef->mmgr,
              sizeof(BRST_UINT16) * 256);
    if (!attr->cmap.glyph_id_array)
        return BRST_Error_Code(fontdef->error);

    parray = attr->cmap.glyph_id_array;
    for (i = 0; i < 256; i++) {
        *parray = attr->cmap.glyph_id_array[i];
        BRST_PTRACE(" ParseCMAP_format0 glyph_id_array[%d]=%u\n",
            i, *parray);
        parray++;
    }

    return BRST_OK;
}

static BRST_STATUS
ParseCMAP_format4(BRST_FontDef fontdef,
    BRST_UINT32 offset)
{
    BRST_TTFontDefAttr attr = (BRST_TTFontDefAttr)fontdef->attr;
    BRST_STATUS ret;
    BRST_UINT i;
    BRST_UINT16* pend_count;
    BRST_UINT16* pstart_count;
    BRST_INT16* pid_delta;
    BRST_UINT16* pid_range_offset;
    BRST_UINT16* pglyph_id_array;
    BRST_INT32 num_read;

    BRST_PTRACE(" ParseCMAP_format4\n");

    if ((ret = BRST_Stream_Seek(attr->stream, offset, BRST_SEEK_SET)) != BRST_OK)
        return ret;

    ret += GetUINT16(attr->stream, &attr->cmap.format);
    ret += GetUINT16(attr->stream, &attr->cmap.length);
    ret += GetUINT16(attr->stream, &attr->cmap.language);

    if (ret != BRST_OK)
        return BRST_Error_Code(fontdef->error);

    if (attr->cmap.format != 4)
        return BRST_Error_Set(fontdef->error, BRST_TTF_INVALID_FORMAT, 0);

    ret += GetUINT16(attr->stream, &attr->cmap.seg_count_x2);
    ret += GetUINT16(attr->stream, &attr->cmap.search_range);
    ret += GetUINT16(attr->stream, &attr->cmap.entry_selector);
    ret += GetUINT16(attr->stream, &attr->cmap.range_shift);

    if (ret != BRST_OK)
        return BRST_Error_Code(fontdef->error);

    /* end_count */
    attr->cmap.end_count = BRST_GetMem(fontdef->mmgr,
        sizeof(BRST_UINT16) * attr->cmap.seg_count_x2 / 2);
    if (!attr->cmap.end_count)
        return BRST_Error_Code(fontdef->error);

    pend_count = attr->cmap.end_count;
    for (i = 0; i < (BRST_UINT)attr->cmap.seg_count_x2 / 2; i++)
        if ((ret = GetUINT16(attr->stream, pend_count++)) != BRST_OK)
            return ret;

    if ((ret = GetUINT16(attr->stream, &attr->cmap.reserved_pad)) != BRST_OK)
        return ret;

    /* start_count */
    attr->cmap.start_count = BRST_GetMem(fontdef->mmgr,
        sizeof(BRST_UINT16) * attr->cmap.seg_count_x2 / 2);
    if (!attr->cmap.start_count)
        return BRST_Error_Code(fontdef->error);

    pstart_count = attr->cmap.start_count;
    for (i = 0; i < (BRST_UINT)attr->cmap.seg_count_x2 / 2; i++)
        if ((ret = GetUINT16(attr->stream, pstart_count++)) != BRST_OK)
            return ret;

    /* id_delta */
    attr->cmap.id_delta = BRST_GetMem(fontdef->mmgr,
        sizeof(BRST_UINT16) * attr->cmap.seg_count_x2 / 2);
    if (!attr->cmap.id_delta)
        return BRST_Error_Code(fontdef->error);

    pid_delta = attr->cmap.id_delta;
    for (i = 0; i < (BRST_UINT)attr->cmap.seg_count_x2 / 2; i++)
        if ((ret = GetINT16(attr->stream, pid_delta++)) != BRST_OK)
            return ret;

    /* id_range_offset */
    attr->cmap.id_range_offset = BRST_GetMem(fontdef->mmgr,
        sizeof(BRST_UINT16) * attr->cmap.seg_count_x2 / 2);
    if (!attr->cmap.id_range_offset)
        return BRST_Error_Code(fontdef->error);

    pid_range_offset = attr->cmap.id_range_offset;
    for (i = 0; i < (BRST_UINT)attr->cmap.seg_count_x2 / 2; i++)
        if ((ret = GetUINT16(attr->stream, pid_range_offset++)) != BRST_OK)
            return ret;

    num_read = BRST_Stream_Tell(attr->stream) - offset;
    if (num_read < 0)
        return BRST_Error_Code(fontdef->error);

    attr->cmap.glyph_id_array_count = (attr->cmap.length - num_read) / 2;

    if (attr->cmap.glyph_id_array_count > 0) {
        /* glyph_id_array */
        attr->cmap.glyph_id_array = BRST_GetMem(fontdef->mmgr,
            sizeof(BRST_UINT16) * attr->cmap.glyph_id_array_count);
        if (!attr->cmap.glyph_id_array)
            return BRST_Error_Code(fontdef->error);

        pglyph_id_array = attr->cmap.glyph_id_array;
        for (i = 0; i < attr->cmap.glyph_id_array_count; i++)
            if ((ret = GetUINT16(attr->stream, pglyph_id_array++)) != BRST_OK)
                return ret;
    } else
        attr->cmap.glyph_id_array = NULL;

#ifdef LIBBRST_DEBUG
    /* print all elements of cmap table */
    for (i = 0; i < (BRST_UINT)attr->cmap.seg_count_x2 / 2; i++) {
        BRST_PTRACE(" ParseCMAP_format4[%d] start_count=0x%04X, "
                     "end_count=0x%04X, id_delta=%d, id_range_offset=%u\n",
            i,
            attr->cmap.start_count[i], attr->cmap.end_count[i],
            attr->cmap.id_delta[i], attr->cmap.id_range_offset[i]);
    }
#endif

    return BRST_OK;
}

BRST_UINT16
BRST_TTFontDef_Glyphid(BRST_FontDef fontdef,
    BRST_UINT16 unicode)
{
    BRST_TTFontDefAttr attr = (BRST_TTFontDefAttr)fontdef->attr;
    BRST_UINT16* pend_count = attr->cmap.end_count;
    BRST_UINT seg_count     = attr->cmap.seg_count_x2 / 2;
    BRST_UINT i;

    BRST_PTRACE(" BRST_TTFontDef_Glyphid\n");

    /* format 0 */
    if (attr->cmap.format == 0) {
        unicode &= 0xFF;
        return attr->cmap.glyph_id_array[unicode];
    }

    /* format 4 */
    if (attr->cmap.seg_count_x2 == 0) {
        BRST_Error_Set(fontdef->error, BRST_TTF_INVALID_CMAP, 0);
        return 0;
    }

    for (i = 0; i < seg_count; i++) {
        if (unicode <= *pend_count)
            break;
        pend_count++;
    }

    if (attr->cmap.start_count[i] > unicode) {
        BRST_PTRACE(" BRST_TTFontDef_Glyphid undefined char(0x%04X)\n",
            unicode);
        return 0;
    }

    if (attr->cmap.id_range_offset[i] == 0) {
        BRST_PTRACE(" BRST_TTFontDef_Glyphid idx=%u code=%u "
                     " ret=%u\n",
            i, unicode,
            unicode + attr->cmap.id_delta[i]);

        return (BRST_UINT16)(unicode + attr->cmap.id_delta[i]);
    } else {
        BRST_UINT idx = attr->cmap.id_range_offset[i] / 2 + (unicode - attr->cmap.start_count[i]) - (seg_count - i);

        if (idx > attr->cmap.glyph_id_array_count) {
            BRST_PTRACE(" BRST_TTFontDef_Glyphid[%u] %u > %u\n",
                i, idx, (BRST_UINT)attr->cmap.glyph_id_array_count);
            return 0;
        } else {
            BRST_UINT16 gid = (BRST_UINT16)(attr->cmap.glyph_id_array[idx] + attr->cmap.id_delta[i]);
            BRST_PTRACE(" BRST_TTFontDef_Glyphid idx=%u unicode=0x%04X "
                         "id=%u\n",
                idx, unicode, gid);
            return gid;
        }
    }
}

BRST_INT16
BRST_TTFontDef_CharWidth(BRST_FontDef fontdef,
    BRST_UINT16 unicode)
{
    BRST_UINT16 advance_width;
    BRST_TTF_LongHorMetric hmetrics;
    BRST_TTFontDefAttr attr = (BRST_TTFontDefAttr)fontdef->attr;
    BRST_UINT16 gid         = BRST_TTFontDef_Glyphid(fontdef, unicode);

    BRST_PTRACE(" BRST_TTFontDef_CharWidth\n");

    if (gid >= attr->num_glyphs) {
        BRST_PTRACE(" BRST_TTFontDef_CharWidth WARNING gid > "
                     "num_glyphs %u > %u\n",
            gid, attr->num_glyphs);
        return fontdef->missing_width;
    }

    hmetrics = attr->h_metric[gid];

    if (!attr->glyph_tbl.flgs[gid]) {
        attr->glyph_tbl.flgs[gid] = 1;

        if (attr->embedding)
            CheckCompositeGlyph(fontdef, gid);
    }

    advance_width = (BRST_UINT16)((BRST_UINT)hmetrics.advance_width * 1000 / attr->header.units_per_em);

    return (BRST_INT16)advance_width;
}

static BRST_STATUS
CheckCompositeGlyph(BRST_FontDef fontdef,
    BRST_UINT16 gid)
{
    BRST_TTFontDefAttr attr = (BRST_TTFontDefAttr)fontdef->attr;
    BRST_UINT offset        = attr->glyph_tbl.offsets[gid];
    /* BRST_UINT len = attr->glyph_tbl.offsets[gid + 1] - offset; */
    BRST_STATUS ret;

    BRST_PTRACE(" CheckCompositeGlyph\n");

    if (attr->header.index_to_loc_format == 0)
        offset *= 2;

    offset += attr->glyph_tbl.base_offset;

    if ((ret = BRST_Stream_Seek(attr->stream, offset, BRST_SEEK_SET))
        != BRST_OK) {
        return ret;
    } else {
        BRST_INT16 num_of_contours;
        BRST_INT16 flags;
        BRST_UINT16 glyph_index;
        const BRST_UINT16 ARG_1_AND_2_ARE_WORDS    = 1;
        const BRST_UINT16 WE_HAVE_A_SCALE          = 8;
        const BRST_UINT16 MORE_COMPONENTS          = 32;
        const BRST_UINT16 WE_HAVE_AN_X_AND_Y_SCALE = 64;
        const BRST_UINT16 WE_HAVE_A_TWO_BY_TWO     = 128;

        if ((ret = GetINT16(attr->stream, &num_of_contours)) != BRST_OK)
            return ret;

        if (num_of_contours != -1)
            return BRST_OK;

        BRST_PTRACE(" CheckCompositeGlyph composite font gid=%u\n", gid);

        if ((ret = BRST_Stream_Seek(attr->stream, 8, BRST_SEEK_CUR))
            != BRST_OK)
            return ret;

        do {
            if ((ret = GetINT16(attr->stream, &flags)) != BRST_OK)
                return ret;

            if ((ret = GetUINT16(attr->stream, &glyph_index)) != BRST_OK)
                return ret;

            if (flags & ARG_1_AND_2_ARE_WORDS) {
                if ((ret = BRST_Stream_Seek(attr->stream, 4, BRST_SEEK_CUR))
                    != BRST_OK)
                    return ret;
            } else {
                if ((ret = BRST_Stream_Seek(attr->stream, 2, BRST_SEEK_CUR))
                    != BRST_OK)
                    return ret;
            }

            if (flags & WE_HAVE_A_SCALE) {
                if ((ret = BRST_Stream_Seek(attr->stream, 2, BRST_SEEK_CUR))
                    != BRST_OK)
                    return ret;
            } else if (flags & WE_HAVE_AN_X_AND_Y_SCALE) {
                if ((ret = BRST_Stream_Seek(attr->stream, 4, BRST_SEEK_CUR))
                    != BRST_OK)
                    return ret;
            } else if (flags & WE_HAVE_A_TWO_BY_TWO) {
                if ((ret = BRST_Stream_Seek(attr->stream, 8, BRST_SEEK_CUR))
                    != BRST_OK)
                    return ret;
            }

            if (glyph_index < attr->num_glyphs && !attr->glyph_tbl.flgs[glyph_index]) {
                BRST_INT32 next_glyph;

                attr->glyph_tbl.flgs[glyph_index] = 1;
                next_glyph                        = BRST_Stream_Tell(attr->stream);
                CheckCompositeGlyph(fontdef, glyph_index);
                BRST_Stream_Seek(attr->stream, next_glyph, BRST_SEEK_SET);
            }

            BRST_PTRACE(" gid=%d, num_of_contours=%d, flags=%d, "
                         "glyph_index=%d\n",
                gid, num_of_contours, flags,
                glyph_index);

        } while (flags & MORE_COMPONENTS);
    }

    return BRST_OK;
}

BRST_INT16
BRST_TTFontDef_GidWidth(BRST_FontDef fontdef,
    BRST_UINT16 gid)
{
    BRST_UINT16 advance_width;
    BRST_TTF_LongHorMetric hmetrics;
    BRST_TTFontDefAttr attr = (BRST_TTFontDefAttr)fontdef->attr;

    BRST_PTRACE(" BRST_TTFontDef_GidWidth\n");

    if (gid >= attr->num_glyphs) {
        BRST_PTRACE(" BRST_TTFontDef_GidWidth WARNING gid > "
                     "num_glyphs %u > %u\n",
            gid, attr->num_glyphs);
        return fontdef->missing_width;
    }

    hmetrics = attr->h_metric[gid];

    advance_width = (BRST_UINT16)((BRST_UINT)hmetrics.advance_width * 1000 / attr->header.units_per_em);

    BRST_PTRACE(" BRST_TTFontDef_GidWidth gid=%u, width=%u\n",
        gid, advance_width);

    return (BRST_INT16)advance_width;
}

static BRST_STATUS
ParseHmtx(BRST_FontDef fontdef)
{
    BRST_TTFontDefAttr attr = (BRST_TTFontDefAttr)fontdef->attr;
    BRST_TTF_Table* tbl     = FindTable(fontdef, "hmtx");
    BRST_STATUS ret;
    BRST_UINT i;
    BRST_UINT16 save_aw = 0;
    BRST_TTF_LongHorMetric* pmetric;

    BRST_PTRACE(" BRST_TTFontDef_ParseHtmx\n");

    if (!tbl)
        return BRST_Error_Set(fontdef->error, BRST_TTF_MISSING_TABLE, 7);

    ret = BRST_Stream_Seek(attr->stream, tbl->offset, BRST_SEEK_SET);
    if (ret != BRST_OK)
        return ret;

    /* allocate memory for a table of holizontal matrix.
     * the count of metric records is same as the number of glyphs
     */
    attr->h_metric = BRST_GetMem(fontdef->mmgr,
        sizeof(BRST_TTF_LongHorMetric) * attr->num_glyphs);

    if (!attr->h_metric)
        return BRST_Error_Code(fontdef->error);

    pmetric = attr->h_metric;
    for (i = 0; i < attr->num_h_metric; i++) {
        if ((ret = GetUINT16(attr->stream, &pmetric->advance_width)) != BRST_OK)
            return ret;

        if ((ret = GetINT16(attr->stream, &pmetric->lsb)) != BRST_OK)
            return ret;

        BRST_PTRACE(" ParseHmtx metric[%u] aw=%u lsb=%d\n", i,
            pmetric->advance_width, pmetric->lsb);

        save_aw = pmetric->advance_width;
        pmetric++;
    }

    /* pad the advance_width of remaining metrics with the value of last metric */
    while (i < attr->num_glyphs) {
        pmetric->advance_width = save_aw;

        if ((ret = GetINT16(attr->stream, &pmetric->lsb)) != BRST_OK)
            return ret;

        pmetric++;
        i++;
    }

    return BRST_OK;
}

static BRST_STATUS
ParseLoca(BRST_FontDef fontdef)
{
    BRST_TTFontDefAttr attr = (BRST_TTFontDefAttr)fontdef->attr;
    BRST_TTF_Table* tbl     = FindTable(fontdef, "loca");
    BRST_STATUS ret;
    BRST_UINT i;
    BRST_UINT32* poffset;

    BRST_PTRACE(" BRST_TTFontDef_ParseLoca\n");

    if (!tbl)
        return BRST_Error_Set(fontdef->error, BRST_TTF_MISSING_TABLE, 8);

    ret = BRST_Stream_Seek(attr->stream, tbl->offset, BRST_SEEK_SET);
    if (ret != BRST_OK)
        return ret;

    /* allocate glyph-offset-table. */
    attr->glyph_tbl.offsets = BRST_GetMem(fontdef->mmgr,
        sizeof(BRST_UINT32) * (attr->num_glyphs + 1));

    if (!attr->glyph_tbl.offsets)
        return BRST_Error_Code(fontdef->error);

    BRST_MemSet(attr->glyph_tbl.offsets, 0,
        sizeof(BRST_UINT32) * (attr->num_glyphs + 1));

    /* allocate glyph-flg-table.
     * this flgs are used to judge whether glyphs should be embedded.
     */
    attr->glyph_tbl.flgs = BRST_GetMem(fontdef->mmgr,
        sizeof(BRST_BYTE) * attr->num_glyphs);

    if (!attr->glyph_tbl.flgs)
        return BRST_Error_Code(fontdef->error);

    BRST_MemSet(attr->glyph_tbl.flgs, 0,
        sizeof(BRST_BYTE) * attr->num_glyphs);
    attr->glyph_tbl.flgs[0] = 1;

    poffset = attr->glyph_tbl.offsets;
    if (attr->header.index_to_loc_format == 0) {
        /* short version */
        for (i = 0; i <= attr->num_glyphs; i++) {
            BRST_UINT16 tmp = 0;

            if ((ret = GetUINT16(attr->stream, &tmp)) != BRST_OK)
                return ret;

            *poffset = tmp;
            poffset++;
        }
    } else {
        /* long version */
        for (i = 0; i <= attr->num_glyphs; i++) {
            if ((ret = GetUINT32(attr->stream, poffset)) != BRST_OK)
                return ret;

            poffset++;
        }
    }

#ifdef LIBBRST_DEBUG
    poffset = attr->glyph_tbl.offsets;
    for (i = 0; i <= attr->num_glyphs; i++) {
        BRST_PTRACE(" ParseLOCA offset[%u]=%u\n", i, (BRST_UINT)*poffset));
        poffset++;
    }
#endif

    return BRST_OK;
}

static BRST_STATUS
LoadUnicodeName(BRST_Stream stream,
    BRST_UINT offset,
    BRST_UINT len,
    char* buf)
{
    BRST_BYTE tmp[BRST_LIMIT_MAX_NAME_LEN * 2 + 1];
    BRST_UINT i = 0;
    BRST_UINT j = 0;
    BRST_STATUS ret;

    BRST_MemSet(buf, 0, BRST_LIMIT_MAX_NAME_LEN + 1);

    if ((ret = BRST_Stream_Seek(stream, offset, BRST_SEEK_SET)) != BRST_OK)
        return ret;

    if ((ret = BRST_Stream_Read(stream, tmp, &len))
        != BRST_OK)
        return ret;

    while (i < len) {
        i++;
        buf[j] = tmp[i];
        j++;
        i++;
    }

    return BRST_OK;
}

static BRST_STATUS
ParseName(BRST_FontDef fontdef)
{
    BRST_TTFontDefAttr attr = (BRST_TTFontDefAttr)fontdef->attr;
    BRST_TTF_Table* tbl     = FindTable(fontdef, "name");
    BRST_STATUS ret;
    BRST_UINT i;
    BRST_TTF_NameRecord* name_rec;
    BRST_UINT offset_id1  = 0;
    BRST_UINT offset_id2  = 0;
    BRST_UINT offset_id1u = 0;
    BRST_UINT offset_id2u = 0;
    BRST_UINT len_id1     = 0;
    BRST_UINT len_id2     = 0;
    BRST_UINT len_id1u    = 0;
    BRST_UINT len_id2u    = 0;
    char tmp[BRST_LIMIT_MAX_NAME_LEN + 1];

    BRST_PTRACE(" BRST_TTFontDef_ParseMaxp\n");

    if (!tbl)
        return BRST_Error_Set(fontdef->error, BRST_TTF_MISSING_TABLE, 10);

    ret = BRST_Stream_Seek(attr->stream, tbl->offset, BRST_SEEK_SET);
    if (ret != BRST_OK)
        return ret;

    ret += GetUINT16(attr->stream, &attr->name_tbl.format);
    ret += GetUINT16(attr->stream, &attr->name_tbl.count);
    ret += GetUINT16(attr->stream, &attr->name_tbl.string_offset);
    if (ret != BRST_OK)
        return BRST_Error_Code(fontdef->error);

    BRST_PTRACE(" ParseName() format=%u, count=%u, string_offset=%u\n",
        attr->name_tbl.format, attr->name_tbl.count,
        attr->name_tbl.string_offset);

    attr->name_tbl.name_records = BRST_GetMem(fontdef->mmgr,
        sizeof(BRST_TTF_NameRecord) * attr->name_tbl.count);

    if (!attr->name_tbl.name_records)
        return BRST_Error_Code(fontdef->error);

    name_rec = attr->name_tbl.name_records;

    for (i = 0; i < attr->name_tbl.count; i++) {
        ret += GetUINT16(attr->stream, &name_rec->platform_id);
        ret += GetUINT16(attr->stream, &name_rec->encoding_id);
        ret += GetUINT16(attr->stream, &name_rec->language_id);
        ret += GetUINT16(attr->stream, &name_rec->name_id);
        ret += GetUINT16(attr->stream, &name_rec->length);
        ret += GetUINT16(attr->stream, &name_rec->offset);

        if (ret != BRST_OK)
            return BRST_Error_Code(fontdef->error);

        BRST_PTRACE(" ParseName() platformID=%u, encodingID=%d, nameID=%d\n",
            name_rec->platform_id, name_rec->encoding_id,
            name_rec->name_id);

        if (name_rec->platform_id == 1 && name_rec->encoding_id == 0 && name_rec->name_id == 6) {
            offset_id1 = tbl->offset + name_rec->offset + attr->name_tbl.string_offset;
            len_id1    = name_rec->length;
        }

        if (name_rec->platform_id == 1 && name_rec->encoding_id == 0 && name_rec->name_id == 2) {
            offset_id2 = tbl->offset + name_rec->offset + attr->name_tbl.string_offset;
            len_id2    = name_rec->length;
        }

        if (name_rec->platform_id == 3 && name_rec->encoding_id == 1 && name_rec->name_id == 6 && name_rec->language_id == 0x0409) {
            offset_id1u = tbl->offset + name_rec->offset + attr->name_tbl.string_offset;
            len_id1u    = name_rec->length;
        }

        if (name_rec->platform_id == 3 && name_rec->encoding_id == 1 && name_rec->name_id == 2 && name_rec->language_id == 0x0409) {
            offset_id2u = tbl->offset + name_rec->offset + attr->name_tbl.string_offset;
            len_id2u    = name_rec->length;
        }

        name_rec++;
    }

    if ((!offset_id1 && !offset_id1u) || (!offset_id2 && !offset_id2u))
        return BRST_Error_Set(fontdef->error, BRST_TTF_INVALID_FORMAT, 0);

    if (len_id1 == 0 && len_id1u > 0)
        len_id1 = len_id1u / 2 + len_id1u % 2;

    if (len_id2 == 0 && len_id2u > 0)
        len_id2 = len_id2u / 2 + len_id2u % 2;

    if (len_id1 + len_id2 + 8 > 127)
        return BRST_Error_Set(fontdef->error, BRST_TTF_INVALID_FORMAT, 0);

    BRST_MemSet(attr->base_font, 0, BRST_LIMIT_MAX_NAME_LEN + 1);

    if (offset_id1) {
        if ((ret = BRST_Stream_Seek(attr->stream, offset_id1,
                 BRST_SEEK_SET))
            != BRST_OK)
            return ret;

        if ((ret = BRST_Stream_Read(attr->stream, (BRST_BYTE*)attr->base_font, &len_id1))
            != BRST_OK)
            return ret;
    } else {
        if ((ret = LoadUnicodeName(attr->stream, offset_id1u, len_id1u,
                 attr->base_font))
            != BRST_OK)
            return ret;
    }

    BRST_MemSet(tmp, 0, BRST_LIMIT_MAX_NAME_LEN + 1);

    if (offset_id2) {
        if ((ret = BRST_Stream_Seek(attr->stream, offset_id2, BRST_SEEK_SET))
            != BRST_OK)
            return ret;

        if ((ret = BRST_Stream_Read(attr->stream, (BRST_BYTE*)tmp, &len_id2)) != BRST_OK)
            return ret;
    } else {
        if ((ret = LoadUnicodeName(attr->stream, offset_id2u, len_id2u,
                 tmp))
            != BRST_OK)
            return ret;
    }

    /*
     * get "postscript name" of from a "name" table as BaseName.
     * if subfamily name is not "Regular", add subfamily name to BaseName.
     * if subfamily name includes the blank character, remove it.
     * if subfamily name is "Bold" or "Italic" or "BoldItalic", set flags
     * attribute.
     */
    if (BRST_MemCmp((BRST_BYTE*)tmp, (BRST_BYTE*)"Regular", 7) != 0) {
        char* dst = attr->base_font + len_id1;
        char* src = tmp;
        BRST_UINT j;

        *dst++ = ',';

        for (j = 0; j < len_id2; j++) {
            if (*src != ' ')
                *dst++ = *src++;

            if (dst >= attr->base_font + BRST_LIMIT_MAX_NAME_LEN)
                break;
        }

        *dst = 0;

        if (BRST_StrStr(tmp, "Bold", len_id2))
            fontdef->flags |= BRST_FONT_FOURCE_BOLD;
        if (BRST_StrStr(tmp, "Italic", len_id2))
            fontdef->flags |= BRST_FONT_ITALIC;
    }

    BRST_MemCopy((BRST_BYTE*)fontdef->base_font, (BRST_BYTE*)attr->base_font, BRST_LIMIT_MAX_NAME_LEN + 1);

    BRST_PTRACE("  ParseName() base_font=%s\n", attr->base_font);

    return BRST_OK;
}

static BRST_STATUS
ParseOS2(BRST_FontDef fontdef)
{
    BRST_TTFontDefAttr attr = (BRST_TTFontDefAttr)fontdef->attr;
    BRST_TTF_Table* tbl     = FindTable(fontdef, "OS/2");
    BRST_STATUS ret;
    BRST_UINT16 version;
    BRST_UINT len;

    BRST_PTRACE(" ParseOS2\n");

    if (!tbl)
        return BRST_Error_Set(fontdef->error, BRST_TTF_MISSING_TABLE, 0);

    /* get the number version. */
    ret = BRST_Stream_Seek(attr->stream, tbl->offset, BRST_SEEK_SET);
    if (ret != BRST_OK)
        return ret;

    if ((ret = GetUINT16(attr->stream, &version)) != BRST_OK)
        return ret;

    /* check whether the font is allowed to be embedded. */
    ret = BRST_Stream_Seek(attr->stream, tbl->offset + 8, BRST_SEEK_SET);
    if (ret != BRST_OK)
        return ret;

    if ((ret = GetUINT16(attr->stream, &attr->fs_type)) != BRST_OK)
        return ret;

    if (attr->fs_type & (0x0002 | 0x0100 | 0x0200) && attr->embedding)
        return BRST_Error_Set(fontdef->error, BRST_TTF_CANNOT_EMBED_FONT,
            0);

    /* get fields sfamilyclass and panose. */
    if ((ret = BRST_Stream_Seek(attr->stream, tbl->offset + 30, BRST_SEEK_SET))
        != BRST_OK)
        return ret;

    len = 2;
    if ((ret = BRST_Stream_Read(attr->stream, attr->sfamilyclass, &len)) != BRST_OK)
        return ret;

    len = 10;
    if ((ret = BRST_Stream_Read(attr->stream, attr->panose, &len)) != BRST_OK)
        return ret;

    BRST_PTRACE(" ParseOS2 sFamilyClass=%d-%d "
                 "Panose=%02X-%02X-%02X-%02X-%02X-%02X-%02X-%02X-%02X-%02X\n",
        attr->sfamilyclass[0], attr->sfamilyclass[1],
        attr->panose[0], attr->panose[1], attr->panose[2], attr->panose[3],
        attr->panose[4], attr->panose[5], attr->panose[6], attr->panose[7],
        attr->panose[8], attr->panose[9]);

    /* Class ID = 1   Oldstyle Serifs
       Class ID = 2   Transitional Serifs
       Class ID = 3   Modern Serifs
       Class ID = 4   Clarendon Serifs
       Class ID = 5   Slab Serifs
       Class ID = 6   (reserved for future use)
       Class ID = 7   Freeform Serifs
       Class ID = 8   Sans Serif
       Class ID = 9   Ornamentals
       Class ID = 10  Scripts
       Class ID = 11  (reserved for future use)
       Class ID = 12  Symbolic */
    if ((attr->sfamilyclass[0] > 0 && attr->sfamilyclass[0] < 6)
        || (attr->sfamilyclass[0] == 7))
        fontdef->flags = fontdef->flags | BRST_FONT_SERIF;

    if (attr->sfamilyclass[0] == 10)
        fontdef->flags = fontdef->flags | BRST_FONT_SCRIPT;

    if (attr->sfamilyclass[0] == 12)
        fontdef->flags = fontdef->flags | BRST_FONT_SYMBOLIC;

    /* get fields ulCodePageRange1 and ulCodePageRange2 */
    if (version > 0) {
        if ((ret = BRST_Stream_Seek(attr->stream, 36, BRST_SEEK_CUR)) != BRST_OK)
            return ret;

        if ((ret = GetUINT32(attr->stream, &attr->code_page_range1)) != BRST_OK)
            return ret;

        if ((ret = GetUINT32(attr->stream, &attr->code_page_range2)) != BRST_OK)
            return ret;
    }

    BRST_PTRACE("  ParseOS2 CodePageRange1=%08X CodePageRange2=%08X\n",
        (BRST_UINT)attr->code_page_range1,
        (BRST_UINT)attr->code_page_range2);

    return BRST_OK;
}

static BRST_STATUS
RecreateGLYF(BRST_FontDef fontdef,
    BRST_UINT32* new_offsets,
    BRST_Stream stream)
{
    BRST_UINT32 save_offset  = 0;
    BRST_UINT32 start_offset = stream->size;
    BRST_TTFontDefAttr attr  = (BRST_TTFontDefAttr)fontdef->attr;
    BRST_STATUS ret;
    BRST_INT i;

    BRST_PTRACE(" RecreateGLYF\n");

    for (i = 0; i < attr->num_glyphs; i++) {
        BRST_BYTE buf[BRST_STREAM_BUF_SIZE];

        if (attr->glyph_tbl.flgs[i] == 1) {
            BRST_UINT offset = attr->glyph_tbl.offsets[i];
            BRST_UINT len    = attr->glyph_tbl.offsets[i + 1] - offset;

            new_offsets[i] = stream->size - start_offset;
            if (attr->header.index_to_loc_format == 0) {
                new_offsets[i] /= 2;
                len *= 2;
            }

            BRST_PTRACE(" RecreateGLYF[%u] move from [%u] to [%u]\n", i,
                (BRST_UINT)attr->glyph_tbl.base_offset + offset,
                (BRST_UINT)new_offsets[i]);

            if (attr->header.index_to_loc_format == 0)
                offset *= 2;

            offset += attr->glyph_tbl.base_offset;

            if ((ret = BRST_Stream_Seek(attr->stream, offset, BRST_SEEK_SET))
                != BRST_OK)
                return ret;

            while (len > 0) {
                BRST_UINT tmp_len = (len > BRST_STREAM_BUF_SIZE) ? BRST_STREAM_BUF_SIZE : len;

                BRST_MemSet(buf, 0, tmp_len);

                if ((ret = BRST_Stream_Read(attr->stream, buf, &tmp_len))
                    != BRST_OK)
                    return ret;

                if ((ret = BRST_Stream_Write(stream, buf, tmp_len)) != BRST_OK)
                    return ret;

                len -= tmp_len;
            }

            save_offset = stream->size - start_offset;
            if (attr->header.index_to_loc_format == 0)
                save_offset /= 2;
        } else {
            new_offsets[i] = save_offset;
        }
    }

    new_offsets[attr->num_glyphs] = save_offset;

#ifdef DEBUG
    for (i = 0; i <= attr->num_glyphs; i++) {
        BRST_PTRACE(" RecreateGLYF[%u] offset=%u\n", i, new_offsets[i]));
    }
#endif

    return BRST_OK;
}

static BRST_STATUS
RecreateName(BRST_FontDef fontdef,
    BRST_Stream stream)
{
    BRST_TTFontDefAttr attr = (BRST_TTFontDefAttr)fontdef->attr;
    BRST_TTF_Table* tbl     = FindTable(fontdef, "name");
    BRST_STATUS ret         = BRST_OK;
    BRST_UINT i;
    BRST_TTF_NameRecord* name_rec;
    BRST_Stream tmp_stream = BRST_MemStream_New(fontdef->mmgr,
        BRST_STREAM_BUF_SIZE);

    BRST_PTRACE(" RecreateName\n");

    if (!tmp_stream)
        return BRST_Error_Code(fontdef->error);

    ret += WriteUINT16(stream, attr->name_tbl.format);
    ret += WriteUINT16(stream, attr->name_tbl.count);
    ret += WriteUINT16(stream, attr->name_tbl.string_offset);

    if (ret != BRST_OK) {
        BRST_Stream_Free(tmp_stream);
        return BRST_Error_Code(fontdef->error);
    }

    name_rec = attr->name_tbl.name_records;
    for (i = 0; i < attr->name_tbl.count; i++) {
        BRST_UINT name_len = name_rec->length;
        BRST_BYTE buf[BRST_STREAM_BUF_SIZE];
        BRST_UINT tmp_len    = name_len;
        BRST_UINT offset     = tbl->offset + attr->name_tbl.string_offset + name_rec->offset;
        BRST_UINT rec_offset = tmp_stream->size;

        /* add suffix to font-name. */
        if (name_rec->name_id == 1 || name_rec->name_id == 4) {
            if (name_rec->platform_id == 0 || name_rec->platform_id == 3) {
                ret += BRST_Stream_Write(tmp_stream, (BRST_BYTE*)attr->tag_name2,
                    sizeof(attr->tag_name2));
                name_len += sizeof(attr->tag_name2);
            } else {
                ret += BRST_Stream_Write(tmp_stream, (BRST_BYTE*)attr->tag_name,
                    sizeof(attr->tag_name));
                name_len += sizeof(attr->tag_name);
            }
        }

        ret += WriteUINT16(stream, name_rec->platform_id);
        ret += WriteUINT16(stream, name_rec->encoding_id);
        ret += WriteUINT16(stream, name_rec->language_id);
        ret += WriteUINT16(stream, name_rec->name_id);
        ret += WriteUINT16(stream, (BRST_UINT16)name_len);
        ret += WriteUINT16(stream, (BRST_UINT16)rec_offset);

        ret += BRST_Stream_Seek(attr->stream, offset, BRST_SEEK_SET);

        if (ret != BRST_OK) {
            BRST_Stream_Free(tmp_stream);
            return BRST_Error_Code(fontdef->error);
        }

        while (tmp_len > 0) {
            BRST_UINT len = (tmp_len > BRST_STREAM_BUF_SIZE) ? BRST_STREAM_BUF_SIZE : tmp_len;

            if ((ret = BRST_Stream_Read(attr->stream, buf, &len)) != BRST_OK) {
                BRST_Stream_Free(tmp_stream);
                return ret;
            }

            if ((ret = BRST_Stream_Write(tmp_stream, buf, len)) != BRST_OK) {
                BRST_Stream_Free(tmp_stream);
                return ret;
            }

            tmp_len -= len;
        }

        BRST_PTRACE(" RecreateNAME name_rec[%u] platform_id=%u "
                     "encoding_id=%u language_id=%u name_rec->name_id=%u "
                     "length=%u offset=%u\n",
            i, name_rec->platform_id,
            name_rec->encoding_id, name_rec->language_id,
            name_rec->name_id, name_len, rec_offset);

        name_rec++;
    }

    ret = BRST_Stream_WriteToStream(tmp_stream, stream,
        BRST_STREAM_FILTER_NONE, NULL);

    BRST_Stream_Free(tmp_stream);

    return ret;
}

static BRST_STATUS
WriteHeader(BRST_FontDef fontdef,
    BRST_Stream stream,
    BRST_UINT32* check_sum_ptr)
{
    BRST_TTFontDefAttr attr = (BRST_TTFontDefAttr)fontdef->attr;
    BRST_STATUS ret         = BRST_OK;

    BRST_PTRACE(" WriteHeader\n");

    ret += BRST_Stream_Write(stream, attr->header.version_number, 4);
    ret += WriteUINT32(stream, attr->header.font_revision);

    /* save the address of checkSumAdjustment.
     * the value is rewrite to computed value after new check-sum-value is
     * generated.
     */
    *check_sum_ptr = stream->size;

    ret += WriteUINT32(stream, 0);
    ret += WriteUINT32(stream, attr->header.magic_number);
    ret += WriteUINT16(stream, attr->header.flags);
    ret += WriteUINT16(stream, attr->header.units_per_em);
    ret += BRST_Stream_Write(stream, attr->header.created, 8);
    ret += BRST_Stream_Write(stream, attr->header.modified, 8);
    ret += WriteINT16(stream, attr->header.x_min);
    ret += WriteINT16(stream, attr->header.y_min);
    ret += WriteINT16(stream, attr->header.x_max);
    ret += WriteINT16(stream, attr->header.y_max);
    ret += WriteUINT16(stream, attr->header.mac_style);
    ret += WriteUINT16(stream, attr->header.lowest_rec_ppem);
    ret += WriteINT16(stream, attr->header.font_direction_hint);
    ret += WriteINT16(stream, attr->header.index_to_loc_format);
    ret += WriteINT16(stream, attr->header.glyph_data_format);

    if (ret != BRST_OK)
        return BRST_Error_Code(fontdef->error);

    return BRST_OK;
}

BRST_STATUS
BRST_TTFontDef_SaveFontData(BRST_FontDef fontdef,
    BRST_Stream stream)
{
    BRST_TTFontDefAttr attr = (BRST_TTFontDefAttr)fontdef->attr;
    BRST_TTF_Table tmp_tbl[BRST_REQUIRED_TAGS_COUNT];
    BRST_Stream tmp_stream;
    BRST_UINT32* new_offsets;
    BRST_UINT i;
    BRST_UINT32 check_sum_ptr = 0;
    BRST_STATUS ret;
    BRST_UINT32 offset_base;
    BRST_UINT32 tmp_check_sum = 0xB1B0AFBA;
    BRST_TTF_Table emptyTable;
    emptyTable.length = 0;
    emptyTable.offset = 0;

    BRST_PTRACE(" SaveFontData\n");

    ret = WriteUINT32(stream, attr->offset_tbl.sfnt_version);
    ret += WriteUINT16(stream, BRST_REQUIRED_TAGS_COUNT);
    ret += WriteUINT16(stream, attr->offset_tbl.search_range);
    ret += WriteUINT16(stream, attr->offset_tbl.entry_selector);
    ret += WriteUINT16(stream, attr->offset_tbl.range_shift);

    if (ret != BRST_OK)
        return BRST_Error_Code(fontdef->error);

    tmp_stream = BRST_MemStream_New(fontdef->mmgr, BRST_STREAM_BUF_SIZE);
    if (!tmp_stream)
        return BRST_Error_Code(fontdef->error);

    offset_base = 12 + 16 * BRST_REQUIRED_TAGS_COUNT;

    new_offsets = BRST_GetMem(fontdef->mmgr,
        sizeof(BRST_UINT32) * (attr->num_glyphs + 1));
    if (!new_offsets) {
        BRST_Stream_Free(tmp_stream);
        return BRST_Error_Code(fontdef->error);
    }

    for (i = 0; i < BRST_REQUIRED_TAGS_COUNT; i++) {
        BRST_TTF_Table* tbl = FindTable(fontdef, REQUIRED_TAGS[i]);
        BRST_UINT32 length;
        BRST_UINT new_offset;
        BRST_UINT32* poffset;
        BRST_UINT32 value;

        if (!tbl) {
            tbl = &emptyTable;
            BRST_MemCopy((BRST_BYTE*)tbl->tag,
                (const BRST_BYTE*)REQUIRED_TAGS[i], 4);
        }

        if (!tbl) {
            ret = BRST_Error_Set(fontdef->error, BRST_TTF_MISSING_TABLE, i);
            goto Exit;
        }

        ret = BRST_Stream_Seek(attr->stream, tbl->offset, BRST_SEEK_SET);
        if (ret != BRST_OK)
            goto Exit;

        length     = tbl->length;
        new_offset = tmp_stream->size;

        if (BRST_MemCmp((BRST_BYTE*)tbl->tag, (BRST_BYTE*)"head", 4) == 0) {
            ret = WriteHeader(fontdef, tmp_stream, &check_sum_ptr);
        } else if (BRST_MemCmp((BRST_BYTE*)tbl->tag, (BRST_BYTE*)"glyf", 4) == 0) {
            ret = RecreateGLYF(fontdef, new_offsets, tmp_stream);
        } else if (BRST_MemCmp((BRST_BYTE*)tbl->tag, (BRST_BYTE*)"hmtx", 4) == 0) {
            BRST_UINT j;
            BRST_TTF_LongHorMetric* pmetric;

            BRST_MemSet(&value, 0, 4);
            pmetric = attr->h_metric;
            for (j = 0; j < attr->num_h_metric; j++) {
                // write all the used glyphs and write the last metric in the hMetrics array
                if (attr->glyph_tbl.flgs[j] == 1 || j == attr->num_h_metric - 1) {
                    ret += WriteUINT16(tmp_stream, pmetric->advance_width);
                    ret += WriteINT16(tmp_stream, pmetric->lsb);
                } else {
                    ret += WriteUINT16(tmp_stream, value);
                    ret += WriteINT16(tmp_stream, value);
                }
                pmetric++;
            }

            while (j < attr->num_glyphs) {
                if (attr->glyph_tbl.flgs[j] == 1) {
                    ret += WriteINT16(tmp_stream, pmetric->lsb);
                } else
                    ret += WriteINT16(tmp_stream, value);
                pmetric++;
                j++;
            }
        } else if (BRST_MemCmp((BRST_BYTE*)tbl->tag, (BRST_BYTE*)"loca", 4) == 0) {
            BRST_UINT j;

            BRST_MemSet(&value, 0, 4);
            poffset = new_offsets;

            if (attr->header.index_to_loc_format == 0) {
                for (j = 0; j <= attr->num_glyphs; j++) {
                    ret += WriteUINT16(tmp_stream, (BRST_UINT16)*poffset);
                    poffset++;
                }
            } else {
                for (j = 0; j <= attr->num_glyphs; j++) {
                    ret += WriteUINT32(tmp_stream, *poffset);
                    poffset++;
                }
            }
        } else if (BRST_MemCmp((BRST_BYTE*)tbl->tag, (BRST_BYTE*)"name", 4) == 0) {
            ret = RecreateName(fontdef, tmp_stream);
        } else if (BRST_MemCmp((BRST_BYTE*)tbl->tag, (BRST_BYTE*)"post", 4) == 0) {
            value = 0x00030000;
            ret += BRST_Stream_Write(tmp_stream, (BRST_BYTE*)&value, 4);
            BRST_MemSet(&value, 0, 4);
            ret = BRST_Stream_Write(tmp_stream, (BRST_BYTE*)&value, 4); // italicAngle
            ret += BRST_Stream_Write(tmp_stream, (BRST_BYTE*)&value, 4); // underlinePosition + underlineThickness
            ret += BRST_Stream_Write(tmp_stream, (BRST_BYTE*)&value, 4); // isFixedPitch
            ret += BRST_Stream_Write(tmp_stream, (BRST_BYTE*)&value, 4); // minMemType42
            ret += BRST_Stream_Write(tmp_stream, (BRST_BYTE*)&value, 4); // maxMemType42
            ret += BRST_Stream_Write(tmp_stream, (BRST_BYTE*)&value, 4); // minMemType1
            ret += BRST_Stream_Write(tmp_stream, (BRST_BYTE*)&value, 4); // maxMemType1
        } else {
            BRST_UINT size = 4;

            while (length > 4) {
                value = 0;
                size  = 4;
                ret   = BRST_Stream_Read(attr->stream, (BRST_BYTE*)&value, &size);
                ret += BRST_Stream_Write(tmp_stream, (BRST_BYTE*)&value, size);
                length -= 4;
            }

            value = 0;
            size  = length;
            ret += BRST_Stream_Read(attr->stream, (BRST_BYTE*)&value, &size);
            ret += BRST_Stream_Write(tmp_stream, (BRST_BYTE*)&value, size);
        }

        tmp_tbl[i].offset = new_offset;
        tmp_tbl[i].length = tmp_stream->size - new_offset;

        /* pad at 4 bytes */
        {
            BRST_UINT size = tmp_tbl[i].length % 4;

            BRST_MemSet(&value, 0, 4);

            if (size != 0)
                ret += BRST_Stream_Write(tmp_stream, (BRST_BYTE*)&value, 4 - size);
        }

        if (ret != BRST_OK)
            goto Exit;
    }

    /* recalcurate checksum */
    for (i = 0; i < BRST_REQUIRED_TAGS_COUNT; i++) {
        BRST_TTF_Table tbl = tmp_tbl[i];
        BRST_UINT32 buf;
        BRST_UINT length = tbl.length;

        BRST_PTRACE(" SaveFontData() tag[%s] length=%u\n",
            REQUIRED_TAGS[i], length);

        if ((ret = BRST_Stream_Seek(tmp_stream, tbl.offset, BRST_SEEK_SET))
            != BRST_OK)
            break;

        tbl.check_sum = 0;
        while (length > 0) {
            BRST_UINT rlen = (length > 4) ? 4 : length;
            buf            = 0;
            if ((ret = BRST_Stream_Read(tmp_stream, (BRST_BYTE*)&buf, &rlen))
                != BRST_OK)
                break;

            UINT32Swap(&buf);
            tbl.check_sum += buf;
            length -= rlen;
        }

        if (ret != BRST_OK)
            break;

        BRST_PTRACE(" SaveFontData tag[%s] check-sum=%u offset=%u\n",
            REQUIRED_TAGS[i], (BRST_UINT)tbl.check_sum,
            (BRST_UINT)tbl.offset);

        ret += BRST_Stream_Write(stream, (BRST_BYTE*)REQUIRED_TAGS[i], 4);
        ret += WriteUINT32(stream, tbl.check_sum);
        tbl.offset += offset_base;
        ret += WriteUINT32(stream, tbl.offset);
        ret += WriteUINT32(stream, tbl.length);

        if (ret != BRST_OK)
            break;
    }

    if (ret != BRST_OK)
        goto Exit;

    /* calucurate checkSumAdjustment.*/
    ret = BRST_Stream_Seek(tmp_stream, 0, BRST_SEEK_SET);
    if (ret != BRST_OK)
        goto Exit;

    for (;;) {
        BRST_UINT32 buf;
        BRST_UINT size = sizeof(buf);

        ret = BRST_Stream_Read(tmp_stream, (BRST_BYTE*)&buf, &size);
        if (ret != BRST_OK || size <= 0) {
            if (ret == BRST_STREAM_EOF)
                ret = BRST_OK;
            break;
        }

        UINT32Swap(&buf);
        tmp_check_sum -= buf;
    }

    if (ret != BRST_OK)
        goto Exit;

    BRST_PTRACE(" SaveFontData new checkSumAdjustment=%u\n",
        (BRST_UINT)tmp_check_sum);

    UINT32Swap(&tmp_check_sum);

    ret = BRST_Stream_Seek(tmp_stream, check_sum_ptr, BRST_SEEK_SET);
    if (ret == BRST_OK) {
        ret = BRST_MemStream_Rewrite(tmp_stream, (BRST_BYTE*)&tmp_check_sum,
            4);
    }

    if (ret != BRST_OK)
        goto Exit;

    attr->length1 = tmp_stream->size + offset_base;
    ret           = BRST_Stream_WriteToStream(tmp_stream, stream, 0, NULL);

    goto Exit;

Exit:
    BRST_FreeMem(fontdef->mmgr, new_offsets);
    BRST_Stream_Free(tmp_stream);
    return ret;
}

void BRST_TTFontDef_SetTagName(BRST_FontDef fontdef,
    char* tag)
{
    BRST_TTFontDefAttr attr = (BRST_TTFontDefAttr)fontdef->attr;
    char buf[BRST_LIMIT_MAX_NAME_LEN + 1];
    BRST_UINT i;

    BRST_PTRACE(" BRST_TTFontDef_SetTagName\n");

    if (BRST_StrLen(tag, BRST_LIMIT_MAX_NAME_LEN) != BRST_TTF_FONT_TAG_LEN)
        return;

    BRST_MemCopy((BRST_BYTE*)attr->tag_name, (BRST_BYTE*)tag, BRST_TTF_FONT_TAG_LEN);
    attr->tag_name[BRST_TTF_FONT_TAG_LEN] = '+';

    for (i = 0; i < BRST_TTF_FONT_TAG_LEN + 1; i++) {
        attr->tag_name2[i * 2]     = 0x00;
        attr->tag_name2[i * 2 + 1] = attr->tag_name[i];
    }

    BRST_MemSet(buf, 0, BRST_LIMIT_MAX_NAME_LEN + 1);
    BRST_MemCopy((BRST_BYTE*)buf, (BRST_BYTE*)attr->tag_name, BRST_TTF_FONT_TAG_LEN + 1);
    BRST_MemCopy((BRST_BYTE*)buf + BRST_TTF_FONT_TAG_LEN + 1, (BRST_BYTE*)fontdef->base_font, BRST_LIMIT_MAX_NAME_LEN - BRST_TTF_FONT_TAG_LEN - 1);

    BRST_MemCopy((BRST_BYTE*)attr->base_font, (BRST_BYTE*)buf, BRST_LIMIT_MAX_NAME_LEN + 1);
}

/*
int
PdfTTFontDef::GetNameAttr(unsigned char* buf, BRST_UINT name_id,
        BRST_UINT platform_id, BRST_UINT lang_id, BRST_UINT max_len)


*/

static BRST_TTF_Table*
FindTable(BRST_FontDef fontdef,
    const char* tag)
{
    BRST_TTFontDefAttr attr = (BRST_TTFontDefAttr)fontdef->attr;
    BRST_TTF_Table* tbl     = attr->offset_tbl.table;
    BRST_UINT i;

    for (i = 0; i < attr->offset_tbl.num_tables; i++, tbl++) {
        if (BRST_MemCmp((BRST_BYTE*)tbl->tag, (BRST_BYTE*)tag, 4) == 0) {
            BRST_PTRACE(" FindTable find table[%c%c%c%c]\n",
                tbl->tag[0], tbl->tag[1], tbl->tag[2], tbl->tag[3]);
            return tbl;
        }
    }

    return NULL;
}

static void
UINT32Swap(BRST_UINT32* value)
{
    BRST_BYTE b[4];

    BRST_MemCopy(b, (BRST_BYTE*)value, 4);
    *value = (BRST_UINT32)((BRST_UINT32)b[0] << 24 | (BRST_UINT32)b[1] << 16 | (BRST_UINT32)b[2] << 8 | (BRST_UINT32)b[3]);
}

static void
UINT16Swap(BRST_UINT16* value)
{
    BRST_BYTE b[2];

    BRST_MemCopy(b, (BRST_BYTE*)value, 2);
    *value = (BRST_UINT16)((BRST_UINT16)b[0] << 8 | (BRST_UINT16)b[1]);
}

static void
INT16Swap(BRST_INT16* value)
{
    BRST_BYTE b[2];

    BRST_MemCopy(b, (BRST_BYTE*)value, 2);
    *value = (BRST_INT16)((BRST_INT16)b[0] << 8 | (BRST_INT16)b[1]);
}
