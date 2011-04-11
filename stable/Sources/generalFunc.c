/* ͨ�ú���
*�� �� ��: 5th Smartcar v3.1_15Laser.mcp                                                                                           
*˵    ��:   

	  Written by: swe07024 ����ٻ           
    Date:       2010.7.19
*/

//��header file��
#include "generalFunc.h"


//��function definitions��
/* ================= GetDist ====================
      desc: BMģʽ��ƥ���м�ֵ
      pre:  δ֪
      Post: δ֪
       
*/          
int GetDist( char c, char sp[])
{
	  // Local Declarations
	  int i;
	  
	  // Statements
  	for(i=sp[0]-1; i>0; i--)
  	{
  		if(c == sp[i])
  		{
  			if(i == sp[0])
  				return sp[0];
  			else
  				return (sp[0]-i);
  		}
	}
	return sp[0];
} //GetDist


/* ================= BM ====================
      desc: BMģʽ��ƥ��
      pre:  1.���� 2.ģʽ�� 3.�������� 4.ģʽ������
      Post: ����ƥ���λ�ã�����-1��ʾ��ƥ��
       
*/    
int BM( char sm[], char sp[], int sm_len, int sp_len )
{
    // Local Declarations
    int sm_ptr,sp_ptr,temp;
    
    // Statements
	  sm_ptr = sp_len;
    while(sm_ptr <= sm_len)
    {
         sp_ptr = sp_len;
         temp = sm_ptr;  
         while(sp_ptr > 0  &&  sm[sm_ptr] == sp[sp_ptr]) 
         {    
             sp_ptr --;
             sm_ptr --;  
         }
 
         if (0 == sp_ptr)    
			 return(sm_ptr+1);
		 else
		 {
			 sm_ptr = sm_ptr + GetDist(sm[sm_ptr],sp);
			 if (temp > sm_ptr)  //������ѭ���ý��
				 return -1;
		 }
    }
    return -1;
} //BM


/* ================= SeparateInt ====================
      desc: ���͸�λ������
      pre:  Ҫ��ֵ�����
      Post: �������͵�λ��+1
       
*/   
int SeparateInt(int n,char str[])
{
	int i=0;
	while(n)
	{
		str[i]=n%10+'0';
		n/=10;
		i++;
	}
	str[i]='\0';
	return i;
} //SeparateInt



