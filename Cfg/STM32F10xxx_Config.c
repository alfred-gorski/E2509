//        
// STM32F10xxx_Config.C
//

#include <STM32F10xxx.h>
#include <RegBit.h>

// <<< Use Configuration Wizard in Context Menu >>>

// <h> General settings
//   <o0> HSE: External High Speed Clock [Hz] <4000000-25000000:100000>
//   <i> clock value for the used External High Speed Clock (4 MHz to 16 or 25 MHz (CL)).
//   <i> Default: 8000000 or 25000000 (8 MHz or 25 MHz)
//   <q3> Enable fault exception and traps
// </h>
#define __HSE                   8000000
#define __HSI                   8000000
#define __LSI                   32000U
#define __SCB_SETUP             1  

#if __SCB_SETUP
# include <HW_NVIC.h>

static void Setup_SCB(void)
{
  SCB.SHCSR |= MASK_SCB_SHCSR_USGFAULTENA | MASK_SCB_SHCSR_BUSFAULTENA | MASK_SCB_SHCSR_MEMFAULTENA;
  SCB.CCR   |= MASK_SCB_CCR_DIV_0_TRP | MASK_SCB_CCR_UNALIGN_TRP | MASK_SCB_CCR_STKALIGN;
}

#else
# define Setup_SCB()
#endif

// <e0> Reset and Clock Control [RCC]
//   <h> Control Register [CR]
//     <e1.24> PLLON: PLL1 enable         
//       <i> Default: PLL1 Disabled
//       <o2.18..21> PLLMUL: PLL1 Multiplication Factor
//         <i> Default: PLLSRC * 2
//         <0=> PLLSRC * 2
//         <1=> PLLSRC * 3
//         <2=> PLLSRC * 4
//         <3=> PLLSRC * 5
//         <4=> PLLSRC * 6
//         <5=> PLLSRC * 7
//         <6=> PLLSRC * 8
//         <7=> PLLSRC * 9
//         <8=> PLLSRC * 10
//         <9=> PLLSRC * 11
//         <10=> PLLSRC * 12
//         <11=> PLLSRC * 13
//         <12=> PLLSRC * 14
//         <13=> PLLSRC * 15
//         <14=> PLLSRC * 16
//       <o2.17> PLLXTPRE: HSE divider for PLL1 input clock
//         <i> Default: HSE
//         <0=> PLL1 input clock = HSE    
//         <1=> PLL1 input clock = HSE / 2
//       <o2.16> PLLSRC: PLL1 input clock         
//         <i> Default: HSI / 2
//         <0=> HSI / 2
//         <1=> HSE 
//     </e>
//     <o1.19> CSSON: Clock Security System enable
//       <i> Default: Clock detector OFF
//     <o1.18> HSEBYP: External High Speed clock Bypass
//       <i> Default: HSE oscillator not bypassed
//     <o1.3..7> HSITRIM: Internal High Speed clock trimming  <0-31>
//       <i> Default: 0
//     <o1.0> HSION: Internal High Speed clock enable
//       <i> Default: internal 8MHz RC oscillator OFF
//   </h>
//   <h> Configuration Register (CFGR)
//     <o2.24..27> MCO: Microcontroller Clock Output   
//       <i> Default: MCO = noClock
//       <0=> MCO = noClock
//       <4=> MCO = SYSCLK
//       <5=> MCO = HSI
//       <6=> MCO = HSE
//       <7=> MCO = PLL1CLK / 2
//     <o2.22> USBPRE: USB prescaler
//       <i> Default: USBCLK = PLLCLK / 1.5
//       <0=> USBCLK = PLLCLK / 1.5
//       <1=> USBCLK = PLLCLK
//     <o2.14..15> ADCPRE: ADC prescaler
//       <i> Default: ADCCLK=PCLK2 / 2
//       <0=> ADCCLK = PCLK2 / 2
//       <1=> ADCCLK = PCLK2 / 4
//       <2=> ADCCLK = PCLK2 / 6
//       <3=> ADCCLK = PCLK2 / 8
//     <o2.11..13> PPRE2: APB High speed prescaler (APB2)
//       <i> Default: PCLK2 = HCLK
//       <0=> PCLK2 = HCLK
//       <4=> PCLK2 = HCLK / 2 
//       <5=> PCLK2 = HCLK / 4 
//       <6=> PCLK2 = HCLK / 8 
//       <7=> PCLK2 = HCLK / 16 
//     <o2.8..10> PPRE1: APB Low speed prescaler (APB1) 
//       <i> Default: PCLK1 = HCLK
//       <0=> PCLK1 = HCLK
//       <4=> PCLK1 = HCLK / 2 
//       <5=> PCLK1 = HCLK / 4 
//       <6=> PCLK1 = HCLK / 8 
//       <7=> PCLK1 = HCLK / 16 
//     <o2.4..7> HPRE: AHB prescaler 
//       <i> Default: HCLK = SYSCLK
//       <0=> HCLK = SYSCLK
//       <8=> HCLK = SYSCLK / 2
//       <9=> HCLK = SYSCLK / 4
//       <10=> HCLK = SYSCLK / 8
//       <11=> HCLK = SYSCLK / 16
//       <12=> HCLK = SYSCLK / 64
//       <13=> HCLK = SYSCLK / 128
//       <14=> HCLK = SYSCLK / 256
//       <15=> HCLK = SYSCLK / 512
//     <o2.0..1> SW: System Clock Switch
//       <i> Default: SYSCLK = HSE
//       <0=> SYSCLK = HSI
//       <1=> SYSCLK = HSE
//       <2=> SYSCLK = PLLCLK
//   </h>
// </e> End of Clock Configuration
#define __CLOCK_SETUP           1
#define __RCC_CR_VAL_PLAIN      0x01010083
#define __RCC_CFGR_VAL          0x001DC402
#define __RCC_CFGR2_VAL         0x00010644

#if __CLOCK_SETUP
# define __RCC_CR_VAL           (__RCC_CR_VAL_PLAIN | MASK_RCC_CR_HSERDY) // HSE clock is ALWAYS on

# include <HW_RCC.h>

static void Setup_RCC_CFGR(void)
{
  RCC.CFGR = __RCC_CFGR_VAL;
  RCC.CR = __RCC_CR_VAL & ~(MASK_RCC_CR_PLL1ON | MASK_RCC_CR_PLL2ON | MASK_RCC_CR_PLL3ON); // set clock control register but don't start PLL yet
}

# if ( (__RCC_CR_VAL & MASK_RCC_CR_PLL1ON) == MASK_RCC_CR_PLL1ON )

static bool Setup_RCC_PLL1(void)
{
  unsigned maxWait = 1000000U;
  
  SET_BIT(RCC, CR, PLL1ON);                           // start PLL now (after HSI and/or HSE ready)

  while ( ! GET_BIT(RCC, CR, PLL1RDY) ) 
  { 
    if ( --maxWait == 0U ) 
      return false;
  }
  
  return true;
}

# else
#  define Setup_RCC_PLL1()
# endif

#  if ( (__RCC_CR_VAL & MASK_RCC_CR_HSION) == MASK_RCC_CR_HSION )

static void Setup_RCC_HSI_Pre(void)
{
  while ( ! GET_BIT(RCC, CR, HSIRDY) ) { }
}

# else
#  define Setup_RCC_HSI_Pre()0
# endif

# if ( (__RCC_CFGR & MASK_RCC_CFGR_SW) == MASK_RCC_CFGR_SW_HSI && ! defined(Setup_RCC_HSI_Pre) )
#  define Setup_RCC_HSI_Post()
# else

static void Setup_RCC_HSI_Post(void)
{
  RES_BIT(RCC, CR, HSION);

  while (   GET_BIT(RCC, CR, HSIRDY) ) { }
}

# endif
 
static void Setup_RCC_HSE(void)
{
  while ( ! GET_BIT(RCC, CR, HSERDY) ) { }
}

static void Setup_RCC(void)
{
  WORD const expectedSws = (__RCC_CFGR_VAL << 2) & MASK_RCC_CFGR_SWS;

  Setup_RCC_CFGR();

  Setup_RCC_HSI_Pre();
  Setup_RCC_HSE();
 
  if ( Setup_RCC_PLL1() )
  {
    // Wait till SYSCLK is stabilized (depending on selected clock) 
    while ( (RCC.CFGR & MASK_RCC_CFGR_SWS) != expectedSws ) { }

    Setup_RCC_HSI_Post();
  }
}

#else
# define Setup_RCC()
#endif


// <e0> Nested Vectored Interrupt Controller [NVIC]
//   <e1.0> Vector Table Offset Register 
//     <o2.29> TBLBASE: Vector Table Base         
//       <i> Default: FLASH
//       <0=> FLASH
//       <1=> RAM
//     <o2.7..28> TBLOFF: Vector Table Offset <0x0-0x1FFFFFC0:0x80><#/0x80>
//       <i> Default: 0x00000000
//   </e>
//   <h> DMA interrupts [DMAx]
//     <o3>  DMA1 priority <0-15>         
//     <o4>  DMA2 priority <0-15>         
//     <o5>  DMA3 priority <0-15>         
//     <o6>  DMA4 priority <0-15>         
//     <o7>  DMA5 priority <0-15>         
//     <o8>  DMA6 priority <0-15>         
//     <o9>  DMA7 priority <0-15>         
//   </h> 
//   <h> SPI interrupts [SPIx]
//     <o10> SPI1 priority <0-15>         
//     <o11> SPI2 priority <0-15> 
//   </h> 
//   <h> USART interrupts [U(S)ARTx}
//     <o13> USART1 priority <0-15> 
//     <o14> USART2 priority <0-15> 
//     <o15> USART3 priority <0-15> 
//     <o30> UART4 priority <0-15> 
//     <o31> UART5 priority <0-15> 
//   </h> 
//   <h> Timer interrupts [TIMx]
//     <o16> TIM2 priority <0-15> 
//     <o17> TIM3 priority <0-15> 
//     <o18> TIM4 priority <0-15>
//   </h> 
//   <h> External interrupts [EXTIx]
//     <o19> EXTI00 priority <0-15>
//     <o20> EXTI01 priority <0-15>
//     <o21> EXTI02 priority <0-15>
//     <o22> EXTI03 priority <0-15>
//     <o23> EXTI04 priority <0-15>
//     <o24> EXITI16/PVD priority <0-15>
//   </h> 
//   <h> ADC interrupts [ADCx]
//     <o25> ADC1/2 priority <0-15>
//   </h> 
//   <o25> FLASH interrupt priority <0-15>
//   <o32> RTC interrupt priority <0-15>
//   <h> System handler priorities
//     <o27.28..31> SYSTICK priority <0-15>
//     <o28.28..31> SVC priority <0-15>
//     <o29.4..7> Memory fault priority <0-15>
//     <o29.12..15> Bus fault priority <0-15>
//     <o29.20..23> Usage fault priority <0-15>
//   </h>
// </e> End of Clock Configuration
#define __NVIC_SETUP            1                     //  0
#define __NVIC_USED             0x00000000
#define __NVIC_VTOR_VAL         0x00000000
#define __NVIC_PRIO_DMA1        8
#define __NVIC_PRIO_DMA2        8
#define __NVIC_PRIO_DMA3        8
#define __NVIC_PRIO_DMA4        8
#define __NVIC_PRIO_DMA5        8
#define __NVIC_PRIO_DMA6        8
#define __NVIC_PRIO_DMA7        8                     //  9
#define __NVIC_PRIO_SPI1        8                     // 10
#define __NVIC_PRIO_SPI2        8
#define __NVIC_PRIO_SPI3        8
#define __NVIC_PRIO_USART1      8
#define __NVIC_PRIO_USART2      8
#define __NVIC_PRIO_USART3      8
#define __NVIC_PRIO_TIM2        8
#define __NVIC_PRIO_TIM3        8
#define __NVIC_PRIO_TIM4        8
#define __NVIC_PRIO_EXTI00      8
#define __NVIC_PRIO_EXTI01      8                     // 20
#define __NVIC_PRIO_EXTI02      8
#define __NVIC_PRIO_EXTI03      8
#define __NVIC_PRIO_EXTI04      8
#define __NVIC_PRIO_EXTI16      8                     // 24
#define __NVIC_PRIO_ADC1_2      8                     // 25
#define __NVIC_PRIO_FLASH       8                     // 26
#define __NVIC_PRIO_SYSTICK     0x30000000            // 27
#define __NVIC_PRIO_SVC         0x20000000            // 28
#define __NVIC_PRIO_FAULT       0x00101010            // 29
#define __NVIC_PRIO_UART4       8                     // 30
#define __NVIC_PRIO_UART5       8                     // 31
#define __NVIC_PRIO_RTC         8                     // 32

#if __NVIC_SETUP
# include <HW_NVIC.h>

# if (__NVIC_USED & 1)

static void Setup_NVIC_VTOR(NO_ARGS)
{
  SCB.VTOR = __NVIC_VTOR_VAL & 0x3FFFFF80U;
}

# else
#  define Setup_NVIC_VTOR()
# endif                              

static void Setup_NVIC(void)
{
  Setup_NVIC_VTOR();

  SCB.SHPR[2] = __NVIC_PRIO_SYSTICK;                  // default SysTick IRQ priority
  SCB.SHPR[1] = __NVIC_PRIO_SVC;
  SCB.SHPR[0] = __NVIC_PRIO_FAULT;

  INTERRUPT_PRIO(DMA1_CHAN1, __NVIC_PRIO_DMA1   << 4);
  INTERRUPT_PRIO(DMA1_CHAN2, __NVIC_PRIO_DMA2   << 4);
  INTERRUPT_PRIO(DMA1_CHAN3, __NVIC_PRIO_DMA3   << 4);
  INTERRUPT_PRIO(DMA1_CHAN4, __NVIC_PRIO_DMA4   << 4);
  INTERRUPT_PRIO(DMA1_CHAN5, __NVIC_PRIO_DMA5   << 4);
  INTERRUPT_PRIO(DMA1_CHAN6, __NVIC_PRIO_DMA6   << 4);
  INTERRUPT_PRIO(DMA1_CHAN7, __NVIC_PRIO_DMA7   << 4);
  INTERRUPT_PRIO(SPI1      , __NVIC_PRIO_SPI1   << 4);
  INTERRUPT_PRIO(SPI2      , __NVIC_PRIO_SPI2   << 4);
  INTERRUPT_PRIO(SPI3      , __NVIC_PRIO_SPI3   << 4);
  INTERRUPT_PRIO(USART1    , __NVIC_PRIO_USART1 << 4);
  INTERRUPT_PRIO(USART2    , __NVIC_PRIO_USART2 << 4);
  INTERRUPT_PRIO(USART3    , __NVIC_PRIO_USART3 << 4);
  INTERRUPT_PRIO(UART4     , __NVIC_PRIO_UART4  << 4);
  INTERRUPT_PRIO(UART5     , __NVIC_PRIO_UART5  << 4);
  INTERRUPT_PRIO(TIM2      , __NVIC_PRIO_TIM2   << 4);
  INTERRUPT_PRIO(TIM3      , __NVIC_PRIO_TIM3   << 4);
  INTERRUPT_PRIO(TIM4      , __NVIC_PRIO_TIM4   << 4);
  INTERRUPT_PRIO(EXTI00    , __NVIC_PRIO_EXTI00 << 4);
  INTERRUPT_PRIO(EXTI01    , __NVIC_PRIO_EXTI01 << 4);
  INTERRUPT_PRIO(EXTI02    , __NVIC_PRIO_EXTI02 << 4);
  INTERRUPT_PRIO(EXTI03    , __NVIC_PRIO_EXTI03 << 4);
  INTERRUPT_PRIO(EXTI04    , __NVIC_PRIO_EXTI04 << 4);
  INTERRUPT_PRIO(PVD       , __NVIC_PRIO_EXTI16 << 4);
  INTERRUPT_PRIO(ADC1_2    , __NVIC_PRIO_ADC1_2 << 4);
  INTERRUPT_PRIO(FLASH     , __NVIC_PRIO_FLASH  << 4);
  INTERRUPT_PRIO(RTC       , __NVIC_PRIO_RTC    << 4);
} 

#else
# define Setup_NVIC()
#endif


// <e0> System Tick [STK]
//   <o1.2> System timer clock source selection
//     <i> Default: SYSTICKCLK = HCLK/8
//     <0=> SYSTICKCLK = HCLK/8
//     <1=> SYSTICKCLK = HCLK
//   <o2> SYSTICK period [ms] <1-100>
//     <i> Set the timer period for System Timer.
//     <i> Default: 1 (= 1 ms)
//   <o1.1> Enable interrupt
// </e>
#define __STK_SETUP             1
#define __STK_CTRL_VAL          0x00000006
#define __STK_PERIOD            1

#if __STK_SETUP == 1
# include <HW_STK.h>
# include <HW_NVIC.h>

# if ( (__STK_CTRL_VAL & MASK_STK_CTRL_CLKSOURCE) == 0 )
#  define STK_CLK()             (STM32F10xxx_GetHClk() / 8U)
# else
#  define STK_CLK()             STM32F10xxx_GetHClk()
# endif

static void Setup_SYSTICK(void) 
{
  unsigned const clockValue = STK_CLK();

  STK.LOAD = ((__STK_PERIOD * clockValue) / 1000U) - 1U;
  STK.VAL = 0U; 
  STK.CTRL = __STK_CTRL_VAL | MASK_STK_CTRL_ENABLE; // don't forget to enable the counter
}

#else
# define Setup_SYSTICK()
#endif


// <e0> Embedded Flash
//   <h> Flash Access Control (FLASH_ACR)
//     <o1.0..2> LATENCY: Latency
//       <i> Default: 2 wait states
//       <0=> 0 wait states
//       <1=> 1 wait states
//       <2=> 2 wait states
//     <o1.3> HLFCYA: Flash Half Cycle Access Enable
//     <o1.4> PRFTBE: Prefetch Buffer Enable
//     <o1.5> PRFTBS: Prefetch Buffer Status Enable
//   </h>
//   <q2> Enable Interrupt
// </e>
#define __EFI_SETUP               1
#define __EFI_ACR_VAL             0x00000012
#define __EFI_ENABLE_INTERRUPT    0

#if __EFI_SETUP == 1
# include <HW_FLASH.h>

# if __EFI_ENABLE_INTERRUPT == 1

static void Setup_EFI_Interrupt(NO_ARGS)
{
  INTERRUPT_ENABLE(FLASH);
}
 
# else
#  define Setup_EFI_Interrupt()
# endif

static void Setup_EFI(void) 
{
  FLASH.ACR = __EFI_ACR_VAL;                          // set access control register 
  Setup_EFI_Interrupt();
}

#else
# define Setup_EFI()
#endif

// <<< end of configuration section >>>

static unsigned Pll1Out(void)
{
  unsigned pllClock;

  if ( GET_BIT(RCC, CFGR, PLLSRC) )
  {
    pllClock = __HSE;
    
    if ( GET_BIT(RCC, CFGR, PLLXTPRE) ) pllClock >>= 1;
  } else
    pllClock = __HSI >> 1;

  switch(RCC.CFGR & MASK_RCC_CFGR_PLLMUL)
  {
    default:                      pllClock *=  0U; break;
    case MASK_RCC_CFGR_PLLMUL_16: pllClock *= 16U; break;
    case MASK_RCC_CFGR_PLLMUL_15: pllClock *= 15U; break;
    case MASK_RCC_CFGR_PLLMUL_14: pllClock *= 14U; break;
    case MASK_RCC_CFGR_PLLMUL_13: pllClock *= 13U; break;
    case MASK_RCC_CFGR_PLLMUL_12: pllClock *= 12U; break;
    case MASK_RCC_CFGR_PLLMUL_11: pllClock *= 11U; break;
    case MASK_RCC_CFGR_PLLMUL_10: pllClock *= 10U; break;
    case MASK_RCC_CFGR_PLLMUL_09: pllClock *=  9U; break;
    case MASK_RCC_CFGR_PLLMUL_08: pllClock *=  8U; break;
    case MASK_RCC_CFGR_PLLMUL_07: pllClock *=  7U; break;
    case MASK_RCC_CFGR_PLLMUL_06: pllClock *=  6U; break;
    case MASK_RCC_CFGR_PLLMUL_05: pllClock *=  5U; break;
    case MASK_RCC_CFGR_PLLMUL_04: pllClock *=  4U; break;
    case MASK_RCC_CFGR_PLLMUL_03: pllClock *=  3U; break;
    case MASK_RCC_CFGR_PLLMUL_02: pllClock *=  2U; break;
  } 

  return pllClock;
}

unsigned STM32F10xxx_GetAHB_Prescaler_Shift(void)
{
  switch(RCC.CFGR & MASK_RCC_CFGR_HPRE)
  {
    case MASK_RCC_CFGR_HPRE_512: return 9U; 
    case MASK_RCC_CFGR_HPRE_256: return 8U; 
    case MASK_RCC_CFGR_HPRE_128: return 7U; 
    case MASK_RCC_CFGR_HPRE_064: return 6U; 
    case MASK_RCC_CFGR_HPRE_016: return 4U; 
    case MASK_RCC_CFGR_HPRE_008: return 3U; 
    case MASK_RCC_CFGR_HPRE_004: return 2U; 
    case MASK_RCC_CFGR_HPRE_002: return 1U; 
  }
  
  return 0U;
}

unsigned STM32F10xxx_GetAPB1_Prescaler_Shift(void)
{
  switch(RCC.CFGR & MASK_RCC_CR_PPRE1)
  {
    case MASK_RCC_CR_PPRE1_16: return 4U;
    case MASK_RCC_CR_PPRE1_08: return 3U;
    case MASK_RCC_CR_PPRE1_04: return 2U;
    case MASK_RCC_CR_PPRE1_02: return 1U;
  }
  
  return 0U;
}

unsigned STM32F10xxx_GetAPB2_Prescaler_Shift(void)
{
  switch(RCC.CFGR & MASK_RCC_CR_PPRE2)
  {
    case MASK_RCC_CR_PPRE2_16: return 4U;
    case MASK_RCC_CR_PPRE2_08: return 3U;
    case MASK_RCC_CR_PPRE2_04: return 2U;
    case MASK_RCC_CR_PPRE2_02: return 1U;
  }
  
  return 0U;
}

unsigned STM32F10xxx_GetAPB1_Clock(void)
{
  return STM32F10xxx_GetHClk() >> STM32F10xxx_GetAPB1_Prescaler_Shift();
}

unsigned STM32F10xxx_GetAPB2_Clock(void)
{
  return STM32F10xxx_GetHClk() >> STM32F10xxx_GetAPB2_Prescaler_Shift();
}

unsigned STM32F10xxx_GetHClk(void)
{
  return STM32F10xxx_GetSysClk() >> STM32F10xxx_GetAHB_Prescaler_Shift();
}

unsigned STM32F10xxx_GetSysClk(void)
{
  switch(RCC.CFGR & MASK_RCC_CFGR_SW) // check system clock switch    
  {
    default: 
    case MASK_RCC_CFGR_SW_HSI: return __HSI;
    case MASK_RCC_CFGR_SW_HSE: return __HSE;
    case MASK_RCC_CFGR_SW_PLL: return Pll1Out(); 
  }
}

void OnStartUp(void)
{
  Setup_EFI();
  Setup_RCC();
}

#include <HW_RCC.h>

void STM32F10xxx_Config(void)
{
  Setup_SCB();
  Setup_SYSTICK();
  Setup_NVIC();
}

#include <Debug.h>
#include <Reset.h>

void HandleSVC(WORD * const argStack)
{
  WORD const regPC = argStack[6];
  BYTE const svcNum = ((BYTE const *)regPC)[-2];

  DEBUG_PRINT("SVC #0x%02X", (unsigned)svcNum);
  
  switch(svcNum)
  {
    default   : DEBUG_BREAK(4);
    case 0x00U: ResetController_privileged(); break;
  }
}

void __asm IRQ_SVC(void)
{
  IMPORT  HandleSVC

  TST     LR, #4
  MRSEQ   R0, MSP
  MRSNE   R0, PSP
  B       HandleSVC
}

void IRQ_PendSV(void) {	}
