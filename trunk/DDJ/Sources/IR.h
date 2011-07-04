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
 IR_temp_laser_array[0]=(byte)(ReadATD(0)/100);
 IR_temp_laser_array[1]=(byte)(ReadATD(1)/100);
 IR_temp_laser_array[2]=(byte)(ReadATD(2)/100);
 IR_temp_laser_array[3]=(byte)(ReadATD(3)/100);
 IR_temp_laser_array[4]=(byte)(ReadATD(4)/100);
 IR_temp_laser_array[5]=(byte)(ReadATD(5)/100);
 IR_temp_laser_array[6]=(byte)(ReadATD(6)/100);
}

/* ===================红外累计值全满处理方法=======================
*.红外累加值复位
*.十字交叉位标记位复位
*.红外累加值计数复位      
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

/* ===================红外采集的值初步处理方法=======================
*.红外临时值与累加值与,临时值如果该为为黑则累计值为黑
*.如果红外累加值计数小于101，则红外累加值计数记100，如果红外累加值计数大于100,红外累加值计数复位      
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

/* ===================十字交叉与起跑线处理方法=======================
*.先执行红外采集的值初步处理方法,如果累加值计数值为10时,就进行处理,先判断是否为一排黑线,
如果为黑线则十字交叉位标记位为1(一般只有十字交叉或过弯道会出现这种情况),如果十字交叉位标记位没变,且
2,3,4的红外其中有白色的,则进行十字交叉判断,判断方法为看累加值是否会出现黑白黑的方法,如果出现就是起跑线,
起跑线位标记位为1,然后用红外累计值全满处理方法处理标记位
*/ 

void TestCross_judge(void) {
int i=0,start_flag=0,cross_flag=0,judge_flag=0;
  Collect_IR();   //红外获取
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

/* ===================红外上坡到方法=======================
*.
*/ 
void IR_Ramp(byte a){
int i,IR_rampjudge_flag=0;
 Collect_IR();   //红外获取
if(a){
for(i=0;i<7;i++) 
{
if(IR_process_array[i]<3&&i<5){IR_rampjudge_flag=1;break;}//情况一,如果是2,3,4的红外扫到的话,居中走
else if(IR_process_array[i]<2&&i>4){IR_rampjudge_flag=2;break;}//情况二,如果是5,6扫到的话向左拐一点点,然后摆正
else if(IR_process_array[i]<2&&i<2){IR_rampjudge_flag=3;break;}//情况三,如果是0,1扫到的话向右拐一点点,然后摆正
else IR_rampjudge_flag=1; 
}
switch(IR_rampjudge_flag){
  case 1:{
  PWMDTY45 = PWM45;      //上舵机居中
  PWMDTY01 = PWM01;      //下舵机居中
  SpeedCtrl(2);
  }
  break;
  case 2:{
  PWMDTY45 = PWM45;      //上舵机居中
  PWMDTY01 = PWM01+20;      //舵机左拐一点点
  SpeedCtrl(2);
  PWMDTY01 = PWM01;      //舵机居中
  }
  break;
  case 3:{
  PWMDTY45 = PWM45;      //上舵机居中
  PWMDTY01 = PWM01-20;      //舵机居中
  SpeedCtrl(2);
  PWMDTY01 = PWM01;      //舵机居中
  }
  break;
}
}
}

/*---------------------------------------
发送红外信息数组
编写日期：200110607
----------------------------------------- */ 
void Test_IR(byte temp_laser_array[]) {
    int i; 
    char data[5];
    for(i=0;i<=6;i++)    //发送激光管信息数组
        {  
    (void)sprintf(data,"%.1d",temp_laser_array[6-i]);
		SCISend_chars(data);
		SCISend(' ');
		SCISend(' ');
        }
	    SCISend('\n'); 	
}
