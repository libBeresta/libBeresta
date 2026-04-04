// license
#ifndef BRST_DOC_XOBJECT_H
#define BRST_DOC_XOBJECT_H

/**
  \ingroup 
  \brief Создание XObject из изображения

  \param pdf Описатель объекта документа.
  \param rect Прямоугольник размещения
  \param image Изображение
  \param zoom :ru is not set

  \return Описатель объекта XObject.
*/
BRST_EXPORT(BRST_XObject)
BRST_Doc_XObject_CreateFromImage(
   BRST_Doc pdf,
   BRST_Rect rect,
   BRST_Image image,
   BRST_BOOL zoom
);

/**
  \ingroup 
  \brief Создать белый прямоугольник XObject

  \param pdf Описатель объекта документа.
  \param rect Размеры белого прямоугольника

  \return Описатель объекта XObject.
*/
BRST_EXPORT(BRST_XObject)
BRST_Doc_XObject_CreateAsWhiteRect(
   BRST_Doc pdf,
   BRST_Rect rect
);

/**
  \ingroup doc
  \brief Создание объекта XObject Form

  \param pdf Описатель объекта документа.
  \param width Ширина XObject в логических единицах
  \param height Высота XObject в логических единицах
  \param scalex Горизонтальное соотношение единиц в XObject и в документе
  \param scaley Вертикальное соотношение единиц в XObject и в документе

  \return Описатель объекта XObject.

  \see 
    BRST_Page_XObject_Execute()
    BRST_Page_DrawImage()
    BRST_Page_GSave()
    BRST_Page_GRestore()
    BRST_Page_Concat()
    BRST_XObject_Stream()
*/
BRST_EXPORT(BRST_XObject)
BRST_Doc_XObject_Create(
   BRST_Doc pdf,
   BRST_REAL width,
   BRST_REAL height,
   BRST_REAL scalex,
   BRST_REAL scaley
);

#endif /* BRST_DOC_XOBJECT_H */
