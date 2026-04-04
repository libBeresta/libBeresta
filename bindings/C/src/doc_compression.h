// license
#ifndef BRST_DOC_COMPRESSION_H
#define BRST_DOC_COMPRESSION_H

/**
  \ingroup doc
  \brief Устанавливает режим сжатия документа.

  \param pdf Описатель объекта документа.
  \param mode Режим сжатия документа. \parblock Одно или несколько значение, объединенных битовым \c OR:
  | Режим                   | Описание                                                   |
  | -----                   | --------                                                   |
  | \ref BRST_COMP_NONE     | Без сжатия                                                 |
  | \ref BRST_COMP_TEXT     | Сжатие содержимого потока страницы.                        |
  | \ref BRST_COMP_IMAGE    | Сжатие потоков объектов изображений.                       |
  | \ref BRST_COMP_METADATA | Сжатие потоков других данных (шрифты, cmaps и т.д.)        |
  | \ref BRST_COMP_ALL      | Сжатие всех потоков <br/>(комбинация  \ref BRST_COMP_TEXT, \ref BRST_COMP_IMAGE и \ref BRST_COMP_METADATA). |

  \return \ref BRST_OK при успешном выполнении, иначе возвращает код ошибки и вызывает обработчик ошибок.
*/
BRST_EXPORT(BRST_STATUS)
BRST_Doc_SetCompressionMode(
   BRST_Doc pdf,
   BRST_CompressionMode mode
);

#endif /* BRST_DOC_COMPRESSION_H */
