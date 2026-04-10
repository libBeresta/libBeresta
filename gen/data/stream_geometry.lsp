(:file "stream_geometry"
 :functions
       (
        ;; BRST_Stream_GSave
        (:caption "Stream_GSave"
         :group "graphics"
         :errors ()
	 :result (:type "STATUS"
		     :ru ":return_ok"
		     :en ":return_ok")
         :ru "Сохранение в стек текущего графического состояния страницы.

Функция BRST_Stream_GSave() сохраняет графическое состояние и восстанавливает ранее сохранённое состояние с помощью функции BRST_Stream_GRestore().

Параметры состояния, сохраняемые функцией BRST_Stream_GSave(), включают:

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

  Application can call BRST_Stream_GSave() and can restore saved state by calling BRST_Stream_GRestore().

  Saved by BRST_Stream_GSave() state parameters are:

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
         :command "q"
         :params ((:type "Stream"
                      :name "page"
                      :ru ":param_stream"
                      :en ":param_stream")))

        ;; BRST_Stream_GRestore
        (:caption "Stream_GRestore"
         :group "graphics"
         :errors ()
	 :result (:type "STATUS"
		     :ru ":return_ok"
		     :en ":return_ok")
         :ru "Восстановление графического состояния страницы, ранее сохраненного функцией BRST_Stream_GSave()."
         :en "Restore graphics state which is saved by BRST_Stream_GSave()."
         :command "Q"
         :params ((:type "Stream"
                      :name "page"
                      :ru ":param_stream"
                      :en ":param_stream")))

        ;; BRST_Stream_Concat
        (:caption "Stream_Concat"
         :group "graphics"
         :errors ()
	 :result (:type "STATUS"
		     :ru ":return_ok"
		     :en ":return_ok")
         :ru "Конкатенация указанной матрицы и матрицы преобразования страницы.

  Например, если вам нужно повернуть систему координат страницы на 45 градусов, функцию BRST_Stream_Concat() следует вызвать так:

  \\code
  BRST_REAL rad = 45 / 180 * BRST_PI;
  BRST_Stream_Concat(page, cos(rad), sin(rad), -sin(rad), cos(rad), 0, 0);
  \\endcode

  С помощью следующей команды можно изменить разрешение системы системы координат на 300 точек на дюйм (dpi):

  \\code
  BRST_Stream_Concat(page, 72.0f / 300.0f, 0, 0, 72.0f / 300.0f, 0, 0);
  \\endcode

  Перед вызовом функции BRST_Stream_Concat() рекомендуется сохранить текущее графическое состояние
  с помощью функции BRST_Stream_GSave(). Затем внесённые изменения можно отменить,
  восстановив предыдущее графическое состояние с помощью функции BRST_Stream_GRestore().

  \\code
  // Сохраняем текущее состояние графики
  BRST_Stream_GSave(page);

  // Применяем матрицу преобразования
  BRST_Stream_Concat(page, 72.0f / 300.0f, 0, 0, 72.0f / 300.0f, 0, 0);

  // Показываем текст на с учетом изменения разрешения
  BRST_Stream_BeginText(page);
  BRST_Stream_MoveTextPos(page, 50, 100);
  BRST_Stream_ShowText(page, \"Текст на трансформированных координатах\");
  BRST_Stream_EndText(page);

  // Восстанавливаем предыдущее состояние графики
  BRST_Stream_GRestore(page);
  \\endcode

  Функцию BRST_Stream_GSave() можно вызывать, когда установлен режим \\ref BRST_GMODE_PAGE_DESCRIPTION."

		   :en "Concatenate the page's transformation matrix and specified matrix.

  For example, if you want to rotate the coordinate system of the page by 45 degrees, use BRST_Stream_Concat() as follows.

  \code
  BRST_REAL rad = 45 / 180 * BRST_PI;
  BRST_Stream_Concat(page, cos(rad), sin(rad), -sin(rad), cos(rad), 0, 0);
  \endcode

  To change the coordinate system of the page to 300 dpi, use BRST_Stream_Concat() as follows.

  \\code
  BRST_Stream_Concat(page, 72.0f / 300.0f, 0, 0, 72.0f / 300.0f, 0, 0);
  \\endcode

  Invoke BRST_Stream_GSave() before BRST_Stream_Concat(). Then the changes by BRST_Stream_Concat() can be restored by invoking BRST_Stream_GRestore().

  \\code
  // Save current graphics state
  BRST_Stream_GSave(page);

  //Concatenate transformation matrix
  BRST_Stream_Concat(page, 72.0f / 300.0f, 0, 0, 72.0f / 300.0f, 0, 0);

  // Show text on translated coordinates
  BRST_Stream_BeginText(page);
  BRST_Stream_MoveTextPos(page, 50, 100);
  BRST_Stream_ShowText(page, \"Text on the translated coordinates\");
  BRST_Stream_EndText(page);

  // Restore the graphics states
  BRST_Stream_GRestore (page);
  \\endcode

  Application can call BRST_Stream_GSave() when graphics mode is \\ref BRST_GMODE_PAGE_DESCRIPTION."

		   :command "cm"
		   :params ((:type "Stream"
				:name "page"
				:ru ":param_stream"
				:en ":param_stream")
			       (:type "REAL"
				:name "a"
				:ru "Параметр \\c a матрицы преобразования."
				:en "\\c a parameter of transformation matrix.")
			       (:type "REAL"
				:name "b"
				:ru "Параметр \\c b матрицы преобразования."
				:en "\\c b parameter of transformation matrix.")
			       (:type "REAL"
				:name "c"
				:ru "Параметр \\c c матрицы преобразования."
				:en "\\c c parameter of transformation matrix.")
			       (:type "REAL"
				:name "d"
				:ru "Параметр \\c d матрицы преобразования."
				:en "\\c d parameter of transformation matrix.")
			       (:type "REAL"
				:name "x"
				:ru "Параметр \\c x матрицы преобразования."
				:en "\\c x parameter of transformation matrix.")
			       (:type "REAL"
				:name "y"
				:ru "Параметр \\c y матрицы преобразования."
				:en "\\c y parameter of transformation matrix.")))

        ;; BRST_Stream_Translate
        (:caption "Stream_Translate"
         :group "graphics"
         :errors ()
	 :result (:type "STATUS"
		     :ru ":return_ok"
		     :en ":return_ok")
         :ru "Конкатенация матрицы переноса и матрицы преобразования страницы.

  Координатная система страницы переносится на \\c dx координатных единиц по горизонтали
  и \\c dy координатных единиц по вертикали."
         :en "Concatenate the page's transformation matrix with translation matrix.

  Coordinate system is translated by \\c dx and \\c dy coordinate units."
         :command "cm"
         :params ((:type "Stream"
                      :name "page"
                      :ru ":param_stream"
                      :en ":param_stream")
                     (:type "REAL"
                      :name "dx"
                      :ru "Расстояние переноса координатной системы по горизонтали."
                      :en "Coordinate system horizontal translate distance.")
                     (:type "REAL"
                      :name "dy"
                      :ru "Расстояние переноса координатной системы по вертикали."
                      :en "Coordinate system vertical translate distance.")))

        ;; BRST_Stream_Scale
        (:caption "Stream_Scale"
         :group "graphics"
         :errors ()
	 :result (:type "STATUS"
		     :ru ":return_ok"
		     :en ":return_ok")
         :ru "Конкатенация матрицы масштабирования и матрицы преобразования страницы.

  Масштаб системы координат изменяется так, что одна единица по горизонтали равна \\c sx единицам
  и одна единица по вертикали равна \\c sy единицам в новой системе координат."
         :en "Concatenate the page's transformation matrix with scale matrix.

  The coordinate system is scaled such that 1 unit horizontally equals \\с sx units
  and 1 unit vertically equals \\с sy units in the new coordinate system."

         :command "cm"
         :see ("Stream_Concat")
         :params ((:type "Stream"
                      :name "page"
                      :ru ":param_stream"
                      :en ":param_stream")
                     (:type "REAL"
                      :name "sx"
                      :ru "Значение масштаба по горизонтали."
                      :en "Horizontal scale value.")
                     (:type "REAL"
                      :name "sy"
                      :ru "Значение масштаба по вертикали."
                      :en "Vertical scale value.")))

        ;; BRST_Stream_RotateDeg
        (:caption "Stream_RotateDeg"
         :group "graphics"
         :errors ()
	 :result (:type "STATUS"
		     :ru ":return_ok"
		     :en ":return_ok")
         :ru "Конкатенация матрицы поворота и матрицы преобразования страницы.

  Оси системы координат поворачиваются против часовой стрелки на угол \\c degrees градусов."
         :en "Concatenate the page's transformation matrix with rotate matrix.

  The coordinate system axes are rotated counterclockwise by angle \\с degrees (in degrees)."
         :command "cm"
         :see ("Stream_Concat"
              "Stream_Rotate")
         :params ((:type "Stream"
                      :name "page"
                      :ru ":param_stream"
                      :en ":param_stream")
                     (:type "REAL"
                      :name "degrees"
                      :ru "Угол поворота системы координат (градусы)."
                      :en "Coordinate system rotate angle (degrees).")))

        ;; BRST_Stream_Rotate
        (:caption "Stream_Rotate"
         :group "graphics"
         :errors ()
	 :result (:type "STATUS"
		     :ru ":return_ok"
		     :en ":return_ok")
         :ru "Конкатенация матрицы поворота и матрицы преобразования страницы.

  Оси системы координат поворачиваются против часовой стрелки на угол \\c degrees радиан."
         :en "Concatenate the page's transformation matrix with rotate matrix.

  The coordinate system axes are rotated counterclockwise by angle \\с degrees (in radians)."
         :command "cm"
         :see ("Stream_Concat"
              "Stream_RotateDeg")
         :params ((:type "Stream"
                      :name "page"
                      :ru ":param_stream"
                      :en ":param_stream")
                     (:type "REAL"
                      :name "radians"
                      :ru "Угол поворота системы координат (радианы)."
                      :en "Coordinate system rotate angle (radians).")))

        ;; BRST_Stream_Skew
        (:caption "Stream_Skew"
         :group "graphics"
         :errors ()
	 :result (:type "STATUS"
		     :ru ":return_ok"
		     :en ":return_ok")
         :ru "Конкатенация матрицы наклона и матрицы преобразования страницы.

  Система координат наклоняется на угол \\c a по оси \\a x и на угол \\c b по оси \\a y."
         :en "Concatenate the page's transformation matrix with skew matrix.

  Coordinate system is skewed by an angle \\c a at \\a x axis and by angle \\c b at \\a y axis."
         :command "cm"
         :see ("Stream_Concat")
         :params ((:type "Stream"
                      :name "page"
                      :ru ":param_stream"
                      :en ":param_stream")
                     (:type "REAL"
                      :name "a"
                      :ru "Угол наклона по оси \\c x."
                      :en "\\c x axis skew value.")
                     (:type "REAL"
                      :name "b"
                      :ru "Угол наклона по оси \\c у."
                      :en "\\c y axis skew value.")))

        ;; BRST_Stream_Circle
        (:caption "Stream_Circle"
         :group "graphics"
         :errors ()
         :result (:type "STATUS"
                     :ru ":return_ok"
                     :en ":return_ok")
         :ru "Добавление окружности к пути."
         :en "Append circle to current path."
         :params ((:type "Stream"
                      :name "page"
                      :ru ":param_stream"
                      :en ":param_stream")
                     (:type "REAL"
                      :name "x"
                      :ru "Координата \\c x центра окружности."
                      :en "Circle center \\c x coordinate.")
                     (:type "REAL"
                      :name "y"
                      :ru "Координата \\c y центра окружности."
                      :en "Circle center \\c y coordinate.")
                     (:type "REAL"
                      :name "radius"
                      :ru "Радиус окружности."
                      :en "Circle radius.")))

;;;        ;; BRST_Stream_Ellipse
;;;        (:caption "Stream_Ellipse"
;;;         :group "graphics"
;;;         :errors ()
;;;	 :result (:type "STATUS"
;;;		     :ru ":return_ok"
;;;		     :en ":return_ok")
;;;         :ru "Добавление эллипса к пути."
;;;         :en "Append ellipse to current path."
;;;         :params ((:type "Stream"
;;;                      :name "page"
;;;                      :ru ":param_stream"
;;;                      :en ":param_stream")
;;;                     (:type "REAL"
;;;                      :name "x"
;;;                      :ru "Координата \\c x центра эллипса."
;;;                      :en "Ellipse center \\c y coordinate.")
;;;                     (:type "REAL"
;;;                      :name "y"
;;;                      :ru "Координата \\c y центра эллипса."
;;;                      :en "Ellipse center \\c y coordinate.")
;;;                     (:type "REAL"
;;;                      :name "a"
;;;                      :ru "Горизонтальная полуось эллипса."
;;;                      :en "The horizontal semi-axis of the ellipse.")
;;;                     (:type "REAL"
;;;                      :name "b"
;;;                      :ru "Вертикальная полуось эллипса."
;;;                      :en "The vertical semi-axis of the ellipse.")))

;;;        ;; BRST_Stream_Arc
;;;        (:caption "Stream_Arc"
;;;         :group "graphics"
;;;         :errors ()
;;;         :result (:type "STATUS"
;;;                     :ru ":return_ok"
;;;                     :en ":return_ok")
;;;         :ru "Функция добавляет дугу окружности к текущему графическому пути на указанной странице. 
;;;  Углы задаются в градусах, начиная от вертикали (угол 0 градусов направлен вертикально вверх). 
;;;  Дуга рисуется против часовой стрелки от начального угла (\\c angle1) до конечного угла (\\c angle2)."
;;;         :en "Append circle arc to current path.
;;;
;;;  Angles are measured in degrees, with 0 degree corresponding to the vertical direction pointing upwards from the reference point `(x, y)`."
;;;         :params ((:type "Stream"
;;;                      :name "page"
;;;                      :ru ":param_stream"
;;;                      :en ":param_stream")
;;;                     (:type "REAL"
;;;                      :name "x"
;;;                      :ru "Координата \\c x центра окружности дуги."
;;;                      :en "Arc circle center \\c x coordinate.")
;;;                     (:type "REAL"
;;;                      :name "y"
;;;                      :ru "Координата \\c у центра окружности дуги."
;;;                      :en "Arc circle center \\c y coordinate.")
;;;                     (:type "REAL"
;;;                      :name "radius"
;;;                      :ru "Радиус окружности дуги."
;;;                      :en "Arc circle radius.")
;;;                     (:type "REAL"
;;;                      :name "angle1"
;;;                      :ru "Начальный угол дуги (градусы)."
;;;                      :en "Initial angle of the arc (degrees).")
;;;                     (:type "REAL"
;;;                      :name "angle2"
;;;                      :ru "Конечный угол дуги (градусы). Должен быть больше начального угла."
;;;                      :en "Final angle of the arc (degrees). Must exceed the initial angle.")))

        ;; BRST_Stream_SetGrayFill
        (:caption "Stream_SetGrayFill"
         :group "graphics"
         :errors ()
	 :result (:type "STATUS"
		     :ru ":return_ok"
		     :en ":return_ok")
         :ru "Установка цвета заливки (тона серого)."
         :en "Set fill color (gray)."
         :command "g"
         :params ((:type "Stream"
                      :name "page"
                      :ru ":param_stream"
                      :en ":param_stream")
                     (:type "REAL"
                      :name "value"
                      :ru "Уровень серого цвета от \\c 0.0 до \\c 1.0."
                      :en "Gray level between \\c 0.0 and \\c 1.0.")))

        ;; BRST_Stream_SetGrayStroke
        (:caption "Stream_SetGrayStroke"
         :group "graphics"
         :errors ()
	 :result (:type "STATUS"
		     :ru ":return_ok"
		     :en ":return_ok")
         :ru "Установка цвета линии (тона серого)."
         :en "Set stroke color (gray)."
         :command "G"
         :params ((:type "Stream"
                      :name "page"
                      :ru ":param_stream"
                      :en ":param_stream")
                     (:type "REAL"
                      :name "value"
                      :ru "Уровень серого цвета от \\c 0.0 до \\c 1.0."
                      :en "Gray level between \\c 0.0 and \\c 1.0.")))

        ;; BRST_Stream_SetRGBFill
        (:caption "Stream_SetRGBFill"
         :group "graphics"
         :errors ()
	 :result (:type "STATUS"
		     :ru ":return_ok"
		     :en ":return_ok")
         :ru "Установка цвета заливки (RGB)."
         :en "Set fill color (RGB)."
         :command "rg"
         :params ((:type "Stream"
                      :name "page"
                      :ru ":param_stream"
                      :en ":param_stream")
                     (:type "REAL"
                      :name "r"
                      :ru "Уровень красного цвета от \\c 0.0 до \\c 1.0."
                      :en "Red level between \\c 0.0 and \\c 1.0.")
                     (:type "REAL"
                      :name "g"
                      :ru "Уровень зеленого цвета от \\c 0.0 до \\c 1.0."
                      :en "Green level between \\c 0.0 and \\c 1.0.")
                     (:type "REAL"
                      :name "b"
                      :ru "Уровень синего цвета от \\c 0.0 до \\c 1.0."
                      :en "Blue level between \\c 0.0 and \\c 1.0.")))

        ;; BRST_Stream_SetRGBFillUint
        (:caption "Stream_SetRGBFillUint"
         :group "graphics"
         :errors ()
	 :result (:type "STATUS"
		     :ru ":return_ok"
		     :en ":return_ok")
         :ru "Установка цвета заливки (RGB) с использованием значений типа \\ref BRST_UINT8."
         :en "Set fill color (RGB) using \\ref BRST_UINT8 values."
         :command "rg"
         :params ((:type "Stream"
                      :name "page"
                      :ru ":param_stream"
                      :en ":param_stream")
                     (:type "UINT8"
                      :name "r"
                      :ru "Уровень красного цвета от \\c 0 до \\c 255."
                      :en "Red level between \\c 0 and \\c 255.")
                     (:type "UINT8"
                      :name "g"
                      :ru "Уровень зеленого цвета от \\c 0 до \\c 255."
                      :en "Green level between \\c 0 and \\c 255.")
                     (:type "UINT8"
                      :name "b"
                      :ru "Уровень синего цвета от \\c 0 до \\c 255."
                      :en "Blue level between \\c 0 and \\c 255.")))

        ;; BRST_Stream_SetRGBFillHex
        (:caption "Stream_SetRGBFillHex"
         :group "graphics"
         :errors ()
	 :result (:type "STATUS"
		     :ru ":return_ok"
		     :en ":return_ok")
         :ru "Установка цвета заливки (RGB) с использованием значения типа \\ref BRST_UINT32."
         :en "Set fill color (RGB) using \\ref BRST_UINT32 value."
         :command "rg"
         :params ((:type "Stream"
                      :name "page"
                      :ru ":param_stream"
                      :en ":param_stream")
                     (:type "UINT32"
                      :name "rgb"
                      :ru "Значения цветов RGB задаются в трех байтах 32-битного беззнакового числа.
  Синий задается битами 0-7, зеленый битами 8-15, красный битами 16-23.
  Это соответствует битовым маскам \\c 0xFF, \\c 0xFF00 и \\c 0xFF0000 соответственно."
                      :en "RGB color values are represented in three bytes of a 32-bit unsigned integer.
  Blue is defined by bits 0–7, green by bits 8–15, red by bits 16–23.
  This corresponds to bit masks 0xFF, 0xFF00, and 0xFF0000, respectively.")))

        ;; BRST_Stream_SetRGBStroke
        (:caption "Stream_SetRGBStroke"
         :group "graphics"
         :errors ()
	 :result (:type "STATUS"
		     :ru ":return_ok"
		     :en ":return_ok")
         :ru "Установка цвета линии (RGB)."
         :en "Set stroke color (RGB)."
         :command "RG"
         :params ((:type "Stream"
                      :name "page"
                      :ru ":param_stream"
                      :en ":param_stream")
                     (:type "REAL"
                      :name "r"
                      :ru "Уровень красного цвета от \\c 0.0 до \\c 1.0."
                      :en "Red level between \\c 0.0 and \\c 1.0.")
                     (:type "REAL"
                      :name "g"
                      :ru "Уровень зеленого цвета от \\c 0.0 до \\c 1.0."
                      :en "Green level between \\c 0.0 and \\c 1.0.")
                     (:type "REAL"
                      :name "b"
                      :ru "Уровень синего цвета от \\c 0.0 до \\c 1.0."
                      :en "Blue level between \\c 0.0 and \\c 1.0.")))

        ;; BRST_Stream_SetRGBStrokeUint
        (:caption "Stream_SetRGBStrokeUint"
         :group "graphics"
         :errors ()
	 :result (:type "STATUS"
		     :ru ":return_ok"
		     :en ":return_ok")
         :ru "Установка цвета линии (RGB) с использованием значений типа \\ref BRST_UINT8."
         :en "Set stroke color (RGB) using \\ref BRST_UINT8 values."
         :command "RG"
         :params ((:type "Stream"
                      :name "page"
                      :ru ":param_stream"
                      :en ":param_stream")
                   (:type "UINT8"
                    :name "r"
                     :ru "Уровень красного цвета от \\c 0 до \\c 255."
                     :en "Red level between \\c 0 and \\c 255.")
                   (:type "UINT8"
                    :name "g"
                    :ru "Уровень зеленого цвета от \\c 0 до \\c 255."
                    :en "Green level between \\c 0 and \\c 255.")
                   (:type "UINT8"
                    :name "b"
                    :ru "Уровень синего цвета от \\c 0 до \\c 255."
                    :en "Blue level between \\c 0 and \\c 255.")))

       ;; BRST_Stream_SetRGBStrokeHex
       (:caption "Stream_SetRGBStrokeHex"
        :group "graphics"
        :errors ()
	:result (:type "STATUS"
		    :ru ":return_ok"
		    :en ":return_ok")
        :ru "Установка цвета линии (RGB) с использованием значения типа \\ref BRST_UINT32."
        :en "Set stroke color (RGB) using \\ref BRST_UINT32 value."
        :command "rg"
        :params ((:type "Stream"
                     :name "page"
                     :ru ":param_stream"
                     :en ":param_stream")
                    (:type "UINT32"
                     :name "rgb"
                     :ru "Значения цветов RGB задаются в трех байтах 32-битного беззнакового числа.
  Синий задается битами 0-7, зеленый битами 8-15, красный битами 16-23.
  Это соответствует битовым маскам \\c 0xFF, \\c 0xFF00 и \\c 0xFF0000 соответственно."
                     :en "RGB color values are represented in three bytes of a 32-bit unsigned integer.
  Blue is defined by bits 0–7, green by bits 8–15, red by bits 16–23.
  This corresponds to bit masks 0xFF, 0xFF00, and 0xFF0000, respectively.")))

       ;; BRST_Stream_SetCMYKFill
       (:caption "Stream_SetCMYKFill"
        :group "graphics"
        :errors ()
	:result (:type "STATUS"
		    :ru ":return_ok"
		    :en ":return_ok")
        :ru "Установка цвета заливки (CMYK)."
        :en "Set fill color (CMYK)."
        :command "k"
        :params ((:type "Stream"
                     :name "page"
                     :ru ":param_stream"
                     :en ":param_stream")
                    (:type "REAL"
                     :name "c"
                     :ru "Уровень синего (cyan) цвета от \\c 0.0 до \\c 1.0."
                     :en "Cyan level between \\c 0.0 and \\c 1.0.")
                    (:type "REAL"
                     :name "m"
                     :ru "Уровень пурпурного (magenta) цвета от \\c 0.0 до \\c 1.0."
                     :en "Magenta level between \\c 0.0 and \\c 1.0.")
                    (:type "REAL"
                     :name "y"
                     :ru "Уровень желтого (yellow) цвета от \\c 0.0 до \\c 1.0."
                     :en "Yellow level between \\c 0.0 and \\c 1.0.")
                    (:type "REAL"
                     :name "k"
                     :ru "Уровень черного (blacK) цвета от \\c 0.0 до \\c 1.0."
                     :en "BlacK level between \\c 0.0 and \\c 1.0.")))

       ;; BRST_Stream_SetCMYKStroke
       (:caption "Stream_SetCMYKStroke"
        :group "graphics"
        :errors ()
	:result (:type "STATUS"
		    :ru ":return_ok"
		    :en ":return_ok")
        :ru "Установка цвета линии (CMYK)."
        :en "Set stroke color (CMYK)."
        :command "K"
        :params ((:type "Stream"
                     :name "page"
                     :ru ":param_stream"
                     :en ":param_stream")
                    (:type "REAL"
                     :name "c"
                     :ru "Уровень синего (cyan) цвета от \\c 0.0 до \\c 1.0."
                     :en "Cyan level between \\c 0.0 and \\c 1.0.")
                    (:type "REAL"
                     :name "m"
                     :ru "Уровень пурпурного (magenta) цвета от \\c 0.0 до \\c 1.0."
                     :en "Magenta level between \\c 0.0 and \\c 1.0.")
                    (:type "REAL"
                     :name "y"
                     :ru "Уровень желтого (yellow) цвета от \\c 0.0 до \\c 1.0."
                     :en "Yellow level between \\c 0.0 and \\c 1.0.")
                    (:type "REAL"
                     :name "k"
                     :ru "Уровень черного (blacK) цвета от \\c 0.0 до \\c 1.0."
                     :en "BlacK level between \\c 0.0 and \\c 1.0.")))

       ;; BRST_Stream_Clip
       (:caption "Stream_Clip"
        :group "graphics"
        :errors ()
	:result (:type "STATUS"
		    :ru ":return_ok"
		    :en ":return_ok")
        :ru "Изменение текущей область отсечения, пересечение её с текущим путём, что определяет внутренние регионы
  области отсечения с применением правила ненулевого счёта обхода (nonzero winding number rule).

  Область отсечения изменяется только после следующего оператора рисования.Чтобы избежать рисования текущего пути, используйте функцию BRST_Stream_EndPath().

  Все последующие операции рисования будут влиять только на области страницы, входящие в пределы области отсечения.
  Первоначально область отсечения включает всю страницу.
  Увеличить или заменить новой областью отсечения Текущую область отсечения нельзя.
  Функции BRST_Stream_GSave() и BRST_Stream_GRestore() позволяют сохранять и восстанавливать
  текущее графическое состояние, включая область отсечения."

        :en "Modifies the current clipping path by intersecting it with the current path, using
  the nonzero winding number rule to determine which regions lie inside the clipping path.

  The clipping path is only modified after the succeeding painting operator.
  To avoid painting the current path, use the function BRST_Stream_EndPath().

  Following painting operations will only affect the regions of the page contained by the clipping path.
  Initially, the clipping path includes the entire page. There is no way to enlarge the current clipping path
  or to replace the clipping path with a new one. The functions BRST_Stream_GSave() and BRST_Stream_GRestore()
  may be used to save and restore the current graphics state, including the clipping path."
        :command "W"
        :see (
             "Stream_EndPath"
             "Stream_GSave"
             "Stream_GRestore"
             "Stream_Eoclip"
             )
        :params ((:type "Stream"
                     :name "page"
                     :ru ":param_stream"
                     :en ":param_stream")))

       ;; BRST_Stream_Eoclip
       (:caption "Stream_Eoclip"
        :group "graphics"
        :errors ()
	:result (:type "STATUS"
		    :ru ":return_ok"
		    :en ":return_ok")
        :ru "Изменение текущей область отсечения, пересечение её с текущим путём, что определяет внутренние регионы
  области отсечения с применением правила чётный-нечётный (even-odd rule).

    Область отсечения изменяется только после следующего оператора рисования.Чтобы избежать рисования текущего пути, используйте функцию BRST_Stream_EndPath().

  Все последующие операции рисования будут влиять только на области страницы, входящие в пределы области отсечения.
  Первоначально область отсечения включает всю страницу.
  Увеличить или заменить новой областью отсечения Текущую область отсечения нельзя.
  Функции BRST_Stream_GSave() и BRST_Stream_GRestore() позволяют сохранять и восстанавливать
  текущее графическое состояние, включая область отсечения."

        :en "Modifies the current clipping path by intersecting it with current path using the even-odd rule.

  The clipping path is only modified after the succeeding painting operator.
  To avoid painting the current path, use the function BRST_Stream_EndPath().

  Following painting operations will only affect the regions of the page contained by the clipping path.
  Initially, the clipping path includes the entire page. There is no way to enlarge the current clipping path
  or to replace the clipping path with a new one. The functions BRST_Stream_GSave() and BRST_Stream_GRestore()
  may be used to save and restore the current graphics state, including the clipping path."
        :command "W*"
        :see (
             "Stream_EndPath"
             "Stream_GSave"
             "Stream_GRestore"
             "Stream_Clip"
             )
        :params ((:type "Stream"
                     :name "page"
                     :ru ":param_stream"
                     :en ":param_stream")))

       ;; BRST_Stream_Stroke
       (:caption "Stream_Stroke"
        :group "graphics"
        :errors ()
        :result (:type "STATUS"
		    :ru ":return_ok"
		    :en ":return_ok")
        :ru "Отображение текущего пути."
        :en "Paint current path."
        :command "S"
        :params ((:type "Stream"
                     :name "page"
                     :ru ":param_stream"
                     :en ":param_stream")))

       ;; BRST_Stream_ClosePathStroke
       (:caption "Stream_ClosePathStroke"
        :group "graphics"
        :errors ()
	:result (:type "STATUS"
		    :ru ":return_ok"
		    :en ":return_ok")
        :ru "Закрытие и отображение текущего пути."
        :en "Close and paint current path."
        :command "s"
        :params ((:type "Stream"
                     :name "page"
                     :ru ":param_stream"
                     :en ":param_stream")))

       ;; BRST_Stream_Fill
       (:caption "Stream_Fill"
        :group "graphics"
        :errors ()
	:result (:type "STATUS"
		    :ru ":return_ok"
		    :en ":return_ok")
        :ru "Заполнение текущего пути с применением правила ненулевого счёта обхода."
        :en "Fill current path using nonzero winding number rule."
        :command "f"
        :params ((:type "Stream"
                     :name "page"
                     :ru ":param_stream"
                     :en ":param_stream")))

       ;; BRST_Stream_Eofill
       (:caption "Stream_Eofill"
        :group "graphics"
        :errors ()
	:result (:type "STATUS"
		    :ru ":return_ok"
		    :en ":return_ok")
        :ru "Заполнение текущего пути с применением правила чётный-нечётный."
        :en "Fill current path using even-odd rule."
        :command "f*"
        :params ((:type "Stream"
                     :name "page"
                     :ru ":param_stream"
                     :en ":param_stream")))

       ;; BRST_Stream_FillStroke
       (:caption "Stream_FillStroke"
        :group "graphics"
        :errors ()
	:result (:type "STATUS"
		    :ru ":return_ok"
		    :en ":return_ok")
        :ru "Заполнение текущего пути с применением правила ненулевого счёта обхода с последующим отображением пути."
        :en "Fill current path using the nonzero winding number rule and then paint the path."
        :command "B"
        :params ((:type "Stream"
                     :name "page"
                     :ru ":param_stream"
                     :en ":param_stream")))

       ;; BRST_Stream_EofillStroke
       (:caption "Stream_EofillStroke"
        :group "graphics"
        :errors ()
	:result (:type "STATUS"
		    :ru ":return_ok"
		    :en ":return_ok")
        :ru "Заполнение текущего пути с применением правила чётный-нечётный с последующим отображением пути."
        :en "Fill current path using the even-odd rule and then paint the path."
        :command "B*"
        :params ((:type "Stream"
                     :name "page"
                     :ru ":param_stream"
                     :en ":param_stream")))

       ;; BRST_Stream_ClosePathFillStroke
       (:caption "Stream_ClosePathFillStroke"
        :group "graphics"
        :errors ()
	:result (:type "STATUS"
		    :ru ":return_ok"
		    :en ":return_ok")
        :ru "Закрытие пути, заполнение текущего пути с применением правила ненулевого счёта обхода с последующим отображением пути."
        :en "Close current path, fill current path using the nonzero winding number rule, then paint path."
        :command "b"
        :params ((:type "Stream"
                     :name "page"
                     :ru ":param_stream"
                     :en ":param_stream")))

       ;; BRST_Stream_ClosePathEofillStroke
       (:caption "Stream_ClosePathEofillStroke"
        :group "graphics"
        :errors ()
	:result (:type "STATUS"
		    :ru ":return_ok"
		    :en ":return_ok")
        :ru "Закрытие пути, заполнение текущего пути с применением правила чётный-нечётный с последующим отображением пути."
        :en "Close current path, fill current path using the even-odd rule and then paint the path."
        :command "b*"
        :params ((:type "Stream"
                     :name "page"
                     :ru ":param_stream"
                     :en ":param_stream")))

       ;; BRST_Stream_EndPath
       (:caption "Stream_EndPath"
        :group "graphics"
        :errors ()
	:result (:type "STATUS"
		    :ru ":return_ok"
		    :en ":return_ok")
        :ru "Окончание пути без заполнения и отображения."
        :en "Finish path object without fill or painting."
        :command "n"
        :params ((:type "Stream"
                     :name "page"
                     :ru ":param_stream"
                     :en ":param_stream")))

       ;; BRST_Stream_MoveTo
       (:caption "Stream_MoveTo"
        :group "graphics"
        :errors ()
	:result (:type "STATUS"
		    :ru ":return_ok"
		    :en ":return_ok")
        :ru "Начало нового подпути с переносом текущей точки отображения путей."
        :en "Start new subpath and move current point for drawing path."
        :command "m"
        :params ((:type "Stream"
                     :name "page"
                     :ru ":param_stream"
                     :en ":param_stream")
                    (:type "REAL"
                     :name "x"
                     :ru "Координата \\c x начальной точки отображения пути."
                     :en "Starting point \\c x coordinate for drawing path.")
                    (:type "REAL"
                     :name "y"
                     :ru "Координата \\c y начальной точки отображения пути."
                     :en "Starting point \\c y coordinate for drawing path.")))

       ;; BRST_Stream_LineTo
       (:caption "Stream_LineTo"
        :group "graphics"
        :errors ()
	:result (:type "STATUS"
		    :ru ":return_ok"
		    :en ":return_ok")
        :ru "Добавление отрезка прямой из текущей точки в точку с координатами `(x, y)` как подпуть текущего пути.
        Точка `(x, y)` становится текущей для отображения путей."
        :en "Append a straight line segment from the current point to the point `(x, y)`. The new current point shall be `(x, y)`."
        :command "l"
        :params ((:type "Stream"
                     :name "page"
                     :ru ":param_stream"
                     :en ":param_stream")
                    (:type "REAL"
                     :name "x"
                     :ru "Координата \\c x целевой (конечной) точки добавляемого отрезка."
                     :en "End point \\c x coordinate for line segment.")
                    (:type "REAL"
                     :name "y"
                     :ru "Координата \\c y целевой (конечной) точки добавляемого отрезка."
                     :en "End point \\c y coordinate for line segment.")))

       ;; BRST_Stream_CurveTo
       (:caption "Stream_CurveTo"
        :group "graphics"
        :errors ()
	:result (:type "STATUS"
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
        :command "c"
        :params ((:type "Stream"
                     :name "page"
                     :ru ":param_stream"
                     :en ":param_stream")
                    (:type "REAL"
                     :name "x1"
                     :ru "Координата \\c x первой контрольной точки кубической кривой Безье."
                     :en "First cubic Bézier curve control point \\c x coordinate.")
                    (:type "REAL"
                     :name "y1"
                     :ru "Координата \\c y первой контрольной точки кубической кривой Безье."
                     :en "First cubic Bézier curve control point \\c y coordinate.")
                    (:type "REAL"
                     :name "x2"
                     :ru "Координата \\c x второй контрольной точки кубической кривой Безье."
                     :en "Second cubic Bézier curve control point \\c x coordinate.")
                    (:type "REAL"
                     :name "y2"
                     :ru "Координата \\c y второй контрольной точки кубической кривой Безье."
                     :en "Second cubic Bézier curve control point \\c y coordinate.")
                    (:type "REAL"
                     :name "x3"
                     :ru "Координата \\c x третьей контрольной точки кубической кривой Безье."
                     :en "Third cubic Bézier curve control point \\c x coordinate.")
                    (:type "REAL"
                     :name "y3"
                     :ru "Координата \\c y третьей контрольной точки кубической кривой Безье."
                     :en "Third cubic Bézier curve control point \\c y coordinate.")))

       ;; BRST_Stream_CurveTo2
       (:caption "Stream_CurveTo2"
        :group "graphics"
        :errors ()
	:result (:type "STATUS"
		    :ru ":return_ok"
		    :en ":return_ok")
        :ru "Добавление кубической кривой Безье с использованием контрольных точек (x<sub>2</sub>, y<sub>2</sub>)
  и (x<sub>3</sub>, y<sub>3</sub>). Точка (x<sub>3</sub>, y<sub>3</sub>) становится текущей для отображения путей.
  \\image html img/curveto2.png"

        :en "Append Bézier curve to current path using current point and (x<sub>2</sub>, y<sub>2</sub>)
  and (x<sub>3</sub>, y<sub>3</sub>) as control points. Then current point is set to (x<sub>3</sub>, y<sub>3</sub>).

  \\image html img/curveto2.png"
        :command "v"
        :params ((:type "Stream"
                     :name "page"
                     :ru ":param_stream"
                     :en ":param_stream")
                    (:type "REAL"
                     :name "x2"
                     :ru "Координата \\c x второй контрольной точки кубической кривой Безье."
                     :en "Second cubic Bézier curve control point \\c x coordinate.")
                    (:type "REAL"
                     :name "y2"
                     :ru "Координата \\c y второй контрольной точки кубической кривой Безье."
                     :en "Second cubic Bézier curve control point \\c y coordinate.")
                    (:type "REAL"
                     :name "x3"
                     :ru "Координата \\c x третьей контрольной точки кубической кривой Безье."
                     :en "Third cubic Bézier curve control point \\c x coordinate.")
                    (:type "REAL"
                     :name "y3"
                     :ru "Координата \\c y третьей контрольной точки кубической кривой Безье."
                     :en "Third cubic Bézier curve control point \\c y coordinate.")))

       ;; BRST_Stream_CurveTo3
       (:caption "Stream_CurveTo3"
        :group "graphics"
        :errors ()
	:result (:type "STATUS"
		    :ru ":return_ok"
		    :en ":return_ok")
        :ru "Добавление кубической кривой Безье с использованием контрольных точек (x<sub>1</sub>, y<sub>1</sub>)
  и (x<sub>3</sub>, y<sub>3</sub>). Точка (x<sub>3</sub>, y<sub>3</sub>) становится текущей для отображения путей.

  \\image html img/curveto3.png."

        :en "Append a cubic Bézier curve to the current path using control points
  (x<sub>1</sub>, y<sub>1</sub>) and (x<sub>3</sub>, y<sub>3</sub>), then set current point
  to (x<sub>3</sub>, y<sub>3</sub>).

  \\image html img/curveto3.png."
        :command "y"
        :params ((:type "Stream"
                     :name "page"
                     :ru ":param_stream"
                     :en ":param_stream")
                    (:type "REAL"
                     :name "x1"
                     :ru "Координата \\c x первой контрольной точки кубической кривой Безье."
                     :en "First cubic Bézier curve control point \\c x coordinate.")
                    (:type "REAL"
                     :name "y1"
                     :ru "Координата \\c y первой контрольной точки кубической кривой Безье."
                     :en "First cubic Bézier curve control point \\c y coordinate.")
                    (:type "REAL"
                     :name "x3"
                     :ru "Координата \\c x третьей контрольной точки кубической кривой Безье."
                     :en "Third cubic Bézier curve control point \\c x coordinate.")
                    (:type "REAL"
                     :name "y3"
                     :ru "Координата \\c y третьей контрольной точки кубической кривой Безье."
                     :en "Third cubic Bézier curve control point \\c y coordinate.")))

       ;; BRST_Stream_ClosePath
       (:caption "Stream_ClosePath"
        :group "graphics"
        :errors ()
	:result (:type "STATUS"
		    :ru ":return_ok"
		    :en ":return_ok")
        :ru "Закрытие текущего подпути добавлением отрезка из текущей точки в начальную точку подпути."
        :en "Close the current subpath by appending a straight line segment from the current point to the starting point of the subpath."
        :command "h"
        :params ((:type "Stream"
                     :name "page"
                     :ru ":param_stream"
                     :en ":param_stream")))

       ;; BRST_Stream_Rectangle
       (:caption "Stream_Rectangle"
        :group "graphics"
        :errors ()
	:result (:type "STATUS"
		    :ru ":return_ok"
		    :en ":return_ok")
        :ru "Добавление прямоугольника к текущему пути в качестве самостоятельного подпути.
  У прямоугольника левый нижний угол расположен в точке `(x, y)` и измерениями \\c width и \\c height."

        :en "Append a rectangle to the current path as a complete
subpath, with lower-left corner `(x, y)` and dimensions \\c width
and \\c height in user space."
        :command "re"
        :params ((:type "Stream"
                     :name "page"
                     :ru ":param_stream"
                     :en ":param_stream")
                    (:type "REAL"
                     :name "x"
                     :ru "Координата \\c x левого нижнего угла прямоугольника."
                     :en "Rectangle low-left corner \\c x coordinate.")
                    (:type "REAL"
                     :name "y"
                     :ru "Координата \\c y левого нижнего угла прямоугольника."
                     :en "Rectangle low-left corner \\c y coordinate.")
                    (:type "REAL"
                     :name "width"
                     :ru "Ширина прямоугольника."
                     :en "Rectangle width")
                    (:type "REAL"
                     :name "height"
                     :ru "Высота прямоугольника."
                     :en "Rectangle height")))

       ;; BRST_Stream_SetLineWidth
       (:caption "Stream_SetLineWidth"
        :group "graphics"
        :errors ()
	:result (:type "STATUS"
		    :ru ":return_ok"
		    :en ":return_ok")
        :ru "Установка толщины линии для отображения путей."
        :en "Set width of the line used to stroke paths."
        :command "w"
        :params ((:type "Stream"
                     :name "page"
                     :ru ":param_stream"
                     :en ":param_stream")
                    (:type "REAL"
                     :name "line_width"
                     :ru "Толщина линии для отображения путей. По умолчанию равна \\c 1.0."
                     :en "Line width. Default \\c line_width is \\c 1.0")))


       ;; BRST_Stream_SetLineCap
       (:caption "Stream_SetLineCap"
        :group "graphics"
        :errors ()
	:result (:type "STATUS"
		    :ru ":return_ok"
		    :en ":return_ok")
        :ru "Установка стиля окончания линии."
        :en "Set lines endpoints shape style."
        :command "J"
        :params ((:type "Stream"
                     :name "page"
                     :ru ":param_stream"
                     :en ":param_stream")
                    (:type "LineCap"
                     :name "line_cap"
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

       ;; BRST_Stream_SetLineJoin
       (:caption "Stream_SetLineJoin"
        :group "graphics"
        :errors ()
	:result (:type "STATUS"
		    :ru ":return_ok"
		    :en ":return_ok")
        :ru "Установка стиля стыка линий."
        :en "Set line join shape style."
        :command "j"
        :params ((:type "Stream"
                     :name "page"
                     :ru ":param_stream"
                     :en ":param_stream")
                    (:type "LineJoin"
                     :name "line_join"
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

       ;; Stream_SetMiterLimit
       (:caption "Stream_SetMiterLimit"
        :group "graphics"
        :errors ()
	:result (:type "STATUS"
		    :ru ":return_ok"
		    :en ":return_ok")
        :ru "Установка предельного значения острого угла линии для пересечений.
  Предельное значение острого угла (miter limit) равное \\c 1.414, превращает острые углы соединения в скос при угле меньше \\c 90 градусов.
  Ограничение 2.0 делает это для углов меньше \\c 60 градусов, а ограничение 10.0 действует для углов менее \\c 11.5 градусов."

        :en "Set miter limit for line joins.

  A miter limit of 1.414 converts miters to bevels for \\c angle less than \\c 90 degrees,
  a limit of \\c 2.0 converts them for \\c angle less than 60 degrees, and a limit of 10.0
  converts them for angle less than approximately 11.5 degrees."
        :command "M"
        :params ((:type "Stream"
                     :name "page"
                     :ru ":param_stream"
                     :en ":param_stream")
                    (:type "REAL"
                     :name "miter_limit"
                     :ru "Предельное значение острого угла линии."
                     :en "Miter limit value.")))

       ;; BRST_Stream_SetDash
       (:caption "Stream_SetDash"
        :group "graphics"
        :errors ()
	:result (:type "STATUS"
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
        :command "d"
        :params ((:type "Stream"
                     :name "page"
                     :ru ":param_stream"
                     :en ":param_stream")
                    (:type "DASH_PATTERN"
                     :name "dash_pattern"
                     :ru ""
                     :en "Pattern of dashes and gaps used to stroke paths.")
                    (:type "UINT"
                     :name "num_elem"
                     :ru ""
                     :en "Number of elements in dash_pattern, `0 <= num_param <= 8`.")
                    (:type "REAL"
                     :name "phase"
                     :ru ""
                     :en "Phase in which pattern begins (default is \\c 0)")))

       ;; BRST_Stream_SetFlat
       (:caption "Stream_SetFlat"
        :group "graphics"
        :errors ()
	:result (:type "STATUS"
		    :ru ":return_ok"
		    :en ":return_ok")
        :ru ""
        :en "Set flatness tolerance for curves rendering."
        :command "i"
        :params ((:type "Stream"
                     :name "page"
                     :ru ":param_stream"
                     :en ":param_stream")
                    (:type "REAL"
                     :name "flatness"
                     :ru ""
                     :en "")))))

