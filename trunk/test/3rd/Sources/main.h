#define LASER_MAX 12          //���������
char SCIreceive[100];
int count;
byte light_temp_laser_array[LASER_MAX];  //��ǰ�������Ϣ��������
#define PWM67 1531
#define PWM45 1478


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
//=====================�����ʼ��======================//
 void LIGHT_Init(void){ 
	DDRA = 0X3F;      //PA0--PA5������źŵ���
	DDRB = 0X00;      //PB0--PB3������źŽ���
 }
 
 //=====================�����ʼ��======================//
static void PWM_Init(void){     		//PWM��ʼ��������P4,P5���Ƶ������ת, P6,P7��������ܿ��ƶ����

	PWME=0X00;            		//��ʼ��������ͨ��ʹ�ܽ�ֹ��
	
	PWMCAE_CAE4=0;				//ת���ͷ������뷽ʽ
	PWMCAE_CAE5=0;	
	PWMCAE_CAE6=0;         		//�����ͷ���ֶ�����뷽ʽ
	PWMCAE_CAE7=0;
	
	PWMCNT45 = 0;				//45�ڼ���������
  PWMCNT67 = 0;				//45�ڼ��������㣻�
  
  PWMPOL_PPOL4=1;				//ת���ͷ�������ѡ������
	PWMPOL_PPOL5=1;
	PWMPOL_PPOL6=1;				//�����ͷ���ּ���ѡ������
	PWMPOL_PPOL7=1;
	
	PWMCTL=0B11000000;            	//���ƼĴ�����45��67�ڼ�����
  
  PWMPRCLK=0x11;				//Ԥ��Ƶ��A,Bʱ��Ϊ���ߵ�1/2������Clock A��Clock B��
	
	PWMCLK_PCLK4=1;	
	PWMCLK_PCLK5=1;
	PWMCLK_PCLK6=1;
	PWMCLK_PCLK7=1;

	PWMSCLA=10;            		//SAʱ������,Clock SA=Clock A/(2*PWMSCLA)��

	PWMSCLB=10;             	//SBʱ������,Clock SB=Clock B/(2*PWMSCLB)��

	PWMPOL_PPOL4=1;				//ת���ͷ�������ѡ������
	PWMPOL_PPOL5=1;
	PWMPOL_PPOL6=1;				//�����ͷ���ּ���ѡ������
	PWMPOL_PPOL7=1;
  
  //PWMCTL = 0B00100000;     //ͨ��23����
  

	
  
  //PWMCNT23 = 0;			//������23���� 
  

	
//	PWMPER23 = 125;    //Ƶ�� 8kHz 
	PWMPER45=20000;				//1024��1024��Ƶ�ʣ�*Clock A/2/PWMSCLB/PWMPER67
	PWMPER67=20000;				//1024��1024��Ƶ�ʣ�*Clock B/2/PWMSCLB/PWMPER67
 
	PWMDTY45=PWM45;
	//PWMDTY23 = 0;      //�ٶ�Ϊ0������ֹ
	PWMDTY67=PWM67;				//PWMDTY67/PWMPER67*100%
  PWME=0xff;  
}
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
     delayms(1); 
	    light_temp_laser_array[0] = PORTB_PB0;
        light_temp_laser_array[6] = PORTB_PB2;
    }   
  

   else if(send == 1)   { 
    PORTA = 0B00000010;
     delayms(1); 
	    light_temp_laser_array[1] = PORTB_PB0;
        light_temp_laser_array[7] = PORTB_PB2;
        
    }
    
    else if(send ==2)   { 
    PORTA = 0B00000100;
     delayms(1); 
	    light_temp_laser_array[2] = PORTB_PB0;
        light_temp_laser_array[8] = PORTB_PB2;
    } 
    else	if(send == 3)       { 
    PORTA = 0B00001000;
     delayms(1); 
	    light_temp_laser_array[3] = PORTB_PB1;	
        light_temp_laser_array[9] = PORTB_PB3;
  }
   else if(send == 4)   {
    PORTA = 0B00010000;
     delayms(1); 
	    light_temp_laser_array[4] = PORTB_PB1;
        light_temp_laser_array[10] = PORTB_PB3;
    } 
   else if(send == 5)   {
    PORTA = 0B00100000;
     delayms(1); 
	    light_temp_laser_array[5] = PORTB_PB1;
        light_temp_laser_array[11] = PORTB_PB3;
    }
   
} 

