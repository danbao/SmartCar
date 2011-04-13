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
