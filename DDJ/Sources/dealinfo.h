

/*=====================�����ͷ�˲�======================
long JG_clear[2];                      //����һ�ε����˲� �˴κ��ϴ�
long JG_clear_Pos[2];                  //���뵱ǰ����һ��JG_clear ��ֵ
*/
 
 
void Clear_baitou(void){
//long JG_sum[2];
//JG_clear[3]=JG_clear[1];

JG_clear[1]=position*50;
//JG_clear[1]=(JG_clear[0]*20+JG_clear[1]*70) /90 ;  
JG_clear[0]=JG_clear[1];

//JG_clear[3]=(JG_clear[2]*30+JG_clear[3]*40)/70;
//JG_clear[2]=JG_clear[3]; 
}

  
/*=====================�����ͷ======================
//1881   2602 1160
LASER_MAX         11  10    9    8    7     6     5    4     3     2        1     0
��Ӧ��Ȩֵ        11   9    7    5    3     1    -1   -3    -5    -7       -9   -11
�ֶ�����Ҫ�غ�
int BP1=54,BP2=45,BP3=36,BP4=27,BP5=20;
*/
void  baitou (void) {
    
    int JG_pos_abs=JG_clear[1];
    int JG_pwm;
    int JG_pwm_his=PWMDTY45;
    int sub_p[9];
    int Diff_pos;
    int BD1=4;
    int BD2=2;
    byte BD_flag;
JG_pos_abs=aabs(JG_pos_abs);
JG_clear_Pos[1]=JG_clear[1];
        
Diff_pos=JG_clear_Pos[1]-JG_clear[3];
if((position>0)&&(Diff_pos>0))
BD_flag=1;
else if((position<0)&&(Diff_pos<0))
BD_flag=1;
else BD_flag=0;

sub_p[0]=100/BP1;
sub_p[1]=200/BP2-(200/BP1-sub_p[0]);
sub_p[2]=300/BP3-(300/BP2-sub_p[1]);
sub_p[3]=400/BP4-(400/BP3-sub_p[2]);
sub_p[4]=500/BP5-(500/BP4-sub_p[3]);
sub_p[5]=600/BP6-(600/BP5-sub_p[4]);
sub_p[6]=700/BP7-(700/BP6-sub_p[5]);
sub_p[7]=800/BP8-(800/BP7-sub_p[6]);
sub_p[8]=900/BP9-(900/BP8-sub_p[7]);
    
    if(JG_pos_abs<=100)                             //���Ķ�P 
    JG_pwm=0;
    else if(JG_pos_abs>100&&JG_pos_abs<=200) 
          {
      if(position>0)    
      JG_pwm=(JG_clear_Pos[1]/BP1-sub_p[0]);//+BD_flag*Diff_pos/BD1;
      else if(position<0)
      JG_pwm=(JG_clear_Pos[1]/BP1+sub_p[0]);//+BD_flag*Diff_pos/BD1; 
          }
   
    else if(JG_pos_abs>200&&JG_pos_abs<=300) 
          {
      if(position>0)   
      JG_pwm=(JG_clear_Pos[1]/BP2-sub_p[1]);//+BD_flag*Diff_pos/BD1;
      else if(position<0)
      JG_pwm=(JG_clear_Pos[1]/BP2+sub_p[1]);//+BD_flag*Diff_pos/BD1;
      
          }
    else if(JG_pos_abs>300&&JG_pos_abs<=400) 
          {
      if(position>0)   
      JG_pwm=(JG_clear_Pos[1]/BP3-sub_p[2]);//+BD_flag*Diff_pos/BD1;
      else if(position<0)
      JG_pwm=(JG_clear_Pos[1]/BP3+sub_p[2]);//+BD_flag*Diff_pos/BD1;
          }      
    else if(JG_pos_abs>400&&JG_pos_abs<=500)
          {
      if(position>0)    
      JG_pwm=(JG_clear_Pos[1]/BP4-sub_p[3]);//+BD_flag*Diff_pos/BD2;
      else if(position<0)
      JG_pwm=(JG_clear_Pos[1]/BP4+sub_p[3]);//+BD_flag*Diff_pos/BD2;
          }
    else if(JG_pos_abs>500&&JG_pos_abs<=600)
          {
      if(position>0)    
      JG_pwm=(JG_clear_Pos[1]/BP5-sub_p[4]);//+BD_flag*Diff_pos/BD2;
      else if(position<0)
      JG_pwm=(JG_clear_Pos[1]/BP5+sub_p[4]);//+BD_flag*Diff_pos/BD2;
          }
    
    else if(JG_pos_abs>600&&JG_pos_abs<=700)
          {
      if(position>0)    
      JG_pwm=(JG_clear_Pos[1]/BP6-sub_p[5]);//+BD_flag*Diff_pos/BD2;
      else if(position<0)
      JG_pwm=(JG_clear_Pos[1]/BP6+sub_p[5]);//+BD_flag*Diff_pos/BD2;
          }
    
    else if(JG_pos_abs>700&&JG_pos_abs<=800)
          {
      if(position>0)    
      JG_pwm=(JG_clear_Pos[1]/BP7-sub_p[6]);//+BD_flag*Diff_pos/BD2;
      else if(position<0)
      JG_pwm=(JG_clear_Pos[1]/BP7+sub_p[6]);//+BD_flag*Diff_pos/BD2;
          }                  
    else if(JG_pos_abs>800&&JG_pos_abs<=900) 
          {
      if(position>0)    
      JG_pwm=(JG_clear_Pos[1]/BP8-sub_p[7]);//+BD_flag*Diff_pos/BD2;
      else if(position<0)
      JG_pwm=(JG_clear_Pos[1]/BP8+sub_p[7]);//+BD_flag*Diff_pos/BD2;
          }      
    else if(JG_pos_abs>900)
         {
      if(position>0)   
      JG_pwm=(JG_clear_Pos[1]/BP9-sub_p[8]);//+BD_flag*Diff_pos/BD2;
      else if(position<0)
      JG_pwm=(JG_clear_Pos[1]/BP9+sub_p[8]);//+BD_flag*Diff_pos/BD2;
      
         }                        
   
       
     JG_clear_Pos[0]=JG_clear_Pos[1];
     if(JG_pwm_his+JG_pwm>5528)
     PWMDTY45=5528;
     else if(JG_pwm_his+JG_pwm<1928)
     PWMDTY45=1928;
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




/*================�ۺ�ƫ��======================
˼·�ǰ�ÿ������Ķ��ֵ���ϵ�ǰҡͷ���ֵ ���λ��
ʵ�����ҡͷ����޷������ܿ�Ļ�λ ���ڴ��20ms�� 
��������Ļ� ���ǾͰ�ÿ��ҡͷ�����Ķ�����´δ���ǰ �ȷ�

*/
void General_Position(void)       
{
int num=position+20;    //�������ƫ�ƴ���
baitou_diff=PWMDTY45-PWM45;      //��ͷִ�к�Ĳ�ֵ ���ǰ����ȷ����� 

befo_General_pos=change_JG_DJ_array[num]+baitou_diff;//*baitou_delay/11;
}



/*================б��ƫ���˲�======================
�˲�ʱ����������ʮ��   Ϊ���ڼ���б��ʱ�����ٶ�ֵ����Ȼ������һ����  
�ͼ�������
*/
void Clear_General(void) {

if(befo_General_pos>=0)
General_pos=befo_General_pos*0.5127+19.61;
else General_pos=befo_General_pos*0.5127-19.61;

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


void dajiao(void){
//int abs_pos;

//int sub_p[7];

int changebaitou;
int dj_pwm;
//int speedinfo;
//int abs_affect;

//int speedaffect;
//int code[2]={3,1},sum_code=4;


 changebaitou=baitoupwm/10;      //��ͷռ�ձ� ��
 speedinfo=speed_clear[1]-110;    //��׼���ٶ� ���С�����Ͳ�ִ���ٶȼ���ת��

 
 if(speedinfo>=5)
 {
 speedinfo=speedinfo/4;
 speedaffect1=speedinfo*speedinfo;
 speedaffect2=speedaffect1*changebaitou;
 speedaffect3=speedaffect2/111;
//speedaffect=speedinfo*speedinfo*changebaitou/48; 
 //speedaffect[1]=(10*speedaffect[0]+60*speedaffect[1])/70;
 //speedaffect[1]=speedaffect[1];
 }
// abs_affect=speedaffect[1];
 //abs_affect=aabs(abs_affect); 


if(turn_flag==0)
   {
   dj_pwm=General_pos;
   }


else
   {
   dj_pwm=General_pos+speedaffect3; 
   }

 
  

//abs_pos=position;
//abs_pos=aabs(abs_pos);



       

if(dj_pwm>780)
dj_pwm=780;
else if(dj_pwm<-780)
dj_pwm=-780;

dj_pwm=dj_pwm+PWM01;
PWMDTY01=dj_pwm;
}





/*=====================����ٶȵ���======================*/


void SpeedCtrl (void) {
int subspeed;
int changebaitou;
int okspeed;


PWMDTY23 = 500;      //��ת�̶�
PORTB_PB7=1;

changebaitou=baitoupwm/10;  //�ٶȵ��ڷ�70��

okspeed=-2*changebaitou+320;

subspeed=speed_clear[1]-okspeed;



if(Straight_flag==1)
   {
   PWMDTY6 = 7;      //ռ�ձ�50%     60
   } 
   
else if(Straight_flag==0)
   {
   Straight_stop=1;
   turn_stop=0;
   
   if(subspeed>10)PWMDTY6=61;
   
   else  turn_stop=1;
      
   }
   
   if(turn_stop==1) 
     {
     if(subspeed>10)
     PWMDTY6=30;
     
     else PWMDTY6 = 7;
     }
  




 

    
}          










/*================�ռ�N����Ϊ�����һ��======================
���ʵʱ�ռ����������� ���Զ���Ϊһ���� �������Ϊһ�� ��κ�Ϊһ·
road_point[5]Ϊ����ֵ

void Collect_Point(void) {
int i;
int code[5]={1,2,3,4,5},sum_code=15;   //��Ȩ����ƽ����Ч����Σ� 
long point_sum=0;      //�ۼӹ��������ֵ�ᳬ��32767 ��Ϊ������

if(point_count==4) 
     {
     road_point[4]=befo_General_pos;
     for(i=0;i<=4;i++) 
       {
     point_sum+=road_point[i]*code[i];
     
        }
     point_sum=point_sum/sum_code;
     road_point[5]=point_sum;   
     point_count=0;
     } 
else
    {
    road_point[point_count]=befo_General_pos;
    point_count++;
    }
}
*/
/*================N����Ϊһ�� ���ѭ������ ������======================
����2.5  ��ô����15cmһ�μ����һ�㵽��15cm���б�� ����������� 15cm��Ϊ�˶Զ���ӳٵ�����
 int road_section[8];              //8�ι�Ϊһ��·  ͬ����8��Ϊ15cm
 int section_count;
 ��������15cm  0-7
byte Straight_flag;                     //ֱ�����  ��0��Ч
byte turn_flag;                         //������  ��0��Ч 

void Collect_Section(void){
int i;
int sub_section;

if(first_flag)
  {
  
  }
if(point_count==0)
{  
for(i=19;i>=0;i--) 
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
}



*/


/*================б�ʼ���======================
15cm��б�ʼ��� ��׽�ٶ�ֵ��������
�ٶ� ����200Ϊ2.5M/S  ��ô15cm �ۼ�ֵ���Ϊ6*200
ȡ��б�� ֱ���õ�  

void Judge_Slope(void){
long slop_sum;
if(speed_clera[1]<=230) 
     {
     dajiao_Slope[0]=road_section[0];
     dajiao_Slope[1]=road_section[19];
     slop_sum=(3*dajiao_Slope[0]+dajiao_Slope[1])/4;
     dajiao_Slope[2]=slop_sum;
     } 
else if((speed_clera[1]>230)&&(speed_clera[1]<=270)) 
     {
     dajiao_Slope[0]=road_section[0];
     dajiao_Slope[1]=road_section[18]; 
     slop_sum=(3*dajiao_Slope[0]+dajiao_Slope[1])/4;
     dajiao_Slope[2]=slop_sum;
     } 
else if((speed_clera[1]>270)&&(speed_clera[1]<=310))      
     {
     dajiao_Slope[0]=road_section[0];
     dajiao_Slope[1]=road_section[17]; 
     slop_sum=(3*dajiao_Slope[0]+dajiao_Slope[1])/4;
     dajiao_Slope[2]=slop_sum;
     } 
else      
     {
     dajiao_Slope[0]=road_section[0];
     dajiao_Slope[1]=road_section[16];
     slop_sum=(3*dajiao_Slope[0]+dajiao_Slope[1])/4;
     dajiao_Slope[2]=slop_sum;
     }      
}
*/


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
  temp_position_array[0] = PWMDTY45;
}


*/


