/*--------------------------------------------
    Date:       2011.04.11
    Update:     2011.04.11
	˵�������ڵ��ü�����ģ��
----------------------------------------------*/
char jiguang[3],hongwai[28];
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
void Testjiguang(byte temp_laser_array[]) 
{ 
    int i; 
    //int data;
    //char g[20]=" ";
    for(i=LASER_MAX-1;i>=0;i--)    //���ͼ������Ϣ����
        {
            if(temp_laser_array[i] == 0) {
            SCISend('0');   
            }
        else if(temp_laser_array[i] == 1) {
             SCISend('1'); 
        }  
        }
}

/*---------------------------------------
����״̬ת��Ϊ16����
��д���ڣ�200110521
-----------------------------------------  */   
void Testhongwai(float a[]) {
int i,tmp;
char *p;
p=hongwai;
for (i=0;i<7;i++)
{
		tmp = (int)(a[i]*1000+0.5);	//ת��������ֵ
		sprintf(p, "%04d", tmp);//ת����16�����ַ���
		p+=4;
}   
}

void TestSMinfo(){
	SCISend_chars("SED");
	Testjiguang(light_temp_laser_array);
	Clear_baitou();
  //sprintf(SCIreceive," %4d ",JG_clear_position);
  sprintf(SCIreceive," %4d ",g_temp_pulse);
  SCISend_chars(SCIreceive);
	SCISend('\n');
    }
