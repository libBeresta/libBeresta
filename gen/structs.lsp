(:file "structs"
 :structs ((:name "Point"
              :en "Point position on a page" :ru "Положение точки на странице"
              :fields ((:field "x" :type "REAL" :en "" :ru "")
                     (:field "y" :type "REAL" :en "" :ru "")))
             (:name "Rect"
              :en "" :ru ""
              :fields ((:field "left"   :type "REAL" :en "" :ru "")
                     (:field "bottom" :type "REAL" :en "" :ru "")
                     (:field "right"  :type "REAL" :en "" :ru "")
                     (:field "top"    :type "REAL" :en "" :ru "")))

             (:name "TextWidth"
              :en "" :ru ""
              :fields ((:field "numchars"   :type "UINT" :en "" :ru "")
                     (:field "numwords" :type "UINT" :en "" :ru "")
                     (:field "width"  :type "UINT" :en "" :ru "")
                     (:field "numspace"    :type "UINT" :en "" :ru "")))))
