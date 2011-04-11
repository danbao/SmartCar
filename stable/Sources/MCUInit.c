/* 芯片初始化函数
*工 程 名: 5th Smartcar v3.1_15Laser.mcp                                                                                   
*说    明:   

	  Written by: swe07024 张苷倩           
    Date:       2010.7.19
    Update:     2010.7.19
*/

//【header file】
#include "MCUInit.h"


//【function definitions】
/* ================= PWMInit ====================
      desc: PWM初始化
      pre:  无
      Post: 无
       
*/ 
void PWMInit (void) {
  // Local Declarations

  // Statements
   PWME = 0X00;       //禁止PWM输出  
   PWMCAE = 0X00;     //左对齐
   
   PWMCNT01 = 0;			//计数器01清零
   PWMCNT23 = 0;			//计数器23清零
   PWMCNT45 = 0;			//计数器23清零
 
   PWMPOL = 0XFF;     //先输出高电平
   PWMCTL = 0X70;     //通道01.23.45级联
   PWMPRCLK = 0X40;   //clockA不分频,clockA=busclock=16MHz;CLK B 16分频:1Mhz 
   PWMSCLA = 8;       //对clock SA 进行2*8=16分频；pwm clock=clockA/16=1MHz;
   PWMCLK_PCLK1 = 1;  //选择clock SA做时钟源  
   
   PWMPER23 = 125;    //频率 8kHz 
   PWMPER01 = 10000;  //频率 100Hz 
   PWMPER45 = 125;    //频率 8kHz 
   PWMDTY23 = 0;      //速度为0，即静止
   PWMDTY45 = 0;      //速度为0，即静止
   PWME_PWME1 = 1;    //通道1输出，舵机使能
   PWME_PWME3 = 1;    //通道3输出,电机正转使能 
   PWME_PWME5 = 1;    //通道5输出,电机反转使能     
} //PWMInit


/* ================= PITInit ====================
      desc: PIT初始化，用于速度捕捉--定时5ms,双沿捕捉
      pre:  无
      Post: 无
       
*/ 
void PITInit (void) {
    // Local Declarations

    // Statements
    PITCFLMT_PITE = 0; //定时中断通道0,1关
    
    PITCE_PCE0 = 1;    //定时器通道0使能
    PITMUX_PMUX0 = 0;  //定时0通道0使用微计数器0 
    PITMTLD0 = 160-1;  //设置微计数器0的加载寄存器。8位定时器初值设定。160分频，在16MHzBusClock下，为0.1MHz。即10us.
    PITLD0 = 142-1;    //16位定时器初值设定。140  -->  1.4ms 
    PITINTE_PINTE0 = 1;//定时器中断通道0中断使能
    
    PITCE_PCE1 = 1;    //定时器通道1使能
    PITMUX_PMUX1 = 0;  //定时1通道1使用微计数器0
    PITMTLD1 = 160-1;  //设置微计数器0的加载寄存器。8位定时器初值设定。160分频，在16MHzBusClock下，为0.1MHz。即10us.
    PITLD1 = 2000-1;   //16位定时器初值设定。2000  -->  20ms
    PITINTE_PINTE1 = 1;//定时器中断通道1中断使能 
   
    PITCFLMT_PITE = 1; //定时器通道0,1使能
} //PITInit


/* ================= PLLInit ====================
      desc: BUS CLOCK=16M
      pre:  无
      Post: 无
       
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
      desc: 普通IO口初始化
      pre:  无
      Post: 无
       
*/ 
void GIOInit (void) {
  // Local Declarations

  // Statements
  DDRA = 0B00011111;  //PA0--PA4激光管信号控制 --- 输出 ,PA5--PA7 --- 输入，接收拨码开关123
  DDRB |= 0X00;        //PB0--PB8激光管信号采集 --- 输入
  DDR1AD0 |= 0X00;     //AN0--AN6激光管信号采集 --- 输入
  ATD0DIENL = 0XFF;    //AD口数字输入允许
  ATD0DIENH = 0XFF;
  DDRT |= 0X00;        //PT0--PT3拨码开关 --- 输入
  DDRE |= 0XF0;        //PE5,PE6输出，开启绿色LED灯, PE3输入，接收拨码开关4    
} //GIOInit


/* ================= SCIInit ====================
      desc: SCI串口初始化
      pre:  无
      Post: 无
       
*/ 
void SCIInit(void){
  byte tmp;     //定义一个临时变量,用来读寄存器
  SCI0BD = 104; //80m。 40M时的38400波特率   bus/16*bd   80MHZ 82
  SCI0CR1 = 0x00;   //8位数据位,无校验
  SCI0CR2_RE = 1;   
  SCI0CR2_TE = 1;   //允许发送+接收
  SCI0CR2_RIE = 1;  //接收中断
  SCI0CR2_TCIE = 0; //禁止发送完毕中断
  
  //清除TDRE标志,首先读SCI0SR1,然后写SCI0DRH
  tmp = SCI0SR1;
  SCI0DRH = 0x00;
  return;         //SCI0BDL=busclk/(16*SCI0BDL) 
                  //busclk 16MHz, 9600bps,SCI0BD=0x68                 
} //SCIInit               


/* ================= PACNTInit ====================
      desc: 速度模块脉冲计数初始化
      pre:  无
      Post: 无
       
*/ 
void PACNTInit (void) {
     PACTL = 0X50;  //PT7输入捕捉
     PACNT = 0;         
} //PACNTInit               


/* ================= MCUInit ====================
      desc: 芯片总初始化
      pre:  无
      Post: 无
       
*/ 
void MCUInit (void) {
  // Local Declarations

  // Statements
  PLLInit ();  //时钟频率
  PWMInit ();  //PWM输出
  PITInit ();  //定时器  
  GIOInit ();  //普通IO口
  SCIInit ();  //串口
  PACNTInit (); //测速模块
} //MCUInit


