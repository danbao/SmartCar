/* оƬ��ʼ����
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
static void PWMInit (void);  //PWM���
static void PITInit (void);  //��ʱ��
static void PLLInit (void);  //ʱ��Ƶ��
static void GIOInit (void);  //��ͨIO��
static void SCIInit (void);  //SCI����
static void PACNTInit(void); //����ģ��
extern void MCUInit (void);  //оƬ�ܳ�ʼ��

