//=================AD初始化===========================//



 void AD_Init(void)     
{
  
  ATD0CTL1=0x00;  //选择AD通道为外部触发,8位精度,采样前不放电 
  ATD0CTL2=0x40;   //标志位自动清零，禁止外部触发, 禁止中断    
  ATD0CTL3=0x88;   //右对齐无符号,每次转换1个序列, No FIFO, Freeze模式下继续转;      
  ATD0CTL4=0x01;  //采样时间为4个AD时钟周期,PRS=1,ATDClock=6MHz  
  ATD0CTL5=0x20;  //特殊通道禁止,连续转换 ,单通道转换，起始通道为0转换4个通道    
  ATD0DIEN=0x00;   //禁止数字输入
 }
 
 
//==============获取AD转换的结果=====================//


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

//===================采集红外进数组=======================//
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







/*=====================红外对应权值======================
IR_MAX         6     5     4     3    2     1     0
对应的权值     3     2     1     0    -1   -2    -3
                                                 
程序未完成，必须有参数和返回值，需要建立联系！  

==========================================================*/

void IR_num(void)
{
  int i;
  for(i=0;i<7;i++)
  {
    q_temp_ir_num[i]=-3+i;
  }
}

/*=====================红外位置的判定======================

权值公式：  position= ∑（light[i]*lightnum[i]） / blacknum  
Light[i]为第i个激光的数值 0或1   ight_temp_laser_array[3]
Lightnum 为表1值   q_temp_laser_num[LASER_MAX]
blacknum为照黑个数
                                                          
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


/*int supple_dajiaopwm(void)//获取的值作为一个红外的一个打角舵机的补足的系数，正负代表左右
{
  int dajiaopwm;
	dajiaopwm=IR_position*2;//2代表一格舵机的偏差的值，再乘以系数就等于红外对打角舵机的补足值
	
	return dajiaopwm;
}//这个一个加在main.c里面baitou()和dajiao()之间,这个函数在非坡道方面还可以再进行扩展

*/
