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

/*=====================ʮ�ֽ����ߵ��ж�======================
����׼ȷ�ز��ԣ��ó���һЩ�׶��ԵĽ��ۣ�
һ�κ����ȡ������������6��0��1������£�array_count������
ֱ������6ʱ�����жϴ�Ϊʮ�ֽ�����

������i Ϊ����ĸ���
      array_count   Ϊ������    ����Ϊȫ�ֱ���
      dot_count    Ϊÿ�λ�ȡ������������������ĵ���    
                    ���Ϊ�ֲ���������ÿ��ִ����֮����ͷŵ��ڴ�
                    ÿ��ִ��Startingline_judge����ʼ������0��ʼ
========================================================
void Crossing_judge(void)
{
  int i,dot_count=0;
  for(i=0;i<7;i++)
  {
    if(IR_temp_laser_array[i]==0||IR_temp_laser_array[i]==1)
      dot_count++;
    if(dot_count == 6)//�������Ҫ���ڳ�������������У�ÿ���ж�һ�飬Ҫ�д��ڵ���3���ж�
      array_count++;
  }
  if(array_count == 3) 
  {
    crossing_flag =1;
  }
��*/

/*=====================�����ߵ��ж�======================
����׼ȷ�ز��ԣ��ó���һЩ�׶��ԵĽ��ۣ�
һ�κ����ȡ������������2��2������£�array_count������
ֱ������3ʱ�����жϴ�Ϊ������

������i Ϊ����ĸ���
      array_count   Ϊ������    ����Ϊȫ�ֱ���
      dot_count    Ϊÿ�λ�ȡ������������������ĵ���    
                    ���Ϊ�ֲ���������ÿ��ִ����֮����ͷŵ��ڴ�
                    ÿ��ִ��Startingline_judge����ʼ������0��ʼ
========================================================
void Startingline_judge(void)
{
  int i,dot_count=0;
  for(i=0;i<7;i++)
  {
    if(IR_temp_laser_array[i]==2) 
    {
      dot_count++;
      if(IR_temp_laser_array[i-1]==0||IR_temp_laser_array[i-1]==1)
        if(IR_temp_laser_array[i+1]==0||IR_temp_laser_array[i+1]==1)
          if(dot_array>=2) 
          { 
            array_count++;//������Ҫд���жϺ�������,array_countһ��Ҫ����Ϊȫ�ֱ���
          }
    }
  }
  if(array_count>=3)
  {
    startingline_flag=1;
  }
}*/

/*===========================��ձ�־λ============================
һ�����ֲ����������飬crossingline_flag��startingline_flag�Զ�����
==================================================================*/
void emptyflag(void)
{
  if(empty_count==5) 
  {
    if(startingline_array_count>=3)
    {
      startingline_flag=1;
	  startingline_array_count=0;
    }
    if(crossingline_array_count==1)
    {
      crossingline_flag=1;
	  crossingline_array_count=0;
    }
    empty_count=0;
  }
}

/*=========================����������ж�==========================
����ͼ��
1�����ж�ÿ�κ����ȡ�����飬ͳ������㣨0��1��2���ĵ�����dot_array��
2���ٸ���ʮ�ֽ���������ߵ��ص�����жϣ�һ��if-else��䡣
==================================================================*/
void Specialline_judge(void) 
{
  int i,dot2_count=0,dot12_count=0;
  for(i=0;i<7;i++)
  {
    if(IR_temp_laser_array[i]==2) 
    {
      dot2_count++;//2��Ϊ����ĵ�
      if(IR_temp_laser_array[i-1]==0||IR_temp_laser_array[i-1]==1)
        if(IR_temp_laser_array[i+1]==0||IR_temp_laser_array[i+1]==1)
          if(dot2_count>=2) 
          { 
            startingline_array_count++;//������Ҫд���жϺ�������,array_countһ��Ҫ����Ϊȫ�ֱ���
          }
    } 
    else 
    {
      if(IR_temp_laser_array[i]==0||IR_temp_laser_array[i]==1)
        dot12_count++;
      if(dot12_count>=5)
        crossingline_array_count++;
    }
      
  }
  empty_count++;
  emptyflag();
}  

