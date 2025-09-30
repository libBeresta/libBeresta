(:файл "doc_font"
 :функции (
           ;; BRST_Doc_Font
           (:название "Doc_Font"
            :группа "font"
            :ru "Получает запрошенный описатель объекта шрифта."
            :en "Get requested font object handle."
            :параметры ((:тип "Doc"
                         :имя "pdf"
                         :ru ":param_pdf"
                         :en ":param_pdf")
                        (:тип "CSTR"
                         :имя "font_name"
                         :ru "Корректное название шрифта"
                         :en "Valid font name")
                        (:тип "CSTR"
                         :имя "encoding_name"
                         :ru "Корректное название кодировки"
                         :en "Valid encoding name"))
            :результат (:тип "Font"
                        :ru "Описатель объекта шрифта при успехе, в противном случае возвращает \\c NULL и вызывает обработчик ошибок."
                        :en "Font object handle on success, otherwise returns \\c NULL and calls error handler.")
            :ошибки ("INVALID_DOCUMENT"
                     "FAILED_TO_ALLOC_MEM"
                     "INVALID_FONT_NAME"
                     "INVALID_ENCODING_NAME"
                     "UNSUPPORTED_FONT_TYPE"))

           ;; BRST_Doc_TTFont_LoadFromFile
           (:название "Doc_TTFont_LoadFromFile"
            :группа "font"
            :ru "Получает запрошенный описатель объекта шрифта."
            :en "Get requested font object handle."
            :параметры ((:тип "Doc"
                         :имя "pdf"
                         :ru ":param_pdf"
                         :en ":param_pdf")
                        (:тип "CSTR"
                         :имя "filename"
                         :ru "Путь до файла шрифта TrueType (`.ttf`)"
                         :en "Path of TrueType font file (`.ttf`)")
                        (:тип "BOOL"
                         :имя "embedding"
                         :ru "Если этот параметр равен \\ref BRST_TRUE, данные о глифах шрифта встраиваются в PDF-файл, иначе в PDF-файл включаются только матричные данные."
                         :en "If this parameter is set to \\ref BRST_TRUE, the glyph data of the font is included to PDF file, otherwise only the matrix data is included to PDF file."))
            :результат (:тип "Font"
                        :ru "Наименование (идентификатор) шрифта при успехе, в противно случае возвращается \\c NULL и вызывается обработчик ошибок."
                        :en "Name of the font on success, otherwise, it returns \\c NULL and calls error handler.")
            :см ("fonts")
            :ошибки ("INVALID_DOCUMENT"
                     "FAILED_TO_ALLOC_MEM"
                     "FONT_EXISTS"
                     "INVALID_TTC_INDEX"
                     "INVALID_TTC_FILE"
                     "TTF_INVALID_CMAP"
                     "TTF_INVALID_FORMAT"
                     "TTF_MISSING_TABLE"
                     "TTF_CANNOT_EMBEDDING_FONT"))))

;;; TODO BRST_Doc_TTFont_LoadFromFile2
;;; TODO BRST_Doc_TTFont_LoadFromMemory
