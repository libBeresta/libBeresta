(:file "doc_info"
 :enums
       ((:name "InfoType"
         :ru "Атрибуты метаданных документа (Таблица 317)"
         :en "Document metadata attributes (Table 317)"
         :elements (
                    (:element "INFO_CREATION_DATE"               :ru "Дата создания документа"  :en "Document creation date")
                    (:element "INFO_MOD_DATE"      :version "1.1" :ru "Дата изменения документа" :en "Document modification date")
                    (:element "INFO_AUTHOR"                      :ru "Автор документа"          :en "Document author")
                    (:element "INFO_CREATOR"                     :ru "Разработчик документа"    :en "Document creator")
                    (:element "INFO_PRODUCER"                    :ru "Продюсер документа"       :en "Document producer")
                    (:element "INFO_TITLE"         :version "1.1" :ru "Заголовок документа"      :en "Document title")
                    (:element "INFO_SUBJECT"       :version "1.1" :ru "Тема документа"           :en "Document subject")
                    (:element "INFO_KEYWORDS"      :version "1.1" :ru "Ключевые слова документа" :en "Document keywords")
                    (:element "INFO_TRAPPED"       :version "1.3"
                     :ru "Признак наличия информации о треппинге в документе.
  Возможные значения (чувствительно к регистру):
  - True
  - False
  - Unknown (по умолчанию)"
                     :en "Trapping information flag.
  Possible values are (case sensitive):
  - True
  - False
  - Unknown (default value)")
                    ;; TODO 14.11.5 Output Intents?
                    (:element "INFO_GTS_PDFX" :ru "" :en ""))))
 :functions (
           (:caption "Doc_SetInfoAttr"
            :group "info"
            :ru "Устанавливается значение атрибута в словаре \\c info. Значение устанавливается с использованием текущей кодировки документа."
            :en "Set the text of \\c info dictionary attribute using current encoding of the document."
            :errors ("INVALID_DOCUMENT"
                     "FAILED_TO_ALLOC_MEM"
                     "INVALID_PARAMETER")
            :params ((:type "Doc"
                         :name "pdf"
                         :ru ":param_pdf"
                         :en ":param_pdf")
                        (:type "InfoType"
                         :name "type"
                         :ru "\\parblock Одно из значений:
    - \\ref BRST_INFO_AUTHOR
    - \\ref BRST_INFO_CREATOR
    - \\ref BRST_INFO_TITLE
    - \\ref BRST_INFO_SUBJECT
    - \\ref BRST_INFO_KEYWORDS
    \\endparblock"
                         :en "\\parblock One of the following values:
    - \\ref BRST_INFO_AUTHOR
    - \\ref BRST_INFO_CREATOR
    - \\ref BRST_INFO_TITLE
    - \\ref BRST_INFO_SUBJECT
    - \\ref BRST_INFO_KEYWORDS
    \\endparblock")
                        (:type "CSTR"
                         :name "value"
                         :ru "Устанавливаемое значение"
                         :en "Attribute text to be set"))
            :result (:type "STATUS"
                        :ru ":return_ok"
                        :en ":return_ok"))

           (:caption "Doc_SetInfoDateAttr"
            :group "info"
            :ru "Устанавливается значение даты в словаре \\c info."
            :en "Set date atturbute of \\c info dictionary."
            :errors ("INVALID_DOCUMENT"
                     "FAILED_TO_ALLOC_MEM"
                     "INVALID_PARAMETER"
                     "INVALID_DATE_TIME")
            :params ((:type "Doc"
                         :name "pdf"
                         :ru ":param_pdf"
                         :en ":param_pdf")
                        (:type "InfoType"
                         :name "type"
                         :ru "\\parblock Одно из значений:
    - \\ref BRST_INFO_CREATION_DATE
    - \\ref BRST_INFO_MOD_DATE
    \\endparblock"
                         :en "\\parblock One of the following values:
    - \\ref BRST_INFO_CREATION_DATE
    - \\ref BRST_INFO_MOD_DATE
    \\endparblock")
                        (:type "Date"
                         :name "value"
                         :ru "Устанавливаемое значение"
                         :en "Attribute text to be set"))
            :result (:type "STATUS"
                        :ru ":return_ok"
                        :en ":return_ok"))))
