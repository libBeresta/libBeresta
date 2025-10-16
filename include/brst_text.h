#ifndef BRST_TEXT_H
#define BRST_TEXT_H

#include "brst_external.h"
#include "brst_types.h"
#include "brst_page.h"
#include "brst_font.h"


/**
  \ingroup graphics
  \brief Begin text object and set text position to `(0, 0)`.

  \copydoc dox_param_page

  \copydoc dox_graphics_mode

  \arg Before \ref BRST_GMODE_PAGE_DESCRIPTION
  \arg After \ref BRST_GMODE_TEXT_OBJECT

  \copydoc dox_return_ok

  \see BRST_Page_EndText()

  \copydoc dox_pdf_cmd
  \c BT

*/
BRST_EXPORT(BRST_STATUS)
BRST_Page_BeginText(
    BRST_Page page
);

/**

  \ingroup graphics
  \brief Finish text object

  \copydoc dox_param_page

  \copydoc dox_graphics_mode

  \arg Before \ref BRST_GMODE_TEXT_OBJECT
  \arg After \ref BRST_GMODE_PAGE_DESCRIPTION

  \copydoc dox_return_ok

  \see BRST_Page_BeginText()

  \copydoc dox_pdf_cmd
  \c ET

*/
BRST_EXPORT(BRST_STATUS)
BRST_Page_EndText(
    BRST_Page page
);

/**

  \ingroup graphics
  \brief Set text leading (line spacing).

  \copydoc dox_param_page
  \param value Value of text leading (initially \c 0).

  \copydoc dox_graphics_mode

  \arg Before \ref BRST_GMODE_PAGE_DESCRIPTION or \ref BRST_GMODE_TEXT_OBJECT
  \arg After \ref BRST_GMODE_PAGE_DESCRIPTION or \ref BRST_GMODE_TEXT_OBJECT

  \copydoc dox_return_ok

  \copydoc dox_pdf_cmd
  \c TL

*/
BRST_EXPORT(BRST_STATUS)
BRST_Page_SetTextLeading(
    BRST_Page page,
    BRST_REAL value
);

/**

  \ingroup graphics
  \brief Set the type of font and size leading.

  \copydoc dox_param_page
  \param font Font object handle.
  \param size Font size.

  \copydoc dox_graphics_mode
  \arg Before \ref BRST_GMODE_PAGE_DESCRIPTION or \ref BRST_GMODE_TEXT_OBJECT
  \arg After \ref BRST_GMODE_PAGE_DESCRIPTION or \ref BRST_GMODE_TEXT_OBJECT

  \copydoc dox_return_ok

  \copydoc dox_pdf_cmd
  \c Tf

*/
BRST_EXPORT(BRST_STATUS)
BRST_Page_SetFontAndSize(
    BRST_Page page,
    BRST_Font font,
    BRST_REAL size
);

BRST_EXPORT(BRST_STATUS)
BRST_Dict_SetFontAndSize(
    BRST_Dict dict,
    BRST_Font font,
    BRST_REAL size
);


/**

  \ingroup graphics
  \brief Set text rendering mode.

  \copydoc dox_param_page
  \param mode Text rendering mode (one of the following).

  | Value                          | Image                    | Description                                          |
  | -----                          | :-----:                  | -----------                                          |
  | \ref BRST_FILL                 | \image html rndmode1.png | Fill text.                                           |
  | \ref BRST_STROKE               | \image html rndmode2.png | Stroke text.                                         |
  | \ref BRST_FILL_THEN_STROKE     | \image html rndmode3.png | Fill, then stroke text.                              |
  | \ref BRST_INVISIBLE            | &mdash;                  | Neither fill nor stroke text (invisible).            |
  | \ref BRST_FILL_CLIPPING        | \image html rndmode4.png | Fill text and add to path for clipping.              |
  | \ref BRST_STROKE_CLIPPING      | \image html rndmode5.png | Stroke text and add to path for clipping.            |
  | \ref BRST_FILL_STROKE_CLIPPING | \image html rndmode6.png | Fill, then stroke text and add to path for clipping. |
  | \ref BRST_CLIPPING             | &mdash;                  | Add text to path for clipping.                       |

  Default \c mode is \ref BRST_FILL.

  \copydoc dox_graphics_mode

  \arg Before \ref BRST_GMODE_PAGE_DESCRIPTION or \ref BRST_GMODE_TEXT_OBJECT
  \arg After \ref BRST_GMODE_PAGE_DESCRIPTION or \ref BRST_GMODE_TEXT_OBJECT

  \copydoc dox_return_ok

  \todo Add picture for \ref BRST_CLIPPING

  \copydoc dox_pdf_cmd
  \c Tr

*/
BRST_EXPORT(BRST_STATUS)
BRST_Page_SetTextRenderingMode(
    BRST_Page              page,
    BRST_TextRenderingMode mode
);

/**

  \ingroup graphics
  \brief Move text position in vertical direction by the amount of \c value.

  Useful for making subscripts or superscripts.

  \copydoc dox_param_page
  \param value Text rise, in user space units.

  \copydoc dox_graphics_mode

  \arg Before \ref BRST_GMODE_PAGE_DESCRIPTION or \ref BRST_GMODE_TEXT_OBJECT
  \arg After \ref BRST_GMODE_PAGE_DESCRIPTION or \ref BRST_GMODE_TEXT_OBJECT

  \copydoc dox_return_ok

  \todo Add picture for \ref BRST_CLIPPING

  \copydoc dox_pdf_cmd
  \c Ts

*/
BRST_EXPORT(BRST_STATUS)
BRST_Page_SetTextRise(
    BRST_Page page,
    BRST_REAL value
);

/*--- Text positioning ---------------------------------------------------*/

/**

  \ingroup graphics
  \brief Change current text position using the specified offset values.

  If the current text position is (x<sub>1</sub>, y<sub>1</sub>), the new text position will be (x<sub>1</sub> + x, y<sub>1</sub> + y).

  \copydoc dox_param_page
  \param x, y Offset to new text position.

  \copydoc dox_graphics_mode

  \arg Before \ref BRST_GMODE_TEXT_OBJECT
  \arg After \ref BRST_GMODE_TEXT_OBJECT

  \copydoc dox_return_ok

  \copydoc dox_pdf_cmd
  \c Td

*/
BRST_EXPORT(BRST_STATUS)
BRST_Page_MoveTextPos(
    BRST_Page page,
    BRST_REAL x,
    BRST_REAL y
);

/**

  \ingroup graphics
  \brief Change current text position using the specified offset values.

  If the current text position is (x<sub>1</sub>, y<sub>1</sub>), the new text position will be (x<sub>1</sub> + x, y<sub>1</sub> + y).

  Also, text leading is set to \a -y.

  \copydoc dox_param_page
  \param x, y Offset to new text position.

  \copydoc dox_graphics_mode

  \arg Before \ref BRST_GMODE_TEXT_OBJECT
  \arg After \ref BRST_GMODE_TEXT_OBJECT

  \copydoc dox_return_ok

  \copydoc dox_pdf_cmd
  \c TD

*/
BRST_EXPORT(BRST_STATUS)
BRST_Page_MoveTextPos2(
    BRST_Page page,
    BRST_REAL x,
    BRST_REAL y
);

/* Tm */
BRST_EXPORT(BRST_STATUS)
BRST_Page_SetTextMatrix(
    BRST_Page page,
    BRST_REAL a,
    BRST_REAL b,
    BRST_REAL c,
    BRST_REAL d,
    BRST_REAL x,
    BRST_REAL y
);

/**

  \ingroup graphics
  \brief Move current position for text showing depending on current text showing point and text leading.

  New position is calculated with current text transition matrix.

  \copydoc dox_param_page

  \copydoc dox_graphics_mode

  \arg Before \ref BRST_GMODE_TEXT_OBJECT
  \arg After \ref BRST_GMODE_TEXT_OBJECT

  \copydoc dox_return_ok

  \copydoc dox_pdf_cmd
  \c T*

*/
BRST_EXPORT(BRST_STATUS)
BRST_Page_MoveToNextLine(
    BRST_Page page
);

/*--- Text showing -------------------------------------------------------*/

/**

  \ingroup graphics
  \brief Put text at the current text position on the page.

  \copydoc dox_param_page
  \param text Text to put to page.

  \copydoc dox_graphics_mode

  \arg Before \ref BRST_GMODE_TEXT_OBJECT
  \arg After \ref BRST_GMODE_TEXT_OBJECT

  \copydoc dox_return_ok

  \see BRST_Page_BeginText(), BRST_Page_EndText()

  \copydoc dox_pdf_cmd
  \c Tj

*/
BRST_EXPORT(BRST_STATUS)
BRST_Page_ShowText(
    BRST_Page page,
    BRST_CSTR text
);

/* TJ */

/**

  \ingroup graphics
  \brief Move current text position to the start of the next line, then put the text at the current text position on the page.

  \copydoc dox_param_page
  \param text Text to put to page.

  \copydoc dox_graphics_mode

  \arg Before \ref BRST_GMODE_TEXT_OBJECT
  \arg After \ref BRST_GMODE_TEXT_OBJECT

  \copydoc dox_return_ok

  \see BRST_Page_BeginText(), BRST_Page_EndText()

  \copydoc dox_pdf_cmd
  \c ' (apostrophe)
*/
BRST_EXPORT(BRST_STATUS)
BRST_Page_ShowTextNextLine(
    BRST_Page page,
    BRST_CSTR text
);

/**

  \ingroup graphics
  \brief Move current text position to the start of the next line, then set word spacing and character spacing, finally put the text at the current text position on the page.

  \copydoc dox_param_page
  \param text Text to put to page.
  \param word_space Word spacing value
  \param char_space Char spacing value

  \copydoc dox_graphics_mode

  \arg Before \ref BRST_GMODE_TEXT_OBJECT
  \arg After \ref BRST_GMODE_TEXT_OBJECT

  \copydoc dox_return_ok

  \todo Write note: same as aw Tw; ac Tc; string ', Table 109 of PDF book

  \see BRST_Page_BeginText(), BRST_Page_EndText()

  \copydoc dox_pdf_cmd
  \c " (quote)

*/
BRST_EXPORT(BRST_STATUS)
BRST_Page_ShowTextNextLineEx(
    BRST_Page page,
    BRST_REAL word_space,
    BRST_REAL char_space,
    BRST_CSTR text
);

/**

  \ingroup graphics
  \brief Put text to the specified position.

  \copydoc dox_param_page
  \param xpos, ypos Point position where the text is displayed.
  \param text Text to show.

  \copydoc dox_graphics_mode

  \arg Before \ref BRST_GMODE_TEXT_OBJECT
  \arg After \ref BRST_GMODE_TEXT_OBJECT

  \copydoc dox_return_ok

*/
BRST_EXPORT(BRST_STATUS)
BRST_Page_TextOut(
    BRST_Page page,
    BRST_REAL xpos,
    BRST_REAL ypos,
    BRST_CSTR text
);

/**

  \ingroup graphics
  \brief Put text inside the specified region.

  \copydoc dox_param_page
  \param left, top, right, bottom Coordinates of corners of the region to output text.
  \param text Text to show.
  \param align \parblock Text alignment (one of the following).

  | Value                    | Description                                                       |
  | -----                    | -----------                                                       |
  | \ref BRST_TALIGN_LEFT    | The text is aligned to left.                                      |
  | \ref BRST_TALIGN_RIGHT   | The text is aligned to right.                                     |
  | \ref BRST_TALIGN_CENTER  | The text is aligned to center.                                    |
  | \ref BRST_TALIGN_JUSTIFY | Add spaces between the words to justify both left and right side. |
  \endparblock
  \param len If not \c NULL, the number of characters printed in the area is returned.

  \copydoc dox_graphics_mode

  \arg Before \ref BRST_GMODE_TEXT_OBJECT
  \arg After \ref BRST_GMODE_TEXT_OBJECT

  \return \ref BRST_OK on success. May return \ref BRST_PAGE_INSUFFICIENT_SPACE on success but whole text doesn't fit into declared space. 
  Otherwise, returns error code and calls error handler.

*/
BRST_EXPORT(BRST_STATUS)
BRST_Page_TextRect(
    BRST_Page          page,
    BRST_REAL          left,
    BRST_REAL          top,
    BRST_REAL          right,
    BRST_REAL          bottom,
    BRST_CSTR          text,
    BRST_TextAlignment align,
    BRST_UINT*         len
);

/**

  \ingroup graphics
  \brief Set text character spacing.

  \copydoc dox_param_page
  \param value Character spacing (initial value is \c 0).

  \copydoc dox_graphics_mode

  \arg Before \ref BRST_GMODE_PAGE_DESCRIPTION or \ref BRST_GMODE_TEXT_OBJECT
  \arg After \ref BRST_GMODE_PAGE_DESCRIPTION or \ref BRST_GMODE_TEXT_OBJECT

  \copydoc dox_return_ok

  \copydoc dox_pdf_cmd
  \c Tc

*/
BRST_EXPORT(BRST_STATUS)
BRST_Page_SetCharSpace(
    BRST_Page page,
    BRST_REAL value
);

/**

  \ingroup graphics
  \brief Set text word spacing.

  \copydoc dox_param_page
  \param value Word spacing (initial value is \c 0).

  \copydoc dox_graphics_mode

  \arg Before \ref BRST_GMODE_PAGE_DESCRIPTION or \ref BRST_GMODE_TEXT_OBJECT
  \arg After \ref BRST_GMODE_PAGE_DESCRIPTION or \ref BRST_GMODE_TEXT_OBJECT

  \copydoc dox_return_ok

  \copydoc dox_pdf_cmd
  \c Tw

*/
BRST_EXPORT(BRST_STATUS)
BRST_Page_SetWordSpace(
    BRST_Page page,
    BRST_REAL value
);

/**

  \ingroup page
  \brief Get page current text transformation matrix.

  \copydoc dox_param_page

  \return Page current \ref BRST_Matrix on success, otherwise it returns `{1, 0, 0, 1, 0, 0}`.

*/
BRST_EXPORT(BRST_Matrix)
BRST_Page_TextMatrix(
    BRST_Page page
);

/**

  \ingroup page
  \brief Get page current text leading value.

  \copydoc dox_param_page

  \return Page current text leading value on success, otherwise it returns \c 0.

*/
BRST_EXPORT(BRST_REAL)
BRST_Page_TextLeading(
    BRST_Page page
);

/**

  \ingroup page
  \brief Get page current text rendering mode.

  \copydoc dox_param_page

  \return Page current text rendering mode on success, otherwise it returns \c 0.

*/
BRST_EXPORT(BRST_TextRenderingMode)
BRST_Page_TextRenderingMode(
    BRST_Page page
);

/**

  \ingroup page
  \brief Get page current text rise value.

  \copydoc dox_param_page

  \return Page current text rise value on success, otherwise it returns \c 0.

*/
BRST_EXPORT(BRST_REAL)
BRST_Page_TextRise(
    BRST_Page page
);

/**

  \ingroup page
  \brief Get page current character spacing value.

  \copydoc dox_param_page

  \return Page current character spacing value on success, otherwise it returns \c 0.

*/
BRST_EXPORT(BRST_REAL)
BRST_Page_CharSpace(
    BRST_Page page
);

/**

  \ingroup page
  \brief Get page current word spacing value.

  \copydoc dox_param_page

  \return Page current word spacing value on success, otherwise it returns \c 0.

*/
BRST_EXPORT(BRST_REAL)
BRST_Page_WordSpace(
    BRST_Page page
);

/**

  \ingroup page
  \brief Get current position for text showing.

  Application can call BRST_Page_CurrentTextPos() only when graphics mode is \ref BRST_GMODE_TEXT_OBJECT.

  \copydoc dox_param_page

  \return \ref BRST_Point struct with current position for text showing of the page. Otherwise it returns `BRST_Point{0, 0}`.

*/
BRST_EXPORT(BRST_Point)
BRST_Page_CurrentTextPos(
    BRST_Page page
);

BRST_EXPORT(BRST_STATUS)
BRST_Page_CurrentTextPos2(
    BRST_Page page,
    BRST_Point* pos
);

/**

  \ingroup page
  \brief Get page current font handle.

  \copydoc dox_param_page

  \return Page current font handle on success, otherwise it returns \c NULL.

*/
BRST_EXPORT(BRST_Font)
BRST_Page_CurrentFont(
    BRST_Page page
);

/**

  \ingroup page
  \brief Get page current font size.

  \copydoc dox_param_page

  \return Page current font size on success, otherwise it returns \c 0.

*/
BRST_EXPORT(BRST_REAL)
BRST_Page_CurrentFontSize(
    BRST_Page page
);

/**

  \ingroup page
  \brief Get text width in current font size, character spacing and word spacing.

  \copydoc dox_param_page
  \param text Text to get width

  \return Text width in current font size, character spacing and word spacing. Otherwise it returns \c 0 and calls error handler.

  \copydoc dox_error_codes

  - \ref BRST_INVALID_PAGE
  - \ref BRST_FAILED_TO_ALLOC_MEM
  - \ref BRST_PAGE_FONT_NOT_FOUND

*/
BRST_EXPORT(BRST_REAL)
BRST_Page_TextWidth(
    BRST_Page page,
    BRST_CSTR text
);

/**

  \ingroup page
  \brief Calculate byte length which can be included within the specified width.

  \copydoc dox_param_page
  \param text Text to get width
  \param width Width of the area to put text.
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

  \copydoc dox_error_codes

  - \ref BRST_INVALID_PAGE
  - \ref BRST_PAGE_FONT_NOT_FOUND

*/
BRST_EXPORT(BRST_UINT)
BRST_Page_MeasureText(
    BRST_Page  page,
    BRST_CSTR  text,
    BRST_REAL  width,
    BRST_BOOL  wordwrap,
    BRST_REAL* real_width
);

#endif /* BRST_TEXT_H */