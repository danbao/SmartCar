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
   }
    while(!ATD0STAT0_SCF);
    ad=ATD0DR0L;
   
   return ad;
}

