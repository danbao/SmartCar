#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include <MC9S12XS128.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>      //随机数用到
#include "main.h"
#include <math.h>
#include "SCI.h"

void main(void) {
  //int i;
  EnableInterrupts;
  SetBusCLK_40M();    //   设置时钟初始化。40MHz.
  SCI_Init();
  LIGHT_Init();
  PWM_Init();
   delayms(2);
   for(;;) {
   Light_Up();
    count++;
    if(count%10==0){  
   count=1; 
   //SendSmartcarInfo(light_temp_laser_array);   
  }             
   
    }

}
