/** @mainpage E2509 Final Project
 *		<table>
 *  	<tr><th>Project  <td>E2509 Final Project
 *      <tr><th>Author   <td>Zhongzhu Deng github.com/alfred-gorski,
 * 		Hanxi Jiang github.com/AnnaJiang1308
 *		<tr><th>Source <td>github.com/alfred-gorski/E2509
 *  	</table>
 * 	@section Project Functional Describe
 * 	display 2 image on a 16X16 LED matrix, which has Red and Green channel,
 * 	the brightness is controlled by PWM.
 *
 *	@section User Configuration
 *	macro GLOBAL_BRIGHTNESS_PERCENT in file Inc/U_DrvTimer.h defines global
 *  brightness in percentage, the value is configurable in range from 1 to 100.
 */

/** @file Example.c
 * 	@brief main functions
 *  @details in MainInit init image handle and Timer, in MainLoop light the
 * screen.
 */

#include <Compiler.h>
#include <Debug.h>

#include <Reset.h>
#include <STM32F10xxx.h>

#include <HW_RCC.h>
#include <RB_SPI.h>


#include <U_DrvSPI.h>
#include <U_DrvTimer.h>
#include <U_LEDMatrix.h>
#include <U_Queue.h>

unsigned volatile tickCounter = 0U;
bool volatile runApplication = true;

ImageHandle hImage;

/** @variable TimerX
 *  @brief
 *  	<table>
 *  	<tr><th>Timer2 <td>trigger column switch
 *      <tr><th>Timer3 <td>trigger image switch
 *		<tr><th>Timer4 <td>global brightness PWM
 *  	</table>
 *  @ref Declared and Defined in U_DrvTimer.c
 */
extern TimerHandle Timer2;
extern TimerHandle Timer3;
extern TimerHandle Timer4;

static void SetCONTROL(WORD const controlVal) {
    register WORD controlReg __asm("control");

    DEBUG_PRINT("CONTROL=%x", controlVal);

    controlReg = controlVal;
}

static void SetPRIMASK(WORD const primaskVal) {
    register WORD primaskReg __asm("primask");

    DEBUG_PRINT("PRIMASK=%x", primaskVal);

    primaskReg = primaskVal;
}

/// Initialisierung des Hauptprogramms.
static void MainInit(void) {
    /// Hauptinitialisierung des Controllers (inkl. Peripherie) erfolgt durch
    /// Aufruf von STM32F10xxx_Config()
    STM32F10xxx_Config();

    PeripheryEnable(RCC_GPIOA);
    PeripheryEnable(RCC_GPIOB);
    PeripheryEnable(RCC_GPIOC);

    ImageInit(&hImage);

    timerInit(&Timer2);
    timerInit(&Timer3);
    timerInit(&Timer4);

    /// Das PRIMASK-Register ist im Start-up-Code auf 1 eingestellt worden.
    /// Damit kann kein IRQ aktiv werden. Erst mit dem Auruf der nachfolgenden
    /// Funktion können alle IRQs aktiv werden.
    SetPRIMASK(0U);

    /// Indem Bit #0 im CONTROL-Register des Cortex-M3 gesetzt wird, wird der
    /// Prozessor in den non-priviliegierten Modus gesetzt.
    /// Damit können diverse, wichtige Einstellungen nicht mehr versehentlich
    /// überschrieben werden. Aber Achtung: Der Exception-Modus ist immer
    /// privilegiert, unabhängig von CONTROL[0].
    SetCONTROL(1U);
}

/// Deinitialisierung des Hauptprogramms (mit Reset).
__declspec(noreturn) static void MainExit(void) {
    DEBUG_PUTS(__FUNCTION__);
    DEBUG_PUTS("It all stops here ...");

    ResetController();
}

/// Routine, die im Hauprprogramm zyklisch aufgerufen wird.
static void MainLoop(void) {

    ScreenOn(&hImage);

    __wfi();
}

__declspec(noreturn)

    int main() {

    MainInit();

    while (runApplication)
        MainLoop();

    MainExit();
}

void IRQ_SysTick(void) { tickCounter++; }

void IRQ_HrdFault(void) {
    for (;;)
        DEBUG_BREAK(1);
}
void IRQ_UsgFault(void) {
    for (;;)
        DEBUG_BREAK(1);
}
void IRQ_BusFault(void) {
    for (;;)
        DEBUG_BREAK(1);
}
void IRQ_MemFault(void) {
    for (;;)
        DEBUG_BREAK(1);
}
void IRQ_NMI(void) {
    for (;;)
        DEBUG_BREAK(1);
}
