

/*=====================激光摆头滤波======================
long JG_clear[2];                      //激光一次迭代滤波 此次和上次
long JG_clear_Pos[2];                  //存入当前和上一次JG_clear 的值
*/
 
 
void Clear_baitou(void){
//long JG_sum[2];
//JG_clear[3]=JG_clear[1];

if(YDdelay==0)
JG_clear[0]=JG_clear[1];

JG_clear[1]=position*10;

//JG_clear[1]=(JG_clear[0]*20+JG_clear[1]*70) /90 ;  


//JG_clear[3]=(JG_clear[2]*30+JG_clear[3]*40)/70;
//JG_clear[2]=JG_clear[3]; 
}

  
/*=====================激光管对应权值======================
LASER_MAX     20   19   18   17   16   15  14  13  12  11  10    9    8    7     6     5     4     3    2     1     0
对应的权值    20   18   16   14   12   10   8   6   4   2   0   -2   -4    -6    -8   -10  -12   -14   -16   -18   -20
分段连接要重合
int BP1=54,BP2=45,BP3=36,BP4=27,BP5=20;
*/
void  baitou (void) {
    
    int JG_pos_abs=JG_clear[1];
    int JG_pwm;
    int JG_pwm_his=PWMDTY45;
    int sub_p[10];
    
    
    int Diff_pos;
    byte BD_flag;
   

   
JG_pos_abs=aabs(JG_pos_abs);
JG_clear_Pos[1]=JG_clear[1];


YDdelay++;
if(YDdelay%10==0) //||JG_pos_abs>17
{
YDdelay=0;  
Diff_pos=JG_clear_Pos[1]-JG_clear[0];
/*if((JG_clear_Pos[1]>0)&&(Diff_pos>0))//&&(JG_clear[0]>0)
BD_flag=1;
else if((JG_clear_Pos[1]<0)&&(Diff_pos<0))// &&(JG_clear[0]<0)    
BD_flag=1;
else BD_flag=1; */
BD_flag=1;
} 

else BD_flag=0;


sub_p[0]=10/BP1;
sub_p[1]=20/BP2-(20/BP1-sub_p[0]);
sub_p[2]=40/BP3-(40/BP2-sub_p[1]);
sub_p[3]=60/BP4-(60/BP3-sub_p[2]);
sub_p[4]=80/BP5-(80/BP4-sub_p[3]);
sub_p[5]=100/BP6-(100/BP5-sub_p[4]);
sub_p[6]=120/BP7-(120/BP6-sub_p[5]);
sub_p[7]=140/BP8-(140/BP7-sub_p[6]);
sub_p[8]=160/BP9-(160/BP8-sub_p[7]);
sub_p[9]=180/BP10-(180/BP9-sub_p[8]);
    
    if(JG_pos_abs<=10)                             //分四段P 
    JG_pwm=0;
    else if(JG_pos_abs>10&&JG_pos_abs<=20) 
          {
      if(position>0)    
      JG_pwm=-(JG_clear_Pos[1]/BP1-sub_p[0]+BD_flag*Diff_pos/BD1);
      else if(position<0)
      JG_pwm=-(JG_clear_Pos[1]/BP1+sub_p[0]+BD_flag*Diff_pos/BD1); 
          }
   
    else if(JG_pos_abs>20&&JG_pos_abs<=40) 
          {
      if(position>0)   
      JG_pwm=-(JG_clear_Pos[1]/BP2-sub_p[1]+BD_flag*Diff_pos/BD2);
      else if(position<0)
      JG_pwm=-(JG_clear_Pos[1]/BP2+sub_p[1]+BD_flag*Diff_pos/BD2);
      
          }
    else if(JG_pos_abs>40&&JG_pos_abs<=60) 
          {
      if(position>0)   
      JG_pwm=-(JG_clear_Pos[1]/BP3-sub_p[2]+BD_flag*Diff_pos/BD3);
      else if(position<0)
      JG_pwm=-(JG_clear_Pos[1]/BP3+sub_p[2]+BD_flag*Diff_pos/BD3);
          }      
    else if(JG_pos_abs>60&&JG_pos_abs<=80)
          {
      if(position>0)    
      JG_pwm=-(JG_clear_Pos[1]/BP4-sub_p[3]+BD_flag*Diff_pos/BD4);
      else if(position<0)
      JG_pwm=-(JG_clear_Pos[1]/BP4+sub_p[3]+BD_flag*Diff_pos/BD4);
          }
    else if(JG_pos_abs>80&&JG_pos_abs<=100)
          {
      if(position>0)    
      JG_pwm=-(JG_clear_Pos[1]/BP5-sub_p[4]+BD_flag*Diff_pos/BD5);
      else if(position<0)
      JG_pwm=-(JG_clear_Pos[1]/BP5+sub_p[4]+BD_flag*Diff_pos/BD5);
          }
    
    else if(JG_pos_abs>100&&JG_pos_abs<=120)
          {
      if(position>0)    
      JG_pwm=-(JG_clear_Pos[1]/BP6-sub_p[5]+BD_flag*Diff_pos/BD6);
      else if(position<0)
      JG_pwm=-(JG_clear_Pos[1]/BP6+sub_p[5]+BD_flag*Diff_pos/BD6);
          }
    
    else if(JG_pos_abs>120&&JG_pos_abs<=140)
          {
      if(position>0)    
      JG_pwm=-(JG_clear_Pos[1]/BP7-sub_p[6]+BD_flag*Diff_pos/BD7);
      else if(position<0)
      JG_pwm=-(JG_clear_Pos[1]/BP7+sub_p[6]+BD_flag*Diff_pos/BD7);
          }                  
    else if(JG_pos_abs>140&&JG_pos_abs<=160) 
          {
      if(position>0)    
      JG_pwm=-(JG_clear_Pos[1]/BP8-sub_p[7]+BD_flag*Diff_pos/BD8);
      else if(position<0)
      JG_pwm=-(JG_clear_Pos[1]/BP8+sub_p[7]+BD_flag*Diff_pos/BD8);
          }      
    else if(JG_pos_abs>160&&JG_pos_abs<=180)
         {
      if(position>0)   
      JG_pwm=-(JG_clear_Pos[1]/BP9-sub_p[8]+BD_flag*Diff_pos/BD9);
      else if(position<0)
      JG_pwm=-(JG_clear_Pos[1]/BP9+sub_p[8]+BD_flag*Diff_pos/BD9);
      
         }   
         
    else if(JG_pos_abs>180)
         {
      if(position>0)   
      JG_pwm=-(JG_clear_Pos[1]/BP10-sub_p[9]+BD_flag*Diff_pos/BD10);
      else if(position<0)
      JG_pwm=-(JG_clear_Pos[1]/BP10+sub_p[9]+BD_flag*Diff_pos/BD10);
      
         }                             
   
       
     JG_clear_Pos[0]=JG_clear_Pos[1];
     if(JG_pwm_his+JG_pwm>2406)
     PWMDTY45=2406;
     else if(JG_pwm_his+JG_pwm<800)
     PWMDTY45=800;
     else
     PWMDTY45=PWMDTY45+JG_pwm;
    
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
比较害怕PWMDTY45在这边没办法用，到时估计要把午餐的函数方法设一下参数， 进行参数传递
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
int num=position+20;    //数组序号偏移代入
baitou_diff=PWMDTY45-PWM45;      //摆头执行后的差值 我们把他等分试试 

befo_General_pos=-(change_JG_DJ_array[num]+baitou_diff);//*baitou_delay/11;
}



/*================斜率偏差滤波======================
滤波时两次扩大了十倍   为了在计算斜率时除以速度值后仍然保留有一定数  
和激光相似
*/
void Clear_General(void) {

if(befo_General_pos>=0)
General_pos=befo_General_pos*0.5016+4.503;
else General_pos=befo_General_pos*0.5016-4.503;

//General_pos[1]=(10*General_pos[0]+130*General_pos[1])/140;
//cha_pos=General_pos[1]-General_pos[0];
//General_pos[0]=General_pos[1];

//General_pos[3]=General_pos[1];
//General_pos[3]=(40*General_pos[2]+100*General_pos[3])/14;
//General_pos[2]=General_pos[3];
}


/*================打角舵机======================
int DP1=15,DP2=13,DP3=11,DP4=10,DP5=8,DP6=7,DP7=6;
*/


void dajiao(void){
//int abs_pos;

//int sub_p[7];

int changebaitou;
int dj_pwm;
//int speedinfo;
//int abs_affect;

//int speedaffect;
//int code[2]={3,1},sum_code=4;


 changebaitou=baitoupwm/20;      //摆头占空比 除
 speedinfo=speed_clear[1]-130;    //基准的速度 如果小于它就不执行速度加入转角

 
 if(speedinfo>=5)
 {
 speedinfo=speedinfo/20;
 speedaffect1=speedinfo*speedinfo;
 speedaffect2=speedaffect1*changebaitou;
 speedaffect3=speedaffect2/160;
 
//speedaffect=speedinfo*speedinfo*changebaitou/48; 
 //speedaffect[1]=(10*speedaffect[0]+60*speedaffect[1])/70;
 //speedaffect[1]=speedaffect[1];
 }
 

 
 



if(turn_flag==0)
   {
   dj_pwm=General_pos;
   }


else
   {
   dj_pwm=General_pos+speedaffect3; 
   }

 
  

//abs_pos=position;
//abs_pos=aabs(abs_pos);



       

if(dj_pwm>272)
dj_pwm=272;
else if(dj_pwm<-272)
dj_pwm=-272;

dj_pwm=dj_pwm+PWM01;
PWMDTY01=dj_pwm;
}



/*=====================电机速度调节======================*/


void SpeedCtrl (byte a) {
int subspeed;
int changebaitou;
int okspeed;
if(a==1)
{
  PORTB_PB7=0;
  PWMDTY23 = 0; 
  PWMDTY6=0;
 
}

else if(a==2){
 PORTB_PB7=1;
 PWMDTY23 = 550; 
 PWMDTY6=7;
} 

 

else
{
PWMDTY23 = 550;      //正转固定
PORTB_PB7=1;



changebaitou=baitoupwm/20;  //速度调节分70段

if(changebaitou>0)okspeed=-2*changebaitou+310;
else  okspeed=2*changebaitou+310;                    //弯道 偏移和速度的一个假象的关系 没有验证过


subspeed=speed_clear[1]-okspeed;                   //当前速度与可行速度关系



if(Straight_flag==1)
   {
   PWMDTY6 = 7;      //占空比50%     60              //直线加速恒占空比
   } 
   
else if(Straight_flag==0)                            //弯道
   {
   
    if(diansha_count%diansha_num==0)
    {diansha_count=0;diansha_falg=0;  }
    
    if(diansha_falg) 
    {PWMDTY6=70;PWMDTY23 =10;diansha_count++;} 
    else  {PWMDTY23 = 550; PWMDTY6=7;}
   }

}
}





/*================收集N点作为坐标的一点======================
如果实时收集处理量过大 所以多点合为一整点 多整点合为一段 多段和为一路
road_point[5]为最后点值

void Collect_Point(void) {
int i;
int code[5]={1,2,3,4,5},sum_code=15;   //加权递推平均法效果如何？ 
long point_sum=0;      //累加过程中最大值会超过32767 因为有正负

if(point_count==4) 
     {
     road_point[4]=befo_General_pos;
     for(i=0;i<=4;i++) 
       {
     point_sum+=road_point[i]*code[i];
     
        }
     point_sum=point_sum/sum_code;
     road_point[5]=point_sum;   
     point_count=0;
     } 
else
    {
    road_point[point_count]=befo_General_pos;
    point_count++;
    }
}
*/
/*================N整点为一段 这个循环处理 推箱子======================
假设2.5  那么我们15cm一段计算第一点到第15cm点的斜率 用来给舵机跑 15cm是为了对舵机延迟的消除
 int road_section[8];              //8段归为一长路  同假设8段为15cm
 int section_count;
 从上往下15cm  0-7
byte Straight_flag;                     //直道标记  非0有效
byte turn_flag;                         //弯道标记  非0有效 

void Collect_Section(void){
int i;
int sub_section;

if(first_flag)
  {
  
  }
if(point_count==0)
{  
for(i=19;i>=0;i--) 
   {
   if(i==0) 
      {
  // speed[0]=speed_clera[1];
   road_section[0]=road_point[5];
      }
   else 
      { 
   road_section[i]=road_section[i-1];
  // speed[i]=speed[i-1];
      }
   }
 }
}



*/


/*================斜率计算======================
15cm的斜率计算 捕捉速度值放这里面
速度 假设200为2.5M/S  那么15cm 累加值大概为6*200
取消斜率 直接用点  

void Judge_Slope(void){
long slop_sum;
if(speed_clera[1]<=230) 
     {
     dajiao_Slope[0]=road_section[0];
     dajiao_Slope[1]=road_section[19];
     slop_sum=(3*dajiao_Slope[0]+dajiao_Slope[1])/4;
     dajiao_Slope[2]=slop_sum;
     } 
else if((speed_clera[1]>230)&&(speed_clera[1]<=270)) 
     {
     dajiao_Slope[0]=road_section[0];
     dajiao_Slope[1]=road_section[18]; 
     slop_sum=(3*dajiao_Slope[0]+dajiao_Slope[1])/4;
     dajiao_Slope[2]=slop_sum;
     } 
else if((speed_clera[1]>270)&&(speed_clera[1]<=310))      
     {
     dajiao_Slope[0]=road_section[0];
     dajiao_Slope[1]=road_section[17]; 
     slop_sum=(3*dajiao_Slope[0]+dajiao_Slope[1])/4;
     dajiao_Slope[2]=slop_sum;
     } 
else      
     {
     dajiao_Slope[0]=road_section[0];
     dajiao_Slope[1]=road_section[16];
     slop_sum=(3*dajiao_Slope[0]+dajiao_Slope[1])/4;
     dajiao_Slope[2]=slop_sum;
     }      
}
*/


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
  temp_position_array[0] = PWMDTY45;
}






//坡道的判断
void Slope_judge(void) 
{
  int i;
  for(i=0;i<LASER_MAX;i++) 
  {
    if(light_temp_laser_array[LASER_MAX]==1)
    {
      quanyi++; 
    }
  }
  if(quanyi ==15)
  {
    slope_flag=1;
  }
}
    
  
*/

