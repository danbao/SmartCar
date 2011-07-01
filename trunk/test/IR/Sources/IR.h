byte startingline_flag=0;
int startingline_array_count=0;
int empty_count=0;
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


/*===========================清空标志位============================
一旦出现不是连续的组，crossingline_flag和startingline_flag自动清零
==================================================================*/
void emptyflag(void)
{
  if(empty_count==5) 
  {
    if(startingline_array_count>=2)
    {
     startingline_flag=1;
     SCISend_chars("这是起跑线!");
     startingline_flag=0;
     SCISend('\n');
	  startingline_array_count=0;
    }
    empty_count=0;
  }
}

/*=========================特殊情况的判断==========================
流程图：
1.  0或1代表T,2代表F;
2.  flag=0,代表前面扫到的都是F;flag=1,代表前面扫到一个T了,接下去要扫到F才变成flag才变成2;
flag=2代表前面已经扫到T和F,需要扫到T后startingline_array_count才加加
==================================================================*/
void Cross_judge(void) 
{
  int i=0,cross_flag=0;
for(i=0;i<7;i++) 
{
if(IR_temp_laser_array[i]==2&&cross_flag==0){continue;}
else if(IR_temp_laser_array[i]==2&&cross_flag==1){cross_flag=2;continue;}
else if(IR_temp_laser_array[i]==2&&cross_flag==2){continue;}
else if(IR_temp_laser_array[i]<2&&cross_flag==0) {cross_flag=1;continue;} 
else if(IR_temp_laser_array[i]<2&&cross_flag==1){continue;}
else if(IR_temp_laser_array[i]<2&&cross_flag==2){startingline_array_count++;cross_flag=0;break;}

}
  empty_count++;
  emptyflag();
}  
