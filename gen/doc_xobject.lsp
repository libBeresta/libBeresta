(:файл "doc_xobject"
 :группа "page"
 :функции ((:название "Doc_XObject_Create"
            :группа "page"
            :ru "Создание объекта XObject Form"
            :en "XObject Form object creation"
            :см ("Page_XObject_Execute()"
                 "Page_DrawImage()"
                 "Page_GSave()"
                 "Page_GRestore()"
                 "Page_Concat()"
                 "XObject_Stream()")
            :результат (:тип "XObject"
                        :ru ":param_xobject"
                        :en ":param_xobject")
            :параметры ((:тип "Doc"
                         :имя "pdf"
                         :ru ":param_pdf"
                         :en ":param_pdf")
                        (:тип "REAL"
                         :имя "width"
                         :ru "Ширина XObject в логических единицах"
                         :en "XObject logical width")
                        (:тип "REAL"
                         :имя "height"
                         :ru "Высота XObject в логических единицах"
                         :en "XObject logical height")
                        (:тип "REAL"
                         :имя "scalex"
                         :ru "Горизонтальное соотношение единиц в XObject и в документе"
                         :en "XObject horizontal logical unit scale")
                        (:тип "REAL"
                         :имя "scaley"
                         :ru "Вертикальное соотношение единиц в XObject и в документе"
                         :en "XObject vertical logical unit scale")
                         ))))
