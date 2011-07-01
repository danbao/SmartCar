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



//===================采集红外进数组=======================//
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

/*=====================十字交叉线的判断======================
经过准确地测试，得出了一些阶段性的结论：
一次红外获取的数组里面有6个0或1的情况下，array_count自增，
直到等于6时，就判断此为十字交叉线

参数：i 为数组的个数
      array_count   为数组数    设置为全局变量
      dot_count    为每次获取的数组里面符合条件的点数    
                    这个为局部变量，在每次执行完之后就释放掉内存
                    每次执行Startingline_judge都初始化，从0开始
========================================================
void Crossing_judge(void)
{
  int i,dot_count=0;
  for(i=0;i<7;i++)
  {
    if(IR_temp_laser_array[i]==0||IR_temp_laser_array[i]==1)
      dot_count++;
    if(dot_count == 6)//这个估计要加在程序的整个过程中，每次判断一组，要有大于等于3次判断
      array_count++;
  }
  if(array_count == 3) 
  {
    crossing_flag =1;
  }
｝*/

/*=====================起跑线的判断======================
经过准确地测试，得出了一些阶段性的结论：
一次红外获取的数组里面有2个2的情况下，array_count自增，
直到等于3时，就判断此为起跑线

参数：i 为数组的个数
      array_count   为数组数    设置为全局变量
      dot_count    为每次获取的数组里面符合条件的点数    
                    这个为局部变量，在每次执行完之后就释放掉内存
                    每次执行Startingline_judge都初始化，从0开始
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
            array_count++;//如果真的要写在判断函数里面,array_count一定要设置为全局变量
          }
    }
  }
  if(array_count>=3)
  {
    startingline_flag=1;
  }
}*/

/*===========================清空标志位============================
一旦出现不是连续的组，crossingline_flag和startingline_flag自动清零
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

/*=========================特殊情况的判断==========================
流程图：
1、先判断每次红外获取的数组，统计特殊点（0、1、2）的点数（dot_array）
2、再根据十字交叉和起跑线的特点进行判断，一个if-else语句。
==================================================================*/
void Specialline_judge(void) 
{
  int i,dot2_count=0,dot12_count=0;
  for(i=0;i<7;i++)
  {
    if(IR_temp_laser_array[i]==2) 
    {
      dot2_count++;//2点为特殊的点
      if(IR_temp_laser_array[i-1]==0||IR_temp_laser_array[i-1]==1)
        if(IR_temp_laser_array[i+1]==0||IR_temp_laser_array[i+1]==1)
          if(dot2_count>=2) 
          { 
            startingline_array_count++;//如果真的要写在判断函数里面,array_count一定要设置为全局变量
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

