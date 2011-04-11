/* ���Ը�����
*�� �� ��: 5th Smartcar v3.1_15Laser.mcp                                                                                        
*˵    ��:    

	Written by: swe07024 ����ٻ           
  Date:       2010.7.19
*/

//��header file��
#include <hidef.h>          /* common defines and macros */
#include "derivative.h"     /* derivative-specific definitions */

//��constant definition��

//��function declaration��
static void SCISend(unsigned char); //SCI���ڷ���һ���ַ�
static void SendOneData(byte);      //SCI���ڷ���һ������
static void SendSeparator(void);    //SCI���ڷ��ͷָ��źš�====������ǰ�󼤹��״̬��һ��ʱ�Ŵ�ӡ
static void SendLaserStatus(byte);  //SCI���ڷ��ͼ����״̬ö������
static void SendSteerInfo (void);   //SCI���ڷ��͵�ǰ���ת����Ϣ
static void SendTempPulse(unsigned int); //SCI���ڷ������ڲ��ٵ�������
extern void SendSmartcarInfo(byte[],byte,byte,unsigned int); //SCI���ڷ��͵�ǰ����ܲɼ���Ϣ(�����������顢״̬)