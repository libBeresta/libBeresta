// license
#ifndef BRST_DOC_SAVE_H
#define BRST_DOC_SAVE_H

/**
  \ingroup doc
  \brief 

  \param pdf Описатель объекта документа.

  \return \ref BRST_OK при успешном выполнении, иначе возвращает код ошибки и вызывает обработчик ошибок.
*/
BRST_EXPORT(BRST_STATUS)
BRST_Doc_SaveToStream(
   BRST_Doc pdf
);

/**
  \ingroup doc
  \brief Сохраняет документ в файл.

  \param pdf Описатель объекта документа.
  \param filename Имя сохраняемого файла.

  \return \ref BRST_OK при успешном выполнении, иначе возвращает код ошибки и вызывает обработчик ошибок.
*/
BRST_EXPORT(BRST_STATUS)
BRST_Doc_SaveToFile(
   BRST_Doc pdf,
   BRST_CSTR filename
);

#endif /* BRST_DOC_SAVE_H */
