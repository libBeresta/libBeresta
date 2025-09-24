(:файл "stream_text"
 :функции
       (
        ;; BRST_Stream_BeginText
        (:название "Stream_BeginText"
         :группа "graphics"
         :ошибки ()
         :результат (:тип "STATUS"
                     :ru ":return_ok"
                     :en ":return_ok")
         :ru "Начинает текстовый объект и устанавливает начальную позицию текста в точке `(0, 0)`."
         :en "Begins a text object and sets the initial text position to `(0, 0)`."
         :команда "BT"
         :параметры ((:тип "Stream"
                      :имя "stream"
                      :ru ":param_stream"
                      :en ":param_stream")))

        ;; BRST_Stream_EndText
        (:название "Stream_EndText"
         :группа "graphics"
         :ошибки ()
         :результат (:тип "STATUS"
                     :ru ":return_ok"
                     :en ":return_ok")
         :ru "Заканчивает текстовый объект на странице."
         :en "Finish text object."
         :команда "ET"
         :параметры ((:тип "Stream"
                      :имя "stream"
                      :ru ":param_stream"
                      :en ":param_stream")))

        ;; BRST_Stream_SetTextLeading
        (:название "Stream_SetTextLeading"
         :группа "graphics"
         :ошибки ()
         :результат (:тип "STATUS"
                     :ru ":return_ok"
                     :en ":return_ok")
         :ru "Устанавливает интерлиньяж (расстояния между базовыми линиями соседних строк)."
         :en "Set text leading (line spacing)."
         :команда "TL"
         :параметры ((:тип "Stream"
                      :имя "stream"
                      :ru ":param_stream"
                      :en ":param_stream")
                     (:тип "REAL"
                      :имя "value"
                      :ru "Значение интерлиньяжа (начальное значение = \\c 0)."
                      :en "Value of text leading (initially \\c 0).")))

        ;; BRST_Stream_SetTextRenderingMode
        (:название "Stream_SetTextRenderingMode"
         :группа "graphics"
         :ошибки ()
         :результат (:тип "STATUS"
                     :ru ":return_ok"
                     :en ":return_ok")
         :ru "Устанавливает режим рендеринга текста (заполнение, контур, обрезка и др.)."
         :en "Set text rendering mode."
         :команда "Tr"
         :параметры ((:тип "Stream"
                      :имя "stream"
                      :ru ":param_stream"
                      :en ":param_stream")
                     (:тип "TextRenderingMode"
                      :имя "mode"
                      :ru "\\parblock Режим рендеринга текста (одно из значений):

  | Значение                       | Изображение              | Описание                                                 |
  | --------                       | :---------:              | --------                                                 |
  | \\ref BRST_FILL                 | \\image html rndmode1.png | Залить текст.                                            |
  | \\ref BRST_STROKE               | \\image html rndmode2.png | Обвести текст.                                           |
  | \\ref BRST_FILL_THEN_STROKE     | \\image html rndmode3.png | Залить, затем обвести текст.                             |
  | \\ref BRST_INVISIBLE            | &mdash;                  | Не заливать и не обводить текст (невидимый).             |
  | \\ref BRST_FILL_CLIPPING        | \\image html rndmode4.png | Залить текст и добавить путь в отсечение.                |
  | \\ref BRST_STROKE_CLIPPING      | \\image html rndmode5.png | Обвести текст и добавить путь в отсечение.               |
  | \\ref BRST_FILL_STROKE_CLIPPING | \\image html rndmode6.png | Залить, затем обвести текст и добавить путь в отсечение. |
  | \\ref BRST_CLIPPING             | &mdash;                  | Добавить текст в путь отсечения.                         |

  По умолчанию режим рендеринга \\c mode равен \\ref BRST_FILL. \\endparblock
"
                      :en "\\parblock Text rendering mode.

  | Value                          | Image                    | Description                                          |
  | -----                          | :-----:                  | -----------                                          |
  | \\ref BRST_FILL                 | \\image html rndmode1.png | Fill text.                                           |
  | \\ref BRST_STROKE               | \\image html rndmode2.png | Stroke text.                                         |
  | \\ref BRST_FILL_THEN_STROKE     | \\image html rndmode3.png | Fill, then stroke text.                              |
  | \\ref BRST_INVISIBLE            | &mdash;                  | Neither fill nor stroke text (invisible).            |
  | \\ref BRST_FILL_CLIPPING        | \\image html rndmode4.png | Fill text and add to path for clipping.              |
  | \\ref BRST_STROKE_CLIPPING      | \\image html rndmode5.png | Stroke text and add to path for clipping.            |
  | \\ref BRST_FILL_STROKE_CLIPPING | \\image html rndmode6.png | Fill, then stroke text and add to path for clipping. |
  | \\ref BRST_CLIPPING             | &mdash;                  | Add text to path for clipping.                       |

  Default \\c mode is \\ref BRST_FILL. \\endparblock
")))

        ;; BRST_Stream_MoveTextPos
        (:название "Stream_MoveTextPos"
         :группа "graphics"
         :ошибки ()
         :результат (:тип "STATUS"
                     :ru ":return_ok"
                     :en ":return_ok")
         :ru "Перемещает текущую позицию текста на указанное смещение.

  Если текущая текстовая позиция (x<sub>1</sub>, y<sub>1</sub>), обновленная текстовая позиция будет равна (x<sub>1</sub> + x, y<sub>1</sub> + y)."
         :en "Change current text position using specified offsets.

  If the current text position is (x<sub>1</sub>, y<sub>1</sub>), the new text position will be (x<sub>1</sub> + x, y<sub>1</sub> + y)."
         :команда "Td"
         :параметры ((:тип "Stream"
                      :имя "stream"
                      :ru ":param_stream"
                      :en ":param_stream")
                     (:тип "REAL"
                      :имя "x"
                      :ru "Горизонтальное смещение."
                      :en "Offset to new text position along \\с x axis.")
                     (:тип "REAL"
                      :имя "y"
                      :ru "Вертикальное смещение."
                      :en "Offset to new text position along \\c y axis.")))

        ;; BRST_Stream_MoveTextPos2
        (:название "Stream_MoveTextPos2"
         :группа "graphics"
         :ошибки ()
         :результат (:тип "STATUS"
                     :ru ":return_ok"
                     :en ":return_ok")
         :ru "Перемещает текущую позицию текста на указанное смещение.

  Если текущая текстовая позиция (x<sub>1</sub>, y<sub>1</sub>), обновленная текстовая позиция будет равна (x<sub>1</sub> + x, y<sub>1</sub> + y)."
         :en "Change current text position using specified offsets.

  If the current text position is (x<sub>1</sub>, y<sub>1</sub>), the new text position will be (x<sub>1</sub> + x, y<sub>1</sub> + y)."
         :команда "Td"
         :параметры ((:тип "Stream"
                      :имя "stream"
                      :ru ":param_stream"
                      :en ":param_stream")
                     (:тип "REAL"
                      :имя "x"
                      :ru "Горизонтальное смещение."
                      :en "Offset to new text position along \\с x axis.")
                     (:тип "REAL"
                      :имя "y"
                      :ru "Вертикальное смещение."
                      :en "Offset to new text position along \\c y axis.")))

        ;; BRST_Stream_SetTextMatrix
        (:название "Stream_SetTextMatrix"
         :группа "graphics"
         :ошибки ()
         :результат (:тип "STATUS"
                     :ru ":return_ok"
                     :en ":return_ok")
         :ru "Задает матрицу преобразования текста."
         :en "Set text transformation matrix."
         :команда "Tm"
         :параметры ((:тип "Stream"
                      :имя "stream"
                      :ru ":param_stream"
                      :en ":param_stream")
                     (:тип "REAL"
                      :имя "a"
                      :ru "Элемент матрицы"
                      :en "First element of transformation matrix.")
                     (:тип "REAL"
                      :имя "b"
                      :ru "Элемент матрицы"
                      :en "Second element of transformation matrix.")
                     (:тип "REAL"
                      :имя "c"
                      :ru "Элемент матрицы"
                      :en "Third element of transformation matrix.")
                     (:тип "REAL"
                      :имя "d"
                      :ru "Элемент матрицы"
                      :en "Fourth element of transformation matrix.")
                     (:тип "REAL"
                      :имя "x"
                      :ru "Смещение по оси \\c x."
                      :en "Translation component along X-axis.")
                     (:тип "REAL"
                      :имя "y"
                      :ru "Смещение по оси \\c y."
                      :en "Translation component along Y-axis.")))

        ;; BRST_Stream_ShowText
        (:название "Stream_ShowText"
         :группа "graphics"
         :ошибки ()
         :результат (:тип "STATUS"
                     :ru ":return_ok"
                     :en ":return_ok")
         :ru "Отображает текст в текущей позиции."
         :en "Put text at the current text position on the page."
         :команда "Tj"
         :параметры ((:тип "Stream"
                      :имя "stream"
                      :ru ":param_stream"
                      :en ":param_stream")
                     (:тип "Font"
                      :имя "font"
                      :ru ":param_font"
                      :en ":param_font")
                     (:тип "CSTR"
                      :имя "text"
                      :ru "Строка текста."
                      :en "Text to display.")))

        ;; BRST_Stream_TextOut
        (:название "Stream_TextOut"
         :группа "graphics"
         :ошибки ()
         :результат (:тип "STATUS"
                     :ru ":return_ok"
                     :en ":return_ok")
         :ru "Помещает текст в указанную позицию на странице."
         :en "Put text to the specified position."
         :параметры ((:тип "Stream"
                      :имя "stream"
                      :ru ":param_stream"
                      :en ":param_stream")
                     (:тип "Font"
                      :имя "font"
                      :ru ":param_font"
                      :en ":param_font")
                     (:тип "REAL"
                      :имя "xpos"
                      :ru "Позиция по горизонтали"
                      :en "Horizontal position.")
                     (:тип "REAL"
                      :имя "ypos"
                      :ru "Позиция по вертикали"
                      :en "Vertical position.")
                     (:тип "CSTR"
                      :имя "text"
                      :ru "Строка текста"
                      :en "Text to display.")))

        ;; BRST_Stream_MoveToNextLine
        (:название "Stream_MoveToNextLine"
         :группа "graphics"
         :ошибки ()
         :результат (:тип "STATUS"
                     :ru ":return_ok"
                     :en ":return_ok")
         :ru "Переходит к следующей строке с учётом настроек интерлиньяжа.

  Положение текста вычисляется с учетом текущей матрицы преобразования текста."
         :en "Move current position for text showing to the beginning of the next line.

  New position is calculated with current text transition matrix."
         :команда "T*"
         :параметры ((:тип "Stream"
                      :имя "stream"
                      :ru ":param_stream"
                      :en ":param_stream")))))
