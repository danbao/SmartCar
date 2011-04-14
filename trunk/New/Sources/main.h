#define LASER_MAX 15          //���������
#define PWM67 224	
#define PWM01 1488
#define ANGLE_DELTA 30
#define PWM6_MID 224		
//===============ȫ�ֱ�������======================//
  float YP1=0.4,YP2=0.5,YP3=0.7,YP4=0.8,YP5=0.9,YD=2.7;
  float JP1=1.7,JP2=3.5,JP3=4.9,JP4=6.5,JP5=7.8,JD=2.3,SpeedAver,SpeedMax,SpeedMin,SpeedNow;/*ҡͷP1,ҡͷP2,ҡͷP3,ҡͷP4,ҡͷP5,ҡͷD,���P1,���P2,���P3,���P4,���P5,���P6,���D
  ƽ���ٶ�,����ٶ�,��С�ٶ�,��ǰ�ٶ�*/
  
  char SCIreceive[150];             /*�������ߴ�����ʾ���ַ���*/  
  int temp_pwm67=PWM67;						//�����ͷ�����ʼֵ
  int temp_pwm01=PWM01;						//ת���ͷ�����ʼֵ
  byte light_temp_laser_array[LASER_MAX];  //��ǰ�������Ϣ��������
  int testcount=1;
  int count=1;                                  //���ڽ�����ʱ
  int q_temp_laser_num[LASER_MAX];       //����ܶ�Ӧ��Ȩֵ
  int countPIT0=0;
  int position=0;                        
 // int His_ADD_Position[3];                      //�����ۼ�ֵ��ʷ   His_ADD_Position[2]=aabs[1]
  int His_Position[4];                        //��ʷposition  position[3]=position[1]-position[0] position[2]=aabs[position]
  int angle[2]; 
  int Calculate_HitBlackNum(void);
 // int YaoKp ,YaoKd,ZhuanKp,ZhuanKd;
  byte lost_line_flag=0;
  int ADD_Position; 
  int Diff_Position;
  int GDiff_Position[3];                      //ҡͷ����İ�ֵ(���ڲ������ڲ�ͬ �����ֵҪ������)  GDiff_Position[2]=aabs��GD��1����
  int D_His_Position[3];                      //���ȡ�ĵ�ǰ����ʷposition  ���Ͱ�ͷȡƵ�ʲ�ͬ�� 
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

//===============aabs=================================//
int aabs(int num) {
  if(num>=0)return num;
  else {
    num=-num;
    return num;
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
  
  PWMCTL = 0B00110000;     //ͨ��23����
  
	PWMCAE_CAE0=0;				//ת���ͷ������뷽ʽ
	PWMCAE_CAE1=0;	
	PWMCAE_CAE6=1;         		//�����ͷ���ֶ�����뷽ʽ
	PWMCAE_CAE7=1;
	
  PWMCNT01 = 0;				//01�ڼ��������㣻
  PWMCNT23 = 0;			//������23���� 
  
	PWMCTL=0x90;            	//���ƼĴ�����01��67�ڼ�����
	
	PWMPER23 = 1000;    //Ƶ�� 8kHz 
	PWMPER01=20000;				//1024��1024��Ƶ�ʣ�*Clock A/2/PWMSCLB/PWMPER67
	PWMPER67=1000;				//1024��1024��Ƶ�ʣ�*Clock B/2/PWMSCLB/PWMPER67
 
	PWMDTY01=PWM01;
	PWMDTY23 = 0;      //�ٶ�Ϊ0������ֹ
	PWMDTY67=PWM67;				//PWMDTY67/PWMPER67*100%
	PWME=0xff;         			//����ͨ��ʹ��?
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

