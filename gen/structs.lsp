(:файл "structs"
 :структуры ((:имя "Point"
              :en "Point position on a page" :ru "Положение точки на странице"
              :поля ((:поле "x" :тип "REAL" :en "" :ru "")
                     (:поле "y" :тип "REAL" :en "" :ru "")))
             (:имя "Rect"
              :en "" :ru ""
              :поля ((:поле "left"   :тип "REAL" :en "" :ru "")
                     (:поле "bottom" :тип "REAL" :en "" :ru "")
                     (:поле "right"  :тип "REAL" :en "" :ru "")
                     (:поле "top"    :тип "REAL" :en "" :ru "")))

             (:имя "TextWidth"
              :en "" :ru ""
              :поля ((:поле "numchars"   :тип "UINT" :en "" :ru "")
                     (:поле "numwords" :тип "UINT" :en "" :ru "")
                     (:поле "width"  :тип "UINT" :en "" :ru "")
                     (:поле "numspace"    :тип "UINT" :en "" :ru "")))))
