(:файл "error"
 :указатели ((:имя "Error"))

 :перечисления
       ((:имя "ErrorKind"
         :ru "Виды ошибок, возвращаемых библиотекой"
         :en "Error kind"
         :элементы ((:элемент "ARRAY_COUNT_ERR"
                     :ru "Превышено количество элементов массива (\\ref BRST_LIMIT_MAX_ARRAY)."
                     :en "Array count limit exceed (\\ref BRST_LIMIT_MAX_ARRAY)."
                     :значение "0x1001")
                    (:элемент "ARRAY_ITEM_NOT_FOUND"
                     :ru "Элемент массива не найден."
                     :en "Array element not found."
                     :значение "0x1002")
                    (:элемент "ARRAY_ITEM_UNEXPECTED_TYPE"
                     :ru "Элемент массива неизвестного типа"
                     :en "Array element of unexpected type"
                     :значение "0x1003")
                    (:элемент "BINARY_LENGTH_ERR"           :ru "" :en "" :значение "0x1004")
                    (:элемент "CANNOT_GET_PALETTE"          :ru "" :en "" :значение "0x1005")
                    (:элемент "DICT_COUNT_ERR"              :ru "" :en "" :значение "0x1007")
                    (:элемент "DICT_ITEM_NOT_FOUND"         :ru "" :en "" :значение "0x1008")
                    (:элемент "DICT_ITEM_UNEXPECTED_TYPE"   :ru "" :en "" :значение "0x1009")
                    (:элемент "DICT_STREAM_LENGTH_NOT_FOUND":ru "" :en "" :значение "0x100A")
                    (:элемент "DOC_ENCRYPTDICT_NOT_FOUND"   :ru "" :en "" :значение "0x100B")
                    (:элемент "DOC_INVALID_OBJECT"          :ru "" :en "" :значение "0x100C")
                    (:элемент "DUPLICATE_REGISTRATION"      :ru "" :en "" :значение "0x100E")
                    (:элемент "EXCEED_JWW_CODE_NUM_LIMIT"   :ru "" :en "" :значение "0x100F")
                    (:элемент "ENCRYPT_INVALID_PASSWORD"    :ru "" :en "" :значение "0x1011")
                    (:элемент "ERR_UNKNOWN_CLASS"           :ru "" :en "" :значение "0x1013")
                    (:элемент "EXCEED_GSTATE_LIMIT"         :ru "" :en "" :значение "0x1014")
                    (:элемент "FAILED_TO_ALLOC_MEM"         :ru "" :en "" :значение "0x1015")
                    (:элемент "FILE_IO_ERROR"               :ru "" :en "" :значение "0x1016")
                    (:элемент "FILE_OPEN_ERROR"             :ru "" :en "" :значение "0x1017")
                    (:элемент "FONT_EXISTS"                 :ru "" :en "" :значение "0x1019")
                    (:элемент "FONT_INVALID_WIDTH_TABLE"    :ru "" :en "" :значение "0x101A")
                    (:элемент "INVALID_AFM_HEADER"          :ru "" :en "" :значение "0x101B")
                    (:элемент "INVALID_ANNOTATION"          :ru "" :en "" :значение "0x101C")
                    (:элемент "INVALID_BIT_PER_COMPONENT"   :ru "" :en "" :значение "0x101E")
                    (:элемент "INVALID_CHAR_MATRIX_DATA"    :ru "" :en "" :значение "0x101F")
                    (:элемент "INVALID_COLOR_SPACE"         :ru "" :en "" :значение "0x1020")
                    (:элемент "INVALID_COMPRESSION_MODE"    :ru "" :en "" :значение "0x1021")
                    (:элемент "INVALID_DATE_TIME"           :ru "" :en "" :значение "0x1022")
                    (:элемент "INVALID_DESTINATION"         :ru "" :en "" :значение "0x1023")
                    (:элемент "INVALID_DOCUMENT"            :ru "" :en "" :значение "0x1025")
                    (:элемент "INVALID_DOCUMENT_STATE"      :ru "" :en "" :значение "0x1026")
                    (:элемент "INVALID_ENCODER"             :ru "" :en "" :значение "0x1027")
                    (:элемент "INVALID_ENCODER_TYPE"        :ru "" :en "" :значение "0x1028")
                    (:элемент "INVALID_ENCODING_NAME"       :ru "" :en "" :значение "0x102B")
                    (:элемент "INVALID_ENCRYPT_KEY_LEN"     :ru "" :en "" :значение "0x102C")
                    (:элемент "INVALID_FONTDEF_DATA"        :ru "" :en "" :значение "0x102D")
                    (:элемент "INVALID_FONTDEF_TYPE"        :ru "" :en "" :значение "0x102E")
                    (:элемент "INVALID_FONT_NAME"           :ru "" :en "" :значение "0x102F")
                    (:элемент "INVALID_IMAGE"               :ru "" :en "" :значение "0x1030")
                    (:элемент "INVALID_JPEG_DATA"           :ru "" :en "" :значение "0x1031")
                    (:элемент "INVALID_N_DATA"              :ru "" :en "" :значение "0x1032")
                    (:элемент "INVALID_OBJECT"              :ru "" :en "" :значение "0x1033")
                    (:элемент "INVALID_OBJ_ID"              :ru "" :en "" :значение "0x1034")
                    (:элемент "INVALID_OPERATION"           :ru "" :en "" :значение "0x1035")
                    (:элемент "INVALID_OUTLINE"             :ru "" :en "" :значение "0x1036")
                    (:элемент "INVALID_PAGE"                :ru "" :en "" :значение "0x1037")
                    (:элемент "INVALID_PAGES"               :ru "" :en "" :значение "0x1038")
                    (:элемент "INVALID_PARAMETER"           :ru "" :en "" :значение "0x1039")
                    (:элемент "INVALID_PNG_IMAGE"           :ru "" :en "" :значение "0x103B")
                    (:элемент "INVALID_STREAM"              :ru "" :en "" :значение "0x103C")
                    (:элемент "MISSING_FILE_NAME_ENTRY"     :ru "" :en "" :значение "0x103D")
                    (:элемент "INVALID_TTC_FILE"            :ru "" :en "" :значение "0x103F")
                    (:элемент "INVALID_TTC_INDEX"           :ru "" :en "" :значение "0x1040")
                    (:элемент "INVALID_WX_DATA"             :ru "" :en "" :значение "0x1041")
                    (:элемент "ITEM_NOT_FOUND"              :ru "" :en "" :значение "0x1042")
                    (:элемент "LIBPNG_ERROR"                :ru "" :en "" :значение "0x1043")
                    (:элемент "NAME_INVALID_VALUE"          :ru "" :en "" :значение "0x1044")
                    (:элемент "NAME_OUT_OF_RANGE"           :ru "" :en "" :значение "0x1045")
                    (:элемент "PAGES_MISSING_KIDS_ENTRY"    :ru "" :en "" :значение "0x1049")
                    (:элемент "PAGE_CANNOT_FIND_OBJECT"     :ru "" :en "" :значение "0x104A")
                    (:элемент "PAGE_CANNOT_GET_ROOT_PAGES"  :ru "" :en "" :значение "0x104B")
                    (:элемент "PAGE_CANNOT_RESTORE_GSTATE"  :ru "" :en "" :значение "0x104C")
                    (:элемент "PAGE_CANNOT_SET_PARENT"      :ru "" :en "" :значение "0x104D")
                    (:элемент "PAGE_FONT_NOT_FOUND"         :ru "" :en "" :значение "0x104E")
                    (:элемент "PAGE_INVALID_FONT"           :ru "" :en "" :значение "0x104F")
                    (:элемент "PAGE_INVALID_FONT_SIZE"      :ru "" :en "" :значение "0x1050")
                    (:элемент "PAGE_INVALID_GMODE"          :ru "" :en "" :значение "0x1051")
                    (:элемент "PAGE_INVALID_INDEX"          :ru "" :en "" :значение "0x1052")
                    (:элемент "PAGE_INVALID_ROTATE_VALUE"   :ru "" :en "" :значение "0x1053")
                    (:элемент "PAGE_INVALID_SIZE"           :ru "" :en "" :значение "0x1054")
                    (:элемент "PAGE_INVALID_XOBJECT"        :ru "" :en "" :значение "0x1055")
                    (:элемент "PAGE_OUT_OF_RANGE"           :ru "" :en "" :значение "0x1056")
                    (:элемент "REAL_OUT_OF_RANGE"           :ru "" :en "" :значение "0x1057")
                    (:элемент "STREAM_EOF"                  :ru "" :en "" :значение "0x1058")
                    (:элемент "STREAM_READLN_CONTINUE"      :ru "" :en "" :значение "0x1059")
                    (:элемент "STRING_OUT_OF_RANGE"         :ru "" :en "" :значение "0x105B")
                    (:элемент "THIS_FUNC_WAS_SKIPPED"       :ru "" :en "" :значение "0x105C")
                    (:элемент "TTF_CANNOT_EMBED_FONT"       :ru "" :en "" :значение "0x105D")
                    (:элемент "TTF_INVALID_CMAP"            :ru "" :en "" :значение "0x105E")
                    (:элемент "TTF_INVALID_FORMAT"          :ru "" :en "" :значение "0x105F")
                    (:элемент "TTF_MISSING_TABLE"           :ru "" :en "" :значение "0x1060")
                    (:элемент "UNSUPPORTED_FONT_TYPE"       :ru "" :en "" :значение "0x1061")
                    (:элемент "UNSUPPORTED_JPEG_FORMAT"     :ru "" :en "" :значение "0x1063")
                    (:элемент "UNSUPPORTED_TYPE1_FONT"      :ru "" :en "" :значение "0x1064")
                    (:элемент "XREF_COUNT_ERR"              :ru "" :en "" :значение "0x1065")
                    (:элемент "ZLIB_ERROR"                  :ru "" :en "" :значение "0x1066")
                    (:элемент "INVALID_PAGE_INDEX"          :ru "" :en "" :значение "0x1067")
                    (:элемент "INVALID_URI"                 :ru "" :en "" :значение "0x1068")
                    (:элемент "PAGE_LAYOUT_OUT_OF_RANGE"    :ru "" :en "" :значение "0x1069")
                    (:элемент "PAGE_MODE_OUT_OF_RANGE"      :ru "" :en "" :значение "0x1070")
                    (:элемент "PAGE_NUM_STYLE_OUT_OF_RANGE" :ru "" :en "" :значение "0x1071")
                    (:элемент "ANNOT_INVALID_ICON"          :ru "" :en "" :значение "0x1072")
                    (:элемент "ANNOT_INVALID_BORDER_STYLE"  :ru "" :en "" :значение "0x1073")
                    (:элемент "PAGE_INVALID_DIRECTION"      :ru "" :en "" :значение "0x1074")
                    (:элемент "PAGE_INSUFFICIENT_SPACE"     :ru "" :en "" :значение "0x1076")
                    (:элемент "PAGE_INVALID_DISPLAY_TIME"   :ru "" :en "" :значение "0x1077")
                    (:элемент "PAGE_INVALID_TRANSITION_TIME":ru "" :en "" :значение "0x1078")
                    (:элемент "INVALID_PAGE_SLIDESHOW_TYPE" :ru "" :en "" :значение "0x1079")
                    (:элемент "EXT_GSTATE_OUT_OF_RANGE"     :ru "" :en "" :значение "0x1080")
                    (:элемент "INVALID_EXT_GSTATE"          :ru "" :en "" :значение "0x1081")
                    (:элемент "EXT_GSTATE_READ_ONLY"        :ru "" :en "" :значение "0x1082")
                    (:элемент "INVALID_ICC_COMPONENT_NUM"   :ru "" :en "" :значение "0x1085")
                    (:элемент "PAGE_INVALID_BOUNDARY"       :ru "" :en "" :значение "0x1086")
                    (:элемент "INVALID_SHADING_TYPE"        :ru "" :en "" :значение "0x1088"))))

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
