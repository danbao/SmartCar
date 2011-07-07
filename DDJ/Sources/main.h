#define LASER_MAX 21          //激光管数量
#define IR_NUM 7              //红外观数量
//#define PWM67 1845
//#define PWM45 3528
#define ANGLE_DELTA 30
#define PWM6_MID 224
#define PWM01 1972
#define PWM45 1603
#define PWM7 30
#define PWMPE7 60
//#define Speed 50
#define N 5                  //红外滤波权值		
/*===============全局变量定义======================
全局变量相关 
*/
  float YP1=0.4,YP2=0.5,YP3=0.7,YP4=0.8,YP5=0.9,YD=2.7;
  float JP1=1.7,JP2=3.5,JP3=4.9,JP4=6.5,JP5=7.8,JD=2.3,SpeedAver,SpeedMax,SpeedMin,SpeedNow;/*摇头P1,摇头P2,摇头P3,摇头P4,摇头P5,摇头D,打角P1,打角P2,打角P3,打角P4,打角P5,打角P6,打角D
  平均速度,最大速度,最小速度,当前速度*/
  int DP1=1,DP2=1,DP3=1,DP4=1,DP5=1,DP6=1,DP7=1;
  int DD=0;
  int BP1=20,BP2=35,BP3=35,BP4=35,BP5=35,BP6=35,BP7=35,BP8=35,BP9=25,BP10=25;
  int BD1=250,BD2=200,BD3=70,BD4=50,BD5=35,BD6=32,BD7=32,BD8=32,BD9=25,BD10=25;
  char SCIreceive[150];                    /*用于无线串口显示的字符串*/  
  int temp_pwm45=PWM45;						         //激光摆头舵机初始值
  int temp_pwm01=PWM01;					         	 //转向摆头舵机初始值
  
  byte light_temp_laser_array[LASER_MAX];  //当前激光管信息保存数组
  int  light_count;                        //激光点亮延迟
  
  byte maybe_slope_flag=0;                //开启 起跑或者十字 也有可能是坡道
  byte maybe_special_flag=0;                 //开启可能的特殊  为坡道
  byte start_flag=0,cross_flag=0;             //起跑 十字标志
  byte slope_flag=0;                         //坡道 标识 
  int special_count=0;                         //25mm 4571 编码值
 
  byte error[LASER_MAX];
  //int error;
  
  double temp_speed;
  int delay_count=1;                      //普通延时计数
  int send_count=1;                       //串口接收延时计数
  int q_temp_laser_num[LASER_MAX];        //激光管对应的权值
  int countPIT0=0;
  int position;                     //位置 
  
  //红外
  byte IR_temp_laser_array[7];             //当前红外信息保存数组
  byte IR_process_array[7]={2,2,2,2,2,2,2}; 
  byte empty_count=0;
  
  byte nothing_flag=0 ;
  byte right,left,middle;                    //中线左右值
  
  int HitBlackNum;
  int His_HitBlackNum;
  
  int baitou_diff; 
  
  byte SS_flag;                           //小s标记  1有效
  byte LS_flag;                           //大S标记   1有效
  byte Straight_flag=1;                     //直道标记  非0有效
  byte turn_flag=0;                         //弯道标记  非0有效                 
  byte Straight_stop;                      //直道入弯的反转
  byte turn_stop;                          //弯道入直的反转
  byte first_flag=1;
  
  //int quanyi=0;
  
  byte YDdelay=1;
  byte diansha_falg=0;                     //点刹标志
  byte diansha_count;                      //点刹计数
  byte diansha_num;                        //点刹时间 利用入弯时的速度 来进行点刹时间
 // int road_point[6];                      //5点归为一段  假设2.5m/s 5点为1.8cm  road_point[5]为最后点值
 // int point_count;                        //5点计数 同时也可作为段判断开始的标志
 // int road_section[20];                   //8段归为一长路  同假设8段为15cm
 // int section_flag;                      //8段计数
  
  int  befo_General_pos;                  //舵机的综合偏差
  float General_pos;                     //模型
  int change_JG_DJ_array[41]={141,131,119,115,109,103,96,89,83,78,71,66,56,53,46,41,35,30,18,6,0,-6,-18,-30,-35,-41,-46,-53,-56,-66,-71,-78,-83,-89,-96,-103,-109,-115,-119,-131,-141}; 
  int cha_pos=0;
  //int coordinate
 //int standard_position_array[23]=
  //标准position的值
 // int temp_position_array[22];
  //用于记录position的值，形成预判的趋势 
//int last_laser_array[20][11];    
//这个二维数组作为激光管的历史记录
  int baitoupwm;
  
  long speedaffect1;
  long speedaffect2;
  long speedaffect3;
   
  int speedinfo;
  //int dajiao_Slope[3];                   //打角舵机的两个斜率 2为累加值
  
  int  baitou_delay=1;                    //摆头延迟  同时用来等分摆头的每次舵机值
  int JG_clear[4];                      //激光一次迭代滤波 此次和上次
  int JG_clear_Pos[2];                  //存入当前和上一次摆头时的JG_clear 的值
                             
 // int speed_collect;                     //速度捕捉值
  long speed_clear[2];                    //速度滤波值  最终结果 此次和上次
  //int speed[20];                          //给
  
  void calculate_light(void);
  void Status_Judge(void);
  
 // int g_countPIT0 =0;   //用于PIT组别的点亮次数
//	int	g_temp_laser_array[LASER_MAX]; //用于接受各个激光管点亮后获取的数据
	
	
//	int temp_laser_array[LASER_MAX];

/*===============时钟初始化========================*/
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

//=====================PWM初始化======================//
void PWM_Init (void) 
{   //0519暂时写完！
  // Local Declarations

  // Statements
   PWME = 0X00;       //禁止PWM输出  
   PWMCAE = 0X00;     //左对齐
   
   //PWMCNT01 = 0; //计数器01清零
   //PWMCNT23 = 0; //计数器23清零
   //PWMCNT01 = 0; //计数器01清零
   //PWMCNT67 = 0; //计数器67清零
 
   PWMPOL = 0XFF;     //先输出高电平   PWM极性寄存器
   PWMCTL = 0X70;     //通道01级联，23级联，45级联
   PWMPRCLK = 0X21;   //clockA 2分频,clockA=busclock/2=20MHz;CLK B 4分频:10Mhz 
   PWMSCLA = 8;       //对clock SA 进行2*8=16分频；pwm clock=clockA/16=1.25MHz;
   PWMSCLB = 4;       //对clock SB 进行2*4=8分频；pwm clock=clockB/8=1.25MHz;
   PWMCLK_PCLK1 = 1;  //选择clock SA做时钟源  
   PWMCLK_PCLK3 = 0;  //选择clock SB做时钟源  
   PWMCLK_PCLK5 = 1;  //选择clock SA做时钟源  
   PWMCLK_PCLK6 = 1;  //选择clock B 做时钟源
   PWMCLK_PCLK7 = 0;  //选择clock B 做时钟源      

   PWMPER01 = 25000;    //频率 100Hz  周期10ms
   PWMPER23 = 625;    //频率 16kHz    周期6.25us
   PWMPER45 = 12500;  //频率 50Hz    周期10ms
   PWMPER6 = 78;  //频率 16kHz        周期6.25us
   PWMPER7 = PWMPE7;  //频率 166kHz   周期602ns
   
   PWMDTY01 = PWM01;      //占空比50%  前轮舵机
   PWMDTY23 = 500;      //占空比50%    电机正转
   PWMDTY45 = PWM45;      //           摆头舵机
   PWMDTY6 = 7;      //占空比50%      电机反转
   PWMDTY7 = PWM7;      //占空比50%    调制管
   PWME_PWME1 = 1;    //通道1输出,前轮舵机使能  
   PWME_PWME3 = 1;    //通道3输出,电机正转使能
   PWME_PWME5 = 1;    //通道5输出,摆头舵机使能     
   PWME_PWME6 = 1;    //通道6输出,电机反转使能
   PWME_PWME7 = 1;    //通道7输出,调制管使能    
} //PWMInit

//=====================ECT捕捉测速初始化======================//
 void Tect_Speed_Init()
 { 
   TSCR1=0x80;          //使能定时器
   PACTL=0X50;  //PT7输入捕捉  
   PACNT=0;
 }

//=====================激光初始化======================//
 void LIGHT_Init(void)
 { 
   DDRA = 0X7F;      //PA0--PA5激光管信号点亮
   DDRB = 0X80;      //PB0--PB3激光管信号接收
 }

/*=====================PIT初始化======================*/
 void PITInit (void) 
 {
//计算公式：time-out period = (PITMTLD + 1) * (PITLD + 1) / fBUS.
//BUS为总线！！！

    // Local Declarations

    // Statements
    PITCFLMT_PITE = 0;       //PIT通道使能位      
    PITCE_PCE0 = 1;          //定时器通道0使能    
    PITMUX_PMUX0 = 0;       //定时通道0使用微计数器0     
    PITMTLD0 =200-1;  //设置微计数器0的加载寄存器。8位定时器初值设定。200分频，在40MHzBusClock下，为0.2MHz。即5us.    
    PITLD0 = 340-1;    //16位定时器初值设定。4000 -->  20ms   1500-->7.5ms  
    PITINTE_PINTE0 = 1;//定时器中断通道0中断使能            
   // PITCFLMT_PITE = 1;       //PIT通道使能位

    PITCE_PCE1 = 1;          //定时器通道0使能    
    PITMUX_PMUX1 = 1;       //定时通道0使用微计数器0     
    PITMTLD1 =200-1;  //设置微计数器0的加载寄存器。8位定时器初值设定。200分频，在40MHzBusClock下，为0.2MHz。即5us.    
    PITLD1 = 1500-1;    //16位定时器初值设定。4000 -->  20ms   1500-->7.5ms  
    PITINTE_PINTE1 = 1;//定时器中断通道0中断使能            
    PITCFLMT_PITE = 1;       //PIT通道使能位
} //PITInit


/*=====================激光点亮======================
最后发现由于用定时中断还是。。所以就换回在主程序中点亮
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
    PORTA = 0B00000000;         //点亮后关闭通道
  }
  light_count=0;   
} 