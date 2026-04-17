#include "brst_external.h"
#include "brst_types.h"
#include "brst_mmgr.h"
#include "brst_encrypt.h"
#include "brst_stream.h"
#include "brst_xref.h"
#include "brst_dict.h"
#include "private/brst_dict.h"
#include "private/brst_xref.h"
#include "brst_encoder.h"
#include "brst_error.h"
#include "brst_consts.h"
#include "private/brst_utils.h"
#include "brst_base.h"
#include "brst_matrix.h"
#include "brst_array.h"
#include "private/brst_array.h"
#include "private/brst_defines.h"
#include "brst_doc_output_intent.h"
#include "brst_doc.h"
#include "brst_pdfa.h"
#include "brst_page.h"
#include "private/brst_pages.h"
#include "brst_destination.h"
#include "private/brst_catalog.h"
#include "brst_outline.h"
#include "private/brst_encrypt_dict.h"
#include "private/brst_doc.h"
#include "brst_doc_icc_profile.h"

/* "Perceptual", "RelativeColorimetric", "Saturation", "AbsoluteColorimetric" */
BRST_EXPORT(BRST_OutputIntent)
BRST_Doc_IccProfile_LoadFromMemory(BRST_Doc pdf,
    BRST_MMgr mmgr,
    BRST_Stream iccdata,
    BRST_Xref xref,
    int numcomponent)
{
    BRST_OutputIntent icc;
    BRST_STATUS ret;

    BRST_PTRACE(" BRST_Doc_IccProfile_LoadFromMemory\n");

    icc = BRST_Dict_New_Stream_Init(mmgr, xref);
    if (!icc)
        return NULL;

    BRST_Dict_AddNumber(icc, "N", numcomponent);
    switch (numcomponent) {
    case 1:
        BRST_Dict_AddName(icc, "Alternate", "DeviceGray");
        break;
    case 3:
        BRST_Dict_AddName(icc, "Alternate", "DeviceRGB");
        break;
    case 4:
        BRST_Dict_AddName(icc, "Alternate", "DeviceCMYK");
        break;
    default: /* unsupported */
        BRST_Error_Raise(pdf->error, BRST_INVALID_ICC_COMPONENT_NUM, 0);
        BRST_Dict_Free(icc);
        return NULL;
    }

    for (;;) {
        BRST_BYTE buf[BRST_STREAM_BUF_SIZE];
        BRST_UINT len = BRST_STREAM_BUF_SIZE;
        ret           = BRST_Stream_Read(iccdata, buf, &len);

        if (ret != BRST_OK) {
            if (ret == BRST_STREAM_EOF) {
                if (len > 0) {
                    ret = BRST_Stream_Write(icc->stream, buf, len);
                    if (ret != BRST_OK) {
                        BRST_Dict_Free(icc);
                        return NULL;
                    }
                }
                break;
            } else {
                BRST_Dict_Free(icc);
                return NULL;
            }
        }

        if (BRST_Stream_Write(icc->stream, buf, len) != BRST_OK) {
            BRST_Dict_Free(icc);
            return NULL;
        }
    }

    return icc;
}

BRST_EXPORT(BRST_Array)
BRST_Doc_AddColorspaceFromProfile(BRST_Doc pdf,
    BRST_Dict icc)
{
    BRST_STATUS ret = BRST_OK;
    BRST_Array iccentry;

    if (!BRST_Doc_Initialized(pdf))
        return NULL;

    iccentry = BRST_Array_New(pdf->mmgr);
    if (!iccentry)
        return NULL;

    ret = BRST_Array_AddName(iccentry, "ICCBased");
    if (ret != BRST_OK) {
        BRST_Array_Free(iccentry);
        BRST_Error_Check(pdf->error);
        return NULL;
    }

    ret = BRST_Array_Add(iccentry, icc);
    if (ret != BRST_OK) {
        BRST_Array_Free(iccentry);
        return NULL;
    }
    return iccentry;
}

BRST_EXPORT(BRST_OutputIntent)
BRST_Doc_IccProfile_LoadFromFile(BRST_Doc pdf,
    const char* icc_file_name,
    int numcomponent)
{
    BRST_Stream iccdata;
    BRST_OutputIntent iccentry;

    BRST_PTRACE(" BRST_Doc_IccProfile_LoadFromFile\n");

    if (!BRST_Doc_Initialized(pdf))
        return NULL;

    /* create file stream */
    iccdata = BRST_FileReader_New(pdf->mmgr, icc_file_name);

    if (BRST_Stream_Validate(iccdata)) {
        iccentry = BRST_Doc_IccProfile_LoadFromMemory(pdf, pdf->mmgr, iccdata, pdf->xref, numcomponent);
    } else
        iccentry = NULL;

    /* destroy file stream */
    if (iccdata)
        BRST_Stream_Free(iccdata);

    if (!iccentry)
        BRST_Error_Check(pdf->error);

    return iccentry;
}
