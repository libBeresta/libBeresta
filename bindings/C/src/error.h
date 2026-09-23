// license
#ifndef BRST_ERROR_H
#define BRST_ERROR_H

struct _BRST_Error_Rec;
typedef struct _BRST_Error_Rec* BRST_Error;

/**
 Виды ошибок, возвращаемых библиотекой
 */
typedef enum _BRST_ErrorKind { 
    /// Превышено количество элементов массива (\ref BRST_LIMIT_MAX_ARRAY).
    BRST_ARRAY_COUNT_ERR = 0x1001,
    /// Элемент массива не найден.
    BRST_ARRAY_ITEM_NOT_FOUND = 0x1002,
    /// Элемент массива неизвестного типа
    BRST_ARRAY_ITEM_UNEXPECTED_TYPE = 0x1003,
    /// 
    BRST_BINARY_LENGTH_ERR = 0x1004,
    /// 
    BRST_CANNOT_GET_PALETTE = 0x1005,
    /// 
    BRST_DICT_COUNT_ERR = 0x1007,
    /// 
    BRST_DICT_ITEM_NOT_FOUND = 0x1008,
    /// 
    BRST_DICT_ITEM_UNEXPECTED_TYPE = 0x1009,
    /// 
    BRST_DICT_STREAM_LENGTH_NOT_FOUND = 0x100A,
    /// 
    BRST_DOC_ENCRYPTDICT_NOT_FOUND = 0x100B,
    /// 
    BRST_DOC_INVALID_OBJECT = 0x100C,
    /// 
    BRST_DUPLICATE_REGISTRATION = 0x100E,
    /// 
    BRST_EXCEED_JWW_CODE_NUM_LIMIT = 0x100F,
    /// 
    BRST_ENCRYPT_INVALID_PASSWORD = 0x1011,
    /// 
    BRST_ERR_UNKNOWN_CLASS = 0x1013,
    /// 
    BRST_EXCEED_GSTATE_LIMIT = 0x1014,
    /// 
    BRST_FAILED_TO_ALLOC_MEM = 0x1015,
    /// 
    BRST_FILE_IO_ERROR = 0x1016,
    /// 
    BRST_FILE_OPEN_ERROR = 0x1017,
    /// 
    BRST_FONT_EXISTS = 0x1019,
    /// 
    BRST_FONT_INVALID_WIDTH_TABLE = 0x101A,
    /// 
    BRST_INVALID_AFM_HEADER = 0x101B,
    /// 
    BRST_INVALID_ANNOTATION = 0x101C,
    /// 
    BRST_INVALID_BIT_PER_COMPONENT = 0x101E,
    /// 
    BRST_INVALID_CHAR_MATRIX_DATA = 0x101F,
    /// 
    BRST_INVALID_COLOR_SPACE = 0x1020,
    /// 
    BRST_INVALID_COMPRESSION_MODE = 0x1021,
    /// 
    BRST_INVALID_DATE_TIME = 0x1022,
    /// 
    BRST_INVALID_DESTINATION = 0x1023,
    /// 
    BRST_INVALID_DOCUMENT = 0x1025,
    /// 
    BRST_INVALID_DOCUMENT_STATE = 0x1026,
    /// 
    BRST_INVALID_ENCODER = 0x1027,
    /// 
    BRST_INVALID_ENCODER_TYPE = 0x1028,
    /// 
    BRST_INVALID_ENCODING_NAME = 0x102B,
    /// 
    BRST_INVALID_ENCRYPT_KEY_LEN = 0x102C,
    /// 
    BRST_INVALID_FONTDEF_DATA = 0x102D,
    /// 
    BRST_INVALID_FONTDEF_TYPE = 0x102E,
    /// 
    BRST_INVALID_FONT_NAME = 0x102F,
    /// 
    BRST_INVALID_IMAGE = 0x1030,
    /// 
    BRST_INVALID_JPEG_DATA = 0x1031,
    /// 
    BRST_INVALID_N_DATA = 0x1032,
    /// 
    BRST_INVALID_OBJECT = 0x1033,
    /// 
    BRST_INVALID_OBJ_ID = 0x1034,
    /// 
    BRST_INVALID_OPERATION = 0x1035,
    /// 
    BRST_INVALID_OUTLINE = 0x1036,
    /// 
    BRST_INVALID_PAGE = 0x1037,
    /// 
    BRST_INVALID_PAGES = 0x1038,
    /// 
    BRST_INVALID_PARAMETER = 0x1039,
    /// 
    BRST_INVALID_PNG_IMAGE = 0x103B,
    /// 
    BRST_INVALID_STREAM = 0x103C,
    /// 
    BRST_MISSING_FILE_NAME_ENTRY = 0x103D,
    /// 
    BRST_INVALID_TTC_FILE = 0x103F,
    /// 
    BRST_INVALID_TTC_INDEX = 0x1040,
    /// 
    BRST_INVALID_WX_DATA = 0x1041,
    /// 
    BRST_ITEM_NOT_FOUND = 0x1042,
    /// 
    BRST_LIBPNG_ERROR = 0x1043,
    /// 
    BRST_NAME_INVALID_VALUE = 0x1044,
    /// 
    BRST_NAME_OUT_OF_RANGE = 0x1045,
    /// 
    BRST_PAGES_MISSING_KIDS_ENTRY = 0x1049,
    /// 
    BRST_PAGE_CANNOT_FIND_OBJECT = 0x104A,
    /// 
    BRST_PAGE_CANNOT_GET_ROOT_PAGES = 0x104B,
    /// 
    BRST_PAGE_CANNOT_RESTORE_GSTATE = 0x104C,
    /// 
    BRST_PAGE_CANNOT_SET_PARENT = 0x104D,
    /// 
    BRST_PAGE_FONT_NOT_FOUND = 0x104E,
    /// 
    BRST_PAGE_INVALID_FONT = 0x104F,
    /// 
    BRST_PAGE_INVALID_FONT_SIZE = 0x1050,
    /// 
    BRST_PAGE_INVALID_GMODE = 0x1051,
    /// 
    BRST_PAGE_INVALID_INDEX = 0x1052,
    /// 
    BRST_PAGE_INVALID_ROTATE_VALUE = 0x1053,
    /// 
    BRST_PAGE_INVALID_SIZE = 0x1054,
    /// 
    BRST_PAGE_INVALID_XOBJECT = 0x1055,
    /// 
    BRST_PAGE_OUT_OF_RANGE = 0x1056,
    /// 
    BRST_REAL_OUT_OF_RANGE = 0x1057,
    /// 
    BRST_STREAM_EOF = 0x1058,
    /// 
    BRST_STREAM_READLN_CONTINUE = 0x1059,
    /// 
    BRST_STRING_OUT_OF_RANGE = 0x105B,
    /// 
    BRST_THIS_FUNC_WAS_SKIPPED = 0x105C,
    /// 
    BRST_TTF_CANNOT_EMBED_FONT = 0x105D,
    /// 
    BRST_TTF_INVALID_CMAP = 0x105E,
    /// 
    BRST_TTF_INVALID_FORMAT = 0x105F,
    /// 
    BRST_TTF_MISSING_TABLE = 0x1060,
    /// 
    BRST_UNSUPPORTED_FONT_TYPE = 0x1061,
    /// 
    BRST_UNSUPPORTED_JPEG_FORMAT = 0x1063,
    /// 
    BRST_UNSUPPORTED_TYPE1_FONT = 0x1064,
    /// 
    BRST_XREF_COUNT_ERR = 0x1065,
    /// 
    BRST_ZLIB_ERROR = 0x1066,
    /// 
    BRST_INVALID_PAGE_INDEX = 0x1067,
    /// 
    BRST_INVALID_URI = 0x1068,
    /// 
    BRST_PAGE_LAYOUT_OUT_OF_RANGE = 0x1069,
    /// 
    BRST_PAGE_MODE_OUT_OF_RANGE = 0x1070,
    /// 
    BRST_PAGE_NUM_STYLE_OUT_OF_RANGE = 0x1071,
    /// 
    BRST_ANNOT_INVALID_ICON = 0x1072,
    /// 
    BRST_ANNOT_INVALID_BORDER_STYLE = 0x1073,
    /// 
    BRST_PAGE_INVALID_DIRECTION = 0x1074,
    /// 
    BRST_PAGE_INSUFFICIENT_SPACE = 0x1076,
    /// 
    BRST_PAGE_INVALID_DISPLAY_TIME = 0x1077,
    /// 
    BRST_PAGE_INVALID_TRANSITION_TIME = 0x1078,
    /// 
    BRST_INVALID_PAGE_SLIDESHOW_TYPE = 0x1079,
    /// 
    BRST_EXT_GSTATE_OUT_OF_RANGE = 0x1080,
    /// 
    BRST_INVALID_EXT_GSTATE = 0x1081,
    /// 
    BRST_EXT_GSTATE_READ_ONLY = 0x1082,
    /// 
    BRST_INVALID_ICC_COMPONENT_NUM = 0x1085,
    /// 
    BRST_PAGE_INVALID_BOUNDARY = 0x1086,
    /// 
    BRST_INVALID_SHADING_TYPE = 0x1088,
    BRST_ERRORKIND_LAST
} BRST_ErrorKind;

/**
  \ingroup error
  \brief Проверяет наличие ошибки, возвращает её код, вызывает обработчик ошибок, если таковой установлен.

  \param error Кодовое представление ошибки

  \return Возвращенный код ошибки.
*/
BRST_EXPORT(BRST_STATUS)
BRST_Error_Check(
   BRST_Error error
);

/**
  \ingroup error
  \brief Получает последний установленный код ошибки для документа.

  \param pdf Документ, для которого запрашивается ошибка.

  \return Последний установленный код ошибки
*/
BRST_EXPORT(BRST_STATUS)
BRST_Doc_Error_Code(
   BRST_Doc pdf
);

/**
  \ingroup error
  \brief Получает детализированный код ошибки для документа.

  \param pdf Описатель объекта документа.

  \return Детализированный код ошибки
*/
BRST_EXPORT(BRST_STATUS)
BRST_Doc_Error_DetailCode(
   BRST_Doc pdf
);

/**
  \ingroup error
  \brief Очистка ошибки документа

  После установки кода ошибки функции обработки ввода-вывода становятся недоступны. 
  Если необходимо вызвать какую-либо функцию после устранения причины возникновения ошибки, 
  приложение должно предварительно очистить код ошибки путём вызова функции BRST_ResetError().

  \param pdf Документ, чей статус ошибки очищается

  \return -
*/
BRST_EXPORT(void)
BRST_Doc_Error_Reset(
   BRST_Doc pdf
);

/**
  \ingroup error
  \brief Назначает собственный обработчик ошибок для документа.

  \param pdf Документ, которому назначается обработчик
  \param user_error_fn Пользовательский обработчик ошибок

  \return \ref BRST_OK при успешном выполнении, иначе возвращает код ошибки и вызывает обработчик ошибок.

  \par Коды ошибок
    - \ref BRST_BRST_INVALID_DOCUMENT
*/
BRST_EXPORT(BRST_STATUS)
BRST_Doc_Error_SetHandler(
   BRST_Doc pdf,
   BRST_Error_Handler user_error_fn
);

#endif /* BRST_ERROR_H */
