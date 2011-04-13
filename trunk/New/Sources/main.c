#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include <MC9S12XS128.h>
#include "math.h"           //abs绝对值要用到
#include "main.h"           //所有变量的定义都放在main.h文件下了
#include "dealinfo.h"
#include "control.h" 

void main(void) {
  int i;

     
  int temp_laserStatus;           //定义一个数组用来接受 上下舵机值
  EnableInterrupts;
  SetBusCLK_40M();    //   设置时钟初始化。40MHz.
  PWM_Init();
  LIGHT_Init();
  delayms(2);
  Laser_num();
  for(i=0;;i++) {
    if(i == 5) 
    {i = 0;
   
    //  count++;
      //     if(count%20==0){  
      //        count=1; 
//  SendSmartcarInfo(light_temp_laser_array);
  //  SCISend('\n');    
  //          }         
     temp_laserStatus = Status_Judge();
     CalculateAngle(temp_laserStatus); //得到舵机需要调整的转角 
    dajiao();     
   testcount++;
  if(testcount%17==0){
       testcount=1;
   baitou( );
   }
    
     SpeedCtrl();
     receive(i);
    } else receive(i);
  }
// _FEED_COP(); /*看门狗，防死循环用的 */
 /* loop forever */
  /* please make sure that you never leave main */
}
