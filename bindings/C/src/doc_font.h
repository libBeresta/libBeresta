// license
#ifndef BRST_DOC_FONT_H
#define BRST_DOC_FONT_H

/**
  \ingroup font
  \brief Получает запрошенный описатель объекта шрифта.

  \param pdf Описатель объекта документа.
  \param font_name Корректное название шрифта
  \param encoding_name Корректное название кодировки

  \return Описатель объекта шрифта при успехе, в противном случае возвращает \c NULL и вызывает обработчик ошибок.

  \par Коды ошибок
    - \ref BRST_INVALID_DOCUMENT
    - \ref BRST_FAILED_TO_ALLOC_MEM
    - \ref BRST_INVALID_FONT_NAME
    - \ref BRST_INVALID_ENCODING_NAME
    - \ref BRST_UNSUPPORTED_FONT_TYPE
*/
BRST_EXPORT(BRST_Font)
BRST_Doc_Font(
   BRST_Doc pdf,
   BRST_CSTR font_name,
   BRST_CSTR encoding_name
);

/**
  \ingroup font
  \brief Получает запрошенный описатель объекта шрифта.

  \param pdf Описатель объекта документа.
  \param filename Путь до файла шрифта TrueType (`.ttf`)
  \param embedding Если этот параметр равен \ref BRST_TRUE, данные о глифах шрифта встраиваются в PDF-файл, иначе в PDF-файл включаются только матричные данные.

  \return Наименование (идентификатор) шрифта при успехе, в противном случае возвращается \c NULL и вызывается обработчик ошибок.

  \see 
    BRST_fonts

  \par Коды ошибок
    - \ref BRST_INVALID_DOCUMENT
    - \ref BRST_FAILED_TO_ALLOC_MEM
    - \ref BRST_FONT_EXISTS
    - \ref BRST_INVALID_TTC_INDEX
    - \ref BRST_INVALID_TTC_FILE
    - \ref BRST_TTF_INVALID_CMAP
    - \ref BRST_TTF_INVALID_FORMAT
    - \ref BRST_TTF_MISSING_TABLE
    - \ref BRST_TTF_CANNOT_EMBEDDING_FONT
*/
BRST_EXPORT(BRST_Font)
BRST_Doc_TTFont_LoadFromFile(
   BRST_Doc pdf,
   BRST_CSTR filename,
   BRST_BOOL embedding
);

/**
  \ingroup 
  \brief Загрузка шрифта формата Type1 из внешнего файла и регистрация шрифта в документе.

  \param pdf Описатель объекта документа.
  \param afm_filename Путь к файлу AFM
  \param data_filename :ru is not set

  \return Наименование (идентификатор) шрифта при успехе, в противном случае возвращается \c NULL и вызывается обработчик ошибок.
*/
BRST_EXPORT(BRST_CSTR)
BRST_Doc_Type1Font_LoadFromFile(
   BRST_Doc pdf,
   BRST_CSTR afm_filename,
   BRST_CSTR data_filename
);

/**
  \ingroup 
  \brief Загрузка TrueType-шрифта из коллекции (*.ttc)

  \param pdf Описатель объекта документа.
  \param filename Путь к файлу коллекции (*.ttc)
  \param index Номер шрифта в коллекции
  \param embedding Если этот параметр равен \ref BRST_TRUE, данные о глифах шрифта встраиваются в PDF-файл, иначе в PDF-файл включаются только матричные данные.

  \return Наименование (идентификатор) шрифта при успехе, в противном случае возвращается \c NULL и вызывается обработчик ошибок.
*/
BRST_EXPORT(BRST_CSTR)
BRST_Doc_TTFont_LoadFromFile2(
   BRST_Doc pdf,
   BRST_CSTR filename,
   BRST_UINT index,
   BRST_BOOL embedding
);

/**
  \ingroup 
  \brief Загрузка TrueType-шрифта из буфера памяти

  \param pdf Описатель объекта документа.
  \param buffer Буфер с содержимым TrueType-шрифта.
  \param size Размер буфера
  \param embedding Если этот параметр равен \ref BRST_TRUE, данные о глифах шрифта встраиваются в PDF-файл, иначе в PDF-файл включаются только матричные данные.

  \return Наименование (идентификатор) шрифта при успехе, в противно случае возвращается \c NULL и вызывается обработчик ошибок.
*/
BRST_EXPORT(BRST_CSTR)
BRST_Doc_TTFont_LoadFromMemory(
   BRST_Doc pdf,
   BRST_BYTE* buffer,
   BRST_UINT size,
   BRST_BOOL embedding
);

#endif /* BRST_DOC_FONT_H */
