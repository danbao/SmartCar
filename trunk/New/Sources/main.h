#define LASER_MAX 12          //���������
#define PWM67 1531
#define PWM45 1478
#define ANGLE_DELTA 30
#define PWM6_MID 224
#define Speed 50		
//===============ȫ�ֱ�������======================//
  float YP1=0.4,YP2=0.5,YP3=0.7,YP4=0.8,YP5=0.9,YD=2.7;
  float JP1=1.7,JP2=3.5,JP3=4.9,JP4=6.5,JP5=7.8,JD=2.3,SpeedAver,SpeedMax,SpeedMin,SpeedNow;/*ҡͷP1,ҡͷP2,ҡͷP3,ҡͷP4,ҡͷP5,ҡͷD,���P1,���P2,���P3,���P4,���P5,���P6,���D
  ƽ���ٶ�,����ٶ�,��С�ٶ�,��ǰ�ٶ�*/
  
  char SCIreceive[150];             /*�������ߴ�����ʾ���ַ���*/  
  int temp_pwm67=PWM67;						//�����ͷ�����ʼֵ
  int temp_PWM45=PWM45;						//ת���ͷ�����ʼֵ
  byte light_temp_laser_array[LASER_MAX];  //��ǰ�������Ϣ��������
  byte special_flag;
  byte start_flag,cross_flag;          //���� ʮ�ֱ�־

  int testcount=1;
  int count=1;                                  //���ڽ�����ʱ
  int q_temp_laser_num[LASER_MAX];       //����ܶ�Ӧ��Ȩֵ
  int countPIT0=0;
  int position=0; 
  int HitBlackNum; 
                   
 int JG_clear_position;
 int His_Position[4];                        //��ʷposition  position[3]=position[1]-position[0] position[2]=aabs[position]
 int angle[2]; 
 
 void calculate_light(void);
 void Status_Judge(void);
 // int YaoKp ,YaoKd,ZhuanKp,ZhuanKd;
 //byte lost_line_flag=0;
 // int ADD_Position; 
  int Diff_Position;
  int GDiff_Position[3];                      //ҡͷ����İ�ֵ(���ڲ������ڲ�ͬ �����ֵҪ������)  GDiff_Position[2]=aabs��GD��1����
  int J_His_Position[3];                       //��ǻ�ȡposition �������ڲ�ͬ
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
     for(jj=0;jj<667;jj++);    //1/6ms     
}

//===============aabs=================================//
int aabs(int num) {
  if(num>=0)return num;
  else {
    num=-num;
    return num;
  }
}

 //=====================PWM��ʼ��======================//
static void PWM_Init(void){     		//PWM��ʼ��������P4,P5���Ƶ������ת, P6,P7��������ܿ��ƶ����

	PWME=0X00;            		//��ʼ��������ͨ��ʹ�ܽ�ֹ��

	PWMSCLA=10;            		//SAʱ������,Clock SA=Clock A/(2*PWMSCLA)��

	PWMSCLB=10;             	//SBʱ������,Clock SB=Clock B/(2*PWMSCLB)��
	
  PWMCAE_CAE1=0;         // ���뷽ʽ
//  PWMCAE_CAE3=0;
	PWMCAE_CAE4=0;				//ת���ͷ������뷽ʽ
	PWMCAE_CAE5=0;	
	PWMCAE_CAE6=0;         		//�����ͷ���ֶ�����뷽ʽ
	PWMCAE_CAE7=0;
	
	PWMCNT45 = 0;				//45�ڼ���������
  PWMCNT67 = 0;       //45�ڼ���������
  				
  PWMPOL_PPOL1=1;        //����ѡ�����á�
  //PWMPOL_PPOL3=1;
  PWMPOL_PPOL4=1;				//ת���ͷ�������ѡ������
	PWMPOL_PPOL5=1;
	PWMPOL_PPOL6=1;				//�����ͷ���ּ���ѡ������
	PWMPOL_PPOL7=1;
	
	PWMCTL=0B11110000;            	//���ƼĴ�����45��67�ڼ�����ͨ��23����
  
  PWMPRCLK=0x11;				//Ԥ��Ƶ��A,Bʱ��Ϊ���ߵ�1/2������Clock A��Clock B��
	PWMCLK_PCLK1=0;         // ʱ��Դѡ��
  PWMCLK_PCLK3=0;
	PWMCLK_PCLK4=1;	
	PWMCLK_PCLK5=1;
	PWMCLK_PCLK6=1;
	PWMCLK_PCLK7=1;
  

	
  PWMPER01 = 100;    //Ƶ�� 8kHz 
	PWMPER45=10000;				//1024��1024��Ƶ�ʣ�*Clock A/2/PWMSCLB/PWMPER67
	PWMPER67=10000;				//1024��1024��Ƶ�ʣ�*Clock B/2/PWMSCLB/PWMPER67
 
	PWMDTY45=PWM45;
	PWMDTY01 = 0;      //�ٶ�Ϊ0������ֹ
	PWMDTY67=PWM67;				//PWMDTY67/PWMPER67*100%
  PWME=0xf3;  
}
//=====================�����ʼ��======================//
 void LIGHT_Init(void){ 
	DDRA = 0X3F;      //PA0--PA5������źŵ���
	DDRB = 0Xf0;      //PB0--PB3������źŽ���
 }


//=====================�������======================//
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
   
} 

