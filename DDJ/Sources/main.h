#define LASER_MAX 21          //���������
#define IR_NUM 7              //���������
//#define PWM67 1845
//#define PWM45 3528
#define ANGLE_DELTA 30
#define PWM6_MID 224
#define PWM01 1972
#define PWM23 500
#define PWM45 1603
#define PWM7 30
#define PWMPE7 60
//#define Speed 50
#define N 5                  //�����˲�Ȩֵ		
/*===============ȫ�ֱ�������======================
ȫ�ֱ������ 
*/
 // float YP1=0.4,YP2=0.5,YP3=0.7,YP4=0.8,YP5=0.9,YD=2.7;
 // float JP1=1.7,JP2=3.5,JP3=4.9,JP4=6.5,JP5=7.8,JD=2.3,SpeedAver,SpeedMax,SpeedMin,SpeedNow;/*ҡͷP1,ҡͷP2,ҡͷP3,ҡͷP4,ҡͷP5,ҡͷD,���P1,���P2,���P3,���P4,���P5,���P6,���D
 // ƽ���ٶ�,����ٶ�,��С�ٶ�,��ǰ�ٶ�*/
  int DP1=1,DP2=1,DP3=1,DP4=1,DP5=1,DP6=1,DP7=1;
  //int DD=0;
  byte baitou_begin;     //����ͷ��������ʱ �ж����ֱ��  
  
  byte get_flag;
  int side;
  byte side_baipwm;  
 
   byte B1P1=30,B1P2=25,B1P3=21,B1P4=19,B1P5=17,B1P6=16,B1P7=15,B1P8=14,B1P9=13,B1P10=12,B1P11=12,B1P12=13,B1P13=11,B1P14=11;
   byte B2P1=3,B2P2=3,B2P3=2,B2P4=2,B2P5=1,B2P6=1,B2P7=8,B2P8=7,B2P9=7,B2P10=6,B2P11=6,B2P12=6,B2P13=6,B2P14=5;
 // byte B3P1=30,B3P2=20,B3P3=14,B3P4=12,B3P5=11,B3P6=10,B3P7=9,B3P8=8,B3P9=7,B3P10=6;
 // byte B4P1=30,B4P2=20,B4P3=14,B4P4=11,B4P5=10,B4P6=9,B4P7=8,B4P8=7,B4P9=6,B4P10=5;
 // byte B5P1=30,B5P2=20,B5P3=14,B5P4=10,B5P5=9,B5P6=8,B5P7=7,B5P8=6,B5P9=5,B5P10=4;
//  byte B6P1=30,B6P2=20,B6P3=14,B6P4=9,B6P5=8,B6P6=7,B6P7=6,B6P8=5,B6P9=4,B6P10=3;
 // byte B7P1=30,B7P2=20,B7P3=14,B7P4=8,B7P5=7,B7P6=6,B7P7=4,B7P8=3,B7P9=2,B7P10=1;
  
  int BD1=250,BD2=220,BD3=150,BD4=50,BD5=35,BD6=25,BD7=25,BD8=25,BD9=24,BD10=22;
  char SCIreceive[150];                    /*�������ߴ�����ʾ���ַ���*/  
//int temp_pwm45=PWM45;						         //�����ͷ�����ʼֵ
  int temp_pwm01=PWM01;					         	 //ת���ͷ�����ʼֵ
  int temp_pwm23=PWM23;					         	 //�ٶȳ�ʼֵ  */
  
  byte light_temp_laser_array[LASER_MAX];  //��ǰ�������Ϣ��������
  int  light_count;                        //��������ӳ�
  
  byte maybe_slope_flag=0;                //���� ���ܻ���ʮ�� Ҳ�п������µ�
  byte maybe_special_flag=0;                 //�������ܵ�����  Ϊ�µ�
  byte start_flag=0,cross_flag=0;             //���� ʮ�ֱ�־
  byte slope_flag=0;                         //�µ� ��ʶ 
  byte slope_count=0;                         //�µ���ʮ��ʱ�տռ���
  byte maybe_count=0;                         //�����µ���ʮ�ֵĳ������м���
 
  byte error[LASER_MAX];
  //int error;
  
  
  double temp_speed;
  int delay_count=1;                      //��ͨ��ʱ����
  int send_count=1;                       //���ڽ�����ʱ����
  int q_temp_laser_num[LASER_MAX];        //����ܶ�Ӧ��Ȩֵ
  int countPIT0=0;
  int position;                     //λ�� 
  
  //����
  byte IR_temp_laser_array[7];             //��ǰ������Ϣ��������
  byte q_temp_ir_num[7];
  int 	IR_position=0; 
  int   His_IR_pos=0;
  
  byte nothing_flag=0 ;
  byte right,left,middle;                    //��������ֵ
  
  int HitBlackNum;
  int His_HitBlackNum;
  
  int baitou_diff[2]; 
  
 // byte SS_flag;                           //Сs���  1��Ч
 // byte LS_flag;                           //��S���   1��Ч
  byte Straight_flag=1;                     //ֱ�����  ��0��Ч
  byte turn_flag=0;                         //������  ��0��Ч                 
  byte Straight_stop;                      //ֱ������ķ�ת
  byte turn_stop;                          //�����ֱ�ķ�ת
  byte first_flag=1;
  
  //int quanyi=0;
  
  byte YDdelay=1;
  //byte diansha_falg=0;                     //��ɲ��־
  //byte diansha_count;                      //��ɲ����
  //byte diansha_num;                        //��ɲʱ�� ��������ʱ���ٶ� �����е�ɲʱ��
 // int road_point[6];                      //5���Ϊһ��  ����2.5m/s 5��Ϊ1.8cm  road_point[5]Ϊ����ֵ
 // int point_count;                        //5����� ͬʱҲ����Ϊ���жϿ�ʼ�ı�־
 // int road_section[20];                   //8�ι�Ϊһ��·  ͬ����8��Ϊ15cm
 // int section_flag;                      //8�μ���
  
  int  befo_General_pos;                  //������ۺ�ƫ��
  float General_pos;                     //ģ��
  int change_JG_DJ_array[41]={141,131,119,115,109,103,96,89,83,78,71,66,56,53,46,41,35,30,18,6,0,-6,-18,-30,-35,-41,-46,-53,-56,-66,-71,-78,-83,-89,-96,-103,-109,-115,-119,-131,-141}; 
  int cha_pos=0;
  //int coordinate
 //int standard_position_array[23]=
  //��׼position��ֵ
 // int temp_position_array[22];
  //���ڼ�¼position��ֵ���γ�Ԥ�е����� 
//int last_laser_array[20][11];    
//�����ά������Ϊ����ܵ���ʷ��¼
  int baitoupwm;
  
   float Subu=0.9;
   
  
  //int dajiao_Slope[3];                   //��Ƕ��������б�� 2Ϊ�ۼ�ֵ
  
  int baitou_delay=1;                    //��ͷ�ӳ�  ͬʱ�����ȷְ�ͷ��ÿ�ζ��ֵ
  int JG_clear[2];                      //����һ�ε����˲� �˴κ��ϴ�
  int JG_clear_Pos[2];                  //���뵱ǰ����һ�ΰ�ͷʱ��JG_clear ��ֵ
                             
 
  byte speed_begian;                       //��ʼ�ٶȲ��ԣ��ȴ����岶׽��ɣ�
  long speed_clear[2];                    //�ٶ��˲�ֵ  ���ս�� �˴κ��ϴ�
  float Kp=20;                      //��������
  float Ki=0.1;                      //���ֳ���
  float Kd=0;                      //΢�ֳ���
  int error0=0;                      //��ǰ��ΪĿ���ٶȼ�ȥ��ǰ��ȡ������ֵ
  int error1=0;                      //ǰһ�����
  int error2=0;                      //ǰǰһ�ε����
  byte daozhuan_flag;                //��ת��־ ������
  int ZhiSpeed=1500;
  int WanSpeed=180;
  //int speed[20];                          //��
  
  void calculate_light(void);
  void Status_Judge(void);
  
 // int g_countPIT0 =0;   //����PIT���ĵ�������
//	int	g_temp_laser_array[LASER_MAX]; //���ڽ��ܸ�������ܵ������ȡ������
	
	
//	int temp_laser_array[LASER_MAX];

/*===============ʱ�ӳ�ʼ��========================*/
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
     for(jj=0;jj<3338;jj++)
     ;    //40MHz--1ms      
}

void delayMS()
{
    int jj;
    for(jj=0;jj<833;jj++)
    ;    //1/4ms     
}

//===============aabs=================================//
long aabs(long num) 
{
  if(num>=0)
    return num;
  else 
  {
    num=-num;
    return num;
  }
}

//=====================PWM��ʼ��======================//
void PWM_Init (void) 
{   //0519��ʱд�꣡
  // Local Declarations

  // Statements
   PWME = 0X00;       //��ֹPWM���  
   PWMCAE = 0X00;     //�����
   
   //PWMCNT01 = 0; //������01����
   //PWMCNT23 = 0; //������23����
   //PWMCNT01 = 0; //������01����
   //PWMCNT67 = 0; //������67����
 
   PWMPOL = 0XFF;     //������ߵ�ƽ   PWM���ԼĴ���
   PWMCTL = 0X70;     //ͨ��01������23������45����
   PWMPRCLK = 0X11;   //clockA 2��Ƶ,clockA=busclock/2=20MHz;CLK B 2��Ƶ:20Mhz 
   PWMSCLA = 8;       //��clock SA ����2*8=16��Ƶ��pwm clock=clockA/16=1.25MHz;
   PWMSCLB = 4;       //��clock SB ����2*4=8��Ƶ��pwm clock=clockB/8=2.5MHz;
   PWMCLK_PCLK1 = 1;  //ѡ��clock SA��ʱ��Դ  
   PWMCLK_PCLK3 = 0;  //ѡ��clock B��ʱ��Դ  
   PWMCLK_PCLK5 = 1;  //ѡ��clock SA��ʱ��Դ  
   PWMCLK_PCLK6 = 1;  //ѡ��clock SB ��ʱ��Դ
   PWMCLK_PCLK7 = 0;  //ѡ��clock B ��ʱ��Դ      

   PWMPER01 = 25000;    //Ƶ�� 50Hz  ����20ms
   PWMPER23 = 1667;    //Ƶ�� 12kHz    ����6.25us
   PWMPER45 = 12500;  //Ƶ�� 100Hz    ����10ms
   PWMPER6 = 208;  //Ƶ�� 12kHz        ����6.25us
   PWMPER7 = PWMPE7;  //Ƶ�� 166kHz   ����602ns
   
   PWMDTY01 = PWM01;      //ռ�ձ�50%  ǰ�ֶ��
   PWMDTY23 = PWM23;      //ռ�ձ�50%  �����ת
   PWMDTY45 = PWM45;      //           ��ͷ���
   PWMDTY6 = 18;      //ռ�ձ�50%      �����ת18
   PWMDTY7 = PWM7;      //ռ�ձ�50%    ���ƹ�
   PWME_PWME1 = 1;    //ͨ��1���,ǰ�ֶ��ʹ��  
   PWME_PWME3 = 1;    //ͨ��3���,�����תʹ��
   PWME_PWME5 = 1;    //ͨ��5���,��ͷ���ʹ��     
   PWME_PWME6 = 1;    //ͨ��6���,�����תʹ��
   PWME_PWME7 = 1;    //ͨ��7���,���ƹ�ʹ��    
} //PWMInit

//=====================ECT��׽���ٳ�ʼ��======================//
 void Tect_Speed_Init()
 { 
   TSCR1=0x80;          //ʹ�ܶ�ʱ��
   PACTL=0X50;  //PT7���벶׽  
   PACNT=0;
 }

//=====================�����ʼ��======================//
 void LIGHT_Init(void)
 { 
   DDRA = 0X7F;      //PA0--PA5������źŵ���
   DDRB = 0X80;      //PB0--PB3������źŽ���
 }

/*=====================PIT��ʼ��======================*/
 void PITInit (void) 
 {
//���㹫ʽ��time-out period = (PITMTLD + 1) * (PITLD + 1) / fBUS.
//BUSΪ���ߣ�����

    // Local Declarations

    // Statements
    PITCFLMT_PITE = 0;       //PITͨ��ʹ��λ      
    PITCE_PCE0 = 1;          //��ʱ��ͨ��0ʹ��    
    PITMUX_PMUX0 = 0;       //��ʱͨ��0ʹ��΢������0     
    PITMTLD0 =200-1;  //����΢������0�ļ��ؼĴ�����8λ��ʱ����ֵ�趨��200��Ƶ����40MHzBusClock�£�Ϊ0.2MHz����5us.    
    PITLD0 = 340-1;    //16λ��ʱ����ֵ�趨��4000 -->  20ms   1500-->7.5ms  
    PITINTE_PINTE0 = 1;//��ʱ���ж�ͨ��0�ж�ʹ��            
     PITCFLMT_PITE = 1;       //PITͨ��ʹ��λ

   /* PITCE_PCE1 = 1;          //��ʱ��ͨ��0ʹ��    
    PITMUX_PMUX1 = 1;       //��ʱͨ��0ʹ��΢������0     
    PITMTLD1 =200-1;  //����΢������0�ļ��ؼĴ�����8λ��ʱ����ֵ�趨��200��Ƶ����40MHzBusClock�£�Ϊ0.2MHz����5us.    
    PITLD1 = 1700-1;    //16λ��ʱ����ֵ�趨��4000 -->  20ms   1500-->7.5ms    1700-->8.5
    PITINTE_PINTE1 = 1;//��ʱ���ж�ͨ��0�ж�ʹ��            
    PITCFLMT_PITE = 1;       //PITͨ��ʹ��λ       */
} //PITInit


/*=====================�������======================
����������ö�ʱ�жϻ��ǡ������Ծͻ������������е���
*/
void Light_Up(void) 
{
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