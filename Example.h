//
// Example.h
//

#ifndef __EXAMPLE_H__
# define __EXAMPLE_H__          

# include <Compiler.h>

extern unsigned volatile tickCounter;                 // Dies ist die Declaration einer der wenigen Variablen mit externer Linkage. 
                                                      // Sie beinhaltet die Anzahl der Ticks (hier: 1 ms) seit Programmstart (Systemzeit)

extern bool volatile runApplication; 

void __forceinline TerminateApplication()
{
  runApplication = false;
}

#endif



















































































