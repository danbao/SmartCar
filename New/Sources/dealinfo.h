/* ================= SendSmartcarInfo ====================
      desc: SCI���ڷ��͵�ǰ����ܲɼ���Ϣ
      pre:  1��ǰ����ܲɼ����飬2��ǰ�����״̬
      Post: ��
       
*/ 
/*void SendSmartcarInfo(byte temp_laser_array[]) {
    int i; 
    int data;
    char g[20]=" ";
    for(i=LASER_MAX-1;i>=0;i--)    //���ͼ������Ϣ����
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


/*=====================����ܶ�ӦȨֵ======================
LASER_MAX    14   13   12   11  10    9   8   7    6    5    4     3     2        1     0
��Ӧ��Ȩֵ  -14  -12  -10   -8  -6   -4  -2   0    2    4    6      8     10       12    14
                                                 
����δ��ɣ������в����ͷ���ֵ����Ҫ������ϵ��  

==========================================================*/

void Laser_num(void){
  int i;
  for(i=0;i<LASER_MAX;i++){
    q_temp_laser_num[i]=14-2*i;
  }
}

/*=====================�����λ�õ��ж�======================

Ȩֵ��ʽ��  position= �ƣ�light[i]*lightnum[i]�� / blacknum  
Light[i]Ϊ��i���������ֵ 0��1   ight_temp_laser_array[3]
Lightnum Ϊ��1ֵ   q_temp_laser_num[LASER_MAX]
blacknumΪ�պڸ���
                                                          
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

/*=====================������յ����ߵĸ���======================*/

int Calculate_HitBlackNum(void){
  int i,HitBlackNum=0;
  for(i=0;i<LASER_MAX;i++) {
    if(light_temp_laser_array[i]==1){
      HitBlackNum++;
    }
  }
  return HitBlackNum;
}
  
/*=====================�����ͷ======================*/
//ת������1482 1772 1204   ��ͷ�����224+-90
//0.10712*x^2 + 4.5791*10^(-17)*x + 6.7084
//Diff_Position������pd�� �ӵ�pwm�ϵ�����
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

/*=======================��Ƕ��===========================*/
//GDiff_Position�Ǵ洢 ҡͷ�����ֵ ������ǵĲ���
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

//��type declaration��
/* ============== �����״̬ö������ LASER_STATUS ================ 
 LEFT_NONE (0) ------ ���     
     LEFT0 (1) ------ ��0      LEFT01 (2) ------ ��0��1     
     LEFT1 (3) ------ ��1      LEFT12 (4) ------ ��1��2
     LEFT2 (5) ------ ��2      LEFT23 (6) ------ ��2��3    
     LEFT3 (7) ------ ��3      LEFT34 (8) ------ ��3��4
     LEFT4 (9) ------ ��4      LEFT45 (10) ------��4��5    
     LEFT5 (11) ------��5      LEFT56 (12) ------��5��6
     LEFT6 (13) ------��6      LEFT67 (14) ------��6��7 
 MID7 (15) ------ ��7          
     RIGHT78 (16) ------��16        RIGHT8 (17) ------��8    
     RIGHT89 (18) ------��8��9      RIGHT9 (19) ------��9         
    RIGHT910 (20) ------��9��10    RIGHT10 (21) ------��10    
   RIGHT1011 (22) ------��10��11   RIGHT11 (23) ------��11        
   RIGHT1112 (24) ------��11��12   RIGHT12 (25) ------��12    
   RIGHT1213 (26) ------��12��13   RIGHT13 (27) ------��13        
   RIGHT1314 (28) ------��13��14   RIGHT14 (29) ------��14 
  RIGHT_NONE (30) ------�ҿ�  
*/    



/*=====================���㼤��/ת�� ��ͷ�ĽǶ�ֵ======================*/
//27  23  21  20  18  17 16 14 12 11 10  9  7  1 0
void CalculateAngle(int i) {
  // Local Declarations
  int light_micro_delta0 = 0;   /*��΢��0*/    int Steering_micro_delta0 = 10;  /*��΢��0*/
  int light_micro_delta1 = 1;  /*��΢��1*/     int Steering_micro_delta1 = 15;  /*��΢��0*/
  int light_micro_delta2 = 1;  /*��΢��2*/     int Steering_micro_delta2 = 30;  /*��΢��0*/
  int light_micro_delta3 = 1;  /*��΢��3*/     int Steering_micro_delta3 = 50;  /*��΢��0*/
  int light_micro_delta4 = 2;  /*��΢��4*/     int Steering_micro_delta4 = 60;  /*��΢��0*/
  int light_micro_delta5 = 2;  /*��΢��5*/     int Steering_micro_delta5 = 70;  /*��΢��0*/
  
  int light_mid_delta0 = 2;  /*���е�0*/       int Steering_mid_delta0 = 80;  /*���е�0*/
  int light_mid_delta1 = 2; /*���е�1*/        int Steering_mid_delta1 = 90;  /*���е�1*/
  int light_mid_delta2 = 2; /*���е�2*/        int Steering_mid_delta2 = 100;  /*���е�2*/
  int light_mid_delta3 = 2; /*���е�3*/        int Steering_mid_delta3 = 110;  /*���е�3*/
  int light_mid_delta4 = 2; /*���е�4*/        int Steering_mid_delta4 = 120;  /*���е�4*/
  
  int light_large_delta0 = 2; /*�����0*/      int Steering_large_delta0 = 130; /*����0*/
  int light_large_delta1 = 2; /*�����1*/      int Steering_large_delta1 = 140; /*����1*/
  int light_large_delta2 = 2; /*�����2*/      int Steering_large_delta2 = 150; /*����2*/
  int light_large_delta3 = 2; /*�����3*/      int Steering_large_delta3 = 160; /*����3*/
 
  
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

//=====================�����ͷ����ı亯��======================//
void Light_SetDriver(int value){
  PWMDTY67 = value; 
}
void SCI_SetDriver(int value){
  PWMDTY01 = value; 
}
void SpeedCtrl (void) {
PWMDTY23=75;
}
