// license
#ifndef BRST_TEXT_H
#define BRST_TEXT_H

/**
  \ingroup graphics
  \brief Начинает текстовый объект и устанавливает начальную позицию текста в точке `(0, 0)`.

  \param page Описатель объекта страницы.

  \return \ref BRST_OK при успешном выполнении, иначе возвращает код ошибки и вызывает обработчик ошибок.
*/
BRST_EXPORT(BRST_STATUS)
BRST_Page_BeginText(
   BRST_Page page
);

/**
  \ingroup graphics
  \brief Заканчивает текстовый объект на странице.

  \param page Описатель объекта страницы.

  \return \ref BRST_OK при успешном выполнении, иначе возвращает код ошибки и вызывает обработчик ошибок.
*/
BRST_EXPORT(BRST_STATUS)
BRST_Page_EndText(
   BRST_Page page
);

/**
  \ingroup graphics
  \brief Устанавливает интерлиньяж (расстояния между базовыми линиями соседних строк).

  \param page Описатель объекта страницы.
  \param value Значение интерлиньяжа (начальное значение = \c 0).

  \return \ref BRST_OK при успешном выполнении, иначе возвращает код ошибки и вызывает обработчик ошибок.
*/
BRST_EXPORT(BRST_STATUS)
BRST_Page_SetTextLeading(
   BRST_Page page,
   BRST_REAL value
);

/**
  \ingroup graphics
  \brief Устанавливает шрифт и размер шрифта текущего текстового объекта.

  \param page Описатель объекта страницы.
  \param font Описатель объекта шрифта.
  \param size Размер шрифта.

  \return \ref BRST_OK при успешном выполнении, иначе возвращает код ошибки и вызывает обработчик ошибок.
*/
BRST_EXPORT(BRST_STATUS)
BRST_Page_SetFontAndSize(
   BRST_Page page,
   BRST_Font font,
   BRST_REAL size
);

/**
  \ingroup graphics
  \brief Устанавливает шрифт и размер шрифта текущего текстового объекта.

  \param dict Описатель объекта словаря.
  \param font Описатель объекта шрифта.
  \param size Размер шрифта.

  \return \ref BRST_OK при успешном выполнении, иначе возвращает код ошибки и вызывает обработчик ошибок.
*/
BRST_EXPORT(BRST_STATUS)
BRST_Dict_SetFontAndSize(
   BRST_Dict dict,
   BRST_Font font,
   BRST_REAL size
);

/**
  \ingroup graphics
  \brief Устанавливает режим рендеринга текста (заполнение, контур, обрезка и др.).

  \param page Описатель объекта страницы.
  \param mode \parblock Режим рендеринга текста (одно из значений):

  | Значение                       | Изображение              | Описание                                                 |
  | --------                       | :---------:              | --------                                                 |
  | \ref BRST_FILL                 | \image html rndmode1.png | Залить текст.                                            |
  | \ref BRST_STROKE               | \image html rndmode2.png | Обвести текст.                                           |
  | \ref BRST_FILL_THEN_STROKE     | \image html rndmode3.png | Залить, затем обвести текст.                             |
  | \ref BRST_INVISIBLE            | &mdash;                  | Не заливать и не обводить текст (невидимый).             |
  | \ref BRST_FILL_CLIPPING        | \image html rndmode4.png | Залить текст и добавить путь в отсечение.                |
  | \ref BRST_STROKE_CLIPPING      | \image html rndmode5.png | Обвести текст и добавить путь в отсечение.               |
  | \ref BRST_FILL_STROKE_CLIPPING | \image html rndmode6.png | Залить, затем обвести текст и добавить путь в отсечение. |
  | \ref BRST_CLIPPING             | &mdash;                  | Добавить текст в путь отсечения.                         |

  По умолчанию режим рендеринга \c mode равен \ref BRST_FILL. \endparblock


  \return \ref BRST_OK при успешном выполнении, иначе возвращает код ошибки и вызывает обработчик ошибок.
*/
BRST_EXPORT(BRST_STATUS)
BRST_Page_SetTextRenderingMode(
   BRST_Page page,
   BRST_TextRenderingMode mode
);

/**
  \ingroup graphics
  \brief Изменяет вертикальное положение строки относительно базовой линии.

  Полезно для создания верхних и нижних индексов.

  \param page Описатель объекта страницы.
  \param value Значение смещения вверх или вниз.

  \return \ref BRST_OK при успешном выполнении, иначе возвращает код ошибки и вызывает обработчик ошибок.
*/
BRST_EXPORT(BRST_STATUS)
BRST_Page_SetTextRise(
   BRST_Page page,
   BRST_REAL value
);

/**
  \ingroup graphics
  \brief Перемещает текущую позицию текста на указанное смещение.

  Если текущая текстовая позиция (x<sub>1</sub>, y<sub>1</sub>), обновленная текстовая позиция будет равна (x<sub>1</sub> + x, y<sub>1</sub> + y).

  \param page Описатель объекта страницы.
  \param x Горизонтальное смещение.
  \param y Вертикальное смещение.

  \return \ref BRST_OK при успешном выполнении, иначе возвращает код ошибки и вызывает обработчик ошибок.
*/
BRST_EXPORT(BRST_STATUS)
BRST_Page_MoveTextPos(
   BRST_Page page,
   BRST_REAL x,
   BRST_REAL y
);

/**
  \ingroup graphics
  \brief Перемещает текущую позицию текста на указанное смещение и одновременно обновляет величину интерлиньяжа.

  Кроме того, интерлиньяж устанавливается в \c -y.

  \param page Описатель объекта страницы.
  \param x Горизонтальное смещение.
  \param y Вертикальное смещение.

  \return \ref BRST_OK при успешном выполнении, иначе возвращает код ошибки и вызывает обработчик ошибок.
*/
BRST_EXPORT(BRST_STATUS)
BRST_Page_MoveTextPos2(
   BRST_Page page,
   BRST_REAL x,
   BRST_REAL y
);

/**
  \ingroup graphics
  \brief Задает матрицу преобразования текста.

  \param page Описатель объекта страницы.
  \param a Элемент матрицы
  \param b Элемент матрицы
  \param c Элемент матрицы
  \param d Элемент матрицы
  \param x Смещение по оси \c x.
  \param y Смещение по оси \c y.

  \return \ref BRST_OK при успешном выполнении, иначе возвращает код ошибки и вызывает обработчик ошибок.
*/
BRST_EXPORT(BRST_STATUS)
BRST_Page_SetTextMatrix(
   BRST_Page page,
   BRST_REAL a,
   BRST_REAL b,
   BRST_REAL c,
   BRST_REAL d,
   BRST_REAL x,
   BRST_REAL y
);

/**
  \ingroup graphics
  \brief Переходит к следующей строке с учётом настроек интерлиньяжа.

  Положение текста вычисляется с учетом текущей матрицы преобразования текста.

  \param page Описатель объекта страницы.

  \return \ref BRST_OK при успешном выполнении, иначе возвращает код ошибки и вызывает обработчик ошибок.
*/
BRST_EXPORT(BRST_STATUS)
BRST_Page_MoveToNextLine(
   BRST_Page page
);

/**
  \ingroup graphics
  \brief Отображает текст в текущей позиции.

  \param page Описатель объекта страницы.
  \param text Строка текста.

  \return \ref BRST_OK при успешном выполнении, иначе возвращает код ошибки и вызывает обработчик ошибок.
*/
BRST_EXPORT(BRST_STATUS)
BRST_Page_ShowText(
   BRST_Page page,
   BRST_CSTR text
);

/**
  \ingroup graphics
  \brief Переходит к новой строке и отображает указанный текст.

  \param page Описатель объекта страницы.
  \param text Строка текста

  \return \ref BRST_OK при успешном выполнении, иначе возвращает код ошибки и вызывает обработчик ошибок.
*/
BRST_EXPORT(BRST_STATUS)
BRST_Page_ShowTextNextLine(
   BRST_Page page,
   BRST_CSTR text
);

/**
  \ingroup graphics
  \brief Переходит к новой строке, задаёт межсловный и межсимвольный интервал и выводит текст.

  \param page Описатель объекта страницы.
  \param word_space Межсловный интервал.
  \param char_space Межбуквенный интервал.
  \param text Строка текста.

  \return \ref BRST_OK при успешном выполнении, иначе возвращает код ошибки и вызывает обработчик ошибок.
*/
BRST_EXPORT(BRST_STATUS)
BRST_Page_ShowTextNextLineEx(
   BRST_Page page,
   BRST_REAL word_space,
   BRST_REAL char_space,
   BRST_CSTR text
);

/**
  \ingroup graphics
  \brief Помещает текст в указанную позицию на странице.

  \param page Описатель объекта страницы.
  \param xpos Позиция по горизонтали
  \param ypos Позиция по вертикали
  \param text Строка текста

  \return \ref BRST_OK при успешном выполнении, иначе возвращает код ошибки и вызывает обработчик ошибок.
*/
BRST_EXPORT(BRST_STATUS)
BRST_Page_TextOut(
   BRST_Page page,
   BRST_REAL xpos,
   BRST_REAL ypos,
   BRST_CSTR text
);

/**
  \ingroup graphics
  \brief Отображает текст с выравниванием внутри заданного прямоугольника.

  \param page Описатель объекта страницы.
  \param left Левая граница прямоугольной области.
  \param top Верхняя граница прямоугольной области.
  \param right Правая граница прямоугольной области.
  \param bottom Нижняя граница прямоугольной области.
  \param text Строка текста
  \param align \parblock Выравнивание текста (одно из значений).
  | Значение                 | Описание                                                                  |
  | --------                 | --------                                                                  |
  | \ref BRST_TALIGN_LEFT    | Текст выравнивается влево.                                                |
  | \ref BRST_TALIGN_RIGHT   | Текст выравнивается вправо.                                               |
  | \ref BRST_TALIGN_CENTER  | Текст выравнивается по центру.                                            |
  | \ref BRST_TALIGN_JUSTIFY | Добавляются пробелы между словами для выравнивания правой и левой границ. |
  \endparblock
  \param len Адрес переменной, куда записывается количество выведенных символов. Если равно \c NULL, значение не возвращается.

  \return \ref BRST_OK при успешном выполнении. Может вернуть \ref BRST_PAGE_INSUFFICIENT_SPACE при успешном выполнении, 
             но если текст не вместился в заданное пространство. В противном случае возвращает код ошибки и вызывает обработчик ошибок.

  \par Коды ошибок
    - \ref {# Error: There was an error running filter PRE : In function CHAR-CODE, the value of the only argument is
  &quot;BRST_PAGE_INSUFFICIENT_SPACE&quot;
which is not of the expected type CHARACTER #}
*/
BRST_EXPORT(BRST_STATUS)
BRST_Page_TextRect(
   BRST_Page page,
   BRST_REAL left,
   BRST_REAL top,
   BRST_REAL right,
   BRST_REAL bottom,
   BRST_CSTR text,
   BRST_TextAlignment align,
   BRST_UINT* len
);

/**
  \ingroup graphics
  \brief Устанавливает межбуквенный интервал.

  \param page Описатель объекта страницы.
  \param value Межбуквенный интервал (начальное значение = \c 0).

  \return \ref BRST_OK при успешном выполнении, иначе возвращает код ошибки и вызывает обработчик ошибок.
*/
BRST_EXPORT(BRST_STATUS)
BRST_Page_SetCharSpace(
   BRST_Page page,
   BRST_REAL value
);

/**
  \ingroup graphics
  \brief Устанавливает межсловный интервал.

  \param page Описатель объекта страницы.
  \param value Межсловный интервал (начальное значение = \c 0).

  \return \ref BRST_OK при успешном выполнении, иначе возвращает код ошибки и вызывает обработчик ошибок.
*/
BRST_EXPORT(BRST_STATUS)
BRST_Page_SetWordSpace(
   BRST_Page page,
   BRST_REAL value
);

/**
  \ingroup page
  \brief Получение текущей матрицы преобразования текста страницы.

  \param page Описатель объекта страницы.

  \return Матрица трансформации текста \ref BRST_Matrix при успешном выполнении, иначе возвращается `BRST_Matrix{1, 0, 0, 1, 0, 0}`.
*/
BRST_EXPORT(BRST_Matrix)
BRST_Page_TextMatrix(
   BRST_Page page
);

/**
  \ingroup page
  \brief Получение величины межстрочного интервала (текущего интерлиньяжа).

  \param page Описатель объекта страницы.

  \return Текущий межстрочный интервал при успешном выполнении, иначе возвращается \c 0.
*/
BRST_EXPORT(BRST_REAL)
BRST_Page_TextLeading(
   BRST_Page page
);

/**
  \ingroup page
  \brief Получение текущего режима рендеринга текста.

  \param page Описатель объекта страницы.

  \return Текущий режим рендеринга текста при успешном выполнении, иначе возвращается \ref BRST_FILL.
*/
BRST_EXPORT(BRST_TextRenderingMode)
BRST_Page_TextRenderingMode(
   BRST_Page page
);

/**
  \ingroup page
  \brief Получение текущего вертикального смещения текста.

  \param page Описатель объекта страницы.

  \return Текущее смещение текста по вертикали при успешном выполнении, иначе возвращается \c 0.
*/
BRST_EXPORT(BRST_REAL)
BRST_Page_TextRise(
   BRST_Page page
);

/**
  \ingroup page
  \brief Получение текущего межсимвольного расстояния.

  \param page Описатель объекта страницы.

  \return Текущее межсимвольное расстояние при успешном выполнении, иначе возвращается \c 0.
*/
BRST_EXPORT(BRST_REAL)
BRST_Page_CharSpace(
   BRST_Page page
);

/**
  \ingroup page
  \brief Получение текущего межсловного расстояния.

  \param page Описатель объекта страницы.

  \return Текущее межсловное расстояние при успешном выполнении, иначе возвращается \c 0.
*/
BRST_EXPORT(BRST_REAL)
BRST_Page_WordSpace(
   BRST_Page page
);

/**
  \ingroup page
  \brief Записывает текущие координаты позиции текста в предоставленную переменную.

  \param page Описатель объекта страницы.
  \param pos Указатель на структуру для записи текущей позиции.

  \return \ref BRST_OK при успешном выполнении, иначе возвращает код ошибки и вызывает обработчик ошибок.
*/
BRST_EXPORT(BRST_STATUS)
BRST_Page_CurrentTextPos2(
   BRST_Page page,
   BRST_Point* pos
);

/**
  \ingroup page
  \brief Получение текущего выбранного шрифта.

  \param page Описатель объекта страницы.

  \return Текущий выбранный шрифт при успешном выполнении, иначе возвращается \c NULL.
*/
BRST_EXPORT(BRST_Font)
BRST_Page_CurrentFont(
   BRST_Page page
);

/**
  \ingroup page
  \brief Получение текущего размера шрифта.

  \param page Описатель объекта страницы.

  \return Текущий размер шрифта при успешном выполнении, иначе возвращается \c 0.
*/
BRST_EXPORT(BRST_REAL)
BRST_Page_CurrentFontSize(
   BRST_Page page
);

/**
  \ingroup page
  \brief Получение ширины текста с учётом текущего шрифта, межбуквенного и межсимвольного расстояний.

  \param page Описатель объекта страницы.
  \param text Измеряемый текст.

  \return Ширина текста

  \par Коды ошибок
    - \ref BRST_BRST_INVALID_PAGE
    - \ref BRST_BRST_FAILED_TO_ALLOC_MEM
    - \ref BRST_BRST_PAGE_FONT_NOT_FOUND
*/
BRST_EXPORT(BRST_REAL)
BRST_Page_TextWidth(
   BRST_Page page,
   BRST_CSTR text
);

/**
  \ingroup page
  \brief Измеряет количество символов, которое поместится в заданную область с учётом переноса слов.

  \param page Описатель объекта страницы.
  \param text Измеряемый текст.
  \param width Максимальная ширина области.
  \param wordwrap Флаг переноса слов.

  \parblock При наличии трёх слов \a "ABCDE", \a "FGH" и \a "IJKL", если подстрока до буквы \a "J"
  умещается в пределах доступной ширины, то если параметр \c word_wrap равен значению \ref BRST_FALSE, 
  возвращается число 12. А если параметр \c word_wrap установлен в значение \ref BRST_TRUE, 
  тогда возвращается число 10 (длина предыдущего слова).

  \image html img/measuretext.png
  \param real_width Указатель на переменную для записи ширины помещающегося текста.

  \return Количество символов текста, помещающихся в заданную ширину

  \par Коды ошибок
    - \ref BRST_BRST_INVALID_PAGE
    - \ref BRST_BRST_PAGE_FONT_NOT_FOUND
*/
BRST_EXPORT(BRST_UINT)
BRST_Page_MeasureText(
   BRST_Page page,
   BRST_CSTR text,
   BRST_REAL width,
   BRST_BOOL wordwrap,
   BRST_REAL* real_width
);

#endif /* BRST_TEXT_H */
