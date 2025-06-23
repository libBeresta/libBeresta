#include "brst_types.h"
#include "brst_mmgr.h"
#include "brst_encrypt.h"
#include "brst_stream.h"
#include "brst_dict.h"
#include "brst_xref.h"
#include "brst_array.h"
#include "private/brst_array.h"
#include "private/brst_binary.h"
#include "brst_encoder.h"
#include "brst_page.h"
#include "brst_destination.h"
#include "brst_outline.h"
#include "private/brst_md5.h"
#include "private/brst_encrypt_dict.h"
#include "private/brst_catalog.h"
#include "brst_pdfa.h"
#include "brst_doc.h"
#include "private/brst_doc.h"
#include "brst_doc_info.h"
#include "private/brst_info.h"
#include "brst_output_intent.h"
#include "brst_base.h"
#include "brst_error.h"
#include "brst_fontdef.h"
#include "private/brst_fontdef.h"
#include "brst_consts.h"
#include "private/brst_utils.h"

/* This is used to avoid warnings on 'ctime' when compiling in MSVC 9 */
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <string.h>
#include <time.h>

#define HEADER "<?xpacket begin='' id='W5M0MpCehiHzreSzNTczkc9d'?><x:xmpmeta xmlns:x='adobe:ns:meta/' x:xmptk='XMP toolkit 2.9.1-13, framework 1.6'><rdf:RDF xmlns:rdf='http://www.w3.org/1999/02/22-rdf-syntax-ns#' xmlns:iX='http://ns.adobe.com/iX/1.0/'>"
#define DC_HEADER "<rdf:Description xmlns:dc='http://purl.org/dc/elements/1.1/' rdf:about=''>"
#define DC_TITLE_STARTTAG "<dc:title><rdf:Alt><rdf:li xml:lang=\"x-default\">"
#define DC_TITLE_ENDTAG "</rdf:li></rdf:Alt></dc:title>"
#define DC_CREATOR_STARTTAG "<dc:creator><rdf:Seq><rdf:li>"
#define DC_CREATOR_ENDTAG "</rdf:li></rdf:Seq></dc:creator>"
#define DC_DESCRIPTION_STARTTAG "<dc:description><rdf:Alt><rdf:li xml:lang=\"x-default\">"
#define DC_DESCRIPTION_ENDTAG "</rdf:li></rdf:Alt></dc:description>"
#define DC_FOOTER "</rdf:Description>"
#define XMP_HEADER "<rdf:Description xmlns:xmp='http://ns.adobe.com/xap/1.0/' rdf:about=''>"
#define XMP_CREATORTOOL_STARTTAG "<xmp:CreatorTool>"
#define XMP_CREATORTOOL_ENDTAG "</xmp:CreatorTool>"
#define XMP_CREATE_DATE_STARTTAG "<xmp:CreateDate>"
#define XMP_CREATE_DATE_ENDTAG "</xmp:CreateDate>"
#define XMP_MOD_DATE_STARTTAG "<xmp:ModifyDate>"
#define XMP_MOD_DATE_ENDTAG "</xmp:ModifyDate>"
#define XMP_FOOTER "</rdf:Description>"
#define PDF_HEADER "<rdf:Description xmlns:pdf='http://ns.adobe.com/pdf/1.3/' rdf:about=''>"
#define PDF_KEYWORDS_STARTTAG "<pdf:Keywords>"
#define PDF_KEYWORDS_ENDTAG "</pdf:Keywords>"
#define PDF_PRODUCER_STARTTAG "<pdf:Producer>"
#define PDF_PRODUCER_ENDTAG "</pdf:Producer>"
#define PDF_FOOTER "</rdf:Description>"
#define PDFAID_PDFA1A "<rdf:Description rdf:about='' xmlns:pdfaid='http://www.aiim.org/pdfa/ns/id/' pdfaid:part='1' pdfaid:conformance='A'/>"
#define PDFAID_PDFA1B "<rdf:Description rdf:about='' xmlns:pdfaid='http://www.aiim.org/pdfa/ns/id/' pdfaid:part='1' pdfaid:conformance='B'/>"
#define PDFAID_PDFA2A "<rdf:Description rdf:about='' xmlns:pdfaid='http://www.aiim.org/pdfa/ns/id/' pdfaid:part='2' pdfaid:conformance='A'/>"
#define PDFAID_PDFA2B "<rdf:Description rdf:about='' xmlns:pdfaid='http://www.aiim.org/pdfa/ns/id/' pdfaid:part='2' pdfaid:conformance='B'/>"
#define PDFAID_PDFA2U "<rdf:Description rdf:about='' xmlns:pdfaid='http://www.aiim.org/pdfa/ns/id/' pdfaid:part='2' pdfaid:conformance='U'/>"
#define PDFAID_PDFA3A "<rdf:Description rdf:about='' xmlns:pdfaid='http://www.aiim.org/pdfa/ns/id/' pdfaid:part='3' pdfaid:conformance='A'/>"
#define PDFAID_PDFA3B "<rdf:Description rdf:about='' xmlns:pdfaid='http://www.aiim.org/pdfa/ns/id/' pdfaid:part='3' pdfaid:conformance='B'/>"
#define PDFAID_PDFA3U "<rdf:Description rdf:about='' xmlns:pdfaid='http://www.aiim.org/pdfa/ns/id/' pdfaid:part='3' pdfaid:conformance='U'/>"
#define PDFAID_PDFA4 "<rdf:Description rdf:about='' xmlns:pdfaid='http://www.aiim.org/pdfa/ns/id/' pdfaid:part='4' pdfaid:conformance='' pdfaid:rev='2020'/>"
#define PDFAID_PDFA4E "<rdf:Description rdf:about='' xmlns:pdfaid='http://www.aiim.org/pdfa/ns/id/' pdfaid:part='4' pdfaid:conformance='E' pdfaid:rev='2020'/>"
#define PDFAID_PDFA4F "<rdf:Description rdf:about='' xmlns:pdfaid='http://www.aiim.org/pdfa/ns/id/' pdfaid:part='4' pdfaid:conformance='F' pdfaid:rev='2020'/>"
#define FOOTER "</rdf:RDF></x:xmpmeta><?xpacket end='w'?>"

/*
 * Convert date in PDF specific format: D:YYYYMMDDHHmmSS
 * to XMP value in format YYYY-MM-DDTHH:mm:SS+offH:offMin
 */
BRST_STATUS
ConvertDateToXMDate(BRST_Stream stream, BRST_CSTR pDate)
{
    BRST_STATUS ret;

    if (pDate == NULL)
        return BRST_INVALID_PARAMETER;
    if (strlen(pDate) < 16)
        return BRST_INVALID_PARAMETER;
    if (pDate[0] != 'D' || pDate[1] != ':')
        return BRST_INVALID_PARAMETER;
    pDate += 2;
    /* Copy YYYY */
    ret = BRST_Stream_Write(stream, (const BRST_BYTE*)pDate, 4);
    if (ret != BRST_OK)
        return ret;
    pDate += 4;
    /* Write -MM */
    ret = BRST_Stream_Write(stream, (const BRST_BYTE*)"-", 1);
    if (ret != BRST_OK)
        return ret;
    ret = BRST_Stream_Write(stream, (const BRST_BYTE*)pDate, 2);
    if (ret != BRST_OK)
        return ret;
    pDate += 2;
    /* Write -DD */
    ret = BRST_Stream_Write(stream, (const BRST_BYTE*)"-", 1);
    if (ret != BRST_OK)
        return ret;
    ret = BRST_Stream_Write(stream, (const BRST_BYTE*)pDate, 2);
    if (ret != BRST_OK)
        return ret;
    pDate += 2;
    /* Write THH */
    ret = BRST_Stream_Write(stream, (const BRST_BYTE*)"T", 1);
    if (ret != BRST_OK)
        return ret;
    ret = BRST_Stream_Write(stream, (const BRST_BYTE*)pDate, 2);
    if (ret != BRST_OK)
        return ret;
    pDate += 2;
    /* Write :mm */
    ret = BRST_Stream_Write(stream, (const BRST_BYTE*)":", 1);
    if (ret != BRST_OK)
        return ret;
    ret = BRST_Stream_Write(stream, (const BRST_BYTE*)pDate, 2);
    if (ret != BRST_OK)
        return ret;
    pDate += 2;
    /* Write :SS */
    ret = BRST_Stream_Write(stream, (const BRST_BYTE*)":", 1);
    if (ret != BRST_OK)
        return ret;
    ret = BRST_Stream_Write(stream, (const BRST_BYTE*)pDate, 2);
    if (ret != BRST_OK)
        return ret;
    pDate += 2;
    /* Write +... */
    if (pDate[0] == 0 || pDate[0] == 'Z') {
        ret = BRST_Stream_Write(stream, (const BRST_BYTE*)"Z", 1);
        return ret;
    }
    if (pDate[0] == '+' || pDate[0] == '-') {
        ret = BRST_Stream_Write(stream, (const BRST_BYTE*)pDate, 3);
        if (ret != BRST_OK)
            return ret;
        pDate += 4;
        ret = BRST_Stream_Write(stream, (const BRST_BYTE*)":", 1);
        if (ret != BRST_OK)
            return ret;
        ret = BRST_Stream_Write(stream, (const BRST_BYTE*)pDate, 2);
        if (ret != BRST_OK)
            return ret;
        return ret;
    }
    return BRST_Error_Set(stream->error, BRST_INVALID_PARAMETER, 0);
}

/* Generate an ID for the trailer dict, PDF/A needs this.
   TODO: Better algorithm for generate unique ID.
*/
BRST_STATUS
BRST_PDFA_GenerateID(BRST_Doc pdf)
{
    BRST_Array id;
    BRST_BYTE* currentTime;
    BRST_BYTE idkey[BRST_MD5_KEY_LEN];
    BRST_MD5_CTX md5_ctx;
    time_t ltime;

    ltime       = time(NULL);
    currentTime = (BRST_BYTE*)ctime(&ltime);

    id = BRST_Dict_Item(pdf->trailer, "ID", BRST_OCLASS_ARRAY);
    if (!id) {
        id = BRST_Array_New(pdf->mmgr);

        if (!id || BRST_Dict_Add(pdf->trailer, "ID", id) != BRST_OK)
            return BRST_Error_Code(pdf->error);

        BRST_MD5Init(&md5_ctx);
        BRST_MD5Update(&md5_ctx, (BRST_BYTE*)"libHaru", sizeof("libHaru") - 1);
        BRST_MD5Update(&md5_ctx, currentTime, BRST_StrLen((const char*)currentTime, -1));
        BRST_MD5Final(idkey, &md5_ctx);

        if (BRST_Array_Add(id, BRST_Binary_New(pdf->mmgr, idkey, BRST_MD5_KEY_LEN)) != BRST_OK)
            return BRST_Error_Code(pdf->error);

        if (BRST_Array_Add(id, BRST_Binary_New(pdf->mmgr, idkey, BRST_MD5_KEY_LEN)) != BRST_OK)
            return BRST_Error_Code(pdf->error);

        return BRST_OK;
    }

    return BRST_OK;
}

// TODO Разобраься с именованием функций, они должны включать _Doc_?
/* Add XMP Metadata for PDF/A */
BRST_STATUS
BRST_PDFA_AddXmpMetadata(BRST_Doc pdf)
{
    BRST_Dict markinfo;
    BRST_Dict structTreeRoot;
    BRST_Array k;
    BRST_OutputIntent xmp;
    BRST_STATUS ret;
    BRST_PDFVer conformanceVersion;

    const char* dc_title       = NULL;
    const char* dc_creator     = NULL;
    const char* dc_description = NULL;

    const char* xmp_CreatorTool = NULL;
    const char* xmp_CreateDate  = NULL;
    const char* xmp_ModifyDate  = NULL;

    const char* pdf_Keywords = NULL;
    const char* pdf_Producer = NULL;

    if (!BRST_Doc_Initialized(pdf)) {
        return BRST_INVALID_DOCUMENT;
    }

    markinfo = BRST_Dict_New(pdf->mmgr);
    if (!markinfo)
        return BRST_FAILED_TO_ALLOC_MEM;

    ret = BRST_OK;
    ret += BRST_Dict_Add(pdf->catalog, "MarkInfo", markinfo);

    ret += BRST_Dict_AddBoolean(markinfo, "Marked", BRST_TRUE);

    structTreeRoot = BRST_Dict_New(pdf->mmgr);
    if (!structTreeRoot)
        return BRST_FAILED_TO_ALLOC_MEM;
    ret += BRST_Dict_Add(pdf->catalog, "StructTreeRoot", structTreeRoot);
    ret += BRST_Dict_AddName(structTreeRoot, "Type", "StructTreeRoot");

    k = BRST_Array_New(pdf->mmgr);
    if (!k)
        return BRST_FAILED_TO_ALLOC_MEM;
    ret += BRST_Dict_Add(structTreeRoot, "K", k);

    dc_title       = (const char*)BRST_Doc_InfoAttr(pdf, BRST_INFO_TITLE);
    dc_creator     = (const char*)BRST_Doc_InfoAttr(pdf, BRST_INFO_AUTHOR);
    dc_description = (const char*)BRST_Doc_InfoAttr(pdf, BRST_INFO_SUBJECT);

    xmp_CreateDate  = (const char*)BRST_Doc_InfoAttr(pdf, BRST_INFO_CREATION_DATE);
    xmp_ModifyDate  = (const char*)BRST_Doc_InfoAttr(pdf, BRST_INFO_MOD_DATE);
    xmp_CreatorTool = (const char*)BRST_Doc_InfoAttr(pdf, BRST_INFO_CREATOR);

    pdf_Keywords = (const char*)BRST_Doc_InfoAttr(pdf, BRST_INFO_KEYWORDS);
    pdf_Producer = (const char*)BRST_Doc_InfoAttr(pdf, BRST_INFO_PRODUCER);

    if ((dc_title != NULL) || (dc_creator != NULL) || (dc_description != NULL)
        || (xmp_CreateDate != NULL) || (xmp_ModifyDate != NULL) || (xmp_CreatorTool != NULL)
        || (pdf_Keywords != NULL)) {

        xmp = BRST_DictStream_New(pdf->mmgr, pdf->xref);
        if (!xmp) {
            return BRST_INVALID_STREAM;
        }

        BRST_Dict_AddName(xmp, "Type", "Metadata");
        BRST_Dict_AddName(xmp, "Subtype", "XML");

        ret = BRST_OK;
        ret += BRST_Stream_WriteStr(xmp->stream, HEADER);

        /* Add the dc block */
        if ((dc_title != NULL) || (dc_creator != NULL) || (dc_description != NULL)) {
            ret += BRST_Stream_WriteStr(xmp->stream, DC_HEADER);

            if (dc_title != NULL) {
                ret += BRST_Stream_WriteStr(xmp->stream, DC_TITLE_STARTTAG);
                ret += BRST_Stream_WriteStr(xmp->stream, dc_title);
                ret += BRST_Stream_WriteStr(xmp->stream, DC_TITLE_ENDTAG);
            }

            if (dc_creator != NULL) {
                ret += BRST_Stream_WriteStr(xmp->stream, DC_CREATOR_STARTTAG);
                ret += BRST_Stream_WriteStr(xmp->stream, dc_creator);
                ret += BRST_Stream_WriteStr(xmp->stream, DC_CREATOR_ENDTAG);
            }

            if (dc_description != NULL) {
                ret += BRST_Stream_WriteStr(xmp->stream, DC_DESCRIPTION_STARTTAG);
                ret += BRST_Stream_WriteStr(xmp->stream, dc_description);
                ret += BRST_Stream_WriteStr(xmp->stream, DC_DESCRIPTION_ENDTAG);
            }

            ret += BRST_Stream_WriteStr(xmp->stream, DC_FOOTER);
        }

        /* Add the xmp block */
        if ((xmp_CreateDate != NULL) || (xmp_ModifyDate != NULL) || (xmp_CreatorTool != NULL)) {
            ret += BRST_Stream_WriteStr(xmp->stream, XMP_HEADER);

            /* Add CreateDate, ModifyDate, and CreatorTool */
            if (xmp_CreatorTool != NULL) {
                ret += BRST_Stream_WriteStr(xmp->stream, XMP_CREATORTOOL_STARTTAG);
                ret += BRST_Stream_WriteStr(xmp->stream, xmp_CreatorTool);
                ret += BRST_Stream_WriteStr(xmp->stream, XMP_CREATORTOOL_ENDTAG);
            }

            if (xmp_CreateDate != NULL) {
                ret += BRST_Stream_WriteStr(xmp->stream, XMP_CREATE_DATE_STARTTAG);
                /* Convert date to XMP compatible format */
                ret += ConvertDateToXMDate(xmp->stream, xmp_CreateDate);
                ret += BRST_Stream_WriteStr(xmp->stream, XMP_CREATE_DATE_ENDTAG);
            }

            if (xmp_ModifyDate != NULL) {
                ret += BRST_Stream_WriteStr(xmp->stream, XMP_MOD_DATE_STARTTAG);
                ret += ConvertDateToXMDate(xmp->stream, xmp_ModifyDate);
                ret += BRST_Stream_WriteStr(xmp->stream, XMP_MOD_DATE_ENDTAG);
            }

            ret += BRST_Stream_WriteStr(xmp->stream, XMP_FOOTER);
        }

        /* Add the pdf block */
        if ((pdf_Keywords != NULL) || (pdf_Producer != NULL)) {
            ret += BRST_Stream_WriteStr(xmp->stream, PDF_HEADER);

            if (pdf_Keywords != NULL) {
                ret += BRST_Stream_WriteStr(xmp->stream, PDF_KEYWORDS_STARTTAG);
                ret += BRST_Stream_WriteStr(xmp->stream, pdf_Keywords);
                ret += BRST_Stream_WriteStr(xmp->stream, PDF_KEYWORDS_ENDTAG);
            }

            if (pdf_Producer != NULL) {
                ret += BRST_Stream_WriteStr(xmp->stream, PDF_PRODUCER_STARTTAG);
                ret += BRST_Stream_WriteStr(xmp->stream, pdf_Producer);
                ret += BRST_Stream_WriteStr(xmp->stream, PDF_PRODUCER_ENDTAG);
            }

            ret += BRST_Stream_WriteStr(xmp->stream, PDF_FOOTER);
        }

        /* Add the pdfaid block */
        conformanceVersion = -1;
        switch (pdf->pdfa_type) {
        case BRST_PDFA_NON_PDFA:
            break;
        case BRST_PDFA_1A:
            ret += BRST_Stream_WriteStr(xmp->stream, PDFAID_PDFA1A);
            conformanceVersion = BRST_VER_14;
            break;
        case BRST_PDFA_1B:
            ret += BRST_Stream_WriteStr(xmp->stream, PDFAID_PDFA1B);
            conformanceVersion = BRST_VER_14;
            break;
        case BRST_PDFA_2A:
            ret += BRST_Stream_WriteStr(xmp->stream, PDFAID_PDFA2A);
            conformanceVersion = BRST_VER_17;
            break;
        case BRST_PDFA_2B:
            ret += BRST_Stream_WriteStr(xmp->stream, PDFAID_PDFA2B);
            conformanceVersion = BRST_VER_17;
            break;
        case BRST_PDFA_2U:
            ret += BRST_Stream_WriteStr(xmp->stream, PDFAID_PDFA2U);
            conformanceVersion = BRST_VER_17;
            break;
        case BRST_PDFA_3A:
            ret += BRST_Stream_WriteStr(xmp->stream, PDFAID_PDFA3A);
            conformanceVersion = BRST_VER_17;
            break;
        case BRST_PDFA_3B:
            ret += BRST_Stream_WriteStr(xmp->stream, PDFAID_PDFA3B);
            conformanceVersion = BRST_VER_17;
            break;
        case BRST_PDFA_3U:
            ret += BRST_Stream_WriteStr(xmp->stream, PDFAID_PDFA3U);
            conformanceVersion = BRST_VER_17;
            break;
        case BRST_PDFA_4:
            ret += BRST_Stream_WriteStr(xmp->stream, PDFAID_PDFA4);
            conformanceVersion = BRST_VER_20;
            break;
        case BRST_PDFA_4E:
            ret += BRST_Stream_WriteStr(xmp->stream, PDFAID_PDFA4E);
            conformanceVersion = BRST_VER_20;
            break;
        case BRST_PDFA_4F:
            ret += BRST_Stream_WriteStr(xmp->stream, PDFAID_PDFA4F);
            conformanceVersion = BRST_VER_20;
            break;
        }

        /* Update the PDF number version */
        pdf->pdf_version = (pdf->pdf_version > conformanceVersion ? pdf->pdf_version : conformanceVersion);

        /* Append additionnal specific XMP extensions */
        {
            BRST_UINT i;
            BRST_List list;

            list = pdf->xmp_extensions;
            for (i = 0; i < BRST_List_Count(list); i++) {
                BRST_Stream_WriteStr(xmp->stream, (const char*)BRST_List_ItemAt(list, i));
            }
        }

        ret += BRST_Stream_WriteStr(xmp->stream, FOOTER);

        if (ret != BRST_OK) {
            return BRST_INVALID_STREAM;
        }

        if ((ret = BRST_Dict_Add(pdf->catalog, "Metadata", xmp)) != BRST_OK) {
            return ret;
        }

        return BRST_PDFA_GenerateID(pdf);
    }

    return ret;
}

BRST_STATUS
BRST_PDFA_AddXmpExtension(BRST_Doc pdf,
    BRST_CSTR xmp_extension)
{
    BRST_UINT xmp_extension_size;
    void* xmp_extension_copy;

    if (xmp_extension == NULL || xmp_extension[0] == 0)
        return BRST_OK;

    xmp_extension_size = (BRST_UINT)strlen(xmp_extension);
    xmp_extension_copy = BRST_GetMem(pdf->mmgr, xmp_extension_size + 1);
    if (xmp_extension_copy == NULL)
        return BRST_Error_Check(pdf->error);

    strcpy(xmp_extension_copy, xmp_extension);
    return BRST_List_Add(pdf->xmp_extensions, xmp_extension_copy);
}

void BRST_PDFA_ClearXmpExtensions(BRST_Doc pdf)
{
    BRST_UINT i;
    BRST_List list;

    list = pdf->xmp_extensions;
    for (i = 0; i < BRST_List_Count(list); i++) {
        BRST_FreeMem(pdf->mmgr, BRST_List_ItemAt(list, i));
    }
    BRST_List_Clear(pdf->xmp_extensions);
}

/* Function to add one outputintents to the PDF
 * iccname - name of default ICC profile
 * iccdict - dictionary containing number of components
 *           and stream with ICC profile
 *
 * How to use:
 * 1. Create dictionary with ICC profile
 *    BRST_Dict icc = BRST_DictStream_New (pDoc->mmgr, pDoc->xref);
 *    if(icc==NULL) return false;
 *    BRST_Dict_AddNumber (icc, "N", 3);
 *    BRST_STATUS ret = BRST_Stream_Write (icc->stream, (const BRST_BYTE *)pICCData, dwICCSize);
 *    if(ret!=BRST_OK) {
 *      BRST_Dict_Free(icc);
 *      return false;
 *    }
 *
 * 2. Call this function
 */

BRST_STATUS
BRST_PDFA_AppendOutputIntents(BRST_Doc pdf, BRST_CSTR iccname, BRST_Dict iccdict)
{
    BRST_Array intents;
    BRST_Dict intent;
    BRST_STATUS ret;
    if (!BRST_Doc_Initialized(pdf))
        return BRST_INVALID_DOCUMENT;

    /* prepare intent */
    intent = BRST_Dict_New(pdf->mmgr);
    ret    = BRST_Xref_Add(pdf->xref, intent);
    if (ret != BRST_OK) {
        BRST_Dict_Free(intent);
        return ret;
    }
    ret += BRST_Dict_AddName(intent, "Type", "OutputIntent");
    ret += BRST_Dict_AddName(intent, "S", "GTS_PDFA1");
    ret += BRST_Dict_Add(intent, "OutputConditionIdentifier", BRST_String_New(pdf->mmgr, iccname, NULL));
    ret += BRST_Dict_Add(intent, "OutputCondition", BRST_String_New(pdf->mmgr, iccname, NULL));
    ret += BRST_Dict_Add(intent, "Info", BRST_String_New(pdf->mmgr, iccname, NULL));
    ret += BRST_Dict_Add(intent, "DestOutputProfile ", iccdict);
    if (ret != BRST_OK) {
        BRST_Dict_Free(intent);
        return ret;
    }

    /* Copied from BRST_AddIntent - not public function */
    intents = BRST_Dict_Item(pdf->catalog, "OutputIntents", BRST_OCLASS_ARRAY);
    if (intents == NULL) {
        intents = BRST_Array_New(pdf->mmgr);
        if (intents) {
            ret = BRST_Dict_Add(pdf->catalog, "OutputIntents", intents);
            if (ret != BRST_OK) {
                BRST_Error_Check(pdf->error);
                return BRST_Error_DetailCode(pdf->error);
            }
        }
    }

    BRST_Array_Add(intents, intent);
    return BRST_Error_DetailCode(pdf->error);
}
