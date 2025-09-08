#include "brst_external.h"
#include "brst_types.h"
#include "brst_mmgr.h"
#include "brst_encrypt.h"
#include "brst_stream.h"
#include "brst_dict.h"
#include "brst_xref.h"
#include "brst_encoder.h"
#include "private/brst_encoder.h"
#include "brst_error.h"
#include "brst_consts.h"
#include "brst_ext_gstate.h"
#include "brst_font.h"
#include "brst_shading.h"
#include "brst_doc.h"
#include "brst_pdfa.h"
#include "brst_page.h"
#include "brst_destination.h"
#include "private/brst_catalog.h"
#include "brst_outline.h"
#include "private/brst_encrypt_dict.h"
#include "private/brst_doc.h"
#include "brst_pattern.h"
#include "private/brst_page.h"
#include "brst_base.h"
#include "private/brst_doc_pages.h"
#include "private/brst_doc_page_label.h"
#include "brst_matrix.h"
#include "private/brst_array.h"
#include "private/brst_gstate.h"
#include "brst_image.h"

BRST_EXPORT(BRST_Page)
BRST_Doc_Page_Insert(BRST_Doc pdf,
    BRST_Page target)
{
    BRST_Page page;
    BRST_STATUS ret;

    BRST_PTRACE(" BRST_Doc_Page_Insert\n");

    if (!BRST_Doc_Initialized(pdf))
        return NULL;

    if (!BRST_Page_Validate(target)) {
        BRST_Error_Raise(pdf->error, BRST_INVALID_PAGE, 0);
        return NULL;
    }

    /* check whether the page belong to the pdf */
    if (pdf->mmgr != target->mmgr) {
        BRST_Error_Raise(pdf->error, BRST_INVALID_PAGE, 0);
        return NULL;
    }

    page = BRST_Page_New(pdf->mmgr, pdf->xref);
    if (!page) {
        BRST_Error_Check(pdf->error);
        return NULL;
    }

    if ((ret = BRST_Page_InsertBefore(page, target)) != BRST_OK) {
        BRST_Error_Raise(pdf->error, ret, 0);
        return NULL;
    }

    if ((ret = BRST_List_Insert(pdf->page_list, target, page)) != BRST_OK) {
        BRST_Error_Raise(pdf->error, ret, 0);
        return NULL;
    }

    if (pdf->compression_mode & BRST_COMP_TEXT)
        BRST_Page_SetFilter(page, BRST_STREAM_FILTER_FLATE_DECODE);

    return page;
}

BRST_EXPORT(BRST_Page)
BRST_Doc_Page_Add(BRST_Doc pdf)
{
    BRST_Page page;
    BRST_STATUS ret;

    BRST_PTRACE(" BRST_Doc_Page_Add\n");
    BRST_PTRACE(" BRST_Doc_Page_Add pdf = %p\n", (void*)pdf);

    if (!BRST_Doc_Initialized(pdf))
        return NULL;

    if (pdf->page_per_pages) {
        if (pdf->page_per_pages <= pdf->cur_page_num) {
            pdf->cur_pages = BRST_Doc_Pages_AddTo(pdf, pdf->root_pages);
            if (!pdf->cur_pages)
                return NULL;
            pdf->cur_page_num = 0;
        }
    }

    page = BRST_Page_New(pdf->mmgr, pdf->xref);
    if (!page) {
        BRST_Error_Check(pdf->error);
        return NULL;
    }

    if ((ret = BRST_Pages_AddKids(pdf->cur_pages, page)) != BRST_OK) {
        BRST_Error_Raise(pdf->error, ret, 0);
        return NULL;
    }

    if ((ret = BRST_List_Add(pdf->page_list, page)) != BRST_OK) {
        BRST_Error_Raise(pdf->error, ret, 0);
        return NULL;
    }

    pdf->cur_page = page;

    if (pdf->compression_mode & BRST_COMP_TEXT)
        BRST_Page_SetFilter(page, BRST_STREAM_FILTER_FLATE_DECODE);

    pdf->cur_page_num++;

    return page;
}

BRST_EXPORT(BRST_Page)
BRST_Doc_Page_Current(BRST_Doc pdf)
{
    BRST_PTRACE(" BRST_Doc_Page_Current\n");

    if (!BRST_Doc_Initialized(pdf))
        return NULL;

    return pdf->cur_page;
}

BRST_EXPORT(BRST_STATUS)
BRST_Doc_Page_SetLayout(BRST_Doc pdf,
    BRST_PageLayout layout)
{
    BRST_STATUS ret;

    BRST_PTRACE(" BRST_Doc_Page_SetLayout\n");

    if (!BRST_Doc_Initialized(pdf))
        return BRST_INVALID_DOCUMENT;

    if (layout < 0 || layout >= BRST_PAGE_LAYOUT_EOF)
        return BRST_Error_Raise(pdf->error, BRST_PAGE_LAYOUT_OUT_OF_RANGE,
            (BRST_STATUS)layout);

    if ((layout == BRST_PAGE_LAYOUT_TWO_PAGE_LEFT || layout == BRST_PAGE_LAYOUT_TWO_PAGE_RIGHT) && pdf->pdf_version < BRST_VER_15)
        pdf->pdf_version = BRST_VER_15;

    ret = BRST_Catalog_SetPageLayout(pdf->catalog, layout);
    if (ret != BRST_OK)
        BRST_Error_Check(pdf->error);

    return BRST_OK;
}

BRST_EXPORT(BRST_PageMode)
BRST_Doc_Page_Mode(BRST_Doc pdf)
{
    BRST_PTRACE(" BRST_Doc_Page_Mode\n");

    if (!BRST_Doc_Initialized(pdf))
        return BRST_PAGE_MODE_USE_NONE;

    return BRST_Catalog_PageMode(pdf->catalog);
}

BRST_EXPORT(BRST_STATUS)
BRST_Doc_Page_SetMode(BRST_Doc pdf,
    BRST_PageMode mode)
{
    BRST_STATUS ret;

    BRST_PTRACE(" BRST_Doc_Page_SetMode\n");

    if (!BRST_Doc_Initialized(pdf))
        return BRST_INVALID_DOCUMENT;

    if (mode < 0 || mode >= BRST_PAGE_MODE_EOF)
        return BRST_Error_Raise(pdf->error, BRST_PAGE_MODE_OUT_OF_RANGE,
            (BRST_STATUS)mode);

    ret = BRST_Catalog_SetPageMode(pdf->catalog, mode);
    if (ret != BRST_OK)
        return BRST_Error_Check(pdf->error);

    return BRST_OK;
}

BRST_EXPORT(BRST_PageLayout)
BRST_Doc_Page_Layout(BRST_Doc pdf)
{
    BRST_PTRACE(" BRST_Doc_Page_Layout\n");

    if (!BRST_Doc_Initialized(pdf))
        return BRST_PAGE_LAYOUT_SINGLE;

    return BRST_Catalog_PageLayout(pdf->catalog);
}

BRST_EXPORT(BRST_Page)
BRST_Doc_Page_ByIndex(BRST_Doc pdf,
    BRST_UINT index)
{
    BRST_Page ret;

    BRST_PTRACE(" BRST_Doc_Page_ByIndex\n");

    if (!BRST_Doc_Initialized(pdf))
        return NULL;

    ret = BRST_List_ItemAt(pdf->page_list, index);
    if (!ret) {
        BRST_Error_Raise(pdf->error, BRST_INVALID_PAGE_INDEX, 0);
        return NULL;
    }

    return ret;
}

BRST_EXPORT(BRST_STATUS)
BRST_Doc_Page_AddLabel(BRST_Doc pdf,
    BRST_UINT page_num,
    BRST_PageNumStyle style,
    BRST_UINT first_page,
    const char* prefix)
{
    BRST_Dict page_label;
    BRST_STATUS ret;

    BRST_PTRACE(" BRST_Doc_Page_AddLabel\n");

    if (!BRST_Doc_Initialized(pdf))
        return BRST_INVALID_DOCUMENT;

    page_label = BRST_PageLabel_New(pdf, style, first_page, prefix);

    if (!page_label)
        return BRST_Error_Check(pdf->error);

    if (style < 0 || style >= BRST_PAGE_NUM_EOF)
        return BRST_Error_Raise(pdf->error, BRST_PAGE_NUM_OUT_OF_RANGE,
            (BRST_STATUS)style);

    ret = BRST_Catalog_AddPageLabel(pdf->catalog, page_num, page_label);
    if (ret != BRST_OK)
        return BRST_Error_Check(pdf->error);

    return BRST_OK;
}

BRST_EXPORT(BRST_STATUS)
BRST_Doc_Pages_SetConfiguration(BRST_Doc pdf,
    BRST_UINT page_per_pages)
{
    BRST_PTRACE(" BRST_Doc_Pages_SetConfiguration\n");

    if (!BRST_Doc_Initialized(pdf))
        return BRST_INVALID_DOCUMENT;

    if (pdf->cur_page)
        return BRST_Error_Raise(pdf->error, BRST_INVALID_DOCUMENT_STATE, 0);

    if (page_per_pages > BRST_LIMIT_MAX_ARRAY)
        return BRST_Error_Raise(pdf->error, BRST_INVALID_PARAMETER, 0);

    if (pdf->cur_pages == pdf->root_pages) {
        pdf->cur_pages = BRST_Doc_Pages_AddTo(pdf, pdf->root_pages);
        if (!pdf->cur_pages)
            return BRST_Error_Code(pdf->error);
        pdf->cur_page_num = 0;
    }

    pdf->page_per_pages = page_per_pages;

    return BRST_OK;
}
