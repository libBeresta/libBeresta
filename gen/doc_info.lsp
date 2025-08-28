(:файл "doc_info"
 :перечисления
       ((:имя "InfoType"
         :ru "Аттрибуты метаданных документа (Таблица 317)"
         :en "Document metadata attributes (Table 317)"
         :элементы (
                    (:элемент "INFO_CREATION_DATE"               :ru "Дата создания документа"  :en "Document creation date")
                    (:элемент "INFO_MOD_DATE"      :версия "1.1" :ru "Дата изменения документа" :en "Document modification date")
                    (:элемент "INFO_AUTHOR"                      :ru "Автор документа"          :en "Document author")
                    (:элемент "INFO_CREATOR"                     :ru "Разработчик документа"    :en "Document creator")
                    (:элемент "INFO_PRODUCER"                    :ru "Продюсер документа"       :en "Document producer")
                    (:элемент "INFO_TITLE"         :версия "1.1" :ru "Заголовок документа"      :en "Document title")
                    (:элемент "INFO_SUBJECT"       :версия "1.1" :ru "Тема документа"           :en "Document subject")
                    (:элемент "INFO_KEYWORDS"      :версия "1.1" :ru "Ключевые слова документа" :en "Document keywords")
                    (:элемент "INFO_TRAPPED"       :версия "1.3"
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
                    (:элемент "INFO_GTS_PDFX" :ru "" :en ""))))
 :функции (
           (:название "Doc_SetInfoAttr"
            :группа "info"
            :ru "Устанавливается значение атрибута в словаре \\c info. Значение устанавливается с использованием текущей кодировки документа."
            :en "Set the text of \\c info dictionary attribute using current encoding of the document."
            :ошибки ("INVALID_DOCUMENT"
                     "FAILED_TO_ALLOC_MEM"
                     "INVALID_PARAMETER")
            :параметры ((:тип "Doc"
                         :имя "pdf"
                         :ru ":param_pdf"
                         :en ":param_pdf")
                        (:тип "InfoType"
                         :имя "type"
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
                        (:тип "CSTR"
                         :имя "value"
                         :ru "Устанавливааемое значение "
                         :en "Attribute text to be set"))
            :результат (:тип "STATUS"
                        :ru ":return_ok"
                        :en ":return_ok"))

           (:название "Doc_SetInfoDateAttr"
            :группа "info"
            :ru "Устанавливается значение даты в словаре \\c info."
            :en "Set date atturbute of \\c info dictionary."
            :ошибки ("INVALID_DOCUMENT"
                     "FAILED_TO_ALLOC_MEM"
                     "INVALID_PARAMETER"
                     "INVALID_DATE_TIME")
            :параметры ((:тип "Doc"
                         :имя "pdf"
                         :ru ":param_pdf"
                         :en ":param_pdf")
                        (:тип "InfoType"
                         :имя "type"
                         :ru "\\parblock Одно из значений:
    - \\ref BRST_INFO_CREATION_DATE
    - \\ref BRST_INFO_MOD_DATE
    \\endparblock"
                         :en "\\parblock One of the following values:
    - \\ref BRST_INFO_CREATION_DATE
    - \\ref BRST_INFO_MOD_DATE
    \\endparblock")
                        (:тип "Date"
                         :имя "value"
                         :ru "Устанавливааемое значение"
                         :en "Attribute text to be set"))
            :результат (:тип "STATUS"
                        :ru ":return_ok"
                        :en ":return_ok"))))
