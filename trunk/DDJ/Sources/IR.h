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
  switch(k)
  {
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
  IR_temp_laser_array[0]=(byte)(ReadATD(0)/48);
  IR_temp_laser_array[1]=(byte)(ReadATD(1)/48);
  IR_temp_laser_array[2]=(byte)(ReadATD(2)/43);
  IR_temp_laser_array[3]=(byte)(ReadATD(3)/48);
  IR_temp_laser_array[4]=(byte)(ReadATD(4)/48);
  IR_temp_laser_array[5]=(byte)(ReadATD(5)/48);
  IR_temp_laser_array[6]=(byte)(ReadATD(6)/48);
}







/*=====================�����ӦȨֵ======================
IR_MAX         6     5     4     3    2     1     0
��Ӧ��Ȩֵ     3     2     1     0    -1   -2    -3
                                                 
����δ��ɣ������в����ͷ���ֵ����Ҫ������ϵ��  

==========================================================*/

void IR_num(void)
{
  int i;
  for(i=0;i<7;i++)
  {
    q_temp_ir_num[i]=-3+i;
  }
}

/*=====================����λ�õ��ж�======================

Ȩֵ��ʽ��  position= �ƣ�light[i]*lightnum[i]�� / blacknum  
Light[i]Ϊ��i���������ֵ 0��1   ight_temp_laser_array[3]
Lightnum Ϊ��1ֵ   q_temp_laser_num[LASER_MAX]
blacknumΪ�պڸ���
                                                          
==========================================================*/
void IR_Status_Judge(void)
{
	int i,maybepos=0,j=0;
	int Min=IR_temp_laser_array[3];
  int num=3;
  
  His_IR_pos=IR_position;
  
 // if(IR_temp_laser_array[3]<Min)
 // num=3;
  
  for(i=2;i>=0;i--) 
  {
      if(IR_temp_laser_array[i]<Min)
      num=i;
  }
  for(i=4;i<7;i++) 
  {
      if(IR_temp_laser_array[i]<Min)
      num=i;
  }
  
	maybepos=num-3;
	j=maybepos-His_IR_pos;
	j=aabs(j);
	if(j<=1)IR_position= maybepos;
	
}


/*int supple_dajiaopwm(void)//��ȡ��ֵ��Ϊһ�������һ����Ƕ���Ĳ����ϵ����������������
{
  int dajiaopwm;
	dajiaopwm=IR_position*2;//2����һ������ƫ���ֵ���ٳ���ϵ���͵��ں���Դ�Ƕ���Ĳ���ֵ
	
	return dajiaopwm;
}//���һ������main.c����baitou()��dajiao()֮��,��������ڷ��µ����滹�����ٽ�����չ

*/
