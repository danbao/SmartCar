

/*=====================激光摆头滤波======================
long JG_clear[2];                      //激光一次迭代滤波 此次和上次
long JG_clear_Pos[2];                  //存入当前和上一次JG_clear 的值
*/
 
 
void Clear_baitou(void){
//long JG_sum[2];
JG_clear[1]=position*100;
JG_clear[1]=(JG_clear[0]*40+JG_clear[1]*100) /140 ; 
JG_clear[0]=JG_clear[1]; 

}

  
/*=====================激光摆头======================
//1881   2602 1160
LASER_MAX         11  10    9    8    7     6     5    4     3     2        1     0
对应的权值        11   9    7    5    3     1    -1   -3    -5    -7       -9   -11
分段连接要重合
*/
void  baitou (void) {
    
    int JG_pos_abs=JG_clear[1];
    int JG_pwm;
    int JG_pwm_his=PWMDTY67;
    
    JG_pos_abs=aabs(JG_pos_abs);
    JG_clear_Pos[1]=JG_clear[1];
    
    
    if(JG_pos_abs<=60)                             //分四段P 
    JG_pwm=0;
    else if(JG_pos_abs>60&&JG_pos_abs<=300) 
          {
      JG_pwm=JG_clear_Pos[1]/54;
          }
    else if(JG_pos_abs>300&&JG_pos_abs<=400) 
          {
      if(position>0)   
      JG_pwm=JG_clear_Pos[1]/30-4;
      else if(position<0)
      JG_pwm=JG_clear_Pos[1]/30+4;
      
          }
    else if(JG_pos_abs>400&&JG_pos_abs<=800) 
          {
      if(position>0)    
      JG_pwm=JG_clear_Pos[1]/18-13;
      else if(position<0)
      JG_pwm=JG_clear_Pos[1]/18+13;
          }
    else if(JG_pos_abs>800&&JG_pos_abs<=1100)
         {
      if(position>0)   
      JG_pwm=JG_clear_Pos[1]/12-35;
      else if(position<0)
      JG_pwm=JG_clear_Pos[1]/12+35;
      
         }
   
       
     JG_clear_Pos[0]=JG_clear_Pos[1];
     if(JG_pwm_his+JG_pwm>2602)
     PWMDTY67=2602;
     else if(JG_pwm_his+JG_pwm<1160)
     PWMDTY67=1160;
     else
     PWMDTY67=PWMDTY67+JG_pwm;
    
}



/*================根据标准的position形成预判的趋势==========================
  int road_point[6];                //5点归为一段  假设2.5m/s 5点为1.8cm
  int point_count;                  //5点计数
  int road_section[8];              //8段归为一长路  同假设8段为15cm
  int section_count;                //8段计数
此时已经把position的值作为预判的值存储到temp_position_array[i]
作为一个预判的标准，显然也不是最准确的，每次就只从趋势里面找出一个点
来给下面打角舵机作为打角的参数。

BUG：
比较害怕PWMDTY67在这边没办法用，到时估计要把午餐的函数方法设一下参数， 进行参数传递
 int change_JG_DJ_array[23]={-103,-90,-80,-73,-62,-52,-46,-36,-24,-18,-10,0,10,18,24,36,46,52,62,73,80,90,103}; 
 int standard_position_array[23]=
  //标准position的值
  int temp_position_array[22];
  //用于记录position的值，形成预判的趋势 
//int last_laser_array[20][11];    
//这个二维数组作为激光管的历史记录
=========================================================================*/




/*================综合偏差======================
思路是把每个激光的舵机值加上当前摇头舵机值 相对位置
实验后发现摇头舵机无法做到很快的回位 周期大概20ms内 
如果这样的话 我们就把每次摇头处理后的舵机到下次处理前 等分

*/
void General_Position(void)       
{
int num=position+11;    //数组序号偏移代入
int baitou_diff=PWMDTY67-PWM67;      //摆头执行后的差值 我们把他等分试试 

General_pos[1]=change_JG_DJ_array[num]+baitou_diff*baitou_delay/12;
}

/*================综合偏差滤波======================
滤波时两次扩大了十倍   为了在计算斜率时除以速度值后仍然保留有一定数  
和激光相似
*/
void Clear_General(void) {
General_pos[1]=(40*General_pos[0]+100*General_pos[1])/14;
General_pos[0]=General_pos[1];

//General_pos[3]=General_pos[1];
//General_pos[3]=(40*General_pos[2]+100*General_pos[3])/14;
//General_pos[2]=General_pos[3];
}

/*================收集N点作为坐标的一点======================
如果实时收集处理量过大 所以多点合为一整点 多整点合为一段 多段和为一路
road_point[5]为最后点值
*/
void Collect_Point(void) {
int i;
int code[5]={1,2,3,4,5},sum_code=15;   //加权递推平均法效果如何？ 
long point_sum=0;      //累加过程中最大值会超过32767 因为有正负

if(point_count==4) 
     {
     road_point[4]=General_pos[1];
     for(i=0;i<=4;i++) 
       {
     point_sum+=road_point[i]*code[i];
     point_sum=point_sum/sum_code;
        }
     road_point[5]=point_sum;   
     point_count=0;
     } 
else
    {
    road_point[point_count]=General_pos[1];
    point_count++;
    }
}

/*================N整点为一段 这个循环处理 推箱子======================
假设2.5  那么我们15cm一段计算第一点到第15cm点的斜率 用来给舵机跑 15cm是为了对舵机延迟的消除
 int road_section[8];              //8段归为一长路  同假设8段为15cm
 int section_count;
 从上往下15cm  0-7
*/
void Collect_Section(void){
int i;
if(point_count==0)
for(i=7;i>=0;i--) 
   {
   if(i==0)
   road_section[0]=road_point[5];
   else
   road_section[i]=road_section[i-1];
   }
}


/*================N段为一路 这个比较复杂 ======================

*/ 


/*================斜率计算======================
15cm的斜率计算 捕捉速度值放这里面
速度 假设200为2.5M/S  那么15cm 累加值大概为6*200  
*/
void Judge_Slope(void){


}


















/*

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


*/


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




/*=====================电机速度调节======================*/


void SpeedCtrl (void) {
int subspeed;
subspeed=speed_clera[1]-150;
//PORTB_PB7=1;
//PWMDTY01 = 25;      //占空比10%
//PWMDTY23 = 60;      //占空比50%
 
if ((subspeed<=10)&&(subspeed>=-10));
else if((subspeed>10)&&(subspeed<=35)) 
    {
PORTB_PB7=1;
PWMDTY01= 60;
PWMDTY23 = 30;
    }
else if(subspeed>35) 
    {  
PORTB_PB7=1;
PWMDTY01= 80;
PWMDTY23 = 50;
    }
else if((subspeed<-10)&&(subspeed>=-35)) 
   {
PORTB_PB7=1;
PWMDTY23=PWMDTY23-3*subspeed;
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


