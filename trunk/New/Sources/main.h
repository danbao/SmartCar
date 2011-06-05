#define LASER_MAX 12          //激光管数量
#define IR_NUM 7              //红外观数量
#define PWM67 1881
#define PWM45 3666
#define ANGLE_DELTA 30
#define PWM6_MID 224
#define Speed 50
#define N 5                  //红外滤波权值		
//===============全局变量定义======================//
  float YP1=0.4,YP2=0.5,YP3=0.7,YP4=0.8,YP5=0.9,YD=2.7;
  float JP1=1.7,JP2=3.5,JP3=4.9,JP4=6.5,JP5=7.8,JD=2.3,SpeedAver,SpeedMax,SpeedMin,SpeedNow;/*摇头P1,摇头P2,摇头P3,摇头P4,摇头P5,摇头D,打角P1,打角P2,打角P3,打角P4,打角P5,打角P6,打角D
  平均速度,最大速度,最小速度,当前速度*/
 
  char SCIreceive[150];             /*用于无线串口显示的字符串*/  
  int temp_pwm67=PWM67;						//激光摆头舵机初始值
  int temp_pwm45=PWM45;						//转向摆头舵机初始值
  
  byte light_temp_laser_array[LASER_MAX];  //当前激光管信息保存数组
  uint IR_temp_laser_array[7];             //当前红外信息保存数组
  
  byte special_flag;
  byte start_flag,cross_flag;          //起跑 十字标志
  
  int error;
  
  double temp_speed;
  int delay_count=1;                             //普通延时计数
  int send_count=1;                              //串口接收延时计数
  int q_temp_laser_num[LASER_MAX];       //激光管对应的权值
  int countPIT0=0;
  int position=0; 
  int HitBlackNum; 
  
  byte SS_flag;                          //小s标记  1有效
  byte LS_flag;                         //大S标记   1有效
  byte Straight_flag;                   //直道标记  非0有效
  byte turn_flag;                       //弯道标记  非0有效                 

 int standard_position_array[22]={1539,1523,1547,1515,1551,1511,1556,1506,1566,1496,1574,1488,1581,1481,1585,1477,1591,1471,1598,1464,1611,1451}; 
  //标准position的值
  int temp_position_array[22];
  //用于记录position的值，形成预判的趋势 
//int last_laser_array[20][11];    
//这个二维数组作为激光管的历史记录
 
  int IR_position[2];                 //红外位置   红外部分变量都以IR开头
  int IR_blacknun=0;                  //红外黑点
  void Level_IR( void);               //声明  不懂去掉可不可以
  long IR_clear[2];                   //红外滤波值
  
  int  delay_JG=1;
  long JG_clear[2];                      //激光一次迭代滤波 此次和上次
  long JG_clear_Pos[2];                  //存入当前和上一次摆头时的JG_clear 的值
 
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
     for(jj=0;jj<833;jj++);    //1/6ms     
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
void PWM_Init (void) {   //0519暂时写完！
  // Local Declarations

  // Statements
   PWME = 0X00;       //禁止PWM输出  
   PWMCAE = 0X00;     //左对齐
   
   PWMCNT01 = 0;			//计数器01清零
   PWMCNT23 = 0;			//计数器23清零
   PWMCNT45 = 0;			//计数器45清零
   PWMCNT67 = 0;			//计数器67清零
 
   PWMPOL = 0XFF;     //先输出高电平   PWM极性寄存器
   PWMCTL = 0XF0;     //通道01.23.45.67级联  0B11111111   01正转 23反转
   PWMPRCLK = 0X21;   //clockA 2分频,clockA=busclock/2=20MHz;CLK B 4分频:10Mhz 
   PWMSCLA = 4;       //对clock SA 进行2*4=8分频；pwm clock=clockA/8=2.5MHz;
   PWMSCLB = 4;       //对clock SB 进行2*4=8分频；pwm clock=clockB/8=1.25MHz;
   PWMCLK_PCLK1 = 1;  //选择clock SA做时钟源  01
   PWMCLK_PCLK3 = 1;  //选择clock SB做时钟源  23
   PWMCLK_PCLK5 = 1;  //选择clock SA做时钟源  45
   PWMCLK_PCLK7 = 1;  //选择clock SB做时钟源  67	   

   PWMPER01 = 250;    //频率 10kHz  周期0.1ms
   PWMPER23 = 125;    //频率 10kHz  周期0.1ms
   PWMPER45 = 25000;  //频率 100Hz  周期50ms
   PWMPER67 = 12500;  //频率 100Hz  周期50ms
   
   PWMDTY01 = 25;      //占空比10%
   PWMDTY23 = 62;      //占空比50%
   PWMDTY45 = 3666;      //
   PWMDTY67 = 1881;      //占空比50%
   PWME_PWME1 = 1;    //通道1输出,电机正转使能   正转
   PWME_PWME3 = 1;    //通道3输出,电机反转使能 
   PWME_PWME5 = 1;    //通道5输出,前轮舵机使能     
   PWME_PWME7 = 1;    //通道7输出,摆头舵机使能     
} //PWMInit

//=====================ECT捕捉测速初始化======================//
 void Tect_Speed_Init()
 { 
   TSCR1=0x80;          //使能定时器
   PACTL=0X50;  //PT7输入捕捉  
   PACNT=0;
 }


//=====================激光初始化======================//
 void LIGHT_Init(void){ 
	DDRA = 0X3F;      //PA0--PA5激光管信号点亮
	DDRB = 0Xf0;      //PB0--PB3激光管信号接收
 }



//=====================PIT初始化======================//
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
    PITLD1 = 1000-1;   //16位定时器初值设定。1000  -->  10ms
    PITINTE_PINTE1 = 1;//定时器中断通道1中断使能 
   
    PITCFLMT_PITE = 1; //定时器通道0,1使能
} //PITInit


/*=====================激光点亮======================
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