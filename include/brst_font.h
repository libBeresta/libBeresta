#ifndef BRST_FONT_H
#define BRST_FONT_H

typedef BRST_Dict BRST_Font;

/**

  \ingroup font
  \brief Get name of the font.

  \copydoc dox_param_font

  \return Font name on success, otherwise returns \c NULL

*/
BRST_EXPORT(BRST_CSTR)
BRST_Font_FontName(
    BRST_Font font
);

/**

  \ingroup font
  \brief Get encoding name of the font.

  \copydoc dox_param_font

  \return Font encoding name on success, otherwise returns \c NULL

*/
BRST_EXPORT(BRST_CSTR)
BRST_Font_EncodingName(
    BRST_Font font
);

/**

  \ingroup font
  \brief Get width of a Unicode character in a specific font.

  Actual character width on the page can be calculated as follows:

  \code
  BRST_INT char_width = BRST_Font_UnicodeWidth (font, UNICODE);
  float actual_width = char_width * FONT_SIZE / 1000;
  \endcode

  \copydoc dox_param_font
  \param code Unicode character

  \todo Clarify what is \c FONT_SIZE

  \return Character width on success, otherwise returns \c 0

*/
BRST_EXPORT(BRST_INT)
BRST_Font_UnicodeWidth(
    BRST_Font    font,
    BRST_UNICODE code
);

/**

  \ingroup font
  \brief Get bounding box of the font.

  \copydoc dox_param_font

  \return \ref BRST_Box structure specifying font bounding box, otherwise returns `BRST_Box{0, 0, 0, 0}`.

*/
BRST_EXPORT(BRST_Box)
BRST_Font_BBox(
    BRST_Font font
);

/**

  \ingroup font
  \brief Get vertical ascent of the font.

  \copydoc dox_param_font

  \return Font vertical ascent on success, otherwise returns \c 0.

*/
BRST_EXPORT(BRST_INT)
BRST_Font_Ascent(
    BRST_Font font
);

/**

  \ingroup font
  \brief Get vertical descent of the font.

  \copydoc dox_param_font

  \return Font vertical descent on success, otherwise returns \c 0.

*/
BRST_EXPORT(BRST_INT)
BRST_Font_Descent(
    BRST_Font font
);

/**

  \ingroup font
  \brief Get the distance from the baseline and the mean line of lowercase letters in a font.

  \copydoc dox_param_font

  \return Font x-height value on success, otherwise returns \c 0.

*/
BRST_EXPORT(BRST_UINT)
BRST_Font_XHeight(
    BRST_Font font
);

/**

  \ingroup font
  \brief Get the distance from the baseline and the mean line of uppercase letters in a font.

  \copydoc dox_param_font

  \return Font cap height value on success, otherwise returns \c 0.

*/
BRST_EXPORT(BRST_UINT)
BRST_Font_CapHeight(
    BRST_Font font
);

/**

  \ingroup font
  \brief Get total width of the text, number of characters, and number of words.

  \copydoc dox_param_font
  \param text The text to get width.
  \param len - The byte length of the text.

  \return \ref BRST_TextWidth struct with calculation results, otherwise, returns `BRST_TextWidth{0, 0, 0, 0}`.

  \todo What is the meaning of fourth param?
  \todo Byte length or character length?

*/
BRST_EXPORT(BRST_TextWidth)
BRST_Font_TextWidth(
    BRST_Font        font,
    const BRST_BYTE* text,
    BRST_UINT        len
);

/**

  \ingroup font
  \brief Calculate byte length which can be included within the specified width.

  \copydoc dox_param_font
  \param text Text to get width
  \param len Length of the text.
  \param width Width of the area to put text.
  \param font_size The size of the font.
  \param char_space The character spacing value.
  \param word_space The word spacing value.
  \param wordwrap \parblock Word wrap flag.
  When there are three words of \a "ABCDE", \a "FGH", and \a "IJKL", and
  the substring until \a "J" can be included within the width, if \c word_wrap
  parameter is \ref BRST_FALSE it returns \c 12, and if \c word_wrap parameter
  is \ref BRST_TRUE, it returns \c 10 (the end of the previous word).
  \image html img/measuretext.png
  \endparblock
  \param real_width If this parameter is not \c NULL, the real widths of the \c text is set.
  An application can set it to \c NULL, if it is unnecessary.

  \return Byte length which can be included within the specified width in
  current font size, character spacing and word spacing. Otherwise it returns \c 0 and calls error handler.

  \todo Check if function return byte length or character length, it differs in multiple cases.

  \todo \c len is byte length or character length?

*/
BRST_EXPORT(BRST_UINT)
BRST_Font_MeasureText(
    BRST_Font        font,
    const BRST_BYTE* text,
    BRST_UINT        len,
    BRST_REAL        width,
    BRST_REAL        font_size,
    BRST_REAL        char_space,
    BRST_REAL        word_space,
    BRST_BOOL        wordwrap,
    BRST_REAL*       real_width
);

#endif /* BRST_FONT_H */
