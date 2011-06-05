#define LASER_MAX 12          //���������
#define IR_NUM 7              //���������
#define PWM67 1881
#define PWM45 3666
#define ANGLE_DELTA 30
#define PWM6_MID 224
#define Speed 50
#define N 5                  //�����˲�Ȩֵ		
//===============ȫ�ֱ�������======================//
  float YP1=0.4,YP2=0.5,YP3=0.7,YP4=0.8,YP5=0.9,YD=2.7;
  float JP1=1.7,JP2=3.5,JP3=4.9,JP4=6.5,JP5=7.8,JD=2.3,SpeedAver,SpeedMax,SpeedMin,SpeedNow;/*ҡͷP1,ҡͷP2,ҡͷP3,ҡͷP4,ҡͷP5,ҡͷD,���P1,���P2,���P3,���P4,���P5,���P6,���D
  ƽ���ٶ�,����ٶ�,��С�ٶ�,��ǰ�ٶ�*/
 
  char SCIreceive[150];             /*�������ߴ�����ʾ���ַ���*/  
  int temp_pwm67=PWM67;						//�����ͷ�����ʼֵ
  int temp_pwm45=PWM45;						//ת���ͷ�����ʼֵ
  
  byte light_temp_laser_array[LASER_MAX];  //��ǰ�������Ϣ��������
  uint IR_temp_laser_array[7];             //��ǰ������Ϣ��������
  
  byte special_flag;
  byte start_flag,cross_flag;          //���� ʮ�ֱ�־
  
  int error;
  
  double temp_speed;
  int delay_count=1;                             //��ͨ��ʱ����
  int send_count=1;                              //���ڽ�����ʱ����
  int q_temp_laser_num[LASER_MAX];       //����ܶ�Ӧ��Ȩֵ
  int countPIT0=0;
  int position=0; 
  int HitBlackNum; 
  
  byte SS_flag;                          //Сs���  1��Ч
  byte LS_flag;                         //��S���   1��Ч
  byte Straight_flag;                   //ֱ�����  ��0��Ч
  byte turn_flag;                       //������  ��0��Ч                 

 int standard_position_array[22]={1539,1523,1547,1515,1551,1511,1556,1506,1566,1496,1574,1488,1581,1481,1585,1477,1591,1471,1598,1464,1611,1451}; 
  //��׼position��ֵ
  int temp_position_array[22];
  //���ڼ�¼position��ֵ���γ�Ԥ�е����� 
//int last_laser_array[20][11];    
//�����ά������Ϊ����ܵ���ʷ��¼
 
  int IR_position[2];                 //����λ��   ���ⲿ�ֱ�������IR��ͷ
  int IR_blacknun=0;                  //����ڵ�
  void Level_IR( void);               //����  ����ȥ���ɲ�����
  long IR_clear[2];                   //�����˲�ֵ
  
  int  JG_delay=1;
  long JG_clear[2];                      //����һ�ε����˲� �˴κ��ϴ�
  long JG_clear_Pos[2];                  //���뵱ǰ����һ�ΰ�ͷʱ��JG_clear ��ֵ
                             
 void calculate_light(void);
 void Status_Judge(void);
 // int YaoKp ,YaoKd,ZhuanKp,ZhuanKd;
 //byte lost_line_flag=0;
 // int ADD_Position; 
  
  int Diff_Position;
  int GDiff_Position[3];                      //ҡͷ����İ�ֵ(���ڲ������ڲ�ͬ �����ֵҪ������)  GDiff_Position[2]=aabs��GD��1����
  int J_His_Position[3];                       //��ǻ�ȡposition �������ڲ�ͬ
  
  int g_countPIT0 =0;   //����PIT���ĵ�������
	int	g_temp_laser_array[11]; //���ڽ��ܸ�������ܵ������ȡ������
	int g_temp_pulse;
	
	int temp_laser_array[11];
	
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

//===============aabs=================================//
long aabs(long num) {
  if(num>=0)return num;
  else {
    num=-num;
    return num;
  }
}

 //=====================PWM��ʼ��======================//
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
   PWMDTY45 = 3666;      //
   PWMDTY67 = 1881;      //ռ�ձ�50%
   PWME_PWME1 = 1;    //ͨ��1���,�����תʹ��   ��ת
   PWME_PWME3 = 1;    //ͨ��3���,�����תʹ�� 
   PWME_PWME5 = 1;    //ͨ��5���,ǰ�ֶ��ʹ��     
   PWME_PWME7 = 1;    //ͨ��7���,��ͷ���ʹ��     
} //PWMInit

//=====================ECT��׽���ٳ�ʼ��======================//
 void Tect_Speed_Init()
 { 
   TSCR1=0x80;          //ʹ�ܶ�ʱ��
   PACTL=0X50;  //PT7���벶׽  
   PACNT=0;
 }


//=====================�����ʼ��======================//
 void LIGHT_Init(void){ 
	DDRA = 0X3F;      //PA0--PA5������źŵ���
	DDRB = 0Xf0;      //PB0--PB3������źŽ���
 }



//=====================PIT��ʼ��======================//
 void PITInit (void) {
//���㹫ʽ��time-out period = (PITMTLD + 1) * (PITLD + 1) / fBUS.
//BUSΪ���ߣ�����

    // Local Declarations

    // Statements
    PITCFLMT_PITE = 0; //��ʱ�ж�ͨ��0,1��
    
	//PIT0��Ҫ����ܵĵ���
    PITCE_PCE0 = 1;    //��ʱ��ͨ��0ʹ��
    PITMUX_PMUX0 = 0;  //��ʱ0ͨ��0ʹ��΢������0 
    PITMTLD0 = 160-1;  //����΢������0�ļ��ؼĴ�����8λ��ʱ����ֵ�趨��160��Ƶ����16MHzBusClock�£�Ϊ0.1MHz����10us.
    PITLD0 = 142-1;    //16λ��ʱ����ֵ�趨��140  -->  1.4ms 
    PITINTE_PINTE0 = 1;//��ʱ���ж�ͨ��0�ж�ʹ��
    
	//PIT0��Ҫ���٣����õ���������ֵ�����ECT����
    PITCE_PCE1 = 1;    //��ʱ��ͨ��1ʹ��
    PITMUX_PMUX1 = 0;  //��ʱ1ͨ��1ʹ��΢������0
    PITMTLD1 = 160-1;  //����΢������0�ļ��ؼĴ�����8λ��ʱ����ֵ�趨��160��Ƶ����16MHzBusClock�£�Ϊ0.1MHz����10us.
    PITLD1 = 1000-1;   //16λ��ʱ����ֵ�趨��1000  -->  10ms
    PITINTE_PINTE1 = 1;//��ʱ���ж�ͨ��1�ж�ʹ�� 
   
    PITCFLMT_PITE = 1; //��ʱ��ͨ��0,1ʹ��
} //PITInit


/*=====================�������======================
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
*/