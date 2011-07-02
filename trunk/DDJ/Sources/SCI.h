/*--------------------------------------------
    Date:       2011.04.11
    Update:     2011.06.02
	˵�������ڵ��ü�����ģ��
----------------------------------------------*/
int SCI_i=0;
int *SCI_PWMDTY,*SCI_DP;
byte test_info_send=1;
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
void Testpara(int test_sdj,int test_xdj,int test_speed,int test_position) {
char SCIsenddata[50];
	(void)sprintf(SCIsenddata,"SEDPR%.5d%.4d%.4d%.4dEND",test_position+10000,test_sdj,test_xdj,test_speed);
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
Testpara(PWMDTY67,PWMDTY45,speed_clear[1],JG_clear[3]);//������ز���
TestIR(IR_temp_laser_array);
}
}
/*---------------------------------------
����ģ����մ���
��д���ڣ�200110611
����  command�������ַ�������
-----------------------------------------  */ 
void SCI_REC_chuli(char a[],int x)
{
	char *p;
	char *q;
	switch(x){
  case 1:{
	p = strtok(a, ";");
	if(*p!='F'){*SCI_DP=atoi(p);DP1=*SCI_DP;}
	p = strtok(NULL, ";");
	if(*p!='F'){*SCI_DP=atoi(p);DP2=*SCI_DP;}
	p = strtok(NULL, ";");
	if(*p!='F'){*SCI_DP=atoi(p);DP3=*SCI_DP;}
	p = strtok(NULL, ";");
	if(*p!='F'){*SCI_DP=atoi(p);DP4=*SCI_DP;}
	p = strtok(NULL, ";");
	if(*p!='F'){*SCI_DP=atoi(p);DP5=*SCI_DP;}
	p = strtok(NULL, ";");
	if(*p!='F'){*SCI_DP=atoi(p);DP6=*SCI_DP;} 
	p = strtok(NULL, ";");
	if(*p!='F'){*SCI_DP=atoi(p);DP7=*SCI_DP;}
  }
  break; 
  case 3:{
	p = strtok(a, ";");
	if(*p!='F'){*SCI_DP=atoi(p);BP1=*SCI_DP;}
	p = strtok(NULL, ";");
	if(*p!='F'){*SCI_DP=atoi(p);BP2=*SCI_DP;}
	p = strtok(NULL, ";");
	if(*p!='F'){*SCI_DP=atoi(p);BP3=*SCI_DP;}
	p = strtok(NULL, ";");
	if(*p!='F'){*SCI_DP=atoi(p);BP4=*SCI_DP;}
	p = strtok(NULL, ";");
	if(*p!='F'){*SCI_DP=atoi(p);BP5=*SCI_DP;}
	p = strtok(NULL, ";");
	if(*p!='F'){*SCI_DP=atoi(p);BP6=*SCI_DP;} 
	p = strtok(NULL, ";");
	if(*p!='F'){*SCI_DP=atoi(p);BP7=*SCI_DP;}
	p = strtok(NULL, ";");
	if(*p!='F'){*SCI_DP=atoi(p);BP8=*SCI_DP;}
	p = strtok(NULL, ";");
	if(*p!='F'){*SCI_DP=atoi(p);BP9=*SCI_DP;}
	p = strtok(NULL, ";");
	if(*p!='F'){*SCI_DP=atoi(p);BP10=*SCI_DP;}
  }
  break; 
	case 2:{
	q = strtok(a, ";"); 
	{
	  *SCI_PWMDTY=atoi(q); 
  PWMDTY01=*SCI_PWMDTY;
	}
	q = strtok(NULL, ";"); 
	{
	  *SCI_PWMDTY=atoi(q);
	PWMDTY23=*SCI_PWMDTY;
	}
	}   
	break;
	}
}
/*---------------------------------------
����ģ�鷵�ص�ǰ����ֵ
��д���ڣ�200110612
-----------------------------------------  */ 
void SCI_REC_NOW(){
char SCIsend[80];
	(void)sprintf(SCIsend,"SEDNW%.3d%.3d%.3d%.3d%.3d%.3d%.3d%.4d%.4d%.2d%.2d%.2d%.2d%.2d%.2d%.2d%.2d%.2d%.2dEND",DP1,DP2,DP3,DP4,DP5,DP6,DP7,PWMDTY01,PWMDTY45,BP1,BP2,BP3,BP4,BP5,BP6,BP7,BP8,BP9,BP10);		
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
        case '@': 
        {
          SCI_i=0;
          SCI_REC_chuli(SCIreceive,1);
        }  
        break;
        case '&': 
        {
          SCI_i=0;
          SCI_REC_chuli(SCIreceive,3);
        }  
        break;
        case '$': 
        {
          SCI_i=0;
          SCI_REC_NOW();
        }  
        break;
        case '#': 
        {
          SCI_i=0;
         SCI_REC_chuli(SCIreceive,2);
        }
        break;
        case '%': 
        {
          SCI_i=0;
      test_info_send=1; 
        }
        break;
      default:
        SCI_i++;
         break; 
      }
    EnableInterrupts;
} 
#pragma CODE_SEG DEFAULT