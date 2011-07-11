
/*==========================起跑检测=======================*/
void Confirm_Start(void)
{
  int leftside=0,rightside=0,middleleft=0,middleright=0,middleside=0;
  int leftnum=0,rightnum=0,middleleftnum=0,middlerightnum=0,middlesidenum=0;

  leftnum=error[0]+error[1]+error[2]+error[3]+error[4] ;
  rightnum=error[16]+error[17]+error[18]+error[19]+error[20];
  middleleftnum=error[12]+error[13];
  middlerightnum=error[7]+error[8];
  middlesidenum=error[9]+error[10]+error[11]+error[12];


  if (leftnum>=3)
   leftside=1;
  if (rightnum>=3)
   rightside=1;

  if (middleleftnum<=1)
  middleleft=1;

  if(middlerightnum<=1) 
  middleright=1;

  if(middlesidenum>=2)
  middleside=1 ;

  if((leftside&&rightside)&&(middleleft&&middleright)&&middleside)
  start_flag=1;
  else start_flag= 0;
}

/*==========================十字检测=====================
void Confirm_Cross(void)
{
  int i=0,black;
  for(i=0;i<LASER_MAX;i++)
  {  
    if (error[i]==0) 
      continue;
  else if (error[i]==1)
    black++; 
  }
  if(black>=20)
    cross_flag= 1;
  else 
    cross_flag= 0;
}

*/

/*==================赛道汇总============================
i-(7-position/2)>3    排除
不足：当这种情况连续出现 则认同
方向标志Direction       
byte Straight_flag;                     //直道标记  非0有效
byte turn_flag;        
byte really_special_flag=0;                //开启 起跑或者十字 也有可能是坡道
byte maybe_special_flag=0;                 //开启可能的特殊  为坡道
byte start_flag=0,cross_flag=0;             //起跑 十字标志
byte slope_flag=0;
byte slope_count=0;                         //坡道与十字时照空计数
byte maybe_count=0;                         //区别坡道和十字的程序运行计数
========================================================*/

void Confirm_Light()
{
  int i=0,j=0;    //changeposition 是position到位置的转换用于推导
  int abs_baitoupwm;
  int aabs_pos;
   

  baitoupwm=befo_General_pos;          
  abs_baitoupwm=baitoupwm;
  abs_baitoupwm=aabs(abs_baitoupwm);
   
  aabs_pos=position;
  aabs_pos=aabs(aabs_pos);
   
  HitBlackNum=0;


  if(start_flag==1);

  if(slope_flag==1)
  {
    calculate_light();

    if(HitBlackNum==21)
      position=0;
      //PWMDTY01=PWM01+supple_dajiaopwm();
      
      	
    else if(HitBlackNum<=4)
      slope_flag=0;

  } 

  if(maybe_special_flag==1)
  {
    if(maybe_slope_flag==0)
    {
      calculate_light();
      if(HitBlackNum<=3) 
      {
        for(j=0;j<LASER_MAX;j++)
          error[j]=error[j]|light_temp_laser_array[j];
        Confirm_Start();

        maybe_special_flag=0;

        for(j=0;j<LASER_MAX;j++)
          error[j]=0;
      }

      else if(HitBlackNum<21)
      {
        for(j=0;j<LASER_MAX;j++)
        error[j]=error[j]|light_temp_laser_array[j];
      } 
       
      else if(HitBlackNum==21)
      { 
        maybe_slope_flag=1;
      }
    }
    else if(maybe_slope_flag==1)
    {
      calculate_light();
      maybe_count++;
      if(HitBlackNum==21)
      slope_count++;
      
      if(maybe_count%6==0) 
      {
      if(slope_count==maybe_count){slope_flag=1; }
      else slope_flag=0;
      
      maybe_count=0;
      slope_count=0;
      maybe_special_flag=0;
      maybe_slope_flag=0; 
      }
        
    }  
  }
   else 
   {
     calculate_light(); 
     if(HitBlackNum==0)
     {
        nothing_flag=1;
     }
     else if(HitBlackNum<=6) 
     {
        nothing_flag=0;
        Status_Judge();
     } 
     else 
     {
        maybe_special_flag=1;  //
        if (light_temp_laser_array[9]+light_temp_laser_array[10]+light_temp_laser_array[11]>=2);
          
     }
    }
   
   
//==========================弯道直道判断=======
    if(abs_baitoupwm>50)
    { 
      if(Straight_flag==1)
      turn_flag=1;Straight_flag=0;

    }
    
     
    else 
    {
      if(Straight_flag==1) 
      {
        turn_flag=0;Straight_flag=1; 
      } 
      else if((turn_flag==1)&&(abs_baitoupwm>5))
      {
        turn_flag=1;Straight_flag=0;
      }  
      else if((turn_flag==1)&&(abs_baitoupwm<=5)) 
      {
        turn_flag=0;Straight_flag=1;diansha_falg=0;
      }        //出弯补足角度 以防 还没完全出弯就转角就变小
    } 
}


/*================综合偏差======================
思路是把每个激光的舵机值加上当前摇头舵机值 相对位置
实验后发现摇头舵机无法做到很快的回位 周期大概20ms内 
如果这样的话 我们就把每次摇头处理后的舵机到下次处理前 等分

*/
void General_Position(void)       
{
  int num=position+20;    //数组序号偏移代入
  baitou_diff[0]=baitou_diff[1];
  baitou_diff[1]=PWMDTY45-PWM45;      //摆头执行后的差值 我们把他等分试试 
  befo_General_pos=-(change_JG_DJ_array[num]+baitou_diff[1]);//*baitou_delay/11;
}



/*==========================逐个检查 包括计算照黑个数，错误点个数==========*/
void calculate_light(void)
{
  int i=0,changeposition;
  changeposition=10+position/2;
  His_HitBlackNum=HitBlackNum;
   
  for(i=0;i<LASER_MAX;i++) 
  {
    if (light_temp_laser_array[i]==0) 
      continue;
    else if (light_temp_laser_array[i]==1)// &&(aabs(i-changeposition)<=6)
    {
      HitBlackNum++;
    }
  }
}

/*=====================激光管对应权值======================
LASER_MAX     20   19   18   17   16   15  14  13  12  11  10    9    8    7     6     5     4     3    2     1     0
对应的权值    20   18   16   14   12   10   8   6   4   2   0   -2   -4    -6    -8   -10  -12   -14   -16   -18   -20
                                                 
程序未完成，必须有参数和返回值，需要建立联系！  

==========================================================*/

void Laser_num(void)
{
  int i;
  for(i=0;i<=LASER_MAX;i++)
  {
    q_temp_laser_num[i]=-20+2*i;
  }
}

/*=====================激光管位置的判定======================

权值公式：  position= ∑（light[i]*lightnum[i]） / blacknum  
Light[i]为第i个激光的数值 0或1   ight_temp_laser_array[3]
Lightnum 为表1值   q_temp_laser_num[LASER_MAX]
blacknum为照黑个数
                                                          
==========================================================*/
void Status_Judge(void)
{
  int i,temp_HitBlackNum,sum=0;
  temp_HitBlackNum=HitBlackNum;
  for(i=0;i<LASER_MAX;i++)
  {
    sum=sum+light_temp_laser_array[i]*q_temp_laser_num[i];
  }
  position=sum/temp_HitBlackNum;
  
  
}

/*=====================红外管程度值======================
红外暂时把它分为三档小 中 大  越小离黑线越近
因为红外本身采集比较连续所以不需要滤波（目前看没有受干扰的情况?
可以用这个值来给舵机打角 用枚举法 但值可能会比较大 所以可能要减去基准值 

      6   5   4   3   2   1   0
      6   4   2   0  -2  -4   -6       IR_position[1]=-6+2*i  此次
                                       IR_position[0]上次
==========================================================

void Level_IR( void)
{
  int i,j;
  
  IR_blacknun=0;
  IR_position[1]=0;
  for(i=0;i<IR_NUM;i++)
  {
  if(i==1)
      { 
      if(IR_temp_laser_array[1]<=130) 
          {IR_position[1]=IR_position[1]-4;IR_blacknun++;}
     else if((IR_temp_laser_array[1]>81)&&(IR_temp_laser_array[1]<=130)) 
          {IR_position[1]=IR_position[1]-4;IR_blacknun++;}
        
      //else if(IR_temp_laser_array[1]>131)IR_Level[1]=100;
      } 
  else if(i==2) 
      {
      if(IR_temp_laser_array[2]<=160)
          { IR_position[1]=IR_position[1]-2;IR_blacknun++;}
       else if((IR_temp_laser_array[2]>81)&&(IR_temp_laser_array[2]<=160))
          {IR_position[1]=IR_position[1]-2;IR_blacknun++;}
        
      //else if(IR_temp_laser_array[2]>161)IR_Level[2]=100;
      }
  else{
      if(IR_temp_laser_array[i]<=170)
          { IR_position[1]=IR_position[1]+(2*i-6);IR_blacknun++;}
        
      else if((IR_temp_laser_array[i]>81)&&(IR_temp_laser_array[i]<=190)) 
          {IR_position[1]=IR_position[1]+(2*i-6);IR_blacknun++;}
        
      //else if(IR_temp_laser_array[i]>191)IR_Level[i]=100;
      }
  }
  if(IR_blacknun==0)IR_position[1]=IR_position[0]*100;
  else 
    {
    IR_position[1]=(IR_position[1]/IR_blacknun); 
    j=IR_position[1]-IR_position[0] ;
    if( aabs(j) >2)IR_position[1]=IR_position[0]*100;
    else {
      IR_position[0] =IR_position[1];
      IR_position[1]=IR_position[1]*100;
      
          }
    }
   
}

*/

/*===================速度过滤=============================
由于编码盘捕捉的有时候也会不稳定
所以虑一次波既可以平滑 又稳定
*/
void Clear_Speed(void) 
{
  //long Speed_sum;
  speed_clear[1]=(30*speed_clear[0]+10*speed_clear[1])/40;
  speed_clear[0]=speed_clear[1];
}



/*===================测速转换=============================
double Calculate_speed(double temp_pulse)
{
	double a=24,b=76,c=160;//a为编码器的齿轮，b为后轮驱动的齿轮，c为后轮转一圈的距离（毫米）
	double v;
	v=temp_pulse*b*c/2000*a;//
	return v;
}

*/

/*=====================激光管照到黑线的个数======================
合并到control 

void Calculate_HitBlackNum()
{
  int i;
  HitBlackNum=0;
  for(i=0;i<LASER_MAX;i++) 
  {
    if(light_temp_laser_array[i]==1)
    {
      HitBlackNum++;
    }
  }
  //return HitBlackNum;
}
*/

/*======================lost_blackline();======================
void lost_blackline(void)
{
  int HitBlackNum;
  lost_line_flag=0;
  if(HitBlackNum) 
  {
    if (14-aabs(His_Position[2])<=3&&(aabs(His_Position[2]-position))<=2)
      lost_line_flag=0; 
    else if(14-aabs(His_Position[2])<=3&&aabs(His_Position[2]+position)<=11)
      lost_line_flag=1;
  } 
  else  
    lost_line_flag=1; 
}
*/