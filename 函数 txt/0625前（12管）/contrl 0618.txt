/*==========================起跑检测=======================*/
int Confirm_Start(void){
int left=0,right=0,middle=0;
if ((light_temp_laser_array[0]==1)&&(light_temp_laser_array[1]==1))
 right=1;
if ((light_temp_laser_array[10]==1)&&(light_temp_laser_array[11]==1))
 left=1;
if ((light_temp_laser_array[3]==1||light_temp_laser_array[4]==1)&&light_temp_laser_array[7]==1||light_temp_laser_array[8]==1)
 middle=1;

if(right&&left&&middle) 
  return 1;
else return 0;
}


/*==========================十字检测=====================*/
int Confirm_Cross(void){
if(special_flag>=5)
return 1;
else return 0;
}


/*==================排除干扰点============================
i-(7-position/2)>3    排除
不足：当这种情况连续出现 则认同
方向标志Direction       
       */
void Confirm_Light(){
 int i=0;    //changeposition 是position到位置的转换用于推导
 int start_count,cross_count;      //起始和十字计数
           //其实和十字标志
 
 
 HitBlackNum=0;
 special_flag=0;
 
 start_count=0;
 cross_count=0;
 start_flag=0;
 cross_flag=0;
 
 calculate_light();
 

 if(HitBlackNum==0)
   {
   if(right)
      {
      position =-12;
      } 
   else if(left)
      {
      position=12;
      } 
   else  if(middle);
      
   }
 else if(HitBlackNum>0) 
 Status_Judge();
 
}

/*==========================逐个检查 包括计算照黑个数，错误点个数==========*/
void calculate_light(void){
 int i=0,changeposition;
 changeposition=6+position/2;
 for(i=0;i<LASER_MAX;i++) {
  if (light_temp_laser_array[i]==0) continue;
  else if ((light_temp_laser_array[i]==1)&&(aabs(i-changeposition)<=6)) 
  {
  HitBlackNum++;
  }
   
 }

}
/*=====================激光管对应权值======================
LASER_MAX         11  10    9    8    7     6     5    4     3     2        1     0
对应的权值        11   9    7    5    3      1   -1   -3    -5    -7       -9   -11
                                                 
程序未完成，必须有参数和返回值，需要建立联系！  

==========================================================*/

void Laser_num(void){
  int i;
  for(i=0;i<LASER_MAX;i++){
    q_temp_laser_num[i]=-11+2*i;
  }
}

/*=====================激光管位置的判定======================

权值公式：  position= ∑（light[i]*lightnum[i]） / blacknum  
Light[i]为第i个激光的数值 0或1   ight_temp_laser_array[3]
Lightnum 为表1值   q_temp_laser_num[LASER_MAX]
blacknum为照黑个数
                                                          
==========================================================*/
void Status_Judge(void) {
  int i,temp_HitBlackNum,sum=0;
  temp_HitBlackNum=HitBlackNum;
  for(i=0;i<LASER_MAX;i++){
    sum=sum+light_temp_laser_array[i]*q_temp_laser_num[i];
  }
  position=sum/temp_HitBlackNum;
  
  if(position>6){left=1;right=0;middle=0;} 
  else if(position<-6){right=1;left=0;middle=0;} 
  else {middle=1;right=0;left=0;}
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
void Clear_Speed(void) {
//long Speed_sum;
speed_clera[1]=(40*speed_clera[0]+100*speed_clera[1])/140;
speed_clera[0]=speed_clera[1];
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

void Calculate_HitBlackNum(){
  int i;
  HitBlackNum=0;
  for(i=0;i<LASER_MAX;i++) {
    if(light_temp_laser_array[i]==1){
      HitBlackNum++;
    }
  }
  //return HitBlackNum;
}
*/


/*======================lost_blackline();======================
void lost_blackline(void){
  int HitBlackNum;
  lost_line_flag=0;
  if(HitBlackNum) {
  if (14-aabs(His_Position[2])<=3&&(aabs(His_Position[2]-position))<=2)
      lost_line_flag=0; 
   else if(14-aabs(His_Position[2])<=3&&aabs(His_Position[2]+position)<=11)
   lost_line_flag=1;
  } 
  else  
  lost_line_flag=1; 
}
*/