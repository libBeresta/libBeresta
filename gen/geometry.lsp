(:файл ""
 :функции
       (
        ;; BRST_Page_GSave
        (:название "Page_GSave"
         :группа "graphics"
         :ошибки ()
         :результат (:тип "STATUS"
                     :ru ""
                     :en "")
         :ru ""
         :en "Save the page's current graphics state to the stack."
         :команда "q"
         :параметры ((:тип "Page"
                      :имя "page"
                      :ru ":param_page"
                      :en ":param_page")))

        ;; BRST_Page_GRestore
        (:название "Page_GRestore"
         :группа "graphics"
         :ошибки ()
         :результат (:тип "STATUS"
                     :ru ""
                     :en "")
         :ru ""
         :en "Restore graphics state which is saved by BRST_Page_GSave()."
         :команда "Q"
         :параметры ((:тип "Page"
                      :имя "page"
                      :ru ":param_page"
                      :en ":param_page")))

        ;; BRST_Page_Concat
        (:название "Page_Concat"
         :группа "graphics"
         :ошибки ()
         :результат (:тип "STATUS"
                     :ru ""
                     :en "")
         :ru ""
         :en "Concatenate the page's transformation matrix and specified matrix."
         :команда "cm"
         :параметры ((:тип "Page"
                      :имя "page"
                      :ru ":param_page"
                      :en ":param_page")
                     (:тип "REAL"
                      :имя "a"
                      :ru ""
                      :en "")
                     (:тип "REAL"
                      :имя "b"
                      :ru ""
                      :en "")
                     (:тип "REAL"
                      :имя "c"
                      :ru ""
                      :en "")
                     (:тип "REAL"
                      :имя "d"
                      :ru ""
                      :en "")
                     (:тип "REAL"
                      :имя "x"
                      :ru ""
                      :en "")
                     (:тип "REAL"
                      :имя "y"
                      :ru ""
                      :en "")))

        ;; BRST_Page_Translate
        (:название "Page_Translate"
         :группа "graphics"
         :ошибки ()
         :результат (:тип "STATUS"
                     :ru ""
                     :en "")
         :ru ""
         :en "Concatenate the page's transformation matrix with translation matrix."
         :команда "cm"
         :параметры ((:тип "Page"
                      :имя "page"
                      :ru ":param_page"
                      :en ":param_page")
                     (:тип "REAL"
                      :имя "dx"
                      :ru ""
                      :en "")
                     (:тип "REAL"
                      :имя "dy"
                      :ru ""
                      :en "")))

        ;; BRST_Page_Scale
        (:название "Page_Scale"
         :группа "graphics"
         :ошибки ()
         :результат (:тип "STATUS"
                     :ru ""
                     :en "")
         :ru ""
         :en "Concatenate the page's transformation matrix with scale matrix."
         :команда "cm"
         :параметры ((:тип "Page"
                      :имя "page"
                      :ru ":param_page"
                      :en ":param_page")
                     (:тип "REAL"
                      :имя "sx"
                      :ru ""
                      :en "")
                     (:тип "REAL"
                      :имя "sy"
                      :ru ""
                      :en "")))

        ;; BRST_Page_RotateDeg
        (:название "Page_RotateDeg"
         :группа "graphics"
         :ошибки ()
         :результат (:тип "STATUS"
                     :ru ""
                     :en "")
         :ru ""
         :en "Concatenate the page's transformation matrix with rotate matrix."
         :команда "cm"
         :параметры ((:тип "Page"
                      :имя "page"
                      :ru ":param_page"
                      :en ":param_page")
                     (:тип "REAL"
                      :имя "degrees"
                      :ru ""
                      :en "")))

        ;; BRST_Page_Rotate
        (:название "Page_Rotate"
         :группа "graphics"
         :ошибки ()
         :результат (:тип "STATUS"
                     :ru ""
                     :en "")
         :ru ""
         :en "Concatenate the page's transformation matrix with rotate matrix."
         :команда "cm"
         :параметры ((:тип "Page"
                      :имя "page"
                      :ru ":param_page"
                      :en ":param_page")
                     (:тип "REAL"
                      :имя "radians"
                      :ru ""
                      :en "")))

        ;; BRST_Page_Skew
        (:название "Page_Skew"
         :группа "graphics"
         :ошибки ()
         :результат (:тип "STATUS"
                     :ru ""
                     :en "")
         :ru ""
         :en "Concatenate the page's transformation matrix with skew matrix."
         :команда "cm"
         :параметры ((:тип "Page"
                      :имя "page"
                      :ru ":param_page"
                      :en ":param_page")
                     (:тип "REAL"
                      :имя "a"
                      :ru ""
                      :en "")
                     (:тип "REAL"
                      :имя "b"
                      :ru ""
                      :en "")))

        ;; BRST_Page_Circle
        (:название "Page_Circle"
         :группа "graphics"
         :ошибки ()
         :результат (:тип "STATUS"
                     :ru ""
                     :en "")
         :ru ""
         :en "Append circle to current path."
         :параметры ((:тип "Page"
                      :имя "page"
                      :ru ":param_page"
                      :en ":param_page")
                     (:тип "REAL"
                      :имя "x"
                      :ru ""
                      :en "")
                     (:тип "REAL"
                      :имя "y"
                      :ru ""
                      :en "")
                     (:тип "REAL"
                      :имя "radius"
                      :ru ""
                      :en "")))

        ;; BRST_Page_Ellipse
        (:название "Page_Ellipse"
         :группа "graphics"
         :ошибки ()
         :результат (:тип "STATUS"
                     :ru ""
                     :en "")
         :ru ""
         :en "Append ellipse to current path."
         :параметры ((:тип "Page"
                      :имя "page"
                      :ru ":param_page"
                      :en ":param_page")
                     (:тип "REAL"
                      :имя "x"
                      :ru ""
                      :en "")
                     (:тип "REAL"
                      :имя "y"
                      :ru ""
                      :en "")
                     (:тип "REAL"
                      :имя "x_radius"
                      :ru ""
                      :en "")
                     (:тип "REAL"
                      :имя "y_radius"
                      :ru ""
                      :en "")))

        ;; BRST_Page_Arc
        (:название "Page_Arc"
         :группа "graphics"
         :ошибки ()
         :результат (:тип "STATUS"
                     :ru ":return_ok"
                     :en ":return_ok")
         :ru "Функция добавляет дугу окружности к текущему графическому пути на указанной странице. 
  Углы задаются в градусах, начиная от вертикали (угол 0 градусов направлен вертикально вверх). 
  Дуга рисуется против часовой стрелки от начального угла (\\c angle1) до конечного угла (\\c angle2)."
         :en "Append circle arc to current path."
         :параметры ((:тип "Page"
                      :имя "page"
                      :ru ":param_page"
                      :en ":param_page")
                     (:тип "REAL"
                      :имя "x"
                      :ru "Координата \\c x центра окружности"
                      :en "")
                     (:тип "REAL"
                      :имя "y"
                      :ru "Координата \\c у центра окружности"
                      :en "")
                     (:тип "REAL"
                      :имя "radius"
                      :ru "Радиус окружности"
                      :en "")
                     (:тип "REAL"
                      :имя "angle1"
                      :ru "Угол начала дуги (градусы)"
                      :en "")
                     (:тип "REAL"
                      :имя "angle2"
                      :ru "Угол окончания дуги (градусы)"
                      :en "")))

        ;; BRST_Page_SetGrayFill
        (:название "Page_SetGrayFill"
         :группа "graphics"
         :ошибки ()
         :результат (:тип "STATUS"
                     :ru ""
                     :en "")
         :ru ""
         :en "Set the filling color (Gray)."
         :команда "g"
         :параметры ((:тип "Page"
                      :имя "page"
                      :ru ":param_page"
                      :en ":param_page")
                     (:тип "REAL"
                      :имя "value"
                      :ru ""
                      :en "")))

        ;; BRST_Page_SetGrayStroke
        (:название "Page_SetGrayStroke"
         :группа "graphics"
         :ошибки ()
         :результат (:тип "STATUS"
                     :ru ""
                     :en "")
         :ru ""
         :en "Set stroking color (Gray)."
         :команда "G"
         :параметры ((:тип "Page"
                      :имя "page"
                      :ru ":param_page"
                      :en ":param_page")
                     (:тип "REAL"
                      :имя "value"
                      :ru ""
                      :en "")))

        ;; BRST_Page_SetRGBFill
        (:название "Page_SetRGBFill"
         :группа "graphics"
         :ошибки ()
         :результат (:тип "STATUS"
                     :ru ""
                     :en "")
         :ru ""
         :en "Set filling color (RGB)."
         :команда "rg"
         :параметры ((:тип "Page"
                      :имя "page"
                      :ru ":param_page"
                      :en ":param_page")
                     (:тип "REAL"
                      :имя "r"
                      :ru ""
                      :en "")
                     (:тип "REAL"
                      :имя "g"
                      :ru ""
                      :en "")
                     (:тип "REAL"
                      :имя "b"
                      :ru ""
                      :en "")))

        ;; BRST_Page_SetRGBFillUint
        (:название "Page_SetRGBFillUint"
         :группа "graphics"
         :ошибки ()
         :результат (:тип "STATUS"
                     :ru ""
                     :en "")
         :ru ""
         :en "Set filling color (RGB) using \\ref BRST_UINT8 values."
         :команда "rg"
         :параметры ((:тип "Page"
                      :имя "page"
                      :ru ":param_page"
                      :en ":param_page")
                     (:тип "UINT8"
                      :имя "r"
                      :ru ""
                      :en "")
                     (:тип "UINT8"
                      :имя "g"
                      :ru ""
                      :en "")
                     (:тип "UINT8"
                      :имя "b"
                      :ru ""
                      :en "")))

        ;; BRST_Page_SetRGBStroke
        (:название "Page_SetRGBStroke"
         :группа "graphics"
         :ошибки ()
         :результат (:тип "STATUS"
                     :ru ""
                     :en "")
         :ru ""
         :en "Set stroke color (RGB)."
         :команда "RG"
         :параметры ((:тип "Page"
                      :имя "page"
                      :ru ":param_page"
                      :en ":param_page")
                     (:тип "REAL"
                      :имя "r"
                      :ru ""
                      :en "")
                     (:тип "REAL"
                      :имя "g"
                      :ru ""
                      :en "")
                     (:тип "REAL"
                      :имя "b"
                      :ru ""
                      :en "")))

        ;; BRST_Page_SetRGBStrokeUint
        (:название "Page_SetRGBStrokeUint"
         :группа "graphics"
         :ошибки ()
         :результат (:тип "STATUS"
                     :ru ""
                     :en "")
         :ru ""
         :en "Set stroke color (RGB) using \\ref BRST_UINT8 values."
         :команда "RG"
         :параметры ((:тип "Page"
                      :имя "page"
                      :ru ":param_page"
                      :en ":param_page")
                     (:тип "UINT8"
                      :имя "r"
                      :ru ""
                      :en "")
                     (:тип "UINT8"
                      :имя "g"
                      :ru ""
                      :en "")
                     (:тип "UINT8"
                      :имя "b"
                      :ru ""
                      :en "")))

        ;; BRST_Page_SetCMYKFill
        (:название "Page_SetCMYKFill"
         :группа "graphics"
         :ошибки ()
         :результат (:тип "STATUS"
                     :ru ""
                     :en "")
         :ru ""
         :en "Set filling color (CMYK)."
         :команда "k"
         :параметры ((:тип "Page"
                      :имя "page"
                      :ru ":param_page"
                      :en ":param_page")
                     (:тип "REAL"
                      :имя "c"
                      :ru ""
                      :en "")
                     (:тип "REAL"
                      :имя "m"
                      :ru ""
                      :en "")
                     (:тип "REAL"
                      :имя "y"
                      :ru ""
                      :en "")
                     (:тип "REAL"
                      :имя "k"
                      :ru ""
                      :en "")))

        ;; BRST_Page_SetCMYKStroke
        (:название "Page_SetCMYKStroke"
         :группа "graphics"
         :ошибки ()
         :результат (:тип "STATUS"
                     :ru ""
                     :en "")
         :ru ""
         :en "Set stroke color (CMYK)."
         :команда "K"
         :параметры ((:тип "Page"
                      :имя "page"
                      :ru ":param_page"
                      :en ":param_page")
                     (:тип "REAL"
                      :имя "c"
                      :ru ""
                      :en "")
                     (:тип "REAL"
                      :имя "m"
                      :ru ""
                      :en "")
                     (:тип "REAL"
                      :имя "y"
                      :ru ""
                      :en "")
                     (:тип "REAL"
                      :имя "k"
                      :ru ""
                      :en "")))

        ;; BRST_Page_Clip
        (:название "Page_Clip"
         :группа "graphics"
         :ошибки ()
         :результат (:тип "STATUS"
                     :ru ""
                     :en "")
         :ru ""
         :en "Modify current clipping path by intersecting it with current path using the nonzero winding number rule."
         :команда "W"
         :параметры ((:тип "Page"
                      :имя "page"
                      :ru ":param_page"
                      :en ":param_page")))

        ;; BRST_Page_Eoclip
        (:название "Page_Eoclip"
         :группа "graphics"
         :ошибки ()
         :результат (:тип "STATUS"
                     :ru ""
                     :en "")
         :ru ""
         :en "Modifies the current clipping path by intersecting it with current path using the even-odd rule."
         :команда "W*"
         :параметры ((:тип "Page"
                      :имя "page"
                      :ru ":param_page"
                      :en ":param_page")))

        ;; BRST_Page_Stroke
        (:название "Page_Stroke"
         :группа "graphics"
         :ошибки ()
         :результат (:тип "STATUS"
                     :ru ""
                     :en "")
         :ru ""
         :en "Paint current path."
         :команда "S"
         :параметры ((:тип "Page"
                      :имя "page"
                      :ru ":param_page"
                      :en ":param_page")))

        ;; BRST_Page_ClosePathStroke
        (:название "Page_ClosePathStroke"
         :группа "graphics"
         :ошибки ()
         :результат (:тип "STATUS"
                     :ru ""
                     :en "")
         :ru ""
         :en "Close and paint current path."
         :команда "s"
         :параметры ((:тип "Page"
                      :имя "page"
                      :ru ":param_page"
                      :en ":param_page")))

        ;; BRST_Page_Fill
        (:название "Page_Fill"
         :группа "graphics"
         :ошибки ()
         :результат (:тип "STATUS"
                     :ru ""
                     :en "")
         :ru ""
         :en "Fill current path using non-zero winding number rule."
         :команда "f"
         :параметры ((:тип "Page"
                      :имя "page"
                      :ru ":param_page"
                      :en ":param_page")))

        ;; BRST_Page_Eofill
        (:название "Page_Eofill"
         :группа "graphics"
         :ошибки ()
         :результат (:тип "STATUS"
                     :ru ""
                     :en "")
         :ru ""
         :en "Fill current path using even-odd rule."
         :команда "f*"
         :параметры ((:тип "Page"
                      :имя "page"
                      :ru ":param_page"
                      :en ":param_page")))

        ;; BRST_Page_FillStroke
        (:название "Page_FillStroke"
         :группа "graphics"
         :ошибки ()
         :результат (:тип "STATUS"
                     :ru ""
                     :en "")
         :ru ""
         :en "Fill current path using the even-odd rule."
         :команда "B"
         :параметры ((:тип "Page"
                      :имя "page"
                      :ru ":param_page"
                      :en ":param_page")))

        ;; BRST_Page_EofillStroke
        (:название "Page_EofillStroke"
         :группа "graphics"
         :ошибки ()
         :результат (:тип "STATUS"
                     :ru ""
                     :en "")
         :ru ""
         :en "Fill current path using the even-odd rule and then paint the path."
         :команда "B*"
         :параметры ((:тип "Page"
                      :имя "page"
                      :ru ":param_page"
                      :en ":param_page")))

        ;; BRST_Page_ClosePathFillStroke
        (:название "Page_ClosePathFillStroke"
         :группа "graphics"
         :ошибки ()
         :результат (:тип "STATUS"
                     :ru ""
                     :en "")
         :ru ""
         :en "Close current path, fill current path using the non-zero winding number rule, then paint path."
         :команда "b"
         :параметры ((:тип "Page"
                      :имя "page"
                      :ru ""
                      :en "")))

        ;; BRST_Page_ClosePathEofillStroke
        (:название "Page_ClosePathEofillStroke"
         :группа "graphics"
         :ошибки ()
         :результат (:тип "STATUS"
                     :ru ""
                     :en "")
         :ru ""
         :en "Close current path, fill current path using the even-odd rule and then paint the path."
         :команда "b*"
         :параметры ((:тип "Page"
                      :имя "page"
                      :ru ":param_page"
                      :en ":param_page")))

        ;; BRST_Page_EndPath
        (:название "Page_EndPath"
         :группа "graphics"
         :ошибки ()
         :результат (:тип "STATUS"
                     :ru ""
                     :en "")
         :ru ""
         :en "Finish path object without filling or painting."
         :команда "n"
         :параметры ((:тип "Page"
                      :имя "page"
                      :ru ":param_page"
                      :en ":param_page")))

        ;; BRST_Page_MoveTo
        (:название "Page_MoveTo"
         :группа "graphics"
         :ошибки ()
         :результат (:тип "STATUS"
                     :ru ""
                     :en "")
         :ru ""
         :en "Start new subpath and move current point for drawing path."
         :команда "m"
         :параметры ((:тип "Page"
                      :имя "page"
                      :ru ":param_page"
                      :en ":param_page")
                     (:тип "REAL"
                      :имя "x"
                      :ru ""
                      :en "")
                     (:тип "REAL"
                      :имя "y"
                      :ru ""
                      :en "")))

        ;; BRST_Page_LineTo
        (:название "Page_LineTo"
         :группа "graphics"
         :ошибки ()
         :результат (:тип "STATUS"
                     :ru ""
                     :en "")
         :ru ""
         :en "Append path from current point to specified point."
         :команда "l"
         :параметры ((:тип "Page"
                      :имя "page"
                      :ru ":param_page"
                      :en ":param_page")
                     (:тип "REAL"
                      :имя "x"
                      :ru ""
                      :en "")
                     (:тип "REAL"
                      :имя "y"
                      :ru ""
                      :en "")))

        ;; BRST_Page_CurveTo
        (:название "Page_CurveTo"
         :группа "graphics"
         :ошибки ()
         :результат (:тип "STATUS"
                     :ru ""
                     :en "")
         :ru ""
         :en "Append Bézier curve to current path using control points."
         :команда "c"
         :параметры ((:тип "Page"
                      :имя "page"
                      :ru ":param_page"
                      :en ":param_page")
                     (:тип "REAL"
                      :имя "x1"
                      :ru ""
                      :en "")
                     (:тип "REAL"
                      :имя "y1"
                      :ru ""
                      :en "")
                     (:тип "REAL"
                      :имя "x2"
                      :ru ""
                      :en "")
                     (:тип "REAL"
                      :имя "y2"
                      :ru ""
                      :en "")
                     (:тип "REAL"
                      :имя "x3"
                      :ru ""
                      :en "")
                     (:тип "REAL"
                      :имя "y3"
                      :ru ""
                      :en "")))

        ;; BRST_Page_CurveTo2
        (:название "Page_CurveTo2"
         :группа "graphics"
         :ошибки ()
         :результат (:тип "STATUS"
                     :ru ""
                     :en "")
         :ru ""
         :en "Append Bézier curve to current path using current point and (x2, y2), (x3, y3) as control points."
         :команда "v"
         :параметры ((:тип "Page"
                      :имя "page"
                      :ru ":param_page"
                      :en ":param_page")
                     (:тип "REAL"
                      :имя "x2"
                      :ru ""
                      :en "")
                     (:тип "REAL"
                      :имя "y2"
                      :ru ""
                      :en "")
                     (:тип "REAL"
                      :имя "x3"
                      :ru ""
                      :en "")
                     (:тип "REAL"
                      :имя "y3"
                      :ru ""
                      :en "")))

        ;; BRST_Page_CurveTo3
        (:название "Page_CurveTo3"
         :группа "graphics"
         :ошибки ()
         :результат (:тип "STATUS"
                     :ru ""
                     :en "")
         :ru ""
         :en "Append Bézier curve to the current path using two specified points."
         :команда "y"
         :параметры ((:тип "Page"
                      :имя "page"
                      :ru ":param_page"
                      :en ":param_page")
                     (:тип "REAL"
                      :имя "x1"
                      :ru ""
                      :en "")
                     (:тип "REAL"
                      :имя "y1"
                      :ru ""
                      :en "")
                     (:тип "REAL"
                      :имя "x3"
                      :ru ""
                      :en "")
                     (:тип "REAL"
                      :имя "y3"
                      :ru ""
                      :en "")))

        ;; BRST_Page_ClosePath
        (:название "Page_ClosePath"
         :группа "graphics"
         :ошибки ()
         :результат (:тип "STATUS"
                     :ru ""
                     :en "")
         :ru ""
         :en "Append straight line from current point to the start point of subpath."
         :команда "h"
         :параметры ((:тип "Page"
                      :имя "page"
                      :ru ":param_page"
                      :en ":param_page")))

        ;; BRST_Page_Rectangle
        (:название "Page_Rectangle"
         :группа "graphics"
         :ошибки ()
         :результат (:тип "STATUS"
                     :ru ""
                     :en "")
         :ru ""
         :en "Append rectangle to the current path."
         :команда "re"
         :параметры ((:тип "Page"
                      :имя "page"
                      :ru ":param_page"
                      :en ":param_page")
                     (:тип "REAL"
                      :имя "x"
                      :ru ""
                      :en "")
                     (:тип "REAL"
                      :имя "y"
                      :ru ""
                      :en "")
                     (:тип "REAL"
                      :имя "width"
                      :ru ""
                      :en "")
                     (:тип "REAL"
                      :имя "height"
                      :ru ""
                      :en "")))

        ;; BRST_Page_SetLineWidth
        (:название "Page_SetLineWidth"
         :группа "graphics"
         :ошибки ()
         :результат (:тип "STATUS"
                     :ru ""
                     :en "")
         :ru ""
         :en "Set width of the line used to stroke paths."
         :команда "w"
         :параметры ((:тип "Page"
                      :имя "page"
                      :ru ":param_page"
                      :en ":param_page")
                     (:тип "REAL"
                      :имя "line_width"
                      :ru ""
                      :en "")))


        ;; BRST_Page_SetLineCap
        (:название "Page_SetLineCap"
         :группа "graphics"
         :ошибки ()
         :результат (:тип "STATUS"
                     :ru ""
                     :en "")
         :ru ""
         :en "Set lines endpoints shape style."
         :команда "J"
         :параметры ((:тип "Page"
                      :имя "page"
                      :ru ":param_page"
                      :en ":param_page")
                     (:тип "LineCap"
                      :имя "line_cap"
                      :ru ""
                      :en "")))

        ;; BRST_Page_SetLineJoin
        (:название "Page_SetLineJoin"
         :группа "graphics"
         :ошибки ()
         :результат (:тип "STATUS"
                     :ru ""
                     :en "")
         :ru ""
         :en "Set line join shape style."
         :команда "j"
         :параметры ((:тип "Page"
                      :имя "page"
                      :ru ":param_page"
                      :en ":param_page")
                     (:тип "LineJoin"
                      :имя "line_join"
                      :ru ""
                      :en "")))

        ;; Page_SetMiterLimit
        (:название "Page_SetMiterLimit"
         :группа "graphics"
         :ошибки ()
         :результат (:тип "STATUS"
                     :ru ""
                     :en "")
         :ru ""
         :en "Set miter limit for line joins."
         :команда "M"
         :параметры ((:тип "Page"
                      :имя "page"
                      :ru ":param_page"
                      :en ":param_page")
                     (:тип "REAL"
                      :имя "miter_limit"
                      :ru ""
                      :en "")))

        ;; BRST_Page_SetDash
        (:название "Page_SetDash"
         :группа "graphics"
         :ошибки ()
         :результат (:тип "STATUS"
                     :ru ""
                     :en "")
         :ru ""
         :en "Set dash pattern for lines in the page."
         :команда "d"
         :параметры ((:тип "Page"
                      :имя "page"
                      :ru ":param_page"
                      :en ":param_page")
                     (:тип "const REAL*"
                      :имя "dash_pattern"
                      :ru ""
                      :en "")
                     (:тип "UINT"
                      :имя "num_elem"
                      :ru ""
                      :en "")
                     (:тип "REAL"
                      :имя "phase"
                      :ru ""
                      :en "")))

        ;; BRST_Page_SetFlat
        (:название "Page_SetFlat"
         :группа "graphics"
         :ошибки ()
         :результат (:тип "STATUS"
                     :ru ""
                     :en "")
         :ru ""
         :en "Set flatness tolerance for curves rendering."
         :команда "i"
         :параметры ((:тип "Page"
                      :имя "page"
                      :ru ":param_page"
                      :en ":param_page")
                     (:тип "REAL"
                      :имя "flatness"
                      :ru ""
                      :en "")))

        ;; BRST_Page_RGBFill
        (:название "Page_RGBFill"
         :группа "page"
         :ошибки ()
         :результат (:тип "RGBColor"
                     :ru ""
                     :en "")
         :ru ""
         :en "Get page current filling color value (RGB)."
         :параметры ((:тип "Page"
                      :имя "page"
                      :ru ":param_page"
                      :en ":param_page")))

        ;; BRST_Page_RGBStroke
        (:название "Page_RGBStroke"
         :группа "page"
         :ошибки ()
         :результат (:тип "RGBColor"
                     :ru ""
                     :en "")
         :ru ""
         :en "Get page current stroke color value (RGB)."
         :параметры ((:тип "Page"
                      :имя "page"
                      :ru ":param_page"
                      :en ":param_page")))

        ;; BRST_Page_CMYKFill
        (:название "Page_CMYKFill"
         :группа "page"
         :ошибки ()
         :результат (:тип "CMYKColor"
                     :ru ""
                     :en "")
         :ru ""
         :en "Get page current filling color value (CMYK)."
         :параметры ((:тип "Page"
                      :имя "page"
                      :ru ":param_page"
                      :en ":param_page")))

        ;; BRST_Page_CMYKStroke
        (:название "Page_CMYKStroke"
         :группа "page"
         :ошибки ()
         :результат (:тип "CMYKColor"
                     :ru ""
                     :en "")
         :ru ""
         :en "Get page current stroke color value (CMYK)."
         :параметры ((:тип "Page"
                      :имя "page"
                      :ru ":param_page"
                      :en ":param_page")))

        ;; BRST_Page_GrayFill
        (:название "Page_GrayFill"
         :группа "page"
         :ошибки ()
         :результат (:тип "REAL"
                     :ru ""
                     :en "")
         :ru ""
         :en "Get page current filling color value (Gray)."
         :параметры ((:тип "Page"
                      :имя "page"
                      :ru ":param_page"
                      :en ":param_page")))

        ;; BRST_Page_GrayStroke
        (:название "Page_GrayStroke"
         :группа "page"
         :ошибки ()
         :результат (:тип "REAL"
                     :ru ""
                     :en "")
         :ru ""
         :en "Get page current stroke color value (Gray)."
         :параметры ((:тип "Page"
                      :имя "page"
                      :ru ":param_page"
                      :en ":param_page")))

        ;; BRST_Page_StrokingColorSpace
        (:название "Page_StrokingColorSpace"
         :группа "page"
         :ошибки ()
         :результат (:тип "ColorSpace"
                     :ru ""
                     :en "")
         :ru ""
         :en "Get page current stroke color space."
         :параметры ((:тип "Page"
                      :имя "page"
                      :ru ":param_page"
                      :en ":param_page")))

        ;; BRST_Page_FillingColorSpace
        (:название "Page_FillingColorSpace"
         :группа "page"
         :ошибки ()
         :результат (:тип "ColorSpace"
                     :ru ""
                     :en "")
         :ru ""
         :en "Get page current filling color space."
         :параметры ((:тип "Page"
                      :имя "page"
                      :ru ":param_page"
                      :en ":param_page")))

        ;; BRST_Page_LineWidth
        (:название "Page_LineWidth"
         :группа "page"
         :ошибки ()
         :результат (:тип "REAL"
                     :ru ""
                     :en "")
         :ru ""
         :en "Get page current line width."
         :параметры ((:тип "Page"
                      :имя "page"
                      :ru ":param_page"
                      :en ":param_page")))

        ;; BRST_Page_LineCap
        (:название "Page_LineCap"
         :группа "page"
         :ошибки ()
         :результат (:тип "LineCap"
                     :ru ""
                     :en "")
         :ru ""
         :en "Get page current line cap."
         :параметры ((:тип "Page"
                      :имя "page"
                      :ru ":param_page"
                      :en ":param_page")))

        ;; BRST_Page_LineJoin
        (:название "Page_LineJoin"
         :группа "page"
         :ошибки ()
         :результат (:тип "LineJoin"
                     :ru ""
                     :en "")
         :ru ""
         :en "Get page current line join."
         :параметры ((:тип "Page"
                      :имя "page"
                      :ru ":param_page"
                      :en ":param_page")))

        ;; BRST_Page_MiterLimit
        (:название "Page_MiterLimit"
         :группа "page"
         :ошибки ()
         :результат (:тип "REAL"
                     :ru ""
                     :en "")
         :ru ""
         :en "Get page current miter limit."
         :параметры ((:тип "Page"
                      :имя "page"
                      :ru ":param_page"
                      :en ":param_page")))

        ;; BRST_Page_Dash
        (:название "Page_Dash"
         :группа "page"
         :ошибки ()
         :результат (:тип "DashMode"
                     :ru ""
                     :en "")
         :ru ""
         :en "Get page current line dash pattern."
         :параметры ((:тип "Page"
                      :имя "page"
                      :ru ":param_page"
                      :en ":param_page")))

        ;; BRST_Page_Flat
        (:название "Page_Flat"
         :группа "page"
         :ошибки ()
         :результат (:тип "REAL"
                     :ru ""
                     :en "")
         :ru ""
         :en "Get page current flatness value."
         :параметры ((:тип "Page"
                      :имя "page"
                      :ru ":param_page"
                      :en ":param_page")))

        ;; BRST_Page_TransMatrix
        (:название "Page_TransMatrix"
         :группа "page"
         :ошибки ()
         :результат (:тип "TransMatrix"
                     :ru ""
                     :en "")
         :ru ""
         :en "Get page current transformation matrix."
         :параметры ((:тип "Page"
                      :имя "page"
                      :ru ":param_page"
                      :en ":param_page")))))
