// license
#ifndef BRST_BASE_H
#define BRST_BASE_H

/**
  \ingroup doc
  \brief Создает и настраивает экземпляр документа

  \param user_error_fn Пользовательский обработчик ошибок, вызываемые при возникновении ошибок.
  \param user_alloc_fn Пользовательская функция распределения памяти. Если указано \c NULL, используется функция `malloc()`.
  \param user_free_fn Пользовательская функция высвобождения памяти. Если указано \c NULL, используется функция `free()`.
  \param mem_pool_buf_size \parblock \c libBeresta по умолчанию не использует пул памяти.

Функция выделения памяти по требованию вызывается из приложения.

Если параметр установлен в ненулевое значение, управление памятью производится следующим образом:
- память выделяется блоками размера \c mem_pool_buf_size.
- менеджер памяти отдает приложению память запрошенного размера
  и объединяет оставшуюся память для использования при следующем запросе.
- если размер запрошенной памяти больше, чем оставшаяся память,
  выделяется новый блок памяти.
- неиспользуемая память не освобождается незамедлительно, высвобождение
  производится при вызове BRST_Free().
\endparblock
  \param user_data Указатель на пользовательские данные, используемый в обработчике ошибок.

  \return Дескриптор объекта документа при успехе и \c NULL при неудаче.

  \see 
    BRST_New()
    BRST_Free()
*/
BRST_EXPORT(BRST_Doc)
BRST_Doc_New_Ex(
   BRST_Error_Handler user_error_fn,
   BRST_Alloc_Func user_alloc_fn,
   BRST_Free_Func user_free_fn,
   BRST_UINT mem_pool_buf_size,
   BRST_RAW_POINTER user_data
);

/**
  \ingroup doc
  \brief Возвращает версию библиотеки

  \return Версия библиотеки
*/
BRST_EXPORT(BRST_CSTR)
BRST_Version();

/**
  \ingroup doc
  \brief Создает объект документа и настраивает его

  \param user_error_fn Пользовательская функция обработки, вызываемая при возникновении ошибки.
  \param user_data Указатель на пользовательские данные, передаваемые в обработчик ошибок.

  \return Дескриптор объекта документа при успехе и \c NULL при неудаче.

  \see 
    BRST_Doc_New_Ex()
    BRST_Doc_New_Empty()
    BRST_Doc_Free()
*/
BRST_EXPORT(BRST_Doc)
BRST_Doc_New(
   BRST_Error_Handler user_error_fn,
   BRST_RAW_POINTER user_data
);

/**
  \ingroup doc
  \brief Создает объект документа и настраивает его (без дополнительных опций)

  \return Дескриптор объекта документа при успехе и \c NULL при неудаче.

  \see 
    BRST_Doc_New()
    BRST_Doc_New_Ex()
    BRST_Doc_Free()
*/
BRST_EXPORT(BRST_Doc)
BRST_Doc_New_Empty();

/**
  \ingroup doc
  \brief Настраивает документ. Если документ \c doc уже настроен, он предварительно очищается

  \param pdf Описатель объекта документа.

  \return \ref BRST_OK при успешном выполнении, иначе возвращает код ошибки и вызывает обработчик ошибок.

  \see 
    BRST_Doc_Destroy()

  \par Коды ошибок
    - \ref BRST_INVALID_DOCUMENT
    - \ref BRST_FAILED_TO_ALLOC_MEM
*/
BRST_EXPORT(BRST_STATUS)
BRST_Doc_Initialize(
   BRST_Doc pdf
);

/**
  \ingroup doc
  \brief Очищает внутренние структуры документа.

  \param pdf Описатель объекта документа.

  \return Нет

  \see 
    BRST_Doc_Initialize()
    BRST_Doc_Destroy_All()
*/
BRST_EXPORT(void)
BRST_Doc_Destroy(
   BRST_Doc pdf
);

/**
  \ingroup doc
  \brief Проверяет, что описатель объекта документа корректен.

  \param pdf Описатель объекта документа.

  \return \ref BRST_TRUE если описатель документа корректен, иначе возвращает \ref BRST_FALSE, устанавливает код ошибки и вызывает обработчик ошибок.

  \see 
    BRST_Doc_Initialize()

  \par Коды ошибок
    - \ref BRST_INVALID_DOCUMENT
*/
BRST_EXPORT(BRST_BOOL)
BRST_Doc_Initialized(
   BRST_Doc pdf
);

/**
  \ingroup doc
  \brief Очищает внутренние структуры документа.

Функция высвобождает загруженные ресурсы (вроде шрифтов и кодировок).

  \param pdf Описатель объекта документа.

  \return Нет

  \see 
    BRST_Doc_Initialize()
    BRST_Doc_Destroy()
*/
BRST_EXPORT(void)
BRST_Doc_Destroy_All(
   BRST_Doc pdf
);

/**
  \ingroup doc
  \brief Возвращает менеджер памяти документа

  \param pdf Описатель объекта документа.

  \return Менеджер памяти документа, если он установлен.
*/
BRST_EXPORT(BRST_MMgr)
BRST_Doc_MMgr(
   BRST_Doc pdf
);

/**
  \ingroup doc
  \brief Высвобождает данные документа

  \param pdf Описатель объекта документа.

  \return Нет
*/
BRST_EXPORT(void)
BRST_Doc_Free(
   BRST_Doc pdf
);

/**
  \ingroup doc
  \brief Ширина страницы для предопределенного размера. Может использоваться без документа и страницы.

  \param size Предопределённый размер страницы
  \param orientation Ориентация страницы

  \return Ширина страницы в точках
*/
BRST_EXPORT(BRST_REAL)
BRST_PageSize_Width(
   BRST_PageSizes size,
   BRST_PageOrientation orientation
);

/**
  \ingroup doc
  \brief Высота страницы для предопределенного размера. Может использоваться без документа и страницы.

  \param size Предопределённый размер страницы
  \param orientation Ориентация страницы

  \return Ширина страницы в точках
*/
BRST_EXPORT(BRST_REAL)
BRST_PageSize_Height(
   BRST_PageSizes size,
   BRST_PageOrientation orientation
);

#endif /* BRST_BASE_H */
