

/*=====================激光摆头滤波======================
long JG_clear[2];                      //激光一次迭代滤波 此次和上次
long JG_clear_Pos[2];                  //存入当前和上一次JG_clear 的值
*/
 
 
void Clear_baitou(void){
//int clear_position;
JG_clear[1]=position*100;
JG_clear[1]=(JG_clear[0]*40+JG_clear[1]*100) /140 ; 
JG_clear[0]=JG_clear[1]; 

}
  
/*=====================激光摆头======================
//1881   2591 1171
LASER_MAX         11  10    9    8    7     6     5    4     3     2        1     0
对应的权值        11   9    7    5    3     1    -1   -3    -5    -7       -9   -11

//转向舵机：1482 1772 1204   摆头舵机：224+-90
//0.10712*x^2 + 4.5791*10^(-17)*x + 6.7084
//Diff_Position是增量pd的 加到pwm上的增量*/
void  baitou (void) {
    int JG_pos_abs=JG_clear[1];
    int JG_pwm;
    int JG_pwm_his=PWMDTY67;
    
    JG_pos_abs=aabs(JG_pos_abs);
    JG_clear_Pos[1]=JG_clear[1];
    
    
    if(JG_pos_abs<=100)                             //分三段P 
    JG_pwm=0;
    else if(JG_pos_abs>100&&JG_pos_abs<=300) 
          {
      JG_pwm=JG_clear_Pos[1]/60;
          }
    else if(JG_pos_abs>300&&JG_pos_abs<=400) 
          {
      if(position>0)   
      JG_pwm=JG_clear_Pos[1]/30-5;
      else if(position<0)
      JG_pwm=JG_clear_Pos[1]/30+5;
      
          }
    else if(JG_pos_abs>400&&JG_pos_abs<=800) 
          {
      if(position>0)    
      JG_pwm=JG_clear_Pos[1]/15-18;
      else if(position<0)
      JG_pwm=JG_clear_Pos[1]/15+18;
          }
    else if(JG_pos_abs>800&&JG_pos_abs<=1100)
         {
      if(position>0)   
      JG_pwm=JG_clear_Pos[1]/10-44;
      else if(position<0)
      JG_pwm=JG_clear_Pos[1]/10+44;
      
         }
   
       
     JG_clear_Pos[0]=JG_clear_Pos[1];
     if(JG_pwm_his+JG_pwm>2591)
     PWMDTY67=2591;
     else if(JG_pwm_his+JG_pwm<1171)
     PWMDTY67=1171;
     else
     PWMDTY67=PWMDTY67+JG_pwm;
    
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
  for(j=0;j<10;j++) //数组temp_position_array元素为10个
  {
    for(i=0;i<22;i++) 
    {
    //在这个循环里面，数组standard_position_array是一个标准数组
    //根据根据与PWMDTY67的差值比较，把较为靠近的摆角舵机值存入数组temp_position_array
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

void Tendency_judge(void) 
{
//这是对一个趋势的判断，需要考虑两种情况，可能之后会多种，就是直线与非直线。
  int i,temp;
  temp=temp_position_array[9];
  for(i=0;i<10;i++) 
  {
    if(temp_position_array[i]==temp) 
    {
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





/*=======================打角舵机===========================
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


*/




//=====================电机速度调节======================//


void SpeedCtrl (void) {
int subspeed;
subspeed=g_temp_pulse-80;
//PORTB_PB7=1;
//PWMDTY01 = 25;      //占空比10%
//PWMDTY23 = 80;      //占空比50%
 
if ((subspeed<=10)&&(subspeed>=-10));
else if((subspeed>10)&&(subspeed<=35)) 
PORTB_PB7=0;
else if(subspeed>35) 
    {  
PORTB_PB7=1;
PWMDTY01= 80;
PWMDTY23 = 40;
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
   }         
}          



















/*=====================激光摆头舵机改变函数======================
void Light_SetDriver(int value){
  PWMDTY67 = value; 
}
void SCI_SetDriver(int value){
  PWMDTY45 = value; 
}

*/


