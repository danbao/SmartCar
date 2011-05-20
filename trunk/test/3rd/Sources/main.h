#define LASER_MAX 12          //激光管数量
char SCIreceive[100];
int count;
byte light_temp_laser_array[LASER_MAX];  //当前激光管信息保存数组
#define PWM67 1531
#define PWM45 1478


  int temp_pwm67=PWM67;						//激光摆头舵机初始值
  int temp_pwm45=PWM45;	
//===============时钟初始化========================//
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
//==============延时程序================================//
void delayms(int ms)    //延时程序。
{   
   int ii,jj;
   if (ms<1) ms=1;
   for(ii=0;ii<ms;ii++)
     for(jj=0;jj<3338;jj++);    //40MHz--1ms      
}
//=====================激光初始化======================//
 void LIGHT_Init(void){ 
	DDRA = 0X3F;      //PA0--PA5激光管信号点亮
	DDRB = 0X00;      //PB0--PB3激光管信号接收
 }
 
 //=====================舵机初始化======================//
static void PWM_Init(void){     		//PWM初始化。其中P4,P5控制电机正反转, P6,P7级联激光管控制舵机。

	PWME=0X00;            		//初始化，先是通道使能禁止。
	
	PWMCAE_CAE4=0;				//转向摆头舵机对齐方式
	PWMCAE_CAE5=0;	
	PWMCAE_CAE6=0;         		//激光摆头数字舵机对齐方式
	PWMCAE_CAE7=0;
	
	PWMCNT45 = 0;				//45口计数器清零�
  PWMCNT67 = 0;				//45口计数器清零；�
  
  PWMPOL_PPOL4=1;				//转向摆头舵机极性选择设置
	PWMPOL_PPOL5=1;
	PWMPOL_PPOL6=1;				//激光摆头数字极性选择设置
	PWMPOL_PPOL7=1;
	
	PWMCTL=0B11000000;            	//控制寄存器，45和67口级联。
  
  PWMPRCLK=0x11;				//预分频，A,B时钟为总线的1/2，就是Clock A和Clock B。
	
	PWMCLK_PCLK4=1;	
	PWMCLK_PCLK5=1;
	PWMCLK_PCLK6=1;
	PWMCLK_PCLK7=1;

	PWMSCLA=10;            		//SA时钟设置,Clock SA=Clock A/(2*PWMSCLA)。

	PWMSCLB=10;             	//SB时钟设置,Clock SB=Clock B/(2*PWMSCLB)。

	PWMPOL_PPOL4=1;				//转向摆头舵机极性选择设置
	PWMPOL_PPOL5=1;
	PWMPOL_PPOL6=1;				//激光摆头数字极性选择设置
	PWMPOL_PPOL7=1;
  
  //PWMCTL = 0B00100000;     //通道23级联
  

	
  
  //PWMCNT23 = 0;			//计数器23清零 
  

	
//	PWMPER23 = 125;    //频率 8kHz 
	PWMPER45=20000;				//1024×1024（频率）*Clock A/2/PWMSCLB/PWMPER67
	PWMPER67=20000;				//1024×1024（频率）*Clock B/2/PWMSCLB/PWMPER67
 
	PWMDTY45=PWM45;
	//PWMDTY23 = 0;      //速度为0，即静止
	PWMDTY67=PWM67;				//PWMDTY67/PWMPER67*100%
  PWME=0xff;  
}
//=====================激光摆头舵机改变函数======================//
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

