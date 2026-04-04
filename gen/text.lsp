(:file "text"
 :functions
       (
        ;; BRST_Page_BeginText
        (:caption "Page_BeginText"
         :group "graphics"
         :errors ()
         :result (:type "STATUS"
                     :ru ":return_ok"
                     :en ":return_ok")
         :ru "Начинает текстовый объект и устанавливает начальную позицию текста в точке `(0, 0)`."
         :en "Begins a text object and sets the initial text position to `(0, 0)`."
         :command "BT"
         :params ((:type "Page"
                      :name "page"
                      :ru ":param_page"
                      :en ":param_page"))
         :режимы-графики '("Before" . "BRST_GMODE_PAGE_DESCRIPTION") ("After" . "BRST_GMODE_TEXT_OBJECT"))

        ;; BRST_Page_EndText
        (:caption "Page_EndText"
         :group "graphics"
         :errors ()
         :result (:type "STATUS"
                     :ru ":return_ok"
                     :en ":return_ok")
         :ru "Заканчивает текстовый объект на странице."
         :en "Finish text object."
         :command "ET"
         :params ((:type "Page"
                      :name "page"
                      :ru ":param_page"
                      :en ":param_page"))
         :режимы-графики '("Before" . "BRST_GMODE_TEXT_OBJECT") ("After" . "BRST_GMODE_PAGE_DESCRIPTION"))

        ;; BRST_Page_SetTextLeading
        (:caption "Page_SetTextLeading"
         :group "graphics"
         :errors ()
         :result (:type "STATUS"
                     :ru ":return_ok"
                     :en ":return_ok")
         :ru "Устанавливает интерлиньяж (расстояния между базовыми линиями соседних строк)."
         :en "Set text leading (line spacing)."
         :command "TL"
         :params ((:type "Page"
                      :name "page"
                      :ru ":param_page"
                      :en ":param_page")
                     (:type "REAL"
                      :name "value"
                      :ru "Значение интерлиньяжа (начальное значение = \\c 0)."
                      :en "Value of text leading (initially \\c 0)."))
         :режимы-графики '("Before" . "BRST_GMODE_PAGE_DESCRIPTION") ("After" . "BRST_GMODE_PAGE_DESCRIPTION"))

        ;; BRST_Page_SetFontAndSize
        (:caption "Page_SetFontAndSize"
         :group "graphics"
         :errors ()
         :result (:type "STATUS"
                     :ru ":return_ok"
                     :en ":return_ok")
         :ru "Устанавливает шрифт и размер шрифта текущего текстового объекта."
         :en "Set the type of font and its size."
         :command "Tf"
         :params ((:type "Page"
                      :name "page"
                      :ru ":param_page"
                      :en ":param_page")
                     (:type "Font"
                      :name "font"
                      :ru ":param_font"
                      :en ":param_font")
                     (:type "REAL"
                      :name "size"
                      :ru "Размер шрифта."
                      :en "Font size."))
         :режимы-графики '("Before" . "BRST_GMODE_PAGE_DESCRIPTION") ("After" . "BRST_GMODE_PAGE_DESCRIPTION"))

        ;; BRST_Dict_SetFontAndSize
        (:caption "Dict_SetFontAndSize"
         :group "graphics"
         :errors ()
         :result (:type "STATUS"
                     :ru ":return_ok"
                     :en ":return_ok")
         :ru "Устанавливает шрифт и размер шрифта текущего текстового объекта."
         :en "Set the type of font and its size."
         :command "Tf"
         :params ((:type "Dict"
                      :name "dict"
                      :ru ":param_dict"
                      :en ":param_dict")
                     (:type "Font"
                      :name "font"
                      :ru ":param_font"
                      :en ":param_font")
                     (:type "REAL"
                      :name "size"
                      :ru "Размер шрифта."
                      :en "Font size.")))

        ;; BRST_Page_SetTextRenderingMode
        (:caption "Page_SetTextRenderingMode"
         :group "graphics"
         :errors ()
         :result (:type "STATUS"
                     :ru ":return_ok"
                     :en ":return_ok")
         :ru "Устанавливает режим рендеринга текста (заполнение, контур, обрезка и др.)."
         :en "Set text rendering mode."
         :command "Tr"
         :params ((:type "Page"
                      :name "page"
                      :ru ":param_page"
                      :en ":param_page")
                     (:type "TextRenderingMode"
                      :name "mode"
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
"))
         :режимы-графики '("Before" . "BRST_GMODE_PAGE_DESCRIPTION") ("After" . "BRST_GMODE_PAGE_DESCRIPTION"))

        ;; BRST_Page_SetTextRise
        (:caption "Page_SetTextRise"
         :group "graphics"
         :errors ()
         :result (:type "STATUS"
                     :ru ":return_ok"
                     :en ":return_ok")
         :ru "Изменяет вертикальное положение строки относительно базовой линии.

  Полезно для создания верхних и нижних индексов."
         :en "Move text position vertically by given amount.

  Useful for making subscripts or superscripts."
         :command "Ts"
         :params ((:type "Page"
                      :name "page"
                      :ru ":param_page"
                      :en ":param_page")
                     (:type "REAL"
                      :name "value"
                      :ru "Значение смещения вверх или вниз."
                      :en "Text rise, in user space units."))
         :режимы-графики '("Before" . "BRST_GMODE_PAGE_DESCRIPTION") ("After" . "BRST_GMODE_PAGE_DESCRIPTION"))

        ;; BRST_Page_MoveTextPos
        (:caption "Page_MoveTextPos"
         :group "graphics"
         :errors ()
         :result (:type "STATUS"
                     :ru ":return_ok"
                     :en ":return_ok")
         :ru "Перемещает текущую позицию текста на указанное смещение.

  Если текущая текстовая позиция (x<sub>1</sub>, y<sub>1</sub>), обновленная текстовая позиция будет равна (x<sub>1</sub> + x, y<sub>1</sub> + y)."
         :en "Change current text position using specified offsets.

  If the current text position is (x<sub>1</sub>, y<sub>1</sub>), the new text position will be (x<sub>1</sub> + x, y<sub>1</sub> + y)."
         :command "Td"
         :params ((:type "Page"
                      :name "page"
                      :ru ":param_page"
                      :en ":param_page")
                     (:type "REAL"
                      :name "x"
                      :ru "Горизонтальное смещение."
                      :en "Offset to new text position along \\с x axis.")
                     (:type "REAL"
                      :name "y"
                      :ru "Вертикальное смещение."
                      :en "Offset to new text position along \\c y axis."))
         :режимы-графики '("Before" . "BRST_GMODE_TEXT_OBJECT") ("After" . "BRST_GMODE_TEXT_OBJECT"))

        ;; BRST_Page_MoveTextPos2
        (:caption "Page_MoveTextPos2"
         :group "graphics"
         :errors ()
         :result (:type "STATUS"
                     :ru ":return_ok"
                     :en ":return_ok")
         :ru "Перемещает текущую позицию текста на указанное смещение и одновременно обновляет величину интерлиньяжа.

  Кроме того, интерлиньяж устанавливается в \\c -y."
         :en "Change current text position using specified offsets and update text leading simultaneously.

  Also, text leading is set to \\c -y."
         :command "TD"
         :params ((:type "Page"
                      :name "page"
                      :ru ":param_page"
                      :en ":param_page")
                     (:type "REAL"
                      :name "x"
                      :ru "Горизонтальное смещение."
                      :en "Offset to new text position along X axis.")
                     (:type "REAL"
                      :name "y"
                      :ru "Вертикальное смещение."
                      :en "Offset to new text position along Y axis."))
         :режимы-графики '("Before" . "BRST_GMODE_TEXT_OBJECT") ("After" . "BRST_GMODE_TEXT_OBJECT"))

        ;; BRST_Page_SetTextMatrix
        (:caption "Page_SetTextMatrix"
         :group "graphics"
         :errors ()
         :result (:type "STATUS"
                     :ru ":return_ok"
                     :en ":return_ok")
         :ru "Задает матрицу преобразования текста."
         :en "Set text transformation matrix."
         :command "Tm"
         :params ((:type "Page"
                      :name "page"
                      :ru ":param_page"
                      :en ":param_page")
                     (:type "REAL"
                      :name "a"
                      :ru "Элемент матрицы"
                      :en "First element of transformation matrix.")
                     (:type "REAL"
                      :name "b"
                      :ru "Элемент матрицы"
                      :en "Second element of transformation matrix.")
                     (:type "REAL"
                      :name "c"
                      :ru "Элемент матрицы"
                      :en "Third element of transformation matrix.")
                     (:type "REAL"
                      :name "d"
                      :ru "Элемент матрицы"
                      :en "Fourth element of transformation matrix.")
                     (:type "REAL"
                      :name "x"
                      :ru "Смещение по оси \\c x."
                      :en "Translation component along X-axis.")
                     (:type "REAL"
                      :name "y"
                      :ru "Смещение по оси \\c y."
                      :en "Translation component along Y-axis."))
         :режимы-графики '("Before" . "BRST_GMODE_TEXT_OBJECT") ("After" . "BRST_GMODE_TEXT_OBJECT"))

        ;; BRST_Page_MoveToNextLine
        (:caption "Page_MoveToNextLine"
         :group "graphics"
         :errors ()
         :result (:type "STATUS"
                     :ru ":return_ok"
                     :en ":return_ok")
         :ru "Переходит к следующей строке с учётом настроек интерлиньяжа.

  Положение текста вычисляется с учетом текущей матрицы преобразования текста."
         :en "Move current position for text showing to the beginning of the next line.

  New position is calculated with current text transition matrix."
         :command "T*"
         :params ((:type "Page"
                      :name "page"
                      :ru ":param_page"
                      :en ":param_page")))

        ;; BRST_Page_ShowText
        (:caption "Page_ShowText"
         :group "graphics"
         :errors ()
         :result (:type "STATUS"
                     :ru ":return_ok"
                     :en ":return_ok")
         :ru "Отображает текст в текущей позиции."
         :en "Put text at the current text position on the page."
         :command "Tj"
         :params ((:type "Page"
                      :name "page"
                      :ru ":param_page"
                      :en ":param_page")
                     (:type "CSTR"
                      :name "text"
                      :ru "Строка текста."
                      :en "Text to display."))
         :режимы-графики '("Before" . "BRST_GMODE_TEXT_OBJECT") ("After" . "BRST_GMODE_TEXT_OBJECT"))

        ;; BRST_Page_ShowTextNextLine
        (:caption "Page_ShowTextNextLine"
         :group "graphics"
         :errors ()
         :result (:type "STATUS"
                     :ru ":return_ok"
                     :en ":return_ok")
         :ru "Переходит к новой строке и отображает указанный текст."
         :en "Move current text position to the start of the next line, then shows the text."
         :command "'"
         :params ((:type "Page"
                      :name "page"
                      :ru ":param_page"
                      :en ":param_page")
                     (:type "CSTR"
                      :name "text"
                      :ru "Строка текста"
                      :en "Text to display."))
         :режимы-графики '("Before" . "BRST_GMODE_TEXT_OBJECT") ("After" . "BRST_GMODE_TEXT_OBJECT"))

        ;; BRST_Page_ShowTextNextLineEx

        (:caption "Page_ShowTextNextLineEx"
         :group "graphics"
         :errors ()
         :result (:type "STATUS"
                     :ru ":return_ok"
                     :en ":return_ok")
         :ru "Переходит к новой строке, задаёт межсловный и межсимвольный интервал и выводит текст."
         :en "Move current text position to the start of the next line, adjust word and character spacing, then puts the text."
         :command "\""
         :params ((:type "Page"
                      :name "page"
                      :ru ":param_page"
                      :en ":param_page")
                     (:type "REAL"
                      :name "word_space"
                      :ru "Межсловный интервал."
                      :en "Word spacing value.")
                     (:type "REAL"
                      :name "char_space"
                      :ru "Межбуквенный интервал."
                      :en "Character spacing value.")
                     (:type "CSTR"
                      :name "text"
                      :ru "Строка текста."
                      :en "Text to display."))
         :режимы-графики '("Before" . "BRST_GMODE_TEXT_OBJECT") ("After" . "BRST_GMODE_TEXT_OBJECT"))

        ;; BRST_Page_TextOut
        (:caption "Page_TextOut"
         :group "graphics"
         :errors ()
         :result (:type "STATUS"
                     :ru ":return_ok"
                     :en ":return_ok")
         :ru "Помещает текст в указанную позицию на странице."
         :en "Put text to the specified position."
         :params ((:type "Page"
                      :name "page"
                      :ru ":param_page"
                      :en ":param_page")
                     (:type "REAL"
                      :name "xpos"
                      :ru "Позиция по горизонтали"
                      :en "Horizontal position.")
                     (:type "REAL"
                      :name "ypos"
                      :ru "Позиция по вертикали"
                      :en "Vertical position.")
                     (:type "CSTR"
                      :name "text"
                      :ru "Строка текста"
                      :en "Text to display."))
         :режимы-графики '("Before" . "BRST_GMODE_TEXT_OBJECT") ("After" . "BRST_GMODE_TEXT_OBJECT"))

        ;; BRST_Page_TextRect

        (:caption "Page_TextRect"
         :group "graphics"
         :errors (("BRST_PAGE_INSUFFICIENT_SPACE"))
         :result (:type "STATUS"
                     :ru "\\ref BRST_OK при успешном выполнении. Может вернуть \\ref BRST_PAGE_INSUFFICIENT_SPACE при успешном выполнении, 
             но если текст не вместился в заданное пространство. В противном случае возвращает код ошибки и вызывает обработчик ошибок."
                     :en "\\ref BRST_OK on success. May return \\ref BRST_PAGE_INSUFFICIENT_SPACE on success but whole text does not fit into declared space.
  Otherwise, returns error code and calls error handler.")
         :ru "Отображает текст с выравниванием внутри заданного прямоугольника."
         :en "Put text inside the specified rectangle."
         :command ""
         :params ((:type "Page"
                      :name "page"
                      :ru ":param_page"
                      :en ":param_page")
                     (:type "REAL"
                      :name "left"
                      :ru "Левая граница прямоугольной области."
                      :en "Left boundary of the rectangular area.")
                     (:type "REAL"
                      :name "top"
                      :ru "Верхняя граница прямоугольной области."
                      :en "Top boundary of the rectangular area.")
                     (:type "REAL"
                      :name "right"
                      :ru "Правая граница прямоугольной области."
                      :en "Right boundary of the rectangular area.")
                     (:type "REAL"
                      :name "bottom"
                      :ru "Нижняя граница прямоугольной области."
                      :en "Bottom boundary of the rectangular area.")
                     (:type "CSTR"
                      :name "text"
                      :ru "Строка текста"
                      :en "Text to display.")
                     (:type "TextAlignment"
                      :name "align"
                      :ru "\\parblock Выравнивание текста (одно из значений).
  | Значение                 | Описание                                                                  |
  | --------                 | --------                                                                  |
  | \\ref BRST_TALIGN_LEFT    | Текст выравнивается влево.                                                |
  | \\ref BRST_TALIGN_RIGHT   | Текст выравнивается вправо.                                               |
  | \\ref BRST_TALIGN_CENTER  | Текст выравнивается по центру.                                            |
  | \\ref BRST_TALIGN_JUSTIFY | Добавляются пробелы между словами для выравнивания правой и левой границ. |
  \\endparblock"
                      :en "\\parblock Text alignment (one of the following).

  | Value                    | Description                                                       |
  | -----                    | -----------                                                       |
  | \\ref BRST_TALIGN_LEFT    | The text is aligned to left.                                      |
  | \\ref BRST_TALIGN_RIGHT   | The text is aligned to right.                                     |
  | \\ref BRST_TALIGN_CENTER  | The text is aligned to center.                                    |
  | \\ref BRST_TALIGN_JUSTIFY | Add spaces between the words to justify both left and right side. |
  \\endparblock")
                     (:type "UINT*"
                      :name "len"
                      :ru "Адрес переменной, куда записывается количество выведенных символов. Если равно \\c NULL, значение не возвращается."
                      :en "If not \\c NULL, the number of characters printed in the area is returned.")
                     )
         :режимы-графики '("Before" . "BRST_GMODE_TEXT_OBJECT") ("After" . "BRST_GMODE_TEXT_OBJECT"))

        ;; BRST_Page_SetCharSpace
        (:caption "Page_SetCharSpace"
         :group "graphics"
         :errors ()
         :result (:type "STATUS"
                     :ru ":return_ok"
                     :en ":return_ok")
         :ru "Устанавливает межбуквенный интервал."
         :en "Set text character spacing."
         :command "Tc"
         :params ((:type "Page"
                      :name "page"
                      :ru ":param_page"
                      :en ":param_page")
                     (:type "REAL"
                      :name "value"
                      :ru "Межбуквенный интервал (начальное значение = \\c 0)."
                      :en "Character spacing value (initial value is \\c 0)."))
         :режимы-графики '("Before" . "BRST_GMODE_PAGE_DESCRIPTION") ("After" . "BRST_GMODE_PAGE_DESCRIPTION"))

        ;; BRST_Page_SetWordSpace
        (:caption "Page_SetWordSpace"
         :group "graphics"
         :errors ()
         :result (:type "STATUS"
                     :ru ":return_ok"
                     :en ":return_ok")
         :ru "Устанавливает межсловный интервал."
         :en "Set text word spacing."
         :command "Tw"
         :params ((:type "Page"
                      :name "page"
                      :ru ":param_page"
                      :en ":param_page")
                     (:type "REAL"
                      :name "value"
                      :ru "Межсловный интервал (начальное значение = \\c 0)."
                      :en "Word spacing value (initial value is \\c 0)."))
         :режимы-графики '("Before" . "BRST_GMODE_PAGE_DESCRIPTION") ("After" . "BRST_GMODE_PAGE_DESCRIPTION"))


        ;; BRST_Page_TextMatrix
        (:caption "Page_TextMatrix"
         :group "page"
         :errors ()
         :result (:type "Matrix"
                     :ru "Матрица трансформации текста \\ref BRST_Matrix при успешном выполнении, иначе возвращается `BRST_Matrix{1, 0, 0, 1, 0, 0}`."
                     :en "Page current \\ref BRST_Matrix on success, otherwise it returns `BRST_Matrix{1, 0, 0, 1, 0, 0}`.")
         :ru "Получение текущей матрицы преобразования текста страницы."
         :en "Get page's current text transformation matrix."
         :params ((:type "Page"
                      :name "page"
                      :ru ":param_page"
                      :en ":param_page")))

        ;; BRST_Page_TextLeading
        (:caption "Page_TextLeading"
         :group "page"
         :errors ()
         :result (:type "REAL"
                     :ru "Текущий межстрочный интервал при успешном выполнении, иначе возвращается \\c 0."
                     :en "Page current text leading value on success, otherwise it returns \\c 0.")
         :ru "Получение величины межстрочного интервала (текущего интерлиньяжа)."
         :en "Get page's current text leading value."
         :params ((:type "Page"
                      :name "page"
                      :ru ":param_page"
                      :en ":param_page")))

        ;; BRST_Page_TextRenderingMode
        (:caption "Page_TextRenderingMode"
         :group "page"
         :errors ()
         :result (:type "TextRenderingMode"
                     :ru "Текущий режим рендеринга текста при успешном выполнении, иначе возвращается \\ref BRST_FILL."
                     :en "Current text rendering mode on success, otherwise it returns \\ref BRST_FILL.")
         :ru "Получение текущего режима рендеринга текста."
         :en "Get page's current text rendering mode."
         :params ((:type "Page"
                      :name "page"
                      :ru ":param_page"
                      :en ":param_page")))

        ;; BRST_Page_TextRise
        (:caption "Page_TextRise"
         :group "page"
         :errors ()
         :result (:type "REAL"
                     :ru "Текущее смещение текста по вертикали при успешном выполнении, иначе возвращается \\c 0."
                     :en "Current text rise value on success, otherwise it returns \\c 0.")
         :ru "Получение текущего вертикального смещения текста."
         :en "Get page's current text rise value."
         :params ((:type "Page"
                      :name "page"
                      :ru ":param_page"
                      :en ":param_page")))

        ;; BRST_Page_CharSpace

        (:caption "Page_CharSpace"
         :group "page"
         :errors ()
         :result (:type "REAL"
                     :ru "Текущее межсимвольное расстояние при успешном выполнении, иначе возвращается \\c 0."
                     :en "Current character spacing value on success, otherwise it returns \\c 0.")
         :ru "Получение текущего межсимвольного расстояния."
         :en "Get page's current character spacing value."
         :params ((:type "Page"
                      :name "page"
                      :ru ":param_page"
                      :en ":param_page")))

        ;; BRST_Page_WordSpace

        (:caption "Page_WordSpace"
         :group "page"
         :errors ()
         :result (:type "REAL"
                     :ru "Текущее межсловное расстояние при успешном выполнении, иначе возвращается \\c 0."
                     :en "Current word spacing value on success, otherwise it returns \\c 0.")
         :ru "Получение текущего межсловного расстояния."
         :en "Get page's current word spacing value."
         :params ((:type "Page"
                      :name "page"
                      :ru ":param_page"
                      :en ":param_page")))

        ;; BRST_Page_CurrentTextPos
;;        (:caption "Page_CurrentTextPos"
;;         :group "page"
;;         :errors ()
;;         :result (:type "Point"
;;                     :ru "Текущие координаты отображения текста в \\ref BRST_Point при успешном выполнении, иначе возвращается `BRST_Point{0, 0}`."
;;                     :en "\\ref BRST_Point struct with current position for text showing of the page. Otherwise it returns `BRST_Point{0, 0}`.")
;;         :ru "Получение текущих координат отображения текста."
;;         :en "Get page's current text position."
;;         :params ((:type "Page"
;;                      :name "page"
;;                      :ru ":param_page"
;;                      :en ":param_page")))

        ;; BRST_Page_CurrentTextPos2
        (:caption "Page_CurrentTextPos2"
         :group "page"
         :errors ()
         :result (:type "STATUS"
                     :ru ":return_ok"
                     :en ":return_ok")
         :ru "Записывает текущие координаты позиции текста в предоставленную переменную."
         :en "Store page's current text position into provided variable."
         :params ((:type "Page"
                      :name "page"
                      :ru ":param_page"
                      :en ":param_page")
                     (:type "Point*"
                      :name "pos"
                      :ru "Указатель на структуру для записи текущей позиции."
                      :en "Pointer to structure where to store current text position.")))

        ;; BRST_Page_CurrentFont
        (:caption "Page_CurrentFont"
         :group "page"
         :errors ()
         :result (:type "Font"
                     :ru "Текущий выбранный шрифт при успешном выполнении, иначе возвращается \\c NULL."
                     :en "Page current font handle on success, otherwise it returns \\c NULL.")
         :ru "Получение текущего выбранного шрифта."
         :en "Get page's current font handle."
         :params ((:type "Page"
                      :name "page"
                      :ru ":param_page"
                      :en ":param_page")))

        ;; BRST_Page_CurrentFontSize
        (:caption "Page_CurrentFontSize"
         :group "page"
         :errors ()
         :result (:type "REAL"
                     :ru "Текущий размер шрифта при успешном выполнении, иначе возвращается \\c 0."
                     :en "Page current font size on success, otherwise it returns \\c 0.")
         :ru "Получение текущего размера шрифта."
         :en "Get page's current font size."
         :params ((:type "Page"
                      :name "page"
                      :ru ":param_page"
                      :en ":param_page")))

        ;; BRST_Page_TextWidth
        (:caption "Page_TextWidth"
         :group "page"
         :errors ("BRST_INVALID_PAGE"
                  "BRST_FAILED_TO_ALLOC_MEM"
                  "BRST_PAGE_FONT_NOT_FOUND")
         :result (:type "REAL"
                     :ru "Ширина текста"
                     :en "Text width.")
         :ru "Получение ширины текста с учётом текущего шрифта, межбуквенного и межсимвольного расстояний."
         :en "Calculate text width based on current font settings."
         :params ((:type "Page"
                      :name "page"
                      :ru ":param_page"
                      :en ":param_page")
                     (:type "CSTR"
                      :name "text"
                      :ru "Измеряемый текст."
                      :en "Text to measure.")))

        ;; BRST_Page_MeasureText
        (:caption "Page_MeasureText"
         :group "page"
         :errors ("BRST_INVALID_PAGE"
                  "BRST_PAGE_FONT_NOT_FOUND")
         :result (:type "UINT"
                     :ru "Количество символов текста, помещающихся в заданную ширину"
                     :en "Character length that fits within specified width.")
         :ru "Измеряет количество символов, которое поместится в заданную область с учётом переноса слов."
         :en "Measure how many characters fit within specified width considering word wrapping."
         :params ((:type "Page"
                      :name "page"
                      :ru ":param_page"
                      :en ":param_page")
                     (:type "CSTR"
                      :name "text"
                      :ru "Измеряемый текст."
                      :en "Text to measure.")
                     (:type "REAL"
                      :name "width"
                      :ru "Максимальная ширина области."
                      :en "Maximum width of area.")
                     (:type "BOOL"
                      :name "wordwrap"
                      :ru "Флаг переноса слов.

  \\parblock При наличии трёх слов \\a \"ABCDE\", \\a \"FGH\" и \\a \"IJKL\", если подстрока до буквы \\a \"J\"
  умещается в пределах доступной ширины, то если параметр \\c word_wrap равен значению \\ref BRST_FALSE, 
  возвращается число 12. А если параметр \\c word_wrap установлен в значение \\ref BRST_TRUE, 
  тогда возвращается число 10 (длина предыдущего слова).

  \\image html img/measuretext.png"
                      :en "\\parblock Word wrap flag.
  When there are three words of \\a \"ABCDE\", \\a \"FGH\", and \\a \"IJKL\", and
  the substring until \\a \"J\" can be included within the width, if \\c word_wrap
  parameter is \\ref BRST_FALSE it returns \\c 12, and if \\c word_wrap parameter
  is \\ref BRST_TRUE, it returns \\c 10 (the end of the previous word).

  \\image html img/measuretext.png")
                     (:type "REAL*"
                      :name "real_width"
                      :ru "Указатель на переменную для записи ширины помещающегося текста."
                      :en "Optional pointer to store actual width of measured text."))
                   )))
