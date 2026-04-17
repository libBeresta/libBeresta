(:file "doc_output_intent"

 :definitions
       ((:name "OutputIntent"
         :original "Dict"))

 :functions ((:caption "Doc_OutputIntent_New"
              :ru ""
              :en ""
              :result (:type "OutputIntent"
                       :ru ""
                       :en "")
              :params ((:type "Doc"
                        :name "pdf"
                        :ru ":param_pdf"
                        :en ":param_pdf")
                       (:type "CSTR"
                        :name "identifier"
                        :ru ""
                        :en "")
                       (:type "CSTR"
                        :name "condition"
                        :ru ""
                        :en "")
                       (:type "CSTR"
                        :name "registry"
                        :ru ""
                        :en "")
                       (:type "CSTR"
                        :name "info"
                        :ru ""
                        :en "")
                       (:type "Array"
                        :name "outputProfile"
                        :ru ""
                        :en "")))

             (:caption "Doc_OutputIntent_Add"
              :ru ""
              :en ""
              :result (:type "STATUS"
                       :ru ""
                       :en "")
              :params ((:type "Doc"
                        :name "pdf"
                        :ru ":param_pdf"
                        :en ":param_pdf")
                       (:type "OutputIntent"
                        :name "intent"
                        :ru ""
                        :en "")))))
