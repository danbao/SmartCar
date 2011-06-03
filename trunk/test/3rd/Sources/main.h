#define LASER_MAX 12          //���������
char SCIreceive[100];
int count;
byte light_temp_laser_array[LASER_MAX];  //��ǰ�������Ϣ��������
#define PWM67 3666
#define PWM45 3666


  int temp_pwm67=PWM67;						//�����ͷ�����ʼֵ
  int temp_pwm45=PWM45;	
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
	DDRA = 0X3F;      //PA0--PA5������źŵ���
	DDRB = 0X00;      //PB0--PB3������źŽ���
 }
 
 void PWM_Init (void) {   //0519��ʱд�꣡
  // Local Declarations

  // Statements
   PWME = 0X00;       //��ֹPWM���  
   PWMCAE = 0X00;     //�����
   
   PWMCNT01 = 0;			//������01����
   PWMCNT23 = 0;			//������23����
   PWMCNT45 = 0;			//������45����
   PWMCNT67 = 0;			//������67����
 
   PWMPOL = 0XFF;     //������ߵ�ƽ   PWM���ԼĴ���
   PWMCTL = 0XF0;     //ͨ��01.23.45.67����  0B11111111   01��ת 23��ת
   PWMPRCLK = 0X21;   //clockA 2��Ƶ,clockA=busclock/2=20MHz;CLK B 4��Ƶ:10Mhz 
   PWMSCLA = 4;       //��clock SA ����2*4=8��Ƶ��pwm clock=clockA/8=2.5MHz;
   PWMSCLB = 4;       //��clock SB ����2*4=8��Ƶ��pwm clock=clockB/8=1.25MHz;
   PWMCLK_PCLK1 = 1;  //ѡ��clock SA��ʱ��Դ  01
   PWMCLK_PCLK3 = 1;  //ѡ��clock SB��ʱ��Դ  23
   PWMCLK_PCLK5 = 1;  //ѡ��clock SA��ʱ��Դ  45
   PWMCLK_PCLK7 = 1;  //ѡ��clock SB��ʱ��Դ  67	   

   PWMPER01 = 250;    //Ƶ�� 10kHz  ����0.1ms
   PWMPER23 = 125;    //Ƶ�� 10kHz  ����0.1ms
   PWMPER45 = 25000;  //Ƶ�� 100Hz  ����50ms
   PWMPER67 = 12500;  //Ƶ�� 100Hz  ����50ms
   
   PWMDTY01 = 25;      //ռ�ձ�10%
   PWMDTY23 = 62;      //ռ�ձ�50%
   PWMDTY45 = 3666;      //��ֵ
   PWMDTY67 = 3666;      //��ֵ
   PWME_PWME1 = 1;    //ͨ��1���,�����תʹ��   ��ת
   PWME_PWME3 = 1;    //ͨ��3���,�����תʹ�� 
   PWME_PWME5 = 1;    //ͨ��5���,ǰ�ֶ��ʹ��     
   PWME_PWME7 = 1;    //ͨ��7���,��ͷ���ʹ��     
} //PWMInit

//=====================�����ͷ����ı亯��======================//
void Light_SetDriver(int value){
  PWMDTY67 = value; 
}
void SCI_SetDriver(int value){
  PWMDTY45 = value; 
}



 void receive(int send) {
   if(send == 0)   { 
    PORTA = 0B00000001;
     delayMS(); 
	    light_temp_laser_array[0] = PORTB_PB0^1;
      light_temp_laser_array[6] = PORTB_PB2^1;
    }   
  

   else if(send == 1)   { 
      PORTA = 0B00001000;
     delayMS();  
	    light_temp_laser_array[3] = PORTB_PB1^1;	
        light_temp_laser_array[9] = PORTB_PB3^1;
	    
       
        
    }
    
    else if(send ==2)   { 
     PORTA = 0B00000010;
     delayMS();  
	    light_temp_laser_array[1] = PORTB_PB0^1;
        light_temp_laser_array[7] = PORTB_PB2^1;
	   
    
    } 
    else	if(send == 3)       { 
   PORTA = 0B00010000;
     delayMS(); 
	    light_temp_laser_array[4] = PORTB_PB1^1;
        light_temp_laser_array[10] = PORTB_PB3^1;
	 
     
    
   
    
  }
   else if(send == 4)   {
        PORTA = 0B00000100;
     delayMS();  
	    light_temp_laser_array[2] = PORTB_PB0^1;
        light_temp_laser_array[8] = PORTB_PB2^1;
   
  
	   
    
    } 
   else if(send == 5)   {
     PORTA = 0B00100000;
     delayMS();  
	   light_temp_laser_array[5] = PORTB_PB1^1;
     light_temp_laser_array[11] = PORTB_PB3^1;
	 
    }
    PORTA = 0B00000000;
} 