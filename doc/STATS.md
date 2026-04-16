# libBeresta generator statistics

## Pointers

| Pointer | Header | Data file |
| :---    | :---   | :---      |
|Array                    |brst_array.h             |array.lsp                |
|Date                     |brst_date.h              |date.lsp                 |
|Dict                     |brst_dict.h              |dict.lsp                 |
|Doc                      |brst_doc.h               |doc.lsp                  |
|Encoder                  |brst_encoder.h           |&ndash;                  |
|Error                    |brst_error.h             |error.lsp                |
|FontDef                  |brst_fontdef.h           |fontdef.lsp              |
|Matrix                   |brst_matrix.h            |matrix.lsp               |
|MMgr                     |brst_mmgr.h              |mmgr.lsp                 |
|Stream                   |brst_stream.h            |stream.lsp               |
|Xref                     |brst_xref.h              |xref.lsp                 |
| Total | 10 of 11 | 90.91% |

## Enums

| Enumeration | Header | Data file |
| :---        | :---   | :---      |
|AnnotFlags               |brst_annotation.h        |annotation.lsp           |
|AnnotHighlightMode       |brst_annotation.h        |annotation.lsp           |
|AnnotIcon                |brst_annotation.h        |annotation.lsp           |
|AnnotIntent              |brst_annotation.h        |&ndash;                  |
|AnnotType                |brst_annotation.h        |annotation.lsp           |
|LineAnnotCapPosition     |brst_annotation.h        |&ndash;                  |
|LineAnnotEndingStyle     |brst_annotation.h        |&ndash;                  |
|StampAnnotName           |brst_annotation.h        |&ndash;                  |
|Date_Parts               |brst_date.h              |date.lsp                 |
|UT_Relationship          |brst_date.h              |date.lsp                 |
|PdfVer                   |brst_doc.h               |doc.lsp                  |
|InfoType                 |brst_doc_info.h          |doc_info.lsp             |
|AFRelationship           |brst_embedded_file.h     |&ndash;                  |
|BaseEncodings            |brst_encoder.h           |&ndash;                  |
|ByteType                 |brst_encoder.h           |&ndash;                  |
|EncoderType              |brst_encoder.h           |&ndash;                  |
|EncodingType             |brst_encoder.h           |&ndash;                  |
|EncryptMode              |brst_encrypt.h           |encrypt.lsp              |
|BlendMode                |brst_geometry_defines.h  |geometry_defines.lsp     |
|BSSubtype                |brst_geometry_defines.h  |&ndash;                  |
|ColorSpace               |brst_geometry_defines.h  |geometry_defines.lsp     |
|LineCap                  |brst_geometry_defines.h  |geometry_defines.lsp     |
|LineJoin                 |brst_geometry_defines.h  |geometry_defines.lsp     |
|PageBoundary             |brst_page.h              |page.lsp                 |
|PageLayout               |brst_page.h              |page.lsp                 |
|PageMode                 |brst_page.h              |page.lsp                 |
|PageNum                  |brst_page.h              |page.lsp                 |
|PageOrientation          |brst_page.h              |page.lsp                 |
|PageTransition           |brst_page.h              |page.lsp                 |
|PageSizes                |brst_page_sizes_iso_216.h|&ndash;                  |
|PDFA_TYPE                |brst_pdfa.h              |&ndash;                  |
|ShadingType              |brst_shading.h           |&ndash;                  |
|Shading_FreeFormTriangleMeshEdgeFlag|brst_shading.h           |&ndash;                  |
|TextAlignment            |brst_text_defines.h      |text_defines.lsp         |
|TextRenderingMode        |brst_text_defines.h      |text_defines.lsp         |
|WritingMode              |brst_text_defines.h      |text_defines.lsp         |
| Total | 22 of 36 | 61.11% |

## Functions

| Function | Header | Data file |
| :---     | :---   | :---      |
|Doc_Contents             |brst_base.h              |&ndash;                  |
|Doc_Destroy              |brst_base.h              |base.lsp                 |
|Doc_Destroy_All          |brst_base.h              |base.lsp                 |
|Doc_Free                 |brst_base.h              |base.lsp                 |
|Doc_Initialize           |brst_base.h              |base.lsp                 |
|Doc_Initialized          |brst_base.h              |base.lsp                 |
|Doc_MMgr                 |brst_base.h              |base.lsp                 |
|Doc_New                  |brst_base.h              |base.lsp                 |
|Doc_New_Empty            |brst_base.h              |base.lsp                 |
|Doc_New_Ex               |brst_base.h              |base.lsp                 |
|PageSize_Height          |brst_base.h              |base.lsp                 |
|PageSize_Width           |brst_base.h              |base.lsp                 |
|Version                  |brst_base.h              |base.lsp                 |
|Date_Free                |brst_date.h              |date.lsp                 |
|Date_New                 |brst_date.h              |&ndash;                  |
|Date_Now                 |brst_date.h              |date.lsp                 |
|Date_Part                |brst_date.h              |date.lsp                 |
|Date_Validate            |brst_date.h              |date.lsp                 |
|Destination_SetFit       |brst_destination.h       |destination.lsp          |
|Destination_SetFitB      |brst_destination.h       |destination.lsp          |
|Destination_SetFitBH     |brst_destination.h       |destination.lsp          |
|Destination_SetFitBV     |brst_destination.h       |destination.lsp          |
|Destination_SetFitH      |brst_destination.h       |destination.lsp          |
|Destination_SetFitR      |brst_destination.h       |destination.lsp          |
|Destination_SetFitV      |brst_destination.h       |destination.lsp          |
|Destination_SetXYZ       |brst_destination.h       |destination.lsp          |
|Doc_Page_CreateWidgetAnnot_WhiteOnlyWhilePrint|brst_doc_annotation.h    |&ndash;                  |
|Doc_SetCompressionMode   |brst_doc_compression.h   |doc_compression.lsp      |
|Doc_AttachFile           |brst_doc_embedded_file.h |doc_embedded_file.lsp    |
|Doc_Encoder_Current      |brst_doc_encoder.h       |doc_encoder.lsp          |
|Doc_Encoder_Prepare      |brst_doc_encoder.h       |doc_encoder.lsp          |
|Doc_Encoder_SetCurrent   |brst_doc_encoder.h       |doc_encoder.lsp          |
|Doc_UseCNSEncodings      |brst_doc_encoding_cns.h  |&ndash;                  |
|Doc_UseCNSFonts          |brst_doc_encoding_cns.h  |&ndash;                  |
|Doc_UseCNTEncodings      |brst_doc_encoding_cnt.h  |&ndash;                  |
|Doc_UseCNTFonts          |brst_doc_encoding_cnt.h  |&ndash;                  |
|Doc_UseJPEncodings       |brst_doc_encoding_jp.h   |&ndash;                  |
|Doc_UseJPFonts           |brst_doc_encoding_jp.h   |&ndash;                  |
|Doc_UseKREncodings       |brst_doc_encoding_kr.h   |&ndash;                  |
|Doc_UseKRFonts           |brst_doc_encoding_kr.h   |&ndash;                  |
|Doc_UseUTFEncodings      |brst_doc_encoding_utf.h  |doc_encoding_utf.lsp     |
|Doc_Create_ExtGState     |brst_doc_ext_gstate.h    |doc_ext_gstate.lsp       |
|Doc_Font                 |brst_doc_font.h          |doc_font.lsp             |
|Doc_TTFont_LoadFromFile  |brst_doc_font.h          |doc_font.lsp             |
|Doc_TTFont_LoadFromFile2 |brst_doc_font.h          |doc_font.lsp             |
|Doc_TTFont_LoadFromMemory|brst_doc_font.h          |doc_font.lsp             |
|Doc_Type1Font_LoadFromFile|brst_doc_font.h          |doc_font.lsp             |
|Doc_IccProfile_LoadFromFile|brst_doc_icc_profile.h   |&ndash;                  |
|Doc_IccProfile_LoadFromMemory|brst_doc_icc_profile.h   |&ndash;                  |
|Doc_Image_Jpeg_LoadFromFile|brst_doc_image_jpeg.h    |doc_image_jpeg.lsp       |
|Doc_Image_Jpeg_LoadFromMemory|brst_doc_image_jpeg.h    |doc_image_jpeg.lsp       |
|Doc_Image_Png_LoadFromFile|brst_doc_image_png.h     |doc_image_png.lsp        |
|Doc_Image_Png_LoadFromFile2|brst_doc_image_png.h     |doc_image_png.lsp        |
|Doc_Image_Png_LoadFromMemory|brst_doc_image_png.h     |doc_image_png.lsp        |
|Doc_Image_Raw1Bit_LoadFromMemory|brst_doc_image_tiff.h    |doc_image_tiff.lsp       |
|Doc_Image_Raw_LoadFromFile|brst_doc_image_tiff.h    |doc_image_tiff.lsp       |
|Doc_Image_Raw_LoadFromMemory|brst_doc_image_tiff.h    |doc_image_tiff.lsp       |
|Doc_InfoAttr             |brst_doc_info.h          |&ndash;                  |
|Doc_SetInfoAttr          |brst_doc_info.h          |doc_info.lsp             |
|Doc_SetInfoDateAttr      |brst_doc_info.h          |doc_info.lsp             |
|Doc_Matrix_Free          |brst_doc_matrix.h        |doc_matrix.lsp           |
|Doc_Matrix_Identity      |brst_doc_matrix.h        |doc_matrix.lsp           |
|Doc_Matrix_Multiply      |brst_doc_matrix.h        |doc_matrix.lsp           |
|Doc_Matrix_Rotate        |brst_doc_matrix.h        |doc_matrix.lsp           |
|Doc_Matrix_RotateDeg     |brst_doc_matrix.h        |doc_matrix.lsp           |
|Doc_Matrix_Scale         |brst_doc_matrix.h        |doc_matrix.lsp           |
|Doc_Matrix_Skew          |brst_doc_matrix.h        |doc_matrix.lsp           |
|Doc_Matrix_Translate     |brst_doc_matrix.h        |doc_matrix.lsp           |
|Doc_Outline_Create       |brst_doc_outline.h       |&ndash;                  |
|Doc_Pages_SetConfiguration|brst_doc_page.h          |doc_page.lsp             |
|Doc_Page_Add             |brst_doc_page.h          |doc_page.lsp             |
|Doc_Page_AddLabel        |brst_doc_page.h          |doc_page.lsp             |
|Doc_Page_ByIndex         |brst_doc_page.h          |doc_page.lsp             |
|Doc_Page_Current         |brst_doc_page.h          |doc_page.lsp             |
|Doc_Page_Insert          |brst_doc_page.h          |doc_page.lsp             |
|Doc_Page_Layout          |brst_doc_page.h          |doc_page.lsp             |
|Doc_Page_Mode            |brst_doc_page.h          |doc_page.lsp             |
|Doc_Page_SetLayout       |brst_doc_page.h          |doc_page.lsp             |
|Doc_Page_SetMode         |brst_doc_page.h          |doc_page.lsp             |
|Doc_Dict_RGBPatternFillHex_Select|brst_doc_page_pattern.h  |doc_page_pattern.lsp     |
|Doc_Dict_RGBPatternFillUint_Select|brst_doc_page_pattern.h  |doc_page_pattern.lsp     |
|Doc_Dict_RGBPatternFill_Select|brst_doc_page_pattern.h  |doc_page_pattern.lsp     |
|Doc_Page_RGBPatternFillHex_Select|brst_doc_page_pattern.h  |doc_page_pattern.lsp     |
|Doc_Page_RGBPatternFillUint_Select|brst_doc_page_pattern.h  |doc_page_pattern.lsp     |
|Doc_Page_RGBPatternFill_Select|brst_doc_page_pattern.h  |doc_page_pattern.lsp     |
|Doc_Pattern_Stream       |brst_doc_pattern.h       |doc_page_pattern.lsp     |
|Doc_Pattern_Tiling_Create|brst_doc_pattern.h       |doc_page_pattern.lsp     |
|Doc_PDFA_AddXmpExtension |brst_doc_pdfa.h          |doc_pdfa.lsp             |
|Doc_PDFA_AppendOutputIntents|brst_doc_pdfa.h          |doc_pdfa.lsp             |
|Doc_PDFA_SetConformance  |brst_doc_pdfa.h          |doc_pdfa.lsp             |
|Doc_SaveToFile           |brst_doc_save.h          |doc_save.lsp             |
|Doc_SaveToStream         |brst_doc_save.h          |doc_save.lsp             |
|Doc_SetEncryptionMode    |brst_doc_security.h      |doc_security.lsp         |
|Doc_SetPassword          |brst_doc_security.h      |doc_security.lsp         |
|Doc_SetPermission        |brst_doc_security.h      |doc_security.lsp         |
|Doc_Stream_Read          |brst_doc_stream.h        |&ndash;                  |
|Doc_Stream_Reset         |brst_doc_stream.h        |&ndash;                  |
|Doc_Stream_Size          |brst_doc_stream.h        |&ndash;                  |
|Doc_SetOpenAction        |brst_doc_viewer.h        |doc_viewer.lsp           |
|Doc_SetViewerPreference  |brst_doc_viewer.h        |doc_viewer.lsp           |
|Doc_ViewerPreference     |brst_doc_viewer.h        |doc_viewer.lsp           |
|Doc_XObject_Create       |brst_doc_xobject.h       |doc_xobject.lsp          |
|Doc_XObject_CreateAsWhiteRect|brst_doc_xobject.h       |doc_xobject.lsp          |
|Doc_XObject_CreateFromImage|brst_doc_xobject.h       |doc_xobject.lsp          |
|EmbeddedFile_SetAFRelationship|brst_embedded_file.h     |&ndash;                  |
|EmbeddedFile_SetCreationDate|brst_embedded_file.h     |&ndash;                  |
|EmbeddedFile_SetDescription|brst_embedded_file.h     |&ndash;                  |
|EmbeddedFile_SetLastModificationDate|brst_embedded_file.h     |&ndash;                  |
|EmbeddedFile_SetName     |brst_embedded_file.h     |&ndash;                  |
|EmbeddedFile_SetSize     |brst_embedded_file.h     |&ndash;                  |
|EmbeddedFile_SetSubtype  |brst_embedded_file.h     |&ndash;                  |
|Encoder_ByteType         |brst_encoder.h           |&ndash;                  |
|Encoder_Type             |brst_encoder.h           |&ndash;                  |
|Encoder_Unicode          |brst_encoder.h           |&ndash;                  |
|Encoder_WritingMode      |brst_encoder.h           |&ndash;                  |
|Doc_Error_Code           |brst_error.h             |error.lsp                |
|Doc_Error_DetailCode     |brst_error.h             |error.lsp                |
|Doc_Error_Reset          |brst_error.h             |error.lsp                |
|Doc_Error_SetHandler     |brst_error.h             |error.lsp                |
|Error_Check              |brst_error.h             |error.lsp                |
|ExtGState_SetAlphaFill   |brst_ext_gstate.h        |ext_gstate.lsp           |
|ExtGState_SetAlphaStroke |brst_ext_gstate.h        |ext_gstate.lsp           |
|ExtGState_SetBlendMode   |brst_ext_gstate.h        |ext_gstate.lsp           |
|Font_Ascent              |brst_font.h              |&ndash;                  |
|Font_BBox                |brst_font.h              |&ndash;                  |
|Font_CapHeight           |brst_font.h              |&ndash;                  |
|Font_Descent             |brst_font.h              |font.lsp                 |
|Font_EncodingName        |brst_font.h              |&ndash;                  |
|Font_FontName            |brst_font.h              |&ndash;                  |
|Font_MeasureText         |brst_font.h              |&ndash;                  |
|Font_TextWidth           |brst_font.h              |&ndash;                  |
|Font_TextWidth2          |brst_font.h              |font.lsp                 |
|Font_UnicodeWidth        |brst_font.h              |&ndash;                  |
|Font_XHeight             |brst_font.h              |&ndash;                  |
|Dict_SetRGBPatternFill   |brst_geometry.h          |&ndash;                  |
|Dict_SetRGBPatternFillHex|brst_geometry.h          |&ndash;                  |
|Dict_SetRGBPatternFillUint|brst_geometry.h          |&ndash;                  |
|Page_Arc                 |brst_geometry.h          |geometry.lsp             |
|Page_Circle              |brst_geometry.h          |geometry.lsp             |
|Page_Clip                |brst_geometry.h          |geometry.lsp             |
|Page_ClosePath           |brst_geometry.h          |geometry.lsp             |
|Page_ClosePathEofillStroke|brst_geometry.h          |geometry.lsp             |
|Page_ClosePathFillStroke |brst_geometry.h          |geometry.lsp             |
|Page_ClosePathStroke     |brst_geometry.h          |geometry.lsp             |
|Page_CMYKFill            |brst_geometry.h          |&ndash;                  |
|Page_CMYKStroke          |brst_geometry.h          |&ndash;                  |
|Page_Concat              |brst_geometry.h          |geometry.lsp             |
|Page_CurveTo             |brst_geometry.h          |geometry.lsp             |
|Page_CurveTo2            |brst_geometry.h          |geometry.lsp             |
|Page_CurveTo3            |brst_geometry.h          |geometry.lsp             |
|Page_Dash                |brst_geometry.h          |&ndash;                  |
|Page_Ellipse             |brst_geometry.h          |geometry.lsp             |
|Page_EndPath             |brst_geometry.h          |geometry.lsp             |
|Page_Eoclip              |brst_geometry.h          |geometry.lsp             |
|Page_Eofill              |brst_geometry.h          |geometry.lsp             |
|Page_EofillStroke        |brst_geometry.h          |geometry.lsp             |
|Page_Fill                |brst_geometry.h          |geometry.lsp             |
|Page_FillColorSpace      |brst_geometry.h          |geometry.lsp             |
|Page_FillStroke          |brst_geometry.h          |geometry.lsp             |
|Page_Flat                |brst_geometry.h          |geometry.lsp             |
|Page_GrayFill            |brst_geometry.h          |geometry.lsp             |
|Page_GrayStroke          |brst_geometry.h          |geometry.lsp             |
|Page_GRestore            |brst_geometry.h          |geometry.lsp             |
|Page_GSave               |brst_geometry.h          |geometry.lsp             |
|Page_LineCap             |brst_geometry.h          |geometry.lsp             |
|Page_LineJoin            |brst_geometry.h          |geometry.lsp             |
|Page_LineTo              |brst_geometry.h          |geometry.lsp             |
|Page_LineWidth           |brst_geometry.h          |geometry.lsp             |
|Page_Matrix              |brst_geometry.h          |geometry.lsp             |
|Page_MiterLimit          |brst_geometry.h          |geometry.lsp             |
|Page_MoveTo              |brst_geometry.h          |geometry.lsp             |
|Page_Rectangle           |brst_geometry.h          |geometry.lsp             |
|Page_RGBFill             |brst_geometry.h          |&ndash;                  |
|Page_RGBStroke           |brst_geometry.h          |&ndash;                  |
|Page_Rotate              |brst_geometry.h          |geometry.lsp             |
|Page_RotateDeg           |brst_geometry.h          |geometry.lsp             |
|Page_Scale               |brst_geometry.h          |geometry.lsp             |
|Page_SetCMYKFill         |brst_geometry.h          |geometry.lsp             |
|Page_SetCMYKStroke       |brst_geometry.h          |geometry.lsp             |
|Page_SetDash             |brst_geometry.h          |geometry.lsp             |
|Page_SetFlat             |brst_geometry.h          |geometry.lsp             |
|Page_SetGrayFill         |brst_geometry.h          |geometry.lsp             |
|Page_SetGrayStroke       |brst_geometry.h          |geometry.lsp             |
|Page_SetLineCap          |brst_geometry.h          |geometry.lsp             |
|Page_SetLineJoin         |brst_geometry.h          |geometry.lsp             |
|Page_SetLineWidth        |brst_geometry.h          |geometry.lsp             |
|Page_SetMiterLimit       |brst_geometry.h          |geometry.lsp             |
|Page_SetRGBFill          |brst_geometry.h          |geometry.lsp             |
|Page_SetRGBFillHex       |brst_geometry.h          |geometry.lsp             |
|Page_SetRGBFillUint      |brst_geometry.h          |geometry.lsp             |
|Page_SetRGBStroke        |brst_geometry.h          |geometry.lsp             |
|Page_SetRGBStrokeHex     |brst_geometry.h          |geometry.lsp             |
|Page_SetRGBStrokeUint    |brst_geometry.h          |geometry.lsp             |
|Page_SetShading          |brst_geometry.h          |&ndash;                  |
|Page_Skew                |brst_geometry.h          |geometry.lsp             |
|Page_Stroke              |brst_geometry.h          |geometry.lsp             |
|Page_StrokeColorSpace    |brst_geometry.h          |geometry.lsp             |
|Page_Translate           |brst_geometry.h          |geometry.lsp             |
|Image_AddSMask           |brst_image.h             |&ndash;                  |
|Image_BitsPerComponent   |brst_image.h             |&ndash;                  |
|Image_ColorSpace         |brst_image.h             |&ndash;                  |
|Image_Height             |brst_image.h             |&ndash;                  |
|Image_SetColorMask       |brst_image.h             |&ndash;                  |
|Image_SetMaskImage       |brst_image.h             |&ndash;                  |
|Image_Size               |brst_image.h             |&ndash;                  |
|Image_Size2              |brst_image.h             |&ndash;                  |
|Image_Width              |brst_image.h             |&ndash;                  |
|Outline_SetDestination   |brst_outline.h           |&ndash;                  |
|Outline_SetOpened        |brst_outline.h           |&ndash;                  |
|AddIntent                |brst_output_intent.h     |&ndash;                  |
|OutputIntent_New         |brst_output_intent.h     |&ndash;                  |
|Annotation_SetBorderStyle|brst_page_annotation.h   |&ndash;                  |
|Annot_Set3DView          |brst_page_annotation.h   |&ndash;                  |
|Annot_SetCMYKColor       |brst_page_annotation.h   |&ndash;                  |
|Annot_SetGrayColor       |brst_page_annotation.h   |&ndash;                  |
|Annot_SetNoColor         |brst_page_annotation.h   |&ndash;                  |
|Annot_SetRGBColor        |brst_page_annotation.h   |&ndash;                  |
|FreeTextAnnot_Set2PointCalloutLine|brst_page_annotation.h   |&ndash;                  |
|FreeTextAnnot_Set3PointCalloutLine|brst_page_annotation.h   |&ndash;                  |
|FreeTextAnnot_SetDefaultStyle|brst_page_annotation.h   |&ndash;                  |
|FreeTextAnnot_SetLineEndingStyle|brst_page_annotation.h   |&ndash;                  |
|LineAnnot_SetCaption     |brst_page_annotation.h   |&ndash;                  |
|LineAnnot_SetLeader      |brst_page_annotation.h   |&ndash;                  |
|LineAnnot_SetPosition    |brst_page_annotation.h   |&ndash;                  |
|LinkAnnot_SetBorderStyle |brst_page_annotation.h   |&ndash;                  |
|LinkAnnot_SetHighlightMode|brst_page_annotation.h   |&ndash;                  |
|LinkAnnot_SetJavaScript  |brst_page_annotation.h   |&ndash;                  |
|MarkupAnnot_SetCloudEffect|brst_page_annotation.h   |&ndash;                  |
|MarkupAnnot_SetCreationDate|brst_page_annotation.h   |&ndash;                  |
|MarkupAnnot_SetIntent    |brst_page_annotation.h   |&ndash;                  |
|MarkupAnnot_SetInteriorCMYKColor|brst_page_annotation.h   |&ndash;                  |
|MarkupAnnot_SetInteriorGrayColor|brst_page_annotation.h   |&ndash;                  |
|MarkupAnnot_SetInteriorRGBColor|brst_page_annotation.h   |&ndash;                  |
|MarkupAnnot_SetInteriorTransparent|brst_page_annotation.h   |&ndash;                  |
|MarkupAnnot_SetPopup     |brst_page_annotation.h   |&ndash;                  |
|MarkupAnnot_SetRectDiff  |brst_page_annotation.h   |&ndash;                  |
|MarkupAnnot_SetSubject   |brst_page_annotation.h   |&ndash;                  |
|MarkupAnnot_SetTitle     |brst_page_annotation.h   |&ndash;                  |
|MarkupAnnot_SetTransparency|brst_page_annotation.h   |&ndash;                  |
|Page_Create3DAnnot       |brst_page_annotation.h   |&ndash;                  |
|Page_CreateCircleAnnot   |brst_page_annotation.h   |&ndash;                  |
|Page_CreateFreeTextAnnot |brst_page_annotation.h   |&ndash;                  |
|Page_CreateHighlightAnnot|brst_page_annotation.h   |&ndash;                  |
|Page_CreateLineAnnot     |brst_page_annotation.h   |&ndash;                  |
|Page_CreateLinkAnnot     |brst_page_annotation.h   |&ndash;                  |
|Page_CreatePopupAnnot    |brst_page_annotation.h   |&ndash;                  |
|Page_CreateProjectionAnnot|brst_page_annotation.h   |&ndash;                  |
|Page_CreateSquareAnnot   |brst_page_annotation.h   |&ndash;                  |
|Page_CreateSquigglyAnnot |brst_page_annotation.h   |&ndash;                  |
|Page_CreateStampAnnot    |brst_page_annotation.h   |&ndash;                  |
|Page_CreateStrikeOutAnnot|brst_page_annotation.h   |&ndash;                  |
|Page_CreateTextAnnot     |brst_page_annotation.h   |&ndash;                  |
|Page_CreateUnderlineAnnot|brst_page_annotation.h   |&ndash;                  |
|Page_CreateURILinkAnnot  |brst_page_annotation.h   |&ndash;                  |
|Page_CreateWidgetAnnot   |brst_page_annotation.h   |&ndash;                  |
|PopupAnnot_SetOpened     |brst_page_annotation.h   |&ndash;                  |
|ProjectionAnnot_SetExData|brst_page_annotation.h   |&ndash;                  |
|TextAnnot_SetIcon        |brst_page_annotation.h   |&ndash;                  |
|TextAnnot_SetOpened      |brst_page_annotation.h   |&ndash;                  |
|TextMarkupAnnot_SetQuadPoints|brst_page_annotation.h   |&ndash;                  |
|Page_DrawImage           |brst_page_image.h        |&ndash;                  |
|Page_CreateDestination   |brst_page_routines.h     |page_routines.lsp        |
|Page_CurrentPos          |brst_page_routines.h     |&ndash;                  |
|Page_CurrentPos2         |brst_page_routines.h     |&ndash;                  |
|Page_GMode               |brst_page_routines.h     |page_routines.lsp        |
|Page_GStateDepth         |brst_page_routines.h     |page_routines.lsp        |
|Page_Height              |brst_page_routines.h     |page_routines.lsp        |
|Page_HorizontalScaling   |brst_page_routines.h     |page_routines.lsp        |
|Page_Insert_Shared_Content_Stream|brst_page_routines.h     |page_routines.lsp        |
|Page_MMgr                |brst_page_routines.h     |page_routines.lsp        |
|Page_New_Content_Stream  |brst_page_routines.h     |&ndash;                  |
|Page_RawWrite            |brst_page_routines.h     |page_routines.lsp        |
|Page_SetBoundary         |brst_page_routines.h     |page_routines.lsp        |
|Page_SetExtGState        |brst_page_routines.h     |page_routines.lsp        |
|Page_SetHeight           |brst_page_routines.h     |page_routines.lsp        |
|Page_SetHorizontalScaling|brst_page_routines.h     |page_routines.lsp        |
|Page_SetRotate           |brst_page_routines.h     |page_routines.lsp        |
|Page_SetSize             |brst_page_routines.h     |page_routines.lsp        |
|Page_SetSlideShow        |brst_page_routines.h     |page_routines.lsp        |
|Page_SetWidth            |brst_page_routines.h     |page_routines.lsp        |
|Page_SetZoom             |brst_page_routines.h     |page_routines.lsp        |
|Page_Width               |brst_page_routines.h     |page_routines.lsp        |
|Dict_XObject_Execute     |brst_page_xobject.h      |page_xobject.lsp         |
|Page_XObject_Execute     |brst_page_xobject.h      |page_xobject.lsp         |
|Stream_Arc               |brst_stream_geometry.h   |&ndash;                  |
|Stream_Circle            |brst_stream_geometry.h   |stream_geometry.lsp      |
|Stream_Clip              |brst_stream_geometry.h   |stream_geometry.lsp      |
|Stream_ClosePath         |brst_stream_geometry.h   |stream_geometry.lsp      |
|Stream_ClosePathEofillStroke|brst_stream_geometry.h   |stream_geometry.lsp      |
|Stream_ClosePathFillStroke|brst_stream_geometry.h   |stream_geometry.lsp      |
|Stream_ClosePathStroke   |brst_stream_geometry.h   |stream_geometry.lsp      |
|Stream_Concat            |brst_stream_geometry.h   |stream_geometry.lsp      |
|Stream_CurveTo           |brst_stream_geometry.h   |stream_geometry.lsp      |
|Stream_CurveTo2          |brst_stream_geometry.h   |stream_geometry.lsp      |
|Stream_CurveTo3          |brst_stream_geometry.h   |stream_geometry.lsp      |
|Stream_Ellipse           |brst_stream_geometry.h   |&ndash;                  |
|Stream_EndPath           |brst_stream_geometry.h   |stream_geometry.lsp      |
|Stream_Eoclip            |brst_stream_geometry.h   |stream_geometry.lsp      |
|Stream_Eofill            |brst_stream_geometry.h   |stream_geometry.lsp      |
|Stream_EofillStroke      |brst_stream_geometry.h   |stream_geometry.lsp      |
|Stream_Fill              |brst_stream_geometry.h   |stream_geometry.lsp      |
|Stream_FillStroke        |brst_stream_geometry.h   |stream_geometry.lsp      |
|Stream_GRestore          |brst_stream_geometry.h   |stream_geometry.lsp      |
|Stream_GSave             |brst_stream_geometry.h   |stream_geometry.lsp      |
|Stream_LineTo            |brst_stream_geometry.h   |stream_geometry.lsp      |
|Stream_MoveTo            |brst_stream_geometry.h   |stream_geometry.lsp      |
|Stream_Rectangle         |brst_stream_geometry.h   |stream_geometry.lsp      |
|Stream_Rotate            |brst_stream_geometry.h   |stream_geometry.lsp      |
|Stream_RotateDeg         |brst_stream_geometry.h   |stream_geometry.lsp      |
|Stream_Scale             |brst_stream_geometry.h   |stream_geometry.lsp      |
|Stream_SetCMYKFill       |brst_stream_geometry.h   |stream_geometry.lsp      |
|Stream_SetCMYKStroke     |brst_stream_geometry.h   |stream_geometry.lsp      |
|Stream_SetDash           |brst_stream_geometry.h   |stream_geometry.lsp      |
|Stream_SetFlat           |brst_stream_geometry.h   |stream_geometry.lsp      |
|Stream_SetGrayFill       |brst_stream_geometry.h   |stream_geometry.lsp      |
|Stream_SetGrayStroke     |brst_stream_geometry.h   |stream_geometry.lsp      |
|Stream_SetLineCap        |brst_stream_geometry.h   |stream_geometry.lsp      |
|Stream_SetLineJoin       |brst_stream_geometry.h   |stream_geometry.lsp      |
|Stream_SetLineWidth      |brst_stream_geometry.h   |stream_geometry.lsp      |
|Stream_SetMiterLimit     |brst_stream_geometry.h   |stream_geometry.lsp      |
|Stream_SetRGBFill        |brst_stream_geometry.h   |stream_geometry.lsp      |
|Stream_SetRGBFillHex     |brst_stream_geometry.h   |stream_geometry.lsp      |
|Stream_SetRGBFillUint    |brst_stream_geometry.h   |stream_geometry.lsp      |
|Stream_SetRGBPatternFill |brst_stream_geometry.h   |&ndash;                  |
|Stream_SetRGBStroke      |brst_stream_geometry.h   |stream_geometry.lsp      |
|Stream_SetRGBStrokeHex   |brst_stream_geometry.h   |stream_geometry.lsp      |
|Stream_SetRGBStrokeUint  |brst_stream_geometry.h   |stream_geometry.lsp      |
|Stream_Skew              |brst_stream_geometry.h   |stream_geometry.lsp      |
|Stream_Stroke            |brst_stream_geometry.h   |stream_geometry.lsp      |
|Stream_Translate         |brst_stream_geometry.h   |stream_geometry.lsp      |
|Stream_BeginText         |brst_stream_text.h       |stream_text.lsp          |
|Stream_EndText           |brst_stream_text.h       |stream_text.lsp          |
|Stream_MoveTextPos       |brst_stream_text.h       |stream_text.lsp          |
|Stream_MoveTextPos2      |brst_stream_text.h       |stream_text.lsp          |
|Stream_MoveToNextLine    |brst_stream_text.h       |stream_text.lsp          |
|Stream_SetTextLeading    |brst_stream_text.h       |stream_text.lsp          |
|Stream_SetTextMatrix     |brst_stream_text.h       |stream_text.lsp          |
|Stream_SetTextRenderingMode|brst_stream_text.h       |stream_text.lsp          |
|Stream_SetTextRise       |brst_stream_text.h       |&ndash;                  |
|Stream_ShowText          |brst_stream_text.h       |stream_text.lsp          |
|Stream_TextOut           |brst_stream_text.h       |stream_text.lsp          |
|Dict_SetFontAndSize      |brst_text.h              |text.lsp                 |
|Page_BeginText           |brst_text.h              |text.lsp                 |
|Page_CharSpace           |brst_text.h              |text.lsp                 |
|Page_CurrentFont         |brst_text.h              |text.lsp                 |
|Page_CurrentFontSize     |brst_text.h              |text.lsp                 |
|Page_CurrentTextPos      |brst_text.h              |&ndash;                  |
|Page_CurrentTextPos2     |brst_text.h              |text.lsp                 |
|Page_EndText             |brst_text.h              |text.lsp                 |
|Page_MeasureText         |brst_text.h              |text.lsp                 |
|Page_MoveTextPos         |brst_text.h              |text.lsp                 |
|Page_MoveTextPos2        |brst_text.h              |text.lsp                 |
|Page_MoveToNextLine      |brst_text.h              |text.lsp                 |
|Page_SetCharSpace        |brst_text.h              |text.lsp                 |
|Page_SetFontAndSize      |brst_text.h              |text.lsp                 |
|Page_SetTextLeading      |brst_text.h              |text.lsp                 |
|Page_SetTextMatrix       |brst_text.h              |text.lsp                 |
|Page_SetTextRenderingMode|brst_text.h              |text.lsp                 |
|Page_SetTextRise         |brst_text.h              |text.lsp                 |
|Page_SetWordSpace        |brst_text.h              |text.lsp                 |
|Page_ShowText            |brst_text.h              |text.lsp                 |
|Page_ShowTextNextLine    |brst_text.h              |text.lsp                 |
|Page_ShowTextNextLineEx  |brst_text.h              |text.lsp                 |
|Page_TextLeading         |brst_text.h              |text.lsp                 |
|Page_TextMatrix          |brst_text.h              |text.lsp                 |
|Page_TextOut             |brst_text.h              |text.lsp                 |
|Page_TextRect            |brst_text.h              |text.lsp                 |
|Page_TextRenderingMode   |brst_text.h              |text.lsp                 |
|Page_TextRise            |brst_text.h              |text.lsp                 |
|Page_TextWidth           |brst_text.h              |text.lsp                 |
|Page_WordSpace           |brst_text.h              |text.lsp                 |
|XObject_Stream           |brst_xobject.h           |xobject.lsp              |
| Total | 254 of 372 | 68.28% |

<small>Generated on: 16.04.2026 10:44</small>
