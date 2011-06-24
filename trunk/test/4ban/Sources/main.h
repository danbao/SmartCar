#define LASER_MAX 21          //���������
char SCIreceive[100];
int count;
byte light_temp_laser_array[LASER_MAX];  //��ǰ�������Ϣ��������
#define PWM01 3808
#define PWM45 3808
#define PWM7 30
#define PWMPE7 60

  int light_count;	
//===============ʱ�ӳ�ʼ��========================//
void SetBusCLK_40M(void)
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

//=====================PWM��ʼ��======================//
void PWM_Init (void) {   //0519��ʱд�꣡
  // Local Declarations

  // Statements
   PWME = 0X00;       //��ֹPWM���  
   PWMCAE = 0X00;     //�����
   
   //PWMCNT01 = 0; //������01����
   //PWMCNT23 = 0; //������23����
   //PWMCNT45 = 0; //������45����
   //PWMCNT67 = 0; //������67����
 
   PWMPOL = 0XFF;     //������ߵ�ƽ   PWM���ԼĴ���
   PWMCTL = 0X70;     //ͨ��01������23������45����
   PWMPRCLK = 0X21;   //clockA 2��Ƶ,clockA=busclock/2=20MHz;CLK B 4��Ƶ:10Mhz 
   PWMSCLA = 4;       //��clock SA ����2*4=8��Ƶ��pwm clock=clockA/8=2.5MHz;
   PWMSCLB = 4;       //��clock SB ����2*4=8��Ƶ��pwm clock=clockB/8=1.25MHz;
   PWMCLK_PCLK1 = 1;  //ѡ��clock SA��ʱ��Դ  
   PWMCLK_PCLK3 = 0;  //ѡ��clock SB��ʱ��Դ  
   PWMCLK_PCLK5 = 1;  //ѡ��clock SA��ʱ��Դ  
   PWMCLK_PCLK6 = 1;  //ѡ��clock B ��ʱ��Դ
   PWMCLK_PCLK7 = 0;  //ѡ��clock B ��ʱ��Դ      

   PWMPER01 = 25000;    //Ƶ�� 100Hz  ����0.1ms
   PWMPER23 = 625;    //Ƶ�� 16kHz  
   PWMPER45 = 25000;  //Ƶ�� 100Hz  
   PWMPER6 = 78;  //Ƶ�� 16kHz  
   PWMPER7 = PWMPE7;  //Ƶ�� 166kHz  
   
   PWMDTY01 = PWM01;      //ռ�ձ�50%
   PWMDTY23 = 312;      //ռ�ձ�50%
   PWMDTY45 = PWM45;      //
   PWMDTY6 = 39;      //ռ�ձ�50%
   PWMDTY7 = PWM7;      //ռ�ձ�50%
   PWME_PWME1 = 1;    //ͨ��1���,ǰ�ֶ��ʹ��  
   PWME_PWME3 = 1;    //ͨ��3���,�����תʹ��
   PWME_PWME5 = 1;    //ͨ��5���,��ͷ���ʹ��     
   PWME_PWME6 = 1;    //ͨ��6���,�����תʹ��
   PWME_PWME7 = 1;    //ͨ��7���,���ƹ�ʹ��    
} //PWMInit

   
//==============��ʱ����================================//
void delayms(int ms)    //��ʱ����
{   
   int ii,jj;
   if (ms<1) ms=1;
   for(ii=0;ii<ms;ii++)
     for(jj=0;jj<3338;jj++);    //40MHz--1ms      
}
void delayMS()
{
int jj;
     for(jj=0;jj<833;jj++);    //1/6ms     
}
//=====================�����ʼ��======================//
 void LIGHT_Init(void){ 
	DDRA = 0X7F;      //PA0--PA5������źŵ���
	DDRB = 0X00;      //PB0--PB3������źŽ���
 }


  void Light_Up(void) {
   for(light_count=0;light_count<=6;light_count++) 
   {
    if(light_count == 0)   
       { 
      PORTA = 0B00000001;
      delayMS();
	    light_temp_laser_array[6] = PORTB_PB4^1;
      light_temp_laser_array[13] = PORTB_PB2^1;
      light_temp_laser_array[20] = PORTB_PB0^1;
       }   
  
    else if(light_count == 1)   
       {
      PORTA = 0B00010000;
      delayMS();  
	    light_temp_laser_array[2] = PORTB_PB6^1;
      light_temp_laser_array[9] = PORTB_PB3^1;
      light_temp_laser_array[16] = PORTB_PB1^1;
      
     
       }
    
    else if(light_count ==2)   
       {
      PORTA = 0B00000010;
      delayMS();
	    light_temp_laser_array[5] = PORTB_PB5^1;	
      light_temp_laser_array[12] = PORTB_PB2^1;
      light_temp_laser_array[19] = PORTB_PB0^1; 
       
       
      
       } 
    
    else	if(light_count == 3)       
       {
      PORTA = 0B00100000;
      delayMS();  
	    light_temp_laser_array[1] = PORTB_PB6^1;
      light_temp_laser_array[8] = PORTB_PB4^1;
      light_temp_laser_array[15] = PORTB_PB1^1; 
        
      
	     }
   
   else if(light_count == 4)   
      {
      
      PORTA = 0B00000100;
      delayMS();
	    light_temp_laser_array[4] = PORTB_PB5^1;
      light_temp_laser_array[11] = PORTB_PB3^1;
      light_temp_laser_array[18] = PORTB_PB0^1; 
       
      } 
      
   else if(light_count == 5)   
      {
      PORTA = 0B01000000;
      delayMS();  
	    light_temp_laser_array[0] = PORTB_PB6^1;
      light_temp_laser_array[7] = PORTB_PB4^1;
      light_temp_laser_array[14] = PORTB_PB2^1; 
      }
   else if(light_count == 6)   
      {
      PORTA = 0B00001000;
      delayMS(); 
	    light_temp_laser_array[3] = PORTB_PB5^1;
      light_temp_laser_array[10] = PORTB_PB3^1;
      light_temp_laser_array[17] = PORTB_PB1^1;
      }   
 PORTA = 0B00000000;         //������ر�ͨ��
   }
light_count=0;   
} 