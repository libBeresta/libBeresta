#ifndef BRST_PAGE_ANNOTATION_H
#define BRST_PAGE_ANNOTATION_H

/**

  \ingroup link
  \brief Create new text annotation object for the page.

  \copydoc dox_param_page
  \param rect Rectangle where annotation is displayed.
  \param text Text to be displayed.
  \param encoder Encoder handle which is used to encode text. If it is \c NULL, PDFDocEncoding is used.

  \return New annotation object handle. If it failed, it returns \c NULL.

  \todo Clarify what PDFDocEncoding is.

  \copydoc dox_error_codes

  - \ref BRST_INVALID_DOCUMENT
  - \ref BRST_FAILED_TO_ALLOC_MEM
  - \ref BRST_INVALID_ENCODER

*/
BRST_EXPORT(BRST_Annotation)
BRST_Page_CreateTextAnnot(
    BRST_Page    page,
    BRST_Rect    rect,
    BRST_CSTR  text,
    BRST_Encoder encoder
);

BRST_EXPORT(BRST_Annotation)
BRST_Page_CreateFreeTextAnnot(
    BRST_Page    page,
    BRST_Rect    rect,
    BRST_CSTR  text,
    BRST_Encoder encoder
);

BRST_EXPORT(BRST_Annotation)
BRST_Page_CreateLineAnnot(
    BRST_Page    page,
    BRST_CSTR  text,
    BRST_Encoder encoder
);

BRST_EXPORT(BRST_Annotation)
BRST_Page_CreateWidgetAnnot(
    BRST_Page page,
    BRST_Rect rect
);

/**

  \ingroup link
  \brief Create new link annotation object for the page.

  \copydoc dox_param_page
  \param rect Rectangle clickable area.
  \param dst Handle of destination object to jump to.

  \return New annotation object handle. If it fails, it returns \c NULL.

  \copydoc dox_error_codes

  - \ref BRST_INVALID_PAGE
  - \ref BRST_FAILED_TO_ALLOC_MEM
  - \ref BRST_INVALID_DESTINATION

*/
BRST_EXPORT(BRST_Annotation)
BRST_Page_CreateLinkAnnot(
    BRST_Page        page,
    BRST_Rect        rect,
    BRST_Destination dst
);

/**

  \ingroup link
  \brief Create new web link annotation object for the page.

  \copydoc dox_param_page
  \param rect Rectangle of clickable area.
  \param uri Destination URI to jump to.

  \return New annotation object handle. If it fails, it returns \c NULL.

  \copydoc dox_error_codes

  - \ref BRST_INVALID_PAGE
  - \ref BRST_FAILED_TO_ALLOC_MEM

*/
BRST_EXPORT(BRST_Annotation)
BRST_Page_CreateURILinkAnnot(
    BRST_Page page,
    BRST_Rect rect,
    BRST_CSTR uri
);

BRST_EXPORT(BRST_Annotation)
BRST_Page_CreateHighlightAnnot(
    BRST_Page    page,
    BRST_Rect    rect,
    BRST_CSTR    text,
    BRST_Encoder encoder
);

BRST_EXPORT(BRST_Annotation)
BRST_Page_CreateUnderlineAnnot(
    BRST_Page    page,
    BRST_Rect    rect,
    BRST_CSTR    text,
    BRST_Encoder encoder
);

BRST_EXPORT(BRST_Annotation)
BRST_Page_CreateSquigglyAnnot(
    BRST_Page    page,
    BRST_Rect    rect,
    BRST_CSTR    text,
    BRST_Encoder encoder
);

BRST_EXPORT(BRST_Annotation)
BRST_Page_CreateStrikeOutAnnot(
    BRST_Page    page,
    BRST_Rect    rect,
    BRST_CSTR    text,
    BRST_Encoder encoder
);

BRST_EXPORT(BRST_Annotation)
BRST_Page_CreatePopupAnnot(
    BRST_Page       page,
    BRST_Rect       rect,
    BRST_Annotation parent
);

BRST_EXPORT(BRST_Annotation)
BRST_Page_CreateStampAnnot(
    BRST_Page           page,
    BRST_Rect           rect,
    BRST_StampAnnotName name,
    BRST_CSTR           text,
    BRST_Encoder        encoder
);

BRST_EXPORT(BRST_Annotation)
BRST_Page_CreateProjectionAnnot(
    BRST_Page    page,
    BRST_Rect    rect,
    BRST_CSTR    text,
    BRST_Encoder encoder
);

BRST_EXPORT(BRST_Annotation)
BRST_Page_CreateSquareAnnot(
    BRST_Page    page,
    BRST_Rect    rect,
    BRST_CSTR    text,
    BRST_Encoder encoder
);

BRST_EXPORT(BRST_Annotation)
BRST_Page_CreateCircleAnnot(
    BRST_Page    page,
    BRST_Rect    rect,
    BRST_CSTR    text,
    BRST_Encoder encoder
);

/**

  \ingroup link
  \brief Define link annotation mouse click appearance.

  \copydoc dox_param_annot
  \param mode Link annotation highlight mode.

  \copydoc dox_return_ok

  \copydoc dox_error_codes

  - \ref BRST_INVALID_ANNOTATION
  - \ref BRST_FAILED_TO_ALLOC_MEM

  \see _BRST_AnnotHighlightMode
*/
BRST_EXPORT(BRST_STATUS)
BRST_LinkAnnot_SetHighlightMode(
    BRST_Annotation         annot,
    BRST_AnnotHighlightMode mode
);

BRST_EXPORT(BRST_STATUS)
BRST_LinkAnnot_SetJavaScript(
    BRST_Annotation annot,
    BRST_JavaScript javascript
);

/**

  \ingroup link
  \brief Define link annotation border style.

  \copydoc dox_param_annot
  \param width Annotation border width
  \param dash_on, dash_off Dash style parameters

  \copydoc dox_return_ok

  \copydoc dox_error_codes

  - \ref BRST_INVALID_ANNOTATION
  - \ref BRST_INVALID_PARAMETER
  - \ref BRST_FAILED_TO_ALLOC_MEM

*/
BRST_EXPORT(BRST_STATUS)
BRST_LinkAnnot_SetBorderStyle(
    BRST_Annotation annot,
    BRST_REAL       width,
    BRST_UINT16     dash_on,
    BRST_UINT16     dash_off
);

/**

  \ingroup link
  \brief Define link annotation icon.

  \copydoc dox_param_annot
  \param icon Link annotation icon type.

  \copydoc dox_return_ok

  \copydoc dox_error_codes

  - \ref BRST_INVALID_ANNOTATION
  - \ref BRST_ANNOT_INVALID_ICON
  - \ref BRST_FAILED_TO_ALLOC_MEM

  \see _BRST_AnnotIcon

*/
BRST_EXPORT(BRST_STATUS)
BRST_TextAnnot_SetIcon(
    BRST_Annotation annot,
    BRST_AnnotIcon  icon
);

/**

  \ingroup link
  \brief Define whether link annotation is initially opened.

  \copydoc dox_param_annot
  \param opened \ref BRST_TRUE if annotation initially displayed open.

  \copydoc dox_return_ok

  \copydoc dox_error_codes

  - \ref BRST_INVALID_ANNOTATION
  - \ref BRST_FAILED_TO_ALLOC_MEM

*/
BRST_EXPORT(BRST_STATUS)
BRST_TextAnnot_SetOpened(
    BRST_Annotation annot,
    BRST_BOOL       opened
);

BRST_EXPORT(BRST_STATUS)
BRST_Annot_SetRGBColor(
    BRST_Annotation annot,
    BRST_RGBColor   color
);

BRST_EXPORT(BRST_STATUS)
BRST_Annot_SetCMYKColor(
    BRST_Annotation annot,
    BRST_CMYKColor  color
);

BRST_EXPORT(BRST_STATUS)
BRST_Annot_SetGrayColor(
    BRST_Annotation annot,
    BRST_REAL       color
);

BRST_EXPORT(BRST_STATUS)
BRST_Annot_SetNoColor(
    BRST_Annotation annot
);

BRST_EXPORT(BRST_STATUS)
BRST_MarkupAnnot_SetTitle(
    BRST_Annotation annot,
    BRST_CSTR       name
);

BRST_EXPORT(BRST_STATUS)
BRST_MarkupAnnot_SetSubject(
    BRST_Annotation annot,
    BRST_CSTR       name
);

BRST_EXPORT(BRST_STATUS)
BRST_MarkupAnnot_SetCreationDate(
    BRST_Annotation annot,
    BRST_Date       value
);

BRST_EXPORT(BRST_STATUS)
BRST_MarkupAnnot_SetTransparency(
    BRST_Annotation annot,
    BRST_REAL       value
);

BRST_EXPORT(BRST_STATUS)
BRST_MarkupAnnot_SetIntent(
    BRST_Annotation  annot,
    BRST_AnnotIntent intent
);

BRST_EXPORT(BRST_STATUS)
BRST_MarkupAnnot_SetPopup(
    BRST_Annotation annot,
    BRST_Annotation popup
);

/* RD entry */
BRST_EXPORT(BRST_STATUS)
BRST_MarkupAnnot_SetRectDiff(
    BRST_Annotation annot,
    BRST_Rect       rect
); 

/* BE entry */
BRST_EXPORT(BRST_STATUS)
BRST_MarkupAnnot_SetCloudEffect(
    BRST_Annotation annot,
    BRST_INT        cloudIntensity
);

/* IC with RGB entry */
BRST_EXPORT(BRST_STATUS)
BRST_MarkupAnnot_SetInteriorRGBColor(
    BRST_Annotation annot,
    BRST_RGBColor   color
);

/* IC with CMYK entry */
BRST_EXPORT(BRST_STATUS)
BRST_MarkupAnnot_SetInteriorCMYKColor(
    BRST_Annotation annot,
    BRST_CMYKColor  color
);

/* IC with Gray entry */
BRST_EXPORT(BRST_STATUS)
BRST_MarkupAnnot_SetInteriorGrayColor(
    BRST_Annotation annot,
    BRST_REAL       color
);

/* IC with No Color entry */
BRST_EXPORT(BRST_STATUS)
BRST_MarkupAnnot_SetInteriorTransparent(
    BRST_Annotation annot
); 

/* l-left, r-right, b-bottom, t-top positions */
BRST_EXPORT(BRST_STATUS)
BRST_TextMarkupAnnot_SetQuadPoints(
    BRST_Annotation annot,
    BRST_Point      lb,
    BRST_Point      rb,
    BRST_Point      rt,
    BRST_Point      lt
);

BRST_EXPORT(BRST_STATUS)
BRST_Annot_Set3DView(
    BRST_MMgr       mmgr,
    BRST_Annotation annot,
    BRST_Annotation annot3d,
    BRST_Dict       view
);

BRST_EXPORT(BRST_STATUS)
BRST_PopupAnnot_SetOpened(
    BRST_Annotation annot,
    BRST_BOOL       opened
);

BRST_EXPORT(BRST_STATUS)
BRST_FreeTextAnnot_SetLineEndingStyle(
    BRST_Annotation           annot, 
    BRST_LineAnnotEndingStyle startStyle, 
    BRST_LineAnnotEndingStyle endStyle
);

/* Callout line will be in default user space */
BRST_EXPORT(BRST_STATUS)
BRST_FreeTextAnnot_Set3PointCalloutLine(
    BRST_Annotation annot,
    BRST_Point      startPoint,
    BRST_Point      kneePoint,
    BRST_Point      endPoint
); 

/* Callout line will be in default user space */
BRST_EXPORT(BRST_STATUS)
BRST_FreeTextAnnot_Set2PointCalloutLine(
    BRST_Annotation annot,
    BRST_Point      startPoint,
    BRST_Point      endPoint
);

BRST_EXPORT(BRST_STATUS)
BRST_FreeTextAnnot_SetDefaultStyle(
    BRST_Annotation annot,
    BRST_CSTR       style
);

BRST_EXPORT(BRST_STATUS)
BRST_LineAnnot_SetPosition(
    BRST_Annotation           annot,
    BRST_Point                startPoint,
    BRST_LineAnnotEndingStyle startStyle,
    BRST_Point                endPoint,
    BRST_LineAnnotEndingStyle endStyle
);

BRST_EXPORT(BRST_STATUS)
BRST_LineAnnot_SetLeader(
    BRST_Annotation annot,
    BRST_INT        leaderLen,
    BRST_INT        leaderExtLen,
    BRST_INT        leaderOffsetLen
);

BRST_EXPORT(BRST_STATUS)
BRST_LineAnnot_SetCaption(
    BRST_Annotation           annot,
    BRST_BOOL                 showCaption,
    BRST_LineAnnotCapPosition position,
    BRST_INT                  horzOffset,
    BRST_INT                  vertOffset
);

/**

  \ingroup link
  \brief Define text annotation border appearance.

  \copydoc dox_param_annot
  \param subtype Border style subtype. See \ref _BRST_BSSubtype.
  \param width Annotation border width
  \param dash_on, dash_off, dash_phase Dash style

  \copydoc dox_return_ok

  \copydoc dox_error_codes

  - \ref BRST_INVALID_ANNOTATION
  - \ref BRST_FAILED_TO_ALLOC_MEM

  \see _BRST_BSSubtype

*/
BRST_EXPORT(BRST_STATUS)
BRST_Annotation_SetBorderStyle(
    BRST_Annotation annot,
    BRST_BSSubtype  subtype,
    BRST_REAL       width,
    BRST_UINT16     dash_on,
    BRST_UINT16     dash_off,
    BRST_UINT16     dash_phase
);

BRST_EXPORT(BRST_STATUS)
BRST_ProjectionAnnot_SetExData(
    BRST_Annotation annot, 
    BRST_ExData exdata
);

BRST_Annotation
BRST_Page_CreateTextMarkupAnnot(
    BRST_Page      page,
    BRST_Rect      rect,
    BRST_CSTR      text,
    BRST_Encoder   encoder,
    BRST_AnnotType subType
);

#ifdef LIBBRST_U3D_SUPPORT

BRST_EXPORT(BRST_Annotation)
BRST_Page_Create3DAnnot(
    BRST_Page  page,
    BRST_Rect  rect,
    BRST_BOOL  tb,
    BRST_BOOL  np,
    BRST_U3D   u3d,
    BRST_Image ap
);

#endif /* LIBBRST_U3D_SUPPORT */

#endif /* BRST_PAGE_ANNOTATION_H */