
/*==========================���ܼ��=======================*/
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

/*==========================ʮ�ּ��=====================
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

/*==================��������============================
i-(7-position/2)>3    �ų�
���㣺����������������� ����ͬ
�����־Direction       
byte Straight_flag;                     //ֱ�����  ��0��Ч
byte turn_flag;        
byte really_special_flag=0;                //���� ���ܻ���ʮ�� Ҳ�п������µ�
byte maybe_special_flag=0;                 //�������ܵ�����  Ϊ�µ�
byte start_flag=0,cross_flag=0;             //���� ʮ�ֱ�־
byte slope_flag=0;
byte slope_count=0;                         //�µ���ʮ��ʱ�տռ���
byte maybe_count=0;                         //�����µ���ʮ�ֵĳ������м���
========================================================*/

void Confirm_Light()
{
  int i=0,j=0;    //changeposition ��position��λ�õ�ת�������Ƶ�
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
      
      	
    else if(HitBlackNum<=4&&(position>=-12&&position<=12))
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
   
   
//==========================���ֱ���ж�=======
    if(abs_baitoupwm>100)
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
      else if((turn_flag==1)&&(abs_baitoupwm>30))
      {
        turn_flag=1;Straight_flag=0;
      }  
      else if((turn_flag==1)&&(abs_baitoupwm<=30)) 
      {
        turn_flag=0;Straight_flag=1;
      }        //���䲹��Ƕ� �Է� ��û��ȫ�����ת�Ǿͱ�С
    } 
}


/*================�ۺ�ƫ��======================
˼·�ǰ�ÿ������Ķ��ֵ���ϵ�ǰҡͷ���ֵ ���λ��
ʵ�����ҡͷ����޷������ܿ�Ļ�λ ���ڴ��20ms�� 
��������Ļ� ���ǾͰ�ÿ��ҡͷ�����Ķ�����´δ���ǰ �ȷ�

*/
void General_Position(void)       
{
  int num=position+20;    //�������ƫ�ƴ���
  baitou_diff[0]=baitou_diff[1];
  baitou_diff[1]=PWMDTY45-PWM45;      //��ͷִ�к�Ĳ�ֵ ���ǰ����ȷ����� 
  befo_General_pos=-(change_JG_DJ_array[num]+baitou_diff[1]);//*baitou_delay/11;
}



/*==========================������ ���������պڸ�������������==========*/
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

/*=====================����ܶ�ӦȨֵ======================
LASER_MAX     20   19   18   17   16   15  14  13  12  11  10    9    8    7     6     5     4     3    2     1     0
��Ӧ��Ȩֵ    20   18   16   14   12   10   8   6   4   2   0   -2   -4    -6    -8   -10  -12   -14   -16   -18   -20
                                                 
����δ��ɣ������в����ͷ���ֵ����Ҫ������ϵ��  

==========================================================*/

void Laser_num(void)
{
  int i;
  for(i=0;i<=LASER_MAX;i++)
  {
    q_temp_laser_num[i]=-20+2*i;
  }
}

/*=====================�����λ�õ��ж�======================

Ȩֵ��ʽ��  position= �ƣ�light[i]*lightnum[i]�� / blacknum  
Light[i]Ϊ��i���������ֵ 0��1   ight_temp_laser_array[3]
Lightnum Ϊ��1ֵ   q_temp_laser_num[LASER_MAX]
blacknumΪ�պڸ���
                                                          
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
void Clear_Speed(void) 
{
  //long Speed_sum;
  speed_clear[1]=(30*speed_clear[0]+10*speed_clear[1])/40;
  speed_clear[0]=speed_clear[1];
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