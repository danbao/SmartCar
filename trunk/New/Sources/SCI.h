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
void SCISend_chars(const char ch[])
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
���ߴ����ж�
��д���ڣ�200110411
-----------------------------------------  */         
#pragma CODE_SEG __NEAR_SEG NON_BANKED 
interrupt 20 void Rx_SCI(void)
{	
    char tmp;
    char result;
    DisableInterrupts;
    tmp = SCI0SR1; 	//�����־
    result= SCI_RXD();
    switch(result)
    {
      case 'q':							 //����P1ֵ
      YP1=YP1+0.2;
     sprintf(SCIreceive,"ҡͷP1ֵΪ:%.1f",YP1);  
     SCISend_chars(SCIreceive);    
      break;
      case 'a':							 //��СP1ֵ
      YP1=YP1-0.2;
     sprintf(SCIreceive,"ҡͷP1ֵΪ:%.1f",YP1);  
     SCISend_chars(SCIreceive);    
      break;
      case 'w':							 //����P2ֵ
      YP2=YP2+0.2;
     sprintf(SCIreceive,"ҡͷP2ֵΪ:%.1f",YP2);  
     SCISend_chars(SCIreceive);    
      break;      
      case 's':							 //��СP2ֵ
      YP2=YP2-0.2;
     sprintf(SCIreceive,"ҡͷP2ֵΪ:%.1f",YP2);  
     SCISend_chars(SCIreceive);    
      break;
      case 'e':							 //����P3ֵ
      YP3=YP3+0.2;
     sprintf(SCIreceive,"ҡͷP3ֵΪ:%.1f",YP3);  
     SCISend_chars(SCIreceive);    
      break;
      case 'd':							 //��СP3ֵ
      YP3=YP3-0.2;
     sprintf(SCIreceive,"ҡͷP3ֵΪ:%.1f",YP3);  
     SCISend_chars(SCIreceive);    
      break;
      case 'r':							 //����P4ֵ
      YP4=YP4+0.2;
     sprintf(SCIreceive,"ҡͷP4ֵΪ:%.1f",YP4);  
     SCISend_chars(SCIreceive);    
      break;
      case 'f':							 //��СP4ֵ
      YP4=YP4-0.2;
     sprintf(SCIreceive,"ҡͷP4ֵΪ:%.1f",YP4);  
     SCISend_chars(SCIreceive);    
      break;
      case 't':							 //����P5ֵ
      YP5=YP5+0.2;
     sprintf(SCIreceive,"ҡͷP5ֵΪ:%.1f",YP5);  
     SCISend_chars(SCIreceive);
      case 'g':							 //��СP5ֵ
      YP5=YP5-0.2;
     sprintf(SCIreceive,"ҡͷP5ֵΪ:%.1f",YP5);  
     SCISend_chars(SCIreceive);      
      break;
    }
    EnableInterrupts;
}
#pragma CODE_SEG DEFAULT