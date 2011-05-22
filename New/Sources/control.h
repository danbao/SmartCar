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
 
 if(special_flag<3)
  { 
 if(HitBlackNum==0);
 else if((HitBlackNum>0)&&(HitBlackNum<=3)) 
 Status_Judge();
 
   } 
 else {
  Status_Judge();//要调用红外   
  if((light_temp_laser_array[0]==1)&&(light_temp_laser_array[11]==1))
   for(i=0;i<=6;i++){
    calculate_light();
    
    start_count+=Confirm_Start();
 
    cross_count+=Confirm_Cross();
    }
   if(start_count>=4&&cross_count<=1)
   start_flag=1;
   else if(cross_count>=4&&start_count<=1)
   cross_flag=1;
   }
 
}

/*==========================逐个检查 包括计算照黑个数，错误点个数==========*/
void calculate_light(void){
 int i=0,changeposition;
 changeposition=6-position/2;
 for(i=0;i<LASER_MAX;i++) {
  if (light_temp_laser_array[i]==0) continue;
  else if ((light_temp_laser_array[i]==1)&&(aabs(i-changeposition)<=3))  
  {
  HitBlackNum++;
  }
 else if ((light_temp_laser_array[i]==1)&&(aabs(i-changeposition)>=3))
  {
  special_flag++;  //ight_temp_laser_array[i] =0;
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
}


















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