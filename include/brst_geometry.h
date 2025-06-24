#ifndef BRST_GEOMETRY_H
#define BRST_GEOMETRY_H

#include "brst_external.h"
#include "brst_types.h"
#include "brst_page.h"
#include "brst_geometry_defines.h"
#include "brst_shading.h"

/**

  \ingroup graphics
  \brief Save the page's current graphics state to the stack.

  Application can call BRST_Page_GSave() and can restore saved state by calling BRST_Page_GRestore().

  Saved by BRST_Page_GSave() state parameters are:

    - Character Spacing
    - Clipping Path
    - Dash Mode
    - Filling Color
    - Flatness
    - Font
    - Font Size
    - Horizontal Scaling
    - Line Width
    - Line Cap Style
    - Line Join Style
    - Miter Limit
    - Rendering Mode
    - Stroking Color
    - Text Leading
    - Text Rise
    - Transformation Matrix
    - Word Spacing

  \copydoc dox_param_page

  \copydoc dox_graphics_mode

  \arg Before \ref BRST_GMODE_PAGE_DESCRIPTION
  \arg After \ref BRST_GMODE_PAGE_DESCRIPTION

  \copydoc dox_return_ok

  \copydoc dox_pdf_cmd
  \c q

*/
BRST_EXPORT(BRST_STATUS)
BRST_Page_GSave(
    BRST_Page page
);

/**

  \ingroup graphics
  \brief Restore graphics state which is saved by BRST_Page_GSave().

  \copydoc dox_param_page

  \copydoc dox_graphics_mode

  \arg Before \ref BRST_GMODE_PAGE_DESCRIPTION
  \arg After \ref BRST_GMODE_PAGE_DESCRIPTION

  \copydoc dox_return_ok

  \copydoc dox_pdf_cmd
  \c Q

*/
BRST_EXPORT(BRST_STATUS)
BRST_Page_GRestore(
    BRST_Page page
);

/**

  \ingroup graphics
  \brief Concatenate the page's transformation matrix and specified matrix.

  For example, if you want to rotate the coordinate system of the page by 45 degrees, use BRST_Page_Concat() as follows.

  \code
  float rad1 = 45 / 180 * 3.141592;
  BRST_Page_Concat (page, cos (rad1), sin (rad1), -sin (rad1), cos (rad1), 220, 350);
  \endcode

  To change the coordinate system of the page to 300 dpi, use BRST_Page_Concat() as follows.

  \code
  BRST_Page_Concat (page, 72.0f / 300.0f, 0, 0, 72.0f / 300.0f, 0, 0);
  \endcode

  Invoke BRST_Page_GSave() before BRST_Page_Concat(). Then the change by BRST_Page_Concat() can be restored by invoking BRST_Page_GRestore().

  \code
  // Save current graphics state
  BRST_Page_GSave (page);

  //Concatenate transformation matrix
  BRST_Page_Concat (page, 72.0f / 300.0f, 0, 0, 72.0f / 300.0f, 0, 0);

  // Show text on translated coordinates
  BRST_Page_BeginText (page);
  BRST_Page_MoveTextPos (page, 50, 100);
  BRST_Page_ShowText (page, "Text on the translated coordinates");
  BRST_Page_EndText (page);

  // Restore the graphics states
  BRST_Page_GRestore (page);
  \endcode

  Application can call BRST_Page_GSave() when graphics mode is \ref BRST_GMODE_PAGE_DESCRIPTION.

  \copydoc dox_param_page
  \param a, b, c, d, x, y Transformation matrix to concatenate.

  \copydoc dox_return_ok

  \copydoc dox_pdf_cmd
  \c cm

  \see BRST_Page_Translate(), BRST_Page_Scale(), BRST_Page_Rotate(), BRST_Page_Skew()

*/
BRST_EXPORT(BRST_STATUS)
BRST_Page_Concat(
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
  \brief Concatenate the page's transformation matrix with translation matrix.

  Coordinate system is translated by \c dx and \c dy coordinate units.

  \copydoc dox_param_page
  \param dx, dy Coordinate system translate distance.

  \copydoc dox_return_ok

  \copydoc dox_pdf_cmd
  \c cm

  \see BRST_Page_Concat()

  \note Corresponds to `BRST_Page_Concat (page, 1, 0, 0, 1, dx, dy);`
*/
BRST_EXPORT(BRST_STATUS)
BRST_Page_Translate(
    BRST_Page page,
    BRST_REAL dx,
    BRST_REAL dy
);

/**

  \ingroup graphics
  \brief Concatenate the page's transformation matrix with scale matrix.

  Coordinate system is scaled so 1 unit horizontal dimension is same as
  \c sx units and 1 unit in vertical dimension is same as \c sy units
  in new coordinate system..

  \copydoc dox_param_page
  \param sx, sy Coordinate system scale values.

  \copydoc dox_return_ok

  \copydoc dox_pdf_cmd
  \c cm

  \see BRST_Page_Concat()

  \note Corresponds to `BRST_Page_Concat (page, sx, 0, 0, sy, 0, 0);`

*/
BRST_EXPORT(BRST_STATUS)
BRST_Page_Scale(
    BRST_Page page,
    BRST_REAL sx,
    BRST_REAL sy
);

/**

  \ingroup graphics
  \brief Concatenate the page's transformation matrix with rotate matrix.

  Coordinate system axes are rotated by angle \c a counter clocwise (degrees).

  \copydoc dox_param_page
  \param degrees Coordinate system rotate angle (degrees).

  \copydoc dox_return_ok

  \copydoc dox_pdf_cmd
  \c cm

  \see BRST_Page_Concat(), BRST_Page_Rotate()

*/
BRST_EXPORT(BRST_STATUS)
BRST_Page_RotateDeg(
    BRST_Page page,
    BRST_REAL degrees
);

/**

  \ingroup graphics
  \brief Concatenate the page's transformation matrix with rotate matrix.

  Coordinate system axes are rotated by angle \c a counter clocwise.

  \copydoc dox_param_page
  \param radians Coordinate system rotate angle (radians).

  \copydoc dox_return_ok

  \copydoc dox_pdf_cmd
  \c cm

  \see BRST_Page_Concat(), BRST_Page_RotateDeg()

  \note Corresponds to `BRST_Page_Concat (page, cos(q), sin(q), -sin(q), cos(q), 0, 0);`

*/
BRST_EXPORT(BRST_STATUS)
BRST_Page_Rotate(
    BRST_Page page,
    BRST_REAL radians
);

/**

  \ingroup graphics
  \brief Concatenate the page's transformation matrix with skew matrix.

  Coordinate system is skewed by an angle \c a at \a x axis and by angle \c b at \a y axis.

  \copydoc dox_param_page
  \param a, b Coordinate system skew values.

  \copydoc dox_return_ok

  \copydoc dox_pdf_cmd
  \c cm

  \see BRST_Page_Concat()

  \note Corresponds to `BRST_Page_Concat (page, 1, tan(a), tan(b), 1, 0, 0);`

*/
BRST_EXPORT(BRST_STATUS)
BRST_Page_Skew(
    BRST_Page page,
    BRST_REAL a,
    BRST_REAL b
);

/**

  \ingroup graphics
  \brief Append circle to current path.

  \copydoc dox_param_page
  \param x, y Center point of the circle.
  \param radius Circle radius

  \copydoc dox_graphics_mode

  \arg Before \ref BRST_GMODE_PAGE_DESCRIPTION or \ref BRST_GMODE_PATH_OBJECT
  \arg After \ref BRST_GMODE_PATH_OBJECT

  \copydoc dox_return_ok

*/
BRST_EXPORT(BRST_STATUS)
BRST_Page_Circle(
    BRST_Page page,
    BRST_REAL x,
    BRST_REAL y,
    BRST_REAL radius
);

/**

  \ingroup graphics
  \brief Append ellipse to current path.

  \copydoc dox_param_page
  \param x, y Center point of the ellipse.
  \param x_radius, y_radius Horizontal and vertical radii of the ellipse.

  \copydoc dox_graphics_mode

  \arg Before \ref BRST_GMODE_PATH_OBJECT
  \arg After \ref BRST_GMODE_PATH_OBJECT

  \copydoc dox_return_ok

*/
BRST_EXPORT(BRST_STATUS)
BRST_Page_Ellipse(
    BRST_Page page,
    BRST_REAL x,
    BRST_REAL y,
    BRST_REAL x_radius,
    BRST_REAL y_radius
);

/**

  \ingroup graphics
  \brief Append circle arc to current path.

  Angles are given in degrees, with 0 degrees being vertical, upward, from the `(x, y)` position.

  \copydoc dox_param_page
  \param x, y Center point of the circle.
  \param radius Radius of the circle.
  \param angle1 Angle at the beginning of the arc.
  \param angle2 Angle at the end of the arc. It must be greater than \c ang1.

  \copydoc dox_graphics_mode

  \arg Before \ref BRST_GMODE_PAGE_DESCRIPTION or \ref BRST_GMODE_PATH_OBJECT.
  \arg After \ref BRST_GMODE_PATH_OBJECT.

  \copydoc dox_return_ok

*/
BRST_EXPORT(BRST_STATUS)
BRST_Page_Arc(
    BRST_Page page,
    BRST_REAL x,
    BRST_REAL y,
    BRST_REAL radius,
    BRST_REAL angle1,
    BRST_REAL angle2
);
/**

  \ingroup graphics
  \brief Set the filling color (Gray).

  \copydoc dox_param_page
  \param value Value of the gray level between \c 0 and \c 1.

  \copydoc dox_graphics_mode

  \arg Before \ref BRST_GMODE_PAGE_DESCRIPTION or \ref BRST_GMODE_TEXT_OBJECT
  \arg After \ref BRST_GMODE_PAGE_DESCRIPTION or \ref BRST_GMODE_TEXT_OBJECT

  \copydoc dox_return_ok

  \see BRST_Page_GrayFill()

  \copydoc dox_pdf_cmd
  \c g

*/
BRST_EXPORT(BRST_STATUS)
BRST_Page_SetGrayFill(
    BRST_Page page,
    BRST_REAL value
);

/**

  \ingroup graphics
  \brief Set stroking color (Gray).

  \copydoc dox_param_page
  \param value Value of the gray level between \c 0 and \c 1.

  \copydoc dox_graphics_mode

  \arg Before \ref BRST_GMODE_PAGE_DESCRIPTION or \ref BRST_GMODE_TEXT_OBJECT
  \arg After \ref BRST_GMODE_PAGE_DESCRIPTION or \ref BRST_GMODE_TEXT_OBJECT

  \copydoc dox_return_ok

  \see BRST_Page_GrayStroke()

  \copydoc dox_pdf_cmd
  \c G

*/
BRST_EXPORT(BRST_STATUS)
BRST_Page_SetGrayStroke(
    BRST_Page page,
    BRST_REAL value
);

/**

  \ingroup graphics
  \brief Set filling color (RGB).

  \copydoc dox_param_page
  \param r, g, b Level of each color element. They must be between \c 0 and \c 1.

  \copydoc dox_graphics_mode

  \arg Before \ref BRST_GMODE_PAGE_DESCRIPTION or \ref BRST_GMODE_TEXT_OBJECT.
  \arg After \ref BRST_GMODE_PAGE_DESCRIPTION or \ref BRST_GMODE_TEXT_OBJECT.

  \copydoc dox_return_ok

  \see BRST_Page_RGBFill()

  \copydoc dox_pdf_cmd
  \c rg

*/
BRST_EXPORT(BRST_STATUS)
BRST_Page_SetRGBFill(
    BRST_Page  page,
    BRST_REAL  r,
    BRST_REAL  g,
    BRST_REAL  b);

/**

  \ingroup graphics
  \brief Set stroke color (RGB).

  \copydoc dox_param_page
  \param r, g, b Level of each color element. They must be between \c 0 and \c 1.

  \copydoc dox_graphics_mode

  \arg Before \ref BRST_GMODE_PAGE_DESCRIPTION or \ref BRST_GMODE_TEXT_OBJECT.
  \arg After \ref BRST_GMODE_PAGE_DESCRIPTION or \ref BRST_GMODE_TEXT_OBJECT.

  \copydoc dox_return_ok

  \see BRST_Page_RGBStroke()

  \copydoc dox_pdf_cmd
  \c RG

*/
BRST_EXPORT(BRST_STATUS)
BRST_Page_SetRGBStroke(
    BRST_Page page,
    BRST_REAL r,
    BRST_REAL g,
    BRST_REAL b
);

/**

  \ingroup graphics
  \brief Set stroke color (RGB) using \ref BRST_UINT8 values.

  \copydoc dox_param_page
  \param r, g, b Level of each color element. They must be between \c 0x00 and \c 0xFF.

  \copydoc dox_graphics_mode

  \arg Before \ref BRST_GMODE_PAGE_DESCRIPTION or \ref BRST_GMODE_TEXT_OBJECT.
  \arg After \ref BRST_GMODE_PAGE_DESCRIPTION or \ref BRST_GMODE_TEXT_OBJECT.

  \copydoc dox_return_ok

  \see BRST_Page_RGBStroke(), BRST_Page_SetRGBStroke()

  \copydoc dox_pdf_cmd
  \c RG

*/
BRST_EXPORT(BRST_STATUS)
BRST_Page_SetRGBStrokeHex(
    BRST_Page  page,
    BRST_UINT8  r,
    BRST_UINT8  g,
    BRST_UINT8  b
);

/**

  \ingroup graphics
  \brief Set filling color (CMYK).

  \copydoc dox_param_page
  \param c, m, y, k Level of each color element. They must be between \c 0 and \c 1.

  \copydoc dox_graphics_mode

  \arg Before \ref BRST_GMODE_PAGE_DESCRIPTION or \ref BRST_GMODE_TEXT_OBJECT.
  \arg After \ref BRST_GMODE_PAGE_DESCRIPTION or \ref BRST_GMODE_TEXT_OBJECT.

  \copydoc dox_return_ok

  \see BRST_Page_CMYKFill()

  \copydoc dox_pdf_cmd
  \c k

*/
BRST_EXPORT(BRST_STATUS)
BRST_Page_SetCMYKFill(
    BRST_Page page,
    BRST_REAL c,
    BRST_REAL m,
    BRST_REAL y,
    BRST_REAL k
);

/**

  \ingroup graphics
  \brief Set stroke color (CMYK).

  \copydoc dox_param_page
  \param c, m, y, k Level of each color element. They must be between \c 0 and \c 1.

  \copydoc dox_graphics_mode

  \arg Before \ref BRST_GMODE_PAGE_DESCRIPTION or \ref BRST_GMODE_TEXT_OBJECT.
  \arg After \ref BRST_GMODE_PAGE_DESCRIPTION or \ref BRST_GMODE_TEXT_OBJECT.

  \copydoc dox_return_ok

  \see BRST_Page_CMYKStroke()

  \copydoc dox_pdf_cmd
  \c K

*/
BRST_EXPORT(BRST_STATUS)
BRST_Page_SetCMYKStroke(
    BRST_Page page,
    BRST_REAL c,
    BRST_REAL m,
    BRST_REAL y,
    BRST_REAL k
);

/**

  \ingroup graphics
  \brief Modify current clipping path by intersecting it with current path using the nonzero winding number rule.

  The clipping path is only modified after the succeeding painting operator.
  To avoid painting the current path, use the function BRST_Page_EndPath().

  Following painting operations will only affect the regions of the page contained by the clipping path.
  Initially, the clipping path includes the entire page. There is no way to enlarge the current clipping path
  or to replace the clipping path with a new one. The functions BRST_Page_GSave() and BRST_Page_GRestore()
  may be used to save and restore the current graphics state, including the clipping path.

  \copydoc dox_param_page

  \copydoc dox_graphics_mode

  \arg Before \ref BRST_GMODE_PATH_OBJECT
  \arg After \ref BRST_GMODE_PATH_OBJECT

  \copydoc dox_return_ok

  \see BRST_Page_EndPath(), BRST_Page_GSave(), BRST_Page_GRestore(), BRST_Page_Eoclip()

  \copydoc dox_pdf_cmd
  \c W

*/
BRST_EXPORT(BRST_STATUS)
BRST_Page_Clip(
    BRST_Page page
);

/**

  \ingroup graphics
  \brief Modifies the current clipping path by intersecting it with  current path using the even-odd rule.
  Clipping path is only modified after succeeding painting operator. To avoid painting current path, use BRST_Page_EndPath().

  Following painting operations will only affect page regions contained by the clipping path.
  Clipping path includes entire page initially. There is no way to enlarge current clipping path
  or to replace clipping path with new one. Functions BRST_Page_GSave() and BRST_Page_GRestore()
  may be used to save and restore the current graphics state, including the clipping path.

  \copydoc dox_param_page

  \copydoc dox_graphics_mode

  \arg Before \ref BRST_GMODE_PATH_OBJECT
  \arg After \ref BRST_GMODE_PATH_OBJECT

  \copydoc dox_return_ok

  \see BRST_Page_EndPath(), BRST_Page_GSave(), BRST_Page_GRestore(), BRST_Page_Clip()

  \copydoc dox_pdf_cmd
  \c W*

*/
BRST_EXPORT(BRST_STATUS)
BRST_Page_Eoclip(
    BRST_Page page
);

/**

  \ingroup graphics
  \brief Paint current path.

  \copydoc dox_param_page

  \copydoc dox_graphics_mode

  \arg Before \ref BRST_GMODE_PATH_OBJECT
  \arg After \ref BRST_GMODE_PAGE_DESCRIPTION

  \copydoc dox_return_ok

  \copydoc dox_pdf_cmd
  \c S

*/
BRST_EXPORT(BRST_STATUS)
BRST_Page_Stroke(
    BRST_Page page
);

/**

  \ingroup graphics
  \brief Close and paint current path.

  \copydoc dox_param_page

  \copydoc dox_graphics_mode

  \arg Before \ref BRST_GMODE_PATH_OBJECT
  \arg After \ref BRST_GMODE_PAGE_DESCRIPTION

  \copydoc dox_return_ok

  \copydoc dox_pdf_cmd
  \c s

*/
BRST_EXPORT(BRST_STATUS)
BRST_Page_ClosePathStroke(
    BRST_Page page
);

/**

  \ingroup graphics
  \brief Fill current path using non-zero winding number rule.

  \copydoc dox_param_page

  \copydoc dox_graphics_mode

  \arg Before \ref BRST_GMODE_PATH_OBJECT
  \arg After \ref BRST_GMODE_PAGE_DESCRIPTION

  \copydoc dox_return_ok

  \copydoc dox_pdf_cmd
  \c f

*/
BRST_EXPORT(BRST_STATUS)
BRST_Page_Fill(
    BRST_Page page
);

/**

  \ingroup graphics
  \brief Fill current path using even-odd rule.

  \copydoc dox_param_page

  \copydoc dox_graphics_mode

  \arg Before \ref BRST_GMODE_PATH_OBJECT
  \arg After \ref BRST_GMODE_PAGE_DESCRIPTION

  \copydoc dox_return_ok

  \copydoc dox_pdf_cmd
  \c f*

*/
BRST_EXPORT(BRST_STATUS)
BRST_Page_Eofill(
    BRST_Page page
);

/**

  \ingroup graphics
  \brief Fill current path using the even-odd rule.

  \copydoc dox_param_page

  \copydoc dox_graphics_mode

  \arg Before \ref BRST_GMODE_PATH_OBJECT
  \arg After \ref BRST_GMODE_PAGE_DESCRIPTION

  \copydoc dox_return_ok

  \copydoc dox_pdf_cmd
  \c B

*/
BRST_EXPORT(BRST_STATUS)
BRST_Page_FillStroke(
    BRST_Page page
);

/**

  \ingroup graphics
  \brief Fill current path using the even-odd rule and then paint the path.

  \copydoc dox_param_page

  \copydoc dox_graphics_mode
  \arg Before \ref BRST_GMODE_PATH_OBJECT
  \arg After \ref BRST_GMODE_PAGE_DESCRIPTION

  \copydoc dox_return_ok

  \copydoc dox_pdf_cmd
  \c B*

*/
BRST_EXPORT(BRST_STATUS)
BRST_Page_EofillStroke(
    BRST_Page page
);

/**

  \ingroup graphics
  \brief Close current path, fill current path using the non-zero winding number rule, then paint path.

  \copydoc dox_param_page

  \copydoc dox_graphics_mode
  \arg Before \ref BRST_GMODE_PATH_OBJECT
  \arg After \ref BRST_GMODE_PAGE_DESCRIPTION

  \copydoc dox_return_ok

  \copydoc dox_pdf_cmd
  \c b

*/
BRST_EXPORT(BRST_STATUS)
BRST_Page_ClosePathFillStroke(
    BRST_Page page
);

/**

  \ingroup graphics
  \brief Close current path, fill current path using the even-odd rule and then paint the path.

  \copydoc dox_param_page

  \copydoc dox_graphics_mode
  \arg Before \ref BRST_GMODE_PATH_OBJECT
  \arg After \ref BRST_GMODE_PAGE_DESCRIPTION

  \copydoc dox_return_ok

  \copydoc dox_pdf_cmd
  \c b*

*/
BRST_EXPORT(BRST_STATUS)
BRST_Page_ClosePathEofillStroke(
    BRST_Page page
);

/**

  \ingroup graphics
  \brief Finish path object without filling or painting.

  \copydoc dox_param_page

  \copydoc dox_graphics_mode

  \arg Before \ref BRST_GMODE_PATH_OBJECT
  \arg After \ref BRST_GMODE_PAGE_DESCRIPTION

  \copydoc dox_return_ok

  \copydoc dox_pdf_cmd
  \c n

*/
BRST_EXPORT(BRST_STATUS)
BRST_Page_EndPath(
    BRST_Page page
);

/**

  \ingroup graphics
  \brief Start new subpath and move current point for drawing path.

  BRST_Page_MoveTo() set starting point for the path to (x, y).

  \copydoc dox_param_page
  \param x, y Starting point for drawing path

  \copydoc dox_graphics_mode

  \arg Before \ref BRST_GMODE_PAGE_DESCRIPTION or \ref BRST_GMODE_PATH_OBJECT
  \arg After \ref BRST_GMODE_PATH_OBJECT

  \copydoc dox_return_ok

  \copydoc dox_pdf_cmd
  \c m

*/
BRST_EXPORT(BRST_STATUS)
BRST_Page_MoveTo(
    BRST_Page page,
    BRST_REAL x,
    BRST_REAL y
);

/**

  \ingroup graphics
  \brief Append path from current point to specified point.

  \copydoc dox_param_page
  \param x, y End point of the path

  \copydoc dox_graphics_mode

  \arg Before \ref BRST_GMODE_PATH_OBJECT
  \arg After \ref BRST_GMODE_PATH_OBJECT

  \copydoc dox_return_ok

  \copydoc dox_pdf_cmd
  \c l

*/
BRST_EXPORT(BRST_STATUS)
BRST_Page_LineTo(
    BRST_Page page,
    BRST_REAL x,
    BRST_REAL y
);

/**

  \ingroup graphics
  \brief Append Bézier curve to current path using control points
  (x<sub>1</sub>, y<sub>1</sub>) and (x<sub>2</sub>, y<sub>2</sub>)
  and (x<sub>3</sub>, y<sub>3</sub>), then set current point
  to (x<sub>3</sub>, y<sub>3</sub>).

  \image html img/curveto.png

  \copydoc dox_param_page
  \param x1, y1, x2, y2, x3, y3 Control points for Bézier curve.

  \copydoc dox_graphics_mode

  \arg Before \ref BRST_GMODE_PATH_OBJECT
  \arg After \ref BRST_GMODE_PATH_OBJECT

  \copydoc dox_return_ok

  \copydoc dox_pdf_cmd
  \c c

*/
BRST_EXPORT(BRST_STATUS)
BRST_Page_CurveTo(
    BRST_Page page,
    BRST_REAL x1,
    BRST_REAL y1,
    BRST_REAL x2,
    BRST_REAL y2,
    BRST_REAL x3,
    BRST_REAL y3
);

/**

  \ingroup graphics
  \brief Append Bézier curve to current path using current point and (x<sub>2</sub>, y<sub>2</sub>)
  and (x<sub>3</sub>, y<sub>3</sub>) as control points. Then current point is set to (x<sub>3</sub>, y<sub>3</sub>).

  \image html img/curveto2.png

  \copydoc dox_param_page
  \param x2, y2, x3, y3 Control points for Bézier curve along with current point.

  \copydoc dox_graphics_mode

  \arg Before \ref BRST_GMODE_PATH_OBJECT
  \arg After \ref BRST_GMODE_PATH_OBJECT

  \copydoc dox_return_ok

  \copydoc dox_pdf_cmd
  \c v

*/
BRST_EXPORT(BRST_STATUS)
BRST_Page_CurveTo2(
    BRST_Page page,
    BRST_REAL x2,
    BRST_REAL y2,
    BRST_REAL x3,
    BRST_REAL y3
);

/**

  \ingroup graphics
  \brief Append Bézier curve to the current path using two specified points.
  The point (x<sub>1</sub>, y<sub>1</sub>) and the point (x<sub>3</sub>, y<sub>3</sub>)
  are used as the control points for a Bézier curve and current point is moved to the point
  (x<sub>3</sub>, y<sub>3</sub>).

  \image html img/curveto3.png

  \copydoc dox_param_page
  \param x1, y1, x3, y3 Control points for Bézier curve along with current point.

  \copydoc dox_graphics_mode

  \arg Before \ref BRST_GMODE_PATH_OBJECT
  \arg After \ref BRST_GMODE_PATH_OBJECT

  \copydoc dox_return_ok

  \copydoc dox_pdf_cmd
  \c y

*/
BRST_EXPORT(BRST_STATUS)
BRST_Page_CurveTo3(
    BRST_Page  page,
    BRST_REAL  x1,
    BRST_REAL  y1,
    BRST_REAL  x3,
    BRST_REAL  y3
);

/**

  \ingroup graphics
  \brief Append straight line from current point to the start point of subpath.

  Current point is moved to the start point of subpath.

  \copydoc dox_param_page

  \copydoc dox_graphics_mode

  \arg Before \ref BRST_GMODE_PATH_OBJECT
  \arg After \ref BRST_GMODE_PATH_OBJECT

  \copydoc dox_return_ok

  \copydoc dox_pdf_cmd
  \c h

*/
BRST_EXPORT(BRST_STATUS)
BRST_Page_ClosePath(
    BRST_Page page
);

/**

  \ingroup graphics
  \brief Append rectangle to the current path.

  \copydoc dox_param_page
  \param x, y Lower-left point of the rectangle.
  \param width Width of the rectangle.
  \param height Height of the rectangle.

  \copydoc dox_graphics_mode

  \arg Before \ref BRST_GMODE_PAGE_DESCRIPTION or \ref BRST_GMODE_PATH_OBJECT
  \arg After \ref BRST_GMODE_PATH_OBJECT

  \copydoc dox_return_ok

  \copydoc dox_pdf_cmd
  \c re

*/
BRST_EXPORT(BRST_STATUS)
BRST_Page_Rectangle(
    BRST_Page page,
    BRST_REAL x,
    BRST_REAL y,
    BRST_REAL width,
    BRST_REAL height
);

/**

  \ingroup graphics
  \brief Set width of the line used to stroke paths.

  \copydoc dox_param_page
  \param line_width The line width to use.

  Default \c line_width is \c 1.

  \copydoc dox_graphics_mode

  \arg Before \ref BRST_GMODE_PAGE_DESCRIPTION or \ref BRST_GMODE_TEXT_OBJECT
  \arg After \ref BRST_GMODE_PAGE_DESCRIPTION or \ref BRST_GMODE_TEXT_OBJECT

  \copydoc dox_return_ok

  \par Example

  A miter limit of 1.414 converts miters to bevels for \c angle less than \c 90 degrees,
  a limit of \c 2.0 converts them for \c angle less than 60 degrees, and a limit of 10.0
  converts them for angle less than approximately 11.5 degrees.

  \copydoc dox_pdf_cmd
  \c w

*/
BRST_EXPORT(BRST_STATUS)
BRST_Page_SetLineWidth(
    BRST_Page page,
    BRST_REAL line_width
);

/**

  \ingroup graphics
  \brief Set lines endpoints shape style.

  \copydoc dox_param_page
  \param line_cap The line cap style (one of the following).

  | Value                           | Image                    | Description                                                             |
  | -----                           | -----                    | -----------                                                             |
  | \ref BRST_BUTT_END              | \image html linecap1.png | Line is squared off at path endpoint.                                   |
  | \ref BRST_ROUND_END             | \image html linecap2.png | End of line becomes a semicircle with center  at path endpoint.         |
  | \ref BRST_PROJECTING_SQUARE_END | \image html linecap3.png | Line continues beyond endpoint, goes on half the endpoint stroke width. |

  Default \c line_cap is \ref BRST_BUTT_END

  \copydoc dox_graphics_mode

  \arg Before \ref BRST_GMODE_PAGE_DESCRIPTION or \ref BRST_GMODE_TEXT_OBJECT
  \arg After \ref BRST_GMODE_PAGE_DESCRIPTION or \ref BRST_GMODE_TEXT_OBJECT

  \copydoc dox_return_ok

  \copydoc dox_pdf_cmd
  \c J

*/
BRST_EXPORT(BRST_STATUS)
BRST_Page_SetLineCap(
    BRST_Page    page,
    BRST_LineCap line_cap
);

/**

  \ingroup graphics
  \brief Set line join shape style.

  \copydoc dox_param_page
  \param line_join The line join style (one of the following).

  | Value                | Image                     | Description                                                                                                                      |
  | -----                | -----                     | -----------                                                                                                                      |
  | \ref BRST_MITER_JOIN | \image html linejoin1.png | Outer edges of the strokes for the two segments are extended until they meet at an angle.                                        |
  | \ref BRST_ROUND_JOIN | \image html linejoin2.png | An arc of a circle with a diameter equal to the line width is drawn around the point where the two segments meet.                |
  | \ref BRST_BEVEL_JOIN | \image html linejoin3.png | The two segments are finished with butt caps and the resulting notch beyond the ends of the segments are filled with a triangle. |

  Default \c line_join is \ref BRST_MITER_JOIN.

  \copydoc dox_graphics_mode

  \arg Before \ref BRST_GMODE_PAGE_DESCRIPTION or \ref BRST_GMODE_TEXT_OBJECT
  \arg After \ref BRST_GMODE_PAGE_DESCRIPTION or \ref BRST_GMODE_TEXT_OBJECT

  \copydoc dox_return_ok

  \copydoc dox_pdf_cmd
  \c j

*/
BRST_EXPORT(BRST_STATUS)
BRST_Page_SetLineJoin(
    BRST_Page     page,
    BRST_LineJoin line_join
);

/**

  \ingroup graphics
  \brief Set miter limit for line joins.

  \copydoc dox_param_page
  \param miter_limit Miter limit value.

  Default \c miter_limit is \ref BRST_DEF_MITERLIMIT.

  \copydoc dox_graphics_mode

  \arg Before \ref BRST_GMODE_PAGE_DESCRIPTION or \ref BRST_GMODE_TEXT_OBJECT
  \arg After \ref BRST_GMODE_PAGE_DESCRIPTION or \ref BRST_GMODE_TEXT_OBJECT

  \copydoc dox_return_ok

  \note A miter limit of 1.414 converts miters to bevels for \c angle less than \c 90 degrees,
  a limit of \c 2.0 converts them for \c angle less than 60 degrees, and a limit of 10.0
  converts them for angle less than approximately 11.5 degrees.

  \copydoc dox_pdf_cmd
  \c M

*/
BRST_EXPORT(BRST_STATUS)
BRST_Page_SetMiterLimit(
    BRST_Page  page,
    BRST_REAL  miter_limit
);

/**

  \ingroup graphics
  \brief Set dash pattern for lines in the page.

  \copydoc dox_param_page
  \param dash_pattern Pattern of dashes and gaps used to stroke paths.
  \param num_elem Number of elements in dash_pattern, `0 <= num_param <= 8`.
  \param phase Phase in which pattern begins (default is \c 0).

  \copydoc dox_graphics_mode
  \arg Before \ref BRST_GMODE_PAGE_DESCRIPTION or \ref BRST_GMODE_TEXT_OBJECT
  \arg After \ref BRST_GMODE_PAGE_DESCRIPTION or \ref BRST_GMODE_TEXT_OBJECT

  \copydoc dox_return_ok

  \par Examples

  `dash_ptn = NULL`, `num_elem = 0`, `phase = 0` (default for new page)

  \image html setdash1.png

  `dash_ptn = [3]`, `num_elem = 1`, `phase = 1`

  \image html setdash2.png

  `dash_ptn = [7,]`, `num_elem = 2`, `phase = 2`

  \image html setdash3.png

  `dash_ptn = [8,]`, `num_elem = 4`, `phase = 0`

  \image html setdash4.png

  \copydoc dox_pdf_cmd
  \c d

*/
BRST_EXPORT(BRST_STATUS)
BRST_Page_SetDash(
    BRST_Page        page,
    const BRST_REAL* dash_pattern,
    BRST_UINT        num_elem,
    BRST_REAL        phase
);


/* ri --not implemented yet */

/* i */
BRST_EXPORT(BRST_STATUS)
BRST_Page_SetFlat(
    BRST_Page page,
    BRST_REAL flatness
);

/**

  \ingroup page
  \brief Get page current filling color value (RGB).

  BRST_Page_RGBFill() is valid only when the page's filling color space is \ref BRST_CS_DEVICE_RGB.

  \copydoc dox_param_page

  \return Page current filling color value (RGB) on success, otherwise it returns `BRST_RGBColor{0, 0, 0}`.

*/
BRST_EXPORT(BRST_RGBColor)
BRST_Page_RGBFill_Value(
    BRST_Page page
);

/**

  \ingroup page
  \brief Get page current stroke color value (RGB).

  BRST_Page_RGBStroke() is valid only when the page's stroke color space is \ref BRST_CS_DEVICE_RGB.

  \copydoc dox_param_page

  \return Page current stroke color value (RGB) on success, otherwise it returns `BRST_RGBColor{0, 0, 0}`.

*/
BRST_EXPORT(BRST_RGBColor)
BRST_Page_RGBStroke_Value(
    BRST_Page page
);

/**

  \ingroup page
  \brief Get page current filling color value (CMYK).

  BRST_Page_CMYKFill() is valid only when the page's filling color space is \ref BRST_CS_DEVICE_CMYK.

  \copydoc dox_param_page

  \return Page current filling color value (CMYK) on success, otherwise it returns `BRST_CMYKColor{0, 0, 0, 0}`.

*/
BRST_EXPORT(BRST_CMYKColor)
BRST_Page_CMYKFill_Value(
    BRST_Page page
);

/**

  \ingroup page
  \brief Get page current stroke color value (CMYK).

  BRST_Page_CMYKStroke() is valid only when the page's stroke color space is \ref BRST_CS_DEVICE_CMYK.

  \copydoc dox_param_page

  \return Page current stroke color value (CMYK) on success, otherwise it returns `BRST_CMYKColor{0, 0, 0, 0}`.

*/
BRST_EXPORT(BRST_CMYKColor)
BRST_Page_CMYKStroke_Value(
    BRST_Page page
);

/**

  \ingroup page
  \brief Get page current filling color value (Gray).

  BRST_Page_GrayFill() is valid only when the page's filling color space is \ref BRST_CS_DEVICE_GRAY.

  \copydoc dox_param_page

  \return Page current filling color value (Gray) on success, otherwise it returns \c 0.

*/
BRST_EXPORT(BRST_REAL)
BRST_Page_GrayFill_Value(
    BRST_Page page
);

/**

  \ingroup page
  \brief Get page current stroke color value (Gray).

  BRST_Page_GrayStroke() is valid only when the page's stroke color space is \ref BRST_CS_DEVICE_GRAY.

  \copydoc dox_param_page

  \return Page current stroke color value (Gray) on success, otherwise it returns \c 0.

*/
BRST_EXPORT(BRST_REAL)
BRST_Page_GrayStroke_Value(
    BRST_Page page
);

/**

  \ingroup page
  \brief Get page current stroke color space.

  \copydoc dox_param_page

  \return Page current stroke color space on success, otherwise it returns \ref BRST_CS_EOF.

*/
BRST_EXPORT(BRST_ColorSpace)
BRST_Page_StrokingColorSpace_Value(
    BRST_Page page
);

/**

  \ingroup page
  \brief Get page current filling color space.

  \copydoc dox_param_page

  \return Page current filling color space on success, otherwise it returns \ref BRST_CS_EOF.

*/
BRST_EXPORT(BRST_ColorSpace)
BRST_Page_FillingColorSpace_Value(
    BRST_Page page
);

/**

  \ingroup page
  \brief Get page current line width.

  \copydoc dox_param_page

  \return Page current line width for path painting on success, otherwise it returns \ref BRST_DEF_LINEWIDTH.

*/
BRST_EXPORT(BRST_REAL)
BRST_Page_LineWidth_Value(
    BRST_Page page
);

/**

  \ingroup page
  \brief Get page current line cap.

  \copydoc dox_param_page

  \return Page current line cap for path painting on success, otherwise it returns \ref BRST_DEF_LINECAP.

*/
BRST_EXPORT(BRST_LineCap)
BRST_Page_LineCap_Value(
    BRST_Page page
);

/**

  \ingroup page
  \brief Get page current line join.

  \copydoc dox_param_page

  \return Page current line join for path painting on success, otherwise it returns \ref BRST_DEF_LINEJOIN.

*/
BRST_EXPORT(BRST_LineJoin)
BRST_Page_LineJoin_Value(
    BRST_Page page
);

/**

  \ingroup page
  \brief Get page current miter limit.

  \copydoc dox_param_page

  \return Page current line miter limit for path painting on success, otherwise it returns \ref BRST_DEF_MITERLIMIT.

*/
BRST_EXPORT(BRST_REAL)
BRST_Page_MiterLimit_Value(
    BRST_Page page
);

/**

  \ingroup page
  \brief Get page current line dash pattern.

  \copydoc dox_param_page

  \return Page current line dash pattern \ref BRST_DashMode for path painting on success,
  otherwise it returns `BRST_DashMode{{0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f}, 0.0f, 0.0f}`.

*/
BRST_EXPORT(BRST_DashMode)
BRST_Page_Dash_Value(
    BRST_Page page
);

/**

  \ingroup page
  \brief Get page current flatness value.

  \copydoc dox_param_page

  \return Page current flatness value on success, otherwise it returns \ref BRST_DEF_FLATNESS.

*/
BRST_EXPORT(BRST_REAL)
BRST_Page_Flat_Value(
    BRST_Page page
);

/**

  \ingroup page
  \brief Get page current transformation matrix.

  \copydoc dox_param_page

  \return Page current transformation matrix \ref BRST_TransMatrix on success, otherwise it returns default transformation matrix `BRST_TransMatrix{1, 0, 0, 1, 0, 0}`.

  \see BRST_Page_Concat()

*/
BRST_EXPORT(BRST_TransMatrix)
BRST_Page_TransMatrix(
    BRST_Page page
);

/* sh */
BRST_EXPORT(BRST_STATUS)
BRST_Page_SetShading(
    BRST_Page    page,
    BRST_Shading shading
);

#endif /* BRST_GEOMETRY_H */