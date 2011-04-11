/**************************************************************************************
龙丘MC9S12X多功能开发板V1.0  
Designed by 龙丘
E-mail:chiusir@163.com      
软件版本:V1.1
最后更新:2009年2月21日           
相关信息参考下列地址：
博客：  http://longqiu.21ic.org
淘宝店：http://shop36265907.taobao.com
------------------------------------
Code Warrior 4.7
Target : MC9S12XS128
Crystal: 16.000Mhz
busclock:16.000MHz
pllclock:32.000MHz  
============================================
演示程序使用说明：
1.串口9600bps，中断显示
2.PWM波形测试，测试方法：
  按u:增加频率
  按d:降低频率
  按l:减小占空比
  按r:增加占空比
  按o:开启声音
  按c:关闭声音  
 *****************************************************************************************/
#include <hidef.h>           /* common defines and macros */
#include <MC9S12XS128.h>
#include <stdio.h> 

#pragma LINK_INFO DERIVATIVE "mc9s12xs128" 

byte u8_RCV_Ch=0xff;
//====================中断函数================================== 



#pragma CODE_SEG DEFAULT
void Dly_ms(int ms)	
{
	 int ii,jj;
   if (ms<1) ms=1;
   for(ii=0;ii<ms;ii++)
     for(jj=0;jj<2770;jj++);    //32MHz--1ms  
} 
//-----------------------------------------------------
static void SCI_Init(void) 
{
    SCI0CR2=0x2c; //enable Receive Full Interrupt,RX enable,Tx enable
    SCI0BDH=0x00; //busclk  8MHz,19200bps,SCI0BDL=0x1a
    SCI0BDL=0x68; //SCI0BDL=busclk/(16*SCI0BDL)                   
                  //busclk 16MHz, 9600bps,SCI0BDL=0x68                   
}            
void uart_putchar(unsigned char ch)
{ 
  if (ch == '\n')  
  {
      while(!(SCI0SR1&0x80)) ;     
      SCI0DRL= 0x0d;       				 //output'CR'
	    return;
  }
  while(!(SCI0SR1&0x80)) ; 		    //keep waiting when not empty  
  SCI0DRL=ch;
}

void putstr(char ch[])
{
  unsigned char ptr=0;
  while(ch[ptr]){
      uart_putchar((unsigned char)ch[ptr++]);
  } 
}
unsigned char uart_getkey(void)
{  
   byte res=0;
   while(!(SCI0SR1&0x80)) ; 		 //keep waiting when not empty  
   return (SCI0DRL);
}
//----------------------------------------------------- 
static void Port_Init(void)
{   
    DDRB = 0xff;  //LED  PTB0--7,
    PORTB= 0xff;  //LEDs on  
}
// PLL初始化子程序   BUS Clock=16M
void setbusclock(void)
{   
    CLKSEL=0X00;				// disengage PLL to system
    PLLCTL_PLLON=1;			// turn on PLL
    SYNR=0x00 | 0x01; 	// VCOFRQ[7:6];SYNDIV[5:0]
                        // fVCO= 2*fOSC*(SYNDIV + 1)/(REFDIV + 1)
                        // fPLL= fVCO/(2 × POSTDIV) 
                        // fBUS= fPLL/2 
                        // VCOCLK Frequency Ranges  VCOFRQ[7:6]
                        // 32MHz <= fVCO <= 48MHz    00
                        // 48MHz <  fVCO <= 80MHz    01
                        // Reserved                  10
                        // 80MHz <  fVCO <= 120MHz   11				
    REFDV=0x80 | 0x01;  // REFFRQ[7:6];REFDIV[5:0]
                        // fREF=fOSC/(REFDIV + 1)
                        // REFCLK Frequency Ranges  REFFRQ[7:6]
                        // 1MHz <= fREF <=  2MHz       00
                        // 2MHz <  fREF <=  6MHz       01
                        // 6MHz <  fREF <= 12MHz       10
                        // fREF >  12MHz               11                         
                        // pllclock=2*osc*(1+SYNR)/(1+REFDV)=32MHz;
    POSTDIV=0x00;       // 4:0, fPLL= fVCO/(2xPOSTDIV)
                        // If POSTDIV = $00 then fPLL is identical to fVCO (divide by one).
    _asm(nop);          // BUS CLOCK=16M
    _asm(nop);
    while(!(CRGFLG_LOCK==1));	  //when pll is steady ,then use it;
    CLKSEL_PLLSEL =1;		        //engage PLL to system; 
}
//----------------------------------------------------- 
static void PWM_Init(void)
{     
    //SB,B for ch2367
    //SA,A for ch0145  
    PWMPRCLK = 0X55;    //clockA,CLK B 32分频:500khz   
    PWMSCLA = 0x02;     //对clock SA 进行2*PWMSCLA=4分频；pwm clock=clockA/4=125KHz;     
    PWMSCLB = 0X02;     //clk SB=clk B/(2*pwmsclb)=125KHZ

  //pwm1  
    PWMCNT1 = 0;
    PWMCAE_CAE1=0;      
    PWMPOL_PPOL1=0;                      
    PWMPER1 =125;        
    PWMDTY1 =100;        
    PWMCLK_PCLK1 = 1;                 
    PWME_PWME1 = 0; 
} 
//-----------------------------------------------------

void Init_Dev(void)
{
    setbusclock();
    Port_Init();
    SCI_Init();
    PWM_Init();   
}
//----------------------------------------------------- 
void Beep(void)
{   
  word tmper=125,tmdty=100;
  tmper=PWMPER1;
  tmdty=PWMDTY1;
  PWME_PWME1 = 1;
  PWMPER1 =125;         
  PWMDTY1 =100;   
  Dly_ms(40);
  PWMPER1 =tmper;         
  PWMDTY1 =tmdty;
  PWME_PWME1 = 0;  
} 

#pragma CODE_SEG __NEAR_SEG NON_BANKED 
void interrupt 20 SCI0_ISR(void)
{     
  SCI0CR2_RIE=0;
  //此处为串口中断需要处理的事情
  uart_putchar(u8_RCV_Ch=uart_getkey());
  //PORTA_PA0=~PORTA_PA0;
  PORTB_PB7=~PORTB_PB7; 
  switch(u8_RCV_Ch)
    { 
      case 'u':
        u8_RCV_Ch=0xff;
        PWME_PWME1 = 1;           //开启PWM0波形输出   
        if(PWMPER1>15)            //增大频率
            PWMPER1-=5; 
      break; 
      case 'd':
        u8_RCV_Ch=0xff; 
        PWME_PWME1 = 1;
        if(PWMPER1<255)           //减小频率
            PWMPER1++;
        if(PWMDTY1>PWMPER1+10)    //减小占空比
              PWMDTY1=PWMPER1*4/5;  //20%
      break; 
      case 'l':
        u8_RCV_Ch=0xff;
        PWME_PWME1 = 1;
        if(PWMDTY1<PWMPER1)       //增大占空比
            PWMDTY1++;
      break; 
      case 'r':
        u8_RCV_Ch=0xff; 
        PWME_PWME1 = 1;
        if(PWMDTY1<PWMPER1)       //减小占空比
              PWMDTY1--;
      break;      
      default:             
      break;      
    }//switch(u8_RCV_Ch)      
    
  //Beep();
  SCI0CR2_RIE = 1;    
}
//====================main()==================================
#pragma CODE_SEG DEFAULT     
void main(void)    
{   

  char  txtbuf[16]="";
   
  Init_Dev();  
  PORTB=0x00;
  putstr("\nLongQiu s.&t. Co. Ltd.");    
  putstr("\nhttp://shop36265907.taobao.com");
  Dly_ms(1000);   
  PORTB=0xFF;
  EnableInterrupts;    
  for(;;)
  {     
    Dly_ms(500);
//----------PWM0---------------------------------- 
    sprintf(txtbuf,"\nFrequence: %d0Hz",PWMPER1);  
    putstr(txtbuf); 
    sprintf(txtbuf,"\n duty circle: %d%%",(PWMPER1-PWMDTY1)*100/PWMDTY1);
    putstr(txtbuf);        
    PORTB_PB0=~PORTB_PB0;        
  }//for(;;)
} //main

