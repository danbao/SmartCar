




/*=====================�����ͷ�˲�======================
long JG_clear[2];                      //����һ�ε����˲� �˴κ��ϴ�
long JG_clear_Pos[2];                  //���뵱ǰ����һ��JG_clear ��ֵ
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

  
/*=====================����ܶ�ӦȨֵ======================
LASER_MAX     20   19   18   17   16   15  14  13  12  11  10    9    8    7     6     5     4     3    2     1     0
��Ӧ��Ȩֵ    20   18   16   14   12   10   8   6   4   2   0   -2   -4    -6    -8   -10  -12   -14   -16   -18   -20
�ֶ�����Ҫ�غ�
int BP1=54,BP2=45,BP3=36,BP4=27,BP5=20;
*/
void  baitou (void) 
{
    
  int JG_pos=JG_clear[1];
  int JG_pos_abs;
  int JG_pwm;
  int JG_pwm_his=PWMDTY45;
  int sub_p[20],sub2_p[20];
  int sub_baitou;
 // int abs_baitoupwm;
  
 
 
  
 
  
  if((baitou_diff[1]<=150&&baitou_diff[1]>=-150))//ֱ�����
  { //if(position>14)
    //side=1;
    //else if(position<-14)
    //side=-1;
    //else
   baitou_begin=0; 
   get_flag=1;  
   side=0;
  } 
  
  
  
  else if(baitou_diff[1]<-150&&baitou_begin==0) //������
  {
      side=1;
     // side_baipwm=baitou_diff[1]-baitou_diff[0]; 
      if(position<=-4&&get_flag==1) 
      { 
       get_flag=0;
       side_baipwm=baitou_diff[1];  
      }
      
 
   
  
 if(side==1&&get_flag==0){
  
 if(position<=-12) {side=0;baitou_begin=1; }
 }
  } 
 
  else if(baitou_diff[1]>150&&baitou_begin==0) //�ұ����
  {
  side=-1;
   
      if(position>=4&&get_flag==1)
      { 
         get_flag=0;
         side_baipwm=baitou_diff[1];  
      }
   
   if(side==-1&&get_flag==0){
    
   if(position>=12) {side=0;baitou_begin=1; }
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



/*================���ݱ�׼��position�γ�Ԥ�е�����==========================
  int road_point[6];                //5���Ϊһ��  ����2.5m/s 5��Ϊ1.8cm
  int point_count;                  //5�����
  int road_section[8];              //8�ι�Ϊһ��·  ͬ����8��Ϊ15cm
  int section_count;                //8�μ���
  ��ʱ�Ѿ���position��ֵ��ΪԤ�е�ֵ�洢��temp_position_array[i]
  ��Ϊһ��Ԥ�еı�׼����ȻҲ������׼ȷ�ģ�ÿ�ξ�ֻ�����������ҳ�һ����
  ���������Ƕ����Ϊ��ǵĲ�����

  BUG��
  �ȽϺ���PWMDTY45�����û�취�ã���ʱ����Ҫ����͵ĺ���������һ�²����� ���в�������
  int change_JG_DJ_array[23]={-103,-90,-80,-73,-62,-52,-46,-36,-24,-18,-10,0,10,18,24,36,46,52,62,73,80,90,103}; 
  int standard_position_array[23]=
  //��׼position��ֵ
  int temp_position_array[22];
  //���ڼ�¼position��ֵ���γ�Ԥ�е����� 
  //int last_laser_array[20][11];    
  //�����ά������Ϊ����ܵ���ʷ��¼
=========================================================================*/




/*================б��ƫ���˲�======================
�˲�ʱ����������ʮ��   Ϊ���ڼ���б��ʱ�����ٶ�ֵ����Ȼ������һ����  
�ͼ�������
*/
void Clear_General(void) 
{

  if(befo_General_pos>=0)
    General_pos=befo_General_pos*0.5016+4.503;
  else 
    General_pos=befo_General_pos*0.5016-7.503 ;

//General_pos[1]=(10*General_pos[0]+130*General_pos[1])/140;
//cha_pos=General_pos[1]-General_pos[0];
//General_pos[0]=General_pos[1];

//General_pos[3]=General_pos[1];
//General_pos[3]=(40*General_pos[2]+100*General_pos[3])/14;
//General_pos[2]=General_pos[3];
}


/*================��Ƕ��======================
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
    
  
  changebaitou=baitoupwm/10;      //��ͷռ�ձ� ��
  speedinfo=speed_clear[1]-120;    //��׼���ٶ� ���С�����Ͳ�ִ���ٶȼ���ת��

  if(speedinfo>=5)
  {
    speedinfo=speedinfo/20;
    speedaffect1=speedinfo*speedinfo;
    speedaffect2=speedaffect1*changebaitou;
    speedaffect3=speedaffect2/10;
   
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


/*=====================����ٶȵ���======================
long speed_clear[2];                    //�ٶ��˲�ֵ  ���ս�� �˴κ��ϴ�
float Kp=?;                      //��������
float Ki=?;                      //���ֳ���
float Kd=?;                      //΢�ֳ���
int error0=0;                      //��ǰ��ΪĿ���ٶȼ�ȥ��ǰ��ȡ������ֵ
int error1=0;                      //ǰһ�����
int error2=0;                      //ǰǰһ�ε����
*/


void SpeedCtrl (byte a) 
{
 // int subspeed;
  int changebaitou;
  int his_pwm=PWMDTY23;
  float aim_speed;
  float speed_pwm;
  float A,B,C; 
  int abs_error;
  
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
    
  changebaitou=baitoupwm;  //�ٶȵ��ڷ�80��
    if(changebaitou>300)changebaitou=300;
    else if(changebaitou<-300)changebaitou=-300;
    
    if(changebaitou>0)
      aim_speed=(-0.7486)*changebaitou+400;
    else  
      aim_speed=0.7486*changebaitou+400;                    //��� ƫ�ƺ��ٶȵ�һ������Ĺ�ϵ û����֤��
   
     error0=aim_speed-speed_clear[1];
     
   /*  if(error0<=-200)                  //���ַ���
       {
       PWMDTY6=30;
       PWMDTY23=0;
       }     
   
    */  
     // else if(error0>=-200)
    //   {
       A=Kp*(1+Ki+Kd);
       B=Kp*(1+2*Kd);
       C=Kp*(Kd);
       speed_pwm=A*error0+B*error1+C*error2;
       
       PWMDTY6=0;
    //   }
      error2=error1;                                       //�洢�������´μ���
      error1=error0;    
       
      if(his_pwm+speed_pwm>=625)  
     PWMDTY23=625;
     else if(his_pwm+speed_pwm<=0) 
     { PWMDTY23=0;daozhuan_flag=1;  }
     else PWMDTY23=PWMDTY23+speed_pwm;
        
  
 
    }      
   
   
    
 }

