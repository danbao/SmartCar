/*ȫ�ֱ����������������������*/
#define uchar 	unsigned char
#define uint 	unsigned int
float Prop1,Prop2,Diff1,Diff2,SpeedAver,SpeedMax,SpeedMin,SpeedNow;    /*P1,P2,D1,D2ֵ,ƽ���ٶ�,����ٶ�,��С�ٶ�,��ǰ�ٶ�*/
char lcd[100];                    /*����LCD��ʾ���ַ���*/
char SCIreceive[100];             /*���ڴ�����ʾ���ַ���*/
byte light_temp_laser_array[12]="100001000010";
int IR_temp_laser_array[7]={100,0,200,0,255,100,150};
int JG_clear_position;
int position=-11;

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