




/*=====================激光摆头滤波======================
long JG_clear[2];                      //激光一次迭代滤波 此次和上次
long JG_clear_Pos[2];                  //存入当前和上一次JG_clear 的值
*/
 
 
void Clear_baitou(void)
{
 int abs_baitoupwm;

abs_baitoupwm=baitoupwm;
abs_baitoupwm=aabs(abs_baitoupwm);


  /*if(YDdelay==0)
    JG_clear[0]=JG_clear[1];  */

 JG_clear[1]=position*10;   
  
  
  


  //JG_clear[1]=(JG_clear[0]*20+JG_clear[1]*70) /90 ;  


  //JG_clear[3]=(JG_clear[2]*30+JG_clear[3]*40)/70;
  //JG_clear[2]=JG_clear[3]; 
}

  
/*=====================激光管对应权值======================
LASER_MAX     20   19   18   17   16   15  14  13  12  11  10    9    8    7     6     5     4     3    2     1     0
对应的权值    20   18   16   14   12   10   8   6   4   2   0   -2   -4    -6    -8   -10  -12   -14   -16   -18   -20
分段连接要重合
int BP1=54,BP2=45,BP3=36,BP4=27,BP5=20;
*/
void  baitou (void) 
{
    
  int JG_pos=JG_clear[1];
  int JG_pos_abs;
  int JG_pwm;
  int JG_pwm_his=PWMDTY45;
  int sub_p[20],sub2_p[20];
  //int sub_baitou;
 // int abs_baitoupwm;
  
 
 
  
 
  
  if((baitou_diff[1]<=150&&baitou_diff[1]>=-150))//直道情况
  { //if(position>14)
    //side=1;
    //else if(position<-14)
    //side=-1;
    //else
   baitou_begin=0; 
   get_flag=1;  
   side=0;
  } 
  
  
  
  else if(baitou_diff[1]<-150&&baitou_begin==0) //左边情况
  {
      side=1;
     // side_baipwm=baitou_diff[1]-baitou_diff[0]; 
      if(position<=-4&&get_flag==1) 
      { 
       get_flag=0;
       side_baipwm=baitou_diff[1];  
      }
      
 
   
  
 if(side==1&&get_flag==0){
  
 if(position<=-9) {side=0;baitou_begin=1; }
 }
  } 
 
  else if(baitou_diff[1]>150&&baitou_begin==0) //右边情况
  {
  side=-1;
   
      if(position>=4&&get_flag==1)
      { 
         get_flag=0;
         side_baipwm=baitou_diff[1];  
      }
   
   if(side==-1&&get_flag==0){
    
   if(position>=9) {side=0;baitou_begin=1; }
   }
  }
  
 
   if (side==0)
   {
      JG_clear_Pos[1]=JG_clear[1];
      JG_pos_abs=JG_clear_Pos[1];
      JG_pos_abs=aabs(JG_pos_abs);
      
      sub_p[0]=10/B1P1;
      sub_p[1]=20/B1P2-(20/B1P1-sub_p[0]);
      sub_p[2]=40/B1P3-(40/B1P2-sub_p[1]);
      sub_p[3]=60/B1P4-(60/B1P3-sub_p[2]);
      sub_p[4]=80/B1P5-(80/B1P4-sub_p[3]);
      sub_p[5]=100/B1P6-(100/B1P5-sub_p[4]);
      sub_p[6]=120/B1P7-(120/B1P6-sub_p[5]);
      sub_p[7]=140/B1P8-(140/B1P7-sub_p[6]);
      sub_p[8]=160/B1P9-(160/B1P8-sub_p[7]);
      sub_p[9]=180/B1P10-(180/B1P9-sub_p[8]);
  
      if(JG_pos_abs<=10)                            
        JG_pwm=0;
      
      
       else if(JG_pos_abs>10&&JG_pos_abs<=20) 
      {
        if(position>0)    
          JG_pwm=-(JG_clear_Pos[1]/B1P1-sub_p[0]);
        else if(position<0)
          JG_pwm=-(JG_clear_Pos[1]/B1P1+sub_p[0]); 
      }
      else if(JG_pos_abs>20&&JG_pos_abs<=40) 
      {
        if(position>0)   
          JG_pwm=-(JG_clear_Pos[1]/B1P2-sub_p[1]);
        else if(position<0)
          JG_pwm=-(JG_clear_Pos[1]/B1P2+sub_p[1]);
      }
      else if(JG_pos_abs>40&&JG_pos_abs<=60) 
      {
        if(position>0)   
          JG_pwm=-(JG_clear_Pos[1]/B1P3-sub_p[2]);
        else if(position<0)
          JG_pwm=-(JG_clear_Pos[1]/B1P3+sub_p[2]);
      }      
      else if(JG_pos_abs>60&&JG_pos_abs<=80)
      {
        if(position>0)    
          JG_pwm=-(JG_clear_Pos[1]/B1P4-sub_p[3]);
        else if(position<0)
          JG_pwm=-(JG_clear_Pos[1]/B1P4+sub_p[3]);
      }
      else if(JG_pos_abs>80&&JG_pos_abs<=100)
      {
        if(position>0)    
          JG_pwm=-(JG_clear_Pos[1]/B1P5-sub_p[4]);
        else if(position<0)
          JG_pwm=-(JG_clear_Pos[1]/B1P5+sub_p[4]);
      }
      else if(JG_pos_abs>100&&JG_pos_abs<=120)
      {
        if(position>0)    
          JG_pwm=-(JG_clear_Pos[1]/B1P6-sub_p[5]);
        else if(position<0)
          JG_pwm=-(JG_clear_Pos[1]/B1P6+sub_p[5]);
      }
        
      else if(JG_pos_abs>120&&JG_pos_abs<=140)
      {
        if(position>0)    
          JG_pwm=-(JG_clear_Pos[1]/B1P7-sub_p[6]);
        else if(position<0)
          JG_pwm=-(JG_clear_Pos[1]/B1P7+sub_p[6]);
      }                  
      else if(JG_pos_abs>140&&JG_pos_abs<=160) 
      {
        if(position>0)    
          JG_pwm=-(JG_clear_Pos[1]/B1P8-sub_p[7]);
        else if(position<0)
          JG_pwm=-(JG_clear_Pos[1]/B1P8+sub_p[7]);
      }      
      else if(JG_pos_abs>160&&JG_pos_abs<=180)
      {
        if(position>0)   
          JG_pwm=-(JG_clear_Pos[1]/B1P9-sub_p[8]);
        else if(position<0)
          JG_pwm=-(JG_clear_Pos[1]/B1P9+sub_p[8]);
      }         
      else if(JG_pos_abs>180)
      {
        if(position>0)   
          JG_pwm=-(JG_clear_Pos[1]/B1P10-sub_p[9]);
        else if(position<0)
          JG_pwm=-(JG_clear_Pos[1]/B1P10+sub_p[9]);
      }
   } 
/*====================================================*/   
   else if(side==1)
   {
      JG_clear_Pos[1]=JG_clear[1]+80;
      JG_pos_abs=JG_clear_Pos[1];
      JG_pos_abs=aabs(JG_pos_abs);
                                              
      sub_p[0]=10/B1P1;
      sub_p[1]=20/B1P2-(20/B1P1-sub_p[0]);
      sub_p[2]=40/B1P3-(40/B1P2-sub_p[1]);
      sub_p[3]=60/B1P4-(60/B1P3-sub_p[2]);
      sub_p[4]=80/B1P5-(80/B1P4-sub_p[3]);
      sub_p[5]=100/B1P6-(100/B1P5-sub_p[4]);
      sub_p[6]=120/B1P7-(120/B1P6-sub_p[5]);
      sub_p[7]=140/B1P8-(140/B1P7-sub_p[6]);
      sub_p[8]=160/B1P9-(160/B1P8-sub_p[7]);
      sub_p[9]=180/B1P10-(180/B1P9-sub_p[8]);
      sub_p[10]=200/B1P11-(200/B1P10-sub_p[9]);
      sub_p[11]=220/B1P12-(220/B1P11-sub_p[10]);
      sub_p[12]=240/B1P13-(240/B1P12-sub_p[11]);
      sub_p[13]=260/B1P14-(260/B1P13-sub_p[12]);
      
      sub2_p[0]=10/B2P1;
      sub2_p[1]=20/B2P2-(20/B2P1-sub2_p[0]);
      sub2_p[2]=40/B2P3-(40/B2P2-sub2_p[1]);
      sub2_p[3]=60/B2P4-(60/B2P3-sub2_p[2]);
      sub2_p[4]=80/B2P5-(80/B2P4-sub2_p[3]);
   
      if(JG_pos_abs<=10)                            
        JG_pwm=0;
      else if(JG_pos_abs>10&&JG_pos_abs<=20) 
      {
        if(JG_clear_Pos[1]>0)    
         JG_pwm=0;  // JG_pwm=-(JG_clear_Pos[1]/B1P1-sub_p[0]);
        else if(JG_clear_Pos[1]<0)
          JG_pwm=-(JG_clear_Pos[1]/B2P1);  
      }
      else if(JG_pos_abs>20&&JG_pos_abs<=40) 
      {
       if(JG_clear_Pos[1]>0)   
         JG_pwm=0;  // JG_pwm=-(JG_clear_Pos[1]/B1P2-sub_p[1]);
        else if(JG_clear_Pos[1]<0)
          JG_pwm=-(JG_clear_Pos[1]/B2P2+sub2_p[0]);
      }
      else if(JG_pos_abs>40&&JG_pos_abs<=60) 
      {
          if(JG_clear_Pos[1]>0)   
         JG_pwm=0;  // JG_pwm=-(JG_clear_Pos[1]/B1P3-sub_p[2]);
         else if(JG_clear_Pos[1]<0)
          JG_pwm=-(JG_clear_Pos[1]/B2P3+sub2_p[1]);
      }      
      else if(JG_pos_abs>60&&JG_pos_abs<=80)
      {
        if(JG_clear_Pos[1]>0)    
         JG_pwm=-(JG_clear_Pos[1]/B1P4-sub_p[3])*get_flag;
        else  if(JG_clear_Pos[1]<0)
          JG_pwm=-(JG_clear_Pos[1]/B2P4+sub2_p[2]); 
      }
      else if(JG_pos_abs>80&&JG_pos_abs<=100)
      {
        if(JG_clear_Pos[1]>0)    
          JG_pwm=-(JG_clear_Pos[1]/B1P5-sub_p[4])*get_flag;
         else if(JG_clear_Pos[1]<0)
          JG_pwm=-(JG_clear_Pos[1]/B2P5+sub2_p[3]); 
      }
      else if(JG_pos_abs>100&&JG_pos_abs<=120)
      {
        if(JG_clear_Pos[1]>0)    
          JG_pwm=-(JG_clear_Pos[1]/B1P6-sub_p[5]);
         else if(JG_clear_Pos[1]<0)
          JG_pwm=-(JG_clear_Pos[1]/B2P6+sub2_p[4]); 
      }
        
      else if(JG_pos_abs>120&&JG_pos_abs<=140)
      {
        if(JG_clear_Pos[1]>0)    
          JG_pwm=-(JG_clear_Pos[1]/B1P7-sub_p[6]);
       
      } 
    //=========================================  
      else if(JG_pos_abs>140&&JG_pos_abs<=160) 
      {
        if(JG_clear_Pos[1]>0)    
        JG_pwm=-(JG_clear_Pos[1]/B1P8-sub_p[7]);
      
      }      
      else if(JG_pos_abs>160&&JG_pos_abs<=180)
      {
        if(JG_clear_Pos[1]>0)   
          JG_pwm=-(JG_clear_Pos[1]/B1P9-sub_p[8]);
       
      }         
      else if(JG_pos_abs>180&&JG_pos_abs<=200)
      {
        if(JG_clear_Pos[1]>0)   
          JG_pwm=-(JG_clear_Pos[1]/B1P10-sub_p[9]);
        
       }
      else if(JG_pos_abs>200&&JG_pos_abs<=220)
      {
        if(JG_clear_Pos[1]>0)   
          JG_pwm=-(JG_clear_Pos[1]/B1P11-sub_p[10]);
     
       }
       else if(JG_pos_abs>220&&JG_pos_abs<=240)
      {
        if(JG_clear_Pos[1]>0)   
          JG_pwm=-(JG_clear_Pos[1]/B1P12-sub_p[11]);
       }
       else if(JG_pos_abs>240&&JG_pos_abs<=260)
      {
        if(JG_clear_Pos[1]>0)   
          JG_pwm=-(JG_clear_Pos[1]/B1P13-sub_p[12]);
       } 
       else if(JG_pos_abs>260)
      {
        if(JG_clear_Pos[1]>0)   
          JG_pwm=-(JG_clear_Pos[1]/B1P14-sub_p[13]);
       }           
    }
/*===========================================================*/ 
    else if(side==-1)
    { 
     JG_clear_Pos[1]=JG_clear[1]-80;
     
     JG_pos_abs=JG_clear_Pos[1];
     JG_pos_abs=aabs(JG_pos_abs);
     
    sub_p[0]=10/B1P1;
    sub_p[1]=20/B1P2-(20/B1P1-sub_p[0]);
    sub_p[2]=40/B1P3-(40/B1P2-sub_p[1]);
    sub_p[3]=60/B1P4-(60/B1P3-sub_p[2]);
    sub_p[4]=80/B1P5-(80/B1P4-sub_p[3]);
    sub_p[5]=100/B1P6-(100/B1P5-sub_p[4]);
    sub_p[6]=120/B1P7-(120/B1P6-sub_p[5]);
    sub_p[7]=140/B1P8-(140/B1P7-sub_p[6]);
    sub_p[8]=160/B1P9-(160/B1P8-sub_p[7]);
    sub_p[9]=180/B1P10-(180/B1P9-sub_p[8]);
    sub_p[10]=200/B1P11-(200/B1P10-sub_p[9]);
    sub_p[11]=220/B1P12-(220/B1P11-sub_p[10]);
    sub_p[12]=240/B1P13-(240/B1P12-sub_p[11]);
    sub_p[13]=260/B1P14-(260/B1P13-sub_p[12]);
    
    sub2_p[0]=10/B2P1;
    sub2_p[1]=20/B2P2-(20/B2P1-sub2_p[0]);
    sub2_p[2]=40/B2P3-(40/B2P2-sub2_p[1]);
    sub2_p[3]=60/B2P4-(60/B2P3-sub2_p[2]);
    sub2_p[4]=80/B2P5-(80/B2P4-sub2_p[3]);
    
    
    if(JG_pos_abs<=10)                            
      JG_pwm=0;
    else if(JG_pos_abs>10&&JG_pos_abs<=20) 
    {
       if(JG_clear_Pos[1]>0)    
       JG_pwm=-(JG_clear_Pos[1]/B2P1);
       else if(JG_clear_Pos[1]<0)
      JG_pwm=0;  //  JG_pwm=-(JG_clear_Pos[1]/B1P1+sub_p[0]); 
    }
    else if(JG_pos_abs>20&&JG_pos_abs<=40) 
    {
       if(JG_clear_Pos[1]>0)    
        JG_pwm=-(JG_clear_Pos[1]/B2P2-sub2_p[0]);
       else  if(JG_clear_Pos[1]<0)
      JG_pwm=0;  //  JG_pwm=-(JG_clear_Pos[1]/B1P2+sub_p[1]);
    }
    else if(JG_pos_abs>40&&JG_pos_abs<=60) 
    {
       if(JG_clear_Pos[1]>0)    
        JG_pwm=-(JG_clear_Pos[1]/B2P3-sub2_p[1]);
       else if(JG_clear_Pos[1]<0)
      JG_pwm=0;  //  JG_pwm=-(JG_clear_Pos[1]/B1P3+sub_p[2]);
    }      
    else if(JG_pos_abs>60&&JG_pos_abs<=80)
    {
       if(JG_clear_Pos[1]>0)    
        JG_pwm=-(JG_clear_Pos[1]/B2P4-sub2_p[2]);
       else if(JG_clear_Pos[1]<0)
       JG_pwm=-(JG_clear_Pos[1]/B1P4+sub_p[3])*get_flag;
    }
    else if(JG_pos_abs>80&&JG_pos_abs<=100)
    {
       if(JG_clear_Pos[1]>0)    
        JG_pwm=-(JG_clear_Pos[1]/B2P5-sub2_p[3]);
      else if(JG_clear_Pos[1]<0)
      JG_pwm=-(JG_clear_Pos[1]/B1P5+sub_p[4])*get_flag;
    }
    else if(JG_pos_abs>100&&JG_pos_abs<=120)
    {
      if(JG_clear_Pos[1]>0)    
        JG_pwm=-(JG_clear_Pos[1]/B2P6-sub2_p[4]);
      else if(JG_clear_Pos[1]<0)
        JG_pwm=-(JG_clear_Pos[1]/B1P6+sub_p[5]) ;
    }
      
    else if(JG_pos_abs>120&&JG_pos_abs<=140)
    {
      
      if(JG_clear_Pos[1]<0)
        JG_pwm=-(JG_clear_Pos[1]/B1P7+sub_p[6]);
    } 
  //=========================================  
    else if(JG_pos_abs>140&&JG_pos_abs<=160) 
    {
      
       if(JG_clear_Pos[1]<0)    
        JG_pwm=-(JG_clear_Pos[1]/B1P8+sub_p[7]);
      
    }      
    else if(JG_pos_abs>160&&JG_pos_abs<=180)
    {
      
      if(JG_clear_Pos[1]<0)   
        JG_pwm=-(JG_clear_Pos[1]/B1P9+sub_p[8]);
      
    }         
    else if(JG_pos_abs>180&&JG_pos_abs<=200)
    {
      
      if(JG_clear_Pos[1]<0)   
        JG_pwm=-(JG_clear_Pos[1]/B1P10+sub_p[9]);
     }
    
    else if(JG_pos_abs>200&&JG_pos_abs<=220)
    {

      if(JG_clear_Pos[1]<0)   
        JG_pwm=-(JG_clear_Pos[1]/B1P11+sub_p[10]);
     }
     else if(JG_pos_abs>220&&JG_pos_abs<=240)
    {
      if(JG_clear_Pos[1]<0)   
        JG_pwm=-(JG_clear_Pos[1]/B1P12+sub_p[11]);
     }
     else if(JG_pos_abs>240&&JG_pos_abs<=260)
    {
      if(JG_clear_Pos[1]<0)   
        JG_pwm=-(JG_clear_Pos[1]/B1P13+sub_p[12]);
     } 
     else if(JG_pos_abs>260)
    {
      if(JG_clear_Pos[1]<0)   
        JG_pwm=-(JG_clear_Pos[1]/B1P14+sub_p[13]);
    }           
  } 
    
    else if(side==2) 
    {
    JG_pwm=0;
    } 
    
   
    //JG_clear_Pos[0]=JG_clear_Pos[1];
    
    if(JG_pwm_his+JG_pwm>2406)
       PWMDTY45=2406;
    else if(JG_pwm_his+JG_pwm<800)
       PWMDTY45=800;
    else
       PWMDTY45=PWMDTY45+JG_pwm;
  }



/*================根据标准的position形成预判的趋势==========================
  int road_point[6];                //5点归为一段  假设2.5m/s 5点为1.8cm
  int point_count;                  //5点计数
  int road_section[8];              //8段归为一长路  同假设8段为15cm
  int section_count;                //8段计数
  此时已经把position的值作为预判的值存储到temp_position_array[i]
  作为一个预判的标准，显然也不是最准确的，每次就只从趋势里面找出一个点
  来给下面打角舵机作为打角的参数。

  BUG：
  比较害怕PWMDTY45在这边没办法用，到时估计要把午餐的函数方法设一下参数， 进行参数传递
  int change_JG_DJ_array[23]={-103,-90,-80,-73,-62,-52,-46,-36,-24,-18,-10,0,10,18,24,36,46,52,62,73,80,90,103}; 
  int standard_position_array[23]=
  //标准position的值
  int temp_position_array[22];
  //用于记录position的值，形成预判的趋势 
  //int last_laser_array[20][11];    
  //这个二维数组作为激光管的历史记录
=========================================================================*/




/*================斜率偏差滤波======================
滤波时两次扩大了十倍   为了在计算斜率时除以速度值后仍然保留有一定数  
和激光相似
*/
void Clear_General(void) 
{

  if(befo_General_pos>=0)
    General_pos=befo_General_pos*0.5016+7.503;
  else 
    General_pos=befo_General_pos*0.5016-7.503 ;

//General_pos[1]=(10*General_pos[0]+130*General_pos[1])/140;
//cha_pos=General_pos[1]-General_pos[0];
//General_pos[0]=General_pos[1];

//General_pos[3]=General_pos[1];
//General_pos[3]=(40*General_pos[2]+100*General_pos[3])/14;
//General_pos[2]=General_pos[3];
}


/*================打角舵机======================
int DP1=15,DP2=13,DP3=11,DP4=10,DP5=8,DP6=7,DP7=6;
*/


void dajiao(byte a)
{
  long speedaffect1=0;
  long speedaffect2=0;
  long speedaffect3=0;
  int speedinfo;
  int changebaitou;          
  int dj_pwm;
  

  
  if(a==0){
    
  
  changebaitou=baitoupwm/10;      //摆头占空比 除
  speedinfo=speed_clear[1]-160;    //基准的速度 如果小于它就不执行速度加入转角

  if(speedinfo>=5)
  {
    speedinfo=speedinfo/5;
    speedaffect1=speedinfo*speedinfo;
    speedaffect2=speedaffect1*changebaitou;
    speedaffect3=speedaffect2/Subu;
   
    //speedaffect=speedinfo*speedinfo*changebaitou/48; 
    //speedaffect[1]=(10*speedaffect[0]+60*speedaffect[1])/70;
     //speedaffect[1]=speedaffect[1];
  }
  if(turn_flag==0)
  {
    dj_pwm=General_pos;
  }
  else if(turn_flag==1)
  {
    dj_pwm=General_pos+speedaffect3; 
  }
  //abs_pos=position;
  //abs_pos=aabs(abs_pos);

  } 
  
  
  else  if(a==1) 
    {
  dj_pwm=IR_position*50;
 //	PWMDTY01=PWM01+dj_pwm;
  
    }
 
  if(dj_pwm>300)
    dj_pwm=300;
  else if(dj_pwm<-300)
    dj_pwm=-300;
  dj_pwm=dj_pwm+PWM01;
  PWMDTY01=dj_pwm;
}


/*=====================电机速度调节======================
long speed_clear[2];                    //速度滤波值  最终结果 此次和上次
float Kp=?;                      //比例常数
float Ki=?;                      //积分常数
float Kd=?;                      //微分常数
int error0=0;                      //当前误差，为目标速度减去当前获取的脉冲值
int error1=0;                      //前一次误差
int error2=0;                      //前前一次的误差
*/


void SpeedCtrl (byte a) 
{
 // int subspeed;
  int changebaitou;
  int his_pwm=PWMDTY23;
  float aim_speed;
  float speed_pwm;
 // float A,B,C; 
//  int abs_error;
  
 if(a==1)
  {
    PORTB_PB7=0;
    PWMDTY23 = 0; 
    PWMDTY6=0;
  }

  else if(a==2)
  {
    PORTB_PB7=1;
    PWMDTY23 = 550; 
    PWMDTY6=7;
  } 
  
  
     else
 
 {
    PORTB_PB7=1;
    PWMDTY6=0;
  changebaitou=baitoupwm;  //速度调节分80段
    if(changebaitou>=300)changebaitou=300;
    else if(changebaitou<=-300)changebaitou=-300;
    
    if(changebaitou>0)
      aim_speed=(-0.3)*changebaitou+350;
    else  
      aim_speed=0.3*changebaitou+350;                    //弯道 偏移和速度的一个假象的关系 没有验证过
   
     error0=aim_speed-speed_clear[1];
     
     if(error0<-50)                  //积分分离
       {
       PWMDTY6=WanSpeed;
       PWMDTY23=0;
       }     
    
      else if(error0>60)
       {
       PWMDTY23=ZhiSpeed;
       PWMDTY6=0;
        
       }
     
      
     else if(error0>=-50&&error0<=60)
       {
       speed_pwm=Kp*(error0-error1)+Ki*error0+Kd*(error0-2*error1+error2);
       
       
       }
       
      error2=error1;                                       //存储误差，用于下次计算
      error1=error0;    
       
      if(his_pwm+speed_pwm>=1667)  
     PWMDTY23=1667;
     else if(his_pwm+speed_pwm<=0) 
     { PWMDTY23=0; }   //daozhuan_flag=1; 
     
     else PWMDTY23=PWMDTY23+speed_pwm;
        
     if(PWMDTY6>208)PWMDTY6=208;
     else if(PWMDTY6<0)PWMDTY6=0;
 
    } 
   
   
    
 }

