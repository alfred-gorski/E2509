;
; STM32F10xxx_Startup.S (Startup File for the STM32F10xxx Series) 
;

; <<< Use Configuration Wizard in Context Menu >>>

; <h> Stack Configuration
;   <o> Stack Size (in Bytes) <0x0-0xFFFFFFFF:256>
; </h>
StckSize       	EQU     0x00000800
                AREA    STACK, NOINIT, READWRITE, ALIGN=8
StckMem        	SPACE   StckSize
InitialSP

; <h> Heap Configuration
;   <o>  Heap Size (in Bytes) <0x0-0xFFFFFFFF:1024>
; </h>
HeapSize       	EQU     0x00002000
                AREA    HEAP, NOINIT, READWRITE, ALIGN=8
HeapMem        	SPACE   HeapSize

                PRESERVE8
                THUMB

; Vector Table Mapped to Address 0 at Reset

                AREA    RESET, DATA, READONLY
				IMPORT	IRQ_NMI
				IMPORT	IRQ_HrdFault
 				IMPORT	IRQ_UsgFault
 				IMPORT	IRQ_BusFault
 				IMPORT	IRQ_MemFault
 				IMPORT	IRQ_SVC
                IMPORT	IRQ_PendSV
                IMPORT	IRQ_SysTick
                EXPORT  __Vectors
__Vectors       DCD     InitialSP                 ;     Top of Stack
                DCD     Reset_Handler
                DCD     IRQ_NMI
                DCD     IRQ_HrdFault
                DCD     IRQ_MemFault              ;     MPU Fault Handler
                DCD     IRQ_BusFault              ;     Bus Fault Handler
                DCD     IRQ_UsgFault              ;     Usage Fault Handler
                DCD     0                         ;     Reserved
                DCD     0                         ;     Reserved
                DCD     0                         ;     Reserved
                DCD     0                         ;     Reserved
                DCD     IRQ_SVC                   ;     SVCall Handler
                DCD     IRQ_DebugMon              ;     Debug Monitor Handler
                DCD     0                         ;     Reserved
                DCD     IRQ_PendSV                ;     PendSV Handler
                DCD     IRQ_SysTick               ;     SysTick Handler
                ; External Interrupts:
                DCD     IRQ_WWDG                  ;  0: Window Watchdog
                DCD     IRQ_PVD                   ;  1: PVD through EXTI Line detect
                DCD     IRQ_Tamper                ;  2: Tamper
                DCD     IRQ_RTC                   ;  3: RTC
                DCD     IRQ_FLASH                 ;  4: Flash
                DCD     IRQ_RCC                   ;  5: RCC
                DCD     IRQ_EXTI0                 ;  6: EXTI Line 0
                DCD     IRQ_EXTI1                 ;  7: EXTI Line 1
                DCD     IRQ_EXTI2                 ;  8: EXTI Line 2
                DCD     IRQ_EXTI3                 ;  9: EXTI Line 3
                DCD     IRQ_EXTI4                 ; 10: EXTI Line 4
                DCD     IRQ_DMA1_Chan1            ; 11: DMA1 Channel 1
                DCD     IRQ_DMA1_Chan2            ; 12: DMA1 Channel 2
                DCD     IRQ_DMA1_Chan3            ; 13: DMA1 Channel 3
                DCD     IRQ_DMA1_Chan4            ; 14: DMA1 Channel 4
                DCD     IRQ_DMA1_Chan5            ; 15: DMA1 Channel 5
                DCD     IRQ_DMA1_Chan6            ; 16: DMA1 Channel 6
                DCD     IRQ_DMA1_Chan7            ; 17: DMA1 Channel 7
                DCD     IRQ_ADC                   ; 18: ADC1 and ADC2
                DCD     IRQ_CAN1_TX               ; 19: CAN1 TX
                DCD     IRQ_CAN1_RX0              ; 20: CAN1 RX0
                DCD     IRQ_CAN1_RX1              ; 21: CAN1 RX1
                DCD     IRQ_CAN1_SCE              ; 22: CAN1 SCE
                DCD     IRQ_EXTI05to09            ; 23: EXTI Line 9..5
                DCD     IRQ_TIM1_BRK              ; 24: TIM1 Break
                DCD     IRQ_TIM1_UP               ; 25: TIM1 Update
                DCD     IRQ_TIM1_TRG_COM          ; 26: TIM1 Trigger and Commutation
                DCD     IRQ_TIM1_CC               ; 27: TIM1 Capture Compare
                DCD     IRQ_TIM2                  ; 28: TIM2
                DCD     IRQ_TIM3                  ; 29: TIM3
                DCD     IRQ_TIM4                  ; 30: TIM4
                DCD     IRQ_I2C1_EV               ; 31: I2C1 Event
                DCD     IRQ_I2C1_ER               ; 32: I2C1 Error
                DCD     IRQ_I2C2_EV               ; 33: I2C2 Event
                DCD     IRQ_I2C2_ER               ; 34: I2C2 Error
                DCD     IRQ_SPI1                  ; 35: SPI1
                DCD     IRQ_SPI2                  ; 36: SPI2
                DCD     IRQ_USART1                ; 37: USART1
                DCD     IRQ_USART2                ; 38: USART2
                DCD     IRQ_USART3                ; 39: USART3
                DCD     IRQ_EXTI10to15            ; 40: EXTI Line 15..10
                DCD     IRQ_RTCAlarm              ; 41: RTC Alarm through EXTI Line
                DCD     IRQ_OTG_FS                ; 42: USB OTG FS Wakeup
                DCD     IRQ_Default               ; 43: Reserved
                DCD     IRQ_Default               ; 44: Reserved
                DCD     IRQ_Default               ; 45: Reserved
                DCD     IRQ_Default               ; 46: Reserved
                DCD     IRQ_Default               ; 47: Reserved
                DCD     IRQ_Default               ; 48: Reserved
                DCD     IRQ_Default               ; 49: Reserved
                DCD     IRQ_TIM5                  ; 50: TIM5
                DCD     IRQ_SPI3                  ; 51: SPI3
                DCD     IRQ_UART4                 ; 52: UART4
                DCD     IRQ_UART5                 ; 53: UART5
                DCD     IRQ_TIM6                  ; 54: TIM6
                DCD     IRQ_TIM7                  ; 55: TIM7
                DCD     IRQ_DMA2_Chan1            ; 56: DMA2 Channel 1
                DCD     IRQ_DMA2_Chan2            ; 57: DMA2 Channel 2
                DCD     IRQ_DMA2_Chan3            ; 58: DMA2 Channel 3
                DCD     IRQ_DMA2_Chan4            ; 59: DMA2 Channel 4
                DCD     IRQ_DMA2_Chan5            ; 60: DMA2 Channel 5
                DCD     IRQ_ETH                   ; 61: Ethernet
                DCD     IRQ_ETHWakeup             ; 62: Ethernet Wakeup
                DCD     IRQ_CAN2_TX               ; 63: CAN2 TX
                DCD     IRQ_CAN2_RX0              ; 64: CAN2 RX0
                DCD     IRQ_CAN2_RX1              ; 65: CAN2 RX1
                DCD     IRQ_CAN2_SCE              ; 66: CAN2 SCE
                DCD     IRQ_OTG_FS                ; 67: USB On-The-Go FS

                AREA    |.text|, CODE, READONLY

OnStartUp       PROC
                EXPORT  OnStartUp                 [WEAK]
                BX      LR
                ENDP

Reset_Handler   PROC
                EXPORT  Reset_Handler
                IMPORT  __main
                MOV     R0, #1
                MSR     PRIMASK, R0
                BL      OnStartUp
                LDR     R0, =__main
                BX      R0
                ENDP

IRQ_DebugMon    PROC
                EXPORT  IRQ_DebugMon              [WEAK]
                B       .
                ENDP

IRQ_Default     PROC
IRQ_WWDG
IRQ_PVD
IRQ_Tamper
IRQ_RTC
IRQ_FLASH
IRQ_RCC
IRQ_EXTI0
IRQ_EXTI1
IRQ_EXTI2
IRQ_EXTI3
IRQ_EXTI4
IRQ_EXTI05to09
IRQ_EXTI10to15
IRQ_DMA1_Chan1
IRQ_DMA1_Chan2
IRQ_DMA1_Chan3
IRQ_DMA1_Chan4
IRQ_DMA1_Chan5
IRQ_DMA1_Chan6
IRQ_DMA1_Chan7
IRQ_ADC
IRQ_CAN1_TX
IRQ_CAN1_RX0
IRQ_CAN1_RX1
IRQ_CAN1_SCE
IRQ_TIM1_BRK
IRQ_TIM1_UP
IRQ_TIM1_TRG_COM
IRQ_TIM1_CC
IRQ_TIM2
IRQ_TIM3
IRQ_TIM4
IRQ_I2C1_EV
IRQ_I2C1_ER
IRQ_I2C2_EV
IRQ_I2C2_ER
IRQ_SPI1
IRQ_SPI2
IRQ_USART1
IRQ_USART2
IRQ_USART3
IRQ_RTCAlarm
IRQ_OTG_FS_WKUP
IRQ_TIM5
IRQ_SPI3
IRQ_UART4
IRQ_UART5
IRQ_TIM6
IRQ_TIM7
IRQ_DMA2_Chan1
IRQ_DMA2_Chan2
IRQ_DMA2_Chan3
IRQ_DMA2_Chan4
IRQ_DMA2_Chan5
IRQ_ETH
IRQ_ETHWakeup
IRQ_CAN2_TX
IRQ_CAN2_RX0
IRQ_CAN2_RX1
IRQ_CAN2_SCE
IRQ_OTG_FS
                B       .
                ENDP

                EXPORT  IRQ_WWDG                  [WEAK]
                EXPORT  IRQ_PVD                   [WEAK]
                EXPORT  IRQ_Tamper                [WEAK]
                EXPORT  IRQ_RTC                   [WEAK]
                EXPORT  IRQ_FLASH                 [WEAK]
                EXPORT  IRQ_RCC                   [WEAK]
                EXPORT  IRQ_EXTI0                 [WEAK]
                EXPORT  IRQ_EXTI1                 [WEAK]
                EXPORT  IRQ_EXTI2                 [WEAK]
                EXPORT  IRQ_EXTI3                 [WEAK]
                EXPORT  IRQ_EXTI4                 [WEAK]
                EXPORT  IRQ_DMA1_Chan1            [WEAK]
                EXPORT  IRQ_DMA1_Chan2            [WEAK]
                EXPORT  IRQ_DMA1_Chan3            [WEAK]
                EXPORT  IRQ_DMA1_Chan4            [WEAK]
                EXPORT  IRQ_DMA1_Chan5            [WEAK]
                EXPORT  IRQ_DMA1_Chan6            [WEAK]
                EXPORT  IRQ_DMA1_Chan7            [WEAK]
                EXPORT  IRQ_ADC                   [WEAK]
                EXPORT  IRQ_CAN1_TX               [WEAK]
                EXPORT  IRQ_CAN1_RX0              [WEAK]
                EXPORT  IRQ_CAN1_RX1              [WEAK]
                EXPORT  IRQ_CAN1_SCE              [WEAK]
                EXPORT  IRQ_EXTI05to09            [WEAK]
                EXPORT  IRQ_TIM1_BRK              [WEAK]
                EXPORT  IRQ_TIM1_UP               [WEAK]
                EXPORT  IRQ_TIM1_TRG_COM          [WEAK]
                EXPORT  IRQ_TIM1_CC               [WEAK]
                EXPORT  IRQ_TIM2                  [WEAK]
                EXPORT  IRQ_TIM3                  [WEAK]
                EXPORT  IRQ_TIM4                  [WEAK]
                EXPORT  IRQ_I2C1_EV               [WEAK]
                EXPORT  IRQ_I2C1_ER               [WEAK]
                EXPORT  IRQ_I2C2_EV               [WEAK]
                EXPORT  IRQ_I2C2_ER               [WEAK]
                EXPORT  IRQ_SPI1                  [WEAK]
                EXPORT  IRQ_SPI2                  [WEAK]
                EXPORT  IRQ_USART1                [WEAK]
                EXPORT  IRQ_USART2                [WEAK]
                EXPORT  IRQ_USART3                [WEAK]
                EXPORT  IRQ_EXTI10to15            [WEAK]
                EXPORT  IRQ_RTCAlarm              [WEAK]
                EXPORT  IRQ_OTG_FS_WKUP           [WEAK]
                EXPORT  IRQ_TIM5                  [WEAK]
                EXPORT  IRQ_SPI3                  [WEAK]
                EXPORT  IRQ_UART4                 [WEAK]
                EXPORT  IRQ_UART5                 [WEAK]
                EXPORT  IRQ_TIM6                  [WEAK]
                EXPORT  IRQ_TIM7                  [WEAK]
                EXPORT  IRQ_DMA2_Chan1            [WEAK]
                EXPORT  IRQ_DMA2_Chan2            [WEAK]
                EXPORT  IRQ_DMA2_Chan3            [WEAK]
                EXPORT  IRQ_DMA2_Chan4            [WEAK]
                EXPORT  IRQ_DMA2_Chan5            [WEAK]
                EXPORT  IRQ_ETH                   [WEAK]
                EXPORT  IRQ_ETHWakeup             [WEAK]
                EXPORT  IRQ_CAN2_TX               [WEAK]
                EXPORT  IRQ_CAN2_RX0              [WEAK]
                EXPORT  IRQ_CAN2_RX1              [WEAK]
                EXPORT  IRQ_CAN2_SCE              [WEAK]
                EXPORT  IRQ_OTG_FS                [WEAK]

                ALIGN

                IMPORT  __use_two_region_memory
                EXPORT  __user_initial_stackheap
__user_initial_stackheap
                LDR     R0, =HeapMem
                LDR     R1, =(StckMem + StckSize)
                LDR     R2, =(HeapMem +  HeapSize)
                LDR     R3, =StckMem
                BX      LR

                ALIGN

                END
