/* ================= SendSmartcarInfo ====================
      desc: SCI串口发送当前激光管采集信息
      pre:  1当前激光管采集数组，2当前激光管状态
      Post: 无
       
*/ 
/*void SendSmartcarInfo(byte temp_laser_array[]) {
    int i; 
    int data;
    char g[20]=" ";
    for(i=LASER_MAX-1;i>=0;i--)    //发送激光管信息数组
        {data=temp_laser_array[i]  ;
            if(data == 0) {
            SCISend('0');   
            }
        else if(data == 1) {
             SCISend('1'); 
        }
        }
//  SCISend('\n');
 // sprintf(g,"%u",p);
  //for(i=0;g[i]!='\0';i++)
  //SCISend(g[i]);  
     
}       */


/*=====================激光管对应权值======================
LASER_MAX    14   13   12   11  10    9   8   7    6    5    4     3     2        1     0
对应的权值  -14  -12  -10   -8  -6   -4  -2   0    2    4    6      8     10       12    14
                                                 
程序未完成，必须有参数和返回值，需要建立联系！  

==========================================================*/

void Laser_num(void){
  int i;
  for(i=0;i<LASER_MAX;i++){
    q_temp_laser_num[i]=14-2*i;
  }
}

/*=====================激光管位置的判定======================

权值公式：  position= ∑（light[i]*lightnum[i]） / blacknum  
Light[i]为第i个激光的数值 0或1   ight_temp_laser_array[3]
Lightnum 为表1值   q_temp_laser_num[LASER_MAX]
blacknum为照黑个数
                                                          
==========================================================*/
int Status_Judge(void) {
  int i,temp_HitBlackNum,sum=0;
  temp_HitBlackNum=Calculate_HitBlackNum();
  for(i=0;i<LASER_MAX;i++){
    sum=sum+light_temp_laser_array[i]*q_temp_laser_num[i];
  }
  position=sum/temp_HitBlackNum;
  
  return position;
    
}

/*=====================激光管照到黑线的个数======================*/

int Calculate_HitBlackNum(void){
  int i,HitBlackNum=0;
  for(i=0;i<LASER_MAX;i++) {
    if(light_temp_laser_array[i]==1){
      HitBlackNum++;
    }
  }
  return HitBlackNum;
}
  
/*=====================激光摆头======================*/
//转向舵机：1482 1772 1204   摆头舵机：224+-90
//0.10712*x^2 + 4.5791*10^(-17)*x + 6.7084
//Diff_Position是增量pd的 加到pwm上的增量
void  baitou (void) {
   
     
    
  
    
    His_Position[1]=position;  
    His_Position[2]=position;
    His_Position[2]=aabs(His_Position[2]); 
    YDiff_Position[1]= Diff_Position;
    
    if(His_Position[2]<=1)
    Diff_Position=0;
    else if(His_Position[2]>1&&His_Position[2]<=3)
    Diff_Position=0.4*His_Position[1]+2.7*(His_Position[1]-His_Position[0]);
    else if(His_Position[2]>3&&His_Position[2]<=7)
    Diff_Position=0.5*His_Position[1]+2.7*(His_Position[1]-His_Position[0]);
    else if(His_Position[2]>7&&His_Position[2]<=10)
    Diff_Position=0.7*His_Position[1]+2.7*(His_Position[1]-His_Position[0]);
    else if(His_Position[2]>10&&His_Position[2]<=12)
    Diff_Position=0.8*His_Position[1]+2.7*(His_Position[1]-His_Position[0]);
    else if(His_Position[2]>12&&His_Position[2]<=14)
    Diff_Position=0.9*His_Position[1]+2.7*(His_Position[1]-His_Position[0]);
    
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
    
     YDiff_Position[0]=YDiff_Position[1];
     His_Position[0]=His_Position[1];
     PWMDTY67=PWMDTY67+Diff_Position;
    
}

/*=======================打角舵机===========================*/
//GDiff_Position是存储 摇头舵机差值 传给打角的参数
//  1488   1778  1198
   
 
void dajiao(void) {
    
    int ZhuanPwm=0;
    GDiff_Position[1]=PWMDTY67-PWM67;
    GDiff_Position[2]=PWMDTY67-PWM67;
    GDiff_Position[2]=aabs(GDiff_Position[2]);
    //His_Position[3]=position;
    //His_Position[3]=abs(His_Position[3]);
    
    //if(His_Position[3]<=1){  
   // if(GDiff_Position[1]<=6&&GDiff_Position[1]>=-6)
   // ZhuanPwm=PWM01;           
   // }
    if(GDiff_Position[2]<=8)
    ZhuanPwm=PWM01;
    else if(GDiff_Position[2]>8&&GDiff_Position[2]<=14)
    ZhuanPwm=PWM01-(5*position+1.7*GDiff_Position[1])-2.3*(GDiff_Position[1]-GDiff_Position[0]);
    else if(GDiff_Position[2]>14&&GDiff_Position[2]<=24)
    ZhuanPwm=PWM01-(7*position+3.5*GDiff_Position[1])-2.3*(GDiff_Position[1]-GDiff_Position[0]);
    else if(GDiff_Position[2]>24&&GDiff_Position[2]<=40)
    ZhuanPwm=PWM01-(9*position+4.9*GDiff_Position[1])-2.3*(GDiff_Position[1]-GDiff_Position[0]);
    else if(GDiff_Position[2]>40&&GDiff_Position[2]<=60)
    ZhuanPwm=PWM01-(11*position+6.5*GDiff_Position[1])-2.3*(GDiff_Position[1]-GDiff_Position[0]);
    else if(GDiff_Position[2]>60&&GDiff_Position[2]<=80)
    ZhuanPwm=PWM01-(13*position+7.8*GDiff_Position[1])-2.3*(GDiff_Position[1]-GDiff_Position[0]);
    else if(GDiff_Position[2]>80)
    ZhuanPwm=PWM01-(14*position+7.8*GDiff_Position[1])-2.3*(GDiff_Position[1]-GDiff_Position[0]);
    
    if(ZhuanPwm>1778)
    ZhuanPwm=1778;
    else if(ZhuanPwm<1198)
    ZhuanPwm=1198;
    
    PWMDTY01=ZhuanPwm;
    GDiff_Position[0]=GDiff_Position[1]; 
  
  } // DerectionCtrl

//【type declaration】
/* ============== 激光管状态枚举类型 LASER_STATUS ================ 
 LEFT_NONE (0) ------ 左空     
     LEFT0 (1) ------ 左0      LEFT01 (2) ------ 左0左1     
     LEFT1 (3) ------ 左1      LEFT12 (4) ------ 左1左2
     LEFT2 (5) ------ 左2      LEFT23 (6) ------ 左2左3    
     LEFT3 (7) ------ 左3      LEFT34 (8) ------ 左3左4
     LEFT4 (9) ------ 左4      LEFT45 (10) ------左4左5    
     LEFT5 (11) ------左5      LEFT56 (12) ------左5左6
     LEFT6 (13) ------左6      LEFT67 (14) ------左6左7 
 MID7 (15) ------ 中7          
     RIGHT78 (16) ------右16        RIGHT8 (17) ------右8    
     RIGHT89 (18) ------右8右9      RIGHT9 (19) ------右9         
    RIGHT910 (20) ------右9右10    RIGHT10 (21) ------右10    
   RIGHT1011 (22) ------右10右11   RIGHT11 (23) ------右11        
   RIGHT1112 (24) ------右11右12   RIGHT12 (25) ------右12    
   RIGHT1213 (26) ------右12右13   RIGHT13 (27) ------右13        
   RIGHT1314 (28) ------右13右14   RIGHT14 (29) ------右14 
  RIGHT_NONE (30) ------右空  
*/    



/*=====================计算激光/转向 摆头的角度值======================*/
//27  23  21  20  18  17 16 14 12 11 10  9  7  1 0
void CalculateAngle(int i) {
  // Local Declarations
  int light_micro_delta0 = 0;   /*激微调0*/    int Steering_micro_delta0 = 10;  /*向微调0*/
  int light_micro_delta1 = 1;  /*激微调1*/     int Steering_micro_delta1 = 15;  /*向微调0*/
  int light_micro_delta2 = 1;  /*激微调2*/     int Steering_micro_delta2 = 30;  /*向微调0*/
  int light_micro_delta3 = 1;  /*激微调3*/     int Steering_micro_delta3 = 50;  /*向微调0*/
  int light_micro_delta4 = 2;  /*激微调4*/     int Steering_micro_delta4 = 60;  /*向微调0*/
  int light_micro_delta5 = 2;  /*激微调5*/     int Steering_micro_delta5 = 70;  /*向微调0*/
  
  int light_mid_delta0 = 2;  /*激中调0*/       int Steering_mid_delta0 = 80;  /*向中调0*/
  int light_mid_delta1 = 2; /*激中调1*/        int Steering_mid_delta1 = 90;  /*向中调1*/
  int light_mid_delta2 = 2; /*激中调2*/        int Steering_mid_delta2 = 100;  /*向中调2*/
  int light_mid_delta3 = 2; /*激中调3*/        int Steering_mid_delta3 = 110;  /*向中调3*/
  int light_mid_delta4 = 2; /*激中调4*/        int Steering_mid_delta4 = 120;  /*向中调4*/
  
  int light_large_delta0 = 2; /*激大调0*/      int Steering_large_delta0 = 130; /*向大调0*/
  int light_large_delta1 = 2; /*激大调1*/      int Steering_large_delta1 = 140; /*向大调1*/
  int light_large_delta2 = 2; /*激大调2*/      int Steering_large_delta2 = 150; /*向大调2*/
  int light_large_delta3 = 2; /*激大调3*/      int Steering_large_delta3 = 160; /*向大调3*/
 
  
  // Statements
  switch( i ) {
      case  15:   {
          angle[0] =light_large_delta3;
          angle[1] =-Steering_large_delta3;
          break;
      }
      case  14:  {
          angle[0] =light_large_delta2;  
          angle[1] =-Steering_large_delta2;
          break;
      }
      case  13:  {
          angle[0] =light_large_delta1; 
          angle[1] =-Steering_large_delta1;
          break;
      }
      case  12 : {
          angle[0] =light_large_delta0;
          angle[1] =-Steering_large_delta0;
          break;
      }
      case  11:   {
          angle[0] =light_mid_delta4;
          angle[1]=-Steering_mid_delta4;
          break;
      }
      case  10:  {
          angle[0] =light_mid_delta3;
          angle[1]=-Steering_mid_delta3;
          break;
      }
      case  9:  {
          angle[0] =light_mid_delta2;
          angle[1]=-Steering_mid_delta2;
          break;
      }
      case  8: {
          angle[0] =light_mid_delta1; 
          angle[1]=-Steering_mid_delta1;
          break;
      }
      case  7:   {
          angle[0] =light_mid_delta0; 
          angle[1]=-Steering_mid_delta0;
          break;
      }
      case  6:  {
          angle[0] =light_micro_delta5; 
          angle[1]=-Steering_micro_delta5;
          break;
      }
      case  5:  {
          angle[0] =light_micro_delta4; 
          angle[1]=-Steering_micro_delta4;
          break;
      }
      case  4: {
          angle[0] =light_micro_delta3; 
          angle[1]=-Steering_micro_delta3;
          break;
      }
      case  3:   {
          angle[0] =light_micro_delta2; 
          angle[1]=-Steering_micro_delta2;
          break;
      }
      case  2:  {
          angle[0] =light_micro_delta1; 
          angle[1]=-Steering_micro_delta1;
          break;
      }
      case  1:   {
          angle[0] =light_micro_delta0; 
          angle[1]=-Steering_micro_delta0;
          break;
      }
      case  0:  {
          angle[0] = 0;
          angle[1]=0;
          break;
      }
      case  -1:   {
          angle[0] = -light_micro_delta0; 
          angle[1]= Steering_micro_delta0;
          break;
      }
      case  -2:  {
          angle[0] =- light_micro_delta1; 
          angle[1]= Steering_micro_delta1;
          break;
      }                 
      case  -3:   {
          angle[0] = -light_micro_delta2; 
          angle[1]= Steering_micro_delta2;
          break;
      }
      case  -4:  {
          angle[0] = -light_micro_delta3; 
          angle[1]= Steering_micro_delta3;
          break;
      }
      case  -5:   {
          angle[0] = -light_micro_delta4; 
          angle[1]= Steering_micro_delta4;
          break;
      }
      case  -6:  {
          angle[0] = -light_micro_delta5; 
          angle[1]= Steering_micro_delta5;
          break;
      }
      case  -7:  {
          angle[0] = -light_mid_delta0; 
          angle[1]= Steering_mid_delta0;
          break;
      }
      case  -8:  {
          angle[0] =  -light_mid_delta1; 
          angle[1]= Steering_mid_delta1;
          break;
      }
      case  -9:   {
          angle[0] =  -light_mid_delta2; 
          angle[1]= Steering_mid_delta2;
          break;
      } 
      case  -10:  {
          angle[0] =  -light_mid_delta3; 
          angle[1]= Steering_mid_delta3;
          break;
      }
      case  -11:   {
          angle[0] = -light_mid_delta4; 
          angle[1]= Steering_mid_delta4;
          break;
      } 
      case  -12:  {
          angle[0] =  -light_large_delta0; 
          angle[1] = Steering_large_delta0;
          break;
      }
      case  -13: {
          angle[0] =  -light_large_delta1; 
          angle[1] = Steering_large_delta1;
          break;
      }
      case  -14:{
          angle[0] =  -light_large_delta2; 
          angle[1] = Steering_large_delta2;
          break;
      }
      case  -15:{
          angle[0] =  -light_large_delta3; 
          angle[1] = Steering_large_delta3;
          break;
      }
      default: break;
  }  
  
  //return *angle;    
} //CalculateAngle

//=====================激光摆头舵机改变函数======================//
void Light_SetDriver(int value){
  PWMDTY67 = value; 
}
void SCI_SetDriver(int value){
  PWMDTY01 = value; 
}
void SpeedCtrl (void) {
PWMDTY23=75;
}
