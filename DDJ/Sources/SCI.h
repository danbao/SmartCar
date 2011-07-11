/*--------------------------------------------
    Date:       2011.04.11
    Update:     2011.06.02
	˵�������ڵ��ü�����ģ��
----------------------------------------------*/
int SCI_i=0;
byte *SCI_BP;
int *SCI_PWMDTY;
byte test_info_send=1;
//byte B8P1,B8P2,B8P3,B7P1,B7P2,B7P3,B7P4,B6P1,B6P2,B6P3,B6P4,B6P5,B5P1,B5P2,B5P3,B5P4,B5P5,B5P6,B4P1,B4P2,B4P3,B4P4,B4P5,B4P6,B4P7,B3P1,B3P2,B3P3,B3P4,B3P5,B3P6,B3P7,B3P8,B2P1,B2P2,B2P3,B2P4,B2P5,B2P6,B2P7,B2P8,B2P9,B1P1,B1P2,B1P3,B1P4,B1P5,B1P6,B1P7,B1P8,B1P9,B1P10;
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
void TestIR(byte temp_laser_array[]) {
    int i; 
    char data[5];
	SCISend_chars("SEDIR");
    for(i=0;i<=6;i++)    //���ͼ������Ϣ����
        {  
    (void)sprintf(data,"%.1d",temp_laser_array[i]);
		SCISend_chars(data);
        }
		SCISend_chars("END");
	    SCISend('\n'); 	
}      
/*---------------------------------------
������ز���
��д���ڣ�2001100607
-----------------------------------------  */ 
void Testpara(long a,int b) {
char SCIsenddata[50];
	(void)sprintf(SCIsenddata,"��ز���:%.4ld    %.5d",a,b);
    SCISend_chars(SCIsenddata);  
    SCISend('\n');  
}  
/*---------------------------------------
����ģ�鷢���ܺ���
��д���ڣ�200110602
���� t������ѭ�����η���һ��
-----------------------------------------  */  
void TestSMinfo(byte a){
if(a!=0){
Testjiguang(light_temp_laser_array);	//���ͼ�������
Testpara(speed_clear[1],PWMDTY01-PWM01);//������ز���
TestIR(IR_temp_laser_array);
}
}
/*---------------------------------------
����ģ����մ���
��д���ڣ�200110611
����  command�������ַ�������
-----------------------------------------  */ 
void SCI_REC_chuli(char a[],uchar x)
{
	char *p;
	switch(x){
  case 'A':{
	p = strtok(a, ";");
	if(*p!='*'){*SCI_BP=(byte)atoi(p);B1P1=*SCI_BP;}
	p = strtok(NULL, ";");
	if(*p!='*'){*SCI_BP=(byte)atoi(p);B1P2=*SCI_BP;}
	p = strtok(NULL, ";");
	if(*p!='*'){*SCI_BP=(byte)atoi(p);B1P3=*SCI_BP;}	
	p = strtok(NULL, ";");
	if(*p!='*'){*SCI_BP=(byte)atoi(p);B1P4=*SCI_BP;}	
	p = strtok(NULL, ";");
	if(*p!='*'){*SCI_BP=(byte)atoi(p);B1P5=*SCI_BP;}	
	p = strtok(NULL, ";");
	if(*p!='*'){*SCI_BP=(byte)atoi(p);B1P6=*SCI_BP;}	
	p = strtok(NULL, ";");
	if(*p!='*'){*SCI_BP=(byte)atoi(p);B1P7=*SCI_BP;}	
	p = strtok(NULL, ";");
	if(*p!='*'){*SCI_BP=(byte)atoi(p);B1P8=*SCI_BP;}	
	p = strtok(NULL, ";");
	if(*p!='*'){*SCI_BP=(byte)atoi(p);B1P9=*SCI_BP;}
	p = strtok(NULL, ";");
	if(*p!='*'){*SCI_BP=(byte)atoi(p);B1P10=*SCI_BP;}
		p = strtok(NULL, ";");
	if(*p!='*'){*SCI_BP=(byte)atoi(p);B1P11=*SCI_BP;}
		p = strtok(NULL, ";");
	if(*p!='*'){*SCI_BP=(byte)atoi(p);B1P12=*SCI_BP;}
		p = strtok(NULL, ";");
	if(*p!='*'){*SCI_BP=(byte)atoi(p);B1P13=*SCI_BP;}
		p = strtok(NULL, ";");
	if(*p!='*'){*SCI_BP=(byte)atoi(p);B1P14=*SCI_BP;}
  }
  break;
  case 'B':{
	p = strtok(a, ";");
	if(*p!='*'){*SCI_BP=(byte)atoi(p);B2P1=*SCI_BP;}
	p = strtok(NULL, ";");
	if(*p!='*'){*SCI_BP=(byte)atoi(p);B2P2=*SCI_BP;}
	p = strtok(NULL, ";");
	if(*p!='*'){*SCI_BP=(byte)atoi(p);B2P3=*SCI_BP;}	
	p = strtok(NULL, ";");
	if(*p!='*'){*SCI_BP=(byte)atoi(p);B2P4=*SCI_BP;}	
	p = strtok(NULL, ";");
	if(*p!='*'){*SCI_BP=(byte)atoi(p);B2P5=*SCI_BP;}	
	p = strtok(NULL, ";");
	if(*p!='*'){*SCI_BP=(byte)atoi(p);B2P6=*SCI_BP;}	
  }
  break;
  case 'P':{
	p = strtok(a, ";");
	if(*p!='*'){*SCI_PWMDTY=atoi(p);PWMDTY01=*SCI_PWMDTY;}
	p = strtok(NULL, ";");
	if(*p!='*'){*SCI_PWMDTY=atoi(p);PWMDTY23=*SCI_PWMDTY;}
	p = strtok(NULL, ";");
	if(*p!='*'){*SCI_PWMDTY=atoi(p);PWMDTY45=*SCI_PWMDTY;}		
  }
  break;
 /* case 'C':{
	p = strtok(a, ";");
	if(*p!='*'){*SCI_BP=atoi(p);B3P1=*SCI_BP;}
	p = strtok(NULL, ";");
	if(*p!='*'){*SCI_BP=atoi(p);B3P2=*SCI_BP;}
	p = strtok(NULL, ";");
	if(*p!='*'){*SCI_BP=atoi(p);B3P3=*SCI_BP;}	
	p = strtok(NULL, ";");
	if(*p!='*'){*SCI_BP=atoi(p);B3P4=*SCI_BP;}	
	p = strtok(NULL, ";");
	if(*p!='*'){*SCI_BP=atoi(p);B3P5=*SCI_BP;}	
	p = strtok(NULL, ";");
	if(*p!='*'){*SCI_BP=atoi(p);B3P6=*SCI_BP;}	
	p = strtok(NULL, ";");
	if(*p!='*'){*SCI_BP=atoi(p);B3P7=*SCI_BP;}	
	p = strtok(NULL, ";");
	if(*p!='*'){*SCI_BP=atoi(p);B3P8=*SCI_BP;}	
  }
  break;
    case 'D':{
	p = strtok(a, ";");
	if(*p!='*'){*SCI_BP=atoi(p);B4P1=*SCI_BP;}
	p = strtok(NULL, ";");
	if(*p!='*'){*SCI_BP=atoi(p);B4P2=*SCI_BP;}
	p = strtok(NULL, ";");
	if(*p!='*'){*SCI_BP=atoi(p);B4P3=*SCI_BP;}	
	p = strtok(NULL, ";");
	if(*p!='*'){*SCI_BP=atoi(p);B4P4=*SCI_BP;}	
	p = strtok(NULL, ";");
	if(*p!='*'){*SCI_BP=atoi(p);B4P5=*SCI_BP;}	
	p = strtok(NULL, ";");
	if(*p!='*'){*SCI_BP=atoi(p);B4P6=*SCI_BP;}	
	p = strtok(NULL, ";");
	if(*p!='*'){*SCI_BP=atoi(p);B4P7=*SCI_BP;}	
  }
  break;
    case 'E':{
	p = strtok(a, ";");
	if(*p!='*'){*SCI_BP=atoi(p);B5P1=*SCI_BP;}
	p = strtok(NULL, ";");
	if(*p!='*'){*SCI_BP=atoi(p);B5P2=*SCI_BP;}
	p = strtok(NULL, ";");
	if(*p!='*'){*SCI_BP=atoi(p);B5P3=*SCI_BP;}	
	p = strtok(NULL, ";");
	if(*p!='*'){*SCI_BP=atoi(p);B5P4=*SCI_BP;}	
	p = strtok(NULL, ";");
	if(*p!='*'){*SCI_BP=atoi(p);B5P5=*SCI_BP;}	
	p = strtok(NULL, ";");
	if(*p!='*'){*SCI_BP=atoi(p);B5P6=*SCI_BP;}	
  }
  break;
    case 'F':{
	p = strtok(a, ";");
	if(*p!='*'){*SCI_BP=atoi(p);B6P1=*SCI_BP;}
	p = strtok(NULL, ";");
	if(*p!='*'){*SCI_BP=atoi(p);B6P2=*SCI_BP;}
	p = strtok(NULL, ";");
	if(*p!='*'){*SCI_BP=atoi(p);B6P3=*SCI_BP;}	
	p = strtok(NULL, ";");
	if(*p!='*'){*SCI_BP=atoi(p);B6P4=*SCI_BP;}	
	p = strtok(NULL, ";");
	if(*p!='*'){*SCI_BP=atoi(p);B6P5=*SCI_BP;}	
  }
  break;
    case 'G':{
	p = strtok(a, ";");
	if(*p!='*'){*SCI_BP=atoi(p);B7P1=*SCI_BP;}
	p = strtok(NULL, ";");
	if(*p!='*'){*SCI_BP=atoi(p);B7P2=*SCI_BP;}
	p = strtok(NULL, ";");
	if(*p!='*'){*SCI_BP=atoi(p);B7P3=*SCI_BP;}	
	p = strtok(NULL, ";");
	if(*p!='*'){*SCI_BP=atoi(p);B7P4=*SCI_BP;}	
  }
  break;
    case 'H':{
	p = strtok(a, ";");
	if(*p!='*'){*SCI_BP=atoi(p);B8P1=*SCI_BP;}
	p = strtok(NULL, ";");
	if(*p!='*'){*SCI_BP=atoi(p);B8P2=*SCI_BP;}
	p = strtok(NULL, ";");
	if(*p!='*'){*SCI_BP=atoi(p);B8P3=*SCI_BP;}	
  }
  break; */
}   
}

/*---------------------------------------
����ģ�鷵�ص�ǰ����ֵ
��д���ڣ�200110612
-----------------------------------------  */ 
void SCI_REC_NOW(){
char SCIsend[100];
 /*CISend('\n');  
	(void)sprintf(SCIsend,"BP8ֵ:%.2d %.2d %.2d",B8P1,B8P2,B8P3);		
  SCISend_chars(SCIsend);
  SCISend('\n'); 
	(void)sprintf(SCIsend,"BP7ֵ:%.2d %.2d %.2d %.2d",B7P1,B7P2,B7P3,B7P4);		
  SCISend_chars(SCIsend);
  SCISend('\n'); 
	(void)sprintf(SCIsend,"BP6ֵ:%.2d %.2d %.2d %.2d %.2d",B6P1,B6P2,B6P3,B6P4,B6P5);		
  SCISend_chars(SCIsend);
  SCISend('\n'); 
	(void)sprintf(SCIsend,"BP5ֵ:%.2d %.2d %.2d %.2d %.2d %.2d",B5P1,B5P2,B5P3,B5P4,B5P5,B5P6);		
  SCISend_chars(SCIsend);
  SCISend('\n');
	(void)sprintf(SCIsend,"BP4ֵ:%.2d %.2d %.2d %.2d %.2d %.2d %.2d",B4P1,B4P2,B4P3,B4P4,B4P5,B4P6,B4P7);		
  SCISend_chars(SCIsend);
  SCISend('\n'); 
	(void)sprintf(SCIsend,"BP3ֵ:%.2d %.2d %.2d %.2d %.2d %.2d %.2d %.2d",B3P1,B3P2,B3P3,B3P4,B3P5,B3P6,B3P7,B3P8);		
  SCISend_chars(SCIsend); */
  SCISend('\n'); 
	(void)sprintf(SCIsend,"BP2ֵ:%.2d %.2d %.2d %.2d %.2d %.2d %.2d %.2d %.2d",B2P1,B2P2,B2P3,B2P4,B2P5,B2P6,B2P7,B2P8,B2P9);		
  SCISend_chars(SCIsend);
  SCISend('\n'); 
	(void)sprintf(SCIsend,"BP1ֵ:%.2d %.2d %.2d %.2d %.2d %.2d %.2d %.2d %.2d %.2d",B1P1,B1P2,B1P3,B1P4,B1P5,B1P6,B1P7,B1P8,B1P9,B1P10);		
  SCISend_chars(SCIsend);
  SCISend('\n');   
}

/*---------------------------------------
���ߴ����жϽ���
��д���ڣ�20110411
-----------------------------------------*/
#pragma CODE_SEG __NEAR_SEG NON_BANKED 
interrupt 20 void Rx_SCI(void)
{
    DisableInterrupts; 
      	test_info_send=0;
      SCIreceive[SCI_i]=SCI_RXD();
      switch(SCIreceive[SCI_i]) {
        case 'A': 
        {
          SCI_i=0;
          SCI_REC_chuli(SCIreceive,'A');  //����BP1
        }  
        break;
        case 'B': 
        {
          SCI_i=0;
          SCI_REC_chuli(SCIreceive,'B');  //����BP2
        }  
        break;
      /*case 'C': 
        {
          SCI_i=0;
          SCI_REC_chuli(SCIreceive,'C');  //����BP3
        }  
        break;
        case 'D': 
        {
          SCI_i=0;
          SCI_REC_chuli(SCIreceive,'D');  //����BP4
        }  
        break;
        case 'E': 
        {
          SCI_i=0;
          SCI_REC_chuli(SCIreceive,'E');  //����BP5
        }  
        break;
        case 'F': 
        {
          SCI_i=0;
          SCI_REC_chuli(SCIreceive,'F');  //����BP6
        }  
        break;
        case 'G': 
        {
          SCI_i=0;
          SCI_REC_chuli(SCIreceive,'G');  //����BP7
        }  
        case 'H': 
        {
          SCI_i=0;
          SCI_REC_chuli(SCIreceive,'H');  //����BP8
        }  
        break;   */
        case 'N': 
        {
          SCI_i=0;
          SCI_REC_NOW();              	 //������ֵ
        }  
        break;
        case 'R': 
        {
        SCI_i=0;
		test_info_send=1; 				//��������
        }
        break;
        case 'P': 
        {
         SCI_i=0;
        SCI_REC_chuli(SCIreceive,'P'); //�ı��ٶ�ֵ
        }  
        break;
      default:
        SCI_i++;
        break; 
      }
    EnableInterrupts;
} 
#pragma CODE_SEG DEFAULT