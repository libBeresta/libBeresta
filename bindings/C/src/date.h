// license
#ifndef BRST_DATE_H
#define BRST_DATE_H

struct _BRST_Date_Rec;
typedef struct _BRST_Date_Rec* BRST_Date;

/**
 Элементы даты, возвращаемые функцией \ref BRST_Date_Part()
 */
typedef enum _BRST_Date_Parts { 
    /// 
    BRST_DATE_PART_YEAR,
    /// 
    BRST_DATE_PART_MONTH,
    /// 
    BRST_DATE_PART_DAY,
    /// 
    BRST_DATE_PART_HOUR,
    /// 
    BRST_DATE_PART_MINUTE,
    /// 
    BRST_DATE_PART_SECOND,
    /// 
    BRST_DATE_PART_HOUR_OFFSET,
    /// 
    BRST_DATE_PART_MINUTE_OFFSET,
    /// 
    BRST_DATE_PART_UT_RELATIONSHIP,
    BRST_DATE_PARTS_LAST
} BRST_Date_Parts;

/**
 Смещение на восток от UTC
 */
typedef enum _BRST_UT_Relationship { 
    /// Смещение времени от UTC не указано
    BRST_UT_RELATIONSHIP_NONE,
    /// Время позже UTC
    BRST_UT_RELATIONSHIP_PLUS,
    /// Время раньше UTC
    BRST_UT_RELATIONSHIP_MINUS,
    /// Время соответствует UTC
    BRST_UT_RELATIONSHIP_ZERO,
    BRST_UT_RELATIONSHIP_LAST
} BRST_UT_Relationship;

/**
  \ingroup date
  \brief Функция возвращает объект, содержащий текущие дату и время.
  Учитываются настройки локали в операционной системе, и дата/время сохраняются в объекте с учетом временной зоны.  
  В дальнейшем, этот объект используется в функциях, работающих со временем (свойства документа, вложенных файлов и т.д.)

  \param pdf Описатель объекта документа.

  \return Объект, содержащий текущие дату и время
*/
BRST_EXPORT(BRST_Date)
BRST_Date_Now(
   BRST_Doc pdf
);

/**
  \ingroup date
  \brief Элементы даты (год, месяц, день и т.д.)

  \param date Описатель объекта даты.
  \param part Запрашиваемый элемент даты

  \return Значение элемента даты
*/
BRST_EXPORT(BRST_INT)
BRST_Date_Part(
   BRST_Date date,
   BRST_Date_Parts part
);

/**
  \ingroup date
  \brief Проверяет внутреннюю согласованность даты в структуре данных.

  \param date Описатель объекта даты.

  \return Возвращает \c BRST_OK, если дата корректна и \c BRST_INVALID_DATE_TIME в противном случае.
*/
BRST_EXPORT(BRST_STATUS)
BRST_Date_Validate(
   BRST_Date date
);

/**
  \ingroup date
  \brief Высвобождает память, занятую объектом даты.

  \param date Описатель объекта даты.

  \return Нет
*/
BRST_EXPORT(void)
BRST_Date_Free(
   BRST_Date date
);

#endif /* BRST_DATE_H */
