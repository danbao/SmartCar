#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include <MC9S12XS128.h>
#include <stdio.h>
#include <string.h>
#include "main.h"
#include <math.h>
#include "SCI.h"

void main(void) {
int i;
  EnableInterrupts;
  SetBusCLK_40M();    //   设置时钟初始化。40MHz.
  SCI_Init();
  LIGHT_Init();
   delayms(2);
   for(i=0;i<=6;i++) {
    if(i ==  6 ) 
    {i = 0;
   
   count++;
    if(count%20==0){  
            count=1; 
  SendSmartcarInfo(light_temp_laser_array);
    SCISend('\n');    
    }      
     receive(i);
    } else receive(i);
  }
 /* loop forever */
  /* please make sure that you never leave main */
}