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
 #pragma CODE_SEG __NEAR_SEG NON_BANKED 
//===================��ͷ����ж�================//

interrupt 20 void Rx_SetDriver(void)
{
    char tmp;
    char result;
    DisableInterrupts;
    tmp = SCI0SR1;                   //�����־
    result= SCI_RXD();
    switch(result)
    {
      case 'd':                          //�����ͷ�������ƫ����
    temp_pwm67=temp_pwm67+5;
    Light_SetDriver(temp_pwm67);
    sprintf(SCIreceive,"��ǰ���ֵΪ:%d",temp_pwm67);  
     SCISend_chars(SCIreceive);   
      break;
            case 'a':                   //�����ͷ�������ƫ����
        temp_pwm67=temp_pwm67-5;
		Light_SetDriver(temp_pwm67);
    sprintf(SCIreceive,"��ǰ���ֵΪ:%d",temp_pwm67);  
     SCISend_chars(SCIreceive); 
      break;
	  case 'q':                          //�����ͷ�������ƫ����
        temp_pwm67=temp_pwm67+1;
		Light_SetDriver(temp_pwm67);
    sprintf(SCIreceive,"��ǰ���ֵΪ:%d",temp_pwm67);  
     SCISend_chars(SCIreceive); 
      break;
            case 'e':                   //�����ͷ�������ƫ����
        temp_pwm67=temp_pwm67-1;
		Light_SetDriver(temp_pwm67);
    sprintf(SCIreceive,"��ǰ���ֵΪ:%d",temp_pwm67);  
     SCISend_chars(SCIreceive); 
      break;
            case 'r':                      //�����ͷ�������
        temp_pwm67=PWM67; 
		Light_SetDriver(temp_pwm67);
		sprintf(SCIreceive,"�����λ��ǰ���ֵΪ:%d",temp_pwm67);  
     SCISend_chars(SCIreceive); 
      break;
            case 'j':                          //ת���ͷ�������ƫ���� 5�ȵ�
        temp_pwm45=temp_pwm45+5;
        SCI_SetDriver(temp_pwm45);
       SCISend('j'); 
      break;
            case 'l':                         //ת���ͷ�������ƫ���� 5�ȵ�
        temp_pwm45=temp_pwm45-5;
        SCI_SetDriver(temp_pwm45);
       SCISend('l'); 
      break;
            case 'n':                          //ת���ͷ�������ƫ���� 5�ȵ�
        temp_pwm45=temp_pwm45+1;
        SCI_SetDriver(temp_pwm45);
       SCISend('n'); 
      break;
            case 'm':                         //ת���ͷ�������ƫ���� 5�ȵ�
        temp_pwm45=temp_pwm45-1;
        SCI_SetDriver(temp_pwm45);
       SCISend('m'); 
      break;
            case 'p':                      //ת���ͷ�������
        temp_pwm45=PWM45; 
        SCI_SetDriver(temp_pwm45);
       SCISend('p');
      break;
    }
    EnableInterrupts;
}
#pragma CODE_SEG DEFAULT