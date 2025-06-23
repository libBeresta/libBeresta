#ifndef PRIVATE_BRST_FONTDEF_TTF_H
#define PRIVATE_BRST_FONTDEF_TTF_H

#define BRST_TTF_FONT_TAG_LEN  6

typedef struct _BRST_TTF_Table {
        char        tag[4];
        BRST_UINT32 check_sum;
        BRST_UINT32 offset;
        BRST_UINT32 length;
} BRST_TTF_Table;


typedef struct _BRST_TTF_OffsetTbl {
        BRST_UINT32    sfnt_version;
        BRST_UINT16    num_tables;
        BRST_UINT16    search_range;
        BRST_UINT16    entry_selector;
        BRST_UINT16    range_shift;
        BRST_TTF_Table *table;
} BRST_TTF_OffsetTbl;


typedef struct _BRST_TTF_CmapRange {
        BRST_UINT16  format;
        BRST_UINT16  length;
        BRST_UINT16  language;
        BRST_UINT16  seg_count_x2;
        BRST_UINT16  search_range;
        BRST_UINT16  entry_selector;
        BRST_UINT16  range_shift;
        BRST_UINT16* end_count;
        BRST_UINT16  reserved_pad;
        BRST_UINT16* start_count;
        BRST_INT16 * id_delta;
        BRST_UINT16* id_range_offset;
        BRST_UINT16* glyph_id_array;
        BRST_UINT    glyph_id_array_count;
} BRST_TTF_CmapRange;


typedef struct _BRST_TTF_GlyphOffsets {
        BRST_UINT32   base_offset;
        BRST_UINT32  *offsets;
        BRST_BYTE    *flgs;   /* 0: unused, 1: used */
} BRST_TTF_GlyphOffsets;


typedef struct _BRST_TTF_LongHorMetric {
        BRST_UINT16  advance_width;
        BRST_INT16   lsb;
} BRST_TTF_LongHorMetric;


typedef struct _BRST_TTF_FontHeader {
    BRST_BYTE   version_number[4];
    BRST_UINT32 font_revision;
    BRST_UINT32 check_sum_adjustment;
    BRST_UINT32 magic_number;
    BRST_UINT16 flags;
    BRST_UINT16 units_per_em;
    BRST_BYTE   created[8];
    BRST_BYTE   modified[8];
    BRST_INT16  x_min;
    BRST_INT16  y_min;
    BRST_INT16  x_max;
    BRST_INT16  y_max;
    BRST_UINT16 mac_style;
    BRST_UINT16 lowest_rec_ppem;
    BRST_INT16  font_direction_hint;
    BRST_INT16  index_to_loc_format;
    BRST_INT16  glyph_data_format;
} BRST_TTF_FontHeader;


typedef struct _BRST_TTF_NameRecord {
    BRST_UINT16 platform_id;
    BRST_UINT16 encoding_id;
    BRST_UINT16 language_id;
    BRST_UINT16 name_id;
    BRST_UINT16 length;
    BRST_UINT16 offset;
}  BRST_TTF_NameRecord;


typedef struct _BRST_TTF_NamingTable {
    BRST_UINT16          format;
    BRST_UINT16          count;
    BRST_UINT16          string_offset;
    BRST_TTF_NameRecord* name_records;
}  BRST_TTF_NamingTable;

typedef struct _BRST_TTFontDefAttr_Rec {
    char                    base_font[BRST_LIMIT_MAX_NAME_LEN + 1];
    BRST_BYTE               first_char;
    BRST_BYTE               last_char;
    char*                   char_set;
    char                    tag_name[BRST_TTF_FONT_TAG_LEN + 1];
    char                    tag_name2[(BRST_TTF_FONT_TAG_LEN + 1) * 2];
    BRST_TTF_FontHeader     header;
    BRST_TTF_GlyphOffsets   glyph_tbl;
    BRST_UINT16             num_glyphs;
    BRST_TTF_NamingTable    name_tbl;
    BRST_TTF_LongHorMetric* h_metric;
    BRST_UINT16             num_h_metric;
    BRST_TTF_OffsetTbl      offset_tbl;
    BRST_TTF_CmapRange      cmap;
    BRST_UINT16             fs_type;
    BRST_BYTE               sfamilyclass[2];
    BRST_BYTE               panose[10];
    BRST_UINT32             code_page_range1;
    BRST_UINT32             code_page_range2;

    BRST_UINT               length1;

    BRST_BOOL               embedding;
    BRST_BOOL               is_cidfont;

    BRST_Stream             stream;
} BRST_TTFontDefAttr_Rec;
typedef struct _BRST_TTFontDefAttr_Rec   *BRST_TTFontDefAttr;

BRST_FontDef
BRST_TTFontDef_New(
    BRST_MMgr mmgr
);

BRST_FontDef
BRST_TTFontDef_Load(
    BRST_MMgr   mmgr,
    BRST_Stream stream,
    BRST_BOOL   embedding
);

BRST_FontDef
BRST_TTFontDef_Load2(
    BRST_MMgr   mmgr,
    BRST_Stream stream,
    BRST_UINT   index,
    BRST_BOOL   embedding
);

BRST_UINT16
BRST_TTFontDef_Glyphid(
    BRST_FontDef fontdef,
    BRST_UINT16  unicode
);

BRST_INT16
BRST_TTFontDef_CharWidth(
    BRST_FontDef fontdef,
    BRST_UINT16  unicode
);

BRST_INT16
BRST_TTFontDef_GidWidth(
    BRST_FontDef fontdef,
    BRST_UINT16  gid
);

BRST_STATUS
BRST_TTFontDef_SaveFontData(
    BRST_FontDef fontdef,
    BRST_Stream  stream
);

BRST_Box
BRST_TTFontDef_CharBBox(
    BRST_FontDef fontdef,
    BRST_UINT16  unicode
);

void
BRST_TTFontDef_SetTagName(
    BRST_FontDef fontdef,
    char*        tag
);

#endif /* PRIVATE_BRST_FONTDEF_TTF_H */