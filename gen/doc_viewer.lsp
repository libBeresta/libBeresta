(:file "doc_viewer"
 :functions
       (
        ;; BRST_Doc_SetOpenAction
        (:caption "Doc_SetOpenAction" 
         :ru "Задать первую страницу при открытии документа."
         :en "Set the first page to appear when a document is opened."
         :params ((:type "Doc"
                      :name "pdf"
                      :ru ":param_pdf"
                      :en ":param_pdf")
                     (:type "Destination"
                      :name "open_action"
                      :ру "Действие открытия страницы"
                      :en "Set a valid destination object."))
         :result (:type "STATUS"
                     :ru ":return_ok"
                     :en ":return_ok"))

        ;; BRST_Doc_ViewerPreference
        (:caption "Doc_ViewerPreference" 
         :ru "Получение предпочтений просмотра документа."
         :en "Get viewer preferences of a document."
         :params ((:type "Doc"
                      :name "pdf"
                      :ru ":param_pdf"
                      :en ":param_pdf"))
         :result (:type "ViewerPreference"
                     :ru "Набор предпочтений программы просмотра."
                     :en "Viewer preferences of a document"))

        ;; BRST_Doc_SetViewerPreference
        (:caption "Doc_SetViewerPreference" 
         :ru "Установить предпочтения просмотра документа"
         :en "Set viewer preferences of document"
         :params ((:type "Doc"
                      :name "pdf"
                      :ru ":param_pdf"
                      :en ":param_pdf")
                     (:type "ViewerPreference"
                      :name "value"
                      :ру "Значение параметра"
                      :en "Viewer preference value"))
         :result (:type "STATUS"
                     :ru ":return_ok"
                     :en ":return_ok"))
        ))
