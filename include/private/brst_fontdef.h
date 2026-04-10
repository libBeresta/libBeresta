#ifndef PRIVATE_BRST_FONTDEF_H
#define PRIVATE_BRST_FONTDEF_H

#define BRST_FONTDEF_SIG_BYTES 0x464F4E54L

/*------ collection of flags for defining characteristics. ---*/

#define BRST_FONT_FIXED_WIDTH    1
#define BRST_FONT_SERIF          2
#define BRST_FONT_SYMBOLIC       4
#define BRST_FONT_SCRIPT         8
/* Reserved                      16 */
#define BRST_FONT_STD_CHARSET    32
#define BRST_FONT_ITALIC         64
  /* Reserved                    128
     Reserved                    256
     Reserved                    512
     Reserved                    1024
     Reserved                    2048
     Reserved                    4096
     Reserved                    8192
     Reserved                    16384
     Reserved                    32768 */
#define BRST_FONT_ALL_CAP        65536
#define BRST_FONT_SMALL_CAP      131072
#define BRST_FONT_FOURCE_BOLD    262144

#define BRST_CID_W_TYPE_FROM_TO     0
#define BRST_CID_W_TYPE_FROM_ARRAY  1


typedef enum _BRST_FontDefType {
    BRST_FONTDEF_TYPE_TYPE1,
    BRST_FONTDEF_TYPE_TRUETYPE,
    BRST_FONTDEF_TYPE_CID,
    BRST_FONTDEF_TYPE_UNINITIALIZED,
    BRST_FONTDEF_TYPE_EOF
} BRST_FontDefType;

typedef void (*BRST_FontDef_FreeFunc) (BRST_FontDef fontdef);
typedef void (*BRST_FontDef_CleanFunc) (BRST_FontDef fontdef);
typedef BRST_STATUS (*BRST_FontDef_InitFunc) (BRST_FontDef fontdef);

typedef struct _BRST_FontDef_Rec {
    BRST_UINT32            sig_bytes;
    char                   base_font[BRST_LIMIT_MAX_NAME_LEN + 1];
    BRST_MMgr              mmgr;
    BRST_Error             error;
    BRST_FontDefType       type;
    BRST_FontDef_CleanFunc clean_fn;
    BRST_FontDef_FreeFunc  free_fn;
    BRST_FontDef_InitFunc  init_fn;

    BRST_INT16             ascent;
    BRST_INT16             descent;
    BRST_UINT              flags;
    BRST_Box               font_bbox;
    BRST_INT16             italic_angle;
    BRST_UINT16            stemv;
    BRST_INT16             avg_width;
    BRST_INT16             max_width;
    BRST_INT16             missing_width;
    BRST_UINT16            stemh;
    BRST_UINT16            x_height;
    BRST_UINT16            cap_height;

    /*  the initial value of descriptor entry is NULL.
     *  when first font-object based on the fontdef object is created,
     *  the font-descriptor object is created and descriptor entry is set.
     */
    BRST_Dict              descriptor;
    BRST_Stream            data;

    BRST_BOOL              valid;
    void*                  attr;
} BRST_FontDef_Rec;
typedef struct _BRST_FontDef_Rec *BRST_FontDef;

typedef struct _BRST_CharData {
    BRST_INT16     char_cd;
    BRST_UNICODE   unicode;
    BRST_INT16     width;
} BRST_CharData;
typedef struct _BRST_CharData BRST_CharData;

void
BRST_FontDef_Free(
    BRST_FontDef fontdef
);

void
BRST_FontDef_Cleanup(
    BRST_FontDef fontdef
);

BRST_BOOL
BRST_FontDef_Validate(
    BRST_FontDef fontdef
);

#endif /* PRIVATE_BRST_FONTDEF_H */