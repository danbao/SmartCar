byte startingline_flag=0;
byte crossingline_flag=0;
int startingline_array_count=0;
int empty_count=0;
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
 IR_temp_laser_array[0]=ReadATD(0)/100;
 IR_temp_laser_array[1]=ReadATD(1)/100;
 IR_temp_laser_array[2]=ReadATD(2)/100;
 IR_temp_laser_array[3]=ReadATD(3)/100;
 IR_temp_laser_array[4]=ReadATD(4)/100;
 IR_temp_laser_array[5]=ReadATD(5)/100;
 IR_temp_laser_array[6]=ReadATD(6)/100;
}


/*===========================��ձ�־λ============================
һ�����ֲ����������飬crossingline_flag��startingline_flag�Զ�����
==================================================================*/
void emptyflag(void)
{
  if(empty_count==6) 
  {
  if(startingline_array_count>=3&&crossingline_flag==0)
  {
   startingline_flag=1;
	 startingline_array_count=0;
  }
  else if( crossingline_flag==1) crossingline_flag=0;
 empty_count=0;
  }   
}

/*=========================����������ж�==========================
����ͼ��
1.  0��1����T,2����F;
2.  flag=0,����ǰ��ɨ���Ķ���F;flag=1,����ǰ��ɨ��һ��T��,����ȥҪɨ��F�ű��flag�ű��2;
flag=2����ǰ���Ѿ�ɨ��T��F,��Ҫɨ��T��startingline_array_count�żӼ�
==================================================================*/
void Start_judge(void) 
{
int i=0,start_flag=0,start_temp,cross_flag=0;
start_temp=startingline_array_count;
for(i=0;i<7;i++) 
{
if(IR_temp_laser_array[i]==2&&start_flag==0){continue;}
else if(IR_temp_laser_array[i]==2&&start_flag==1){start_flag=2;continue;}
else if(IR_temp_laser_array[i]==2&&start_flag==2){continue;}
else if(IR_temp_laser_array[i]<2&&start_flag==0) {start_flag=1;continue;} 
else if(IR_temp_laser_array[i]<2&&start_flag==1){continue;}
else if(IR_temp_laser_array[i]<2&&start_flag==2){startingline_array_count++;start_flag=0;break;}
}
if(start_temp==startingline_array_count)
{
for(i=0;i<7;i++) 
{
if(IR_temp_laser_array[i]==2)cross_flag++;
}
if(cross_flag<4)crossingline_flag=1;
}
  empty_count++;
  emptyflag(); 
}

