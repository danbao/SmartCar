

/*=====================�����ͷ�˲�======================
long JG_clear[2];                      //����һ�ε����˲� �˴κ��ϴ�
long JG_clear_Pos[2];                  //���뵱ǰ����һ��JG_clear ��ֵ
*/
 
 
void Clear_baitou(void){
//long JG_sum[2];
JG_clear[1]=position*100;
JG_clear[1]=(JG_clear[0]*40+JG_clear[1]*100) /140 ; 
JG_clear[0]=JG_clear[1]; 

}

  
/*=====================�����ͷ======================
//1881   2602 1160
LASER_MAX         11  10    9    8    7     6     5    4     3     2        1     0
��Ӧ��Ȩֵ        11   9    7    5    3     1    -1   -3    -5    -7       -9   -11
�ֶ�����Ҫ�غ�
*/
void  baitou (void) {
    
    int JG_pos_abs=JG_clear[1];
    int JG_pwm;
    int JG_pwm_his=PWMDTY67;
    
    JG_pos_abs=aabs(JG_pos_abs);
    JG_clear_Pos[1]=JG_clear[1];
    
    
    if(JG_pos_abs<=60)                             //���Ķ�P 
    JG_pwm=0;
    else if(JG_pos_abs>60&&JG_pos_abs<=300) 
          {
      JG_pwm=JG_clear_Pos[1]/54;
          }
    else if(JG_pos_abs>300&&JG_pos_abs<=400) 
          {
      if(position>0)   
      JG_pwm=JG_clear_Pos[1]/30-4;
      else if(position<0)
      JG_pwm=JG_clear_Pos[1]/30+4;
      
          }
    else if(JG_pos_abs>400&&JG_pos_abs<=800) 
          {
      if(position>0)    
      JG_pwm=JG_clear_Pos[1]/18-13;
      else if(position<0)
      JG_pwm=JG_clear_Pos[1]/18+13;
          }
    else if(JG_pos_abs>800&&JG_pos_abs<=1100)
         {
      if(position>0)   
      JG_pwm=JG_clear_Pos[1]/12-35;
      else if(position<0)
      JG_pwm=JG_clear_Pos[1]/12+35;
      
         }
   
       
     JG_clear_Pos[0]=JG_clear_Pos[1];
     if(JG_pwm_his+JG_pwm>2602)
     PWMDTY67=2602;
     else if(JG_pwm_his+JG_pwm<1160)
     PWMDTY67=1160;
     else
     PWMDTY67=PWMDTY67+JG_pwm;
    
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
�ȽϺ���PWMDTY67�����û�취�ã���ʱ����Ҫ����͵ĺ���������һ�²����� ���в�������
 int change_JG_DJ_array[23]={-103,-90,-80,-73,-62,-52,-46,-36,-24,-18,-10,0,10,18,24,36,46,52,62,73,80,90,103}; 
 int standard_position_array[23]=
  //��׼position��ֵ
  int temp_position_array[22];
  //���ڼ�¼position��ֵ���γ�Ԥ�е����� 
//int last_laser_array[20][11];    
//�����ά������Ϊ����ܵ���ʷ��¼
=========================================================================*/




/*================�ۺ�ƫ��======================
˼·�ǰ�ÿ������Ķ��ֵ���ϵ�ǰҡͷ���ֵ ���λ��
ʵ�����ҡͷ����޷������ܿ�Ļ�λ ���ڴ��20ms�� 
��������Ļ� ���ǾͰ�ÿ��ҡͷ�����Ķ�����´δ���ǰ �ȷ�

*/
void General_Position(void)       
{
int num=position+11;    //�������ƫ�ƴ���
 baitou_diff=PWMDTY67-PWM67;      //��ͷִ�к�Ĳ�ֵ ���ǰ����ȷ����� 

befo_General_pos=change_JG_DJ_array[num]+baitou_diff;//*baitou_delay/11;
}


/*================�ռ�N����Ϊ�����һ��======================
���ʵʱ�ռ����������� ���Զ���Ϊһ���� �������Ϊһ�� ��κ�Ϊһ·
road_point[5]Ϊ����ֵ
*/
void Collect_Point(void) {
int i;
int code[5]={1,2,3,4,5},sum_code=15;   //��Ȩ����ƽ����Ч����Σ� 
long point_sum=0;      //�ۼӹ��������ֵ�ᳬ��32767 ��Ϊ������

if(point_count==4) 
     {
     road_point[4]=befo_General_pos;
     for(i=0;i<=4;i++) 
       {
     point_sum+=road_point[i];
     
        }
     point_sum=point_sum/5;
     road_point[5]=point_sum;   
     point_count=0;
     } 
else
    {
    road_point[point_count]=befo_General_pos;
    point_count++;
    }
}

/*================N����Ϊһ�� ���ѭ������ ������======================
����2.5  ��ô����15cmһ�μ����һ�㵽��15cm���б�� ����������� 15cm��Ϊ�˶Զ���ӳٵ�����
 int road_section[8];              //8�ι�Ϊһ��·  ͬ����8��Ϊ15cm
 int section_count;
 ��������15cm  0-7
*/
void Collect_Section(void){
int i;
if(point_count==0)
for(i=23;i>=0;i--) 
   {
   if(i==0) 
      {
  // speed[0]=speed_clera[1];
   road_section[0]=road_point[5];
      }
   else 
      { 
   road_section[i]=road_section[i-1];
  // speed[i]=speed[i-1];
      }
   }
}






/*================б�ʼ���======================
15cm��б�ʼ��� ��׽�ٶ�ֵ��������
�ٶ� ����200Ϊ2.5M/S  ��ô15cm �ۼ�ֵ���Ϊ6*200
ȡ��б�� ֱ���õ�  
*/
void Judge_Slope(void){
//int sub_speed;
if(speed_clera[1]<=158) 
     {
     dajiao_Slope[0]=road_section[0];
     dajiao_Slope[1]=road_section[23];
     dajiao_Slope[2]=(3*dajiao_Slope[0]+dajiao_Slope[1])/4;
     } 
else if((speed_clera[1]>158)&&(speed_clera[1]<=177)) 
     {
     dajiao_Slope[0]=road_section[0];
     dajiao_Slope[1]=road_section[21]; 
     dajiao_Slope[2]=(3*dajiao_Slope[0]+dajiao_Slope[1])/4;
     } 
else if((speed_clera[1]>177)&&(speed_clera[1]<=195))      
     {
     dajiao_Slope[0]=road_section[0];
     dajiao_Slope[1]=road_section[19]; 
     dajiao_Slope[2]=(3*dajiao_Slope[0]+dajiao_Slope[1])/4;
     } 
else      
     {
     dajiao_Slope[0]=road_section[0];
     dajiao_Slope[1]=road_section[17];
     dajiao_Slope[2]=(3*dajiao_Slope[0]+dajiao_Slope[1])/4; 
     }      
}

/*================б��ƫ���˲�======================
�˲�ʱ����������ʮ��   Ϊ���ڼ���б��ʱ�����ٶ�ֵ����Ȼ������һ����  
�ͼ�������
*/
void Clear_General(void) {

General_pos[1]=dajiao_Slope[2]*10;
General_pos[1]=(40*General_pos[0]+100*General_pos[1])/140;
General_pos[0]=General_pos[1];

//General_pos[3]=General_pos[1];
//General_pos[3]=(40*General_pos[2]+100*General_pos[3])/14;
//General_pos[2]=General_pos[3];
}


/*================��Ƕ��======================*/


void dajiao(void){
int zhuan,zhuan_abs;
int dj_pwm;
//int code[2]={3,1},sum_code=4;

zhuan=General_pos[1];
zhuan_abs=zhuan;
zhuan_abs=aabs(zhuan_abs);

if(zhuan_abs<=100)
dj_pwm=0;

else if((zhuan_abs>100)&&zhuan_abs<=1000) 
    {
   if(befo_General_pos>0)
   dj_pwm=zhuan/50;
   else if(befo_General_pos<0)
   dj_pwm=zhuan/50; 
    }
else if((zhuan_abs>1000)&&zhuan_abs<=2000)
    {
   if(befo_General_pos>0)
   dj_pwm=zhuan/45-2;
   else if(befo_General_pos<0)
   dj_pwm=zhuan/45+2; 
    }

else if((zhuan_abs>2000)&&zhuan_abs<=3000)
    {
   if(befo_General_pos>0)
   dj_pwm=zhuan/40-7;
   else if(befo_General_pos<0)
   dj_pwm=zhuan/40+7; 
    }

else if((zhuan_abs>3000)&&zhuan_abs<=4000)
    {
   if(befo_General_pos>0)
   dj_pwm=zhuan/35-17;
   else if(befo_General_pos<0)
   dj_pwm=zhuan/35+17; 
    }

else if((zhuan_abs>4000)&&zhuan_abs<=5000) 
    {
   if(befo_General_pos>0)
   dj_pwm=zhuan/30-35;
   else if(befo_General_pos<0)
   dj_pwm=zhuan/30+35; 
    }


else if((zhuan_abs>5000)&&zhuan_abs<=6000)

    {
   if(befo_General_pos>0)
   dj_pwm=zhuan/25-68;
   else if(befo_General_pos<0)
   dj_pwm=zhuan/25+68; 
    }

else if((zhuan_abs>6000))

    {
   if(befo_General_pos>0)
   dj_pwm=zhuan/20-120;
   else if(befo_General_pos<0)
   dj_pwm=zhuan/20+120; 
    }

if(dj_pwm>287)
dj_pwm=287;
else if(dj_pwm<-287)
dj_pwm=-287;

dj_pwm=dj_pwm+PWM45;

PWMDTY45=dj_pwm;
}






/*=====================����ٶȵ���======================*/


void SpeedCtrl (void) {
int subspeed;
subspeed=speed_clera[1]-150;
//PORTB_PB7=1;
//PWMDTY01 = 25;      //ռ�ձ�10%
//PWMDTY23 = 60;      //ռ�ձ�50%
 
if ((subspeed<=10)&&(subspeed>=-10));
else if((subspeed>10)&&(subspeed<=35)) 
    {
PORTB_PB7=1;
PWMDTY01= 60;
PWMDTY23 = 30;
    }
else if(subspeed>35) 
    {  
PORTB_PB7=1;
PWMDTY01= 80;
PWMDTY23 = 50;
    }
else if((subspeed<-10)&&(subspeed>=-35)) 
   {
PORTB_PB7=1;
PWMDTY23=PWMDTY23-3*subspeed;
PWMDTY01= 0; 
   }
else if(subspeed<-35)
   {
  
PORTB_PB7=1;
PWMDTY23=80;
PWMDTY01= 0;
   }         


}          








/*

void Tendency_judge(void) 
{
//���Ƕ�һ�����Ƶ��жϣ���Ҫ�����������������֮�����֣�����ֱ�����ֱ�ߡ�
  int i,temp;
  temp=temp_position_array[9];
  for(i=0;i<10;i++) 
  {
    if(temp_position_array[i]==temp) 
    {
    //ֱ�Ӱ��ٶȣ����¶����д��������ʱ���ܹ��������ڷֿ���
    
    
    
    
     
    }
    else   ;
  //    dajiao((temp_position_array[i]+temp)/2);//����ͼֻ�ҳ�һ���㣬Ȼ����аڽǣ��滻�滻�������е���
                  
  }
}

void Replace_array(void)
{
  int i;
//�������ּ���滻���Ƶ���ʷ���飬�������һ������滻
  for(i=9;i>0;i--)
  {             //������ʷ״̬
    temp_position_array[i] =  temp_position_array[i-1];   
  }
  temp_position_array[0] = PWMDTY67;
}


*/


/*=======================��Ƕ��===========================
//GDiff_Position�Ǵ洢 ҡͷ�����ֵ ������ǵĲ���
//  1482   1772  1192
   
 
void dajiao(void) {
    
    int ZhuanPwm=0;
    GDiff_Position[1]=PWMDTY67-PWM67;
    GDiff_Position[2]=PWMDTY67-PWM67;
    GDiff_Position[2]=aabs(GDiff_Position[2]);
    His_Position[3]=position;
    His_Position[3]=aabs(His_Position[3]);
    J_His_Position[1]=position;
    J_His_Position[2]=J_His_Position[1]-J_His_Position[0];
   
    if(GDiff_Position[2]<=7&&His_Position[3]<=1)
    ZhuanPwm=PWM45;
    else{  
    if(GDiff_Position[2]<=14)
    ZhuanPwm=PWM45-(6*position+3.2*GDiff_Position[1])-2.9*(J_His_Position[2]+GDiff_Position[1]-GDiff_Position[0]);
    else if(GDiff_Position[2]>14&&GDiff_Position[2]<=24)
    ZhuanPwm=PWM45-(8*position+5.5*GDiff_Position[1])-2.9*(J_His_Position[2]+GDiff_Position[1]-GDiff_Position[0]);
    else if(GDiff_Position[2]>24&&GDiff_Position[2]<=40)
    ZhuanPwm=PWM45-(11*position+7.1*GDiff_Position[1])-2.9*(J_His_Position[2]+GDiff_Position[1]-GDiff_Position[0]);
    else if(GDiff_Position[2]>40&&GDiff_Position[2]<=60)
    ZhuanPwm=PWM45-(14*position+9.1*GDiff_Position[1])-2.9*(J_His_Position[2]+GDiff_Position[1]-GDiff_Position[0]);
    else if(GDiff_Position[2]>60&&GDiff_Position[2]<=80)
    ZhuanPwm=PWM45-(17*position+11.1*GDiff_Position[1])-2.9*(J_His_Position[2]+GDiff_Position[1]-GDiff_Position[0]);
    else if(GDiff_Position[2]>80)
    ZhuanPwm=PWM45-(19*position+13.1*GDiff_Position[1])-2.9*(J_His_Position[2]+GDiff_Position[1]-GDiff_Position[0]);
    }
    if(ZhuanPwm>1768)
    ZhuanPwm=1768;
    else if(ZhuanPwm<1188)
    ZhuanPwm=1188;
    
    PWMDTY45=ZhuanPwm;
    GDiff_Position[0]=GDiff_Position[1]; 
    J_His_Position[0]=J_His_Position[1];
  } // DerectionCtrl


*/
























/*=====================�����ͷ����ı亯��======================
void Light_SetDriver(int value){
  PWMDTY67 = value; 
}
void SCI_SetDriver(int value){
  PWMDTY45 = value; 
}

*/


