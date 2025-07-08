(:файл "geometry"
 :функции
       (
        ;; BRST_Page_GSave
        (:название "Page_GSave"
         :группа "graphics"
         :ошибки ()
	 :результат (:тип "STATUS"
		     :ru ":return_ok"
		     :en ":return_ok")
         :ru "Сохранение в стек текущего графического состояния страницы.

Функция BRST_Page_GSave() сохраняет графическое состояние и восстанавливает ранее сохранённое состояние с помощью функции BRST_Page_GRestore().

Параметры состояния, сохраняемые функцией BRST_Page_GSave(), включают:

    - Межбуквенный интервал
    - Область отсечения
    - Шаблон пунктира
    - Цвет заливки
    - Точность аппроксимации
    - Шрифт
    - Размер шрифта
    - Горизонтальное масштабирование
    - Толщина линии
    - Стиль конца линии (line cap)
    - Стиль стыка линий (line join)
    - Gредельное значение острого угла линии (miter limit)
    - Режим отображения (rendering mode)
    - Цвет штриха
    - Межстрочный интервал текста
    - Подъём базовой линии текста (text rise)
    - Матрица преобразований
    - Межсловный интервал"

         :en "Save the page's current graphics state to the stack.

  Application can call BRST_Page_GSave() and can restore saved state by calling BRST_Page_GRestore().

  Saved by BRST_Page_GSave() state parameters are:

    - Character Spacing
    - Clipping Path
    - Dash Mode
    - Fill Color
    - Flatness
    - Font
    - Font Size
    - Horizontal Scaling
    - Line Width
    - Line Cap Style
    - Line Join Style
    - Miter Limit
    - Rendering Mode
    - Stroke Color
    - Text Leading
    - Text Rise
    - Transformation Matrix
    - Word Spacing"
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
		     :ru ":return_ok"
		     :en ":return_ok")
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
		     :ru ":return_ok"
		     :en ":return_ok")
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
		     :ru ":return_ok"
		     :en ":return_ok")
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
		     :ru ":return_ok"
		     :en ":return_ok")
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
		     :ru ":return_ok"
		     :en ":return_ok")
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
		     :ru ":return_ok"
		     :en ":return_ok")
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
		     :ru ":return_ok"
		     :en ":return_ok")
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
		     :ru ":return_ok"
		     :en ":return_ok")
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
		     :ru ":return_ok"
		     :en ":return_ok")
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
		     :ru ":return_ok"
		     :en ":return_ok")
         :ru ""
         :en "Set the fill color (Gray)."
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
		     :ru ":return_ok"
		     :en ":return_ok")
         :ru ""
         :en "Set stroke color (Gray)."
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
		     :ru ":return_ok"
		     :en ":return_ok")
         :ru ""
         :en "Set fill color (RGB)."
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
		     :ru ":return_ok"
		     :en ":return_ok")
         :ru ""
         :en "Set fill color (RGB) using \\ref BRST_UINT8 values."
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
		     :ru ":return_ok"
		     :en ":return_ok")
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
		     :ru ":return_ok"
		     :en ":return_ok")
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
		     :ru ":return_ok"
		     :en ":return_ok")
         :ru ""
         :en "Set fill color (CMYK)."
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
		     :ru ":return_ok"
		     :en ":return_ok")
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
		     :ru ":return_ok"
		     :en ":return_ok")
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
		     :ru ":return_ok"
		     :en ":return_ok")
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
		     :ru ":return_ok"
		     :en ":return_ok")
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
		     :ru ":return_ok"
		     :en ":return_ok")
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
		     :ru ":return_ok"
		     :en ":return_ok")
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
		     :ru ":return_ok"
		     :en ":return_ok")
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
		     :ru ":return_ok"
		     :en ":return_ok")
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
		     :ru ":return_ok"
		     :en ":return_ok")
         :ru ""
         :en "Close current path, fill current path using the non-zero winding number rule, then paint path."
         :команда "b"
         :параметры ((:тип "Page"
                      :имя "page"
                      :ru ":param_page"
                      :en ":param_page")))

        ;; BRST_Page_ClosePathEofillStroke
        (:название "Page_ClosePathEofillStroke"
         :группа "graphics"
         :ошибки ()
	 :результат (:тип "STATUS"
		     :ru ":return_ok"
		     :en ":return_ok")
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
		     :ru ":return_ok"
		     :en ":return_ok")
         :ru ""
         :en "Finish path object without fill or painting."
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
		     :ru ":return_ok"
		     :en ":return_ok")
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
		     :ru ":return_ok"
		     :en ":return_ok")
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
		     :ru ":return_ok"
		     :en ":return_ok")
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
		     :ru ":return_ok"
		     :en ":return_ok")
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
		     :ru ":return_ok"
		     :en ":return_ok")
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
		     :ru ":return_ok"
		     :en ":return_ok")
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
		     :ru ":return_ok"
		     :en ":return_ok")
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
		     :ru ":return_ok"
		     :en ":return_ok")
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
		     :ru ":return_ok"
		     :en ":return_ok")
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
		     :ru ":return_ok"
		     :en ":return_ok")
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
		     :ru ":return_ok"
		     :en ":return_ok")
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
		     :ru ":return_ok"
		     :en ":return_ok")
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
		     :ru ":return_ok"
		     :en ":return_ok")
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
                     :ru "Текущее значение цвета заливки (RGB) при успехе, в противном случае возвращается `BRST_RGBColor{0, 0, 0}`."
                     :en "Page current fill color value (RGB) on success, otherwise it returns `BRST_RGBColor{0, 0, 0}`.")
         :ru "Текущее значение цвета заливки (RGB).
  BRST_Page_RGBFill() действительна только в случае использования цветового пространства \\ref BRST_CS_DEVICE_RGB."
         :en "Get page current fill color value (RGB).
  BRST_Page_RGBFill() is valid only when the page's fill color space is \\ref BRST_CS_DEVICE_RGB."
         :параметры ((:тип "Page"
                      :имя "page"
                      :ru ":param_page"
                      :en ":param_page")))

        ;; BRST_Page_RGBStroke
        (:название "Page_RGBStroke"
         :группа "page"
         :ошибки ()
         :результат (:тип "RGBColor"
                     :ru "Текущее значение цвета штриха (RGB) при успехе, в противном случае возвращается `BRST_RGBColor{0, 0, 0}`."
                     :en "Page current stroke color value (RGB) on success, otherwise it returns `BRST_RGBColor{0, 0, 0}`.")
         :ru "Текущее значение цвета штриха (RGB).
  BRST_Page_RGBStroke() действительна только в случае использования цветового пространства \\ref BRST_CS_DEVICE_RGB."
         :en "Get page current stroke color value (RGB).
  BRST_Page_RGBStroke() is valid only when the page's stroke color space is \\ref BRST_CS_DEVICE_RGB."
         :параметры ((:тип "Page"
                      :имя "page"
                      :ru ":param_page"
                      :en ":param_page")))

        ;; BRST_Page_CMYKFill
        (:название "Page_CMYKFill"
         :группа "page"
         :ошибки ()
         :результат (:тип "CMYKColor"
                     :ru "Текущее значение цвета заливки (CMYK) при успехе, в противном случае возвращается `BRST_CMYKColor{0, 0, 0, 0}`."
                     :en "Page current fill color value (CMYK) on success, otherwise it returns `BRST_CMYKColor{0, 0, 0, 0}`.")
         :ru "Текущее значение цвета заливки (CMYK).
  BRST_Page_CMYKFill() действительна только в случае использования цветового пространства \\ref BRST_CS_DEVICE_CMYK."
         :en "Get page current fill color value (CMYK).
  BRST_Page_CMYKFill() is valid only when the page's fill color space is \\ref BRST_CS_DEVICE_CMYK."
         :параметры ((:тип "Page"
                      :имя "page"
                      :ru ":param_page"
                      :en ":param_page")))

        ;; BRST_Page_CMYKStroke
        (:название "Page_CMYKStroke"
         :группа "page"
         :ошибки ()
         :результат (:тип "CMYKColor"
                     :ru "Текущее значение цвета штриха (CMYK) при успехе, в противном случае возвращается `BRST_CMYKColor{0, 0, 0, 0}`."
                     :en "Page current stroke color value (CMYK) on success, otherwise it returns `BRST_CMYKColor{0, 0, 0, 0}`.")
         :ru "Текущее значение цвета штриха (CMYK).
  BRST_Page_CMYKFill() действительна только в случае использования цветового пространства \\ref BRST_CS_DEVICE_CMYK."
         :en "Get page current stroke color value (CMYK).
  BRST_Page_CMYKFill() is valid only when the page's stroke color space is \\ref BRST_CS_DEVICE_CMYK."
         :параметры ((:тип "Page"
                      :имя "page"
                      :ru ":param_page"
                      :en ":param_page")))

        ;; BRST_Page_GrayFill
        (:название "Page_GrayFill"
         :группа "page"
         :ошибки ()
         :результат (:тип "REAL"
                     :ru "Текущее значение цвета заливки (Gray) при успехе, в противном случае возвращается `0.0`."
                     :en "Page current fill color value (Gray) on success, otherwise it returns `0.0`.")
         :ru "Текущее значение цвета заливки (Gray).
  BRST_Page_GrayFill() действительна только в случае использования цветового пространства \\ref BRST_CS_DEVICE_GRAY."
         :en "Get page current fill color value (Gray).
  BRST_Page_GrayFill() is valid only when the page's fill color space is \\ref BRST_CS_DEVICE_GRAY."
         :параметры ((:тип "Page"
                      :имя "page"
                      :ru ":param_page"
                      :en ":param_page")))

        ;; BRST_Page_GrayStroke
        (:название "Page_GrayStroke"
         :группа "page"
         :ошибки ()
         :результат (:тип "REAL"
                     :ru "Текущее значение цвета штриха (Gray) при успехе, в противном случае возвращается `0.0`."
                     :en "Page current fill color value (Gray) on success, otherwise it returns `0.0`.")
         :ru "Текущее значение цвета штриха (Gray).
  BRST_Page_GrayStroke() действительна только в случае использования цветового пространства \\ref BRST_CS_DEVICE_GRAY."
         :en "Get page current stroke color value (Gray).
  BRST_Page_Gray() is valid only when the page's fill color space is \\ref BRST_CS_DEVICE_GRAY."
         :параметры ((:тип "Page"
                      :имя "page"
                      :ru ":param_page"
                      :en ":param_page")))

        ;; BRST_Page_StrokeColorSpace
        (:название "Page_StrokeColorSpace"
         :группа "page"
         :ошибки ()
         :результат (:тип "ColorSpace"
                     :ru "Текущее значение цветового пространства штриха при успехе, в противном случае возвращается \\ref BRST_CS_EOF."
                     :en "Page current stroke color space on success, otherwise it returns \\ref BRST_CS_EOF.")
         :ru "Текущее значение цветового пространства штриха."
         :en "Get page current stroke color space."
         :параметры ((:тип "Page"
                      :имя "page"
                      :ru ":param_page"
                      :en ":param_page")))

        ;; BRST_Page_FillColorSpace
        (:название "Page_FillColorSpace"
         :группа "page"
         :ошибки ()
         :результат (:тип "ColorSpace"
                     :ru "Текущее значение цветового пространства заливки при успехе, в противном случае возвращается \\ref BRST_CS_EOF."
                     :en "Page current fill color space on success, otherwise it returns \\ref BRST_CS_EOF.")
         :ru "Текущее значение цветового пространства заливки."
         :en "Get page current fill color space."
         :параметры ((:тип "Page"
                      :имя "page"
                      :ru ":param_page"
                      :en ":param_page")))

        ;; BRST_Page_LineWidth
        (:название "Page_LineWidth"
         :группа "page"
         :ошибки ()
         :результат (:тип "REAL"
                     :ru "Текущее значение толщины линии для отображения путей, в противном случае возвращается \\ref BRST_DEF_LINEWIDTH."
                     :en "Page current line width for path painting on success, otherwise it returns \\ref BRST_DEF_LINEWIDTH.")
         :ru "Текущее значение толщины линии."
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
                     :ru "Текущее значение стиля конца линии для отображения путей, в противном случае возвращается \\ref BRST_DEF_LINECAP."
                     :en "Page current line cap for path painting on success, otherwise it returns \\ref BRST_DEF_LINECAP.")
         :ru "Стиль конца линии."
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
                     :ru "Текущее значение стиля стыка линии для отображения путей при успехе, в противном случае возвращается \\ref BRST_DEF_LINEJOIN."
                     :en "Page current line join for path painting on success, otherwise it returns \\ref BRST_DEF_LINEJOIN.")
         :ru "Текущий стиль стыка линий."
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
                     :ru "Текущее предельное значение острого угла линии для отображения путей при успехе, в противном случае возвращается \\ref BRST_DEF_MITERLIMIT."
                     :en "Page current line miter limit for path painting on success, otherwise it returns \\ref BRST_DEF_MITERLIMIT.")
         :ru "Текущее предельное значение острого угла (miter limit)."
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
                     :ru "Текущее значение шаблона пунктира \\ref BRST_DashMode для отображения линий при успехе,
  в противном случае возвращается `BRST_DashMode{{0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f}, 0.0f, 0.0f}`."
                     :en "Page current line dash pattern \\ref BRST_DashMode for path painting on success,
  otherwise it returns `BRST_DashMode{{0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f}, 0.0f, 0.0f}`.")
         :ru "Текущий шаблон пунктира (line dash pattern)."
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
                     :ru "Текущее значение точности аппроксимации (flatness) при успехе, в противном случае возвращается \\ref BRST_DEF_FLATNESS."
                     :en "Page current flatness value on success, otherwise it returns \\ref BRST_DEF_FLATNESS.")
         :ru "Текущее значение точности аппроксимации (flatness)."
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
                     :ru "Матрица преобразований \\ref BRST_TransMatrix при успехе, в противном случае возвращается `BRST_TransMatrix{1, 0, 0, 1, 0, 0}` (тождественная матрица преобразований)."
                     :en "Page current transformation matrix \\ref BRST_TransMatrix on success, otherwise it returns `BRST_TransMatrix{1, 0, 0, 1, 0, 0}` (identity transfromation matrix).")
         :ru "Текущая матрица преобразований."
         :en "Get page current transformation matrix."
         :параметры ((:тип "Page"
                      :имя "page"
                      :ru ":param_page"
                      :en ":param_page")))))
