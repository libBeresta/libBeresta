(:file "doc_save"
 :functions
       (

;; Функция BRST_Doc_SaveToStream
(:caption "Doc_SaveToStream"
   :group "doc"
   :errors ()
   :result (:type "STATUS"
  	           :ru ":return_ok"
               :en ":return_ok")
   :ru ""
   :en ""
   :params ((:type "Doc"
            :name "pdf"
            :ru ":param_pdf"
            :en ":param_pdf")))

;; Функция BRST_Doc_SaveToFile
(:caption "Doc_SaveToFile"
   :group "doc"
   :errors ()
   :result (:type "STATUS"
  	           :ru ":return_ok"
               :en ":return_ok")
   :ru "Сохраняет документ в файл."
   :en "Save document to file."
   :params ((:type "Doc"
            :name "pdf"
            :ru ":param_pdf"
            :en ":param_pdf")
            (:type "CSTR"
            :name "filename"
            :ru "Имя сохраняемого файла."
            :en "Saved file name.")
            ))))
