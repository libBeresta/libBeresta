(:файл "error"
 :указатели ((:имя "Error"))

 :перечисления
       ((:имя "ErrorKind"
         :ru "Виды ошибок, возвращаемых библиотекой"
         :en "Error kind"
         :элементы ((:элемент "BRST_ARRAY_COUNT_ERR"
                     :ru "Превышено количество элементов массива (\\ref BRST_LIMIT_MAX_ARRAY)."
                     :en "Array count limit exceed (\\ref BRST_LIMIT_MAX_ARRAY)."
                     :значение "0x1001")
                    (:элемент "BRST_ARRAY_ITEM_NOT_FOUND"
                     :ru "Элемент массива не найден."
                     :en "Array element not found."
                     :значение "0x1002")
                    (:элемент "BRST_ARRAY_ITEM_UNEXPECTED_TYPE"
                     :ru "Элемент массива неизвестного типа"
                     :en "Array element of unexpected type"
                     :значение "0x1003")
                    (:элемент "BRST_BINARY_LENGTH_ERR"           :ru "" :en "" :значение "0x1004")
                    (:элемент "BRST_CANNOT_GET_PALETTE"          :ru "" :en "" :значение "0x1005")
                    (:элемент "BRST_DICT_COUNT_ERR"              :ru "" :en "" :значение "0x1007")
                    (:элемент "BRST_DICT_ITEM_NOT_FOUND"         :ru "" :en "" :значение "0x1008")
                    (:элемент "BRST_DICT_ITEM_UNEXPECTED_TYPE"   :ru "" :en "" :значение "0x1009")
                    (:элемент "BRST_DICT_STREAM_LENGTH_NOT_FOUND":ru "" :en "" :значение "0x100A")
                    (:элемент "BRST_DOC_ENCRYPTDICT_NOT_FOUND"   :ru "" :en "" :значение "0x100B")
                    (:элемент "BRST_DOC_INVALID_OBJECT"          :ru "" :en "" :значение "0x100C")
                    (:элемент "BRST_DUPLICATE_REGISTRATION"      :ru "" :en "" :значение "0x100E")
                    (:элемент "BRST_EXCEED_JWW_CODE_NUM_LIMIT"   :ru "" :en "" :значение "0x100F")
                    (:элемент "BRST_ENCRYPT_INVALID_PASSWORD"    :ru "" :en "" :значение "0x1011")
                    (:элемент "BRST_ERR_UNKNOWN_CLASS"           :ru "" :en "" :значение "0x1013")
                    (:элемент "BRST_EXCEED_GSTATE_LIMIT"         :ru "" :en "" :значение "0x1014")
                    (:элемент "BRST_FAILED_TO_ALLOC_MEM"         :ru "" :en "" :значение "0x1015")
                    (:элемент "BRST_FILE_IO_ERROR"               :ru "" :en "" :значение "0x1016")
                    (:элемент "BRST_FILE_OPEN_ERROR"             :ru "" :en "" :значение "0x1017")
                    (:элемент "BRST_FONT_EXISTS"                 :ru "" :en "" :значение "0x1019")
                    (:элемент "BRST_FONT_INVALID_WIDTH_TABLE"    :ru "" :en "" :значение "0x101A")
                    (:элемент "BRST_INVALID_AFM_HEADER"          :ru "" :en "" :значение "0x101B")
                    (:элемент "BRST_INVALID_ANNOTATION"          :ru "" :en "" :значение "0x101C")
                    (:элемент "BRST_INVALID_BIT_PER_COMPONENT"   :ru "" :en "" :значение "0x101E")
                    (:элемент "BRST_INVALID_CHAR_MATRIX_DATA"    :ru "" :en "" :значение "0x101F")
                    (:элемент "BRST_INVALID_COLOR_SPACE"         :ru "" :en "" :значение "0x1020")
                    (:элемент "BRST_INVALID_COMPRESSION_MODE"    :ru "" :en "" :значение "0x1021")
                    (:элемент "BRST_INVALID_DATE_TIME"           :ru "" :en "" :значение "0x1022")
                    (:элемент "BRST_INVALID_DESTINATION"         :ru "" :en "" :значение "0x1023")
                    (:элемент "BRST_INVALID_DOCUMENT"            :ru "" :en "" :значение "0x1025")
                    (:элемент "BRST_INVALID_DOCUMENT_STATE"      :ru "" :en "" :значение "0x1026")
                    (:элемент "BRST_INVALID_ENCODER"             :ru "" :en "" :значение "0x1027")
                    (:элемент "BRST_INVALID_ENCODER_TYPE"        :ru "" :en "" :значение "0x1028")
                    (:элемент "BRST_INVALID_ENCODING_NAME"       :ru "" :en "" :значение "0x102B")
                    (:элемент "BRST_INVALID_ENCRYPT_KEY_LEN"     :ru "" :en "" :значение "0x102C")
                    (:элемент "BRST_INVALID_FONTDEF_DATA"        :ru "" :en "" :значение "0x102D")
                    (:элемент "BRST_INVALID_FONTDEF_TYPE"        :ru "" :en "" :значение "0x102E")
                    (:элемент "BRST_INVALID_FONT_NAME"           :ru "" :en "" :значение "0x102F")
                    (:элемент "BRST_INVALID_IMAGE"               :ru "" :en "" :значение "0x1030")
                    (:элемент "BRST_INVALID_JPEG_DATA"           :ru "" :en "" :значение "0x1031")
                    (:элемент "BRST_INVALID_N_DATA"              :ru "" :en "" :значение "0x1032")
                    (:элемент "BRST_INVALID_OBJECT"              :ru "" :en "" :значение "0x1033")
                    (:элемент "BRST_INVALID_OBJ_ID"              :ru "" :en "" :значение "0x1034")
                    (:элемент "BRST_INVALID_OPERATION"           :ru "" :en "" :значение "0x1035")
                    (:элемент "BRST_INVALID_OUTLINE"             :ru "" :en "" :значение "0x1036")
                    (:элемент "BRST_INVALID_PAGE"                :ru "" :en "" :значение "0x1037")
                    (:элемент "BRST_INVALID_PAGES"               :ru "" :en "" :значение "0x1038")
                    (:элемент "BRST_INVALID_PARAMETER"           :ru "" :en "" :значение "0x1039")
                    (:элемент "BRST_INVALID_PNG_IMAGE"           :ru "" :en "" :значение "0x103B")
                    (:элемент "BRST_INVALID_STREAM"              :ru "" :en "" :значение "0x103C")
                    (:элемент "BRST_MISSING_FILE_NAME_ENTRY"     :ru "" :en "" :значение "0x103D")
                    (:элемент "BRST_INVALID_TTC_FILE"            :ru "" :en "" :значение "0x103F")
                    (:элемент "BRST_INVALID_TTC_INDEX"           :ru "" :en "" :значение "0x1040")
                    (:элемент "BRST_INVALID_WX_DATA"             :ru "" :en "" :значение "0x1041")
                    (:элемент "BRST_ITEM_NOT_FOUND"              :ru "" :en "" :значение "0x1042")
                    (:элемент "BRST_LIBPNG_ERROR"                :ru "" :en "" :значение "0x1043")
                    (:элемент "BRST_NAME_INVALID_VALUE"          :ru "" :en "" :значение "0x1044")
                    (:элемент "BRST_NAME_OUT_OF_RANGE"           :ru "" :en "" :значение "0x1045")
                    (:элемент "BRST_PAGES_MISSING_KIDS_ENTRY"    :ru "" :en "" :значение "0x1049")
                    (:элемент "BRST_PAGE_CANNOT_FIND_OBJECT"     :ru "" :en "" :значение "0x104A")
                    (:элемент "BRST_PAGE_CANNOT_GET_ROOT_PAGES"  :ru "" :en "" :значение "0x104B")
                    (:элемент "BRST_PAGE_CANNOT_RESTORE_GSTATE"  :ru "" :en "" :значение "0x104C")
                    (:элемент "BRST_PAGE_CANNOT_SET_PARENT"      :ru "" :en "" :значение "0x104D")
                    (:элемент "BRST_PAGE_FONT_NOT_FOUND"         :ru "" :en "" :значение "0x104E")
                    (:элемент "BRST_PAGE_INVALID_FONT"           :ru "" :en "" :значение "0x104F")
                    (:элемент "BRST_PAGE_INVALID_FONT_SIZE"      :ru "" :en "" :значение "0x1050")
                    (:элемент "BRST_PAGE_INVALID_GMODE"          :ru "" :en "" :значение "0x1051")
                    (:элемент "BRST_PAGE_INVALID_INDEX"          :ru "" :en "" :значение "0x1052")
                    (:элемент "BRST_PAGE_INVALID_ROTATE_VALUE"   :ru "" :en "" :значение "0x1053")
                    (:элемент "BRST_PAGE_INVALID_SIZE"           :ru "" :en "" :значение "0x1054")
                    (:элемент "BRST_PAGE_INVALID_XOBJECT"        :ru "" :en "" :значение "0x1055")
                    (:элемент "BRST_PAGE_OUT_OF_RANGE"           :ru "" :en "" :значение "0x1056")
                    (:элемент "BRST_REAL_OUT_OF_RANGE"           :ru "" :en "" :значение "0x1057")
                    (:элемент "BRST_STREAM_EOF"                  :ru "" :en "" :значение "0x1058")
                    (:элемент "BRST_STREAM_READLN_CONTINUE"      :ru "" :en "" :значение "0x1059")
                    (:элемент "BRST_STRING_OUT_OF_RANGE"         :ru "" :en "" :значение "0x105B")
                    (:элемент "BRST_THIS_FUNC_WAS_SKIPPED"       :ru "" :en "" :значение "0x105C")
                    (:элемент "BRST_TTF_CANNOT_EMBED_FONT"       :ru "" :en "" :значение "0x105D")
                    (:элемент "BRST_TTF_INVALID_CMAP"            :ru "" :en "" :значение "0x105E")
                    (:элемент "BRST_TTF_INVALID_FORMAT"          :ru "" :en "" :значение "0x105F")
                    (:элемент "BRST_TTF_MISSING_TABLE"           :ru "" :en "" :значение "0x1060")
                    (:элемент "BRST_UNSUPPORTED_FONT_TYPE"       :ru "" :en "" :значение "0x1061")
                    (:элемент "BRST_UNSUPPORTED_JPEG_FORMAT"     :ru "" :en "" :значение "0x1063")
                    (:элемент "BRST_UNSUPPORTED_TYPE1_FONT"      :ru "" :en "" :значение "0x1064")
                    (:элемент "BRST_XREF_COUNT_ERR"              :ru "" :en "" :значение "0x1065")
                    (:элемент "BRST_ZLIB_ERROR"                  :ru "" :en "" :значение "0x1066")
                    (:элемент "BRST_INVALID_PAGE_INDEX"          :ru "" :en "" :значение "0x1067")
                    (:элемент "BRST_INVALID_URI"                 :ru "" :en "" :значение "0x1068")
                    (:элемент "BRST_PAGE_LAYOUT_OUT_OF_RANGE"    :ru "" :en "" :значение "0x1069")
                    (:элемент "BRST_PAGE_MODE_OUT_OF_RANGE"      :ru "" :en "" :значение "0x1070")
                    (:элемент "BRST_PAGE_NUM_STYLE_OUT_OF_RANGE" :ru "" :en "" :значение "0x1071")
                    (:элемент "BRST_ANNOT_INVALID_ICON"          :ru "" :en "" :значение "0x1072")
                    (:элемент "BRST_ANNOT_INVALID_BORDER_STYLE"  :ru "" :en "" :значение "0x1073")
                    (:элемент "BRST_PAGE_INVALID_DIRECTION"      :ru "" :en "" :значение "0x1074")
                    (:элемент "BRST_PAGE_INSUFFICIENT_SPACE"     :ru "" :en "" :значение "0x1076")
                    (:элемент "BRST_PAGE_INVALID_DISPLAY_TIME"   :ru "" :en "" :значение "0x1077")
                    (:элемент "BRST_PAGE_INVALID_TRANSITION_TIME":ru "" :en "" :значение "0x1078")
                    (:элемент "BRST_INVALID_PAGE_SLIDESHOW_TYPE" :ru "" :en "" :значение "0x1079")
                    (:элемент "BRST_EXT_GSTATE_OUT_OF_RANGE"     :ru "" :en "" :значение "0x1080")
                    (:элемент "BRST_INVALID_EXT_GSTATE"          :ru "" :en "" :значение "0x1081")
                    (:элемент "BRST_EXT_GSTATE_READ_ONLY"        :ru "" :en "" :значение "0x1082")
                    (:элемент "BRST_INVALID_ICC_COMPONENT_NUM"   :ru "" :en "" :значение "0x1085")
                    (:элемент "BRST_PAGE_INVALID_BOUNDARY"       :ru "" :en "" :значение "0x1086")
                    (:элемент "BRST_INVALID_SHADING_TYPE"        :ru "" :en "" :значение "0x1088"))))

 :функции (
           ;; BRST_Error_Check
           (:название "Error_Check"
            :группа "error"
            :ошибки ()
            :результат (:тип "STATUS"
                        :ru "Возвращенный код ошибки."
                        :en "Error code.")
            :ru "Проверяет наличие ошибки, возвращает её код, вызывает обработчик ошибок, если таковой установлен."
            :en "Check error code and optionally invokes error handler."
            :параметры ((:тип "Error"
                         :имя "error"
                         :ru "Кодовое представление ошибки"
                         :en "Error code representation.")))

           ;; BRST_Doc_Error_Code
           (:название "Doc_Error_Code"
            :группа "error"
            :ошибки ()
            :результат (:тип "STATUS"
                        :ru "Последний установленный код ошибки"
                        :en "Last error code.")
            :ru "Получает последний установленный код ошибки для документа."
            :en "Return the last error code of document object."
            :параметры ((:тип "Doc"
                         :имя "pdf"
                         :ru "Документ, для которого запрашивается ошибка."
                         :en "Document whose error code is requested.")))

           ;; BRST_Doc_Error_DetailCode
           (:название "Doc_Error_DetailCode"
            :группа "error"
            :ошибки ()
            :результат (:тип "STATUS"
                        :ru "Детализированный код ошибки"
                        :en "Detailed error code.")
            :ru "Получает детализированный код ошибки для документа."
            :en "Return detailed error code of document object."
            :параметры ((:тип "Doc"
                         :имя "pdf"
                         :ru ":param_pdf"
                         :en ":param_pdf")))

           ;; BRST_Doc_Error_Reset
           (:название "Doc_Error_Reset"
            :группа "error"
            :ошибки ()
            :результат (:тип "void"
                        :ru "-"
                        :en "-")
            :ru "Очистка ошибки документа

  После установки кода ошибки функции обработки ввода-вывода становятся недоступны. 
  Если необходимо вызвать какую-либо функцию после устранения причины возникновения ошибки, 
  приложение должно предварительно очистить код ошибки путём вызова функции BRST_ResetError()."

            :en "Cleanup document error

  Once an error code is set, IO processing functions cannot be invoked.
  In case of executing a function after the cause of the error is fixed,
  an application has to invoke BRST_ResetError() to clear error-code before executing functions."
            :параметры ((:тип "Doc"
                         :имя "pdf"
                         :ru "Документ, чей статус ошибки очищается"
                         :en "Document whose error state is reset.")))

           ;; BRST_Doc_Error_SetHandler
           (:название "Doc_Error_SetHandler"
            :группа "error"
            :ошибки ("BRST_INVALID_DOCUMENT")
            :результат (:тип "STATUS"
                        :ru ":return_ok"
                        :en ":return_ok")
            :ru "Назначает собственный обработчик ошибок для документа."
            :en "Set custom error handler for document."
            :параметры ((:тип "Doc"
                         :имя "pdf"
                         :ru "Документ, которому назначается обработчик"
                         :en "Document to assign error handler.")
                        (:тип "Error_Handler"
                         :имя "user_error_fn"
                         :ru "Пользовательский обработчик ошибок"
                         :en "User defined error handling callback. If null, previous handler is removed.")))
           ))
