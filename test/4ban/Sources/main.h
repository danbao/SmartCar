#define LASER_MAX 21          //激光管数量
char SCIreceive[100];
int count;
byte light_temp_laser_array[LASER_MAX];  //当前激光管信息保存数组
#define PWM01 3808
#define PWM45 3808
#define PWM7 30
#define PWMPE7 60

  int light_count;	
//===============时钟初始化========================//
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

//=====================PWM初始化======================//
void PWM_Init (void) {   //0519暂时写完！
  // Local Declarations

  // Statements
   PWME = 0X00;       //禁止PWM输出  
   PWMCAE = 0X00;     //左对齐
   
   //PWMCNT01 = 0; //计数器01清零
   //PWMCNT23 = 0; //计数器23清零
   //PWMCNT45 = 0; //计数器45清零
   //PWMCNT67 = 0; //计数器67清零
 
   PWMPOL = 0XFF;     //先输出高电平   PWM极性寄存器
   PWMCTL = 0X70;     //通道01级联，23级联，45级联
   PWMPRCLK = 0X21;   //clockA 2分频,clockA=busclock/2=20MHz;CLK B 4分频:10Mhz 
   PWMSCLA = 4;       //对clock SA 进行2*4=8分频；pwm clock=clockA/8=2.5MHz;
   PWMSCLB = 4;       //对clock SB 进行2*4=8分频；pwm clock=clockB/8=1.25MHz;
   PWMCLK_PCLK1 = 1;  //选择clock SA做时钟源  
   PWMCLK_PCLK3 = 0;  //选择clock SB做时钟源  
   PWMCLK_PCLK5 = 1;  //选择clock SA做时钟源  
   PWMCLK_PCLK6 = 1;  //选择clock B 做时钟源
   PWMCLK_PCLK7 = 0;  //选择clock B 做时钟源      

   PWMPER01 = 25000;    //频率 100Hz  周期0.1ms
   PWMPER23 = 625;    //频率 16kHz  
   PWMPER45 = 25000;  //频率 100Hz  
   PWMPER6 = 78;  //频率 16kHz  
   PWMPER7 = PWMPE7;  //频率 166kHz  
   
   PWMDTY01 = PWM01;      //占空比50%
   PWMDTY23 = 312;      //占空比50%
   PWMDTY45 = PWM45;      //
   PWMDTY6 = 39;      //占空比50%
   PWMDTY7 = PWM7;      //占空比50%
   PWME_PWME1 = 1;    //通道1输出,前轮舵机使能  
   PWME_PWME3 = 1;    //通道3输出,电机正转使能
   PWME_PWME5 = 1;    //通道5输出,摆头舵机使能     
   PWME_PWME6 = 1;    //通道6输出,电机反转使能
   PWME_PWME7 = 1;    //通道7输出,调制管使能    
} //PWMInit

   
//==============延时程序================================//
void delayms(int ms)    //延时程序。
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
//=====================激光初始化======================//
 void LIGHT_Init(void){ 
	DDRA = 0X7F;      //PA0--PA5激光管信号点亮
	DDRB = 0X00;      //PB0--PB3激光管信号接收
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
 PORTA = 0B00000000;         //点亮后关闭通道
   }
light_count=0;   
} 