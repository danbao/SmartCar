#define LASER_MAX 12          //���������
char SCIreceive[100];
int count;
byte light_temp_laser_array[LASER_MAX];  //��ǰ�������Ϣ��������
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
//=====================�����ʼ��======================//
 void LIGHT_Init(void){ 
	DDRA = 0X3F;      //PA0--PA5������źŵ���
	DDRB = 0X00;      //PB0--PB3������źŽ���
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

