//=================AD��ʼ��===========================//



 void AD_Init(void)     
{
  
  ATD0CTL1=0x00;  //ѡ��ADͨ��Ϊ�ⲿ����,8λ����,����ǰ���ŵ� 
  ATD0CTL2=0x40;   //��־λ�Զ����㣬��ֹ�ⲿ����, ��ֹ�ж�    
  ATD0CTL3=0x88;   //�Ҷ����޷���,ÿ��ת��1������, No FIFO, Freezeģʽ�¼���ת;      
  ATD0CTL4=0x01;  //����ʱ��Ϊ4��ADʱ������,PRS=1,ATDClock=6MHz  
  ATD0CTL5=0x20;  //����ͨ����ֹ,����ת�� ,��ͨ��ת������ʼͨ��Ϊ0ת��4��ͨ��    
  ATD0DIEN=0x00;   //��ֹ��������
 }
 
 
//==============��ȡADת���Ľ��=====================//


  int ReadATD(int k)               
{
   int ad=0;
   ATD0CTL2=0x40; 
   switch(k){
   case 0:ATD0CTL5=0x20;break;
   case 1:ATD0CTL5=0x21;break;
   case 2:ATD0CTL5=0x22;break;
   case 3:ATD0CTL5=0x23;break;
   case 4:ATD0CTL5=0x24;break;
   case 5:ATD0CTL5=0x25;break;
   case 6:ATD0CTL5=0x26;break;
   case 7:ATD0CTL5=0x27;break; 
   }
    while(!ATD0STAT0_SCF);
    ad=ATD0DR0L;
   
   return ad;
}



//===================�ɼ����������=======================//
void Collect_IR(void)
{
 IR_temp_laser_array[0]=(byte)(ReadATD(0)/100);
 IR_temp_laser_array[1]=(byte)(ReadATD(1)/100);
 IR_temp_laser_array[2]=(byte)(ReadATD(2)/100);
 IR_temp_laser_array[3]=(byte)(ReadATD(3)/100);
 IR_temp_laser_array[4]=(byte)(ReadATD(4)/100);
 IR_temp_laser_array[5]=(byte)(ReadATD(5)/100);
 IR_temp_laser_array[6]=(byte)(ReadATD(6)/100);
}

/* ===================�����ۼ�ֵȫ��������=======================
*.�����ۼ�ֵ��λ
*.ʮ�ֽ���λ���λ��λ
*.�����ۼ�ֵ������λ      
*/ 
void Linefull_process(byte a){
int i=0;
if(a==1){
  for(i=0;i<7;i++) {
  IR_process_array[i]=2;
}
crossingline_flag=0;
empty_count=0; 
}
}

/* ===================����ɼ���ֵ����������=======================
*.������ʱֵ���ۼ�ֵ��,��ʱֵ�����ΪΪ�����ۼ�ֵΪ��
*.��������ۼ�ֵ����С��101��������ۼ�ֵ������100����������ۼ�ֵ��������100,�����ۼ�ֵ������λ      
*/ 

void TestCross_process(void){
int i=0;
for(i=0;i<7;i++) {
  if(IR_temp_laser_array[i]<2)IR_process_array[i]=0;
}
if(empty_count<101)empty_count++; 
else {
  empty_count=1;Linefull_process(1);
}
}

/* ===================ʮ�ֽ����������ߴ�����=======================
*.��ִ�к���ɼ���ֵ����������,����ۼ�ֵ����ֵΪ10ʱ,�ͽ��д���,���ж��Ƿ�Ϊһ�ź���,
���Ϊ������ʮ�ֽ���λ���λΪ1(һ��ֻ��ʮ�ֽ��������������������),���ʮ�ֽ���λ���λû��,��
2,3,4�ĺ��������а�ɫ��,�����ʮ�ֽ����ж�,�жϷ���Ϊ���ۼ�ֵ�Ƿ����ֺڰ׺ڵķ���,������־���������,
������λ���λΪ1,Ȼ���ú����ۼ�ֵȫ��������������λ
*/ 

void TestCross_judge(void) {
int i=0,start_flag=0,cross_flag=0,judge_flag=0;
  Collect_IR();   //�����ȡ
  TestCross_process();
if(empty_count%10==0){
for(i=0;i<7;i++) 
{
if(IR_process_array[i]<2)cross_flag++;
else if(1<i&&i<5)judge_flag=1;
}
if(cross_flag>5){crossingline_flag=1;} 
else if(crossingline_flag==0&&judge_flag==1){
for(i=0;i<7;i++) 
{
     if(IR_process_array[i]==2&&start_flag==0){continue;}
else if(IR_process_array[i]==2&&start_flag==1){start_flag=2;continue;}
else if(IR_process_array[i]==2&&start_flag==2){continue;}
else if(IR_process_array[i]<2&&start_flag==0) {start_flag=1;continue;} 
else if(IR_process_array[i]<2&&start_flag==1){continue;}
else if(IR_process_array[i]<2&&start_flag==2){startingline_flag=1;start_flag=0;break;}
}
}
}
Linefull_process(startingline_flag);
Linefull_process(crossingline_flag);
}

/* ===================�������µ�����=======================
*.
*/ 
void IR_Ramp(byte a){
int i,IR_rampjudge_flag=0;
 Collect_IR();   //�����ȡ
if(a){
for(i=0;i<7;i++) 
{
if(IR_process_array[i]<3&&i<5){IR_rampjudge_flag=1;break;}//���һ,�����2,3,4�ĺ���ɨ���Ļ�,������
else if(IR_process_array[i]<2&&i>4){IR_rampjudge_flag=2;break;}//�����,�����5,6ɨ���Ļ������һ���,Ȼ�����
else if(IR_process_array[i]<2&&i<2){IR_rampjudge_flag=3;break;}//�����,�����0,1ɨ���Ļ����ҹ�һ���,Ȼ�����
else IR_rampjudge_flag=1; 
}
switch(IR_rampjudge_flag){
  case 1:{
  PWMDTY45 = PWM45;      //�϶������
  PWMDTY01 = PWM01;      //�¶������
  SpeedCtrl(2);
  }
  break;
  case 2:{
  PWMDTY45 = PWM45;      //�϶������
  PWMDTY01 = PWM01+20;      //������һ���
  SpeedCtrl(2);
  PWMDTY01 = PWM01;      //�������
  }
  break;
  case 3:{
  PWMDTY45 = PWM45;      //�϶������
  PWMDTY01 = PWM01-20;      //�������
  SpeedCtrl(2);
  PWMDTY01 = PWM01;      //�������
  }
  break;
}
}
}

/*---------------------------------------
���ͺ�����Ϣ����
��д���ڣ�200110607
----------------------------------------- */ 
void Test_IR(byte temp_laser_array[]) {
    int i; 
    char data[5];
    for(i=0;i<=6;i++)    //���ͼ������Ϣ����
        {  
    (void)sprintf(data,"%.1d",temp_laser_array[6-i]);
		SCISend_chars(data);
		SCISend(' ');
		SCISend(' ');
        }
	    SCISend('\n'); 	
}
