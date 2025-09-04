#include "brst_types.h"
#include "brst_encrypt.h"
#include "brst_consts.h"
#include "brst_mmgr.h"
#include "brst_matrix.h"
#include "private/brst_matrix.h"
#include "brst_array.h"
#include "brst_error.h"
#include "private/brst_error.h"
#include "private/brst_mmgr.h"
#include "brst_dict.h"
#include "brst_encoder.h"
#include "brst_stream.h"
#include "brst_xref.h"
#include "brst_font.h"
#include "private/brst_font.h"
#include "private/brst_defines.h"
#include "brst_consts.h"
#include "brst_geometry_defines.h"
#include "private/brst_gstate.h"

BRST_GState
BRST_GState_New(BRST_MMgr mmgr,
    BRST_GState current)
{
    BRST_GState gstate;

    if (current && current->depth >= BRST_LIMIT_MAX_GSTATE) {
        BRST_Error_Set(BRST_MMgr_Error(mmgr), BRST_EXCEED_GSTATE_LIMIT, 0);

        return NULL;
    }

    gstate = BRST_GetMem(mmgr, sizeof(BRST_GState_Rec));
    if (!gstate)
        return NULL;

    if (current) {
        gstate->trans_matrix = current->trans_matrix;
        gstate->line_width   = current->line_width;
        gstate->line_cap     = current->line_cap;
        gstate->line_join    = current->line_join;
        gstate->miter_limit  = current->miter_limit;
        gstate->dash_mode    = current->dash_mode;
        gstate->flatness     = current->flatness;

        gstate->char_space     = current->char_space;
        gstate->word_space     = current->word_space;
        gstate->h_scaling      = current->h_scaling;
        gstate->text_leading   = current->text_leading;
        gstate->rendering_mode = current->rendering_mode;
        gstate->text_rise      = current->text_rise;

        gstate->cs_stroke   = current->cs_stroke;
        gstate->cs_fill     = current->cs_fill;
        gstate->rgb_fill    = current->rgb_fill;
        gstate->rgb_stroke  = current->rgb_stroke;
        gstate->cmyk_fill   = current->cmyk_fill;
        gstate->cmyk_stroke = current->cmyk_stroke;
        gstate->gray_fill   = current->gray_fill;
        gstate->gray_stroke = current->gray_stroke;

        gstate->font         = current->font;
        gstate->font_size    = current->font_size;
        gstate->writing_mode = current->writing_mode;

        gstate->prev  = current;
        gstate->depth = current->depth + 1;
    } else {
        gstate->trans_matrix = BRST_Matrix_Identity(mmgr);
        gstate->line_width   = BRST_DEF_LINEWIDTH;
        gstate->line_cap     = BRST_DEF_LINECAP;
        gstate->line_join    = BRST_DEF_LINEJOIN;
        gstate->miter_limit  = BRST_DEF_MITERLIMIT;
        gstate->dash_mode    = DEF_DASH_MODE;
        gstate->flatness     = BRST_DEF_FLATNESS;

        gstate->char_space     = BRST_DEF_CHARSPACE;
        gstate->word_space     = BRST_DEF_WORDSPACE;
        gstate->h_scaling      = BRST_DEF_HSCALING;
        gstate->text_leading   = BRST_DEF_LEADING;
        gstate->rendering_mode = BRST_DEF_RENDERING_MODE;
        gstate->text_rise      = BRST_DEF_RISE;

        gstate->cs_stroke   = BRST_CS_DEVICE_GRAY;
        gstate->cs_fill     = BRST_CS_DEVICE_GRAY;
        gstate->rgb_fill    = DEF_RGB_COLOR;
        gstate->rgb_stroke  = DEF_RGB_COLOR;
        gstate->cmyk_fill   = DEF_CMYK_COLOR;
        gstate->cmyk_stroke = DEF_CMYK_COLOR;
        gstate->gray_fill   = 0;
        gstate->gray_stroke = 0;

        gstate->font         = NULL;
        gstate->font_size    = 0;
        gstate->writing_mode = BRST_WMODE_HORIZONTAL;

        gstate->prev  = NULL;
        gstate->depth = 1;
    }

    return gstate;
}

BRST_GState
BRST_GState_Free(BRST_MMgr mmgr,
    BRST_GState gstate)
{
    BRST_GState current = NULL;

    if (gstate) {
        current = gstate->prev;
        BRST_FreeMem(mmgr, gstate);
    }

    return current;
}
