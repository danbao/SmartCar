/*=====================�����ͷ�˲�======================*/
void Clear_baitou(void){
int clear_position;
clear_position=position*100;
JG_clear_position=(JG_clear_position*40+clear_position*100) /140 ;  
}
  
/*=====================�����ͷ======================*/
//ת������1482 1772 1204   ��ͷ�����224+-90
//0.10712*x^2 + 4.5791*10^(-17)*x + 6.7084
//Diff_Position������pd�� �ӵ�pwm�ϵ�����
void  baitou (void) {
   
 
    His_Position[1]=JG_clear_position;
    His_Position[2]=position;
    His_Position[2]=aabs(His_Position[2]); 
    
    
    if(His_Position[2]<=1)
    Diff_Position=0;
    else if(His_Position[2]>1&&His_Position[2]<=3)
    Diff_Position=His_Position[1]/50;//+4.3*(His_Position[1]-His_Position[0]);
    else if(His_Position[2]>3&&His_Position[2]<=7)
    Diff_Position=His_Position[1]/50;//+4.3*(His_Position[1]-His_Position[0]);
    else if(His_Position[2]>7&&His_Position[2]<=10)
    Diff_Position=His_Position[1]/50;//+4.3*(His_Position[1]-His_Position[0]);
    else if(His_Position[2]>10&&His_Position[2]<=12)
    Diff_Position=His_Position[1]/50;//+4.3*(His_Position[1]-His_Position[0]);
    else if(His_Position[2]>12&&His_Position[2]<=14)
    Diff_Position=His_Position[1]/50;//+4.3*(His_Position[1]-His_Position[0]);
    
  /*  else if(His_Position[3]>4&&His_Position[3]<=6)
    Diff_Position=(1+2)*His_Position[2]-(2+2*2)*His_Position[1]+2*His_Position[0];
    else if(His_Position[3]>6&&His_Position[3]<=8)
    Diff_Position=(1+2)*His_Position[2]-(2+2*2)*His_Position[1]+2*His_Position[0];
    else if(His_Position[3]>8&&His_Position[3]<=10)
    Diff_Position=(1+2)*His_Position[2]-(2+2*2)*His_Position[1]+2*His_Position[0];
    else if(His_Position[3]>10&&His_Position[3]<=12)
    Diff_Position=(1+2)*His_Position[2]-(2+2*2)*His_Position[1]+2*His_Position[0];
    else if(His_Position[3]>12&&His_Position[3]<=14)
    Diff_Position=(1+2)*His_Position[2]-(2+2*2)*His_Position[1]+2*His_Position[0];  */
    
     
     His_Position[0]=His_Position[1];
     PWMDTY67=PWMDTY67+Diff_Position;
    
}



/*================���ݱ�׼��position�γ�Ԥ�е�����==========================

��ʱ�Ѿ���position��ֵ��ΪԤ�е�ֵ�洢��temp_position_array[i]
��Ϊһ��Ԥ�еı�׼����ȻҲ������׼ȷ�ģ�ÿ�ξ�ֻ�����������ҳ�һ����
���������Ƕ����Ϊ��ǵĲ�����

BUG��
�ȽϺ���PWMDTY67�����û�취�ã���ʱ����Ҫ����͵ĺ���������һ�²����� ���в�������

=========================================================================*/
void Form_tendency(void)
{
  int i,j;
  for(j=0;j<10;j++) //����temp_position_arrayԪ��Ϊ10��
  {
    for(i=0;i<22;i++) 
    {
    //�����ѭ�����棬����standard_position_array��һ����׼����
    //���ݸ�����PWMDTY67�Ĳ�ֵ�Ƚϣ��ѽ�Ϊ�����İڽǶ��ֵ��������temp_position_array
      if(PWMDTY67 == standard_position_array[i]) 
      {
        temp_position_array[j]=PWMDTY67;
      } 
      else if((PWMDTY67-standard_position_array[i])>0) 
      {
        if((PWMDTY67-standard_position_array[i])>(standard_position_array[i+1]-PWMDTY67))
          temp_position_array[j]=standard_position_array[i+1];
      } 
      else if((PWMDTY67-standard_position_array[i])<0)
      {
        if((standard_position_array[i]-PWMDTY67)>(PWMDTY67-standard_position_array[i-1]))
          temp_position_array[j]=standard_position_array[i-1];
      }
    }
  }
}

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





/*=======================��Ƕ��===========================*/
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







//=====================����ٶȵ���======================//


void SpeedCtrl (void) {
int subspeed;
subspeed=g_temp_pulse-100;
PORTB_PB7=1;
PWMDTY01 = 25;      //ռ�ձ�10%
PWMDTY23 = 80;      //ռ�ձ�50%
 
/* if ((subspeed<=10)&&(subspeed>=-10));
else if((subspeed>10)&&(subspeed<=35)) 
PORTB_PB7=0;
else if(subspeed>35) 
    {  
PORTB_PB7=1;
PWMDTY01= 80;
    }
else if((subspeed<-10)&&(subspeed>=-35)) 
   {
PORTB_PB7=1;
PWMDTY23=PWMDTY23-2*subspeed;
PWMDTY01= 0; 
   }
else if(subspeed<-35)
   {
  
PORTB_PB7=1;
PWMDTY23=80;
PWMDTY01= 0;
   }         */
}          



















/*=====================�����ͷ����ı亯��======================
void Light_SetDriver(int value){
  PWMDTY67 = value; 
}
void SCI_SetDriver(int value){
  PWMDTY45 = value; 
}

*/


