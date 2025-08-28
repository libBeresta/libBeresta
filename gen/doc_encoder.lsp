(:файл "doc_encoder"
 :функции (
           (:название "Doc_Encoder_SetCurrent" 
            :ru "Установка кодировщика документа"
            :en "Set current encoder for document"
            :параметры ((:тип "Doc"
                         :имя "pdf"
                         :ru ":param_pdf"
                         :en ":param_pdf")                         
                        (:тип "CSTR"
                         :имя "encoding_name"
                         :ru "Название кодировки" 
                         :en "Valid encoding name"))
            :результат (:тип "STATUS"
                        :ru ":return_ok"
                        :en ":return_ok"))))
