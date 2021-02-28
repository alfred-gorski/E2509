//                                                      
// Example.c
//

#include <Compiler.h>
#include <Debug.h>

#include <STM32F10xxx.h>
#include <Reset.h>

#include <DrvUSART.h>

#include <RB_SPI.h>
#include <HW_RCC.h>

#include <U_DrvSPI.h>
#include <U_DrvTimer.h>
#include <U_LEDMatrix.h>
#include <U_Queue.h>

#define COUNT_MASK (1<<3)-1

unsigned volatile tickCounter = 0U;
bool volatile runApplication = true; 

WORD volatile code;
int count;
int countmask;


SPIHandle hSPIGn;
SPIHandle hSPIRd;

extern TimerHandle Timer2;
extern TimerHandle Timer3;







typedef enum 
{
  testIdle, 
  testBusy
} TestStateType;

typedef struct
{
  TestStateType state;
  BYTE data;
  UsartHandleType handle;
} TestContextType;  

static TestContextType context = { testIdle, 0 };

static void SetCONTROL(WORD const controlVal)
{
  register WORD controlReg __asm("control");

  DEBUG_PRINT("CONTROL=%x", controlVal);
	
	controlReg = controlVal;
}

static void SetPRIMASK(WORD const primaskVal)
{
  register WORD primaskReg __asm("primask");
	
  DEBUG_PRINT("PRIMASK=%x", primaskVal);

	primaskReg = primaskVal;
}

/// Initialisierung des Hauptprogramms.
static void MainInit(void)
{
	/// Hauptinitialisierung des Controllers (inkl. Peripherie) erfolgt durch Aufruf von STM32F10xxx_Config()
	STM32F10xxx_Config();
	
	
	PeripheryEnable(RCC_GPIOA);
	PeripheryEnable(RCC_GPIOB);
	PeripheryEnable(RCC_GPIOC);
	

	//Init
	
	//GPIO for all AnTx
	AnTInit();
	
	//GPIO and RCC for SPI
	hSPIGn = SPIInit(Gn);
	hSPIRd = SPIInit(Rd);
	
	
	
	//TIM_Init
	/*
	InitTIM2();
	InitTIM3();
		
	
	StartTIM2();
	StartTIM3();
	
	ENABLETIM2();
	ENABLETIM3();
	
	*/
	
	timerInit(&Timer2);
	timerInit(&Timer3);
	timerEn(&Timer2);
	timerEn(&Timer3);
	timerStart(&Timer2);
	timerStart(&Timer3);
	
	
	
  /// Das PRIMASK-Register ist im Start-up-Code auf 1 eingestellt worden. Damit kann kein IRQ aktiv werden. 
  /// Erst mit dem Auruf der nachfolgenden Funktion können alle IRQs aktiv werden.
	SetPRIMASK(0U);

	
	 /// Indem Bit #0 im CONTROL-Register des Cortex-M3 gesetzt wird, wird der Prozessor in den non-priviliegierten Modus gesetzt.
  /// Damit können diverse, wichtige Einstellungen nicht mehr versehentlich überschrieben werden.
  /// Aber Achtung: Der Exception-Modus ist immer privilegiert, unabhängig von CONTROL[0].
	SetCONTROL(1U);
	
	
}

/// Deinitialisierung des Hauptprogramms (mit Reset).
__declspec(noreturn) 
static void MainExit(void)
{
  DEBUG_PUTS(__FUNCTION__);
	DEBUG_PUTS("It all stops here ...");

	ResetController();
}

static void TestFsm(TestContextType * context)
{
  switch(context->state)
  {
    case testIdle:
    if ( UsartRecv(context->handle, &context->data) == usartSuccess ) 
      context->state = testBusy;
    break;
    
    case testBusy:
    if ( UsartSend(context->handle, context->data) == usartSuccess ) 
      context->state = testIdle;
    break;
  }
}

/// Routine, die im Hauprprogramm zyklisch aufgerufen wird.




static void MainLoop(void){
	
	while(code == 1){
		SPIOutEnOff(&hSPIGn);
		SPIOutEnOff(&hSPIRd);
		code =0;
		count++;
		countmask=count&COUNT_MASK;
		SPIEmit(&hSPIGn,0x12345678);
		SPIEmit(&hSPIRd,0xABCDEF12);
		SPILatch(&hSPIGn);
		SPILatch(&hSPIRd);
		SPIOutEn(&hSPIGn);
		SPIOutEn(&hSPIRd);
		AnTOffAt(countmask-1 );
		AnTOnAt(countmask);

	
	}
		
	
	
  __wfi();
}

__declspec(noreturn) 
int main(){

	
  
	MainInit();

	while ( runApplication )
		MainLoop();
	
	MainExit();
}

void IRQ_SysTick(void)
{
  tickCounter++; 
}

void IRQ_HrdFault(void) {	for ( ;; ) DEBUG_BREAK(1); }
void IRQ_UsgFault(void) {	for ( ;; ) DEBUG_BREAK(1); }
void IRQ_BusFault(void) {	for ( ;; ) DEBUG_BREAK(1); }
void IRQ_MemFault(void) {	for ( ;; ) DEBUG_BREAK(1); }
void IRQ_NMI(void)      {	for ( ;; ) DEBUG_BREAK(1); }

