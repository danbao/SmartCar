

/*=====================�����ͷ�˲�======================
long JG_clear[2];                      //����һ�ε����˲� �˴κ��ϴ�
long JG_clear_Pos[2];                  //���뵱ǰ����һ��JG_clear ��ֵ
*/
 
 
void Clear_baitou(void){
//long JG_sum[2];
//JG_clear[3]=JG_clear[1];

if(YDdelay==0)
JG_clear[0]=JG_clear[1];

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
void  baitou (void) {
    
    int JG_pos_abs=JG_clear[1];
    int JG_pwm;
    int JG_pwm_his=PWMDTY45;
    int sub_p[10];
    
    
    int Diff_pos;
    byte BD_flag;
   

   
JG_pos_abs=aabs(JG_pos_abs);
JG_clear_Pos[1]=JG_clear[1];


YDdelay++;
if(YDdelay%10==0||JG_pos_abs>17) 
{
YDdelay=0;  
Diff_pos=JG_clear_Pos[1]-JG_clear[0];
if((JG_clear_Pos[1]>0)&&(Diff_pos>0))//&&(JG_clear[0]>0)
BD_flag=1;
else if((JG_clear_Pos[1]<0)&&(Diff_pos<0))// &&(JG_clear[0]<0)    
BD_flag=1;
else BD_flag=1;
} 

else BD_flag=0;


sub_p[0]=10/BP1;
sub_p[1]=20/BP2-(20/BP1-sub_p[0]);
sub_p[2]=40/BP3-(40/BP2-sub_p[1]);
sub_p[3]=60/BP4-(60/BP3-sub_p[2]);
sub_p[4]=80/BP5-(80/BP4-sub_p[3]);
sub_p[5]=100/BP6-(100/BP5-sub_p[4]);
sub_p[6]=120/BP7-(120/BP6-sub_p[5]);
sub_p[7]=140/BP8-(140/BP7-sub_p[6]);
sub_p[8]=160/BP9-(160/BP8-sub_p[7]);
sub_p[9]=180/BP10-(180/BP9-sub_p[8]);
    
    if(JG_pos_abs<=10)                             //���Ķ�P 
    JG_pwm=0;
    else if(JG_pos_abs>10&&JG_pos_abs<=20) 
          {
      if(position>0)    
      JG_pwm=-(JG_clear_Pos[1]/BP1-sub_p[0]+BD_flag*Diff_pos/BD1);
      else if(position<0)
      JG_pwm=-(JG_clear_Pos[1]/BP1+sub_p[0]+BD_flag*Diff_pos/BD1); 
          }
   
    else if(JG_pos_abs>20&&JG_pos_abs<=40) 
          {
      if(position>0)   
      JG_pwm=-(JG_clear_Pos[1]/BP2-sub_p[1]+BD_flag*Diff_pos/BD2);
      else if(position<0)
      JG_pwm=-(JG_clear_Pos[1]/BP2+sub_p[1]+BD_flag*Diff_pos/BD2);
      
          }
    else if(JG_pos_abs>40&&JG_pos_abs<=60) 
          {
      if(position>0)   
      JG_pwm=-(JG_clear_Pos[1]/BP3-sub_p[2]+BD_flag*Diff_pos/BD3);
      else if(position<0)
      JG_pwm=-(JG_clear_Pos[1]/BP3+sub_p[2]+BD_flag*Diff_pos/BD3);
          }      
    else if(JG_pos_abs>60&&JG_pos_abs<=80)
          {
      if(position>0)    
      JG_pwm=-(JG_clear_Pos[1]/BP4-sub_p[3]+BD_flag*Diff_pos/BD4);
      else if(position<0)
      JG_pwm=-(JG_clear_Pos[1]/BP4+sub_p[3]+BD_flag*Diff_pos/BD4);
          }
    else if(JG_pos_abs>80&&JG_pos_abs<=100)
          {
      if(position>0)    
      JG_pwm=-(JG_clear_Pos[1]/BP5-sub_p[4]+BD_flag*Diff_pos/BD5);
      else if(position<0)
      JG_pwm=-(JG_clear_Pos[1]/BP5+sub_p[4]+BD_flag*Diff_pos/BD5);
          }
    
    else if(JG_pos_abs>100&&JG_pos_abs<=120)
          {
      if(position>0)    
      JG_pwm=-(JG_clear_Pos[1]/BP6-sub_p[5]+BD_flag*Diff_pos/BD6);
      else if(position<0)
      JG_pwm=-(JG_clear_Pos[1]/BP6+sub_p[5]+BD_flag*Diff_pos/BD6);
          }
    
    else if(JG_pos_abs>120&&JG_pos_abs<=140)
          {
      if(position>0)    
      JG_pwm=-(JG_clear_Pos[1]/BP7-sub_p[6]+BD_flag*Diff_pos/BD7);
      else if(position<0)
      JG_pwm=-(JG_clear_Pos[1]/BP7+sub_p[6]+BD_flag*Diff_pos/BD7);
          }                  
    else if(JG_pos_abs>140&&JG_pos_abs<=160) 
          {
      if(position>0)    
      JG_pwm=-(JG_clear_Pos[1]/BP8-sub_p[7]+BD_flag*Diff_pos/BD8);
      else if(position<0)
      JG_pwm=-(JG_clear_Pos[1]/BP8+sub_p[7]+BD_flag*Diff_pos/BD8);
          }      
    else if(JG_pos_abs>160&&JG_pos_abs<=180)
         {
      if(position>0)   
      JG_pwm=-(JG_clear_Pos[1]/BP9-sub_p[8]+BD_flag*Diff_pos/BD9);
      else if(position<0)
      JG_pwm=-(JG_clear_Pos[1]/BP9+sub_p[8]+BD_flag*Diff_pos/BD9);
      
         }   
         
    else if(JG_pos_abs>180)
         {
      if(position>0)   
      JG_pwm=-(JG_clear_Pos[1]/BP10-sub_p[9]+BD_flag*Diff_pos/BD10);
      else if(position<0)
      JG_pwm=-(JG_clear_Pos[1]/BP10+sub_p[9]+BD_flag*Diff_pos/BD10);
      
         }                             
   
       
     JG_clear_Pos[0]=JG_clear_Pos[1];
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




/*================�ۺ�ƫ��======================
˼·�ǰ�ÿ������Ķ��ֵ���ϵ�ǰҡͷ���ֵ ���λ��
ʵ�����ҡͷ����޷������ܿ�Ļ�λ ���ڴ��20ms�� 
��������Ļ� ���ǾͰ�ÿ��ҡͷ�����Ķ�����´δ���ǰ �ȷ�

*/
void General_Position(void)       
{
int num=position+20;    //�������ƫ�ƴ���
baitou_diff=PWMDTY45-PWM45;      //��ͷִ�к�Ĳ�ֵ ���ǰ����ȷ����� 

befo_General_pos=-(change_JG_DJ_array[num]+baitou_diff);//*baitou_delay/11;
}



/*================б��ƫ���˲�======================
�˲�ʱ����������ʮ��   Ϊ���ڼ���б��ʱ�����ٶ�ֵ����Ȼ������һ����  
�ͼ�������
*/
void Clear_General(void) {

if(befo_General_pos>=0)
General_pos=befo_General_pos*0.5016+4.503;
else General_pos=befo_General_pos*0.5016-4.503;

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


 changebaitou=baitoupwm/20;      //��ͷռ�ձ� ��
 speedinfo=speed_clear[1]-110;    //��׼���ٶ� ���С�����Ͳ�ִ���ٶȼ���ת��

 
 if(speedinfo>=5)
 {
 speedinfo=speedinfo/4;
 speedaffect1=speedinfo*speedinfo;
 speedaffect2=speedaffect1*changebaitou;
 speedaffect3=speedaffect2/115;
 
//speedaffect=speedinfo*speedinfo*changebaitou/48; 
 //speedaffect[1]=(10*speedaffect[0]+60*speedaffect[1])/70;
 //speedaffect[1]=speedaffect[1];
 }
 

 
 



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



       

if(dj_pwm>315)
dj_pwm=315;
else if(dj_pwm<-315)
dj_pwm=-315;

dj_pwm=dj_pwm+PWM01;
PWMDTY01=dj_pwm;
}



/*=====================����ٶȵ���======================*/


void SpeedCtrl (byte a) {
int subspeed;
int changebaitou;
int okspeed;
if(a==1)
{
  PORTB_PB7=0;
}
else if(a==2){
 PORTB_PB7=1;
 PWMDTY23 = 500; 
 PWMDTY6=7;
}
else
{
PWMDTY23 = 500;      //��ת�̶�
PORTB_PB7=1;



changebaitou=baitoupwm/10;  //�ٶȵ��ڷ�70��

if(changebaitou>0)okspeed=-2*changebaitou+320;
else  okspeed=2*changebaitou+320;                    //��� ƫ�ƺ��ٶȵ�һ������Ĺ�ϵ û����֤��


subspeed=speed_clear[1]-okspeed;                   //��ǰ�ٶ�������ٶȹ�ϵ



if(Straight_flag==1)
   {
   PWMDTY6 = 7;      //ռ�ձ�50%     60              //ֱ�߼��ٺ�ռ�ձ�
   } 
   
else if(Straight_flag==0)                            //���
   {
   
    if(diansha_count%diansha_num==0)
    {diansha_count=0;diansha_falg=0;  }
    
    if(diansha_falg) 
    {PWMDTY6=70;PWMDTY23 =10;diansha_count++;} 
    else  {PWMDTY23 = 500; PWMDTY6=7;}
   }

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


