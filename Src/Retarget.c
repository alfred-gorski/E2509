#pragma import(__use_no_semihosting_swi)
#pragma import(__use_no_semihosting)

struct __FILE { int handle; };

#include <stdio.h>
#include <stdlib.h>
#include <rt_sys.h>

#include <Debug.h>
#include <Reset.h>

__weak int getkey(void)
{
  return EOF;
}

__weak int sendchar(int const c)
{
	DEBUG_PUTC(c);
	
  return c;
}

FILE __stdout;
FILE __stdin;

int fputc(int const c, FILE * const f) 
{
  return sendchar(c);
}

int fgetc(FILE * const f) 
{
  return getkey();
}

int ferror(FILE * const f) 
{
  return EOF;
}

void _ttywrch(int const c) 
{
  sendchar(c);
}

int __aeabi_idiv0(void) 
{ 
  DEBUG_BREAK(4); 
  
  return 0;
}

void abort(void)
{
  ResetController();
}

void exit(int x)
{
  ResetController();
}

void _sys_exit(int x) 
{
  ResetController();
}

void __rt_exit(int x)
{
  ResetController();
}  
