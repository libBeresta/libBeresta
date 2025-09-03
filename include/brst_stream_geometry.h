#ifndef BRST_STREAM_GEOMETRY_H
#define BRST_STREAM_GEOMETRY_H

#include "brst_external.h"
#include "brst_types.h"
#include "brst_stream.h"
#include "brst_geometry_defines.h"
#include "brst_shading.h"

BRST_EXPORT(BRST_STATUS)
BRST_Stream_GSave(
    BRST_Stream stream
);

BRST_EXPORT(BRST_STATUS)
BRST_Stream_GRestore(
    BRST_Stream stream
);

BRST_EXPORT(BRST_STATUS)
BRST_Stream_Concat(
    BRST_Stream stream,
    BRST_REAL   a,
    BRST_REAL   b,
    BRST_REAL   c,
    BRST_REAL   d,
    BRST_REAL   x,
    BRST_REAL   y
);

BRST_EXPORT(BRST_STATUS)
BRST_Stream_Translate(
    BRST_Stream stream,
    BRST_REAL   dx,
    BRST_REAL   dy
);

BRST_EXPORT(BRST_STATUS)
BRST_Stream_Scale(
    BRST_Stream stream,
    BRST_REAL   sx,
    BRST_REAL   sy
);

BRST_EXPORT(BRST_STATUS)
BRST_Stream_RotateDeg(
    BRST_Stream stream,
    BRST_REAL   degrees
);

BRST_EXPORT(BRST_STATUS)
BRST_Stream_Rotate(
    BRST_Stream stream,
    BRST_REAL   radians
);

BRST_EXPORT(BRST_STATUS)
BRST_Stream_Skew(
    BRST_Stream stream,
    BRST_REAL   a,
    BRST_REAL   b
);

/*
BRST_EXPORT(BRST_STATUS)
BRST_Stream_Circle(
    BRST_Stream stream,
    BRST_REAL   x,
    BRST_REAL   y,
    BRST_REAL   radius
);

BRST_EXPORT(BRST_STATUS)
BRST_Stream_Ellipse(
    BRST_Stream stream,
    BRST_REAL   x,
    BRST_REAL   y,
    BRST_REAL   x_radius,
    BRST_REAL   y_radius
);

BRST_EXPORT(BRST_STATUS)
BRST_Stream_Arc(
    BRST_Stream stream,
    BRST_REAL   x,
    BRST_REAL   y,
    BRST_REAL   radius,
    BRST_REAL   angle1,
    BRST_REAL   angle2
);
*/

BRST_EXPORT(BRST_STATUS)
BRST_Stream_SetGrayFill(
    BRST_Stream stream,
    BRST_REAL   value
);

BRST_EXPORT(BRST_STATUS)
BRST_Stream_SetGrayStroke(
    BRST_Stream stream,
    BRST_REAL   value
);

BRST_EXPORT(BRST_STATUS)
BRST_Stream_SetRGBFill(
    BRST_Stream stream,
    BRST_REAL r,
    BRST_REAL g,
    BRST_REAL b);

BRST_EXPORT(BRST_STATUS)
BRST_Stream_SetRGBFillUint(
    BRST_Stream stream,
    BRST_UINT8  r,
    BRST_UINT8  g,
    BRST_UINT8  b
);

BRST_EXPORT(BRST_STATUS)
BRST_Stream_SetRGBFillHex(
    BRST_Stream stream,
    BRST_UINT32  rgb
);

BRST_EXPORT(BRST_STATUS)
BRST_Stream_SetRGBStroke(
    BRST_Stream stream,
    BRST_REAL   r,
    BRST_REAL   g,
    BRST_REAL   b
);

BRST_EXPORT(BRST_STATUS)
BRST_Stream_SetRGBStrokeUint(
    BRST_Stream stream,
    BRST_UINT8  r,
    BRST_UINT8  g,
    BRST_UINT8  b
);

BRST_EXPORT(BRST_STATUS)
BRST_Stream_SetRGBStrokeHex(
    BRST_Stream stream,
    BRST_UINT32  rgb
);

BRST_EXPORT(BRST_STATUS)
BRST_Stream_SetCMYKFill(
    BRST_Stream stream,
    BRST_REAL   c,
    BRST_REAL   m,
    BRST_REAL   y,
    BRST_REAL   k
);

BRST_EXPORT(BRST_STATUS)
BRST_Stream_SetCMYKStroke(
    BRST_Stream stream,
    BRST_REAL   c,
    BRST_REAL   m,
    BRST_REAL   y,
    BRST_REAL   k
);

BRST_EXPORT(BRST_STATUS)
BRST_Stream_Clip(
    BRST_Stream stream
);

BRST_EXPORT(BRST_STATUS)
BRST_Stream_Eoclip(
    BRST_Stream stream
);

BRST_EXPORT(BRST_STATUS)
BRST_Stream_Stroke(
    BRST_Stream stream
);

BRST_EXPORT(BRST_STATUS)
BRST_Stream_ClosePathStroke(
    BRST_Stream stream
);

BRST_EXPORT(BRST_STATUS)
BRST_Stream_Fill(
    BRST_Stream stream
);

BRST_EXPORT(BRST_STATUS)
BRST_Stream_Eofill(
    BRST_Stream stream
);

BRST_EXPORT(BRST_STATUS)
BRST_Stream_FillStroke(
    BRST_Stream stream
);

BRST_EXPORT(BRST_STATUS)
BRST_Stream_EofillStroke(
    BRST_Stream stream
);

BRST_EXPORT(BRST_STATUS)
BRST_Stream_ClosePathFillStroke(
    BRST_Stream stream
);

BRST_EXPORT(BRST_STATUS)
BRST_Stream_ClosePathEofillStroke(
    BRST_Stream stream
);

BRST_EXPORT(BRST_STATUS)
BRST_Stream_EndPath(
    BRST_Stream stream
);

BRST_EXPORT(BRST_STATUS)
BRST_Stream_MoveTo(
    BRST_Stream stream,
    BRST_REAL   x,
    BRST_REAL   y
);

BRST_EXPORT(BRST_STATUS)
BRST_Stream_LineTo(
    BRST_Stream stream,
    BRST_REAL   x,
    BRST_REAL   y
);

BRST_EXPORT(BRST_STATUS)
BRST_Stream_CurveTo(
    BRST_Stream stream,
    BRST_REAL   x1,
    BRST_REAL   y1,
    BRST_REAL   x2,
    BRST_REAL   y2,
    BRST_REAL   x3,
    BRST_REAL   y3
);

BRST_EXPORT(BRST_STATUS)
BRST_Stream_CurveTo2(
    BRST_Stream stream,
    BRST_REAL   x2,
    BRST_REAL   y2,
    BRST_REAL   x3,
    BRST_REAL   y3
);

BRST_EXPORT(BRST_STATUS)
BRST_Stream_CurveTo3(
    BRST_Stream stream,
    BRST_REAL x1,
    BRST_REAL y1,
    BRST_REAL x3,
    BRST_REAL y3
);

BRST_EXPORT(BRST_STATUS)
BRST_Stream_ClosePath(
    BRST_Stream stream
);

BRST_EXPORT(BRST_STATUS)
BRST_Stream_Rectangle(
    BRST_Stream stream,
    BRST_REAL   x,
    BRST_REAL   y,
    BRST_REAL   width,
    BRST_REAL   height
);

BRST_EXPORT(BRST_STATUS)
BRST_Stream_SetLineWidth(
    BRST_Stream stream,
    BRST_REAL   line_width
);

BRST_EXPORT(BRST_STATUS)
BRST_Stream_SetLineCap(
    BRST_Stream  stream,
    BRST_LineCap line_cap
);

BRST_EXPORT(BRST_STATUS)
BRST_Stream_SetLineJoin(
    BRST_Stream   stream,
    BRST_LineJoin line_join
);

BRST_EXPORT(BRST_STATUS)
BRST_Stream_SetMiterLimit(
    BRST_Stream stream,
    BRST_REAL   miter_limit
);

BRST_EXPORT(BRST_STATUS)
BRST_Stream_SetDash(
    BRST_Stream      stream,
    const BRST_REAL* dash_pattern,
    BRST_UINT        num_elem,
    BRST_REAL        phase
);

BRST_EXPORT(BRST_STATUS)
BRST_Stream_SetFlat(
    BRST_Stream stream,
    BRST_REAL flatness
);

#endif /* BRST_STREAM_GEOMETRY_H */