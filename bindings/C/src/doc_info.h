// license
#ifndef BRST_DOC_INFO_H
#define BRST_DOC_INFO_H

/**
 Атрибуты метаданных документа (Таблица 317)
 */
typedef enum _BRST_InfoType { 
    /// Дата создания документа
    BRST_INFO_CREATION_DATE,
    /// Дата изменения документа
    BRST_INFO_MOD_DATE,
    /// Автор документа
    BRST_INFO_AUTHOR,
    /// Разработчик документа
    BRST_INFO_CREATOR,
    /// Продюсер документа
    BRST_INFO_PRODUCER,
    /// Заголовок документа
    BRST_INFO_TITLE,
    /// Тема документа
    BRST_INFO_SUBJECT,
    /// Ключевые слова документа
    BRST_INFO_KEYWORDS,
    /// Признак наличия информации о треппинге в документе.
  Возможные значения (чувствительно к регистру):
  - True
  - False
  - Unknown (по умолчанию)
    BRST_INFO_TRAPPED,
    /// 
    BRST_INFO_GTS_PDFX,
    BRST_INFOTYPE_LAST
} BRST_InfoType;

/**
  \ingroup info
  \brief Устанавливается значение атрибута в словаре \c info. Значение устанавливается с использованием текущей кодировки документа.

  \param pdf Описатель объекта документа.
  \param type \parblock Одно из значений:
    - \ref BRST_INFO_AUTHOR
    - \ref BRST_INFO_CREATOR
    - \ref BRST_INFO_TITLE
    - \ref BRST_INFO_SUBJECT
    - \ref BRST_INFO_KEYWORDS
    \endparblock
  \param value Устанавливаемое значение

  \return \ref BRST_OK при успешном выполнении, иначе возвращает код ошибки и вызывает обработчик ошибок.

  \par Коды ошибок
    - \ref BRST_INVALID_DOCUMENT
    - \ref BRST_FAILED_TO_ALLOC_MEM
    - \ref BRST_INVALID_PARAMETER
*/
BRST_EXPORT(BRST_STATUS)
BRST_Doc_SetInfoAttr(
   BRST_Doc pdf,
   BRST_InfoType type,
   BRST_CSTR value
);

/**
  \ingroup info
  \brief Устанавливается значение даты в словаре \c info.

  \param pdf Описатель объекта документа.
  \param type \parblock Одно из значений:
    - \ref BRST_INFO_CREATION_DATE
    - \ref BRST_INFO_MOD_DATE
    \endparblock
  \param value Устанавливаемое значение

  \return \ref BRST_OK при успешном выполнении, иначе возвращает код ошибки и вызывает обработчик ошибок.

  \par Коды ошибок
    - \ref BRST_INVALID_DOCUMENT
    - \ref BRST_FAILED_TO_ALLOC_MEM
    - \ref BRST_INVALID_PARAMETER
    - \ref BRST_INVALID_DATE_TIME
*/
BRST_EXPORT(BRST_STATUS)
BRST_Doc_SetInfoDateAttr(
   BRST_Doc pdf,
   BRST_InfoType type,
   BRST_Date value
);

#endif /* BRST_DOC_INFO_H */
