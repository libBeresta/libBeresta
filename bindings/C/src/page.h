// license
#ifndef BRST_PAGE_H
#define BRST_PAGE_H

typedef BRST_Dict BRST_Page;

/**
 
 */
typedef enum _BRST_PageLayout { 
    /// 
    BRST_PAGE_LAYOUT_SINGLE,
    /// 
    BRST_PAGE_LAYOUT_ONE_COLUMN,
    /// 
    BRST_PAGE_LAYOUT_TWO_COLUMN_LEFT,
    /// 
    BRST_PAGE_LAYOUT_TWO_COLUMN_RIGHT,
    /// 
    BRST_PAGE_LAYOUT_TWO_PAGE_LEFT,
    /// 
    BRST_PAGE_LAYOUT_TWO_PAGE_RIGHT,
    BRST_PAGELAYOUT_LAST
} BRST_PageLayout;

/**
 
 */
typedef enum _BRST_PageMode { 
    /// 
    BRST_PAGE_MODE_USE_NONE,
    /// 
    BRST_PAGE_MODE_USE_OUTLINE,
    /// 
    BRST_PAGE_MODE_USE_THUMBS,
    /// 
    BRST_PAGE_MODE_FULL_SCREEN,
    /// 
    BRST_PAGE_MODE_USE_OC,
    /// 
    BRST_PAGE_MODE_USE_ATTACHMENTS,
    BRST_PAGEMODE_LAST
} BRST_PageMode;

/**
 
 */
typedef enum _BRST_PageNum { 
    /// 
    BRST_PAGE_NUM_DECIMAL,
    /// 
    BRST_PAGE_NUM_UPPER_ROMAN,
    /// 
    BRST_PAGE_NUM_LOWER_ROMAN,
    /// 
    BRST_PAGE_NUM_UPPER_LETTERS,
    /// 
    BRST_PAGE_NUM_LOWER_LETTERS,
    BRST_PAGENUM_LAST
} BRST_PageNum;

/**
 
 */
typedef enum _BRST_PageBoundary { 
    /// 
    BRST_PAGE_MEDIABOX,
    /// 
    BRST_PAGE_CROPBOX,
    /// 
    BRST_PAGE_BLEEDBOX,
    /// 
    BRST_PAGE_TRIMBOX,
    /// 
    BRST_PAGE_ARTBOX,
    BRST_PAGEBOUNDARY_LAST
} BRST_PageBoundary;

/**
 
 */
typedef enum _BRST_PageTransition { 
    /// 
    BRST_PAGE_TRANSITION_WIPE_RIGHT,
    /// 
    BRST_PAGE_TRANSITION_WIPE_UP,
    /// 
    BRST_PAGE_TRANSITION_WIPE_LEFT,
    /// 
    BRST_PAGE_TRANSITION_WIPE_DOWN,
    /// 
    BRST_PAGE_TRANSITION_BARN_DOORS_HORIZONTAL_OUT,
    /// 
    BRST_PAGE_TRANSITION_BARN_DOORS_HORIZONTAL_IN,
    /// 
    BRST_PAGE_TRANSITION_BARN_DOORS_VERTICAL_OUT,
    /// 
    BRST_PAGE_TRANSITION_BARN_DOORS_VERTICAL_IN,
    /// 
    BRST_PAGE_TRANSITION_BOX_OUT,
    /// 
    BRST_PAGE_TRANSITION_BOX_IN,
    /// 
    BRST_PAGE_TRANSITION_BLINDS_HORIZONTAL,
    /// 
    BRST_PAGE_TRANSITION_BLINDS_VERTICAL,
    /// 
    BRST_PAGE_TRANSITION_DISSOLVE,
    /// 
    BRST_PAGE_TRANSITION_GLITTER_RIGHT,
    /// 
    BRST_PAGE_TRANSITION_GLITTER_DOWN,
    /// 
    BRST_PAGE_TRANSITION_GLITTER_TOP_LEFT_TO_BOTTOM_RIGHT,
    /// 
    BRST_PAGE_TRANSITION_REPLACE,
    BRST_PAGETRANSITION_LAST
} BRST_PageTransition;

/**
 Ориентация страницы
 */
typedef enum _BRST_PageOrientation { 
    /// Портретная ориентация (длинная сторона по вертикали)
    BRST_PAGE_ORIENTATION_PORTRAIT,
    /// Ландшафтная ориентация (длинная сторона по горизонтали)
    BRST_PAGE_ORIENTATION_LANDSCAPE,
    BRST_PAGEORIENTATION_LAST
} BRST_PageOrientation;

#endif /* BRST_PAGE_H */
