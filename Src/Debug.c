//
// Debug.c
//

#include <Compiler.h>
#include <Debug.h>

typedef struct __reg_bank_DBG
{
  WORD DHCSR;
  WORD DCRSR;
  WORD DCRDR;
  WORD DEMCR;
} RegisterBankDBG;

// DEMCR definitions

# define INDX_DBG_DEMCR_TRCENA  24
# define MASK_DBG_DEMCR_TRCENA  (1U << INDX_DBG_DEMCR_TRCENA)

typedef struct __reg_bank_ITM
{
  /// Stimulus ports.
  union
  {
    BYTE asByte;
    HWRD asHwrd;
    WORD asWord;
  } PORT[32];

  WORD reserved0[864];
  
  // offset: 0xE00
  
  WORD TER;                     ///< Trace enable register.
  WORD reserved1[15];
  
  WORD TPR;											///< Trace priviledge register.
  WORD reserved2[15];

  WORD TCR;											///< Trace control register.
  WORD reserved3[29];                                  

  WORD IWR;
  WORD IRR;
  WORD IMCR;
  WORD reserved4[43];                                  
  WORD LAR;
  WORD LSR;
  WORD reserved5[6];                                   
  WORD PID4;
  WORD PID5;
  WORD PID6;
  WORD PID7;
  WORD PID0;
  WORD PID1;
  WORD PID2;
  WORD PID3;
  WORD CID0;
  WORD CID1;
  WORD CID2;
  WORD CID3;
} RegisterBankITM;

// TCR definitions

# define INDX_ITM_TCR_ITMENA    0
# define MASK_ITM_TCR_ITMENA    (1U << INDX_ITM_TCR_ITMENA)

// TER definitions

# define INDX_ITM_TER_ENAPORT00 0  
# define MASK_ITM_TER_ENAPORT00 (1U << INDX_ITM_TER_ENAPORT00)

static RegisterBankDBG volatile DBG __attribute__((at(0xE000EDF0U)));
static RegisterBankITM volatile ITM __attribute__((at(0xE0000000U)));
static bool traceEnabled = false;

__attribute__((constructor(101))) 
static void InitTraceFlag(void) 
{ 
  // Achtung: Auf DBG.DEMCR kann nur im priviligierten Modus zugegriffen werden.
  // Da erst in MainInit() in den User-Modus gewechselt wird, kann man in dieser Funktion (die aufgrund des Attributes noch VOR main()
  // aufgerufen wird) prüfen, ob der Trace-Port aktiviert ist. Ich gehe davon aus, dass zur Laufzeit der Trace-Port entweder enabled
  // oder disabled bleibt (sinnvoll, da nur der Debugger dieses Bit einmalig setzt).

  traceEnabled = (DBG.DEMCR & MASK_DBG_DEMCR_TRCENA ) != 0U
  &&             (ITM.TCR   & MASK_ITM_TCR_ITMENA   ) != 0U 
  &&             (ITM.TER   & MASK_ITM_TER_ENAPORT00) != 0U;
 }

static int SaveItmChan0(BYTE const anyChr)
{
  unsigned retryCntr = 100U;
  
  while ( ITM.PORT[0].asWord == 0 ) 
  {
    if ( --retryCntr == 0U )
      return -1;
  }

  ITM.PORT[0].asByte = anyChr;
  
  return anyChr;
}

static bool TestNewLine(void)
{
  return traceEnabled
  &&     SaveItmChan0('\r') >= 0
  &&     SaveItmChan0('\n') >= 0;
}  

#include <stdio.h>
#include <stdarg.h>

static void OutTextStr(char const * anyTxt)
{
  char theChr;
  
  while ( (theChr = *anyTxt++) != '\0' )
  {
    SaveItmChan0((BYTE)theChr);
  }
}

static void OutTextLst(char const fmtString[], va_list argList)
{
  char chrBuffer[128];
  int const numOfChars = vsnprintf(chrBuffer, ARRAY_DIM(chrBuffer) - 1U, fmtString, argList);

  if ( numOfChars >= 0 )
  {
    chrBuffer[numOfChars] = '\0';
    
    OutTextStr(chrBuffer);
  } else
    OutTextStr("???");
}

static void OutTextVar(char const fmtString[], ...)
{
  va_list argList;

  va_start(argList, fmtString);
  OutTextLst(fmtString, argList);
  va_end(argList);  
}

__declspec(noreturn) 
void AssertionFailed(char const argExpr[], char const argFile[], unsigned lineNum, char const argFunc[])
{
  if ( TestNewLine() )
  {
    OutTextStr(argFile);
    OutTextVar("(%04u), ", lineNum);
    OutTextStr(argFunc);
    OutTextStr(": ");
    OutTextStr(argExpr);
  }
  
  __breakpoint(3);

  for ( ;; ) { }
}  

__declspec(noreturn) 
void ProgramAbortion(char const argText[], char const argFile[], unsigned lineNum, char const argFunc[])
{
  AssertionFailed(argText, argFile, lineNum, argFunc);
}

void DebugPutC(char const anyChr)
{
  if ( traceEnabled )
  {
    SaveItmChan0((BYTE)anyChr);
  }
}

void DebugPutS(char const * const anyTxt)
{
  if ( TestNewLine() )
  {
    OutTextStr(anyTxt);
  }
}

void DebugPrint(char const fmtString[], ...)
{
  if ( TestNewLine() )
  {
    va_list argList;

    va_start(argList, fmtString);
    OutTextLst(fmtString, argList);
    va_end(argList);  
  }
}
