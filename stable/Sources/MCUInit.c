/* оƬ��ʼ������
*�� �� ��: 5th Smartcar v3.1_15Laser.mcp                                                                                   
*˵    ��:   

	  Written by: swe07024 ����ٻ           
    Date:       2010.7.19
    Update:     2010.7.19
*/

//��header file��
#include "MCUInit.h"


//��function definitions��
/* ================= PWMInit ====================
      desc: PWM��ʼ��
      pre:  ��
      Post: ��
       
*/ 
void PWMInit (void) {
  // Local Declarations

  // Statements
   PWME = 0X00;       //��ֹPWM���  
   PWMCAE = 0X00;     //�����
   
   PWMCNT01 = 0;			//������01����
   PWMCNT23 = 0;			//������23����
   PWMCNT45 = 0;			//������23����
 
   PWMPOL = 0XFF;     //������ߵ�ƽ
   PWMCTL = 0X70;     //ͨ��01.23.45����
   PWMPRCLK = 0X40;   //clockA����Ƶ,clockA=busclock=16MHz;CLK B 16��Ƶ:1Mhz 
   PWMSCLA = 8;       //��clock SA ����2*8=16��Ƶ��pwm clock=clockA/16=1MHz;
   PWMCLK_PCLK1 = 1;  //ѡ��clock SA��ʱ��Դ  
   
   PWMPER23 = 125;    //Ƶ�� 8kHz 
   PWMPER01 = 10000;  //Ƶ�� 100Hz 
   PWMPER45 = 125;    //Ƶ�� 8kHz 
   PWMDTY23 = 0;      //�ٶ�Ϊ0������ֹ
   PWMDTY45 = 0;      //�ٶ�Ϊ0������ֹ
   PWME_PWME1 = 1;    //ͨ��1��������ʹ��
   PWME_PWME3 = 1;    //ͨ��3���,�����תʹ�� 
   PWME_PWME5 = 1;    //ͨ��5���,�����תʹ��     
} //PWMInit


/* ================= PITInit ====================
      desc: PIT��ʼ���������ٶȲ�׽--��ʱ5ms,˫�ز�׽
      pre:  ��
      Post: ��
       
*/ 
void PITInit (void) {
    // Local Declarations

    // Statements
    PITCFLMT_PITE = 0; //��ʱ�ж�ͨ��0,1��
    
    PITCE_PCE0 = 1;    //��ʱ��ͨ��0ʹ��
    PITMUX_PMUX0 = 0;  //��ʱ0ͨ��0ʹ��΢������0 
    PITMTLD0 = 160-1;  //����΢������0�ļ��ؼĴ�����8λ��ʱ����ֵ�趨��160��Ƶ����16MHzBusClock�£�Ϊ0.1MHz����10us.
    PITLD0 = 142-1;    //16λ��ʱ����ֵ�趨��140  -->  1.4ms 
    PITINTE_PINTE0 = 1;//��ʱ���ж�ͨ��0�ж�ʹ��
    
    PITCE_PCE1 = 1;    //��ʱ��ͨ��1ʹ��
    PITMUX_PMUX1 = 0;  //��ʱ1ͨ��1ʹ��΢������0
    PITMTLD1 = 160-1;  //����΢������0�ļ��ؼĴ�����8λ��ʱ����ֵ�趨��160��Ƶ����16MHzBusClock�£�Ϊ0.1MHz����10us.
    PITLD1 = 2000-1;   //16λ��ʱ����ֵ�趨��2000  -->  20ms
    PITINTE_PINTE1 = 1;//��ʱ���ж�ͨ��1�ж�ʹ�� 
   
    PITCFLMT_PITE = 1; //��ʱ��ͨ��0,1ʹ��
} //PITInit


/* ================= PLLInit ====================
      desc: BUS CLOCK=16M
      pre:  ��
      Post: ��
       
*/ 
void PLLInit (void) {
    // Local Declarations

    // Statements
    CLKSEL=0X00;    //disengage PLL to system
    PLLCTL_PLLON=1;   //turn on PLL
    SYNR=1;          
    REFDV=1;          //pllclock=2*osc*(1+SYNR)/(1+REFDV)=32MHz;
    _asm(nop);          //BUS CLOCK=16M
    _asm(nop);
    while(!(CRGFLG_LOCK==1));   //when pll is steady ,then use it;
    CLKSEL_PLLSEL =1;          //engage PLL to system; 
   
} //PLLInit


/* ================= GIOInit ====================
      desc: ��ͨIO�ڳ�ʼ��
      pre:  ��
      Post: ��
       
*/ 
void GIOInit (void) {
  // Local Declarations

  // Statements
  DDRA = 0B00011111;  //PA0--PA4������źſ��� --- ��� ,PA5--PA7 --- ���룬���ղ��뿪��123
  DDRB |= 0X00;        //PB0--PB8������źŲɼ� --- ����
  DDR1AD0 |= 0X00;     //AN0--AN6������źŲɼ� --- ����
  ATD0DIENL = 0XFF;    //AD��������������
  ATD0DIENH = 0XFF;
  DDRT |= 0X00;        //PT0--PT3���뿪�� --- ����
  DDRE |= 0XF0;        //PE5,PE6�����������ɫLED��, PE3���룬���ղ��뿪��4    
} //GIOInit


/* ================= SCIInit ====================
      desc: SCI���ڳ�ʼ��
      pre:  ��
      Post: ��
       
*/ 
void SCIInit(void){
  byte tmp;     //����һ����ʱ����,�������Ĵ���
  SCI0BD = 104; //80m�� 40Mʱ��38400������   bus/16*bd   80MHZ 82
  SCI0CR1 = 0x00;   //8λ����λ,��У��
  SCI0CR2_RE = 1;   
  SCI0CR2_TE = 1;   //������+����
  SCI0CR2_RIE = 1;  //�����ж�
  SCI0CR2_TCIE = 0; //��ֹ��������ж�
  
  //���TDRE��־,���ȶ�SCI0SR1,Ȼ��дSCI0DRH
  tmp = SCI0SR1;
  SCI0DRH = 0x00;
  return;         //SCI0BDL=busclk/(16*SCI0BDL) 
                  //busclk 16MHz, 9600bps,SCI0BD=0x68                 
} //SCIInit               


/* ================= PACNTInit ====================
      desc: �ٶ�ģ�����������ʼ��
      pre:  ��
      Post: ��
       
*/ 
void PACNTInit (void) {
     PACTL = 0X50;  //PT7���벶׽
     PACNT = 0;         
} //PACNTInit               


/* ================= MCUInit ====================
      desc: оƬ�ܳ�ʼ��
      pre:  ��
      Post: ��
       
*/ 
void MCUInit (void) {
  // Local Declarations

  // Statements
  PLLInit ();  //ʱ��Ƶ��
  PWMInit ();  //PWM���
  PITInit ();  //��ʱ��  
  GIOInit ();  //��ͨIO��
  SCIInit ();  //����
  PACNTInit (); //����ģ��
} //MCUInit


