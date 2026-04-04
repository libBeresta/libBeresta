(:file "date"
 :pointers ((:name "Date"))
       
 :enums
       ((:name "Date_Parts"
         :ru "Элементы даты, возвращаемые функцией \\ref BRST_Date_Part()"
         :en "Date elements, returned by \\ref BRST_Date_Part() function"
         :elements ((:element "DATE_PART_YEAR" :ru "" :en "")
                    (:element "DATE_PART_MONTH" :ru "" :en "")
                    (:element "DATE_PART_DAY" :ru "" :en "")
                    (:element "DATE_PART_HOUR" :ru "" :en "")
                    (:element "DATE_PART_MINUTE" :ru "" :en "")
                    (:element "DATE_PART_SECOND" :ru "" :en "")
                    (:element "DATE_PART_HOUR_OFFSET" :ru "" :en "")
                    (:element "DATE_PART_MINUTE_OFFSET" :ru "" :en "")
                    (:element "DATE_PART_UT_RELATIONSHIP" :ru "" :en "")))
        (:name "UT_Relationship"
         :ru "Смещение на восток от UTC"
         :en "UTC east offset"
         :elements ((:element "UT_RELATIONSHIP_NONE"  :ru "Смещение времени от UTC не указано" :en "UTC offset is not set")
                    (:element "UT_RELATIONSHIP_PLUS"  :ru "Время позже UTC" :en "Local time is later than UTC")
                    (:element "UT_RELATIONSHIP_MINUS" :ru "Время раньше UTC" :en "Local time is earlier than UTC")
                    (:element "UT_RELATIONSHIP_ZERO"  :ru "Время соответствует UTC" :en "Local time equal to UTC"))))

 :functions (

           (:caption "Date_Now"
            :group "date"
            :ru "Функция возвращает объект, содержащий текущие дату и время.
  Учитываются настройки локали в операционной системе, и дата/время сохраняются в объекте с учетом временной зоны.  
  В дальнейшем, этот объект используется в функциях, работающих со временем (свойства документа, вложенных файлов и т.д.)"
            :en ""
            :params ((:type "Doc"
                         :name "pdf"
                         :ru ":param_pdf"
                         :en ":param_pdf"))
            :result (:type "Date"
                        :ru "Объект, содержащий текущие дату и время"
                        :en "Object with current date and time"))

           (:caption "Date_Part"
            :group "date"
            :ru "Элементы даты (год, месяц, день и т.д.)"
            :en "Date elements (year, month, day and so on)"
            :params ((:type "Date"
                         :name "date"
                         :ru ":param_date"
                         :en ":param_date")
                        (:type "Date_Parts"
                         :name "part"
                         :ru "Запрашиваемый элемент даты"
                         :en "Date element"))
            :result (:type "INT"
                        :ru "Значение элемента даты"
                        :en "Date element value"))

           (:caption "Date_Validate"
            :group "date"
            :ru "Проверяет внутреннюю согласованность даты в структуре данных."
            :en "Validates internal date structure"
            :params ((:type "Date"
                         :name "date"
                         :ru ":param_date"
                         :en ":param_date"))
            :result (:type "STATUS"
                        :ru "Возвращает \\c BRST_OK, если дата корректна и \\c BRST_INVALID_DATE_TIME в противном случае."
                        :en "Returns \\c BRST_OK on success and \\c BRST_INVALID_DATE_TIME otherwise."))

           (:caption "Date_Free"
            :group "date"
            :ru "Высвобождает память, занятую объектом даты."
            :en "Frees date memory"
            :params ((:type "Date"
                         :name "date"
                         :ru ":param_date"
                         :en ":param_date"))
            :result (:type "void"
                        :ru "Нет"
                        :en "No"))))
