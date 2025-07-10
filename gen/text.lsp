
;; BRST_Page_BeginText
(:название "Page_BeginText"
 :группа "graphics"
 :ошибки ()
 :результат (:тип "STATUS"
              :ru ":return_ok"
              :en ":return_ok")
 :ru "Начинает текстовый объект и устанавливает начальную позицию текста в точке (0, 0)."
 :en "Begins a text object and sets the initial text position to (0, 0)."
 :команда "BT"
 :параметры ((:тип "Page"
                  :имя "page"
                  :ru ":param_page"
                  :en ":param_page"))
 :режимы-графики '("Before" . "BRST_GMODE_PAGE_DESCRIPTION") ("After" . "BRST_GMODE_TEXT_OBJECT"))

;; BRST_Page_EndText
(:название "Page_EndText"
 :группа "graphics"
 :ошибки ()
 :результат (:тип "STATUS"
              :ru ":return_ok"
              :en ":return_ok")
 :ru "Заканчивает текстовый объект на странице."
 :en "Finish text object."
 :команда "ET"
 :параметры ((:тип "Page"
                  :имя "page"
                  :ru ":param_page"
                  :en ":param_page"))
 :режимы-графики '("Before" . "BRST_GMODE_TEXT_OBJECT") ("After" . "BRST_GMODE_PAGE_DESCRIPTION"))

;; BRST_Page_SetTextLeading
(:название "Page_SetTextLeading"
 :группа "graphics"
 :ошибки ()
 :результат (:тип "STATUS"
              :ru ":return_ok"
              :en ":return_ok")
 :ru "Устанавливает интерлиньяж (расстояния между базовыми линиями соседних строк)."
 :en "Set text leading (line spacing)."
 :команда "TL"
 :параметры ((:тип "Page"
                  :имя "page"
                  :ru ":param_page"
                  :en ":param_page")
                 (:тип "REAL"
                  :имя "value"
                  :ru "Значение интерлиньяжа (начальное значение = \\c 0)."
                  :en "Value of text leading (initially \\c 0)."))
 :режимы-графики '("Before" . "BRST_GMODE_PAGE_DESCRIPTION") ("After" . "BRST_GMODE_PAGE_DESCRIPTION"))

;; BRST_Page_SetFontAndSize
(:название "Page_SetFontAndSize"
 :группа "graphics"
 :ошибки ()
 :результат (:тип "STATUS"
              :ru ":return_ok"
              :en ":return_ok")
 :ru "Устанавливает шрифт и размер шрифта текущего текстового объекта."
 :en "Set the type of font and its size."
 :команда "Tf"
 :параметры ((:тип "Page"
                  :имя "page"
                  :ru ":param_page"
                  :en ":param_page")
                 (:тип "Font"
                  :имя "font"
                  :ru ":param_font"
                  :en ":param_font")
                 (:тип "REAL"
                  :имя "size"
                  :ru "Размер шрифта."
                  :en "Font size."))
 :режимы-графики '("Before" . "BRST_GMODE_PAGE_DESCRIPTION") ("After" . "BRST_GMODE_PAGE_DESCRIPTION"))

;; BRST_Page_SetTextRenderingMode
(:название "Page_SetTextRenderingMode"
 :группа "graphics"
 :ошибки ()
 :результат (:тип "STATUS"
              :ru ":return_ok"
              :en ":return_ok")
 :ru "Устанавливает режим рендеринга текста (заполнение, контур, обрезка и др.)."
 :en "Set text rendering mode."
 :команда "Tr"
 :параметры ((:тип "Page"
                  :имя "page"
                  :ru ":param_page"
                  :en ":param_page")
                 (:тип "TextRenderingMode"
                  :имя "mode"
                  :ru "Режим рендеринга текста (одно из значений):
 
  | Значение                       | Изображение              | Описание                                                |
  | --------                       | :---------:              | --------                                                |
  | \\ref BRST_FILL                 | \\image html rndmode1.png | Залить текст.                                            |
  | \\ref BRST_STROKE               | \\image html rndmode2.png | Обвести текст.                                           |
  | \\ref BRST_FILL_THEN_STROKE     | \\image html rndmode3.png | Залить, затем обвести текст.                             |
  | \\ref BRST_INVISIBLE            | &mdash;                  | Не заливать и не обводить текст (невидимый).             |
  | \\ref BRST_FILL_CLIPPING        | \\image html rndmode4.png | Залить текст и добавить путь в отсечение.                |
  | \\ref BRST_STROKE_CLIPPING      | \\image html rndmode5.png | Обвести текст и добавить путь в отсечение.               |
  | \\ref BRST_FILL_STROKE_CLIPPING | \\image html rndmode6.png | Залить, затем обвести текст и добавить путь в отсечение. |
  | \\ref BRST_CLIPPING             | &mdash;                  | Добавить текст в путь отсечения.                         |

  По умолчанию режим рендеринга \\c mode равен \\ref BRST_FILL.
"
                  :en "Text rendering mode.
                  
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

  Default \\c mode is \\ref BRST_FILL.
"))
 :режимы-графики '("Before" . "BRST_GMODE_PAGE_DESCRIPTION") ("After" . "BRST_GMODE_PAGE_DESCRIPTION"))

;; BRST_Page_SetTextRise
(:название "Page_SetTextRise"
 :группа "graphics"
 :ошибки ()
 :результат (:тип "STATUS"
              :ru ":return_ok"
              :en ":return_ok")
 :ru "Изменяет вертикальное положение строки относительно базовой линии.
 
  Полезно для создания верхних и нижних индексов."
 :en "Move text position vertically by given amount.
 
  Useful for making subscripts or superscripts."
 :команда "Ts"
 :параметры ((:тип "Page"
                  :имя "page"
                  :ru ":param_page"
                  :en ":param_page")
                 (:тип "REAL"
                  :имя "value"
                  :ru "Значение смещения вверх или вниз."
                  :en "Text rise, in user space units."))
 :режимы-графики '("Before" . "BRST_GMODE_PAGE_DESCRIPTION") ("After" . "BRST_GMODE_PAGE_DESCRIPTION"))

;; BRST_Page_MoveTextPos
(:название "Page_MoveTextPos"
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
 :параметры ((:тип "Page"
                  :имя "page"
                  :ru ":param_page"
                  :en ":param_page")
                 (:тип "REAL"
                  :имя "x"
                  :ru "Горизонтальное смещение."
                  :en "Offset to new text position along \\с x axis.")
                 (:тип "REAL"
                  :имя "y"
                  :ru "Вертикальное смещение."
                  :en "Offset to new text position along \\c y axis."))
 :режимы-графики '("Before" . "BRST_GMODE_TEXT_OBJECT") ("After" . "BRST_GMODE_TEXT_OBJECT"))

;; BRST_Page_MoveTextPos2
(:название "Page_MoveTextPos2"
 :группа "graphics"
 :ошибки ()
 :результат (:тип "STATUS"
              :ru ":return_ok"
              :en ":return_ok")
 :ru "Перемещает текущую позицию текста на указанное смещение и одновременно обновляет величину интерлиньяжа.
 
  Кроме того, интерлиньяж устанавливается в \\c -y."
 :en "Change current text position using specified offsets and update text leading simultaneously.
 
  Also, text leading is set to \\c -y."
 :команда "TD"
 :параметры ((:тип "Page"
                  :имя "page"
                  :ru ":param_page"
                  :en ":param_page")
                 (:тип "REAL"
                  :имя "x"
                  :ru "Горизонтальное смещение."
                  :en "Offset to new text position along X axis.")
                 (:тип "REAL"
                  :имя "y"
                  :ru "Вертикальное смещение."
                  :en "Offset to new text position along Y axis."))
 :режимы-графики '("Before" . "BRST_GMODE_TEXT_OBJECT") ("After" . "BRST_GMODE_TEXT_OBJECT"))

;; BRST_Page_SetTextMatrix
(:название "Page_SetTextMatrix"
 :группа "graphics"
 :ошибки ()
 :результат (:тип "STATUS"
              :ru ":return_ok"
              :en ":return_ok")
 :ru "Задает матрицу преобразования текста."
 :en "Set text transformation matrix."
 :команда "Tm"
 :параметры ((:тип "Page"
                  :имя "page"
                  :ru ":param_page"
                  :en ":param_page")
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
                  :en "Translation component along Y-axis."))
 :режимы-графики '("Before" . "BRST_GMODE_TEXT_OBJECT") ("After" . "BRST_GMODE_TEXT_OBJECT"))

;; BRST_Page_MoveToNextLine
(:название "Page_MoveToNextLine"
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
 :параметры ((:тип "Page"
                  :имя "page"
                  :ru ":param_page"
                  :en ":param_page")))

;; BRST_Page_ShowText
(:название "Page_ShowText"
 :группа "graphics"
 :ошибки ()
 :результат (:тип "STATUS"
              :ru ":return_ok"
              :en ":return_ok")
 :ru "Отображает текст в текущей позиции."
 :en "Put text at the current text position on the page."
 :команда "Tj"
 :параметры ((:тип "Page"
                  :имя "page"
                  :ru ":param_page"
                  :en ":param_page")
                 (:тип "CSTR"
                  :имя "text"
                  :ru "Строка текста."
                  :en "Text to display."))
 :режимы-графики '("Before" . "BRST_GMODE_TEXT_OBJECT") ("After" . "BRST_GMODE_TEXT_OBJECT"))

;; BRST_Page_ShowTextNextLine
(:название "Page_ShowTextNextLine"
 :группа "graphics"
 :ошибки ()
 :результат (:тип "STATUS"
              :ru ":return_ok"
              :en ":return_ok")
 :ru "Переходит к новой строке и отображает указанный текст."
 :en "Move current text position to the start of the next line, then shows the text."
 :команда "'"
 :параметры ((:тип "Page"
                  :имя "page"
                  :ru ":param_page"
                  :en ":param_page")
                 (:тип "CSTR"
                  :имя "text"
                  :ru "Строка текста"
                  :en "Text to display."))
 :режимы-графики '("Before" . "BRST_GMODE_TEXT_OBJECT") ("After" . "BRST_GMODE_TEXT_OBJECT"))

;; BRST_Page_ShowTextNextLineEx

(:название "Page_ShowTextNextLineEx"
 :группа "graphics"
 :ошибки ()
 :результат (:тип "STATUS"
              :ru ":return_ok"
              :en ":return_ok")
 :ru "Переходит к новой строке, задаёт межсловный и межсимвольный интервал и выводит текст."
 :en "Move current text position to the start of the next line, adjust word and character spacing, then puts the text."
 :команда "\""
 :параметры ((:тип "Page"
                  :имя "page"
                  :ru ":param_page"
                  :en ":param_page")
                 (:тип "REAL"
                  :имя "word_space"
                  :ru "Межсловный интервал."
                  :en "Word spacing value.")
                 (:тип "REAL"
                  :имя "char_space"
                  :ru "Межбуквенный интервал."
                  :en "Character spacing value.")
                 (:тип "CSTR"
                  :имя "text"
                  :ru "Строка текста."
                  :en "Text to display."))
 :режимы-графики '("Before" . "BRST_GMODE_TEXT_OBJECT") ("After" . "BRST_GMODE_TEXT_OBJECT"))

;; BRST_Page_TextOut
(:название "Page_TextOut"
 :группа "graphics"
 :ошибки ()
 :результат (:тип "STATUS"
              :ru ":return_ok"
              :en ":return_ok")
 :ru "Помещает текст в указанную позицию на странице."
 :en "Put text to the specified position."
 :параметры ((:тип "Page"
                  :имя "page"
                  :ru ":param_page"
                  :en ":param_page")
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
                  :en "Text to display."))
 :режимы-графики '("Before" . "BRST_GMODE_TEXT_OBJECT") ("After" . "BRST_GMODE_TEXT_OBJECT"))

;; BRST_Page_TextRect

(:название "Page_TextRect"
 :группа "graphics"
 :ошибки (("BRST_PAGE_INSUFFICIENT_SPACE"))
 :результат (:тип "STATUS"
              :ru "\\ref BRST_OK при успехе. Может вернуть \\ref BRST_PAGE_INSUFFICIENT_SPACE при успехе, но текст не вместился в заданное пространство.
  В противном случае возвращает код ошибки и вызывает обработчик ошибок."
              :en "\\ref BRST_OK on success. May return \\ref BRST_PAGE_INSUFFICIENT_SPACE on success but whole text doesn't fit into declared space.
  Otherwise, returns error code and calls error handler.")
 :ru "Отображает текст с выравниванием внутри заданного прямоугольника."
 :en "Put text inside the specified rectangle."
 :команда ""
 :параметры ((:тип "Page"
                  :имя "page"
                  :ru ":param_page"
                  :en ":param_page")
                 (:тип "REAL"
                  :имя "left"
                  :ru "Левая граница прямоугольной области."
                  :en "Left boundary of the rectangular area.")
                 (:тип "REAL"
                  :имя "top"
                  :ru "Верхняя граница прямоугольной области."
                  :en "Top boundary of the rectangular area.")
                 (:тип "REAL"
                  :имя "right"
                  :ru "Правая граница прямоугольной области."
                  :en "Right boundary of the rectangular area.")
                 (:тип "REAL"
                  :имя "bottom"
                  :ru "Нижняя граница прямоугольной области."
                  :en "Bottom boundary of the rectangular area.")
                 (:тип "CSTR"
                  :имя "text"
                  :ru "Строка текста"
                  :en "Text to display.")
                 (:тип "TextAlignment"
                  :имя "align"
                  :ru "\\parblock Выравнивание текста (одно из значений).
  | Value                    | Description                                                       |
  | -----                    | -----------                                                       |
  | \\ref BRST_TALIGN_LEFT    | The text is aligned to left.                                      |
  | \\ref BRST_TALIGN_RIGHT   | The text is aligned to right.                                     |
  | \\ref BRST_TALIGN_CENTER  | The text is aligned to center.                                    |
  | \\ref BRST_TALIGN_JUSTIFY | Add spaces between the words to justify both left and right side. |
  \\endparblock"
                  :en "\\parblock Text alignment (one of the following).

  | Value                    | Description                                                       |
  | -----                    | -----------                                                       |
  | \\ref BRST_TALIGN_LEFT    | The text is aligned to left.                                      |
  | \\ref BRST_TALIGN_RIGHT   | The text is aligned to right.                                     |
  | \\ref BRST_TALIGN_CENTER  | The text is aligned to center.                                    |
  | \\ref BRST_TALIGN_JUSTIFY | Add spaces between the words to justify both left and right side. |
  \\endparblock")
                 (:тип "UINT*"
                  :имя "len"
                  :ru "Адрес переменной, куда записывается количество выведенных символов. Если равно \\c NULL, значение не возвращается."
                  :en "If not \\c NULL, the number of characters printed in the area is returned.")
                  )
 :режимы-графики '("Before" . "BRST_GMODE_TEXT_OBJECT") ("After" . "BRST_GMODE_TEXT_OBJECT"))

;; BRST_Page_SetCharSpace
(:название "Page_SetCharSpace"
 :группа "graphics"
 :ошибки ()
 :результат (:тип "STATUS"
              :ru ":return_ok"
              :en ":return_ok")
 :ru "Устанавливает межбуквенный интервал."
 :en "Set text character spacing."
 :команда "Tc"
 :параметры ((:тип "Page"
                  :имя "page"
                  :ru ":param_page"
                  :en ":param_page")
                 (:тип "REAL"
                  :имя "value"
                  :ru "Межбуквенный интервал (начальное значение = \\c 0)."
                  :en "Character spacing value (initial value is \\c 0)."))
 :режимы-графики '("Before" . "BRST_GMODE_PAGE_DESCRIPTION") ("After" . "BRST_GMODE_PAGE_DESCRIPTION"))

;; BRST_Page_SetWordSpace
(:название "Page_SetWordSpace"
 :группа "graphics"
 :ошибки ()
 :результат (:тип "STATUS"
              :ru ":return_ok"
              :en ":return_ok")
 :ru "Устанавливает межсловный интервал."
 :en "Set text word spacing."
 :команда "Tw"
 :параметры ((:тип "Page"
                  :имя "page"
                  :ru ":param_page"
                  :en ":param_page")
                 (:тип "REAL"
                  :имя "value"
                  :ru "Межсловный интервал (начальное значение = \\c 0)."
                  :en "Word spacing value (initial value is \\c 0)."))
 :режимы-графики '("Before" . "BRST_GMODE_PAGE_DESCRIPTION") ("After" . "BRST_GMODE_PAGE_DESCRIPTION"))

