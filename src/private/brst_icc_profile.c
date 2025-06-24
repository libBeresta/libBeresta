// TODO Включить в компиляцию

/* "Perceptual", "RelativeColorimetric", "Saturation", "AbsoluteColorimetric" */
BRST_EXPORT(BRST_OutputIntent)
BRST_ICC_LoadIccFromMem(BRST_Doc pdf,
    BRST_MMgr mmgr,
    BRST_Stream iccdata,
    BRST_Xref xref,
    int numcomponent)
{
    BRST_OutputIntent icc;
    BRST_STATUS ret;

    BRST_PTRACE((" BRST_ICC_LoadIccFromMem\n"));

    icc = BRST_DictStream_New(mmgr, xref);
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
        BRST_RaiseError(&pdf->error, BRST_INVALID_ICC_COMPONENT_NUM, 0);
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
BRST_AddColorspaceFromProfile(BRST_Doc pdf,
    BRST_Dict icc)
{
    BRST_STATUS ret = BRST_OK;
    BRST_Array iccentry;

    if (!BRST_HasDoc(pdf))
        return NULL;

    iccentry = BRST_Array_New(pdf->mmgr);
    if (!iccentry)
        return NULL;

    ret = BRST_Array_AddName(iccentry, "ICCBased");
    if (ret != BRST_OK) {
        BRST_Array_Free(iccentry);
        BRST_CheckError(&pdf->error);
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
BRST_LoadIccProfileFromFile(BRST_Doc pdf,
    const char* icc_file_name,
    int numcomponent)
{
    BRST_Stream iccdata;
    BRST_OutputIntent iccentry;

    BRST_PTRACE((" BRST_LoadIccProfileFromFile\n"));

    if (!BRST_HasDoc(pdf))
        return NULL;

    /* create file stream */
    iccdata = BRST_FileReader_New(pdf->mmgr, icc_file_name);

    if (BRST_Stream_Validate(iccdata)) {
        iccentry = BRST_ICC_LoadIccFromMem(pdf, pdf->mmgr, iccdata, pdf->xref, numcomponent);
    } else
        iccentry = NULL;

    /* destroy file stream */
    if (iccdata)
        BRST_Stream_Free(iccdata);

    if (!iccentry)
        BRST_CheckError(&pdf->error);

    return iccentry;
}
