/*--------------------------------------------
    Date:       2011.04.11
    Update:     2011.05.31
	˵�������ڵ��ü�����ģ��
----------------------------------------------*/
char jiguang[3];
int sdj,xdj,speed;
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
����״̬ת��Ϊ16����
��д���ڣ�200110521
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
/*=====================���߷����ܲ���======================*/
void TestSMinfo(){
  int	IR_position[2]={0,10};
    sdj=99;
    xdj=99;
//	speed=g_temp_pulse;
speed=200;
	position=99;  
//	Clear_baitou();
	SCISend_chars("SED");
	Testjiguang(light_temp_laser_array);
   (void)sprintf(SCIreceive,"%.5d%.4d%.4d%.4d%.3d%.3d%.3d%.3d%.3d%.3d%.3d%.3dEND",position,sdj,xdj,speed,IR_temp_laser_array[0],IR_temp_laser_array[1],IR_temp_laser_array[2],IR_temp_laser_array[3],IR_temp_laser_array[4],IR_temp_laser_array[5],IR_temp_laser_array[6],IR_position[1]+10);
   SCISend_chars(SCIreceive);
    SCISend('\n');
  }