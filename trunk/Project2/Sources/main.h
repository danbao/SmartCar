#define LASER_MAX 15          //���������
#define PWM67 224	
#define PWM01 1488
#define ANGLE_DELTA 30
#define PWM6_MID 224		
//===============ȫ�ֱ�������======================//
   int temp_pwm67=PWM67;						//�����ͷ�����ʼֵ
  int temp_pwm01=PWM01;						//ת���ͷ�����ʼֵ
  byte light_temp_laser_array[LASER_MAX];  //��ǰ�������Ϣ��������
  int testcount=1;
  int count=1;                                  //���ڽ�����ʱ
  int q_temp_laser_num[LASER_MAX];       //����ܶ�Ӧ��Ȩֵ
  int countPIT0=0;
  int position=0;                        
  int His_ADD_Position[3];                      //�����ۼ�ֵ��ʷ   His_ADD_Position[2]=aabs[1]
  int His_Position[4];                        //��ʷposition  position[3]=position[1]-position[0] position[2]=aabs[position]
  int angle[2]; 
  int Calculate_HitBlackNum(void);
  int YaoKp ,YaoKd,ZhuanKp,ZhuanKd;
  byte lost_line_flag=0;
  int ADD_Position; 
  int Diff_Position;
  int GDiff_Position[3];                      //ҡͷ����İ�ֵ(���ڲ������ڲ�ͬ �����ֵҪ������)  GDiff_Position[2]=aabs��GD��1����
  int YDiff_Position[2];                      //ҡͷ�����ֵ
//===============ʱ�ӳ�ʼ��========================//

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
//==============��ʱ����================================//
void delayms(int ms)    //��ʱ����
{   
   int ii,jj;
   if (ms<1) ms=1;
   for(ii=0;ii<ms;ii++)
     for(jj=0;jj<3338;jj++);    //40MHz--1ms      
}
