(:файл "geometry_defines"
 :структуры ((:имя "RGBColor"
              :en "RGB colour storage structure" :ru "Структура для хранения информации о цвете (RGB)"
              :поля ((:поле "r" :тип "REAL" :en "" :ru "Красная компонента цвета")
                     (:поле "g" :тип "REAL" :en "" :ru "Зеленая компонента цвета")
                     (:поле "b" :тип "REAL" :en "" :ru "Синяя компонента цвета")))

             (:имя "CMYKColor"
              :en "CMYK colour storage structure" :ru "Структура для хранения информации о цвете (CMYK)"
              :поля ((:поле "c" :тип "REAL" :en "" :ru "Голубая компонента цвета")
                     (:поле "m" :тип "REAL" :en "" :ru "Пурпурная компонента цвета")
                     (:поле "y" :тип "REAL" :en "" :ru "Желтая компонента цвета")
                     (:поле "k" :тип "REAL" :en "" :ru "Черная компонента цвета")))

             (:имя "DashMode"
              :en "Dash pattern structure" :ru "Структура описания пунктира"
              :поля ((:поле "ptn"     :тип "REAL" :en "" :ru "" :размер "8")
                     (:поле "num_ptn" :тип "UINT" :en "" :ru "")
                     (:поле "phase"   :тип "REAL" :en "" :ru ""))))
 :перечисления
       ((:имя "LineCap"
         :ru ""
         :en "Line Cap Styles (Table 54)"
         :элементы ((:элемент "BUTT_CAP"              :en "Butt cap. The stroke shall be squared off at the endpoint of the path. There shall be no projection beyond the end of the path." 
                                                      :ru "Квадратное окончание. Линия заканчивается квадратом, проходящим через концевую точку. За конец пути ничего не выступает.")
                    (:элемент "ROUND_CAP"             :en "Round cap. A semicircular arc with a diameter equal to the line width shall be drawn around the endpoint and shall be filled in." 
                                                      :ru "Круглое окончание. Рисуется и заливается полуокружность с центром в конечной точке диаметром, равным ширине линии.")
                    (:элемент "PROJECTING_SQUARE_CAP" :en "Projecting square cap. The stroke shall continue beyond the endpoint of the path for a distance equal to half the line width and shall be squared off." 
                                                      :ru "Выступающее квадратное окончание. Линия продолжается за конечную точку на расстояние, равное половине ширины линии и затем в этой точке строится квадратное окончание.")))

        (:имя "LineJoin"
         :ru ""
         :en "Line Join Styles (Table 55)"
         :элементы ((:элемент "MITER_JOIN" :en "" :ru "")
                    (:элемент "ROUND_JOIN" :en "" :ru "")
                    (:элемент "BEVEL_JOIN" :en "" :ru "")))

       (:имя "BorderStyle"
        :ru ""
        :en "Entries in a border style dictionary (Table 166)"
        :элементы ((:элемент "BORDERSTYLE_SOLID"      :en "Solid rectangle"                                :ru "")
                   (:элемент "BORDERSTYLE_DASHED"     :en "Dashed rectangle"                               :ru "")
                   (:элемент "BORDERSTYLE_BEVELED"    :en "Embossed rectangle"                             :ru "")
                   (:элемент "BORDERSTYLE_INSET"      :en "Engraved rectangle"                             :ru "")
                   (:элемент "BORDERSTYLE_UNDERLINED" :en "Single line under the bottom of the annotation" :ru "")))

       (:имя "BlendMode"
        :ru ""
        :en "Standard separable blend modes (Table 136)"
        :элементы ((:элемент "BLENDMODE_NORMAL"      :en "" :ru "")
                   (:элемент "BLENDMODE_COMPATIBLE"  :en "" :ru "")
                   (:элемент "BLENDMODE_MULTIPLY"    :en "" :ru "")
                   (:элемент "BLENDMODE_SCREEN"      :en "" :ru "")
                   (:элемент "BLENDMODE_OVERLAY"     :en "" :ru "")
                   (:элемент "BLENDMODE_DARKEN"      :en "" :ru "")
                   (:элемент "BLENDMODE_LIGHTEN"     :en "" :ru "")
                   (:элемент "BLENDMODE_COLOR_DODGE" :en "" :ru "")
                   (:элемент "BLENDMODE_COLOR_BURN"  :en "" :ru "")
                   (:элемент "BLENDMODE_HARD_LIGHT"  :en "" :ru "")
                   (:элемент "BLENDMODE_SOFT_LIGHT"  :en "" :ru "")
                   (:элемент "BLENDMODE_DIFFERENCE"  :en "" :ru "")
                   (:элемент "BLENDMODE_EXCLUSION"   :en "" :ru "")))

       (:имя "ColorSpace"
        :ru ""
        :en "Colour Space Families (Table 62)"
        :элементы ((:элемент "COLORSPACE_DEVICE_GRAY" :en "" :ru "")
                   (:элемент "COLORSPACE_DEVICERGB"   :en "" :ru "")
                   (:элемент "COLORSPACE_DEVICECMYK"  :en "" :ru "")
                   (:элемент "COLORSPACE_CALGRAY"     :en "" :ru "")
                   (:элемент "COLORSPACE_CALRGB"      :en "" :ru "")
                   (:элемент "COLORSPACE_LAB"         :en "" :ru "")
                   (:элемент "COLORSPACE_ICCBASED"    :en "" :ru "")
                   (:элемент "COLORSPACE_SEPARATION"  :en "" :ru "")
                   (:элемент "COLORSPACE_DEVICEN"     :en "" :ru "")
                   (:элемент "COLORSPACE_INDEXED"     :en "" :ru "")
                   (:элемент "COLORSPACE_PATTERN"     :en "" :ru "")))))
