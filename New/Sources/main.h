#define LASER_MAX 15          //激光管数量
#define PWM67 224	
#define PWM01 1488
#define ANGLE_DELTA 30
#define PWM6_MID 224		
//===============全局变量定义======================//
   int temp_pwm67=PWM67;						//激光摆头舵机初始值
  int temp_pwm01=PWM01;						//转向摆头舵机初始值
  byte light_temp_laser_array[LASER_MAX];  //当前激光管信息保存数组
  int testcount=1;
  int count=1;                                  //串口接收延时
  int q_temp_laser_num[LASER_MAX];       //激光管对应的权值
  int countPIT0=0;
  int position=0;                        
  int His_ADD_Position[3];                      //步进累加值历史   His_ADD_Position[2]=aabs[1]
  int His_Position[4];                        //历史position  position[3]=position[1]-position[0] position[2]=aabs[position]
  int angle[2]; 
  int Calculate_HitBlackNum(void);
  int YaoKp ,YaoKd,ZhuanKp,ZhuanKd;
  byte lost_line_flag=0;
  int ADD_Position; 
  int Diff_Position;
  int GDiff_Position[3];                      //摇头舵机的摆值(由于采样周期不同 舵机差值要设两个)  GDiff_Position[2]=aabs（GD【1】）
  int YDiff_Position[2];                      //摇头舵机摆值
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

 //=====================舵机初始化======================//
void PWM_Init(void){     		//PWM初始化。其中P4,P5控制电机正反转, P6,P7级联激光管控制舵机。

	PWME=0X00;            		//初始化，先是通道使能禁止。
	PWMPRCLK=0x11;				//预分频，A,B时钟为总线的1/2，就是Clock A和Clock B。
  
	PWMSCLA=10;            		//SA时钟设置,Clock SA=Clock A/(2*PWMSCLA)。
	PWMSCLB=35;             	//SB时钟设置,Clock SB=Clock B/(2*PWMSCLB)。
  

	PWMCLK_PCLK0=1;	
	PWMCLK_PCLK1=1;
	PWMCLK_PCLK6=1;
	PWMCLK_PCLK7=1;
  

	PWMPOL_PPOL0=1;				//转向摆头舵机极性选择设置
	PWMPOL_PPOL1=1;
	PWMPOL_PPOL6=1;				//激光摆头数字极性选择设置
	PWMPOL_PPOL7=1;
  
  PWMCTL = 0B00110000;     //通道23级联
  
	PWMCAE_CAE0=0;				//转向摆头舵机对齐方式
	PWMCAE_CAE1=0;	
	PWMCAE_CAE6=1;         		//激光摆头数字舵机对齐方式
	PWMCAE_CAE7=1;
	
  PWMCNT01 = 0;				//01口计数器清零；
  PWMCNT23 = 0;			//计数器23清零 
  
	PWMCTL=0x90;            	//控制寄存器，01和67口级联。
	
	PWMPER23 = 1000;    //频率 8kHz 
	PWMPER01=20000;				//1024×1024（频率）*Clock A/2/PWMSCLB/PWMPER67
	PWMPER67=1000;				//1024×1024（频率）*Clock B/2/PWMSCLB/PWMPER67
 
	PWMDTY01=PWM01;
	PWMDTY23 = 0;      //速度为0，即静止
	PWMDTY67=PWM67;				//PWMDTY67/PWMPER67*100%
	PWME=0xff;         			//启动通道使能?
}
//=====================激光初始化======================//
 void LIGHT_Init(void){ 
	DDRA = 0B00011111;  //PA0--PA7激光管信号控制 --- 输出 
	DDRB = 0X00;        //PB0--PB8激光管信号采集 --- 输入
 }
 

//=====================激光点亮======================//
void receive(int send) {
   if(send == 0)   { 
     delayms(1); 
	    light_temp_laser_array[3] = PORTB_PB1^1;	//接收第4组（3,8,13）  
        light_temp_laser_array[8] = PORTB_PB2^1;
        light_temp_laser_array[13] = PORTB_PB4^1;
        PORTA = 0B00000001;					//点亮第0组（1,6,11）
    }   
  

   else if(send == 1)   { 
    delayms(1);
        light_temp_laser_array[0] = PORTB_PB0^1;	//接收第0组（0,5,10）   
        light_temp_laser_array[5] = PORTB_PB1^1; 
        light_temp_laser_array[10] = PORTB_PB3^1;
        PORTA = 0B00000100;					//点亮第1组（2,7,12）
        
    }
    
    else if(send ==2)   { 
     delayms(1);
		light_temp_laser_array[2] = PORTB_PB0^1;	//接收第1组（2,7,12）  
        light_temp_laser_array[7] = PORTB_PB2^1; 
        light_temp_laser_array[12] = PORTB_PB4^1;
        PORTA = 0B00010000;					//点亮第2组（4,9,14）
    } 
    else	if(send == 3)       { 
         delayms(1);
	    light_temp_laser_array[4] = PORTB_PB1^1;	//接收第2组（4,9,14） 
        light_temp_laser_array[9] = PORTB_PB3^1; 
        light_temp_laser_array[14] = PORTB_PB4^1;
     PORTA = 0B00000010;					//点亮第3组（1,6,11）
  }
   else if(send == 4)   {
       delayms(1);
        light_temp_laser_array[1] = PORTB_PB0^1;	//接收第3组（1,6,11）
        light_temp_laser_array[6] = PORTB_PB2^1; 
        light_temp_laser_array[11] = PORTB_PB3^1;	
        PORTA = 0B00001000;					//点亮第4组（3,8,13）
    } 
   
} 

