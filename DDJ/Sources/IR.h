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


void TestCross_process(void){
int i=0;
for(i=0;i<7;i++) {
  if(IR_temp_laser_array[i]<2)IR_process_array[i]=0;
} 
empty_count++;
}



void TestCross_judge(void) {
int i=0,start_flag=0;
  TestCross_process();
   if(empty_count==50){
   for(i=0;i<7;i++) 
{
if(IR_process_array[i]==2&&start_flag==1){start_flag=2;}
else if(IR_process_array[i]<2&&start_flag==0) {start_flag=1;} 
else if(IR_process_array[i]<2&&start_flag==2){startingline_flag=1;start_flag=0;}
IR_process_array[i]=2;
}
empty_count=0; 
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
