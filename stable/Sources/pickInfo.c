/* ��Ϣ�ɼ�����
*�� �� ��: 5th Smartcar v3.1_15Laser.mcp                                                                                        
*˵    ��:   

	  Written by: swe07024 ����ٻ           
    Date:       2010.7.19
    Update:     2010.7.19
*/

//��header file��
#include "pickInfo.h"



//��function definitions��
/* ================= SaveLaser ====================
      desc: ���漤��ͷ�ɼ�·��
      pre:  1.�������Ϣ�������� 2.�������Ϣ��������
      Post: ��
       
*/ 
void SaveLaser (byte last_laser_array[], byte temp_laser_array[]) {
  // Local Declarations
  int i = 0;
  // Statements
  for(i=0;i<LASER_MAX;i++) {
      last_laser_array[i] = temp_laser_array[i];  
  }
} //SaveLaser


