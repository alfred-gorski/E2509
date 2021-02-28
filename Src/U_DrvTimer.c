# include <U_DrvTimer.h>
# include <Compiler.h>
# include <HW_STK.h>



void delay_us(WORD nus){
	WORD temp;
	STK.LOAD = 9*nus;
	STK.VAL=0X00;
	STK.CTRL=0X01;
 do
 {
  temp=STK.CTRL;
 }while((temp&0x01)&&(!(temp&(1<<16))));
			STK.CTRL=0x00; 
			STK.VAL =0X00; 
}



