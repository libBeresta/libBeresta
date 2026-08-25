#ifndef BRST_EXTERNAL_H
#define BRST_EXTERNAL_H

#define BRST_STDCALL 
#define BRST_EXPORT(A) extern A
#define BRST_UNUSED(a) ((void)(a))
#define BRST_HANDLER(A) A

/*----------------------------------------------------------------------------*/
/*----- macros for debug -----------------------------------------------------*/

#ifdef LIBBRST_DEBUG_TRACE
#ifndef BRST_PTRACE_ON
#define BRST_PTRACE_ON
#endif /* BRST_PTRACE_ON */
#endif /* LIBBRST_DEBUG_TRACE */

#ifdef BRST_PTRACE_ON
#define BRST_PTRACE(...)  BRST_PRINTF(__VA_ARGS__)
#else
#define BRST_PTRACE(...)  /* do nothing */
#endif /* BRST_PTRACE */

#ifdef LIBBRST_DEBUG
#define BRST_PRINT_BINARY(BUF, LEN, CAPTION) BRST_PrintBinary(BUF, LEN, CAPTION)
#else
#define BRST_PRINT_BINARY(BUF, LEN, CAPTION) /* do nothing */
#endif

#endif /* BRST_EXTERNAL_H */
