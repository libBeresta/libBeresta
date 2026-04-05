#include "brst_external.h"
#include "brst_types.h"
#include "brst_mmgr.h"
#include "brst_encrypt.h"
#include "brst_stream.h"
#include "brst_dict.h"
#include "brst_xref.h"
#include "brst_encoder.h"
#include "brst_error.h"
#include "brst_consts.h"
#include "private/brst_utils.h"
#include "brst_page.h"
#include "private/brst_encrypt_dict.h"
#include "brst_outline.h"
#include "private/brst_catalog.h"
#include "private/brst_pdfa.h"
#include "brst_pdfa.h"
#include "brst_doc.h"
#include "private/brst_doc.h"
#include "brst_fontdef.h"
#include "private/brst_doc_fontdef.h"
#include "private/brst_doc_encoder.h"
#include "brst_version.h"
#include "brst_doc_info.h"

BRST_EXPORT(BRST_CSTR)
BRST_Version(void)
{
    return BRST_VERSION_TEXT;
}

BRST_EXPORT(BRST_BOOL)
BRST_Doc_Initialized(BRST_Doc pdf)
{
    BRST_PTRACE(" BRST_Doc_Initialized\n");

    if (!pdf || pdf->sig_bytes != BRST_SIG_BYTES)
        return BRST_FALSE;

    if (!pdf->catalog || BRST_Error_Code(pdf->error) != BRST_NOERROR) {
        BRST_Error_Raise(pdf->error, BRST_INVALID_DOCUMENT, 0);
        return BRST_FALSE;
    } else {
        return BRST_TRUE;
    }
}

BRST_EXPORT(BRST_MMgr)
BRST_Doc_MMgr(BRST_Doc doc)
{
    BRST_PTRACE(" BRST_Doc_MMgr\n");

    return doc->mmgr;
}

BRST_EXPORT(void)
BRST_Doc_Destroy(BRST_Doc pdf)
{
    BRST_PTRACE(" BRST_Doc_Destroy\n");

    if (BRST_Doc_Validate(pdf)) {
        if (pdf->xref) {
            BRST_Xref_Free(pdf->xref);
            pdf->xref = NULL;
        }

        if (pdf->font_mgr) {
            BRST_List_Free(pdf->font_mgr);
            pdf->font_mgr = NULL;
        }

        if (pdf->fontdef_list)
            CleanupFontDefList(pdf);

        BRST_MemSet(pdf->ttfont_tag, 0, 6);

        pdf->pdf_version    = BRST_VER_13;
        pdf->outlines       = NULL;
        pdf->catalog        = NULL;
        pdf->root_pages     = NULL;
        pdf->cur_pages      = NULL;
        pdf->cur_page       = NULL;
        pdf->encrypt_on     = BRST_FALSE;
        pdf->cur_page_num   = 0;
        pdf->cur_encoder    = NULL;
        pdf->def_encoder    = NULL;
        pdf->page_per_pages = 0;

        if (pdf->page_list) {
            BRST_List_Free(pdf->page_list);
            pdf->page_list = NULL;
        }

        pdf->encrypt_dict = NULL;
        pdf->info         = NULL;

        BRST_Error_Reset(pdf->error);

        if (pdf->stream) {
            BRST_Stream_Free(pdf->stream);
            pdf->stream = NULL;
        }

        pdf->pdfa_type = BRST_PDFA_NON_PDFA;
        if (pdf->xmp_extensions) {
            BRST_PDFA_ClearXmpExtensions(pdf);
            BRST_List_Free(pdf->xmp_extensions);
            pdf->xmp_extensions = NULL;
        }
    }
}

BRST_EXPORT(void)
BRST_Doc_Destroy_All(BRST_Doc pdf)
{
    BRST_PTRACE(" BRST_Doc_Destroy_All\n");

    if (BRST_Doc_Validate(pdf)) {
        BRST_Doc_Destroy(pdf);

        if (pdf->fontdef_list)
            FreeFontDefList(pdf);

        if (pdf->encoder_list)
            FreeEncoderList(pdf);

        pdf->compression_mode = BRST_COMP_NONE;

        BRST_Error_Reset(pdf->error);

        BRST_Error_Free(pdf->error);
    }
}

BRST_EXPORT(void)
BRST_Doc_Free(BRST_Doc pdf)
{
    BRST_PTRACE(" BRST_Doc_Free\n");

    if (pdf) {
        BRST_MMgr mmgr = pdf->mmgr;

        BRST_Doc_Destroy_All(pdf);

        pdf->sig_bytes = 0;

        BRST_FreeMem(mmgr, pdf);
        BRST_MMgr_Free(mmgr);
    }
}

BRST_EXPORT(BRST_STATUS)
BRST_Doc_Initialize(BRST_Doc pdf)
{
    char buf[BRST_TMP_BUF_SIZE];
    char* ptr  = buf;
    char* eptr = buf + BRST_TMP_BUF_SIZE - 1;
    const char* version;

    BRST_PTRACE(" BRST_Doc_Initialize\n");

    if (!BRST_Doc_Validate(pdf))
        return BRST_DOC_INVALID_OBJECT;

    BRST_Doc_Destroy(pdf);

    pdf->xref = BRST_Xref_New(pdf->mmgr, 0);
    if (!pdf->xref)
        return BRST_Error_Check(pdf->error);

    pdf->trailer = pdf->xref->trailer;

    pdf->font_mgr = BRST_List_New(pdf->mmgr, BRST_DEF_ITEMS_PER_BLOCK);
    if (!pdf->font_mgr)
        return BRST_Error_Check(pdf->error);

    if (!pdf->fontdef_list) {
        pdf->fontdef_list = BRST_List_New(pdf->mmgr,
            BRST_DEF_ITEMS_PER_BLOCK);
        if (!pdf->fontdef_list)
            return BRST_Error_Check(pdf->error);
    }

    if (!pdf->encoder_list) {
        pdf->encoder_list = BRST_List_New(pdf->mmgr,
            BRST_DEF_ITEMS_PER_BLOCK);
        if (!pdf->encoder_list)
            return BRST_Error_Check(pdf->error);
    }

    pdf->catalog = BRST_Catalog_New(pdf->mmgr, pdf->xref);
    if (!pdf->catalog)
        return BRST_Error_Check(pdf->error);

    pdf->root_pages = BRST_Catalog_Root(pdf->catalog);
    if (!pdf->root_pages)
        return BRST_Error_Check(pdf->error);

    pdf->page_list = BRST_List_New(pdf->mmgr, BRST_DEF_PAGE_LIST_NUM);
    if (!pdf->page_list)
        return BRST_Error_Check(pdf->error);

    pdf->cur_pages = pdf->root_pages;

    ptr     = (char*)BRST_StrCopy(ptr, (const char*)"Beresta Free PDF Library ", eptr);
    version = BRST_Version();
    BRST_StrCopy(ptr, version, eptr);

    if (BRST_Doc_SetInfoAttr(pdf, BRST_INFO_PRODUCER, buf) != BRST_OK)
        return BRST_Error_Check(pdf->error);

    pdf->pdfa_type      = BRST_PDFA_NON_PDFA;
    pdf->xmp_extensions = BRST_List_New(pdf->mmgr, BRST_DEF_ITEMS_PER_BLOCK);

    return BRST_OK;
}

BRST_EXPORT(BRST_Doc)
BRST_Doc_New_Ex(BRST_Error_Handler user_error_fn,
    BRST_Alloc_Func user_alloc_fn,
    BRST_Free_Func user_free_fn,
    BRST_UINT mem_pool_buf_size,
    void* user_data)
{
    BRST_Doc pdf;
    BRST_MMgr mmgr;
    BRST_Error tmp_error = BRST_Error_New();

    BRST_PTRACE(" BRST_New_Doc_Ex\n");

    /* initialize temporary-error object */
    BRST_Error_Init(tmp_error, user_data);

    /* create memory-manager object */
    mmgr = BRST_MMgr_New(tmp_error, mem_pool_buf_size, user_alloc_fn,
        user_free_fn);

    if (!mmgr) {
        BRST_Error_Check(tmp_error);
        return NULL;
    }

    BRST_PTRACE(" BRST_New_Doc_Ex 1\n");

    BRST_PTRACE("%p mmbr\n", (void*)mmgr);

    /* now create pdf_doc object */
    pdf = BRST_GetMem(mmgr, sizeof(BRST_Doc_Rec));
    BRST_PTRACE(" BRST_New_Doc_Ex4 pdf=%p, sizeof=%lu\n", (void*) pdf, sizeof(BRST_Doc_Rec));
    if (!pdf) {
        BRST_MMgr_Free(mmgr);
        BRST_Error_Check(tmp_error);
        return NULL;
    }

    BRST_PTRACE(" BRST_New_Doc_Ex2\n");

    BRST_MemSet(pdf, 0, sizeof(BRST_Doc_Rec));
    pdf->sig_bytes        = BRST_SIG_BYTES;
    pdf->mmgr             = mmgr;
    pdf->pdf_version      = BRST_VER_13;
    pdf->compression_mode = BRST_COMP_NONE;

    BRST_PTRACE(" BRST_New_Doc_Ex3\n");

    /* copy the data of temporary-error object to the one which is
       included in pdf_doc object */
    pdf->error = tmp_error;

    // TODO Вероятно, это присваивание избыточно, см. BRST_MMgr_New()
    //    /* switch the error-object of memory-manager */
    //    mmgr->error = pdf->error;

    BRST_PTRACE(" BRST_New_Doc_Ex4\n");

    if (BRST_Doc_Initialize(pdf) != BRST_OK) {
        BRST_Doc_Free(pdf);
        BRST_Error_Check(tmp_error);
        return NULL;
    }

    BRST_PTRACE(" BRST_New_Doc_Ex5\n");

    BRST_Error_SetHandler(pdf->error, user_error_fn);

    BRST_PTRACE(" BRST_New_Doc_Ex OK\n");

    return pdf;
}

BRST_EXPORT(BRST_Doc)
BRST_Doc_New(BRST_Error_Handler user_error_fn,
    void* user_data)
{
    BRST_PTRACE(" BRST_Doc_New\n");

    return BRST_Doc_New_Ex(user_error_fn, NULL, NULL, 0, user_data);
}

BRST_EXPORT(BRST_Doc)
BRST_Doc_New_Empty()
{
    BRST_PTRACE(" BRST_Doc_New_Empty\n");

    BRST_Doc pdf = BRST_Doc_New_Ex(NULL, NULL, NULL, 0, NULL);
    BRST_Doc_Initialized(pdf);
    return pdf;
}

BRST_EXPORT(BRST_STATUS)
BRST_Doc_Contents(BRST_Doc pdf,
    BRST_BYTE* buf,
    BRST_UINT32* size)
{
    BRST_Stream stream;
    BRST_UINT isize = *size;
    BRST_STATUS ret;

    BRST_PTRACE(" BRST_Doc_Contents\n");

    if (!BRST_Doc_Initialized(pdf)) {
        return BRST_INVALID_DOCUMENT;
    }

    stream = BRST_MemStream_New(pdf->mmgr, BRST_STREAM_BUF_SIZE);

    if (!stream) {
        return BRST_Error_Check(pdf->error);
    }

    if (InternalSaveToStream(pdf, stream) != BRST_OK) {
        BRST_Stream_Free(stream);
        return BRST_Error_Check(pdf->error);
    }

    ret = BRST_Stream_Read(stream, buf, &isize);

    *size = isize;
    BRST_Stream_Free(stream);

    return ret;
}

BRST_EXPORT(BRST_REAL)
BRST_PageSize_Width(BRST_PageSizes size, BRST_PageOrientation orientation) {
    if ((size >= 0 && size < BRST_PAGE_SIZE_EOF) &&
       (orientation == BRST_PAGE_ORIENTATION_LANDSCAPE || orientation == BRST_PAGE_ORIENTATION_PORTRAIT)) {
        if (orientation == BRST_PAGE_ORIENTATION_PORTRAIT) {
            return BRST_PREDEFINED_PAGE_SIZES[size].x;
        } else {
            return BRST_PREDEFINED_PAGE_SIZES[size].y;
        }
    } else {
        return 0.0;
    }
}

BRST_EXPORT(BRST_REAL)
BRST_PageSize_Height(BRST_PageSizes size, BRST_PageOrientation orientation) {
    if ((size >= 0 && size < BRST_PAGE_SIZE_EOF) &&
       (orientation == BRST_PAGE_ORIENTATION_LANDSCAPE || orientation == BRST_PAGE_ORIENTATION_PORTRAIT)) {
        if (orientation == BRST_PAGE_ORIENTATION_PORTRAIT) {
            return BRST_PREDEFINED_PAGE_SIZES[size].y;
        } else {
            return BRST_PREDEFINED_PAGE_SIZES[size].x;
        }
    } else {
        return 0.0;
    }
}
