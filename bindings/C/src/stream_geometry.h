// license
#ifndef BRST_STREAM_GEOMETRY_H
#define BRST_STREAM_GEOMETRY_H

/**
  \ingroup graphics
  \brief Сохранение в стек текущего графического состояния страницы.

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
    - Межсловный интервал

  \param page Описатель объекта потока.

  \return \ref BRST_OK при успешном выполнении, иначе возвращает код ошибки и вызывает обработчик ошибок.
*/
BRST_EXPORT(BRST_STATUS)
BRST_Stream_GSave(
   BRST_Stream page
);

/**
  \ingroup graphics
  \brief Восстановление графического состояния страницы, ранее сохраненного функцией BRST_Stream_GSave().

  \param page Описатель объекта потока.

  \return \ref BRST_OK при успешном выполнении, иначе возвращает код ошибки и вызывает обработчик ошибок.
*/
BRST_EXPORT(BRST_STATUS)
BRST_Stream_GRestore(
   BRST_Stream page
);

/**
  \ingroup graphics
  \brief Конкатенация указанной матрицы и матрицы преобразования страницы.

  Например, если вам нужно повернуть систему координат страницы на 45 градусов, функцию BRST_Stream_Concat() следует вызвать так:

  \code
  BRST_REAL rad = 45 / 180 * BRST_PI;
  BRST_Stream_Concat(page, cos(rad), sin(rad), -sin(rad), cos(rad), 0, 0);
  \endcode

  С помощью следующей команды можно изменить разрешение системы системы координат на 300 точек на дюйм (dpi):

  \code
  BRST_Stream_Concat(page, 72.0f / 300.0f, 0, 0, 72.0f / 300.0f, 0, 0);
  \endcode

  Перед вызовом функции BRST_Stream_Concat() рекомендуется сохранить текущее графическое состояние
  с помощью функции BRST_Stream_GSave(). Затем внесённые изменения можно отменить,
  восстановив предыдущее графическое состояние с помощью функции BRST_Stream_GRestore().

  \code
  // Сохраняем текущее состояние графики
  BRST_Stream_GSave(page);

  // Применяем матрицу преобразования
  BRST_Stream_Concat(page, 72.0f / 300.0f, 0, 0, 72.0f / 300.0f, 0, 0);

  // Показываем текст на с учетом изменения разрешения
  BRST_Stream_BeginText(page);
  BRST_Stream_MoveTextPos(page, 50, 100);
  BRST_Stream_ShowText(page, "Текст на трансформированных координатах");
  BRST_Stream_EndText(page);

  // Восстанавливаем предыдущее состояние графики
  BRST_Stream_GRestore(page);
  \endcode

  Функцию BRST_Stream_GSave() можно вызывать, когда установлен режим \ref BRST_GMODE_PAGE_DESCRIPTION.

  \param page Описатель объекта потока.
  \param a Параметр \c a матрицы преобразования.
  \param b Параметр \c b матрицы преобразования.
  \param c Параметр \c c матрицы преобразования.
  \param d Параметр \c d матрицы преобразования.
  \param x Параметр \c x матрицы преобразования.
  \param y Параметр \c y матрицы преобразования.

  \return \ref BRST_OK при успешном выполнении, иначе возвращает код ошибки и вызывает обработчик ошибок.
*/
BRST_EXPORT(BRST_STATUS)
BRST_Stream_Concat(
   BRST_Stream page,
   BRST_REAL a,
   BRST_REAL b,
   BRST_REAL c,
   BRST_REAL d,
   BRST_REAL x,
   BRST_REAL y
);

/**
  \ingroup graphics
  \brief Конкатенация матрицы переноса и матрицы преобразования страницы.

  Координатная система страницы переносится на \c dx координатных единиц по горизонтали
  и \c dy координатных единиц по вертикали.

  \param page Описатель объекта потока.
  \param dx Расстояние переноса координатной системы по горизонтали.
  \param dy Расстояние переноса координатной системы по вертикали.

  \return \ref BRST_OK при успешном выполнении, иначе возвращает код ошибки и вызывает обработчик ошибок.
*/
BRST_EXPORT(BRST_STATUS)
BRST_Stream_Translate(
   BRST_Stream page,
   BRST_REAL dx,
   BRST_REAL dy
);

/**
  \ingroup graphics
  \brief Конкатенация матрицы масштабирования и матрицы преобразования страницы.

  Масштаб системы координат изменяется так, что одна единица по горизонтали равна \c sx единицам
  и одна единица по вертикали равна \c sy единицам в новой системе координат.

  \param page Описатель объекта потока.
  \param sx Значение масштаба по горизонтали.
  \param sy Значение масштаба по вертикали.

  \return \ref BRST_OK при успешном выполнении, иначе возвращает код ошибки и вызывает обработчик ошибок.

  \see 
    BRST_Stream_Concat()
*/
BRST_EXPORT(BRST_STATUS)
BRST_Stream_Scale(
   BRST_Stream page,
   BRST_REAL sx,
   BRST_REAL sy
);

/**
  \ingroup graphics
  \brief Конкатенация матрицы поворота и матрицы преобразования страницы.

  Оси системы координат поворачиваются против часовой стрелки на угол \c degrees градусов.

  \param page Описатель объекта потока.
  \param degrees Угол поворота системы координат (градусы).

  \return \ref BRST_OK при успешном выполнении, иначе возвращает код ошибки и вызывает обработчик ошибок.

  \see 
    BRST_Stream_Concat()
    BRST_Stream_Rotate()
*/
BRST_EXPORT(BRST_STATUS)
BRST_Stream_RotateDeg(
   BRST_Stream page,
   BRST_REAL degrees
);

/**
  \ingroup graphics
  \brief Конкатенация матрицы поворота и матрицы преобразования страницы.

  Оси системы координат поворачиваются против часовой стрелки на угол \c degrees радиан.

  \param page Описатель объекта потока.
  \param radians Угол поворота системы координат (радианы).

  \return \ref BRST_OK при успешном выполнении, иначе возвращает код ошибки и вызывает обработчик ошибок.

  \see 
    BRST_Stream_Concat()
    BRST_Stream_RotateDeg()
*/
BRST_EXPORT(BRST_STATUS)
BRST_Stream_Rotate(
   BRST_Stream page,
   BRST_REAL radians
);

/**
  \ingroup graphics
  \brief Конкатенация матрицы наклона и матрицы преобразования страницы.

  Система координат наклоняется на угол \c a по оси \a x и на угол \c b по оси \a y.

  \param page Описатель объекта потока.
  \param a Угол наклона по оси \c x.
  \param b Угол наклона по оси \c у.

  \return \ref BRST_OK при успешном выполнении, иначе возвращает код ошибки и вызывает обработчик ошибок.

  \see 
    BRST_Stream_Concat()
*/
BRST_EXPORT(BRST_STATUS)
BRST_Stream_Skew(
   BRST_Stream page,
   BRST_REAL a,
   BRST_REAL b
);

/**
  \ingroup graphics
  \brief Добавление окружности к пути.

  \param page Описатель объекта потока.
  \param x Координата \c x центра окружности.
  \param y Координата \c y центра окружности.
  \param radius Радиус окружности.

  \return \ref BRST_OK при успешном выполнении, иначе возвращает код ошибки и вызывает обработчик ошибок.
*/
BRST_EXPORT(BRST_STATUS)
BRST_Stream_Circle(
   BRST_Stream page,
   BRST_REAL x,
   BRST_REAL y,
   BRST_REAL radius
);

/**
  \ingroup graphics
  \brief Установка цвета заливки (тона серого).

  \param page Описатель объекта потока.
  \param value Уровень серого цвета от \c 0.0 до \c 1.0.

  \return \ref BRST_OK при успешном выполнении, иначе возвращает код ошибки и вызывает обработчик ошибок.
*/
BRST_EXPORT(BRST_STATUS)
BRST_Stream_SetGrayFill(
   BRST_Stream page,
   BRST_REAL value
);

/**
  \ingroup graphics
  \brief Установка цвета линии (тона серого).

  \param page Описатель объекта потока.
  \param value Уровень серого цвета от \c 0.0 до \c 1.0.

  \return \ref BRST_OK при успешном выполнении, иначе возвращает код ошибки и вызывает обработчик ошибок.
*/
BRST_EXPORT(BRST_STATUS)
BRST_Stream_SetGrayStroke(
   BRST_Stream page,
   BRST_REAL value
);

/**
  \ingroup graphics
  \brief Установка цвета заливки (RGB).

  \param page Описатель объекта потока.
  \param r Уровень красного цвета от \c 0.0 до \c 1.0.
  \param g Уровень зеленого цвета от \c 0.0 до \c 1.0.
  \param b Уровень синего цвета от \c 0.0 до \c 1.0.

  \return \ref BRST_OK при успешном выполнении, иначе возвращает код ошибки и вызывает обработчик ошибок.
*/
BRST_EXPORT(BRST_STATUS)
BRST_Stream_SetRGBFill(
   BRST_Stream page,
   BRST_REAL r,
   BRST_REAL g,
   BRST_REAL b
);

/**
  \ingroup graphics
  \brief Установка цвета заливки (RGB) с использованием значений типа \ref BRST_UINT8.

  \param page Описатель объекта потока.
  \param r Уровень красного цвета от \c 0 до \c 255.
  \param g Уровень зеленого цвета от \c 0 до \c 255.
  \param b Уровень синего цвета от \c 0 до \c 255.

  \return \ref BRST_OK при успешном выполнении, иначе возвращает код ошибки и вызывает обработчик ошибок.
*/
BRST_EXPORT(BRST_STATUS)
BRST_Stream_SetRGBFillUint(
   BRST_Stream page,
   BRST_UINT8 r,
   BRST_UINT8 g,
   BRST_UINT8 b
);

/**
  \ingroup graphics
  \brief Установка цвета заливки (RGB) с использованием значения типа \ref BRST_UINT32.

  \param page Описатель объекта потока.
  \param rgb Значения цветов RGB задаются в трех байтах 32-битного беззнакового числа.
  Синий задается битами 0-7, зеленый битами 8-15, красный битами 16-23.
  Это соответствует битовым маскам \c 0xFF, \c 0xFF00 и \c 0xFF0000 соответственно.

  \return \ref BRST_OK при успешном выполнении, иначе возвращает код ошибки и вызывает обработчик ошибок.
*/
BRST_EXPORT(BRST_STATUS)
BRST_Stream_SetRGBFillHex(
   BRST_Stream page,
   BRST_UINT32 rgb
);

/**
  \ingroup graphics
  \brief Установка цвета линии (RGB).

  \param page Описатель объекта потока.
  \param r Уровень красного цвета от \c 0.0 до \c 1.0.
  \param g Уровень зеленого цвета от \c 0.0 до \c 1.0.
  \param b Уровень синего цвета от \c 0.0 до \c 1.0.

  \return \ref BRST_OK при успешном выполнении, иначе возвращает код ошибки и вызывает обработчик ошибок.
*/
BRST_EXPORT(BRST_STATUS)
BRST_Stream_SetRGBStroke(
   BRST_Stream page,
   BRST_REAL r,
   BRST_REAL g,
   BRST_REAL b
);

/**
  \ingroup graphics
  \brief Установка цвета линии (RGB) с использованием значений типа \ref BRST_UINT8.

  \param page Описатель объекта потока.
  \param r Уровень красного цвета от \c 0 до \c 255.
  \param g Уровень зеленого цвета от \c 0 до \c 255.
  \param b Уровень синего цвета от \c 0 до \c 255.

  \return \ref BRST_OK при успешном выполнении, иначе возвращает код ошибки и вызывает обработчик ошибок.
*/
BRST_EXPORT(BRST_STATUS)
BRST_Stream_SetRGBStrokeUint(
   BRST_Stream page,
   BRST_UINT8 r,
   BRST_UINT8 g,
   BRST_UINT8 b
);

/**
  \ingroup graphics
  \brief Установка цвета линии (RGB) с использованием значения типа \ref BRST_UINT32.

  \param page Описатель объекта потока.
  \param rgb Значения цветов RGB задаются в трех байтах 32-битного беззнакового числа.
  Синий задается битами 0-7, зеленый битами 8-15, красный битами 16-23.
  Это соответствует битовым маскам \c 0xFF, \c 0xFF00 и \c 0xFF0000 соответственно.

  \return \ref BRST_OK при успешном выполнении, иначе возвращает код ошибки и вызывает обработчик ошибок.
*/
BRST_EXPORT(BRST_STATUS)
BRST_Stream_SetRGBStrokeHex(
   BRST_Stream page,
   BRST_UINT32 rgb
);

/**
  \ingroup graphics
  \brief Установка цвета заливки (CMYK).

  \param page Описатель объекта потока.
  \param c Уровень синего (cyan) цвета от \c 0.0 до \c 1.0.
  \param m Уровень пурпурного (magenta) цвета от \c 0.0 до \c 1.0.
  \param y Уровень желтого (yellow) цвета от \c 0.0 до \c 1.0.
  \param k Уровень черного (blacK) цвета от \c 0.0 до \c 1.0.

  \return \ref BRST_OK при успешном выполнении, иначе возвращает код ошибки и вызывает обработчик ошибок.
*/
BRST_EXPORT(BRST_STATUS)
BRST_Stream_SetCMYKFill(
   BRST_Stream page,
   BRST_REAL c,
   BRST_REAL m,
   BRST_REAL y,
   BRST_REAL k
);

/**
  \ingroup graphics
  \brief Установка цвета линии (CMYK).

  \param page Описатель объекта потока.
  \param c Уровень синего (cyan) цвета от \c 0.0 до \c 1.0.
  \param m Уровень пурпурного (magenta) цвета от \c 0.0 до \c 1.0.
  \param y Уровень желтого (yellow) цвета от \c 0.0 до \c 1.0.
  \param k Уровень черного (blacK) цвета от \c 0.0 до \c 1.0.

  \return \ref BRST_OK при успешном выполнении, иначе возвращает код ошибки и вызывает обработчик ошибок.
*/
BRST_EXPORT(BRST_STATUS)
BRST_Stream_SetCMYKStroke(
   BRST_Stream page,
   BRST_REAL c,
   BRST_REAL m,
   BRST_REAL y,
   BRST_REAL k
);

/**
  \ingroup graphics
  \brief Изменение текущей область отсечения, пересечение её с текущим путём, что определяет внутренние регионы
  области отсечения с применением правила ненулевого счёта обхода (nonzero winding number rule).

  Область отсечения изменяется только после следующего оператора рисования.Чтобы избежать рисования текущего пути, используйте функцию BRST_Stream_EndPath().

  Все последующие операции рисования будут влиять только на области страницы, входящие в пределы области отсечения.
  Первоначально область отсечения включает всю страницу.
  Увеличить или заменить новой областью отсечения Текущую область отсечения нельзя.
  Функции BRST_Stream_GSave() и BRST_Stream_GRestore() позволяют сохранять и восстанавливать
  текущее графическое состояние, включая область отсечения.

  \param page Описатель объекта потока.

  \return \ref BRST_OK при успешном выполнении, иначе возвращает код ошибки и вызывает обработчик ошибок.

  \see 
    BRST_Stream_EndPath()
    BRST_Stream_GSave()
    BRST_Stream_GRestore()
    BRST_Stream_Eoclip()
*/
BRST_EXPORT(BRST_STATUS)
BRST_Stream_Clip(
   BRST_Stream page
);

/**
  \ingroup graphics
  \brief Изменение текущей область отсечения, пересечение её с текущим путём, что определяет внутренние регионы
  области отсечения с применением правила чётный-нечётный (even-odd rule).

    Область отсечения изменяется только после следующего оператора рисования.Чтобы избежать рисования текущего пути, используйте функцию BRST_Stream_EndPath().

  Все последующие операции рисования будут влиять только на области страницы, входящие в пределы области отсечения.
  Первоначально область отсечения включает всю страницу.
  Увеличить или заменить новой областью отсечения Текущую область отсечения нельзя.
  Функции BRST_Stream_GSave() и BRST_Stream_GRestore() позволяют сохранять и восстанавливать
  текущее графическое состояние, включая область отсечения.

  \param page Описатель объекта потока.

  \return \ref BRST_OK при успешном выполнении, иначе возвращает код ошибки и вызывает обработчик ошибок.

  \see 
    BRST_Stream_EndPath()
    BRST_Stream_GSave()
    BRST_Stream_GRestore()
    BRST_Stream_Clip()
*/
BRST_EXPORT(BRST_STATUS)
BRST_Stream_Eoclip(
   BRST_Stream page
);

/**
  \ingroup graphics
  \brief Отображение текущего пути.

  \param page Описатель объекта потока.

  \return \ref BRST_OK при успешном выполнении, иначе возвращает код ошибки и вызывает обработчик ошибок.
*/
BRST_EXPORT(BRST_STATUS)
BRST_Stream_Stroke(
   BRST_Stream page
);

/**
  \ingroup graphics
  \brief Закрытие и отображение текущего пути.

  \param page Описатель объекта потока.

  \return \ref BRST_OK при успешном выполнении, иначе возвращает код ошибки и вызывает обработчик ошибок.
*/
BRST_EXPORT(BRST_STATUS)
BRST_Stream_ClosePathStroke(
   BRST_Stream page
);

/**
  \ingroup graphics
  \brief Заполнение текущего пути с применением правила ненулевого счёта обхода.

  \param page Описатель объекта потока.

  \return \ref BRST_OK при успешном выполнении, иначе возвращает код ошибки и вызывает обработчик ошибок.
*/
BRST_EXPORT(BRST_STATUS)
BRST_Stream_Fill(
   BRST_Stream page
);

/**
  \ingroup graphics
  \brief Заполнение текущего пути с применением правила чётный-нечётный.

  \param page Описатель объекта потока.

  \return \ref BRST_OK при успешном выполнении, иначе возвращает код ошибки и вызывает обработчик ошибок.
*/
BRST_EXPORT(BRST_STATUS)
BRST_Stream_Eofill(
   BRST_Stream page
);

/**
  \ingroup graphics
  \brief Заполнение текущего пути с применением правила ненулевого счёта обхода с последующим отображением пути.

  \param page Описатель объекта потока.

  \return \ref BRST_OK при успешном выполнении, иначе возвращает код ошибки и вызывает обработчик ошибок.
*/
BRST_EXPORT(BRST_STATUS)
BRST_Stream_FillStroke(
   BRST_Stream page
);

/**
  \ingroup graphics
  \brief Заполнение текущего пути с применением правила чётный-нечётный с последующим отображением пути.

  \param page Описатель объекта потока.

  \return \ref BRST_OK при успешном выполнении, иначе возвращает код ошибки и вызывает обработчик ошибок.
*/
BRST_EXPORT(BRST_STATUS)
BRST_Stream_EofillStroke(
   BRST_Stream page
);

/**
  \ingroup graphics
  \brief Закрытие пути, заполнение текущего пути с применением правила ненулевого счёта обхода с последующим отображением пути.

  \param page Описатель объекта потока.

  \return \ref BRST_OK при успешном выполнении, иначе возвращает код ошибки и вызывает обработчик ошибок.
*/
BRST_EXPORT(BRST_STATUS)
BRST_Stream_ClosePathFillStroke(
   BRST_Stream page
);

/**
  \ingroup graphics
  \brief Закрытие пути, заполнение текущего пути с применением правила чётный-нечётный с последующим отображением пути.

  \param page Описатель объекта потока.

  \return \ref BRST_OK при успешном выполнении, иначе возвращает код ошибки и вызывает обработчик ошибок.
*/
BRST_EXPORT(BRST_STATUS)
BRST_Stream_ClosePathEofillStroke(
   BRST_Stream page
);

/**
  \ingroup graphics
  \brief Окончание пути без заполнения и отображения.

  \param page Описатель объекта потока.

  \return \ref BRST_OK при успешном выполнении, иначе возвращает код ошибки и вызывает обработчик ошибок.
*/
BRST_EXPORT(BRST_STATUS)
BRST_Stream_EndPath(
   BRST_Stream page
);

/**
  \ingroup graphics
  \brief Начало нового подпути с переносом текущей точки отображения путей.

  \param page Описатель объекта потока.
  \param x Координата \c x начальной точки отображения пути.
  \param y Координата \c y начальной точки отображения пути.

  \return \ref BRST_OK при успешном выполнении, иначе возвращает код ошибки и вызывает обработчик ошибок.
*/
BRST_EXPORT(BRST_STATUS)
BRST_Stream_MoveTo(
   BRST_Stream page,
   BRST_REAL x,
   BRST_REAL y
);

/**
  \ingroup graphics
  \brief Добавление отрезка прямой из текущей точки в точку с координатами `(x, y)` как подпуть текущего пути.
        Точка `(x, y)` становится текущей для отображения путей.

  \param page Описатель объекта потока.
  \param x Координата \c x целевой (конечной) точки добавляемого отрезка.
  \param y Координата \c y целевой (конечной) точки добавляемого отрезка.

  \return \ref BRST_OK при успешном выполнении, иначе возвращает код ошибки и вызывает обработчик ошибок.
*/
BRST_EXPORT(BRST_STATUS)
BRST_Stream_LineTo(
   BRST_Stream page,
   BRST_REAL x,
   BRST_REAL y
);

/**
  \ingroup graphics
  \brief Добавление кубической кривой Безье с использованием контрольных точек (x<sub>1</sub>, y<sub>1</sub>), (x<sub>2</sub>, y<sub>2</sub>)
  и (x<sub>3</sub>, y<sub>3</sub>). Точка (x<sub>3</sub>, y<sub>3</sub>) становится текущей для отображения путей.

  \image html img/curveto.png.

  \param page Описатель объекта потока.
  \param x1 Координата \c x первой контрольной точки кубической кривой Безье.
  \param y1 Координата \c y первой контрольной точки кубической кривой Безье.
  \param x2 Координата \c x второй контрольной точки кубической кривой Безье.
  \param y2 Координата \c y второй контрольной точки кубической кривой Безье.
  \param x3 Координата \c x третьей контрольной точки кубической кривой Безье.
  \param y3 Координата \c y третьей контрольной точки кубической кривой Безье.

  \return \ref BRST_OK при успешном выполнении, иначе возвращает код ошибки и вызывает обработчик ошибок.
*/
BRST_EXPORT(BRST_STATUS)
BRST_Stream_CurveTo(
   BRST_Stream page,
   BRST_REAL x1,
   BRST_REAL y1,
   BRST_REAL x2,
   BRST_REAL y2,
   BRST_REAL x3,
   BRST_REAL y3
);

/**
  \ingroup graphics
  \brief Добавление кубической кривой Безье с использованием контрольных точек (x<sub>2</sub>, y<sub>2</sub>)
  и (x<sub>3</sub>, y<sub>3</sub>). Точка (x<sub>3</sub>, y<sub>3</sub>) становится текущей для отображения путей.
  \image html img/curveto2.png

  \param page Описатель объекта потока.
  \param x2 Координата \c x второй контрольной точки кубической кривой Безье.
  \param y2 Координата \c y второй контрольной точки кубической кривой Безье.
  \param x3 Координата \c x третьей контрольной точки кубической кривой Безье.
  \param y3 Координата \c y третьей контрольной точки кубической кривой Безье.

  \return \ref BRST_OK при успешном выполнении, иначе возвращает код ошибки и вызывает обработчик ошибок.
*/
BRST_EXPORT(BRST_STATUS)
BRST_Stream_CurveTo2(
   BRST_Stream page,
   BRST_REAL x2,
   BRST_REAL y2,
   BRST_REAL x3,
   BRST_REAL y3
);

/**
  \ingroup graphics
  \brief Добавление кубической кривой Безье с использованием контрольных точек (x<sub>1</sub>, y<sub>1</sub>)
  и (x<sub>3</sub>, y<sub>3</sub>). Точка (x<sub>3</sub>, y<sub>3</sub>) становится текущей для отображения путей.

  \image html img/curveto3.png.

  \param page Описатель объекта потока.
  \param x1 Координата \c x первой контрольной точки кубической кривой Безье.
  \param y1 Координата \c y первой контрольной точки кубической кривой Безье.
  \param x3 Координата \c x третьей контрольной точки кубической кривой Безье.
  \param y3 Координата \c y третьей контрольной точки кубической кривой Безье.

  \return \ref BRST_OK при успешном выполнении, иначе возвращает код ошибки и вызывает обработчик ошибок.
*/
BRST_EXPORT(BRST_STATUS)
BRST_Stream_CurveTo3(
   BRST_Stream page,
   BRST_REAL x1,
   BRST_REAL y1,
   BRST_REAL x3,
   BRST_REAL y3
);

/**
  \ingroup graphics
  \brief Закрытие текущего подпути добавлением отрезка из текущей точки в начальную точку подпути.

  \param page Описатель объекта потока.

  \return \ref BRST_OK при успешном выполнении, иначе возвращает код ошибки и вызывает обработчик ошибок.
*/
BRST_EXPORT(BRST_STATUS)
BRST_Stream_ClosePath(
   BRST_Stream page
);

/**
  \ingroup graphics
  \brief Добавление прямоугольника к текущему пути в качестве самостоятельного подпути.
  У прямоугольника левый нижний угол расположен в точке `(x, y)` и измерениями \c width и \c height.

  \param page Описатель объекта потока.
  \param x Координата \c x левого нижнего угла прямоугольника.
  \param y Координата \c y левого нижнего угла прямоугольника.
  \param width Ширина прямоугольника.
  \param height Высота прямоугольника.

  \return \ref BRST_OK при успешном выполнении, иначе возвращает код ошибки и вызывает обработчик ошибок.
*/
BRST_EXPORT(BRST_STATUS)
BRST_Stream_Rectangle(
   BRST_Stream page,
   BRST_REAL x,
   BRST_REAL y,
   BRST_REAL width,
   BRST_REAL height
);

/**
  \ingroup graphics
  \brief Установка толщины линии для отображения путей.

  \param page Описатель объекта потока.
  \param line_width Толщина линии для отображения путей. По умолчанию равна \c 1.0.

  \return \ref BRST_OK при успешном выполнении, иначе возвращает код ошибки и вызывает обработчик ошибок.
*/
BRST_EXPORT(BRST_STATUS)
BRST_Stream_SetLineWidth(
   BRST_Stream page,
   BRST_REAL line_width
);

/**
  \ingroup graphics
  \brief Установка стиля окончания линии.

  \param page Описатель объекта потока.
  \param line_cap Стиль окончания линии (одно из значений):

  | Значение                         | Изображение               | Описание                                                                  |
  | --------                         | -----------               | --------                                                                  |
  | \ref BRST_BUTT_END               | \image html linecap1.png  | Линия заканчивается прямоугольником в конечной точке.                     |
  | \ref BRST_ROUND_END              | \image html linecap2.png  | Линия заканчивается полуокружностью с центром в конечной точке.           |
  | \ref BRST_PROJECTING_SQUARE_END  | \image html linecap3.png  | Линия продолжается, выступая за конечную точку на половину толщины линии. |

  По умолчанию стиль окончания линии \c line_cap равен \ref BRST_BUTT_END

  \return \ref BRST_OK при успешном выполнении, иначе возвращает код ошибки и вызывает обработчик ошибок.
*/
BRST_EXPORT(BRST_STATUS)
BRST_Stream_SetLineCap(
   BRST_Stream page,
   BRST_LineCap line_cap
);

/**
  \ingroup graphics
  \brief Установка стиля стыка линий.

  \param page Описатель объекта потока.
  \param line_join Стиль стыка линий (одно из значений).

  | Значение              | Изображение                | Описание                                                                                             |
  | --------              | -----------                | --------                                                                                             |
  | \ref BRST_MITER_JOIN  | \image html linejoin1.png  | Внешние грани линии двух сегментов продлеваются, пока не встретятся под углом.                       |
  | \ref BRST_ROUND_JOIN  | \image html linejoin2.png  | Из точки пересечения двух сегментов проводится дуга окружности, диаметр которой равен толщине линии. |
  | \ref BRST_BEVEL_JOIN  | \image html linejoin3.png  | Оба сегмента заканчиваются прямоугольным окончанием, получившаяся выемка заполняется треугольником.  |

  По умолчанию стиль стыка линий \c line_join равен \ref BRST_MITER_JOIN.

  \return \ref BRST_OK при успешном выполнении, иначе возвращает код ошибки и вызывает обработчик ошибок.
*/
BRST_EXPORT(BRST_STATUS)
BRST_Stream_SetLineJoin(
   BRST_Stream page,
   BRST_LineJoin line_join
);

/**
  \ingroup graphics
  \brief Установка предельного значения острого угла линии для пересечений.
  Предельное значение острого угла (miter limit) равное \c 1.414, превращает острые углы соединения в скос при угле меньше \c 90 градусов.
  Ограничение 2.0 делает это для углов меньше \c 60 градусов, а ограничение 10.0 действует для углов менее \c 11.5 градусов.

  \param page Описатель объекта потока.
  \param miter_limit Предельное значение острого угла линии.

  \return \ref BRST_OK при успешном выполнении, иначе возвращает код ошибки и вызывает обработчик ошибок.
*/
BRST_EXPORT(BRST_STATUS)
BRST_Stream_SetMiterLimit(
   BRST_Stream page,
   BRST_REAL miter_limit
);

/**
  \ingroup graphics
  \brief Устанавливает шаблон пунктира линий.

  \par Примеры

  `dash_ptn = NULL`, `num_elem = 0`, `phase = 0` (по умолчанию для новой страницы)

  \image html setdash1.png

  `dash_ptn = [3]`, `num_elem = 1`, `phase = 1`

  \image html setdash2.png

  `dash_ptn = [7,]`, `num_elem = 2`, `phase = 2`

  \image html setdash3.png

  `dash_ptn = [8,]`, `num_elem = 4`, `phase = 0`

  \image html setdash4.png

  \param page Описатель объекта потока.
  \param dash_pattern 
  \param num_elem 
  \param phase 

  \return \ref BRST_OK при успешном выполнении, иначе возвращает код ошибки и вызывает обработчик ошибок.
*/
BRST_EXPORT(BRST_STATUS)
BRST_Stream_SetDash(
   BRST_Stream page,
   BRST_DASH_PATTERN dash_pattern,
   BRST_UINT num_elem,
   BRST_REAL phase
);

/**
  \ingroup graphics
  \brief 

  \param page Описатель объекта потока.
  \param flatness 

  \return \ref BRST_OK при успешном выполнении, иначе возвращает код ошибки и вызывает обработчик ошибок.
*/
BRST_EXPORT(BRST_STATUS)
BRST_Stream_SetFlat(
   BRST_Stream page,
   BRST_REAL flatness
);

#endif /* BRST_STREAM_GEOMETRY_H */
