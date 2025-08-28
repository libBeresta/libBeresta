(:файл "date"
 :указатели ((:имя "Date"))
       
 :перечисления
       ((:имя "Date_Parts"
         :ru "Элементы даты, возвращаемые функцией \\ref BRST_Date_Part()"
         :en "Date elements, returned by \\ref BRST_Date_Part() function"
         :элементы ((:элемент "DATE_PART_YEAR" :ru "" :en "")
                    (:элемент "DATE_PART_MONTH" :ru "" :en "")
                    (:элемент "DATE_PART_DAY" :ru "" :en "")
                    (:элемент "DATE_PART_HOUR" :ru "" :en "")
                    (:элемент "DATE_PART_MINUTE" :ru "" :en "")
                    (:элемент "DATE_PART_SECOND" :ru "" :en "")
                    (:элемент "DATE_PART_HOUR_OFFSET" :ru "" :en "")
                    (:элемент "DATE_PART_MINUTE_OFFSET" :ru "" :en "")
                    (:элемент "DATE_PART_UT_RELATIONSHIP" :ru "" :en "")))
        (:имя "UT_Relationship"
         :ru "Смещение на восток от UTC"
         :en "UTC east offset"
         :элементы ((:элемент "UT_RELATIONSHIP_NONE" :ru "Смещение времени от UTC не указано" :en "UTC offset is not set")
                    (:элемент "UT_RELATIONSHIP_PLUS" :ru "Смещение времени UTC положительное" :en "UTC offset is positive")
                    (:элемент "UT_RELATIONSHIP_MINUS" :ru "" :en "")
                    (:элемент "UT_RELATIONSHIP_ZERO" :ru "" :en ""))))

 :функции (

           (:название "Date_Now"
            :группа "date"
            :ru "Функция возвращает объект, содержащий текущие дату и время.
  Учитываются настройки локали в операционной системе, и дата/время сохраняются в объекте с учетом временной зоны.  
  В дальнейшем, этот объект используется в функциях, работающих со временем (свойства документа, вложенных файлов и т.д.)"
            :en ""
            :параметры ((:тип "Doc"
                         :имя "pdf"
                         :ru ":param_pdf"
                         :en ":param_pdf"))
            :результат (:тип "Date"
                        :ru "Объект, содержащий текущие дату и время"
                        :en "Object with current date and time"))

           (:название "Date_Part"
            :группа "date"
            :ru "Элементы даты (год, месяц, день и т.д.)"
            :en "Date elements (year, month, day and so on)"
            :параметры ((:тип "Date"
                         :имя "date"
                         :ru ":param_date"
                         :en ":param_date")
                        (:тип "Date_Parts"
                         :имя "part"
                         :ru "Запрашиваемый элемент даты"
                         :en "Date element"))
            :результат (:тип "INT"
                        :ru "Значение элемента даты"
                        :en "Date element value"))

           (:название "Date_Validate"
            :группа "date"
            :ru "Проверяет внутреннюю согласованность даты в структуре данных."
            :en "Validates internal date structure"
            :параметры ((:тип "Date"
                         :имя "date"
                         :ru ":param_date"
                         :en ":param_date"))
            :результат (:тип "STATUS"
                        :ru "Возвращает \\c BRST_OK, если дата корректна и \\c BRST_INVALID_DATE_TIME в противном случае."
                        :en "Returns \\c BRST_OK on success and \\c BRST_INVALID_DATE_TIME otherwise."))

           (:название "Date_Free"
            :группа "date"
            :ru "Высвобождает память, занятую объектом даты."
            :en "Frees date memory"
            :параметры ((:тип "Date"
                         :имя "date"
                         :ru ":param_date"
                         :en ":param_date"))
            :результат (:тип "void"
                        :ru "Нет"
                        :en "No"))))
