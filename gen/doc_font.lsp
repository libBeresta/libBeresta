(:file "doc_font"
 :functions (
            ;; BRST_Doc_Font
           (:caption "Doc_Font"
            :group "font"
            :ru "Получает запрошенный описатель объекта шрифта."
            :en "Get requested font object handle."
            :params ((:type "Doc"
                         :name "pdf"
                         :ru ":param_pdf"
                         :en ":param_pdf")
                        (:type "CSTR"
                         :name "font_name"
                         :ru "Корректное название шрифта"
                         :en "Valid font name")
                        (:type "CSTR"
                         :name "encoding_name"
                         :ru "Корректное название кодировки"
                         :en "Valid encoding name"))
            :result (:type "Font"
                        :ru "Описатель объекта шрифта при успехе, в противном случае возвращает \\c NULL и вызывает обработчик ошибок."
                        :en "Font object handle on success, otherwise returns \\c NULL and calls error handler.")
            :errors ("INVALID_DOCUMENT"
                     "FAILED_TO_ALLOC_MEM"
                     "INVALID_FONT_NAME"
                     "INVALID_ENCODING_NAME"
                     "UNSUPPORTED_FONT_TYPE"))

           ;; BRST_Doc_TTFont_LoadFromFile
           (:caption "Doc_TTFont_LoadFromFile"
            :group "font"
            :ru "Получает запрошенный описатель объекта шрифта."
            :en "Get requested font object handle."
            :params ((:type "Doc"
                         :name "pdf"
                         :ru ":param_pdf"
                         :en ":param_pdf")
                        (:type "CSTR"
                         :name "filename"
                         :ru "Путь до файла шрифта TrueType (`.ttf`)"
                         :en "Path of TrueType font file (`.ttf`)")
                        (:type "BOOL"
                         :name "embedding"
                         :ru "Если этот параметр равен \\ref BRST_TRUE, данные о глифах шрифта встраиваются в PDF-файл, иначе в PDF-файл включаются только матричные данные."
                         :en "If this parameter is set to \\ref BRST_TRUE, the glyph data of the font is included to PDF file, otherwise only the matrix data is included to PDF file."))
            :result (:type "Font"
                        :ru "Наименование (идентификатор) шрифта при успехе, в противном случае возвращается \\c NULL и вызывается обработчик ошибок."
                        :en "Name of the font on success, otherwise, it returns \\c NULL and calls error handler.")
            :see ("fonts")
            :errors ("INVALID_DOCUMENT"
                     "FAILED_TO_ALLOC_MEM"
                     "FONT_EXISTS"
                     "INVALID_TTC_INDEX"
                     "INVALID_TTC_FILE"
                     "TTF_INVALID_CMAP"
                     "TTF_INVALID_FORMAT"
                     "TTF_MISSING_TABLE"
                     "TTF_CANNOT_EMBEDDING_FONT"))

 ;; BRST_Doc_Type1Font_LoadFromFile
 (:caption "Doc_Type1Font_LoadFromFile"
            :ru "Загрузка шрифта формата Type1 из внешнего файла и регистрация шрифта в документе."
            :en "Load Type1 font from external file and register it in the document object."
            :params ((:type "Doc"
                         :name "pdf"
                         :ru ":param_pdf"
                         :en ":param_pdf")
                        (:type "CSTR"
                         :name "afm_filename"
                         :ru "Путь к файлу AFM"
                         :en "Path of AFM file")
                        (:type "CSTR"
                         :name "data_filename"
                         :ру "Путь к файлу PFA/PFB"
                         :en "Path of PFA/PFB file"))
            :result (:type "CSTR"
                        :ru "Наименование (идентификатор) шрифта при успехе, в противном случае возвращается \\c NULL и вызывается обработчик ошибок."
                        :en "Name of the font on success, otherwise, it returns \\c NULL and calls error handler."))

           ;; BRST_Doc_TTFont_LoadFromFile2
           (:caption "Doc_TTFont_LoadFromFile2"
            :ru "Загрузка TrueType-шрифта из коллекции (*.ttc)"
            :en "Load TrueType font from TrueType Collection file (*.ttc) and register it in the document object"
            :params ((:type "Doc"
                         :name "pdf"
                         :ru ":param_pdf"
                         :en ":param_pdf")
                        (:type "CSTR"
                         :name "filename"
                         :ru "Путь к файлу коллекции (*.ttc)"
                         :en "Path of TrueType Collection file (*.ttc)")
                        (:type "UINT"
                         :name "index"
                         :ru "Номер шрифта в коллекции"
                         :en "Index of font in collection to be loaded")
                        (:type "BOOL"
                         :name "embedding"
                         :ru "Если этот параметр равен \\ref BRST_TRUE, данные о глифах шрифта встраиваются в PDF-файл, иначе в PDF-файл включаются только матричные данные."
                         :en "If this parameter is set to \\ref BRST_TRUE, the glyph data of the font is included to PDF file, otherwise only the matrix data is included to PDF file."))
            :result (:type "CSTR"
                        :ru "Наименование (идентификатор) шрифта при успехе, в противном случае возвращается \\c NULL и вызывается обработчик ошибок."
                        :en "Name of the font on success, otherwise, it returns \\c NULL and calls error handler."))

           ;; BRST_Doc_TTFont_LoadFromMemory
           (:caption "Doc_TTFont_LoadFromMemory"
            :ru "Загрузка TrueType-шрифта из буфера памяти"
            :en "Load TrueType font from memory buffer and register it in the document object"
            :params ((:type "Doc"
                         :name "pdf"
                         :ru ":param_pdf"
                         :en ":param_pdf")
                        (:type "BYTE*"
                         :name "buffer"
                         :ru "Буфер с содержимым TrueType-шрифта."
                         :en "Buffer containing TrueType font bytes")
                        (:type "UINT"
                         :name "size"
                         :ru "Размер буфера"
                         :en "Size of buffer")
                        (:type "BOOL"
                         :name "embedding"
                         :ru "Если этот параметр равен \\ref BRST_TRUE, данные о глифах шрифта встраиваются в PDF-файл, иначе в PDF-файл включаются только матричные данные."
                         :en "If this parameter is set to \\ref BRST_TRUE, the glyph data of the font is included to PDF file, otherwise only the matrix data is included to PDF file."))
            :result (:type "CSTR"
                        :ru "Наименование (идентификатор) шрифта при успехе, в противно случае возвращается \\c NULL и вызывается обработчик ошибок."
                        :en ":return_font_name_or_null"))))

