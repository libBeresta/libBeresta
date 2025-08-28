(:файл "doc_encoding_utf"
 :функции (
           (:название "Doc_UseUTFEncodings" 
            :ru "Включение поддержки кодировки UTF-8.

  После этого вызова приложение может использовать тексты в кодировке Unicode."
            :en "Enable UTF-8 encoding.

  Application can include UTF-8 encoded Unicode text (up to 3-byte UTF-8 sequences).

  \\note UTF-8 encoding works only with TrueType fonts."
            :ошибки (
                    "INVALID_DOCUMENT"
                     "FAILED_TO_ALLOC_MEM"
                     "DUPLICATE_REGISTRATION")
            :параметры ((:тип "Doc"
                         :имя "pdf"
                         :ru ":param_pdf"
                         :en ":param_pdf"))
            :результат (:тип "STATUS"
                        :ru ":return_ok"
                        :en ":return_ok"))))
