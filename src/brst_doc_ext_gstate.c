// TODO Включить в CMakeLists.txt

BRST_EXPORT(BRST_ExtGState)
BRST_CreateExtGState(BRST_Doc pdf)
{
    BRST_ExtGState ext_gstate;

    if (!BRST_Doc_Initialized(pdf))
        return NULL;

    pdf->pdf_version = (pdf->pdf_version > BRST_VER_14 ? pdf->pdf_version : BRST_VER_14);

    ext_gstate = BRST_ExtGState_New(pdf->mmgr, pdf->xref);
    if (!ext_gstate)
        BRST_Error_Check(&pdf->error);

    return ext_gstate;
}
