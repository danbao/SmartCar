/* ���Ը�������
*�� �� ��: 5th Smartcar v3.1_15Laser.mcp                                                                                         
*˵    ��:   

	  Written by: swe07024 ����ٻ           
    Date:       2010.7.19
    Update:     2010.7.19
*/

//��header file��
#include "testingAuxiliary.h"
#include "dealInfo.h"


//��function definitions��
/* ================= SCISend ====================
      desc: SCI���ڷ���һ���ַ�
      pre:  Ҫ���͵��ַ�
      Post: ��
       
*/ 
void SCISend(unsigned char o)
{
    while (!(SCI0SR1&0x80));
    SCI0DRH=0;
    SCI0DRL=o;
}  //SCISend


/* ================= SendOneData ====================
      desc: SCI���ڷ���һ������
      pre:  Ҫ���͵�����
      Post: ��
       
*/ 
void SendOneData(byte data)  {
    if(data == 0)
        SCISend('0');
    else if(data == 1)
        SCISend('1');
} //SendOneData


/* ================= SendSeparator ====================
      desc: SCI���ڷ��ͷָ��źš�====������ǰ�󼤹��״̬��һ��ʱ�Ŵ�ӡ
      pre:  ��
      Post: ��
       
*/ 
void SendSeparator(void)  {
   int i;
   for(i=0;i<4;i++)
      SCISend('=');  
} //SendSeparator

 
/* ================= SendSteerInfo ====================
      desc: SCI���ڷ��͵�ǰ���ת����Ϣ
      pre:  ��
      Post: ��
       
*/ 
void SendSteerInfo (void) {
    int i,length;
    char str[6] = "";
    int data = PWMDTY01;
    length = SeparateInt(data,str);
	  for(i=0;i<5;i++)
	      SCISend(' ');
	  for(i=length-1; i>=0; i--)
		    SCISend(str[i]);
} //SendSteerInfo


/* ================= SendSpeed ====================
      desc: SCI���ڷ��͵�ǰ�ٶ�
      pre:  ��
      Post: ��
       
*/ 
void SendSpeed (void) {
    int i,length;
    char str[6] = "";
    int data = PWMDTY23;
    length = SeparateInt(data,str);
	  for(i=0;i<5;i++)
	      SCISend(' ');
	  for(i=length-1; i>=0; i--)
		    SCISend(str[i]);
} //SendSpeed


/* ================= SendLaserStatus ====================
      desc: SCI���ڷ��͵�ǰ�����״̬ö������
      pre:  ��
      Post: ��
       
*/ 
void SendLaserStatus(byte laser_status) {
   int i;
   for(i=0;i<4;i++)
      SCISend(' '); 
    
   switch( laser_status ) {
      case  LEFT_NONE:   {
          SCISend('p');   break;
      }
      case  LEFT0:  {
          SCISend('n');   break;
      }
      case  LEFT01:  {
          SCISend('m'); break;
      }
      case LEFT1 : {
          SCISend('l'); break;
      }
      case LEFT12:   {
          SCISend('k'); break;
      }
      case  LEFT2:  {
          SCISend('j'); break;
      }
      case  LEFT23:  {
          SCISend('i'); break;
      }
      case  LEFT3: {
          SCISend('h'); break;
      }
      case  LEFT34:   {
          SCISend('g'); break;
      }
      case  LEFT4:  {
          SCISend('f'); break;
      }
      case  LEFT45:  {
          SCISend('e'); break;
      }
      case  LEFT5: {
          SCISend('d'); break;
      }
      case  LEFT56:   {
          SCISend('c'); break;
      }
      case  LEFT6:  {
          SCISend('b'); break;
      }
      case  LEFT67:   {
          SCISend('a'); break;
      }
      case  MID7:  {
          SCISend('X'); break;
      }
      case  RIGHT78:   {
          SCISend('A'); break;
      }
      case  RIGHT8:  {
          SCISend('B'); break;
      }
      case  RIGHT89:   {
          SCISend('C'); break;
      }
      case  RIGHT9:  {
          SCISend('D'); break;
      }
      case  RIGHT910:   {
          SCISend('E'); break;
      }
      case  RIGHT10:  {
          SCISend('F'); break;
      }
      case  RIGHT1011:  {
          SCISend('G'); break;
      }
      case  RIGHT11:  {
          SCISend('H');break;
      }
      case  RIGHT1112:   {
          SCISend('I'); break;
      } 
      case  RIGHT12:  {
          SCISend('J'); break;
      }
      case  RIGHT1213:   {
          SCISend('K'); break;
      } 
      case  RIGHT13:  {
          SCISend('L'); break;
      }
      case  RIGHT1314: {
          SCISend('M'); break;
      }
      case  RIGHT14:{
          SCISend('N'); break;
      }
      case  RIGHT_NONE:{
          SCISend('P'); break;
      }
      default: break;
  }  
} //SendLaserStatus
 

/* ================= SendTempPulse ====================
      desc: SCI���ڷ������ڲ��ٵ�������
      pre:  ���ڲ��ٵ�������
      Post: ��
       
*/ 
void SendTempPulse(unsigned int temp_pulse) {
    int i,length;
    char str[6] = "";
    length = SeparateInt(temp_pulse,str);
	  for(i=0;i<5;i++)
	      SCISend(' ');
	  for(i=length-1; i>=0; i--)
		    SCISend(str[i]);
} //SendTempPulse(



/* ================= SendSmartcarInfo ====================
      desc: SCI���ڷ��͵�ǰ����ܲɼ���Ϣ
      pre:  1��ǰ����ܲɼ����飬2��ǰ�����״̬
      Post: ��
       
*/ 
void SendSmartcarInfo(byte temp_laser_array[],byte temp_laserStatus,byte last_laserStatus,unsigned int temp_pulse) {
    int i; 
    for(i=LASER_MAX-1;i>=0;i--)             //���ͼ������Ϣ����
        SendOneData(temp_laser_array[i]);
 
    SendLaserStatus(temp_laserStatus);//���ͼ����״̬
    SendSteerInfo ();  //���Ͷ��ת��
    SendSpeed();       //�����ٶ�
    SendTempPulse(temp_pulse);   //�������ڲ��ٵ�������
   
    if(temp_laserStatus != last_laserStatus)      //��״̬�����ı䣬���ͷָ���
        SendSeparator();
    SCISend(13); 
    SCISend(10);    
} //SendSmartcarInfo
 