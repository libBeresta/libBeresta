// license
#ifndef BRST_DOC_EXT_GSTATE_H
#define BRST_DOC_EXT_GSTATE_H

/**
  \ingroup doc
  \brief Добавляет в документ словарь расширенного графического состояния ExtGState. (Таблица 58).

  \param pdf Описатель объекта документа.

  \return Описатель расширенного графического состояния при успехе или \c NULL при возникновении ошибки.
*/
BRST_EXPORT(BRST_ExtGState)
BRST_Doc_Create_ExtGState(
   BRST_Doc pdf
);

#endif /* BRST_DOC_EXT_GSTATE_H */
