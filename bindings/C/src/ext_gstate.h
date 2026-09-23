// license
#ifndef BRST_EXT_GSTATE_H
#define BRST_EXT_GSTATE_H

typedef BRST_Dict BRST_ExtGState;

/**
  \ingroup 
  \brief :ru is not set

  \param ext_gstate :param_ext_gstate
  \param value Значение прозрачности штриха.

  \return \ref BRST_OK при успешном выполнении, иначе возвращает код ошибки и вызывает обработчик ошибок.
*/
BRST_EXPORT(BRST_STATUS)
BRST_ExtGState_SetAlphaStroke(
   BRST_ExtGState ext_gstate,
   BRST_REAL value
);

/**
  \ingroup 
  \brief :ru is not set

  \param ext_gstate :param_ext_gstate
  \param value Значение прозрачности заливки.

  \return \ref BRST_OK при успешном выполнении, иначе возвращает код ошибки и вызывает обработчик ошибок.
*/
BRST_EXPORT(BRST_STATUS)
BRST_ExtGState_SetAlphaFill(
   BRST_ExtGState ext_gstate,
   BRST_REAL value
);

/**
  \ingroup 
  \brief :ru is not set

  \param ext_gstate :param_ext_gstate
  \param mode 

  \return \ref BRST_OK при успешном выполнении, иначе возвращает код ошибки и вызывает обработчик ошибок.
*/
BRST_EXPORT(BRST_STATUS)
BRST_ExtGState_SetBlendMode(
   BRST_ExtGState ext_gstate,
   BRST_BlendMode mode
);

#endif /* BRST_EXT_GSTATE_H */
