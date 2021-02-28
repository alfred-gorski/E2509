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
#include <U_LEDMatrix.h>
#include <U_Queue.h>

unsigned volatile tickCounter = 0U;
bool volatile runApplication = true; 


SPIHandle hSPIGn;
SPIHandle hSPIRd;









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
	GPIO_An_Init();
	
	
	//GPIO and RCC for SPI1,SPI2

	// SPIInit(Gn);
	// SPIInit(Rd);
	
	hSPIGn = SPIInit(Gn);
	hSPIRd = SPIInit(Rd);
	
	
	
		
	SetPRIMASK(0U);
	
	
	SetCONTROL(1U);
	
	
	
	
  /*DEBUG_PUTS(__FUNCTION__);

  /// Hauptinitialisierung des Controllers (inkl. Peripherie) erfolgt durch Aufruf von STM32F10xxx_Config()

  STM32F10xxx_Config();

  if ( InitUsart(usartPort3, 9600U, &context.handle) == usartSuccess )
  {
  } else
    DEBUG_BREAK(1U);
  
  /// Das PRIMASK-Register ist im Start-up-Code auf 1 eingestellt worden. Damit kann kein IRQ aktiv werden. 
  /// Erst mit dem Auruf der nachfolgenden Funktion können alle IRQs aktiv werden.

  SetPRIMASK(0U);
  
  /// Indem Bit #0 im CONTROL-Register des Cortex-M3 gesetzt wird, wird der Prozessor in den non-priviliegierten Modus gesetzt.
  /// Damit können diverse, wichtige Einstellungen nicht mehr versehentlich überschrieben werden.
  /// Aber Achtung: Der Exception-Modus ist immer privilegiert, unabhängig von CONTROL[0].
  
  SetCONTROL(1U);
	*/
	
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




static void MainLoop(void)
{

	
	SPIEmit(&hSPIGn,0x12345678);
	SPIEmit(&hSPIRd,0xABCDEF12);
	
	
	GPIO_ResetPin(&GPIOA, 9);
	GPIO_ResetPin(&GPIOA, 10);
	
	SPILatch(&hSPIGn);
	SPIOutEn(&hSPIGn);
	
	SPILatch(&hSPIRd);
	SPIOutEn(&hSPIRd);
	
	
	
	
		
	
	
  __wfi();
}

__declspec(noreturn) 
int main()
{
 	DEBUG_PUTS("It all starts here ...");
 	DEBUG_PRINT("System clock = %u MHz", STM32F10xxx_GetSysClk() / 1000000U);
 	DEBUG_PRINT("APB1 clock = %u MHz", STM32F10xxx_GetAPB1_Clock() / 1000000U);
 	DEBUG_PRINT("APB2 clock = %u MHz", STM32F10xxx_GetAPB2_Clock() / 1000000U);
  
	MainInit();

 	DEBUG_PUTS("Starting main loop ...");

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

