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
����״̬ת��Ϊ16����
��д���ڣ�200110521
-----------------------------------------  */         
void Testjiguang(byte a[12]) 
{ 
char b[3]; 
int i,result = 0,k = 1,j = 0; 
for(i = 11;i >= 0;i --) 
{ 
if(a[11-i] == '1') result += 1 << (k-1); //�����1����1*λȨ 
if(k == 4 || i == 0) //ÿ��λ����һ�ν����result���� 
//����������λ��i==0��������λ������100 0000����Ҳ���� 
{ 
switch(result) 
{ 
case 10: b[j++]='A';break; //���ڵ���ʮת������ĸ 
case 11: b[j++]='B';break; 
case 12: b[j++]='C';break; 
case 13: b[j++]='D';break; 
case 14: b[j++]='E';break; 
case 15: b[j++]='F';break; 
default: b[j++]=result + '0';break; 
} 
result = 0; //������� 
k = 0; //��ʾλȨ��K���� 
} 
k ++; // ��ʼλȨΪ1 
}
for(i = 2;i >= 0;i --) 
jiguang[2-i]=b[i];
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
  //  sdj=rand()%10000;
 //   xdj=rand()%10000;
//	speed=rand()%10000;
	Testjiguang(light_temp_laser_array);
//	Testhongwai(IR_temp_laser_array);
  Clear_baitou();
    sprintf(SCIreceive,"SED%.s%d",jiguang,JG_clear_position);
    SCISend_chars(SCIreceive);
    }
