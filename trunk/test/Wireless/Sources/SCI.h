/*--------------------------------------------
    Date:       2011.04.11
    Update:     2011.04.11
	˵�������ڵ��ü�����ģ��
----------------------------------------------*/
/*--------------------------------------------
SCI_RXD: ���ڽ��պ���
��д���ڣ�20110411
----------------------------------------------*/
char SCI_RXD(void)
{
    char ch; 
    while (!(SCI0SR1 & 0x20));       //�ȴ������������
    SCI0SR1_RDRF = 1;
    ch = SCI0DRL;
    return ch;
}
/*---------------------------------------------
SCISend: ���������ʾ����(��ʾ�����ַ�)
���������ch����ʾ���ַ���
��д���ڣ�20110411
-----------------------------------------------*/
void SCISend(unsigned char ch)
{ 
  if (ch == '\n')  
  {
      while(!(SCI0SR1&0x80)) ;     
      SCI0DRL= 0x0d;   
      while(!(SCI0SR1&0x80)) ;     
      SCI0DRL= 0x0a;               
     return;
  } 
  else while (!(SCI0SR1&0x80));
    SCI0DRH=0;
    SCI0DRL=ch;
}
/*---------------------------------------------
LCD_write_cizu: ���������ʾ����(��ʾ�ַ���)
���������ch����ʾ���ַ���
��д���ڣ�20110411
-----------------------------------------------*/
void SCISend_chars(const signed char ch[])
 {
 int i;
 for(i=0;i<strlen(ch);i++) {
 SCISend(ch[i]);
 }
 SCISend('\n');
 }
 /*---------------------------------------
SCI_Init: SCI��ʼ��
��д���ڣ�200110411
-----------------------------------------  */
static void SCI_Init(void)  //SCI
{
    SCI0CR1=0x00;
    SCI0CR2=0x2c;
     SCI0BD=260;                     //���ò����ʹ�ʽ=����Ƶ��/����Ҫ�Ĳ�����/16=��Ҫ���õ�ֵ;
                  
}
 /*---------------------------------------
SCI�ж�
��д���ڣ�200110411
-----------------------------------------  */
#pragma CODE_SEG __NEAR_SEG NON_BANKED 
interrupt 20 void Rx_SCI(void)
{
    char tmp;
    char result;
    DisableInterrupts;
    tmp = SCI0SR1;                  	 //�����־
    result= SCI_RXD();
    switch(result)
    {
    case 'p':							 //����P1ֵ
     Prop1=Prop1+5;
     sprintf(SCIreceive,"Proportion1ֵΪ:%d",Prop1);  
     SCISend_chars(SCIreceive);
      break;
      case 'c':                          //����
    SCISend_chars("clear");
    LCD_clear();
      break;
    }
    EnableInterrupts;
}
#pragma CODE_SEG DEFAULT