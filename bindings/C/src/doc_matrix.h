// license
#ifndef BRST_DOC_MATRIX_H
#define BRST_DOC_MATRIX_H

/**
  \ingroup 
  \brief Создается единичная матрица преобразований.

  \param pdf Описатель объекта документа.

  \return Описатель объекта матрицы преобразования.
*/
BRST_EXPORT(BRST_Matrix)
BRST_Doc_Matrix_Identity(
   BRST_Doc pdf
);

/**
  \ingroup 
  \brief Высвобождение памяти, занятой матрицей преобразований.

  \param m Описатель объекта матрицы преобразования.

  \return Нет
*/
BRST_EXPORT(void)
BRST_Doc_Matrix_Free(
   BRST_Matrix m
);

/**
  \ingroup 
  \brief Перемножение матриц преобразований. Результирующая матрица - это перемножение матриц \c m и \c n.

  \param pdf Описатель объекта документа.
  \param m Описатель объекта матрицы преобразования.
  \param n Описатель объекта матрицы преобразования.

  \return Описатель объекта матрицы преобразования.
*/
BRST_EXPORT(BRST_Matrix)
BRST_Doc_Matrix_Multiply(
   BRST_Doc pdf,
   BRST_Matrix m,
   BRST_Matrix n
);

/**
  \ingroup 
  \brief Создание матрицы переноса на расстояние \c dx и \c dy.

  \param pdf Описатель объекта документа.
  \param m Описатель объекта матрицы преобразования.
  \param dx Перенос координат по оси X.
  \param dy Перенос координат по оси Y.

  \return Описатель объекта матрицы преобразования.
*/
BRST_EXPORT(BRST_Matrix)
BRST_Doc_Matrix_Translate(
   BRST_Doc pdf,
   BRST_Matrix m,
   BRST_REAL dx,
   BRST_REAL dy
);

/**
  \ingroup 
  \brief Создание матрицы масштабирования с коэффициентами \c sx и \c sy.

  \param pdf Описатель объекта документа.
  \param m Описатель объекта матрицы преобразования.
  \param sx Масштабный коэффициент по оси X.
  \param sy Масштабный коэффициент по оси Y.

  \return Описатель объекта матрицы преобразования.
*/
BRST_EXPORT(BRST_Matrix)
BRST_Doc_Matrix_Scale(
   BRST_Doc pdf,
   BRST_Matrix m,
   BRST_REAL sx,
   BRST_REAL sy
);

/**
  \ingroup 
  \brief Создание матрицы поворота на угол \c angle (радиан).

  \param pdf Описатель объекта документа.
  \param m Описатель объекта матрицы преобразования.
  \param angle Угол поворота координат (радиан).

  \return Описатель объекта матрицы преобразования.
*/
BRST_EXPORT(BRST_Matrix)
BRST_Doc_Matrix_Rotate(
   BRST_Doc pdf,
   BRST_Matrix m,
   BRST_REAL angle
);

/**
  \ingroup 
  \brief Создание матрицы поворота на угол \c angle (градусов).

  \param pdf Описатель объекта документа.
  \param m Описатель объекта матрицы преобразования.
  \param degrees Угол поворота координат (градусов).

  \return Описатель объекта матрицы преобразования.
*/
BRST_EXPORT(BRST_Matrix)
BRST_Doc_Matrix_RotateDeg(
   BRST_Doc pdf,
   BRST_Matrix m,
   BRST_REAL degrees
);

/**
  \ingroup 
  \brief Создание матрицы сдвига на \c a и \c b по осям координат.

  \param pdf Описатель объекта документа.
  \param m Описатель объекта матрицы преобразования.
  \param a Значение сдвига по оси X.
  \param b Значение сдвига по оси Y.

  \return Описатель объекта матрицы преобразования.
*/
BRST_EXPORT(BRST_Matrix)
BRST_Doc_Matrix_Skew(
   BRST_Doc pdf,
   BRST_Matrix m,
   BRST_REAL a,
   BRST_REAL b
);

#endif /* BRST_DOC_MATRIX_H */
