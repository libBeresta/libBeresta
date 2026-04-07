#ifndef BRST_ERROR_H
#define BRST_ERROR_H

#include "brst_external.h"
#include "brst_types.h"
#include "brst_error_handler.h"
#include "brst_doc.h"

/* Коды ошибок */
#define BRST_ARRAY_COUNT_ERR                      0x1001
#define BRST_ARRAY_ITEM_NOT_FOUND                 0x1002
#define BRST_ARRAY_ITEM_UNEXPECTED_TYPE           0x1003
#define BRST_BINARY_LENGTH_ERR                    0x1004
#define BRST_CANNOT_GET_PALETTE                   0x1005
#define BRST_DICT_COUNT_ERR                       0x1007
#define BRST_DICT_ITEM_NOT_FOUND                  0x1008
#define BRST_DICT_ITEM_UNEXPECTED_TYPE            0x1009
#define BRST_DICT_STREAM_LENGTH_NOT_FOUND         0x100A
#define BRST_DOC_ENCRYPTDICT_NOT_FOUND            0x100B
#define BRST_DOC_INVALID_OBJECT                   0x100C
#define BRST_DUPLICATE_REGISTRATION               0x100E
#define BRST_EXCEED_JWW_CODE_NUM_LIMIT            0x100F
#define BRST_ENCRYPT_INVALID_PASSWORD             0x1011
#define BRST_ERR_UNKNOWN_CLASS                    0x1013
#define BRST_EXCEED_GSTATE_LIMIT                  0x1014

/**

  \ingroup error
  \brief Memory allocation failed
  \todo Deprecate constant
*/
#define BRST_FAILED_TO_ALLOC_MEM                  0x1015

/**

  \ingroup error
  \brief An error occurred while processing file I/O

*/
#define BRST_FILE_IO_ERROR                        0x1016
#define BRST_FILE_OPEN_ERROR                      0x1017
#define BRST_FONT_EXISTS                          0x1019
#define BRST_FONT_INVALID_WIDTH_TABLE             0x101A
#define BRST_INVALID_AFM_HEADER                   0x101B
#define BRST_INVALID_ANNOTATION                   0x101C
#define BRST_INVALID_BIT_PER_COMPONENT            0x101E
#define BRST_INVALID_CHAR_MATRIX_DATA             0x101F
#define BRST_INVALID_COLOR_SPACE                  0x1020
#define BRST_INVALID_COMPRESSION_MODE             0x1021
#define BRST_INVALID_DATE_TIME                    0x1022
#define BRST_INVALID_DESTINATION                  0x1023

/**

  \ingroup error
  \brief Document object handle is not valid.

*/
#define BRST_INVALID_DOCUMENT                     0x1025
#define BRST_INVALID_DOCUMENT_STATE               0x1026
#define BRST_INVALID_ENCODER                      0x1027
#define BRST_INVALID_ENCODER_TYPE                 0x1028
#define BRST_INVALID_ENCODING_NAME                0x102B
#define BRST_INVALID_ENCRYPT_KEY_LEN              0x102C
#define BRST_INVALID_FONTDEF_DATA                 0x102D
#define BRST_INVALID_FONTDEF_TYPE                 0x102E
#define BRST_INVALID_FONT_NAME                    0x102F
#define BRST_INVALID_IMAGE                        0x1030
#define BRST_INVALID_JPEG_DATA                    0x1031
#define BRST_INVALID_N_DATA                       0x1032
#define BRST_INVALID_OBJECT                       0x1033
#define BRST_INVALID_OBJ_ID                       0x1034
#define BRST_INVALID_OPERATION                    0x1035
#define BRST_INVALID_OUTLINE                      0x1036
#define BRST_INVALID_PAGE                         0x1037
#define BRST_INVALID_PAGES                        0x1038
#define BRST_INVALID_PARAMETER                    0x1039
#define BRST_INVALID_PNG_IMAGE                    0x103B
#define BRST_INVALID_STREAM                       0x103C
#define BRST_MISSING_FILE_NAME_ENTRY              0x103D
#define BRST_INVALID_TTC_FILE                     0x103F
#define BRST_INVALID_TTC_INDEX                    0x1040
#define BRST_INVALID_WX_DATA                      0x1041
#define BRST_ITEM_NOT_FOUND                       0x1042
#define BRST_LIBPNG_ERROR                         0x1043
#define BRST_NAME_INVALID_VALUE                   0x1044
#define BRST_NAME_OUT_OF_RANGE                    0x1045
#define BRST_PAGES_MISSING_KIDS_ENTRY             0x1049
#define BRST_PAGE_CANNOT_FIND_OBJECT              0x104A
#define BRST_PAGE_CANNOT_GET_ROOT_PAGES           0x104B
#define BRST_PAGE_CANNOT_RESTORE_GSTATE           0x104C
#define BRST_PAGE_CANNOT_SET_PARENT               0x104D
#define BRST_PAGE_FONT_NOT_FOUND                  0x104E
#define BRST_PAGE_INVALID_FONT                    0x104F
#define BRST_PAGE_INVALID_FONT_SIZE               0x1050
#define BRST_PAGE_INVALID_GMODE                   0x1051
#define BRST_PAGE_INVALID_INDEX                   0x1052
#define BRST_PAGE_INVALID_ROTATE_VALUE            0x1053
#define BRST_PAGE_INVALID_SIZE                    0x1054
#define BRST_PAGE_INVALID_XOBJECT                 0x1055
#define BRST_PAGE_OUT_OF_RANGE                    0x1056
#define BRST_REAL_OUT_OF_RANGE                    0x1057
#define BRST_STREAM_EOF                           0x1058
#define BRST_STREAM_READLN_CONTINUE               0x1059
#define BRST_STRING_OUT_OF_RANGE                  0x105B
#define BRST_THIS_FUNC_WAS_SKIPPED                0x105C
#define BRST_TTF_CANNOT_EMBED_FONT                0x105D
#define BRST_TTF_INVALID_CMAP                     0x105E
#define BRST_TTF_INVALID_FORMAT                   0x105F
#define BRST_TTF_MISSING_TABLE                    0x1060
#define BRST_UNSUPPORTED_FONT_TYPE                0x1061
#define BRST_UNSUPPORTED_FUNC                     0x1062
#define BRST_UNSUPPORTED_JPEG_FORMAT              0x1063
#define BRST_UNSUPPORTED_TYPE1_FONT               0x1064
#define BRST_XREF_COUNT_ERR                       0x1065
#define BRST_ZLIB_ERROR                           0x1066
#define BRST_INVALID_PAGE_INDEX                   0x1067
#define BRST_INVALID_URI                          0x1068
#define BRST_PAGE_LAYOUT_OUT_OF_RANGE             0x1069
#define BRST_PAGE_MODE_OUT_OF_RANGE               0x1070
#define BRST_PAGE_NUM_OUT_OF_RANGE                0x1071
#define BRST_ANNOT_INVALID_ICON                   0x1072
#define BRST_ANNOT_INVALID_BORDER_STYLE           0x1073
#define BRST_PAGE_INVALID_ORIENTATION             0x1074
#define BRST_PAGE_INSUFFICIENT_SPACE              0x1076
#define BRST_PAGE_INVALID_DISPLAY_TIME            0x1077
#define BRST_PAGE_INVALID_TRANSITION_TIME         0x1078
#define BRST_INVALID_PAGE_SLIDESHOW_TYPE          0x1079
#define BRST_EXT_GSTATE_OUT_OF_RANGE              0x1080
#define BRST_INVALID_EXT_GSTATE                   0x1081
#define BRST_EXT_GSTATE_READ_ONLY                 0x1082
#define BRST_INVALID_ICC_COMPONENT_NUM            0x1085
#define BRST_PAGE_INVALID_BOUNDARY                0x1086
#define BRST_INVALID_SHADING_TYPE                 0x1088
#define BRST_PAGE_INVALID_PATTERN                 0x1089

/*---------------------------------------------------------------------------*/
/*----- BRST_Error ----------------------------------------------------------*/
struct _BRST_Error_Rec;
typedef struct _BRST_Error_Rec* BRST_Error;

/**

  \ingroup error
  \brief Check error code

  Function returns error code if it is not equal to \ref BRST_OK.
  If error code is not equal to \ref BRST_OK and error handler is set, then error handler is called.

  \param error Error to be checked

  \return Error code from \c error parameter.

*/
BRST_EXPORT(BRST_STATUS)
BRST_Error_Check(
    BRST_Error error
);


/**

  \ingroup error
  \brief Return the last error code of specified document object.

  \copydoc dox_param_pdf

  \return Last error code of document object, or \ref BRST_OK if no last error.

*/
BRST_EXPORT(BRST_STATUS)
BRST_Doc_Error_Code(
    BRST_Doc pdf
);

BRST_EXPORT(BRST_STATUS)
BRST_Doc_Error_DetailCode(
    BRST_Doc pdf
);

/**

  \ingroup error
  \brief Cleanup document error

  Once an error code is set, IO processing functions cannot be invoked.
  In case of executing a function after the cause of the error is fixed,
  an application has to invoke BRST_ResetError() to clear error-code before executing functions.

  \copydoc dox_param_pdf

*/
BRST_EXPORT(void)
BRST_Doc_Error_Reset(
    BRST_Doc pdf
);

/**

  \ingroup doc
  \brief Set a user-defined error handler for document. If subsequent function calls fail, the error handler is called.

  \copydoc dox_param_pdf
  \param user_error_fn User-defined error handler. If \c NULL, previous error handler is revoked.

  \return \ref BRST_OK on success, otherwise returns \ref BRST_INVALID_DOCUMENT.

*/
BRST_EXPORT(BRST_STATUS)
BRST_Doc_Error_SetHandler(
    BRST_Doc           pdf,
    BRST_Error_Handler user_error_fn
);


#endif /* BRST_ERROR_H */