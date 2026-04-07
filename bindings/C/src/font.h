// license
#ifndef BRST_FONT_H
#define BRST_FONT_H

typedef BRST_Dict BRST_Font;

/**
  \ingroup font
  \brief 

  \param font Описатель объекта шрифта.
  \param font_size 

  \return 
*/
BRST_EXPORT(BRST_REAL)
BRST_Font_Descent(
   BRST_Font font,
   BRST_REAL font_size
);

/**
  \ingroup font
  \brief 

  \param font Описатель объекта шрифта.
  \param font_size 
  \param word_space 
  \param char_space 
  \param text 

  \return 
*/
BRST_EXPORT(BRST_REAL)
BRST_Font_TextWidth2(
   BRST_Font font,
   BRST_REAL font_size,
   BRST_REAL word_space,
   BRST_REAL char_space,
   BRST_CSTR text
);

#endif /* BRST_FONT_H */
