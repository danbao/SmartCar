/*==========================���ܼ��=======================*/
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


/*==========================ʮ�ּ��=====================*/
int Confirm_Cross(void){
if(special_flag>=5)
return 1;
else return 0;
}


/*==================��������============================
i-(7-position/2)>3    �ų�
���㣺����������������� ����ͬ
�����־Direction       
byte Straight_flag;                     //ֱ�����  ��0��Ч
byte turn_flag;        
*/
void Confirm_Light(){
 int i=0;    //changeposition ��position��λ�õ�ת�������Ƶ�
 int start_count,cross_count;      //��ʼ��ʮ�ּ���
 int abs_baitoupwm;
 int aabs_pos;
 
 
 
 baitoupwm=befo_General_pos;          
 abs_baitoupwm=baitoupwm;
 abs_baitoupwm=aabs(abs_baitoupwm);
 
 aabs_pos=position;
 aabs_pos=aabs(aabs_pos);
 
 HitBlackNum=0;
 special_flag=0;
 
 start_count=0;
 cross_count=0;
 start_flag=0;
 cross_flag=0; 
 calculate_light();
 



 if(HitBlackNum==0)
     {
     nothing_flag=1;
     //if((aabs_pos<=20)&&(aabs_pos>17))nothing_flag=1;
     
     }
 
 else  
  {
  nothing_flag=0;
  Status_Judge();
  }
  
 
 
 if(abs_baitoupwm>60)
     { 
      if(Straight_flag)
      {diansha_falg=1;diansha_num=speed_clear[1]/15;diansha_num=aabs(diansha_num);}             //��һ�μ�⵽��� �궨��ɲ��ʼ  ��ɲʱ��Ϊ�ٶȳ���10
     
      turn_flag=1;Straight_flag=0;
      } 
 
 else 
  {
  if(Straight_flag==1) 
  {turn_flag=0;Straight_flag=1; } 
  else if((turn_flag==1)&&(abs_baitoupwm>5))
  {turn_flag=1;Straight_flag=0;}  
  else if((turn_flag==1)&&(abs_baitoupwm<=5)) 
  {turn_flag=0;Straight_flag=1;diansha_falg=0;}        //���䲹��Ƕ� �Է� ��û��ȫ�����ת�Ǿͱ�С
  } 
  
  
  
 
}





/*==========================������ ���������պڸ�������������==========*/
void calculate_light(void){
 int i=0,changeposition;
 changeposition=10+position/2;
 for(i=0;i<LASER_MAX;i++) {
  if (light_temp_laser_array[i]==0) continue;
  else if (light_temp_laser_array[i]==1)// &&(aabs(i-changeposition)<=6)
  {
  
  HitBlackNum++;
  }
   
 }

}
/*=====================����ܶ�ӦȨֵ======================
LASER_MAX     20   19   18   17   16   15  14  13  12  11  10    9    8    7     6     5     4     3    2     1     0
��Ӧ��Ȩֵ    20   18   16   14   12   10   8   6   4   2   0   -2   -4    -6    -8   -10  -12   -14   -16   -18   -20
                                                 
����δ��ɣ������в����ͷ���ֵ����Ҫ������ϵ��  

==========================================================*/

void Laser_num(void){
  int i;
  for(i=0;i<=LASER_MAX;i++){
    q_temp_laser_num[i]=-20+2*i;
  }
}

/*=====================�����λ�õ��ж�======================

Ȩֵ��ʽ��  position= �ƣ�light[i]*lightnum[i]�� / blacknum  
Light[i]Ϊ��i���������ֵ 0��1   ight_temp_laser_array[3]
Lightnum Ϊ��1ֵ   q_temp_laser_num[LASER_MAX]
blacknumΪ�պڸ���
                                                          
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



/*=====================����̶ܳ�ֵ======================
������ʱ������Ϊ����С �� ��  ԽС�����Խ��
��Ϊ���Ȿ��ɼ��Ƚ��������Բ���Ҫ�˲���Ŀǰ��û���ܸ��ŵ����?
���������ֵ���������� ��ö�ٷ� ��ֵ���ܻ�Ƚϴ� ���Կ���Ҫ��ȥ��׼ֵ 

      6   5   4   3   2   1   0
      6   4   2   0  -2  -4   -6       IR_position[1]=-6+2*i  �˴�
                                       IR_position[0]�ϴ�
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

/*===================�ٶȹ���=============================
���ڱ����̲�׽����ʱ��Ҳ�᲻�ȶ�
������һ�β��ȿ���ƽ�� ���ȶ�
*/
void Clear_Speed(void) {
//long Speed_sum;
//speed_clear[1]=(60*speed_clear[0]+20*speed_clear[1])/80;
//speed_clear[0]=speed_clear[1];
}



















/*===================����ת��=============================
double Calculate_speed(double temp_pulse)
{
	double a=24,b=76,c=160;//aΪ�������ĳ��֣�bΪ���������ĳ��֣�cΪ����תһȦ�ľ��루���ף�
	double v;
	v=temp_pulse*b*c/2000*a;//
	return v;
}

*/

/*=====================������յ����ߵĸ���======================
�ϲ���control 

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