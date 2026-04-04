(:file "doc_pdfa"
 :functions (
           ;; BRST_Doc_PDFA_SetConformance
           (:caption "Doc_PDFA_SetConformance" 
            :ru "Установить уровень соответствия PDF/A"
            :en "Set PDF/A conformance level"
            :params ((:type "Doc"
                         :name "pdf"
                         :ru ":param_pdf"
                         :en ":param_pdf")
                        (:type "PDFAType"
                         :name "pdfa_type"
                         :ru "Тип стандарта PDF/A"
                         :en "PDFA standard type"))
            :result (:type "STATUS"
                        :ru ":return_ok"
                        :en ":return_ok"))

           ;; BRST_Doc_PDFA_AddXmpExtension
           (:caption "Doc_PDFA_AddXmpExtension" 
            :ru "Добавление расширения метаданных XMP"
            :en "Add XMP metadata extension"
            :params ((:type "Doc"
                         :name "pdf"
                         :ru ":param_pdf"
                         :en ":param_pdf")
                        (:type "CSTR"
                         :name "xmp_description"
                         :ru "Описание метаданных XMP"
                         :en "XMP metadata description"))
            :result (:type "STATUS"
                        :ru ":return_ok"
                        :en ":return_ok"))

           ;; BRST_Doc_PDFA_AppendOutputIntents
           (:caption "Doc_PDFA_AppendOutputIntents" 
            :ru "Добавить профиль вывода ICC"
            :en "Append output intent profile"
            :params ((:type "Doc"
                         :name "pdf"
                         :ru ":param_pdf"
                         :en ":param_pdf")
                        (:type "CSTR"
                         :name "iccname"
                         :ru "Имя профиля ICC"
                         :en "ICC profile name")
                        (:type "Dict"
                         :name "iccdict"
                         :ru "Параметры профиля ICC"
                         :en "ICC profile parameters dictionary"))
            :result (:type "STATUS"
                        :ru ":return_ok"
                        :en ":return_ok"))))
