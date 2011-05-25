#define LASER_MAX 12          //激光管数量
#define PWM67 1531
#define PWM45 1478
#define ANGLE_DELTA 30
#define PWM6_MID 224
#define Speed 50		
//===============全局变量定义======================//
  float YP1=0.4,YP2=0.5,YP3=0.7,YP4=0.8,YP5=0.9,YD=2.7;
  float JP1=1.7,JP2=3.5,JP3=4.9,JP4=6.5,JP5=7.8,JD=2.3,SpeedAver,SpeedMax,SpeedMin,SpeedNow;/*摇头P1,摇头P2,摇头P3,摇头P4,摇头P5,摇头D,打角P1,打角P2,打角P3,打角P4,打角P5,打角P6,打角D
  平均速度,最大速度,最小速度,当前速度*/
  
  char SCIreceive[150];             /*用于无线串口显示的字符串*/  
  int temp_pwm67=PWM67;						//激光摆头舵机初始值
  int temp_PWM45=PWM45;						//转向摆头舵机初始值
  byte light_temp_laser_array[LASER_MAX];  //当前激光管信息保存数组
  float IR_temp_laser_array[7];             //当前红外信息保存数组
  byte special_flag;
  byte start_flag,cross_flag;          //起跑 十字标志

  int testcount=1;
  int count=1;                                  //串口接收延时
  int q_temp_laser_num[LASER_MAX];       //激光管对应的权值
  int countPIT0=0;
  int position=0; 
  int HitBlackNum; 
                   
 int JG_clear_position;
 int His_Position[4];                        //历史position  position[3]=position[1]-position[0] position[2]=aabs[position]
 int angle[2]; 
 
 void calculate_light(void);
 void Status_Judge(void);
 // int YaoKp ,YaoKd,ZhuanKp,ZhuanKd;
 //byte lost_line_flag=0;
 // int ADD_Position; 
  int Diff_Position;
  int GDiff_Position[3];                      //摇头舵机的摆值(由于采样周期不同 舵机差值要设两个)  GDiff_Position[2]=aabs（GD【1】）
  int J_His_Position[3];                       //打角获取position 采样周期不同
  
  int g_countPIT0 =0;   //用于PIT组别的点亮次数
	int	g_temp_laser_array[11]; //用于接受各个激光管点亮后获取的数据
	int g_temp_pulse;
	
	int temp_laser_array[11];
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

 //=====================PWM初始化======================//
static void PWM_Init(void){     		//PWM初始化。其中P4,P5控制电机正反转, P6,P7级联激光管控制舵机。

	PWME=0X00;            		//初始化，先是通道使能禁止。

	PWMSCLA=10;            		//SA时钟设置,Clock SA=Clock A/(2*PWMSCLA)。

	PWMSCLB=10;             	//SB时钟设置,Clock SB=Clock B/(2*PWMSCLB)。
	
  PWMCAE_CAE1=0;         // 对齐方式
//  PWMCAE_CAE3=0;
	PWMCAE_CAE4=0;				//转向摆头舵机对齐方式
	PWMCAE_CAE5=0;	
	PWMCAE_CAE6=0;         		//激光摆头数字舵机对齐方式
	PWMCAE_CAE7=0;
	
	PWMCNT45 = 0;				//45口计数器清零
  PWMCNT67 = 0;       //45口计数器清零
  				
  PWMPOL_PPOL1=1;        //极性选择设置。
  //PWMPOL_PPOL3=1;
  PWMPOL_PPOL4=1;				//转向摆头舵机极性选择设置
	PWMPOL_PPOL5=1;
	PWMPOL_PPOL6=1;				//激光摆头数字极性选择设置
	PWMPOL_PPOL7=1;
	
	PWMCTL=0B11110000;            	//控制寄存器，45和67口级联。通道23级联
  
  PWMPRCLK=0x11;				//预分频，A,B时钟为总线的1/2，就是Clock A和Clock B。
	PWMCLK_PCLK1=0;         // 时钟源选择。
  PWMCLK_PCLK3=0;
	PWMCLK_PCLK4=1;	
	PWMCLK_PCLK5=1;
	PWMCLK_PCLK6=1;
	PWMCLK_PCLK7=1;
  

	
  PWMPER01 = 100;    //频率 8kHz 
	PWMPER45=10000;				//1024×1024（频率）*Clock A/2/PWMSCLB/PWMPER67
	PWMPER67=10000;				//1024×1024（频率）*Clock B/2/PWMSCLB/PWMPER67
 
	PWMDTY45=PWM45;
	PWMDTY01 = 0;      //速度为0，即静止
	PWMDTY67=PWM67;				//PWMDTY67/PWMPER67*100%
  PWME=0xf3;  
}
//=====================激光初始化======================//
 void LIGHT_Init(void){ 
	DDRA = 0X3F;      //PA0--PA5激光管信号点亮
	DDRB = 0Xf0;      //PB0--PB3激光管信号接收
 }
 
 
 void PITInit (void) {
//计算公式：time-out period = (PITMTLD + 1) * (PITLD + 1) / fBUS.
//BUS为总线！！！

    // Local Declarations

    // Statements
    PITCFLMT_PITE = 0; //定时中断通道0,1关
    
	//PIT0主要激光管的点亮
    PITCE_PCE0 = 1;    //定时器通道0使能
    PITMUX_PMUX0 = 0;  //定时0通道0使用微计数器0 
    PITMTLD0 = 160-1;  //设置微计数器0的加载寄存器。8位定时器初值设定。160分频，在16MHzBusClock下，为0.1MHz。即10us.
    PITLD0 = 142-1;    //16位定时器初值设定。140  -->  1.4ms 
    PITINTE_PINTE0 = 1;//定时器中断通道0中断使能
    
	//PIT0主要测速，所得到的是脉冲值，结合ECT。。
    PITCE_PCE1 = 1;    //定时器通道1使能
    PITMUX_PMUX1 = 0;  //定时1通道1使用微计数器0
    PITMTLD1 = 160-1;  //设置微计数器0的加载寄存器。8位定时器初值设定。160分频，在16MHzBusClock下，为0.1MHz。即10us.
    PITLD1 = 2000-1;   //16位定时器初值设定。2000  -->  20ms
    PITINTE_PINTE1 = 1;//定时器中断通道1中断使能 
   
    PITCFLMT_PITE = 1; //定时器通道0,1使能
} //PITInit


//=====================激光点亮======================//
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
