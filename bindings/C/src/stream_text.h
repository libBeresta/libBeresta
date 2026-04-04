// license
#ifndef BRST_STREAM_TEXT_H
#define BRST_STREAM_TEXT_H

/**
  \ingroup graphics
  \brief Начинает текстовый объект и устанавливает начальную позицию текста в точке `(0, 0)`.

  \param stream Описатель объекта потока.

  \return \ref BRST_OK при успешном выполнении, иначе возвращает код ошибки и вызывает обработчик ошибок.
*/
BRST_EXPORT(BRST_STATUS)
BRST_Stream_BeginText(
   BRST_Stream stream
);

/**
  \ingroup graphics
  \brief Заканчивает текстовый объект на странице.

  \param stream Описатель объекта потока.

  \return \ref BRST_OK при успешном выполнении, иначе возвращает код ошибки и вызывает обработчик ошибок.
*/
BRST_EXPORT(BRST_STATUS)
BRST_Stream_EndText(
   BRST_Stream stream
);

/**
  \ingroup graphics
  \brief Устанавливает интерлиньяж (расстояния между базовыми линиями соседних строк).

  \param stream Описатель объекта потока.
  \param value Значение интерлиньяжа (начальное значение = \c 0).

  \return \ref BRST_OK при успешном выполнении, иначе возвращает код ошибки и вызывает обработчик ошибок.
*/
BRST_EXPORT(BRST_STATUS)
BRST_Stream_SetTextLeading(
   BRST_Stream stream,
   BRST_REAL value
);

/**
  \ingroup graphics
  \brief Устанавливает режим рендеринга текста (заполнение, контур, обрезка и др.).

  \param stream Описатель объекта потока.
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
BRST_Stream_SetTextRenderingMode(
   BRST_Stream stream,
   BRST_TextRenderingMode mode
);

/**
  \ingroup graphics
  \brief Перемещает текущую позицию текста на указанное смещение.

  Если текущая текстовая позиция (x<sub>1</sub>, y<sub>1</sub>), обновленная текстовая позиция будет равна (x<sub>1</sub> + x, y<sub>1</sub> + y).

  \param stream Описатель объекта потока.
  \param x Горизонтальное смещение.
  \param y Вертикальное смещение.

  \return \ref BRST_OK при успешном выполнении, иначе возвращает код ошибки и вызывает обработчик ошибок.
*/
BRST_EXPORT(BRST_STATUS)
BRST_Stream_MoveTextPos(
   BRST_Stream stream,
   BRST_REAL x,
   BRST_REAL y
);

/**
  \ingroup graphics
  \brief Перемещает текущую позицию текста на указанное смещение.

  Если текущая текстовая позиция (x<sub>1</sub>, y<sub>1</sub>), обновленная текстовая позиция будет равна (x<sub>1</sub> + x, y<sub>1</sub> + y).

  \param stream Описатель объекта потока.
  \param x Горизонтальное смещение.
  \param y Вертикальное смещение.

  \return \ref BRST_OK при успешном выполнении, иначе возвращает код ошибки и вызывает обработчик ошибок.
*/
BRST_EXPORT(BRST_STATUS)
BRST_Stream_MoveTextPos2(
   BRST_Stream stream,
   BRST_REAL x,
   BRST_REAL y
);

/**
  \ingroup graphics
  \brief Задает матрицу преобразования текста.

  \param stream Описатель объекта потока.
  \param a Элемент матрицы
  \param b Элемент матрицы
  \param c Элемент матрицы
  \param d Элемент матрицы
  \param x Смещение по оси \c x.
  \param y Смещение по оси \c y.

  \return \ref BRST_OK при успешном выполнении, иначе возвращает код ошибки и вызывает обработчик ошибок.
*/
BRST_EXPORT(BRST_STATUS)
BRST_Stream_SetTextMatrix(
   BRST_Stream stream,
   BRST_REAL a,
   BRST_REAL b,
   BRST_REAL c,
   BRST_REAL d,
   BRST_REAL x,
   BRST_REAL y
);

/**
  \ingroup graphics
  \brief Отображает текст в текущей позиции.

  \param stream Описатель объекта потока.
  \param font Описатель объекта шрифта.
  \param text Строка текста.

  \return \ref BRST_OK при успешном выполнении, иначе возвращает код ошибки и вызывает обработчик ошибок.
*/
BRST_EXPORT(BRST_STATUS)
BRST_Stream_ShowText(
   BRST_Stream stream,
   BRST_Font font,
   BRST_CSTR text
);

/**
  \ingroup graphics
  \brief Помещает текст в указанную позицию на странице.

  \param stream Описатель объекта потока.
  \param font Описатель объекта шрифта.
  \param xpos Позиция по горизонтали
  \param ypos Позиция по вертикали
  \param text Строка текста

  \return \ref BRST_OK при успешном выполнении, иначе возвращает код ошибки и вызывает обработчик ошибок.
*/
BRST_EXPORT(BRST_STATUS)
BRST_Stream_TextOut(
   BRST_Stream stream,
   BRST_Font font,
   BRST_REAL xpos,
   BRST_REAL ypos,
   BRST_CSTR text
);

/**
  \ingroup graphics
  \brief Переходит к следующей строке с учётом настроек интерлиньяжа.

  Положение текста вычисляется с учетом текущей матрицы преобразования текста.

  \param stream Описатель объекта потока.

  \return \ref BRST_OK при успешном выполнении, иначе возвращает код ошибки и вызывает обработчик ошибок.
*/
BRST_EXPORT(BRST_STATUS)
BRST_Stream_MoveToNextLine(
   BRST_Stream stream
);

#endif /* BRST_STREAM_TEXT_H */
