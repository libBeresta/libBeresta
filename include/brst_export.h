

#ifdef BRST_DLL_MAKE
#    define BRST_EXPORT(A)  __declspec(dllexport) A  __stdcall
#else
#    ifdef BRST_DLL_MAKE_CDECL
#        define BRST_EXPORT(A)  __declspec(dllexport) A
#    else
#        ifdef BRST_SHARED_MAKE
#            define BRST_EXPORT(A)  extern A
#        endif /* BRST_SHARED_MAKE */
#    endif /* BRST_DLL_MAKE_CDECL */
#endif /* BRST_DLL_MAKE */

#ifdef BRST_DLL
#    define BRST_SHARED
#    define BRST_EXPORT(A)  __declspec(dllimport) A  __stdcall
#    define BRST_HANDLER(A) A __stdcall
#else
#    ifdef BRST_DLL_CDECL
#        define BRST_SHARED
#        define BRST_EXPORT(A)  __declspec(dllimport) A
#    endif /* BRST_DLL_CDECL */
#    define BRST_HANDLER(A) A
#endif /* BRST_DLL */

#ifdef BRST_SHARED

#ifndef BRST_EXPORT
#define BRST_EXPORT(A) extern A
#endif /* BRST_EXPORT */

#else

#ifndef BRST_EXPORT
#define BRST_EXPORT(A)  A
#endif /* BRST_EXPORT  */

#include "brst_consts.h"
#include "brst_doc.h"
#include "brst_error.h"
#include "brst_pdfa.h"
#include "brst_page_sizes.h"

#endif /* BRST_SHARED */

/* cs --not implemented yet */
/* CS --not implemented yet */
/* sc --not implemented yet */
/* scn --not implemented yet */
/* SC --not implemented yet */
/* SCN --not implemented yet */

/* BI --not implemented yet */
/* ID --not implemented yet */
/* EI --not implemented yet */

/* BMC --not implemented yet */
/* BDC --not implemented yet */
/* EMC --not implemented yet */
/* MP --not implemented yet */
/* DP --not implemented yet */

/* BX --not implemented yet */
/* EX --not implemented yet */





