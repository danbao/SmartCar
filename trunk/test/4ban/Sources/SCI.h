/*--------------------------------------------
    Date:       2011.04.11
    Update:     2011.04.11
	˵�������ڵ��ü�����ģ��
----------------------------------------------*/
int SCI_i=0;
int *SCI_PWMDTY;
byte *SCI_PWM7;
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

void SendSmartcarInfo(byte temp_laser_array[]) {
    int i; 
    int data;
    char g[20]=" ";
    for(i=LASER_MAX-1;i>=0;i--)    //���ͼ������Ϣ����
        {data=temp_laser_array[i]  ;
            if(data == 0) {
            SCISend('0');   
            }
        else if(data == 1) {
             SCISend('1'); 
        }
        }
//  SCISend('\n');
 // sprintf(g,"%u",p);
  //for(i=0;g[i]!='\0';i++)
  //SCISend(g[i]);  
     
}

void SCI_chuli(char a[],char x)
{
	char *q;
	char SCIsend[50];
	switch(x){ 
	case 'X':{
	q = strtok(a, "X"); 
	{
	  *SCI_PWMDTY=atoi(q); 
  PWMDTY01=*SCI_PWMDTY;
  (void)sprintf(SCIsend,"��ǰ��ͷ���ֵΪ:%d",PWMDTY01);  
  SCISend_chars(SCIsend);
	}
	}   
	break;
	case 'S':{
	q = strtok(a, "S"); 
	{
  *SCI_PWMDTY=atoi(q); 
  PWMDTY45=*SCI_PWMDTY;
  (void)sprintf(SCIsend,"��ǰת�Ƕ��ֵΪ:%d",PWMDTY45);  
  SCISend_chars(SCIsend); 
	}
	}   
	break;
	case 'P':{
	q = strtok(a, "P"); 
	{
	*SCI_PWM7=(byte)atoi(q); 
  PWMPER7=*SCI_PWM7;
  (void)sprintf(SCIsend,"P7�ڵ�Ƶ��Ϊ:%d",PWMPER7);  
  SCISend_chars(SCIsend);
	}
	}   
	break;
	case 'Z':{
	q = strtok(a, "Z"); 
	{
	*SCI_PWM7=(byte)atoi(q); 
  PWMDTY7=*SCI_PWM7;
  (void)sprintf(SCIsend,"P7�ڵ�ռ�ձ�Ϊ:%d",PWMDTY7);  
  SCISend_chars(SCIsend);
	}
	}   
	break;
}
}
/*---------------------------------------
���ߴ����жϽ���
��д���ڣ�20110411
-----------------------------------------*/
#pragma CODE_SEG __NEAR_SEG NON_BANKED 
interrupt 20 void Rx_SCI(void)
{
    DisableInterrupts;
      SCIreceive[SCI_i]=SCI_RXD();
      switch(SCIreceive[SCI_i]) {
        case 'S': 
        {
        SCI_chuli(SCIreceive,'S');
        SCI_i=0; 
        }  
        break;
        case 'X': 
        {
        SCI_chuli(SCIreceive,'X');
        SCI_i=0; 
        }  
        break;
        case 'P': 
        {

        SCI_chuli(SCIreceive,'P');
        SCI_i=0;
        }
        break;
        case 'Z': 
        {
        SCI_chuli(SCIreceive,'Z');
        SCI_i=0;
        }
        break;
      default:
        SCI_i++;
        break; 
      }
    EnableInterrupts;
} 
#pragma CODE_SEG DEFAULT