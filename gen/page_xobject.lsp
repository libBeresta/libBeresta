(:файл "page_xobject"
 :группа "page"
 :функции ((:название "Page_XObject_Execute"
            :группа "page"
            :ru "Отображает объект XObject в текущем графическом контексте.

  XObject можно создать с помощью функции \\ref BRST_Doc_Page_XObject_Create(), он может включать в себя
  графические команды, а также другие данные.

  Также эта функция используется \\ref BRST_Page_DrawImage() для отображения изображения \\ref BRST_Image."
            :en "Draw XObject using current graphics context.

  XObject can be created using \\ref BRST_Doc_Page_XObject_Create() and can include drawing commands as well
  other data.

  This is also used by \\ref BRST_Page_DrawImage() to draw the \\ref BRST_Image by first calling
  \\ref BRST_Page_GSave() and \\ref BRST_Page_Concat() and then calling \\ref BRST_Page_GRestore()
  after BRST_Page_XObject_Execute(). It could be used manually to rotate an image."
            :см ("Doc_Page_XObject_Create()"
                 "Page_DrawImage()"
                 "Page_GSave()"
                 "Page_GRestore()"
                 "Page_Concat()")
            :результат (:тип "Stream"
                        :ru ":param_stream"
                        :en ":param_stream")
            :параметры ((:тип "Page"
                         :имя "page"
                         :ru ":param_page"
                         :en ":param_page")
                        (:тип "XObject"
                         :имя "xobj"
                         :ru ":param_xobject"
                         :en ":param_xobject")))))
