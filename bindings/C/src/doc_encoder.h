// license
#ifndef BRST_DOC_ENCODER_H
#define BRST_DOC_ENCODER_H

/**
  \ingroup 
  \brief Установка кодировщика документа

  \param pdf Описатель объекта документа.
  \param encoding_name Название кодировки

  \return \ref BRST_OK при успешном выполнении, иначе возвращает код ошибки и вызывает обработчик ошибок.
*/
BRST_EXPORT(BRST_STATUS)
BRST_Doc_Encoder_SetCurrent(
   BRST_Doc pdf,
   BRST_CSTR encoding_name
);

/**
  \ingroup 
  \brief Получение объекта кодировщика по имени кодировки

  \param pdf Описатель объекта документа.
  \param encoding_name Название кодировки

  \return Описатель объекта кодировщика.
*/
BRST_EXPORT(BRST_Encoder)
BRST_Doc_Encoder_Prepare(
   BRST_Doc pdf,
   BRST_CSTR encoding_name
);

/**
  \ingroup 
  \brief Получение текущего кодировщика документа

  \param pdf Описатель объекта документа.

  \return Описатель объекта кодировщика.
*/
BRST_EXPORT(BRST_Encoder)
BRST_Doc_Encoder_Current(
   BRST_Doc pdf
);

#endif /* BRST_DOC_ENCODER_H */
