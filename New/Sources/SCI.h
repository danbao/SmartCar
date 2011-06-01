/*--------------------------------------------
    Date:       2011.04.11
    Update:     2011.06.02
	˵�������ڵ��ü�����ģ��
----------------------------------------------*/
int test_sdj,test_xdj,test_speed,test_position,test_IR_position;
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
 int i=0;
 do{
 SCISend(ch[i]);
 i++;
 }while(ch[i]!='\0');
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
���ͼ������Ϣ����
��д���ڣ�200110602
-----------------------------------------  */ 
void Testjiguang(byte temp_laser_array[]) {
    int i; 
    int data;
    for(i=LASER_MAX-1;i>=0;i--)    //���ͼ������Ϣ����
        {data=temp_laser_array[i]  ;
            if(data == 0) {
            SCISend('0');   
            }
        else if(data == 1) {
             SCISend('1'); 
        }
        }   
}     
/*---------------------------------------
���ͺ�����Ϣ���飨�����죬�ݲ�ʹ�ã�
��д���ڣ�200110602
-----------------------------------------  */  
/*void TestIR(byte temp_laser_array[]) {
    int i; 
    int data;
    for(i=0;i<=6;i++)    //���ͼ������Ϣ����
        {data=temp_laser_array[i];
		SCISend_chars(data);
        }   
		data=IR_position[1]+10;
		SCISend_chars(data);
}      */

/*---------------------------------------
����ģ�鷢���ܺ���
��д���ڣ�200110602
-----------------------------------------  */  
void TestSMinfo(){
    test_sdj=temp_pwm67;		//�϶����ֵ
    test_xdj=temp_pwm45;		//�¶����ֵ
	test_speed=g_temp_pulse;	//�ٶ�ֵ
	test_position=position;		//�����˲�ֵ
	test_IR_position=IR_position[1]+10;	//�����˲�ֵ
	SCISend_chars("SED");		//���ͱ�ʶ��
	Testjiguang(light_temp_laser_array);	//���ͼ�������
   (void)sprintf(SCIreceive,"%.5d%.4d%.4d%.4d%.3d%.3d%.3d%.3d%.3d%.3d%.3d%.3dEND",test_position,test_sdj,test_xdj,test_speed,IR_temp_laser_array[0],IR_temp_laser_array[1],IR_temp_laser_array[2],IR_temp_laser_array[3],IR_temp_laser_array[4],IR_temp_laser_array[5],IR_temp_laser_array[6],test_IR_position);
   SCISend_chars(SCIreceive);
   SCISend('\n');
  }