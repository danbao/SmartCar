/*============================================
����MC9S12XS128�๦�ܿ����� 
Designed by Chiu Sir
E-mail:chiusir@163.com
����汾:V1.1
������:2009��11��26��
�����Ϣ�ο����е�ַ��
��վ��  http://www.lqist.cn
�Ա��꣺http://shop36265907.taobao.com   
============================================*/
#include "derivative.h" 
#include "LQprintp.h"
#include "LQSDdriver.h"

         
#define SD_Sel()   PTM_PTM3=0        //�͵�ƽ
#define SD_deSel() PTM_PTM3=1        //�ߵ�ƽ

extern byte RXBUF[]; 

#pragma CODE_SEG DEFAULT  
void Dly_ms(int ms)
{   
   int ii,jj;
   if (ms<1) ms=1;
   for(ii=0;ii<ms;ii++)
     for(jj=0;jj<1335;jj++);  //16MHz--1ms
     
}
void New_Buf8(byte buffer[],byte ch)
{
    //-- Tx & Rx Buffer initialize
    int i, j=0;
    for(i=0;i<512;i++)
		*(buffer+i)=ch;   
}

void CLS_Buf8(byte buffer[])
{
    //-- Flushing Rx buffer 
    int i;     
    for(i=0;i<512;i++)
		*(buffer+i)=0;
}
void View_Buf8(byte buffer[])
{
    int i=0;
    for(i=0;i<512;i++)
    {          
        if((i%32)==0)	  printp( "\n" );
        printp("%02x,", buffer[i]);
    }    
}  
/*******************************************
*                ��ʼ������                *
********************************************/  
void SCI_Init(void) 
{
  SCI0CR2=0x2c; //enable Receive Full Interrupt,RX enable,Tx enable
  SCI0BDH=0x00; //busclk  8MHz,19200bps,SCI0BDL=0x1a
  SCI0BDL=0x34; //SCI0BDL=busclk/(16*SCI0BDL)=19200                 
}
void InitPorts(void) 
{   
  DDRB= 0xff;          // set  port B bit0 as output
  PORTB=0X0;
} 
void SetBusCLK_16M(void)
{   
    CLKSEL=0X00;				// disengage PLL to system
    PLLCTL_PLLON=1;			// turn on PLL
    SYNR=0x00 | 0x01; 	// VCOFRQ[7:6];SYNDIV[5:0]
                        // fVCO= 2*fOSC*(SYNDIV + 1)/(REFDIV + 1)
                        // fPLL= fVCO/(2 �� POSTDIV) 
                        // fBUS= fPLL/2 
                        // VCOCLK Frequency Ranges  VCOFRQ[7:6]
                        // 32MHz <= fVCO <= 48MHz    00
                        // 48MHz <  fVCO <= 80MHz    01
                        // Reserved                  10
                        // 80MHz <  fVCO <= 120MHz   11				
    REFDV=0x80 | 0x01;  // REFFRQ[7:6];REFDIV[5:0]
                        // fREF=fOSC/(REFDIV + 1)
                        // REFCLK Frequency Ranges  REFFRQ[7:6]
                        // 1MHz <= fREF <=  2MHz       00
                        // 2MHz <  fREF <=  6MHz       01
                        // 6MHz <  fREF <= 12MHz       10
                        // fREF >  12MHz               11                         
                        // pllclock=2*osc*(1+SYNR)/(1+REFDV)=32MHz;
    POSTDIV=0x00;       // 4:0, fPLL= fVCO/(2xPOSTDIV)
                        // If POSTDIV = $00 then fPLL is identical to fVCO (divide by one).
    _asm(nop);          // BUS CLOCK=16M
    _asm(nop);
    while(!(CRGFLG_LOCK==1));	  //when pll is steady ,then use it;
    CLKSEL_PLLSEL =1;		        //engage PLL to system; 
}
void Init_Dev(void)
{
  SetBusCLK_16M();
  InitPorts();
  PORTB=0;   
  SCI_Init();      
}   
 
//д����һ���ֽ�
byte SPI_RdWr_Byte(byte val)
{
	while (!SPI0SR_SPTEF);   
	SPI0DRL = val;
	while(!(SPI0SR_SPIF));
	return SPI0DRL;
}
void SPI_High_Rate(void) 
{ 
  //��߲������ʲ��ܸ���25Mbps
  SPI0BR  = 0x02; //BR=busclk/((SPPR + 1)�� 2^(SPR + 1))=16M/8=2M                
};
//sd����ʼ��
void SD_Init(void)
{ 	
  MODRR_MODRR4 =0;   //ʹ��M��
  DDRM    = 0x38;    //�����ʼ��IO����  
  SPI0CR2 = 0x10;
  SPI0CR1 = 0x5e;    //
  SPI0BR  = 0x44;    //��ʼ���õ�����
	SD_deSel();
}

//sd��д����
byte SD_Send_Cmd(byte cmd, dword arg)
{
	byte r1;
	byte retry=0;
	
	(void)SPI_RdWr_Byte(0xff);
	SD_Sel();
	
	(void)SPI_RdWr_Byte(cmd | 0x40);          //�ֱ�д������
	(void)SPI_RdWr_Byte((byte)(arg>>24));
	(void)SPI_RdWr_Byte((byte)(arg>>16));
	(void)SPI_RdWr_Byte((byte)(arg>>8));
	(void)SPI_RdWr_Byte((byte)(arg));
	(void)SPI_RdWr_Byte(0x95);
	r1 = SPI_RdWr_Byte(0xff);
	while(r1== 0xff) //�ȴ���Ӧ��
	{
	  r1 = SPI_RdWr_Byte(0xff);
		if(++retry > 100) break;                //��ʱ�˳�
	}
	SD_deSel();

	return r1;                                //����״ֵ̬
}

//sd����λ
byte SD_Reset(void)
{
	byte i;
	byte retry;
	byte r1=0;
	retry = 0; 	
	do
	{
		for(i=0;i<10;i++) 
		  (void)SPI_RdWr_Byte(0xff);
		r1 = SD_Send_Cmd(0, 0);                 //��idle���� 	
		if(++retry>100) return 1;               //��ʱ�˳�
	}while(r1 != 0x01);   

	retry = 0;
	do
	{
		r1 = SD_Send_Cmd(1, 0);           //��active����  		
		if(++retry>100) return 1;         //��ʱ�˳�
	} while(r1);
	
	r1 = SD_Send_Cmd(59, 0);            //��crc

	r1 = SD_Send_Cmd(16, 512);          //��������С512

	return 0;                           //��������
}


#pragma CODE_SEG DEFAULT
//дһ������
byte Wt_Block(dword sector, byte* buffer)
{
	byte r1;
	word i;
	//byte retry=0;
  if(sector<1) return 0xff;         //Ϊ�˱���SD������������������
	r1 = SD_Send_Cmd(24, sector<<9);  //д����
	if(r1 != 0x00) return r1;

	SD_Sel();
	
	(void)SPI_RdWr_Byte(0xff);
	(void)SPI_RdWr_Byte(0xff);
	(void)SPI_RdWr_Byte(0xff); 
	(void)SPI_RdWr_Byte(0xfe);        //����ʼ��
	
	for(i=0; i<512; i++)              //��512�ֽ�����
	{
		(void)SPI_RdWr_Byte(*buffer++);
	}
	
	(void)SPI_RdWr_Byte(0xff);
	(void)SPI_RdWr_Byte(0xff);
	
	r1 = SPI_RdWr_Byte(0xff);
	
	if((r1&0x1f) != 0x05)             //�ȴ��Ƿ�ɹ�
	{
	  SD_deSel();
		return r1;
	}
	//�ȴ�������
	while(!SPI_RdWr_Byte(0xff));      //if(++retry > 50){SPI_CS_Deassert();return 1;}

  SD_deSel();

	return 0;     
}
 
//��һ������
byte Rd_Block(dword sector, byte* buffer)
{
	byte r1;          
	word i;
	//byte retry=0;

	r1 = SD_Send_Cmd(17, sector<<9);//������ 	
	if(r1 != 0x00) 		return r1;

	SD_Sel();
	//�����ݵĿ�ʼ
	while(SPI_RdWr_Byte(0xff) != 0xfe);//if(++retry > 50){SD_deSel();return 1;}

	for(i=0; i<512; i++)//��512������
	{
		*buffer++ = SPI_RdWr_Byte(0xff);
	}

	(void)SPI_RdWr_Byte(0xff);//αcrc
	(void)SPI_RdWr_Byte(0xff);  	
	SD_deSel();

	return 0;
} 


#pragma CODE_SEG DEFAULT 


// 

