// license
#ifndef BRST_XOBJECT_H
#define BRST_XOBJECT_H

typedef BRST_Dict BRST_XObject;

/**
  \ingroup 
  \brief Возвращает поток объекта XObject. Поток используется для записи команд рисования и пр.

  \param xobj Описатель объекта XObject.

  \return Описатель объекта потока.
*/
BRST_EXPORT(BRST_Stream)
BRST_XObject_Stream(
   BRST_XObject xobj
);

#endif /* BRST_XOBJECT_H */
