/* 通用函数
*工 程 名: 5th Smartcar v3.1_15Laser.mcp                                                                                           
*说    明:   

	  Written by: swe07024 张苷倩           
    Date:       2010.7.19
*/

//【header file】
#include "generalFunc.h"


//【function definitions】
/* ================= GetDist ====================
      desc: BM模式串匹配中间值
      pre:  未知
      Post: 未知
       
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
      desc: BM模式串匹配
      pre:  1.主串 2.模式串 3.主串长度 4.模式串长度
      Post: 返回匹配的位置，返回-1表示不匹配
       
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
			 if (temp > sm_ptr)  //进入死循环得解决
				 return -1;
		 }
    }
    return -1;
} //BM


/* ================= SeparateInt ====================
      desc: 整型各位数分离
      pre:  要拆分的整数
      Post: 返回整型的位数+1
       
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



