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
    - Стиль окончания линии (line cap)
    - Стиль стыка линий (line join)
    - Предельное значение острого угла линии (miter limit)
    - Режим отображения (rendering mode)
    - Цвет линии
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
         :ru "Восстановление графического состояния страницы, ранее сохраненного функцией BRST_Page_GSave()."
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
         :ru "Конкатенация указанной матрицы и матрицы преобразования страницы.

  Например, если вам нужно повернуть систему координат страницы на 45 градусов, функцию BRST_Page_Concat() следует вызвать так:

  \\code
  BRST_REAL rad = 45 / 180 * BRST_PI;
  BRST_Page_Concat(page, cos(rad), sin(rad), -sin(rad), cos(rad), 0, 0);
  \\endcode

  С помощью следующей команды можно изменить разрешение системы системы координат на 300 точек на дюйм (dpi):

  \\code
  BRST_Page_Concat(page, 72.0f / 300.0f, 0, 0, 72.0f / 300.0f, 0, 0);
  \\endcode

  Перед вызовом функции BRST_Page_Concat() рекомендуется сохранить текущее графическое состояние
  с помощью функции BRST_Page_GSave(). Затем внесённые изменения можно отменить,
  восстановив предыдущее графическое состояние с помощью функции BRST_Page_GRestore().

  \\code
  // Сохраняем текущее состояние графики
  BRST_Page_GSave(page);

  // Применяем матрицу преобразования
  BRST_Page_Concat(page, 72.0f / 300.0f, 0, 0, 72.0f / 300.0f, 0, 0);

  // Показываем текст на с учетом изменения разрешения
  BRST_Page_BeginText(page);
  BRST_Page_MoveTextPos(page, 50, 100);
  BRST_Page_ShowText(page, \"Текст на трансформированных координатах\");
  BRST_Page_EndText(page);

  // Восстанавливаем предыдущее состояние графики
  BRST_Page_GRestore(page);
  \\endcode

  Функцию BRST_Page_GSave() можно вызывать, когда установлен режим \\ref BRST_GMODE_PAGE_DESCRIPTION."

		   :en "Concatenate the page's transformation matrix and specified matrix.

  For example, if you want to rotate the coordinate system of the page by 45 degrees, use BRST_Page_Concat() as follows.

  \code
  BRST_REAL rad = 45 / 180 * BRST_PI;
  BRST_Page_Concat(page, cos(rad), sin(rad), -sin(rad), cos(rad), 0, 0);
  \endcode

  To change the coordinate system of the page to 300 dpi, use BRST_Page_Concat() as follows.

  \\code
  BRST_Page_Concat(page, 72.0f / 300.0f, 0, 0, 72.0f / 300.0f, 0, 0);
  \\endcode

  Invoke BRST_Page_GSave() before BRST_Page_Concat(). Then the changes by BRST_Page_Concat() can be restored by invoking BRST_Page_GRestore().

  \\code
  // Save current graphics state
  BRST_Page_GSave(page);

  //Concatenate transformation matrix
  BRST_Page_Concat(page, 72.0f / 300.0f, 0, 0, 72.0f / 300.0f, 0, 0);

  // Show text on translated coordinates
  BRST_Page_BeginText(page);
  BRST_Page_MoveTextPos(page, 50, 100);
  BRST_Page_ShowText(page, \"Text on the translated coordinates\");
  BRST_Page_EndText(page);

  // Restore the graphics states
  BRST_Page_GRestore (page);
  \\endcode

  Application can call BRST_Page_GSave() when graphics mode is \\ref BRST_GMODE_PAGE_DESCRIPTION."

		   :команда "cm"
		   :параметры ((:тип "Page"
				:имя "page"
				:ru ":param_page"
				:en ":param_page")
			       (:тип "REAL"
				:имя "a"
				:ru "Параметр \\c a матрицы преобразования."
				:en "\\c a parameter of transformation matrix.")
			       (:тип "REAL"
				:имя "b"
				:ru "Параметр \\c b матрицы преобразования."
				:en "\\c b parameter of transformation matrix.")
			       (:тип "REAL"
				:имя "c"
				:ru "Параметр \\c c матрицы преобразования."
				:en "\\c c parameter of transformation matrix.")
			       (:тип "REAL"
				:имя "d"
				:ru "Параметр \\c d матрицы преобразования."
				:en "\\c d parameter of transformation matrix.")
			       (:тип "REAL"
				:имя "x"
				:ru "Параметр \\c x матрицы преобразования."
				:en "\\c x parameter of transformation matrix.")
			       (:тип "REAL"
				:имя "y"
				:ru "Параметр \\c y матрицы преобразования."
				:en "\\c y parameter of transformation matrix.")))

        ;; BRST_Page_Translate
        (:название "Page_Translate"
         :группа "graphics"
         :ошибки ()
	 :результат (:тип "STATUS"
		     :ru ":return_ok"
		     :en ":return_ok")
         :ru "Конкатенация матрицы переноса и матрицы преобразования страницы.

  Координатная система страницы переносится на \\c dx координатных единиц по горизонтали
  и \\c dy координатных единиц по вертикали."
         :en "Concatenate the page's transformation matrix with translation matrix.

  Coordinate system is translated by \\c dx and \\c dy coordinate units."
         :команда "cm"
         :параметры ((:тип "Page"
                      :имя "page"
                      :ru ":param_page"
                      :en ":param_page")
                     (:тип "REAL"
                      :имя "dx"
                      :ru "Расстояние переноса координатной системы по горизонтали."
                      :en "Coordinate system horizontal translate distance.")
                     (:тип "REAL"
                      :имя "dy"
                      :ru "Расстояние переноса координатной системы по вертикали."
                      :en "Coordinate system vertical translate distance.")))

        ;; BRST_Page_Scale
        (:название "Page_Scale"
         :группа "graphics"
         :ошибки ()
	 :результат (:тип "STATUS"
		     :ru ":return_ok"
		     :en ":return_ok")
         :ru "Конкатенация матрицы масштабирования и матрицы преобразования страницы.

  Масштаб системы координат изменяется так, что одна единица по горизонтали равна \\c sx единицам
  и одна единица по вертикали равна \\c sy единицам в новой системе координат."
         :en "Concatenate the page's transformation matrix with scale matrix.

  The coordinate system is scaled such that 1 unit horizontally equals \\с sx units
  and 1 unit vertically equals \\с sy units in the new coordinate system."

         :команда "cm"
         :см ("Page_Concat()")
         :параметры ((:тип "Page"
                      :имя "page"
                      :ru ":param_page"
                      :en ":param_page")
                     (:тип "REAL"
                      :имя "sx"
                      :ru "Значение масштаба по горизонтали."
                      :en "Horizontal scale value.")
                     (:тип "REAL"
                      :имя "sy"
                      :ru "Значение масштаба по вертикали."
                      :en "Vertical scale value.")))

        ;; BRST_Page_RotateDeg
        (:название "Page_RotateDeg"
         :группа "graphics"
         :ошибки ()
	 :результат (:тип "STATUS"
		     :ru ":return_ok"
		     :en ":return_ok")
         :ru "Конкатенация матрицы поворота и матрицы преобразования страницы.

  Оси системы координат поворачиваются против часовой стрелки на угол \\c degrees градусов."
         :en "Concatenate the page's transformation matrix with rotate matrix.

  The coordinate system axes are rotated counterclockwise by angle \\с degrees (in degrees)."
         :команда "cm"
         :см ("Page_Concat()"
              "Page_Rotate()")
         :параметры ((:тип "Page"
                      :имя "page"
                      :ru ":param_page"
                      :en ":param_page")
                     (:тип "REAL"
                      :имя "degrees"
                      :ru "Угол поворота системы координат (градусы)."
                      :en "Coordinate system rotate angle (degrees).")))

        ;; BRST_Page_Rotate
        (:название "Page_Rotate"
         :группа "graphics"
         :ошибки ()
	 :результат (:тип "STATUS"
		     :ru ":return_ok"
		     :en ":return_ok")
         :ru "Конкатенация матрицы поворота и матрицы преобразования страницы.

  Оси системы координат поворачиваются против часовой стрелки на угол \\c degrees радиан."
         :en "Concatenate the page's transformation matrix with rotate matrix.

  The coordinate system axes are rotated counterclockwise by angle \\с degrees (in radians)."
         :команда "cm"
         :см ("Page_Concat()"
              "Page_RotateDeg()")
         :параметры ((:тип "Page"
                      :имя "page"
                      :ru ":param_page"
                      :en ":param_page")
                     (:тип "REAL"
                      :имя "radians"
                      :ru "Угол поворота системы координат (радианы)."
                      :en "Coordinate system rotate angle (radians).")))

        ;; BRST_Page_Skew
        (:название "Page_Skew"
         :группа "graphics"
         :ошибки ()
	 :результат (:тип "STATUS"
		     :ru ":return_ok"
		     :en ":return_ok")
         :ru "Конкатенация матрицы наклона и матрицы преобразования страницы.

  Система координат наклоняется на угол \\c a по оси \\a x и на угол \\c b по оси \\a y."
         :en "Concatenate the page's transformation matrix with skew matrix.

  Coordinate system is skewed by an angle \\c a at \\a x axis and by angle \\c b at \\a y axis."
         :команда "cm"
         :см ("Page_Concat()")
         :параметры ((:тип "Page"
                      :имя "page"
                      :ru ":param_page"
                      :en ":param_page")
                     (:тип "REAL"
                      :имя "a"
                      :ru "Угол наклона по оси \\c x."
                      :en "\\c x axis skew value.")
                     (:тип "REAL"
                      :имя "b"
                      :ru "Угол наклона по оси \\c у."
                      :en "\\c y axis skew value.")))

        ;; BRST_Page_Circle
        (:название "Page_Circle"
         :группа "graphics"
         :ошибки ()
	 :результат (:тип "STATUS"
		     :ru ":return_ok"
		     :en ":return_ok")
         :ru "Добавление окружности к пути."
         :en "Append circle to current path."
         :параметры ((:тип "Page"
                      :имя "page"
                      :ru ":param_page"
                      :en ":param_page")
                     (:тип "REAL"
                      :имя "x"
                      :ru "Координата \\c x центра окружности."
                      :en "Circle center \\c x coordinate.")
                     (:тип "REAL"
                      :имя "y"
                      :ru "Координата \\c y центра окружности."
                      :en "Circle center \\c y coordinate.")
                     (:тип "REAL"
                      :имя "radius"
                      :ru "Радиус окружности."
                      :en "Circle radius.")))

        ;; BRST_Page_Ellipse
        (:название "Page_Ellipse"
         :группа "graphics"
         :ошибки ()
	 :результат (:тип "STATUS"
		     :ru ":return_ok"
		     :en ":return_ok")
         :ru "Добавление эллипса к пути."
         :en "Append ellipse to current path."
         :параметры ((:тип "Page"
                      :имя "page"
                      :ru ":param_page"
                      :en ":param_page")
                     (:тип "REAL"
                      :имя "x"
                      :ru "Координата \\c x центра эллипса."
                      :en "Ellipse center \\c y coordinate.")
                     (:тип "REAL"
                      :имя "y"
                      :ru "Координата \\c y центра эллипса."
                      :en "Ellipse center \\c y coordinate.")
                     (:тип "REAL"
                      :имя "a"
                      :ru "Горизонтальная полуось эллипса."
                      :en "The horizontal semi-axis of the ellipse.")
                     (:тип "REAL"
                      :имя "b"
                      :ru "Вертикальная полуось эллипса."
                      :en "The vertical semi-axis of the ellipse.")))

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
         :en "Append circle arc to current path.

  Angles are measured in degrees, with 0 degree corresponding to the vertical direction pointing upwards from the reference point `(x, y)`."
         :параметры ((:тип "Page"
                      :имя "page"
                      :ru ":param_page"
                      :en ":param_page")
                     (:тип "REAL"
                      :имя "x"
                      :ru "Координата \\c x центра окружности дуги."
                      :en "Arc circle center \\c x coordinate.")
                     (:тип "REAL"
                      :имя "y"
                      :ru "Координата \\c у центра окружности дуги."
                      :en "Arc circle center \\c y coordinate.")
                     (:тип "REAL"
                      :имя "radius"
                      :ru "Радиус окружности дуги."
                      :en "Arc circle radius.")
                     (:тип "REAL"
                      :имя "angle1"
                      :ru "Начальный угол дуги (градусы)."
                      :en "Initial angle of the arc (degrees).")
                     (:тип "REAL"
                      :имя "angle2"
                      :ru "Конечный угол дуги (градусы). Должен быть больше начального угла."
                      :en "Final angle of the arc (degrees). Must exceed the initial angle.")))

        ;; BRST_Page_SetGrayFill
        (:название "Page_SetGrayFill"
         :группа "graphics"
         :ошибки ()
	 :результат (:тип "STATUS"
		     :ru ":return_ok"
		     :en ":return_ok")
         :ru "Установка цвета заливки (тона серого)."
         :en "Set fill color (gray)."
         :команда "g"
         :параметры ((:тип "Page"
                      :имя "page"
                      :ru ":param_page"
                      :en ":param_page")
                     (:тип "REAL"
                      :имя "value"
                      :ru "Уровень серого цвета от \\c 0.0 до \\c 1.0."
                      :en "Gray level between \\c 0.0 and \\c 1.0.")))

        ;; BRST_Page_SetGrayStroke
        (:название "Page_SetGrayStroke"
         :группа "graphics"
         :ошибки ()
	 :результат (:тип "STATUS"
		     :ru ":return_ok"
		     :en ":return_ok")
         :ru "Установка цвета линии (тона серого)."
         :en "Set stroke color (gray)."
         :команда "G"
         :параметры ((:тип "Page"
                      :имя "page"
                      :ru ":param_page"
                      :en ":param_page")
                     (:тип "REAL"
                      :имя "value"
                      :ru "Уровень серого цвета от \\c 0.0 до \\c 1.0."
                      :en "Gray level between \\c 0.0 and \\c 1.0.")))

        ;; BRST_Page_SetRGBFill
        (:название "Page_SetRGBFill"
         :группа "graphics"
         :ошибки ()
	 :результат (:тип "STATUS"
		     :ru ":return_ok"
		     :en ":return_ok")
         :ru "Установка цвета заливки (RGB)."
         :en "Set fill color (RGB)."
         :команда "rg"
         :параметры ((:тип "Page"
                      :имя "page"
                      :ru ":param_page"
                      :en ":param_page")
                     (:тип "REAL"
                      :имя "r"
                      :ru "Уровень красного цвета от \\c 0.0 до \\c 1.0."
                      :en "Red level between \\c 0.0 and \\c 1.0.")
                     (:тип "REAL"
                      :имя "g"
                      :ru "Уровень зеленого цвета от \\c 0.0 до \\c 1.0."
                      :en "Green level between \\c 0.0 and \\c 1.0.")
                     (:тип "REAL"
                      :имя "b"
                      :ru "Уровень синего цвета от \\c 0.0 до \\c 1.0."
                      :en "Blue level between \\c 0.0 and \\c 1.0.")))

        ;; BRST_Page_SetRGBFillUint
        (:название "Page_SetRGBFillUint"
         :группа "graphics"
         :ошибки ()
	 :результат (:тип "STATUS"
		     :ru ":return_ok"
		     :en ":return_ok")
         :ru "Установка цвета заливки (RGB) с использованием значений типа \\ref BRST_UINT8."
         :en "Set fill color (RGB) using \\ref BRST_UINT8 values."
         :команда "rg"
         :параметры ((:тип "Page"
                      :имя "page"
                      :ru ":param_page"
                      :en ":param_page")
                     (:тип "UINT8"
                      :имя "r"
                      :ru "Уровень красного цвета от \\c 0 до \\c 255."
                      :en "Red level between \\c 0 and \\c 255.")
                     (:тип "UINT8"
                      :имя "g"
                      :ru "Уровень зеленого цвета от \\c 0 до \\c 255."
                      :en "Green level between \\c 0 and \\c 255.")
                     (:тип "UINT8"
                      :имя "b"
                      :ru "Уровень синего цвета от \\c 0 до \\c 255."
                      :en "Blue level between \\c 0 and \\c 255.")))

        ;; BRST_Page_SetRGBFillHex
        (:название "Page_SetRGBFillHex"
         :группа "graphics"
         :ошибки ()
	 :результат (:тип "STATUS"
		     :ru ":return_ok"
		     :en ":return_ok")
         :ru "Установка цвета заливки (RGB) с использованием значения типа \\ref BRST_UINT32."
         :en "Set fill color (RGB) using \\ref BRST_UINT32 value."
         :команда "rg"
         :параметры ((:тип "Page"
                      :имя "page"
                      :ru ":param_page"
                      :en ":param_page")
                     (:тип "UINT32"
                      :имя "rgb"
                      :ru "Значения цветов RGB задаются в трех байтах 32-битного беззнакового числа.
  Синий задается битами 0-7, зеленый битами 8-15, красный битами 16-23.
  Это соответствует битовым маскам \\c 0xFF, \\c 0xFF00 и \\c 0xFF0000 соответственно."
                      :en "RGB color values are represented in three bytes of a 32-bit unsigned integer.
  Blue is defined by bits 0–7, green by bits 8–15, red by bits 16–23.
  This corresponds to bit masks 0xFF, 0xFF00, and 0xFF0000, respectively.")))

        ;; BRST_Page_SetRGBStroke
        (:название "Page_SetRGBStroke"
         :группа "graphics"
         :ошибки ()
	 :результат (:тип "STATUS"
		     :ru ":return_ok"
		     :en ":return_ok")
         :ru "Установка цвета линии (RGB)."
         :en "Set stroke color (RGB)."
         :команда "RG"
         :параметры ((:тип "Page"
                      :имя "page"
                      :ru ":param_page"
                      :en ":param_page")
                     (:тип "REAL"
                      :имя "r"
                      :ru "Уровень красного цвета от \\c 0.0 до \\c 1.0."
                      :en "Red level between \\c 0.0 and \\c 1.0.")
                     (:тип "REAL"
                      :имя "g"
                      :ru "Уровень зеленого цвета от \\c 0.0 до \\c 1.0."
                      :en "Green level between \\c 0.0 and \\c 1.0.")
                     (:тип "REAL"
                      :имя "b"
                      :ru "Уровень синего цвета от \\c 0.0 до \\c 1.0."
                      :en "Blue level between \\c 0.0 and \\c 1.0.")))

        ;; BRST_Page_SetRGBStrokeUint
        (:название "Page_SetRGBStrokeUint"
         :группа "graphics"
         :ошибки ()
	 :результат (:тип "STATUS"
		     :ru ":return_ok"
		     :en ":return_ok")
         :ru "Установка цвета линии (RGB) с использованием значений типа \\ref BRST_UINT8."
         :en "Set stroke color (RGB) using \\ref BRST_UINT8 values."
         :команда "RG"
         :параметры ((:тип "Page"
                      :имя "page"
                      :ru ":param_page"
                      :en ":param_page")
                   (:тип "UINT8"
                    :имя "r"
                     :ru "Уровень красного цвета от \\c 0 до \\c 255."
                     :en "Red level between \\c 0 and \\c 255.")
                   (:тип "UINT8"
                    :имя "g"
                    :ru "Уровень зеленого цвета от \\c 0 до \\c 255."
                    :en "Green level between \\c 0 and \\c 255.")
                   (:тип "UINT8"
                    :имя "b"
                    :ru "Уровень синего цвета от \\c 0 до \\c 255."
                    :en "Blue level between \\c 0 and \\c 255.")))

       ;; BRST_Page_SetRGBStrokeHex
       (:название "Page_SetRGBStrokeHex"
        :группа "graphics"
        :ошибки ()
	:результат (:тип "STATUS"
		    :ru ":return_ok"
		    :en ":return_ok")
        :ru "Установка цвета линии (RGB) с использованием значения типа \\ref BRST_UINT32."
        :en "Set stroke color (RGB) using \\ref BRST_UINT32 value."
        :команда "rg"
        :параметры ((:тип "Page"
                     :имя "page"
                     :ru ":param_page"
                     :en ":param_page")
                    (:тип "UINT32"
                     :имя "rgb"
                     :ru "Значения цветов RGB задаются в трех байтах 32-битного беззнакового числа.
  Синий задается битами 0-7, зеленый битами 8-15, красный битами 16-23.
  Это соответствует битовым маскам \\c 0xFF, \\c 0xFF00 и \\c 0xFF0000 соответственно."
                     :en "RGB color values are represented in three bytes of a 32-bit unsigned integer.
  Blue is defined by bits 0–7, green by bits 8–15, red by bits 16–23.
  This corresponds to bit masks 0xFF, 0xFF00, and 0xFF0000, respectively.")))

       ;; BRST_Page_SetCMYKFill
       (:название "Page_SetCMYKFill"
        :группа "graphics"
        :ошибки ()
	:результат (:тип "STATUS"
		    :ru ":return_ok"
		    :en ":return_ok")
        :ru "Установка цвета заливки (CMYK)."
        :en "Set fill color (CMYK)."
        :команда "k"
        :параметры ((:тип "Page"
                     :имя "page"
                     :ru ":param_page"
                     :en ":param_page")
                    (:тип "REAL"
                     :имя "c"
                     :ru "Уровень синего (cyan) цвета от \\c 0.0 до \\c 1.0."
                     :en "Cyan level between \\c 0.0 and \\c 1.0.")
                    (:тип "REAL"
                     :имя "m"
                     :ru "Уровень пурпурного (magenta) цвета от \\c 0.0 до \\c 1.0."
                     :en "Magenta level between \\c 0.0 and \\c 1.0.")
                    (:тип "REAL"
                     :имя "y"
                     :ru "Уровень желтого (yellow) цвета от \\c 0.0 до \\c 1.0."
                     :en "Yellow level between \\c 0.0 and \\c 1.0.")
                    (:тип "REAL"
                     :имя "k"
                     :ru "Уровень черного (blacK) цвета от \\c 0.0 до \\c 1.0."
                     :en "BlacK level between \\c 0.0 and \\c 1.0.")))

       ;; BRST_Page_SetCMYKStroke
       (:название "Page_SetCMYKStroke"
        :группа "graphics"
        :ошибки ()
	:результат (:тип "STATUS"
		    :ru ":return_ok"
		    :en ":return_ok")
        :ru "Установка цвета линии (CMYK)."
        :en "Set stroke color (CMYK)."
        :команда "K"
        :параметры ((:тип "Page"
                     :имя "page"
                     :ru ":param_page"
                     :en ":param_page")
                    (:тип "REAL"
                     :имя "c"
                     :ru "Уровень синего (cyan) цвета от \\c 0.0 до \\c 1.0."
                     :en "Cyan level between \\c 0.0 and \\c 1.0.")
                    (:тип "REAL"
                     :имя "m"
                     :ru "Уровень пурпурного (magenta) цвета от \\c 0.0 до \\c 1.0."
                     :en "Magenta level between \\c 0.0 and \\c 1.0.")
                    (:тип "REAL"
                     :имя "y"
                     :ru "Уровень желтого (yellow) цвета от \\c 0.0 до \\c 1.0."
                     :en "Yellow level between \\c 0.0 and \\c 1.0.")
                    (:тип "REAL"
                     :имя "k"
                     :ru "Уровень черного (blacK) цвета от \\c 0.0 до \\c 1.0."
                     :en "BlacK level between \\c 0.0 and \\c 1.0.")))

       ;; BRST_Page_Clip
       (:название "Page_Clip"
        :группа "graphics"
        :ошибки ()
	:результат (:тип "STATUS"
		    :ru ":return_ok"
		    :en ":return_ok")
        :ru "Изменение текущей область отсечения, пересечение её с текущим путём, что определяет внутренние регионы
  области отсечения с применением правила ненулевого счёта обхода (nonzero winding number rule).

  Область отсечения изменяется только после следующего оператора рисования.Чтобы избежать рисования текущего пути, используйте функцию BRST_Page_EndPath().

  Все последующие операции рисования будут влиять только на области страницы, входящие в пределы области отсечения.
  Первоначально область отсечения включает всю страницу.
  Увеличить или заменить новой областью отсечения Текущую область отсечения нельзя.
  Функции BRST_Page_GSave() и BRST_Page_GRestore() позволяют сохранять и восстанавливать
  текущее графическое состояние, включая область отсечения."

        :en "Modifies the current clipping path by intersecting it with the current path, using
  the nonzero winding number rule to determine which regions lie inside the clipping path.

  The clipping path is only modified after the succeeding painting operator.
  To avoid painting the current path, use the function BRST_Page_EndPath().

  Following painting operations will only affect the regions of the page contained by the clipping path.
  Initially, the clipping path includes the entire page. There is no way to enlarge the current clipping path
  or to replace the clipping path with a new one. The functions BRST_Page_GSave() and BRST_Page_GRestore()
  may be used to save and restore the current graphics state, including the clipping path."
        :команда "W"
        :см (
             "Page_EndPath()"
             "Page_GSave()"
             "Page_GRestore()"
             "Page_Eoclip()"
             )
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
        :ru "Изменение текущей область отсечения, пересечение её с текущим путём, что определяет внутренние регионы
  области отсечения с применением правила чётный-нечётный (even-odd rule).

    Область отсечения изменяется только после следующего оператора рисования.Чтобы избежать рисования текущего пути, используйте функцию BRST_Page_EndPath().

  Все последующие операции рисования будут влиять только на области страницы, входящие в пределы области отсечения.
  Первоначально область отсечения включает всю страницу.
  Увеличить или заменить новой областью отсечения Текущую область отсечения нельзя.
  Функции BRST_Page_GSave() и BRST_Page_GRestore() позволяют сохранять и восстанавливать
  текущее графическое состояние, включая область отсечения."

        :en "Modifies the current clipping path by intersecting it with current path using the even-odd rule.

  The clipping path is only modified after the succeeding painting operator.
  To avoid painting the current path, use the function BRST_Page_EndPath().

  Following painting operations will only affect the regions of the page contained by the clipping path.
  Initially, the clipping path includes the entire page. There is no way to enlarge the current clipping path
  or to replace the clipping path with a new one. The functions BRST_Page_GSave() and BRST_Page_GRestore()
  may be used to save and restore the current graphics state, including the clipping path."
        :команда "W*"
        :см (
             "Page_EndPath()"
             "Page_GSave()"
             "Page_GRestore()"
             "Page_Clip()"
             )
        :параметры ((:тип "Page"
                     :имя "page"
                     :ru ":param_page"
                     :en ":param_page")))

       ;; BRST_Page_Stroke
       (:название "Page_Stroke"
        :группа "graphics"
        :ошибки ()
        :результат (:тип "STATUS"
		    :ru ":return_ok"
		    :en ":return_ok")
        :ru "Отображение текущего пути."
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
        :ru "Закрытие и отображение текущего пути."
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
        :ru "Заполнение текущего пути с применением правила ненулевого счёта обхода."
        :en "Fill current path using nonzero winding number rule."
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
        :ru "Заполнение текущего пути с применением правила чётный-нечётный."
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
        :ru "Заполнение текущего пути с применением правила ненулевого счёта обхода с последующим отображением пути."
        :en "Fill current path using the nonzero winding number rule and then paint the path."
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
        :ru "Заполнение текущего пути с применением правила чётный-нечётный с последующим отображением пути."
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
        :ru "Закрытие пути, заполнение текущего пути с применением правила ненулевого счёта обхода с последующим отображением пути."
        :en "Close current path, fill current path using the nonzero winding number rule, then paint path."
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
        :ru "Закрытие пути, заполнение текущего пути с применением правила чётный-нечётный с последующим отображением пути."
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
        :ru "Окончание пути без заполнения и отображения."
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
        :ru "Начало нового подпути с переносом текущей точки отображения путей."
        :en "Start new subpath and move current point for drawing path."
        :команда "m"
        :параметры ((:тип "Page"
                     :имя "page"
                     :ru ":param_page"
                     :en ":param_page")
                    (:тип "REAL"
                     :имя "x"
                     :ru "Координата \\c x начальной точки отображения пути."
                     :en "Starting point \\c x coordinate for drawing path.")
                    (:тип "REAL"
                     :имя "y"
                     :ru "Координата \\c y начальной точки отображения пути."
                     :en "Starting point \\c y coordinate for drawing path.")))

       ;; BRST_Page_LineTo
       (:название "Page_LineTo"
        :группа "graphics"
        :ошибки ()
	:результат (:тип "STATUS"
		    :ru ":return_ok"
		    :en ":return_ok")
        :ru "Добавление отрезка прямой из текущей точки в точку с координатами `(x, y)` как подпуть текущего пути.
        Точка `(x, y)` становится текущей для отображения путей."
        :en "Append a straight line segment from the current point to the point `(x, y)`. The new current point shall be `(x, y)`."
        :команда "l"
        :параметры ((:тип "Page"
                     :имя "page"
                     :ru ":param_page"
                     :en ":param_page")
                    (:тип "REAL"
                     :имя "x"
                     :ru "Координата \\c x целевой (конечной) точки добавляемого отрезка."
                     :en "End point \\c x coordinate for line segment.")
                    (:тип "REAL"
                     :имя "y"
                     :ru "Координата \\c y целевой (конечной) точки добавляемого отрезка."
                     :en "End point \\c y coordinate for line segment.")))

       ;; BRST_Page_CurveTo
       (:название "Page_CurveTo"
        :группа "graphics"
        :ошибки ()
	:результат (:тип "STATUS"
		    :ru ":return_ok"
		    :en ":return_ok")
        :ru "Добавление кубической кривой Безье с использованием контрольных точек (x<sub>1</sub>, y<sub>1</sub>), (x<sub>2</sub>, y<sub>2</sub>)
  и (x<sub>3</sub>, y<sub>3</sub>). Точка (x<sub>3</sub>, y<sub>3</sub>) становится текущей для отображения путей.

  \\image html img/curveto.png."

        :en "Append a cubic Bézier curve to the current path using control points
  (x<sub>1</sub>, y<sub>1</sub>) and (x<sub>2</sub>, y<sub>2</sub>)
  and (x<sub>3</sub>, y<sub>3</sub>), then set current point
  to (x<sub>3</sub>, y<sub>3</sub>).

  \\image html img/curveto.png."
        :команда "c"
        :параметры ((:тип "Page"
                     :имя "page"
                     :ru ":param_page"
                     :en ":param_page")
                    (:тип "REAL"
                     :имя "x1"
                     :ru "Координата \\c x первой контрольной точки кубической кривой Безье."
                     :en "First cubic Bézier curve control point \\c x coordinate.")
                    (:тип "REAL"
                     :имя "y1"
                     :ru "Координата \\c y первой контрольной точки кубической кривой Безье."
                     :en "First cubic Bézier curve control point \\c y coordinate.")
                    (:тип "REAL"
                     :имя "x2"
                     :ru "Координата \\c x второй контрольной точки кубической кривой Безье."
                     :en "Second cubic Bézier curve control point \\c x coordinate.")
                    (:тип "REAL"
                     :имя "y2"
                     :ru "Координата \\c y второй контрольной точки кубической кривой Безье."
                     :en "Second cubic Bézier curve control point \\c y coordinate.")
                    (:тип "REAL"
                     :имя "x3"
                     :ru "Координата \\c x третьей контрольной точки кубической кривой Безье."
                     :en "Third cubic Bézier curve control point \\c x coordinate.")
                    (:тип "REAL"
                     :имя "y3"
                     :ru "Координата \\c y третьей контрольной точки кубической кривой Безье."
                     :en "Third cubic Bézier curve control point \\c y coordinate.")))

       ;; BRST_Page_CurveTo2
       (:название "Page_CurveTo2"
        :группа "graphics"
        :ошибки ()
	:результат (:тип "STATUS"
		    :ru ":return_ok"
		    :en ":return_ok")
        :ru "Добавление кубической кривой Безье с использованием контрольных точек (x<sub>2</sub>, y<sub>2</sub>)
  и (x<sub>3</sub>, y<sub>3</sub>). Точка (x<sub>3</sub>, y<sub>3</sub>) становится текущей для отображения путей.
  \\image html img/curveto2.png"

        :en "Append Bézier curve to current path using current point and (x<sub>2</sub>, y<sub>2</sub>)
  and (x<sub>3</sub>, y<sub>3</sub>) as control points. Then current point is set to (x<sub>3</sub>, y<sub>3</sub>).

  \\image html img/curveto2.png"
        :команда "v"
        :параметры ((:тип "Page"
                     :имя "page"
                     :ru ":param_page"
                     :en ":param_page")
                    (:тип "REAL"
                     :имя "x2"
                     :ru "Координата \\c x второй контрольной точки кубической кривой Безье."
                     :en "Second cubic Bézier curve control point \\c x coordinate.")
                    (:тип "REAL"
                     :имя "y2"
                     :ru "Координата \\c y второй контрольной точки кубической кривой Безье."
                     :en "Second cubic Bézier curve control point \\c y coordinate.")
                    (:тип "REAL"
                     :имя "x3"
                     :ru "Координата \\c x третьей контрольной точки кубической кривой Безье."
                     :en "Third cubic Bézier curve control point \\c x coordinate.")
                    (:тип "REAL"
                     :имя "y3"
                     :ru "Координата \\c y третьей контрольной точки кубической кривой Безье."
                     :en "Third cubic Bézier curve control point \\c y coordinate.")))

       ;; BRST_Page_CurveTo3
       (:название "Page_CurveTo3"
        :группа "graphics"
        :ошибки ()
	:результат (:тип "STATUS"
		    :ru ":return_ok"
		    :en ":return_ok")
        :ru "Добавление кубической кривой Безье с использованием контрольных точек (x<sub>1</sub>, y<sub>1</sub>)
  и (x<sub>3</sub>, y<sub>3</sub>). Точка (x<sub>3</sub>, y<sub>3</sub>) становится текущей для отображения путей.

  \\image html img/curveto3.png."

        :en "Append a cubic Bézier curve to the current path using control points
  (x<sub>1</sub>, y<sub>1</sub>) and (x<sub>3</sub>, y<sub>3</sub>), then set current point
  to (x<sub>3</sub>, y<sub>3</sub>).

  \\image html img/curveto3.png."
        :команда "y"
        :параметры ((:тип "Page"
                     :имя "page"
                     :ru ":param_page"
                     :en ":param_page")
                    (:тип "REAL"
                     :имя "x1"
                     :ru "Координата \\c x первой контрольной точки кубической кривой Безье."
                     :en "First cubic Bézier curve control point \\c x coordinate.")
                    (:тип "REAL"
                     :имя "y1"
                     :ru "Координата \\c y первой контрольной точки кубической кривой Безье."
                     :en "First cubic Bézier curve control point \\c y coordinate.")
                    (:тип "REAL"
                     :имя "x3"
                     :ru "Координата \\c x третьей контрольной точки кубической кривой Безье."
                     :en "Third cubic Bézier curve control point \\c x coordinate.")
                    (:тип "REAL"
                     :имя "y3"
                     :ru "Координата \\c y третьей контрольной точки кубической кривой Безье."
                     :en "Third cubic Bézier curve control point \\c y coordinate.")))

       ;; BRST_Page_ClosePath
       (:название "Page_ClosePath"
        :группа "graphics"
        :ошибки ()
	:результат (:тип "STATUS"
		    :ru ":return_ok"
		    :en ":return_ok")
        :ru "Закрытие текущего подпути добавлением отрезка из текущей точки в начальную точку подпути."
        :en "Close the current subpath by appending a straight line segment from the current point to the starting point of the subpath."
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
        :ru "Добавление прямоугольника к текущему пути в качестве самостоятельного подпути.
  У прямоугольника левый нижний угол расположен в точке `(x, y)` и измерениями \\c width и \\c height."

        :en "Append a rectangle to the current path as a complete
subpath, with lower-left corner `(x, y)` and dimensions \\c width
and \\c height in user space."
        :команда "re"
        :параметры ((:тип "Page"
                     :имя "page"
                     :ru ":param_page"
                     :en ":param_page")
                    (:тип "REAL"
                     :имя "x"
                     :ru "Координата \\c x левого нижнего угла прямоугольника."
                     :en "Rectangle low-left corner \\c x coordinate.")
                    (:тип "REAL"
                     :имя "y"
                     :ru "Координата \\c y левого нижнего угла прямоугольника."
                     :en "Rectangle low-left corner \\c y coordinate.")
                    (:тип "REAL"
                     :имя "width"
                     :ru "Ширина прямоугольника."
                     :en "Rectangle width")
                    (:тип "REAL"
                     :имя "height"
                     :ru "Высота прямоугольника."
                     :en "Rectangle height")))

       ;; BRST_Page_SetLineWidth
       (:название "Page_SetLineWidth"
        :группа "graphics"
        :ошибки ()
	:результат (:тип "STATUS"
		    :ru ":return_ok"
		    :en ":return_ok")
        :ru "Установка толщины линии для отображения путей."
        :en "Set width of the line used to stroke paths."
        :команда "w"
        :параметры ((:тип "Page"
                     :имя "page"
                     :ru ":param_page"
                     :en ":param_page")
                    (:тип "REAL"
                     :имя "line_width"
                     :ru "Толщина линии для отображения путей. По умолчанию равна \\c 1.0."
                     :en "Line width. Default \\c line_width is \\c 1.0")))


       ;; BRST_Page_SetLineCap
       (:название "Page_SetLineCap"
        :группа "graphics"
        :ошибки ()
	:результат (:тип "STATUS"
		    :ru ":return_ok"
		    :en ":return_ok")
        :ru "Установка стиля окончания линии."
        :en "Set lines endpoints shape style."
        :команда "J"
        :параметры ((:тип "Page"
                     :имя "page"
                     :ru ":param_page"
                     :en ":param_page")
                    (:тип "LineCap"
                     :имя "line_cap"
                     :ru "Стиль окончания линии (одно из значений):

  | Значение                         | Изображение               | Описание                                                                  |
  | --------                         | -----------               | --------                                                                  |
  | \\ref BRST_BUTT_END               | \\image html linecap1.png  | Линия заканчивается прямоугольником в конечной точке.                     |
  | \\ref BRST_ROUND_END              | \\image html linecap2.png  | Линия заканчивается полуокружностью с центром в конечной точке.           |
  | \\ref BRST_PROJECTING_SQUARE_END  | \\image html linecap3.png  | Линия продолжается, выступая за конечную точку на половину толщины линии. |

  По умолчанию стиль окончания линии \\c line_cap равен \\ref BRST_BUTT_END"
                     :en "The line cap style (one of the following).

  | Value                            | Image                     | Description                                                             |
  | -----                            | -----                     | -----------                                                             |
  | \\ref BRST_BUTT_END               | \\image html linecap1.png  | Line is squared off at path endpoint.                                   |
  | \\ref BRST_ROUND_END              | \\image html linecap2.png  | End of line becomes a semicircle with center  at path endpoint.         |
  | \\ref BRST_PROJECTING_SQUARE_END  | \\image html linecap3.png  | Line continues beyond endpoint, goes on half the endpoint stroke width. |

  Default \\c line_cap is \\ref BRST_BUTT_END.
")))

       ;; BRST_Page_SetLineJoin
       (:название "Page_SetLineJoin"
        :группа "graphics"
        :ошибки ()
	:результат (:тип "STATUS"
		    :ru ":return_ok"
		    :en ":return_ok")
        :ru "Установка стиля стыка линий."
        :en "Set line join shape style."
        :команда "j"
        :параметры ((:тип "Page"
                     :имя "page"
                     :ru ":param_page"
                     :en ":param_page")
                    (:тип "LineJoin"
                     :имя "line_join"
                     :ru "Стиль стыка линий (одно из значений).

  | Значение              | Изображение                | Описание                                                                                             |
  | --------              | -----------                | --------                                                                                             |
  | \\ref BRST_MITER_JOIN  | \\image html linejoin1.png  | Внешние грани линии двух сегментов продлеваются, пока не встретятся под углом.                       |
  | \\ref BRST_ROUND_JOIN  | \\image html linejoin2.png  | Из точки пересечения двух сегментов проводится дуга окружности, диаметр которой равен толщине линии. |
  | \\ref BRST_BEVEL_JOIN  | \\image html linejoin3.png  | Оба сегмента заканчиваются прямоугольным окончанием, получившаяся выемка заполняется треугольником.  |

  По умолчанию стиль стыка линий \\c line_join равен \\ref BRST_MITER_JOIN."
                     :en "The line join style (one of the following).

  | Value                | Image                     | Description                                                                                                                      |
  | -----                | -----                     | -----------                                                                                                                      |
  | \\ref BRST_MITER_JOIN | \\image html linejoin1.png | Outer edges of the strokes for the two segments are extended until they meet at an angle.                                        |
  | \\ref BRST_ROUND_JOIN | \\image html linejoin2.png | An arc of a circle with a diameter equal to the line width is drawn around the point where the two segments meet.                |
  | \\ref BRST_BEVEL_JOIN | \\image html linejoin3.png | The two segments are finished with butt caps and the resulting notch beyond the ends of the segments are filled with a triangle. |

  Default \\c line_join is \\ref BRST_MITER_JOIN.")))

       ;; Page_SetMiterLimit
       (:название "Page_SetMiterLimit"
        :группа "graphics"
        :ошибки ()
	:результат (:тип "STATUS"
		    :ru ":return_ok"
		    :en ":return_ok")
        :ru "Установка предельного значения острого угла линии для пересечений.
  Предельное значение острого угла (miter limit) равное \\c 1.414, превращает острые углы соединения в скос при угле меньше \\c 90 градусов.
  Ограничение 2.0 делает это для углов меньше \\c 60 градусов, а ограничение 10.0 действует для углов менее \\c 11.5 градусов."

        :en "Set miter limit for line joins.

  A miter limit of 1.414 converts miters to bevels for \\c angle less than \\c 90 degrees,
  a limit of \\c 2.0 converts them for \\c angle less than 60 degrees, and a limit of 10.0
  converts them for angle less than approximately 11.5 degrees."
        :команда "M"
        :параметры ((:тип "Page"
                     :имя "page"
                     :ru ":param_page"
                     :en ":param_page")
                    (:тип "REAL"
                     :имя "miter_limit"
                     :ru "Предельное значение острого угла линии."
                     :en "Miter limit value.")))

       ;; BRST_Page_SetDash
       (:название "Page_SetDash"
        :группа "graphics"
        :ошибки ()
	:результат (:тип "STATUS"
		    :ru ":return_ok"
		    :en ":return_ok")
        :ru "Устанавливает шаблон пунктира линий.

  \\par Примеры

  `dash_ptn = NULL`, `num_elem = 0`, `phase = 0` (по умолчанию для новой страницы)

  \\image html setdash1.png

  `dash_ptn = [3]`, `num_elem = 1`, `phase = 1`

  \\image html setdash2.png

  `dash_ptn = [7,]`, `num_elem = 2`, `phase = 2`

  \\image html setdash3.png

  `dash_ptn = [8,]`, `num_elem = 4`, `phase = 0`

  \\image html setdash4.png"

        :en "Set dash pattern for lines in the page.

  \\par Examples

  `dash_ptn = NULL`, `num_elem = 0`, `phase = 0` (default for new page)

  \\image html setdash1.png

  `dash_ptn = [3]`, `num_elem = 1`, `phase = 1`

  \\image html setdash2.png

  `dash_ptn = [7,]`, `num_elem = 2`, `phase = 2`

  \\image html setdash3.png

  `dash_ptn = [8,]`, `num_elem = 4`, `phase = 0`

  \\image html setdash4.png"
        :команда "d"
        :параметры ((:тип "Page"
                     :имя "page"
                     :ru ":param_page"
                     :en ":param_page")
                    (:тип "DASH_PATTERN"
                     :имя "dash_pattern"
                     :ru ""
                     :en "Pattern of dashes and gaps used to stroke paths.")
                    (:тип "UINT"
                     :имя "num_elem"
                     :ru ""
                     :en "Number of elements in dash_pattern, `0 <= num_param <= 8`.")
                    (:тип "REAL"
                     :имя "phase"
                     :ru ""
                     :en "Phase in which pattern begins (default is \\c 0)")))

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

;;; TODO Заменить функции группами функций, возвращающей отдельные компоненты цвета
;;;       ;; BRST_Page_RGBFill
;;;       (:название "Page_RGBFill"
;;;        :группа "page"
;;;        :ошибки ()
;;;        :результат (:тип "RGBColor"
;;;                    :ru "Текущее значение цвета заливки (RGB) при успешном выполнении, в противном случае возвращается `BRST_RGBColor{0, 0, 0}`."
;;;                    :en "Page current fill color value (RGB) on success, otherwise it returns `BRST_RGBColor{0, 0, 0}`.")
;;;        :ru "Текущее значение цвета заливки (RGB).
;;;  BRST_Page_RGBFill() действительна только в случае использования цветового пространства \\ref BRST_CS_DEVICE_RGB."
;;;        :en "Get page current fill color value (RGB).
;;;  BRST_Page_RGBFill() is valid only when the page's fill color space is \\ref BRST_CS_DEVICE_RGB."
;;;        :параметры ((:тип "Page"
;;;                     :имя "page"
;;;                     :ru ":param_page"
;;;                     :en ":param_page")))

;;;       ;; BRST_Page_RGBStroke
;;;       (:название "Page_RGBStroke"
;;;        :группа "page"
;;;        :ошибки ()
;;;        :результат (:тип "RGBColor"
;;;                    :ru "Текущее значение цвета линии (RGB) при успешном выполнении, в противном случае возвращается `BRST_RGBColor{0, 0, 0}`."
;;;                    :en "Page current stroke color value (RGB) on success, otherwise it returns `BRST_RGBColor{0, 0, 0}`.")
;;;        :ru "Текущее значение цвета линии (RGB).
;;;  BRST_Page_RGBStroke() действительна только в случае использования цветового пространства \\ref BRST_CS_DEVICE_RGB."
;;;        :en "Get page current stroke color value (RGB).
;;;  BRST_Page_RGBStroke() is valid only when the page's stroke color space is \\ref BRST_CS_DEVICE_RGB."
;;;        :параметры ((:тип "Page"
;;;                     :имя "page"
;;;                     :ru ":param_page"
;;;                     :en ":param_page")))

;;;       ;; BRST_Page_CMYKFill
;;;       (:название "Page_CMYKFill"
;;;        :группа "page"
;;;        :ошибки ()
;;;        :результат (:тип "CMYKColor"
;;;                    :ru "Текущее значение цвета заливки (CMYK) при успешном выполнении, в противном случае возвращается `BRST_CMYKColor{0, 0, 0, 0}`."
;;;                    :en "Page current fill color value (CMYK) on success, otherwise it returns `BRST_CMYKColor{0, 0, 0, 0}`.")
;;;        :ru "Текущее значение цвета заливки (CMYK).
;;;  BRST_Page_CMYKFill() действительна только в случае использования цветового пространства \\ref BRST_CS_DEVICE_CMYK."
;;;        :en "Get page current fill color value (CMYK).
;;;  BRST_Page_CMYKFill() is valid only when the page's fill color space is \\ref BRST_CS_DEVICE_CMYK."
;;;        :параметры ((:тип "Page"
;;;                     :имя "page"
;;;                     :ru ":param_page"
;;;                     :en ":param_page")))

;;;       ;; BRST_Page_CMYKStroke
;;;       (:название "Page_CMYKStroke"
;;;        :группа "page"
;;;        :ошибки ()
;;;        :результат (:тип "CMYKColor"
;;;                    :ru "Текущее значение цвета линии (CMYK) при успешном выполнении, в противном случае возвращается `BRST_CMYKColor{0, 0, 0, 0}`."
;;;                    :en "Page current stroke color value (CMYK) on success, otherwise it returns `BRST_CMYKColor{0, 0, 0, 0}`.")
;;;        :ru "Текущее значение цвета линии (CMYK).
;;;  BRST_Page_CMYKFill() действительна только в случае использования цветового пространства \\ref BRST_CS_DEVICE_CMYK."
;;;        :en "Get page current stroke color value (CMYK).
;;;  BRST_Page_CMYKFill() is valid only when the page's stroke color space is \\ref BRST_CS_DEVICE_CMYK."
;;;        :параметры ((:тип "Page"
;;;                     :имя "page"
;;;                     :ru ":param_page"
;;;                     :en ":param_page")))

       ;; BRST_Page_GrayFill
       (:название "Page_GrayFill"
        :группа "page"
        :ошибки ()
        :результат (:тип "REAL"
                    :ru "Текущее значение цвета заливки (Gray) при успешном выполнении, в противном случае возвращается `0.0`."
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
                    :ru "Текущее значение цвета линии (Gray) при успешном выполнении, в противном случае возвращается `0.0`."
                    :en "Page current fill color value (Gray) on success, otherwise it returns `0.0`.")
        :ru "Текущее значение цвета линии (Gray).
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
                    :ru "Текущее значение цветового пространства линии при успешном выполнении, в противном случае возвращается \\ref BRST_CS_EOF."
                    :en "Page current stroke color space on success, otherwise it returns \\ref BRST_CS_EOF.")
        :ru "Текущее значение цветового пространства линии."
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
                    :ru "Текущее значение цветового пространства заливки при успешном выполнении, в противном случае возвращается \\ref BRST_CS_EOF."
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
                    :ru "Текущее значение стиля окончания линии для отображения путей, в противном случае возвращается \\ref BRST_DEF_LINECAP."
                    :en "Page current line cap for path painting on success, otherwise it returns \\ref BRST_DEF_LINECAP.")
        :ru "Стиль окончания линии."
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
                    :ru "Текущее значение стиля стыка линии для отображения путей при успешном выполнении, в противном случае возвращается \\ref BRST_DEF_LINEJOIN."
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
                    :ru "Текущее предельное значение острого угла линии для отображения путей при успешном выполнении, в противном случае возвращается \\ref BRST_DEF_MITERLIMIT."
                    :en "Page current line miter limit for path painting on success, otherwise it returns \\ref BRST_DEF_MITERLIMIT.")
        :ru "Текущее предельное значение острого угла (miter limit)."
        :en "Get page current miter limit."
        :параметры ((:тип "Page"
                     :имя "page"
                     :ru ":param_page"
                     :en ":param_page")))

;;;       ;; BRST_Page_Dash
;;;       (:название "Page_Dash"
;;;        :группа "page"
;;;        :ошибки ()
;;;        :результат (:тип "DashMode"
;;;                    :ru "Текущее значение шаблона пунктира \\ref BRST_DashMode для отображения линий при успешном выполнении,
;;;  в противном случае возвращается `BRST_DashMode{{0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f}, 0.0f, 0.0f}`."
;;;                    :en "Page current line dash pattern \\ref BRST_DashMode for path painting on success,
;;;  otherwise it returns `BRST_DashMode{{0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f}, 0.0f, 0.0f}`.")
;;;        :ru "Текущий шаблон пунктира (line dash pattern)."
;;;        :en "Get page current line dash pattern."
;;;        :параметры ((:тип "Page"
;;;                     :имя "page"
;;;                     :ru ":param_page"
;;;                     :en ":param_page")))

       ;; BRST_Page_Flat
       (:название "Page_Flat"
        :группа "page"
        :ошибки ()
        :результат (:тип "REAL"
                    :ru "Текущее значение точности аппроксимации (flatness) при успешном выполнении, в противном случае возвращается \\ref BRST_DEF_FLATNESS."
                    :en "Page current flatness value on success, otherwise it returns \\ref BRST_DEF_FLATNESS.")
        :ru "Текущее значение точности аппроксимации (flatness)."
        :en "Get page current flatness value."
        :параметры ((:тип "Page"
                     :имя "page"
                     :ru ":param_page"
                     :en ":param_page")))

       ;; BRST_Page_Matrix
       (:название "Page_Matrix"
        :группа "page"
        :ошибки ()
        :результат (:тип "Matrix"
                    :ru "Матрица преобразований \\ref BRST_Matrix при успешном выполнении, в противном случае возвращается `BRST_Matrix{1, 0, 0, 1, 0, 0}` (тождественная матрица преобразований)."
                    :en "Page current transformation matrix \\ref BRST_Matrix on success, otherwise it returns `BRST_Matrix{1, 0, 0, 1, 0, 0}` (identity transformation matrix).")
        :ru "Текущая матрица преобразований."
        :en "Get page current transformation matrix."
        :параметры ((:тип "Page"
                     :имя "page"
                     :ru ":param_page"
                     :en ":param_page")))
))

