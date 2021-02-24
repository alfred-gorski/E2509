//
// Debug.h
//

#ifndef __DEBUG_H__
# define  __DEBUG_H__

# define ARRAY_DIM(a)           (sizeof(a) / sizeof(a[0]))

# if defined(DEBUG) && ! defined(NO_DEBUG_OUT)

void DebugPutC(char anyChr);
void DebugPutS(char const * anyTxt);
void DebugPrint(char const fmtString[], ...);

__declspec(noreturn) 
void AssertionFailed(char const argExpr[], char const argFile[], unsigned lineNum, char const argFunc[]) __attribute__((__nonnull__));

__declspec(noreturn) 
void ProgramAbortion(char const argText[], char const argFile[], unsigned lineNum, char const argFunc[]) __attribute__((__nonnull__));

#  define DEBUG_PUTC(C)					DebugPutC(C)
#  define DEBUG_PUTS(S)					DebugPutS(S)
#  define DEBUG_PRINT(F, ...)   DebugPrint(F, __VA_ARGS__)

#  define DEBUG_BREAK(N)				__breakpoint(N)

#  define ASSERT(c)             do { static char const strText[] = #c; static char const strFile[] = __FILE__; if ( ! (c) ) AssertionFailed(strText, strFile, __LINE__, __FUNCTION__); } while ( false )
#  define CANCEL(t)             do { static char const strText[] = #t; static char const strFile[] = __FILE__;              ProgramAbortion(strText, strFile, __LINE__, __FUNCTION__); } while ( false )
# else
#  define DEBUG_PUTC(C)
#  define DEBUG_PUTS(S)
#  define DEBUG_PRINT(F, ...)

#  define DEBUG_BREAK(N)

#  define ASSERT(c)             
#  define CANCEL(c)             
# endif
#endif
