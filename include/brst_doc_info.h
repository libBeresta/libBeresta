#ifndef BRST_DOC_INFO_H
#define BRST_DOC_INFO_H

#include "brst_doc.h"
#include "brst_date.h"

typedef enum _BRST_InfoType {
    /* date-time type parameters */
    BRST_INFO_CREATION_DATE = 0,
    BRST_INFO_MOD_DATE,

    /* string type parameters */
    BRST_INFO_AUTHOR,
    BRST_INFO_CREATOR,
    BRST_INFO_PRODUCER,
    BRST_INFO_TITLE,
    BRST_INFO_SUBJECT,
    BRST_INFO_KEYWORDS,
    BRST_INFO_TRAPPED,
    BRST_INFO_GTS_PDFX,
    BRST_INFO_EOF
} BRST_InfoType;


/**

  \ingroup prop
  \brief Set the text of \c info dictionary attribute using current encoding of the document.
  If encoding is not set, PDFDocEncoding is used.

  \todo Clarify what PDFDocEncoding is.

  \copydoc dox_param_pdf
  \param type \parblock One of the following values:
    - \ref BRST_INFO_AUTHOR
    - \ref BRST_INFO_CREATOR
    - \ref BRST_INFO_TITLE
    - \ref BRST_INFO_SUBJECT
    - \ref BRST_INFO_KEYWORDS
    \endparblock
  \param value Attribute text to be set.

  \copydoc dox_return_ok

  \copydoc dox_error_codes

    - \ref BRST_INVALID_DOCUMENT
    - \ref BRST_FAILED_TO_ALLOC_MEM
    - \ref BRST_INVALID_PARAMETER

  \see BRST_InfoAttr(), BRST_SetInfoDateAttr()

*/
BRST_EXPORT(BRST_STATUS)
BRST_Doc_SetInfoAttr(
    BRST_Doc      pdf,
    BRST_InfoType type,
    BRST_CSTR     value
);

/**

  \ingroup prop
  \brief Get attribute value from \c info dictionary.

  \copydoc dox_param_pdf
  \param type \parblock One of the following values:
    - \ref BRST_INFO_CREATION_DATE
    - \ref BRST_INFO_MOD_DATE
    - \ref BRST_INFO_AUTHOR
    - \ref BRST_INFO_CREATOR
    - \ref BRST_INFO_TITLE
    - \ref BRST_INFO_SUBJECT
    - \ref BRST_INFO_KEYWORDS
    \endparblock

  \return String value from \c info dictionary. If the information has not been set or an error has occurred, it returns \c NULL.

  \copydoc dox_error_codes

    - \ref BRST_INVALID_DOCUMENT
    - \ref BRST_FAILED_TO_ALLOC_MEM
    - \ref BRST_INVALID_PARAMETER

  \see BRST_SetInfoAttr(), BRST_SetInfoDateAttr()

*/
BRST_EXPORT(BRST_CSTR)
BRST_Doc_InfoAttr(
    BRST_Doc      pdf,
    BRST_InfoType type
);

/**

  \ingroup prop
  \brief Set datetime attribute at \c info dictionary.

  \copydoc dox_param_pdf
  \param type \parblock One of the following attributes:
    - \ref BRST_INFO_CREATION_DATE
    - \ref BRST_INFO_MOD_DATE
    \endparblock
  \param value New attribute value

  \copydoc dox_return_ok

  \copydoc dox_error_codes

  - \ref BRST_INVALID_DOCUMENT
  - \ref BRST_FAILED_TO_ALLOC_MEM
  - \ref BRST_INVALID_PARAMETER
  - \ref BRST_INVALID_DATE_TIME

  \see BRST_InfoAttr(), BRST_SetInfoAttr(), \ref _BRST_Date
*/
BRST_EXPORT(BRST_STATUS)
BRST_Doc_SetInfoDateAttr(
    BRST_Doc      pdf,
    BRST_InfoType type,
    BRST_Date     value
);

#endif /* BRST_DOC_INFO_H */