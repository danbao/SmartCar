#define LASER_MAX 12          //º§π‚π‹ ˝¡ø
char SCIreceive[100];
int count;
byte light_temp_laser_array[LASER_MAX];  //µ±«∞º§π‚π‹–≈œ¢±£¥Ê ˝◊È
#define PWM67 1531
#define PWM45 1478


  int temp_pwm67=PWM67;						//º§π‚∞⁄Õ∑∂Êª˙≥ı º÷µ
  int temp_pwm45=PWM45;	
//=============== ±÷”≥ı ºªØ========================//
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
//==============—” ±≥Ã–Ú================================//
void delayms(int ms)    //—” ±≥Ã–Ú°£
{   
   int ii,jj;
   if (ms<1) ms=1;
   for(ii=0;ii<ms;ii++)
     for(jj=0;jj<3338;jj++);    //40MHz--1ms      
}
//=====================º§π‚≥ı ºªØ======================//
 void LIGHT_Init(void){ 
	DDRA = 0X3F;      //PA0--PA5º§π‚π‹–≈∫≈µ„¡¡
	DDRB = 0X00;      //PB0--PB3º§π‚π‹–≈∫≈Ω” ’
 }
 
 //=====================∂Êª˙≥ı ºªØ======================//
static void PWM_Init(void){     		//PWM≥ı ºªØ°£∆‰÷–P4,P5øÿ÷∆µÁª˙’˝∑¥◊™, P6,P7º∂¡™º§π‚π‹øÿ÷∆∂Êª˙°£

	PWME=0X00;            		//≥ı ºªØ£¨œ» «Õ®µ¿ πƒ‹Ω˚÷π°£
	
	PWMCAE_CAE4=0;				//◊™œÚ∞⁄Õ∑∂Êª˙∂‘∆Î∑Ω Ω
	PWMCAE_CAE5=0;	
	PWMCAE_CAE6=0;         		//º§π‚∞⁄Õ∑ ˝◊÷∂Êª˙∂‘∆Î∑Ω Ω
	PWMCAE_CAE7=0;
	
	PWMCNT45 = 0;				//45ø⁄º∆ ˝∆˜«Â¡„£
  PWMCNT67 = 0;				//45ø⁄º∆ ˝∆˜«Â¡„£ªª
  
  PWMPOL_PPOL4=1;				//◊™œÚ∞⁄Õ∑∂Êª˙º´–‘—°‘Ò…Ë÷√
	PWMPOL_PPOL5=1;
	PWMPOL_PPOL6=1;				//º§π‚∞⁄Õ∑ ˝◊÷º´–‘—°‘Ò…Ë÷√
	PWMPOL_PPOL7=1;
	
	PWMCTL=0B11000000;            	//øÿ÷∆ºƒ¥Ê∆˜£¨45∫Õ67ø⁄º∂¡™°£
  
  PWMPRCLK=0x11;				//‘§∑÷∆µ£¨A,B ±÷”Œ™◊‹œﬂµƒ1/2£¨æÕ «Clock A∫ÕClock B°£
	
	PWMCLK_PCLK4=1;	
	PWMCLK_PCLK5=1;
	PWMCLK_PCLK6=1;
	PWMCLK_PCLK7=1;

	PWMSCLA=10;            		//SA ±÷”…Ë÷√,Clock SA=Clock A/(2*PWMSCLA)°£

	PWMSCLB=10;             	//SB ±÷”…Ë÷√,Clock SB=Clock B/(2*PWMSCLB)°£

	PWMPOL_PPOL4=1;				//◊™œÚ∞⁄Õ∑∂Êª˙º´–‘—°‘Ò…Ë÷√
	PWMPOL_PPOL5=1;
	PWMPOL_PPOL6=1;				//º§π‚∞⁄Õ∑ ˝◊÷º´–‘—°‘Ò…Ë÷√
	PWMPOL_PPOL7=1;
  
  //PWMCTL = 0B00100000;     //Õ®µ¿23º∂¡™
  

	
  
  //PWMCNT23 = 0;			//º∆ ˝∆˜23«Â¡„ 
  

	
//	PWMPER23 = 125;    //∆µ¬  8kHz 
	PWMPER45=20000;				//1024°¡1024£®∆µ¬ £©*Clock A/2/PWMSCLB/PWMPER67
	PWMPER67=20000;				//1024°¡1024£®∆µ¬ £©*Clock B/2/PWMSCLB/PWMPER67
 
	PWMDTY45=PWM45;
	//PWMDTY23 = 0;      //ÀŸ∂»Œ™0£¨º¥æ≤÷π
	PWMDTY67=PWM67;				//PWMDTY67/PWMPER67*100%
  PWME=0xff;  
}
//=====================º§π‚∞⁄Õ∑∂Êª˙∏ƒ±‰∫Ø ˝======================//
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

