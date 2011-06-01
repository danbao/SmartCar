/*=====================激光摆头滤波======================*/
void Clear_baitou(void){
int clear_position;
clear_position=position*100;
JG_clear_position=(JG_clear_position*40+clear_position*100) /140 ;  
}
  
/*=====================激光摆头======================*/
//转向舵机：1482 1772 1204   摆头舵机：224+-90
//0.10712*x^2 + 4.5791*10^(-17)*x + 6.7084
//Diff_Position是增量pd的 加到pwm上的增量
void  baitou (void) {
   
     
    
  
    
    
    His_Position[1]=JG_clear_position;
    His_Position[2]=position;
    His_Position[2]=aabs(His_Position[2]); 
    
    
    if(His_Position[2]<=1)
    Diff_Position=0;
    else if(His_Position[2]>1&&His_Position[2]<=3)
    Diff_Position=His_Position[1]/50;//+4.3*(His_Position[1]-His_Position[0]);
    else if(His_Position[2]>3&&His_Position[2]<=7)
    Diff_Position=His_Position[1]/50;//+4.3*(His_Position[1]-His_Position[0]);
    else if(His_Position[2]>7&&His_Position[2]<=10)
    Diff_Position=His_Position[1]/50;//+4.3*(His_Position[1]-His_Position[0]);
    else if(His_Position[2]>10&&His_Position[2]<=12)
    Diff_Position=His_Position[1]/50;//+4.3*(His_Position[1]-His_Position[0]);
    else if(His_Position[2]>12&&His_Position[2]<=14)
    Diff_Position=His_Position[1]/50;//+4.3*(His_Position[1]-His_Position[0]);
    
  /*  else if(His_Position[3]>4&&His_Position[3]<=6)
    Diff_Position=(1+2)*His_Position[2]-(2+2*2)*His_Position[1]+2*His_Position[0];
    else if(His_Position[3]>6&&His_Position[3]<=8)
    Diff_Position=(1+2)*His_Position[2]-(2+2*2)*His_Position[1]+2*His_Position[0];
    else if(His_Position[3]>8&&His_Position[3]<=10)
    Diff_Position=(1+2)*His_Position[2]-(2+2*2)*His_Position[1]+2*His_Position[0];
    else if(His_Position[3]>10&&His_Position[3]<=12)
    Diff_Position=(1+2)*His_Position[2]-(2+2*2)*His_Position[1]+2*His_Position[0];
    else if(His_Position[3]>12&&His_Position[3]<=14)
    Diff_Position=(1+2)*His_Position[2]-(2+2*2)*His_Position[1]+2*His_Position[0];  */
    
     
     His_Position[0]=His_Position[1];
     PWMDTY67=PWMDTY67+Diff_Position;
    
}



/*================根据标准的position形成预判的趋势==========================

此时已经把position的值作为预判的值存储到temp_position_array[i]
作为一个预判的标准，显然也不是最准确的，每次就只从趋势里面找出一个点
来给下面打角舵机作为打角的参数。

BUG：
比较害怕PWMDTY67在这边没办法用，到时估计要把午餐的函数方法设一下参数， 进行参数传递

=========================================================================*/
void Form_tendency(void)
{
  int i,j;
  for(j=0;j<10;j++)
  {
    for(i=0;i<22;i++) 
    {
      if(PWMDTY67 == standard_position_array[i]) 
      {
        temp_position_array[j]=PWMDTY67;
      } 
      else if((PWMDTY67-standard_position_array[i])>0) 
      {
        if((PWMDTY67-standard_position_array[i])>(standard_position_array[i+1]-PWMDTY67))
          temp_position_array[j]=standard_position_array[i+1];
      } 
      else if((PWMDTY67-standard_position_array[i])<0)
      {
        if((standard_position_array[i]-PWMDTY67)>(PWMDTY67-standard_position_array[i-1]))
          temp_position_array[j]=standard_position_array[i-1];
      }
    }
  }
}

void Tendency_judge(void) {
  int i,j,temp;
  temp=temp_position_array[9];
  for(i=0;i<10;i++) {
    if(temp_position_array[i]==temp) {
    //直接把速度，上下舵机都写进来，到时能跑过后，我们在分开。
    
    
    
                                     }
    else   ;
  //    dajiao((temp_position_array[i]+temp)/2);//整幅图只找出一个点，然后进行摆角，替换替换几组后进行调整
                  
                   }
}

void Replace_array(void)
{
  int i;
//这个函数旨在替换趋势的历史数组，就像队列一样逐个替换
  for(i=9;i>0;i--)
  {             //保存历史状态
    temp_position_array[i] =  temp_position_array[i-1];   
  }
  temp_position_array[0] = PWMDTY67;
}












/*=======================打角舵机===========================*/
//GDiff_Position是存储 摇头舵机差值 传给打角的参数
//  1482   1772  1192
   
 
void dajiao(void) {
    
    int ZhuanPwm=0;
    GDiff_Position[1]=PWMDTY67-PWM67;
    GDiff_Position[2]=PWMDTY67-PWM67;
    GDiff_Position[2]=aabs(GDiff_Position[2]);
    His_Position[3]=position;
    His_Position[3]=aabs(His_Position[3]);
    J_His_Position[1]=position;
    J_His_Position[2]=J_His_Position[1]-J_His_Position[0];
   
    if(GDiff_Position[2]<=7&&His_Position[3]<=1)
    ZhuanPwm=PWM45;
    else{  
    if(GDiff_Position[2]<=14)
    ZhuanPwm=PWM45-(6*position+3.2*GDiff_Position[1])-2.9*(J_His_Position[2]+GDiff_Position[1]-GDiff_Position[0]);
    else if(GDiff_Position[2]>14&&GDiff_Position[2]<=24)
    ZhuanPwm=PWM45-(8*position+5.5*GDiff_Position[1])-2.9*(J_His_Position[2]+GDiff_Position[1]-GDiff_Position[0]);
    else if(GDiff_Position[2]>24&&GDiff_Position[2]<=40)
    ZhuanPwm=PWM45-(11*position+7.1*GDiff_Position[1])-2.9*(J_His_Position[2]+GDiff_Position[1]-GDiff_Position[0]);
    else if(GDiff_Position[2]>40&&GDiff_Position[2]<=60)
    ZhuanPwm=PWM45-(14*position+9.1*GDiff_Position[1])-2.9*(J_His_Position[2]+GDiff_Position[1]-GDiff_Position[0]);
    else if(GDiff_Position[2]>60&&GDiff_Position[2]<=80)
    ZhuanPwm=PWM45-(17*position+11.1*GDiff_Position[1])-2.9*(J_His_Position[2]+GDiff_Position[1]-GDiff_Position[0]);
    else if(GDiff_Position[2]>80)
    ZhuanPwm=PWM45-(19*position+13.1*GDiff_Position[1])-2.9*(J_His_Position[2]+GDiff_Position[1]-GDiff_Position[0]);
    }
    if(ZhuanPwm>1768)
    ZhuanPwm=1768;
    else if(ZhuanPwm<1188)
    ZhuanPwm=1188;
    
    PWMDTY45=ZhuanPwm;
    GDiff_Position[0]=GDiff_Position[1]; 
    J_His_Position[0]=J_His_Position[1];
  } // DerectionCtrl







//=====================电机速度调节======================//


void SpeedCtrl (void) {
int subspeed;
subspeed=g_temp_pulse-100;
PORTB_PB7=1;
PWMDTY01 = 25;      //占空比10%
PWMDTY23 = 80;      //占空比50%
 
/* if ((subspeed<=10)&&(subspeed>=-10));
else if((subspeed>10)&&(subspeed<=35)) 
PORTB_PB7=0;
else if(subspeed>35) 
    {  
PORTB_PB7=1;
PWMDTY01= 80;
    }
else if((subspeed<-10)&&(subspeed>=-35)) 
   {
PORTB_PB7=1;
PWMDTY23=PWMDTY23-2*subspeed;
PWMDTY01= 0; 
   }
else if(subspeed<-35)
   {
  
PORTB_PB7=1;
PWMDTY23=80;
PWMDTY01= 0;
   }         */
}          



















/*=====================激光摆头舵机改变函数======================
void Light_SetDriver(int value){
  PWMDTY67 = value; 
}
void SCI_SetDriver(int value){
  PWMDTY45 = value; 
}

*/


