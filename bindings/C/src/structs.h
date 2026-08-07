// license
#ifndef BRST_STRUCTS_H
#define BRST_STRUCTS_H

/**
  Положение точки на странице
*/
typedef struct _BRST_Point {
  /// 
  BRST_REAL x;
  /// 
  BRST_REAL y;
} BRST_Point;

/**
  
*/
typedef struct _BRST_Rect {
  /// 
  BRST_REAL left;
  /// 
  BRST_REAL bottom;
  /// 
  BRST_REAL right;
  /// 
  BRST_REAL top;
} BRST_Rect;

/**
  
*/
typedef struct _BRST_TextWidth {
  /// 
  BRST_UINT numchars;
  /// 
  BRST_UINT numwords;
  /// 
  BRST_UINT width;
  /// 
  BRST_UINT numspace;
} BRST_TextWidth;

#endif /* BRST_STRUCTS_H */
