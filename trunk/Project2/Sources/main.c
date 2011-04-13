#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include <MC9S12XS128.h>
#include "math.h"			//abs¾ø¶ÔÖµÒªÓÃµ½
#include "main.h"			//ËùÓÐ±äÁ¿µÄ¶¨Òå¶¼·ÅÔÚmain.hÎÄ¼þÏÂÁË 

 //=====================¶æ»ú³õÊ¼»¯======================//
void PWM_Init(void){     		//PWM³õÊ¼»¯¡£ÆäÖÐP4,P5¿ØÖÆµç»úÕý·´×ª, P6,P7¼¶Áª¼¤¹â¹Ü¿ØÖÆ¶æ»ú¡£

	PWME=0X00;            		//³õÊ¼»¯£¬ÏÈÊÇÍ¨µÀÊ¹ÄÜ½ûÖ¹¡£
	PWMPRCLK=0x11;				//Ô¤·ÖÆµ£¬A,BÊ±ÖÓÎª×ÜÏßµÄ1/2£¬¾ÍÊÇClock AºÍClock B¡£
  
	PWMSCLA=10;            		//SAÊ±ÖÓÉèÖÃ,Clock SA=Clock A/(2*PWMSCLA)¡£
	PWMSCLB=35;             	//SBÊ±ÖÓÉèÖÃ,Clock SB=Clock B/(2*PWMSCLB)¡£
  

	PWMCLK_PCLK0=1;	
	PWMCLK_PCLK1=1;
	PWMCLK_PCLK6=1;
	PWMCLK_PCLK7=1;
  

	PWMPOL_PPOL0=1;				//×ªÏò°ÚÍ·¶æ»ú¼«ÐÔÑ¡ÔñÉèÖÃ
	PWMPOL_PPOL1=1;
	PWMPOL_PPOL6=1;				//¼¤¹â°ÚÍ·Êý×Ö¼«ÐÔÑ¡ÔñÉèÖÃ
	PWMPOL_PPOL7=1;
  
  PWMCTL = 0B00110000;     //Í¨µÀ23¼¶Áª
  
	PWMCAE_CAE0=0;				//×ªÏò°ÚÍ·¶æ»ú¶ÔÆë·½Ê½
	PWMCAE_CAE1=0;	
	PWMCAE_CAE6=1;         		//¼¤¹â°ÚÍ·Êý×Ö¶æ»ú¶ÔÆë·½Ê½
	PWMCAE_CAE7=1;
	
  PWMCNT01 = 0;				//01¿Ú¼ÆÊýÆ÷ÇåÁã£»
  PWMCNT23 = 0;			//¼ÆÊýÆ÷23ÇåÁã 
  
	PWMCTL=0x90;            	//¿ØÖÆ¼Ä´æÆ÷£¬01ºÍ67¿Ú¼¶Áª¡£
	
	PWMPER23 = 1000;    //ÆµÂÊ 8kHz 
	PWMPER01=20000;				//1024¡Á1024£¨ÆµÂÊ£©*Clock A/2/PWMSCLB/PWMPER67
	PWMPER67=1000;				//1024¡Á1024£¨ÆµÂÊ£©*Clock B/2/PWMSCLB/PWMPER67
 
	PWMDTY01=PWM01;
	PWMDTY23 = 0;      //ËÙ¶ÈÎª0£¬¼´¾²Ö¹
	PWMDTY67=PWM67;				//PWMDTY67/PWMPER67*100%
	PWME=0xff;         			//Æô¶¯Í¨µÀÊ¹ÄÜ¡
}
//=====================¼¤¹â³õÊ¼»¯======================//
 void LIGHT_Init(void){ 
	DDRA = 0B00011111;  //PA0--PA7¼¤¹â¹ÜÐÅºÅ¿ØÖÆ --- Êä³ö 
	DDRB = 0X00;        //PB0--PB8¼¤¹â¹ÜÐÅºÅ²É¼¯ --- ÊäÈë
 }
 

//=====================¼¤¹âµãÁÁ======================//
void receive(int send) {
   if(send == 0)   { 
     delayms(1); 
	    light_temp_laser_array[3] = PORTB_PB1^1;	//½ÓÊÕµÚ4×é£¨3,8,13£©  
        light_temp_laser_array[8] = PORTB_PB2^1;
        light_temp_laser_array[13] = PORTB_PB4^1;
        PORTA = 0B00000001;					//µãÁÁµÚ0×é£¨1,6,11£©
    }   
  

   else if(send == 1)   { 
    delayms(1);
        light_temp_laser_array[0] = PORTB_PB0^1;	//½ÓÊÕµÚ0×é£¨0,5,10£©   
        light_temp_laser_array[5] = PORTB_PB1^1; 
        light_temp_laser_array[10] = PORTB_PB3^1;
        PORTA = 0B00000100;					//µãÁÁµÚ1×é£¨2,7,12£©
        
    }
    
    else if(send ==2)   { 
     delayms(1);
		light_temp_laser_array[2] = PORTB_PB0^1;	//½ÓÊÕµÚ1×é£¨2,7,12£©  
        light_temp_laser_array[7] = PORTB_PB2^1; 
        light_temp_laser_array[12] = PORTB_PB4^1;
        PORTA = 0B00010000;					//µãÁÁµÚ2×é£¨4,9,14£©
    } 
    else	if(send == 3)       { 
         delayms(1);
	    light_temp_laser_array[4] = PORTB_PB1^1;	//½ÓÊÕµÚ2×é£¨4,9,14£© 
        light_temp_laser_array[9] = PORTB_PB3^1; 
        light_temp_laser_array[14] = PORTB_PB4^1;
     PORTA = 0B00000010;					//µãÁÁµÚ3×é£¨1,6,11£©
  }
   else if(send == 4)   {
       delayms(1);
        light_temp_laser_array[1] = PORTB_PB0^1;	//½ÓÊÕµÚ3×é£¨1,6,11£©
        light_temp_laser_array[6] = PORTB_PB2^1; 
        light_temp_laser_array[11] = PORTB_PB3^1;	
        PORTA = 0B00001000;					//µãÁÁµÚ4×é£¨3,8,13£©
    } 
   
} 


/*==================ÅÅ³ý¸ÉÈÅµã============================
i-(7-position/2)>3    ÅÅ³ý
²»×ã£ºµ±ÕâÖÖÇé¿öÁ¬Ðø³öÏÖ ÔòÈÏÍ¬
       */
void Confirm_Light(){
 int i=0;
 int halfposition=position/2;
 for(i=0;i<LASER_MAX;i++) {
  if (light_temp_laser_array[i]==0) continue;
  else if (abs(i-(7-halfposition))>=3) light_temp_laser_array[i] =0;
  else continue;   
 }
} 

/*======================lost_blackline();======================*/
void lost_blackline(void){
  int HitBlackNum;
  lost_line_flag=0;
  HitBlackNum=Calculate_HitBlackNum();
  if(HitBlackNum) {
  if (14-abs(His_Position[2])<=3&&(abs(His_Position[2]-position))<=2)
      lost_line_flag=0; 
   else if(14-abs(His_Position[2])<=3&&abs(His_Position[2]+position)<=11)
   lost_line_flag=1;
  } 
  else  
  lost_line_flag=1; 
}

/* ================= SendSmartcarInfo ====================
      desc: SCI´®¿Ú·¢ËÍµ±Ç°¼¤¹â¹Ü²É¼¯ÐÅÏ¢
      pre:  1µ±Ç°¼¤¹â¹Ü²É¼¯Êý×é£¬2µ±Ç°¼¤¹â¹Ü×´Ì¬
      Post: ÎÞ
       
*/ 
/*void SendSmartcarInfo(byte temp_laser_array[]) {
    int i; 
    int data;
    char g[20]=" ";
    for(i=LASER_MAX-1;i>=0;i--)    //·¢ËÍ¼¤¹â¹ÜÐÅÏ¢Êý×é
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


/*=====================¼¤¹â¹Ü¶ÔÓ¦È¨Öµ======================
LASER_MAX    14   13   12   11  10    9   8   7    6    5    4     3     2        1     0
¶ÔÓ¦µÄÈ¨Öµ  -14  -12  -10   -8  -6   -4  -2   0    2    4    6      8     10       12    14
                                                 
³ÌÐòÎ´Íê³É£¬±ØÐëÓÐ²ÎÊýºÍ·µ»ØÖµ£¬ÐèÒª½¨Á¢ÁªÏµ£¡  

==========================================================*/

void Laser_num(void){
  int i;
  for(i=0;i<LASER_MAX;i++){
    q_temp_laser_num[i]=14-2*i;
  }
}

/*=====================¼¤¹â¹ÜÎ»ÖÃµÄÅÐ¶¨======================

È¨Öµ¹«Ê½£º  position= ¡Æ£¨light[i]*lightnum[i]£© / blacknum  
Light[i]ÎªµÚi¸ö¼¤¹âµÄÊýÖµ 0»ò1   ight_temp_laser_array[3]
Lightnum Îª±í1Öµ   q_temp_laser_num[LASER_MAX]
blacknumÎªÕÕºÚ¸öÊý
                                                          
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

/*=====================¼¤¹â¹ÜÕÕµ½ºÚÏßµÄ¸öÊý======================*/

int Calculate_HitBlackNum(void){
  int i,HitBlackNum=0;
  for(i=0;i<LASER_MAX;i++) {
    if(light_temp_laser_array[i]==1){
      HitBlackNum++;
    }
  }
  return HitBlackNum;
}
  
/*=====================¼¤¹â°ÚÍ·======================*/
//×ªÏò¶æ»ú£º1482 1772 1204   °ÚÍ·¶æ»ú£º224+-90
//0.10712*x^2 + 4.5791*10^(-17)*x + 6.7084
//Diff_PositionÊÇÔöÁ¿pdµÄ ¼Óµ½pwmÉÏµÄÔöÁ¿
void  baitou (void) {
   
     
    
  
    
    His_Position[1]=position;  
    His_Position[2]=position;
    His_Position[2]=abs(His_Position[2]); 
    YDiff_Position[1]= Diff_Position;
    
    if(His_Position[2]<=1)
    Diff_Position=0;
    else if(His_Position[2]>1&&His_Position[2]<=3)
    Diff_Position=(4*His_Position[1])/5+3*(YDiff_Position[1]-YDiff_Position[0])/11;
    else if(His_Position[2]>3&&His_Position[2]<=7)
    Diff_Position=(4*His_Position[1])/6+3*(YDiff_Position[1]-YDiff_Position[0])/11;
    else if(His_Position[2]>7&&His_Position[2]<=10)
    Diff_Position=(5*His_Position[1])/6+4*(YDiff_Position[1]-YDiff_Position[0])/11;
    else if(His_Position[2]>10&&His_Position[2]<=12)
    Diff_Position=(4*His_Position[1])/6+4*(YDiff_Position[1]-YDiff_Position[0])/11;
    else if(His_Position[2]>12&&His_Position[2]<=14)
    Diff_Position=(4*His_Position[1])/6+4*(YDiff_Position[1]-YDiff_Position[0])/11;
    
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

/*=======================´ò½Ç¶æ»ú===========================*/
//GDiff_PositionÊÇ´æ´¢ Ò¡Í·¶æ»ú²îÖµ ´«¸ø´ò½ÇµÄ²ÎÊý
//  1488   1778  1198
   
 
void dajiao(void) {
    
    int ZhuanPwm=0;
    GDiff_Position[1]=PWMDTY67-PWM67;
    GDiff_Position[2]=PWMDTY67-PWM67;
    GDiff_Position[2]=abs(GDiff_Position[2]);
    //His_Position[3]=position;
    //His_Position[3]=abs(His_Position[3]);
    
    //if(His_Position[3]<=1){  
   // if(GDiff_Position[1]<=6&&GDiff_Position[1]>=-6)
   // ZhuanPwm=PWM01;           
   // }
    if(GDiff_Position[2]<=8)
    ZhuanPwm=PWM01;
    else if(GDiff_Position[2]>8&&GDiff_Position[2]<=14)
    ZhuanPwm=PWM01-(4*position+GDiff_Position[1])-5*(GDiff_Position[1]-GDiff_Position[0])/11;
    else if(GDiff_Position[2]>14&&GDiff_Position[2]<=24)
    ZhuanPwm=PWM01-(6*position+3*GDiff_Position[1])-5*(GDiff_Position[1]-GDiff_Position[0])/11;
    else if(GDiff_Position[2]>24&&GDiff_Position[2]<=40)
    ZhuanPwm=PWM01-(8*position+4*GDiff_Position[1])-5*(GDiff_Position[1]-GDiff_Position[0])/11;
    else if(GDiff_Position[2]>40&&GDiff_Position[2]<=60)
    ZhuanPwm=PWM01-(9*position+5*GDiff_Position[1])-5*(GDiff_Position[1]-GDiff_Position[0])/11;
    else if(GDiff_Position[2]>60&&GDiff_Position[2]<=80)
    ZhuanPwm=PWM01-(11*position+6*GDiff_Position[1])-5*(GDiff_Position[1]-GDiff_Position[0])/11;
    else if(GDiff_Position[2]>80)
    ZhuanPwm=PWM01-(11*position+7*GDiff_Position[1])-5*(GDiff_Position[1]-GDiff_Position[0])/11;
    
    if(ZhuanPwm>1778)
    ZhuanPwm=1778;
    else if(ZhuanPwm<1198)
    ZhuanPwm=1198;
    
    PWMDTY01=ZhuanPwm;
    GDiff_Position[0]=GDiff_Position[1]; 
  
  } // DerectionCtrl

//¡¾type declaration¡¿
/* ============== ¼¤¹â¹Ü×´Ì¬Ã¶¾ÙÀàÐÍ LASER_STATUS ================ 
 LEFT_NONE (0) ------ ×ó¿Õ     
     LEFT0 (1) ------ ×ó0      LEFT01 (2) ------ ×ó0×ó1     
     LEFT1 (3) ------ ×ó1      LEFT12 (4) ------ ×ó1×ó2
     LEFT2 (5) ------ ×ó2      LEFT23 (6) ------ ×ó2×ó3    
     LEFT3 (7) ------ ×ó3      LEFT34 (8) ------ ×ó3×ó4
     LEFT4 (9) ------ ×ó4      LEFT45 (10) ------×ó4×ó5    
     LEFT5 (11) ------×ó5      LEFT56 (12) ------×ó5×ó6
     LEFT6 (13) ------×ó6      LEFT67 (14) ------×ó6×ó7 
 MID7 (15) ------ ÖÐ7          
     RIGHT78 (16) ------ÓÒ16        RIGHT8 (17) ------ÓÒ8    
     RIGHT89 (18) ------ÓÒ8ÓÒ9      RIGHT9 (19) ------ÓÒ9         
    RIGHT910 (20) ------ÓÒ9ÓÒ10    RIGHT10 (21) ------ÓÒ10    
   RIGHT1011 (22) ------ÓÒ10ÓÒ11   RIGHT11 (23) ------ÓÒ11        
   RIGHT1112 (24) ------ÓÒ11ÓÒ12   RIGHT12 (25) ------ÓÒ12    
   RIGHT1213 (26) ------ÓÒ12ÓÒ13   RIGHT13 (27) ------ÓÒ13        
   RIGHT1314 (28) ------ÓÒ13ÓÒ14   RIGHT14 (29) ------ÓÒ14 
  RIGHT_NONE (30) ------ÓÒ¿Õ  
*/    



/*=====================¼ÆËã¼¤¹â/×ªÏò °ÚÍ·µÄ½Ç¶ÈÖµ======================*/
//27  23  21  20  18  17 16 14 12 11 10  9  7  1 0
void CalculateAngle(int i) {
  // Local Declarations
  int light_micro_delta0 = 0;   /*¼¤Î¢µ÷0*/    int Steering_micro_delta0 = 10;  /*ÏòÎ¢µ÷0*/
  int light_micro_delta1 = 1;  /*¼¤Î¢µ÷1*/     int Steering_micro_delta1 = 15;  /*ÏòÎ¢µ÷0*/
  int light_micro_delta2 = 1;  /*¼¤Î¢µ÷2*/     int Steering_micro_delta2 = 30;  /*ÏòÎ¢µ÷0*/
  int light_micro_delta3 = 1;  /*¼¤Î¢µ÷3*/     int Steering_micro_delta3 = 50;  /*ÏòÎ¢µ÷0*/
  int light_micro_delta4 = 2;  /*¼¤Î¢µ÷4*/     int Steering_micro_delta4 = 60;  /*ÏòÎ¢µ÷0*/
  int light_micro_delta5 = 2;  /*¼¤Î¢µ÷5*/     int Steering_micro_delta5 = 70;  /*ÏòÎ¢µ÷0*/
  
  int light_mid_delta0 = 2;  /*¼¤ÖÐµ÷0*/       int Steering_mid_delta0 = 80;  /*ÏòÖÐµ÷0*/
  int light_mid_delta1 = 2; /*¼¤ÖÐµ÷1*/        int Steering_mid_delta1 = 90;  /*ÏòÖÐµ÷1*/
  int light_mid_delta2 = 2; /*¼¤ÖÐµ÷2*/        int Steering_mid_delta2 = 100;  /*ÏòÖÐµ÷2*/
  int light_mid_delta3 = 2; /*¼¤ÖÐµ÷3*/        int Steering_mid_delta3 = 110;  /*ÏòÖÐµ÷3*/
  int light_mid_delta4 = 2; /*¼¤ÖÐµ÷4*/        int Steering_mid_delta4 = 120;  /*ÏòÖÐµ÷4*/
  
  int light_large_delta0 = 2; /*¼¤´óµ÷0*/      int Steering_large_delta0 = 130; /*Ïò´óµ÷0*/
  int light_large_delta1 = 2; /*¼¤´óµ÷1*/      int Steering_large_delta1 = 140; /*Ïò´óµ÷1*/
  int light_large_delta2 = 2; /*¼¤´óµ÷2*/      int Steering_large_delta2 = 150; /*Ïò´óµ÷2*/
  int light_large_delta3 = 2; /*¼¤´óµ÷3*/      int Steering_large_delta3 = 160; /*Ïò´óµ÷3*/
 
  
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

//=====================¼¤¹â°ÚÍ·¶æ»ú¸Ä±äº¯Êý======================//
void Light_SetDriver(int value){
  PWMDTY67 = value; 
}
void SCI_SetDriver(int value){
  PWMDTY01 = value; 
}
void SpeedCtrl (void) {
PWMDTY23=75;
}

void main(void) {
  int i;

     
  int temp_laserStatus;           //¶¨ÒåÒ»¸öÊý×éÓÃÀ´½ÓÊÜ ÉÏÏÂ¶æ»úÖµ
  EnableInterrupts;
  SetBusCLK_40M();    //   ÉèÖÃÊ±ÖÓ³õÊ¼»¯¡£40MHz.
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
     CalculateAngle(temp_laserStatus); //µÃµ½¶æ»úÐèÒªµ÷ÕûµÄ×ª½Ç 
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
// _FEED_COP(); /*¿´ÃÅ¹·£¬·ÀËÀÑ­»·ÓÃµÄ */
 /* loop forever */
  /* please make sure that you never leave main */
}