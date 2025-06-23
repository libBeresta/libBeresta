#ifndef BRST_PAGE_H
#define BRST_PAGE_H

typedef BRST_Dict BRST_Page;
typedef BRST_Dict BRST_XObject;

typedef enum _BRST_PageLayout {
    BRST_PAGE_LAYOUT_SINGLE = 0,
    BRST_PAGE_LAYOUT_ONE_COLUMN,
    BRST_PAGE_LAYOUT_TWO_COLUMN_LEFT,
    BRST_PAGE_LAYOUT_TWO_COLUMN_RIGHT,
    BRST_PAGE_LAYOUT_TWO_PAGE_LEFT,
    BRST_PAGE_LAYOUT_TWO_PAGE_RIGHT,
    BRST_PAGE_LAYOUT_EOF
} BRST_PageLayout;

typedef enum _BRST_PageMode {
    BRST_PAGE_MODE_USE_NONE = 0,
    BRST_PAGE_MODE_USE_OUTLINE,
    BRST_PAGE_MODE_USE_THUMBS,
    BRST_PAGE_MODE_FULL_SCREEN,
/*  BRST_PAGE_MODE_USE_OC,
    BRST_PAGE_MODE_USE_ATTACHMENTS,
 */
    BRST_PAGE_MODE_EOF
} BRST_PageMode;

typedef enum _BRST_PageNumStyle {
    BRST_PAGE_NUM_STYLE_DECIMAL = 0,
    BRST_PAGE_NUM_STYLE_UPPER_ROMAN,
    BRST_PAGE_NUM_STYLE_LOWER_ROMAN,
    BRST_PAGE_NUM_STYLE_UPPER_LETTERS,
    BRST_PAGE_NUM_STYLE_LOWER_LETTERS,
    BRST_PAGE_NUM_STYLE_EOF
} BRST_PageNumStyle;

/*----- slide show -----------------------------------------------------------*/

typedef enum _BRST_TransitionStyle {
    BRST_TS_WIPE_RIGHT = 0,
    BRST_TS_WIPE_UP,
    BRST_TS_WIPE_LEFT,
    BRST_TS_WIPE_DOWN,
    BRST_TS_BARN_DOORS_HORIZONTAL_OUT,
    BRST_TS_BARN_DOORS_HORIZONTAL_IN,
    BRST_TS_BARN_DOORS_VERTICAL_OUT,
    BRST_TS_BARN_DOORS_VERTICAL_IN,
    BRST_TS_BOX_OUT,
    BRST_TS_BOX_IN,
    BRST_TS_BLINDS_HORIZONTAL,
    BRST_TS_BLINDS_VERTICAL,
    BRST_TS_DISSOLVE,
    BRST_TS_GLITTER_RIGHT,
    BRST_TS_GLITTER_DOWN,
    BRST_TS_GLITTER_TOP_LEFT_TO_BOTTOM_RIGHT,
    BRST_TS_REPLACE,
    BRST_TS_EOF
} BRST_TransitionStyle;

/*----------------------------------------------------------------------------*/

typedef enum _BRST_PageBoundary {
    BRST_PAGE_MEDIABOX = 0,
    BRST_PAGE_CROPBOX,
    BRST_PAGE_BLEEDBOX,
    BRST_PAGE_TRIMBOX,
    BRST_PAGE_ARTBOX
} BRST_PageBoundary;

/*----------------------------------------------------------------------------*/

/**
  \brief Page orientation
*/
typedef enum _BRST_PageDirection {
    /// Portrait orientation (longest size vertical)
    BRST_PAGE_PORTRAIT = 0,
    /// Landscape orientation (longest size horizontal)
    BRST_PAGE_LANDSCAPE
} BRST_PageDirection;


#endif /* BRST_PAGE_H */