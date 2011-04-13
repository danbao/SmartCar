/*==================排除干扰点============================
i-(7-position/2)>3    排除
不足：当这种情况连续出现 则认同
       */
void Confirm_Light(){
 int i=0;
 int halfposition=position/2;
 for(i=0;i<LASER_MAX;i++) {
  if (light_temp_laser_array[i]==0) continue;
  else if (abs(i-(7-halfposition))>=3) light_temp_laser_array[i] =0;
  else continue;   
 }
} 

/*======================lost_blackline();======================*/
void lost_blackline(void){
  int HitBlackNum;
  lost_line_flag=0;
  HitBlackNum=Calculate_HitBlackNum();
  if(HitBlackNum) {
  if (14-abs(His_Position[2])<=3&&(abs(His_Position[2]-position))<=2)
      lost_line_flag=0; 
   else if(14-abs(His_Position[2])<=3&&abs(His_Position[2]+position)<=11)
   lost_line_flag=1;
  } 
  else  
  lost_line_flag=1; 
}