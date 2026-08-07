// license
#ifndef BRST_DESTINATION_H
#define BRST_DESTINATION_H

#include "brst_external.h"
#include "brst_types.h"
#include "brst_array.h"

typedef BRST_Array BRST_Destination;

/**
  \ingroup link
  \brief Демонстрация страницы, указываемой \c dst, с позиционированием \c left, \c top и масштабом \c zoom.

  \param dst Описатель объекта места назначения.
  \param left Левая координата на странице для позиционирования окна
  \param top Верхняя координата на странице для позиционирования окна
  \param zoom Множитель масштабирования содержимого страницы. Значение должно быть в диапазоне от \c 0.08 (8%) до \c 32 (3200%).

  \return \ref BRST_OK при успешном выполнении, иначе возвращает код ошибки и вызывает обработчик ошибок.

  \par Коды ошибок
    - \ref BRST_INVALID_DESTINATION
    - \ref BRST_INVALID_PARAMETER
*/
BRST_EXPORT(BRST_STATUS)
BRST_Destination_SetXYZ(
   BRST_Destination dst,
   BRST_REAL left,
   BRST_REAL top,
   BRST_REAL zoom
);

/**
  \ingroup link
  \brief Демонстрация страницы, указываемой \c dst, с полным включение страницы в окно.

  \param dst Описатель объекта места назначения.

  \return \ref BRST_OK при успешном выполнении, иначе возвращает код ошибки и вызывает обработчик ошибок.

  \par Коды ошибок
    - \ref BRST_INVALID_DESTINATION
*/
BRST_EXPORT(BRST_STATUS)
BRST_Destination_SetFit(
   BRST_Destination dst
);

/**
  \ingroup link
  \brief Демонстрация страницы, указываемой \c dst, с позиционированием \c top, вместив страницу в окно по ширине.

  \param dst Описатель объекта места назначения.
  \param top Верхняя координата на странице для позиционирования окна

  \return \ref BRST_OK при успешном выполнении, иначе возвращает код ошибки и вызывает обработчик ошибок.

  \par Коды ошибок
    - \ref BRST_INVALID_DESTINATION
    - \ref BRST_INVALID_PARAMETER
*/
BRST_EXPORT(BRST_STATUS)
BRST_Destination_SetFitH(
   BRST_Destination dst,
   BRST_REAL top
);

/**
  \ingroup link
  \brief Демонстрация страницы, указываемой \c dst, с позиционированием \c left, вместив страницу по высоте

  \param dst Описатель объекта места назначения.
  \param left Левая координата на странице для позиционирования окна

  \return \ref BRST_OK при успешном выполнении, иначе возвращает код ошибки и вызывает обработчик ошибок.

  \par Коды ошибок
    - \ref BRST_INVALID_DESTINATION
*/
BRST_EXPORT(BRST_STATUS)
BRST_Destination_SetFitV(
   BRST_Destination dst,
   BRST_REAL left
);

/**
  \ingroup link
  \brief Демонстрация страницы, указываемой \c dst, таким образом, чтобы вписать прямоугольник, задаваемый \c left, \c top, \c right, \c bottom, в окно.

  \param dst Описатель объекта места назначения.
  \param left Левая координата на странице для позиционирования окна
  \param bottom Нижняя координата на странице для позиционирования окна
  \param right Правая координата на странице для позиционирования окна
  \param top Верхняя координата на странице для позиционирования окна

  \return \ref BRST_OK при успешном выполнении, иначе возвращает код ошибки и вызывает обработчик ошибок.

  \par Коды ошибок
    - \ref BRST_INVALID_DESTINATION
    - \ref BRST_INVALID_PARAMETER
*/
BRST_EXPORT(BRST_STATUS)
BRST_Destination_SetFitR(
   BRST_Destination dst,
   BRST_REAL left,
   BRST_REAL bottom,
   BRST_REAL right,
   BRST_REAL top
);

/**
  \ingroup link
  \brief Демонстрация страницы, указываемой \c dst, с полным включение охватывающего прямоугольника (bounding box) в окно.

  \param dst Описатель объекта места назначения.

  \return \ref BRST_OK при успешном выполнении, иначе возвращает код ошибки и вызывает обработчик ошибок.

  \par Коды ошибок
    - \ref BRST_INVALID_DESTINATION
*/
BRST_EXPORT(BRST_STATUS)
BRST_Destination_SetFitB(
   BRST_Destination dst
);

/**
  \ingroup link
  \brief Демонстрация страницы, указываемой \c dst, с позиционированием \c top, вместив охватывающий прямоугольник (bounding box) страницы в окно по ширине.

  \param dst Описатель объекта места назначения.
  \param top Верхняя координата на странице для позиционирования окна

  \return \ref BRST_OK при успешном выполнении, иначе возвращает код ошибки и вызывает обработчик ошибок.

  \par Коды ошибок
    - \ref BRST_INVALID_DESTINATION
    - \ref BRST_INVALID_PARAMETER
*/
BRST_EXPORT(BRST_STATUS)
BRST_Destination_SetFitBH(
   BRST_Destination dst,
   BRST_REAL top
);

/**
  \ingroup link
  \brief Демонстрация страницы, указываемой \c dst, с позиционированием \c left, вместив охватывающий прямоугольник (bounding box) страницы по высоте.

  \param dst Описатель объекта места назначения.
  \param left Левая координата на странице для позиционирования окна

  \return \ref BRST_OK при успешном выполнении, иначе возвращает код ошибки и вызывает обработчик ошибок.

  \par Коды ошибок
    - \ref BRST_INVALID_DESTINATION
*/
BRST_EXPORT(BRST_STATUS)
BRST_Destination_SetFitBV(
   BRST_Destination dst,
   BRST_REAL left
);

#endif /* BRST_DESTINATION_H */
