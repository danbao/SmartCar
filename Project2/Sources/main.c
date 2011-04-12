#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include <MC9S12XS128.h>
#define LASER_MAX 15          //���������
#define PWM67 224	
#define PWM01 1488
#define ANGLE_DELTA 30
#define PWM6_MID 224		

//===============ȫ�ֱ�������======================//
   int temp_pwm67=PWM67;						//�����ͷ�����ʼֵ
  int temp_pwm01=PWM01;						//ת���ͷ�����ʼֵ
  byte light_temp_laser_array[LASER_MAX];  //��ǰ�������Ϣ��������
  int testcount=1;
  int count=1;                                  //���ڽ�����ʱ
  int q_temp_laser_num[LASER_MAX];       //����ܶ�Ӧ��Ȩֵ
  int countPIT0=0;
  int position=0;                        
  int His_ADD_Position[3];                      //�����ۼ�ֵ��ʷ   His_ADD_Position[2]=aabs[1]
  int His_Position[4];                        //��ʷposition  position[3]=position[1]-position[0] position[2]=aabs[position]
  int angle[2]; 
  int Calculate_HitBlackNum(void);
  int YaoKp ,YaoKd,ZhuanKp,ZhuanKd;
  byte lost_line_flag=0;
  int ADD_Position; 
  int Diff_Position;
  int GDiff_Position[3];                      //ҡͷ����İ�ֵ  GDiff_Position[2]=aabs��GD��1����
  
//===============ʱ�ӳ�ʼ��========================//

void SetBusCLK_40M()
{   
    CLKSEL=0X00;				//disengage PLL to system
    PLLCTL_PLLON=1;			//turn on PLL
    SYNR =0xc0 | 0x04;                        
    REFDV=0x80 | 0x01; 
    POSTDIV=0x00;       //pllclock=2*osc*(1+SYNR)/(1+REFDV)=80MHz;
    _asm(nop);          //BUS CLOCK=40M
    _asm(nop);
    while(!(CRGFLG_LOCK==1));	  //when pll is steady ,then use it;
    CLKSEL_PLLSEL =1;		        //engage PLL to system; 
}  

//=====================���ڽ��պ���====================//
char SCI_RXD(void)
{
    char ch; 
    while (!(SCI0SR1 & 0x20));       //�ȴ������������
    SCI0SR1_RDRF = 1;
    ch = SCI0DRL;
    return ch;
}
//==============���������ʾ����========================//
void SCISend(unsigned char ch)
{ 
  if (ch == '\n')  
  {
      while(!(SCI0SR1&0x80)) ;     
      SCI0DRL= 0x0d;   
      while(!(SCI0SR1&0x80)) ;     
      SCI0DRL= 0x0a;               
     return;
  } 
  else while (!(SCI0SR1&0x80));
    SCI0DRH=0;
    SCI0DRL=ch;
}

static void SCI_Init(void)  //SCI
{
    SCI0CR1=0x00;
    SCI0CR2=0x2c;
     SCI0BD=260;                    //���ò����ʹ�ʽ=����Ƶ��/����Ҫ�Ĳ�����/16=��Ҫ���õ�ֵ;
                  
}
//==============��ʱ����================================//
void delayms(int ms)    //��ʱ����
{   
   int ii,jj;
   if (ms<1) ms=1;
   for(ii=0;ii<ms;ii++)
     for(jj=0;jj<3338;jj++);    //40MHz--1ms      
}

//==============aabs����ֵ================================//
int aabs(int num) {
if (num>=0)return num;
else {
num=-num;return num;
}
}
 //=====================�����ʼ��======================//
void PWM_Init(void){     		//PWM��ʼ��������P4,P5���Ƶ������ת, P6,P7��������ܿ��ƶ����

	PWME=0X00;            		//��ʼ��������ͨ��ʹ�ܽ�ֹ��
	PWMPRCLK=0x11;				//Ԥ��Ƶ��A,Bʱ��Ϊ���ߵ�1/2������Clock A��Clock B��
  
	PWMSCLA=10;            		//SAʱ������,Clock SA=Clock A/(2*PWMSCLA)��
	PWMSCLB=35;             	//SBʱ������,Clock SB=Clock B/(2*PWMSCLB)��
  

	PWMCLK_PCLK0=1;	
	PWMCLK_PCLK1=1;
	PWMCLK_PCLK6=1;
	PWMCLK_PCLK7=1;
  

	PWMPOL_PPOL0=1;				//ת���ͷ�������ѡ������
	PWMPOL_PPOL1=1;
	PWMPOL_PPOL6=1;				//�����ͷ���ּ���ѡ������
	PWMPOL_PPOL7=1;
  
  PWMCTL = 0B00100000;     //ͨ��23����
  PWMCTL=0xf0;
	PWMCAE_CAE0=0;				//ת���ͷ������뷽ʽ
	PWMCAE_CAE1=0;	
	PWMCAE_CAE6=1;         		//�����ͷ���ֶ�����뷽ʽ
	PWMCAE_CAE7=1;
	
  PWMCNT01 = 0;				//01�ڼ��������㣻
  PWMCNT23 = 0;			//������23���� 
  
 //	PWMCTL=0x90;            	//���ƼĴ�����01��67�ڼ�����
	
	PWMPER23 = 125;    //Ƶ�� 8kHz 
	PWMPER01=20000;				//1024��1024��Ƶ�ʣ�*Clock A/2/PWMSCLB/PWMPER67
	PWMPER67=1000;				//1024��1024��Ƶ�ʣ�*Clock B/2/PWMSCLB/PWMPER67
 
	PWMDTY01=PWM01;
	PWMDTY23 =0;      //�ٶ�Ϊ0������ֹ
	PWMDTY67=PWM67;				//PWMDTY67/PWMPER67*100%
	PWME=0xaa;  
}
//=====================�����ʼ��======================//
 void LIGHT_Init(void){ 
	DDRA = 0B00011111;  //PA0--PA7������źſ��� --- ��� 
	DDRB = 0X00;        //PB0--PB8������źŲɼ� --- ����
 }
 

//=====================�������======================//
void receive(int send) {
   if(send == 0)   { 
     delayms(1); 
	    light_temp_laser_array[3] = PORTB_PB1^1;	//���յ�4�飨3,8,13��  
        light_temp_laser_array[8] = PORTB_PB2^1;
        light_temp_laser_array[13] = PORTB_PB4^1;
        PORTA = 0B00000001;					//������0�飨1,6,11��
    }   
  

   else if(send == 1)   { 
    delayms(1);
        light_temp_laser_array[0] = PORTB_PB0^1;	//���յ�0�飨0,5,10��   
        light_temp_laser_array[5] = PORTB_PB1^1; 
        light_temp_laser_array[10] = PORTB_PB3^1;
        PORTA = 0B00000100;					//������1�飨2,7,12��
        
    }
    
    else if(send ==2)   { 
     delayms(1);
		light_temp_laser_array[2] = PORTB_PB0^1;	//���յ�1�飨2,7,12��  
        light_temp_laser_array[7] = PORTB_PB2^1; 
        light_temp_laser_array[12] = PORTB_PB4^1;
        PORTA = 0B00010000;					//������2�飨4,9,14��
    } 
    else	if(send == 3)       { 
         delayms(1);
	    light_temp_laser_array[4] = PORTB_PB1^1;	//���յ�2�飨4,9,14�� 
        light_temp_laser_array[9] = PORTB_PB3^1; 
        light_temp_laser_array[14] = PORTB_PB4^1;
     PORTA = 0B00000010;					//������3�飨1,6,11��
  }
   else if(send == 4)   {
       delayms(1);
        light_temp_laser_array[1] = PORTB_PB0^1;	//���յ�3�飨1,6,11��
        light_temp_laser_array[6] = PORTB_PB2^1; 
        light_temp_laser_array[11] = PORTB_PB3^1;	
        PORTA = 0B00001000;					//������4�飨3,8,13��
    } 
   
} 


/*==================�ų����ŵ�============================
i-(7-position/2)>3    �ų�
���㣺����������������� ����ͬ
*/
void Confirm_Light(){
 int i=0;
 int halfposition=position/2;
 for(i=0;i<LASER_MAX;i++) {
  if (light_temp_laser_array[i]==0) continue;
  else if (aabs(i-(7-halfposition))>=3) light_temp_laser_array[i] =0;
  else continue;   
 }
}

/*======================lost_blackline();======================*/
void lost_blackline(void){
  int HitBlackNum;
  lost_line_flag=0;
  HitBlackNum=Calculate_HitBlackNum();
  if(HitBlackNum) {
  if (14-aabs(His_Position[2])<=3&&(aabs(His_Position[2]-position))<=2)
      lost_line_flag=0; 
   else if(14-aabs(His_Position[2])<=3&&aabs(His_Position[2]+position)<=11)
   lost_line_flag=1;
  } 
  else  
  lost_line_flag=1; 
}

/* ================= SendSmartcarInfo ====================
      desc: SCI���ڷ��͵�ǰ����ܲɼ���Ϣ
      pre:  1��ǰ����ܲɼ����飬2��ǰ�����״̬
      Post: ��
       
*/ 
void SendSmartcarInfo(byte temp_laser_array[]) {
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
     
}


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
    
    if(His_Position[2]<=1)
    Diff_Position=0;
    else if(His_Position[2]>1&&His_Position[2]<=3)
    Diff_Position=(3*His_Position[1])/5;
    else if(His_Position[2]>3&&His_Position[2]<=7)
    Diff_Position=(5*His_Position[1])/4;
    else if(His_Position[2]>7&&His_Position[2]<=10)
    Diff_Position=(6*His_Position[1])/4;
    else if(His_Position[2]>10&&His_Position[2]<=12)
    Diff_Position=(6*His_Position[1])/5;
    else if(His_Position[2]>12&&His_Position[2]<=14)
    Diff_Position=(7*His_Position[1])/5;
    
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

/*=======================��Ƕ��===========================*/
//GDiff_Position�Ǵ洢 ҡͷ�����ֵ ������ǵĲ���
//  1488   1778  1198
   
 
void dajiao(void) {
    
    int ZhuanPwm=0;
    GDiff_Position[1]=PWMDTY67-PWM67;
    GDiff_Position[2]=PWMDTY67-PWM67;
    GDiff_Position[2]=aabs(GDiff_Position[2]);
    //His_Position[3]=position;
    //His_Position[3]=aabs(His_Position[3]);
    
    //if(His_Position[3]<=1){  
   // if(GDiff_Position[1]<=6&&GDiff_Position[1]>=-6)
   // ZhuanPwm=PWM01;           
   // }
    if(GDiff_Position[2]<=8)
    ZhuanPwm=PWM01;
    else if(GDiff_Position[2]>8&&GDiff_Position[2]<=14)
    ZhuanPwm=PWM01-(4*position+GDiff_Position[1])-0*(GDiff_Position[1]-GDiff_Position[0]);
    else if(GDiff_Position[2]>14&&GDiff_Position[2]<=24)
    ZhuanPwm=PWM01-(6*position+3*GDiff_Position[1])-0*(GDiff_Position[1]-GDiff_Position[0]);
    else if(GDiff_Position[2]>24&&GDiff_Position[2]<=40)
    ZhuanPwm=PWM01-(8*position+5*GDiff_Position[1])-0*(GDiff_Position[1]-GDiff_Position[0]);
    else if(GDiff_Position[2]>40&&GDiff_Position[2]<=60)
    ZhuanPwm=PWM01-(10*position+6*GDiff_Position[1])-0*(GDiff_Position[1]-GDiff_Position[0]);
    else if(GDiff_Position[2]>60&&GDiff_Position[2]<=80)
    ZhuanPwm=PWM01-(12*position+7*GDiff_Position[1])-0*(GDiff_Position[1]-GDiff_Position[0]);
    else if(GDiff_Position[2]>80)
    ZhuanPwm=PWM01-(12*position+7*GDiff_Position[1])-0*(GDiff_Position[1]-GDiff_Position[0]);
    
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
PWMDTY23=58;
}

void main(void) {
  int i;

     
  int temp_laserStatus;           //����һ�������������� ���¶��ֵ
  EnableInterrupts;
  SetBusCLK_40M();    //   ����ʱ�ӳ�ʼ����40MHz.
  PWM_Init();
  LIGHT_Init();
  delayms(2);
  Laser_num();
   SCI_Init();
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
     CalculateAngle(temp_laserStatus); //�õ������Ҫ������ת�� 
    dajiao();     
   testcount++;
  if(testcount%25==0){
       testcount=1;
   baitou( );
   }
    
     SpeedCtrl();
     receive(i);
    } else receive(i);
  }
// _FEED_COP(); /*���Ź�������ѭ���õ� */
 /* loop forever */
  /* please make sure that you never leave main */
}
//===================��ͷ����ж�================//
#pragma CODE_SEG __NEAR_SEG NON_BANKED 
interrupt 20 void Rx_SetDriver(void)
{
    char tmp;
    char result;
    DisableInterrupts;
    tmp = SCI0SR1;                   //�����־
    result= SCI_RXD();
    switch(result)
    {
      case 'd':                          //�����ͷ�������ƫ����
        temp_pwm67=temp_pwm67+1;
        Light_SetDriver(temp_pwm67);
       SCISend('d'); 
      break;
            case 'a':                   //�����ͷ�������ƫ����
        temp_pwm67=temp_pwm67-1;
        Light_SetDriver(temp_pwm67);
       SCISend('a'); 
      break;
            case 'r':                      //�����ͷ�������
        temp_pwm67=PWM67; 
        Light_SetDriver(temp_pwm67);
       SCISend('r');
      break;
            case 'j':                          //ת���ͷ�������ƫ���� 5�ȵ�
        temp_pwm01=temp_pwm01+5;
        SCI_SetDriver(temp_pwm01);
       SCISend('j'); 
      break;
            case 'l':                         //ת���ͷ�������ƫ���� 5�ȵ�
        temp_pwm01=temp_pwm01-5;
        SCI_SetDriver(temp_pwm01);
       SCISend('l'); 
      break;
            case 'n':                          //ת���ͷ�������ƫ���� 5�ȵ�
        temp_pwm01=temp_pwm01+1;
        SCI_SetDriver(temp_pwm01);
       SCISend('n'); 
      break;
            case 'm':                         //ת���ͷ�������ƫ���� 5�ȵ�
        temp_pwm01=temp_pwm01-1;
        SCI_SetDriver(temp_pwm01);
       SCISend('m'); 
      break;
            case 'p':                      //ת���ͷ�������
        temp_pwm01=PWM01; 
        SCI_SetDriver(temp_pwm01);
       SCISend('p');
      break;
    }
    EnableInterrupts;
}
#pragma CODE_SEG DEFAULT