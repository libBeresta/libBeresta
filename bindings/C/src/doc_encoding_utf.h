// license
#ifndef BRST_DOC_ENCODING_UTF_H
#define BRST_DOC_ENCODING_UTF_H

/**
  \ingroup 
  \brief Включение поддержки кодировки UTF-8.

  После этого вызова приложение может использовать тексты в кодировке Unicode.

  \note Кодировка UTF-8 работает только со шрифтами TrueType.

  \param pdf Описатель объекта документа.

  \return \ref BRST_OK при успешном выполнении, иначе возвращает код ошибки и вызывает обработчик ошибок.

  \par Коды ошибок
    - \ref BRST_INVALID_DOCUMENT
    - \ref BRST_FAILED_TO_ALLOC_MEM
    - \ref BRST_DUPLICATE_REGISTRATION
*/
BRST_EXPORT(BRST_STATUS)
BRST_Doc_UseUTFEncodings(
   BRST_Doc pdf
);

#endif /* BRST_DOC_ENCODING_UTF_H */
