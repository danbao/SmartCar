/*--------------------------------------------
    Date:       2011.04.11
    Update:     2011.06.02
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
	SCISend_chars("SEDJG");
    for(i=LASER_MAX-1;i>=0;i--)    //���ͼ������Ϣ����
        {data=temp_laser_array[i]  ;
            if(data == 0) {
            SCISend('0');   
            }
        else if(data == 1) {
             SCISend('1'); 
        }
        } 
    SCISend_chars("END");
    SCISend('\n'); 		
}     
/*---------------------------------------
���ͺ�����Ϣ���飨�����죬�ݲ�ʹ�ã�
��д���ڣ�200110607
----------------------------------------- */ 
void TestIR(uint temp_laser_array[],int Test_IR_position) {
    int i; 
    char data[5];
	SCISend_chars("SEDIR");
    for(i=0;i<=6;i++)    //���ͼ������Ϣ����
        {  
    (void)sprintf(data,"%.3d",temp_laser_array[i]);
		SCISend_chars(data);
        }
		(void)sprintf(data,"%.3d",Test_IR_position+10);		
		SCISend_chars(data);
		SCISend_chars("END");
	    SCISend('\n'); 	
}      
/*---------------------------------------
������ز���
��д���ڣ�2001100607
-----------------------------------------  */ 
void Testpara(int test_sdj,int test_xdj,int test_speed,int test_position) {
	(void)sprintf(SCIreceive,"SEDPR%.5d%.4d%.4d%.4dEND",test_position+10000,test_sdj,test_xdj,test_speed);
    SCISend_chars(SCIreceive);  
    SCISend('\n');  
}  
/*---------------------------------------
����ģ�鷢���ܺ���
��д���ڣ�200110602
���� t������ѭ�����η���һ��
-----------------------------------------  */  
void TestSMinfo(void){
Testjiguang(light_temp_laser_array);	//���ͼ�������
Testpara(PWMDTY67,PWMDTY45,speed_clera[1],JG_clear[3]);//������ز���
TestIR(IR_temp_laser_array,IR_position[1]);
  }