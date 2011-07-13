/*--------------------------------------------
	Written by:	����
	Modify by: 	����
    Date:       2011.04.09
    Update:     2011.07.07             
	˵����LCD��ʾ��ʼ������غ�������
----------------------------------------------*/        
uint LCD_flag=0,LCD_temp=0,LCD_para_num=0,LCD_float_flag=0;
byte LCD_plan_xudas,LCD_plan_xuxiaos,LCD_plan_das,LCD_plan_xiaos,LCD_plan_podao,LCD_plan_qipao;
float float_num;

//float Kp,Ki,Kd;

#define RST PTM_PTM0     		//��λ��M7��   
#define SCE PTM_PTM1          //Ƭѡ��M6��
#define DC PTM_PTM2           //DC��M5��
#define SDIN PTM_PTM3         //������M4��
#define SCLK PTM_PTM4       	//ʱ����M3��
unsigned char lcdx=0,lcdy=0;
/*
sbit    \SCE = SCE;  //Ƭѡ		
sbit    \RST = RST;  //��λ,0��λ
sbit    D/C  = DC;  //1д���ݣ�0дָ��
sbit    SDIN = SDIN;  //����
sbit    SCLK = SCLK;  //ʱ��
*/

/*--------------------------------------------
data: 5*8�ַ�
˵��������ASCII�����У���ģ�������ɿո�(sp)��ʼ,�ո��ַ���ASCII��ֵ����32  
��д���ڣ�20110409 
----------------------------------------------*/
unsigned char data[]={
0x00, 0x00, 0x00, 0x00, 0x00,   // sp     
0x00, 0x00, 0x2f, 0x00, 0x00,   // !     
0x00, 0x07, 0x00, 0x07, 0x00,   // "     
0x14, 0x7f, 0x14, 0x7f, 0x14,   // #     
0x24, 0x2a, 0x7f, 0x2a, 0x12,   // $     
0x62, 0x64, 0x08, 0x13, 0x23,   // %     
0x36, 0x49, 0x55, 0x22, 0x50,   // &     
0x00, 0x05, 0x03, 0x00, 0x00,   // ��     
0x00, 0x1c, 0x22, 0x41, 0x00,   // (     
0x00, 0x41, 0x22, 0x1c, 0x00,   // )     
0x14, 0x08, 0x3E, 0x08, 0x14,   // *     
0x08, 0x08, 0x3E, 0x08, 0x08,   // +     
0x00, 0x00, 0xA0, 0x60, 0x00,   // ,     
0x08, 0x08, 0x08, 0x08, 0x08,   // -     
0x00, 0x60, 0x60, 0x00, 0x00,   // .     
0x20, 0x10, 0x08, 0x04, 0x02,   // /     
0x3E, 0x51, 0x49, 0x45, 0x3E,   // 0     
0x00, 0x42, 0x7F, 0x40, 0x00,   // 1     
0x42, 0x61, 0x51, 0x49, 0x46,   // 2     
0x21, 0x41, 0x45, 0x4B, 0x31,   // 3     
0x18, 0x14, 0x12, 0x7F, 0x10,   // 4     
0x27, 0x45, 0x45, 0x45, 0x39,   // 5     
0x3C, 0x4A, 0x49, 0x49, 0x30,   // 6     
0x01, 0x71, 0x09, 0x05, 0x03,   // 7     
0x36, 0x49, 0x49, 0x49, 0x36,   // 8     
0x06, 0x49, 0x49, 0x29, 0x1E,   // 9     
0x00, 0x36, 0x36, 0x00, 0x00,   // :     
0x00, 0x56, 0x36, 0x00, 0x00,   // ;     
0x08, 0x14, 0x22, 0x41, 0x00,   // <     
0x14, 0x14, 0x14, 0x14, 0x14,   // =     
0x00, 0x41, 0x22, 0x14, 0x08,   // >     
0x02, 0x01, 0x51, 0x09, 0x06,   // ?     
0x32, 0x49, 0x59, 0x51, 0x3E,   // @     
0x7C, 0x12, 0x11, 0x12, 0x7C,   // A     
0x7F, 0x49, 0x49, 0x49, 0x36,   // B     
0x3E, 0x41, 0x41, 0x41, 0x22,   // C     
0x7F, 0x41, 0x41, 0x22, 0x1C,   // D     
0x7F, 0x49, 0x49, 0x49, 0x41,   // E     
0x7F, 0x09, 0x09, 0x09, 0x01,   // F     
0x3E, 0x41, 0x49, 0x49, 0x7A,   // G     
0x7F, 0x08, 0x08, 0x08, 0x7F,   // H     
0x00, 0x41, 0x7F, 0x41, 0x00,   // I     
0x20, 0x40, 0x41, 0x3F, 0x01,   // J     
0x7F, 0x08, 0x14, 0x22, 0x41,   // K     
0x7F, 0x40, 0x40, 0x40, 0x40,   // L     
0x7F, 0x02, 0x0C, 0x02, 0x7F,   // M     
0x7F, 0x04, 0x08, 0x10, 0x7F,   // N     
0x3E, 0x41, 0x41, 0x41, 0x3E,   // O     
0x7F, 0x09, 0x09, 0x09, 0x06,   // P     
0x3E, 0x41, 0x51, 0x21, 0x5E,   // Q     
0x7F, 0x09, 0x19, 0x29, 0x46,   // R     
0x46, 0x49, 0x49, 0x49, 0x31,   // S     
0x01, 0x01, 0x7F, 0x01, 0x01,   // T     
0x3F, 0x40, 0x40, 0x40, 0x3F,   // U     
0x1F, 0x20, 0x40, 0x20, 0x1F,   // V     
0x3F, 0x40, 0x38, 0x40, 0x3F,   // W     
0x63, 0x14, 0x08, 0x14, 0x63,   // X     
0x07, 0x08, 0x70, 0x08, 0x07,   // Y     
0x61, 0x51, 0x49, 0x45, 0x43,   // Z     
0x00, 0x7F, 0x41, 0x41, 0x00,   // [     
0x55, 0x2A, 0x55, 0x2A, 0x55,   // 55     
0x00, 0x41, 0x41, 0x7F, 0x00,   // ]     
0x04, 0x02, 0x01, 0x02, 0x04,   // ^     
0x40, 0x40, 0x40, 0x40, 0x40,   // _     
0x00, 0x01, 0x02, 0x04, 0x00,   // ��     
0x20, 0x54, 0x54, 0x54, 0x78,   // a     
0x7F, 0x48, 0x44, 0x44, 0x38,   // b     
0x38, 0x44, 0x44, 0x44, 0x20,   // c     
0x38, 0x44, 0x44, 0x48, 0x7F,   // d     
0x38, 0x54, 0x54, 0x54, 0x18,   // e     
0x08, 0x7E, 0x09, 0x01, 0x02,   // f     
0x18, 0xA4, 0xA4, 0xA4, 0x7C,   // g     
0x7F, 0x08, 0x04, 0x04, 0x78,   // h     
0x00, 0x44, 0x7D, 0x40, 0x00,   // i     
0x40, 0x80, 0x84, 0x7D, 0x00,   // j     
0x7F, 0x10, 0x28, 0x44, 0x00,   // k     
0x00, 0x41, 0x7F, 0x40, 0x00,   // l     
0x7C, 0x04, 0x18, 0x04, 0x78,   // m     
0x7C, 0x08, 0x04, 0x04, 0x78,   // n     
0x38, 0x44, 0x44, 0x44, 0x38,   // o     
0xFC, 0x24, 0x24, 0x24, 0x18,   // p     
0x18, 0x24, 0x24, 0x18, 0xFC,   // q     
0x7C, 0x08, 0x04, 0x04, 0x08,   // r     
0x48, 0x54, 0x54, 0x54, 0x20,   // s     
0x04, 0x3F, 0x44, 0x40, 0x20,   // t     
0x3C, 0x40, 0x40, 0x20, 0x7C,   // u     
0x1C, 0x20, 0x40, 0x20, 0x1C,   // v     
0x3C, 0x40, 0x30, 0x40, 0x3C,   // w     
0x44, 0x28, 0x10, 0x28, 0x44,   // x     
0x1C, 0xA0, 0xA0, 0xA0, 0x7C,   // y     
0x44, 0x64, 0x54, 0x4C, 0x44,   // z     
0x00, 0x08, 0x36, 0x41, 0x00,   // {     
0x00, 0x00, 0x7F, 0x00, 0x00,   // |     
0x00, 0x41, 0x36, 0x08, 0x00,   // }     
0x08, 0x10, 0x08, 0x04, 0x08   // ~    
};

/*--------------------------------------------
hanzi_16: �Զ��庺��16*16�ֿ�
˵����������Ӻ��֣�������水˳����ӣ������м����
��д���ڣ�20110707 
----------------------------------------------*/
unsigned char hanzi_16[]=
{
/*--  ����:  ��  --*/
/*--  ����12;  �������¶�Ӧ�ĵ���Ϊ����x��=16x16   --*/
0x00,0x00,0xFF,0x05,0x05,0xF5,0x55,0x5D,0x55,0x55,0x55,0x55,0xF5,0x05,0x01,0x00,
0x40,0x30,0x0F,0x80,0xA0,0x97,0xBD,0x55,0x55,0x55,0x55,0x55,0xB7,0x80,0x80,0x00,

/*--  ����:  ��  --*/
/*--  ����12;  �������¶�Ӧ�ĵ���Ϊ����x��=16x16   --*/
0x00,0xF8,0x01,0x06,0x00,0x00,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0xFE,0x00,0x00,
0x00,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x40,0x80,0x7F,0x00,0x00,

/*--  ����:  ��  --*/
/*--  ����12;  �������¶�Ӧ�ĵ���Ϊ����x��=16x16   --*/
0x20,0x20,0x20,0x20,0x20,0x20,0x20,0xFF,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x00,
0x80,0x80,0x40,0x20,0x10,0x0C,0x03,0x00,0x03,0x0C,0x10,0x20,0x40,0x80,0x80,0x00,

/*--  ����:  ѧ  --*/
/*--  ����12;  �������¶�Ӧ�ĵ���Ϊ����x��=16x16   --*/
0x40,0x30,0x11,0x96,0x90,0x90,0x91,0x96,0x90,0x90,0x98,0x14,0x13,0x50,0x30,0x00,
0x04,0x04,0x04,0x04,0x04,0x44,0x84,0x7E,0x06,0x05,0x04,0x04,0x04,0x04,0x04,0x00,

/*--  ����:  ��  --*/
/*--  ����12;  �������¶�Ӧ�ĵ���Ϊ����x��=16x16   --*/
0x02,0x02,0x0A,0xEA,0xAA,0xAA,0xAA,0xAF,0xAA,0xAA,0xAA,0xEA,0x0A,0x02,0x02,0x00,
0x82,0x4A,0x2A,0x1E,0x0B,0x4A,0x8A,0x7A,0x02,0xFA,0x4B,0x4A,0x4A,0xFA,0x02,0x00,

/*--  ����:  �� --*/
/*--  ����12;  �������¶�Ӧ�ĵ���Ϊ����x��=16x16   --*/
0x00,0x00,0xFC,0x04,0x24,0x24,0x24,0x25,0xF6,0x24,0x24,0x24,0xE4,0x04,0x04,0x00,
0x40,0x30,0x8F,0x81,0x49,0x49,0x29,0x19,0x0F,0x19,0x29,0x49,0x4F,0x81,0x81,0x00,

/*--  ����:  ѧ  --*/
/*--  ����12;  �������¶�Ӧ�ĵ���Ϊ����x��=16x16   --*/
0x40,0x30,0x10,0x12,0x5C,0x54,0x50,0x51,0x5E,0xD4,0x50,0x18,0x57,0x32,0x10,0x00,
0x00,0x02,0x02,0x02,0x02,0x02,0x42,0x82,0x7F,0x02,0x02,0x02,0x02,0x02,0x02,0x00,

/*--  ����:  Ժ  --*/
/*--  ����12;  �������¶�Ӧ�ĵ���Ϊ����x��=16x16   --*/
0xFE,0x02,0x32,0x4A,0x86,0x0C,0x24,0x24,0x25,0x26,0x24,0x24,0x24,0x0C,0x04,0x00,
0xFF,0x00,0x02,0x04,0x83,0x41,0x31,0x0F,0x01,0x01,0x7F,0x81,0x81,0x81,0xF1,0x00,

/*--  ����:  ��  --*/
/*--  ����12;  �������¶�Ӧ�ĵ���Ϊ����x��=16x16   --*/
0x40,0x40,0x42,0x44,0x58,0xC0,0x40,0x7F,0x40,0xC0,0x50,0x48,0x46,0x40,0x40,0x00,
0x80,0x80,0x40,0x20,0x18,0x07,0x00,0x00,0x00,0x3F,0x40,0x40,0x40,0x40,0x78,0x00,

/*--  ����:  ��  --*/
/*--  ����12;  �������¶�Ӧ�ĵ���Ϊ����x��=16x16   --*/
0x00,0x00,0xF8,0x88,0x88,0x88,0x88,0xFF,0x88,0x88,0x88,0x88,0xF8,0x00,0x00,0x00,
0x00,0x00,0x1F,0x08,0x08,0x08,0x08,0x7F,0x88,0x88,0x88,0x88,0x9F,0x80,0xF0,0x00,

/*--  ����:  ��  --*/
/*--  ����12;  �������¶�Ӧ�ĵ���Ϊ����x��=16x16   --*/
0x00,0x10,0x88,0x84,0x43,0x20,0x10,0x0C,0x10,0x20,0x41,0x82,0x84,0x08,0x00,0x00,
0x01,0x01,0x00,0xFE,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0xFE,0x00,0x01,0x01,0x00,

/*--  ����:  ��  --*/
/*--  ����12;  �������¶�Ӧ�ĵ���Ϊ����x��=16x16   --*/
0x00,0x00,0xFE,0x02,0x12,0x22,0xC2,0x02,0xC2,0x32,0x02,0xFE,0x00,0x00,0x00,0x00,
0x80,0x60,0x1F,0x00,0x20,0x10,0x0C,0x03,0x0C,0x30,0x00,0x0F,0x30,0x40,0xF8,0x00,

};

/*--------------------------------------------
hanzi_12: �Զ��庺��12*12�ֿ�
˵����������Ӻ��֣�������水˳����ӣ������м����
��д���ڣ�20110707 
----------------------------------------------*/
	unsigned char hanzi_12[]=
{
//��
	0x10,0x11,0xF2,0x40,0x44,0xFF,0x44,0x44,0xFF,0x44,0x40,0x00,0x08,0x04,0x03,0x04,0x0A,0x09,0x08,0x08,0x0B,0x08,0x08,0x00,
//��
	0x00,0x00,0x01,0x81,0x72,0x0C,0x70,0x80,0x00,0x00,0x00,0x00,0x08,0x04,0x02,0x01,0x00,0x00,0x00,0x01,0x02,0x04,0x08,0x00,
//��
	0x26,0xAA,0xEA,0xBE,0xAA,0xAB,0xAA,0xBE,0xEA,0xAA,0x26,0x00,0x01,0x00,0x0B,0x08,0x04,0x03,0x04,0x04,0x0B,0x00,0x01,0x00,
//��
	0x10,0x11,0xF2,0x00,0xFA,0xAB,0xAE,0xAA,0xAA,0xAB,0xFA,0x00,0x08,0x04,0x03,0x04,0x0B,0x0A,0x0A,0x0A,0x0A,0x0A,0x0B,0x00,
//��
	0x22,0x44,0xFE,0x02,0xFA,0x02,0xFE,0x00,0xFC,0x00,0xFF,0x00,0x04,0x02,0x09,0x04,0x03,0x04,0x09,0x00,0x01,0x08,0x0F,0x00,
//��
	0x11,0xF2,0x00,0x00,0x24,0xE4,0x24,0x04,0xFF,0x04,0x05,0x00,0x00,0x0F,0x04,0x00,0x04,0x07,0x02,0x00,0x03,0x04,0x0E,0x00,
//��
	0x11,0xF2,0x00,0x00,0xFF,0x21,0xA9,0xBD,0xA9,0x21,0xFF,0x00,0x00,0x07,0x02,0x08,0x07,0x00,0x03,0x02,0x0B,0x08,0x0F,0x00,
//��
	0x24,0x24,0x24,0x2F,0xE4,0x24,0x24,0x2F,0x24,0xE4,0x04,0x00,0x00,0x00,0x00,0x00,0x0F,0x00,0x00,0x00,0x02,0x03,0x00,0x00,
//��
	0x90,0x54,0xB6,0x95,0x5C,0x54,0x34,0x94,0x36,0x54,0x90,0x00,0x00,0x0A,0x0A,0x0A,0x0A,0x09,0x05,0x04,0x04,0x02,0x00,0x00,
//��
	0x48,0x2A,0x98,0x7F,0x28,0x4A,0x10,0xEF,0x08,0xF8,0x08,0x00,0x09,0x0B,0x05,0x05,0x0B,0x00,0x08,0x05,0x02,0x05,0x08,0x00,
//��
	0x22,0x44,0x80,0xBE,0xEB,0xBE,0x10,0xEC,0x0B,0xF8,0x08,0x00,0x04,0x02,0x08,0x07,0x0A,0x0E,0x08,0x04,0x03,0x04,0x08,0x00,
//��
	0x20,0x22,0x24,0xE8,0x20,0x3F,0x20,0xE8,0x24,0x22,0x20,0x00,0x08,0x04,0x02,0x01,0x00,0x00,0x00,0x07,0x08,0x08,0x0E,0x00,
//��
	0x98,0xD4,0xB3,0x88,0x00,0x02,0x02,0xFE,0x02,0x02,0x00,0x00,0x04,0x04,0x02,0x02,0x08,0x08,0x08,0x0F,0x08,0x08,0x08,0x00,
//��
	0x40,0x30,0x4F,0x88,0x78,0x00,0x00,0xFF,0x10,0x20,0xC0,0x00,0x08,0x04,0x02,0x01,0x00,0x00,0x00,0x0F,0x00,0x00,0x00,0x00,
//��
	0x80,0x92,0x94,0xFF,0x94,0x92,0x80,0xFC,0x00,0x00,0xFF,0x00,0x00,0x08,0x06,0x01,0x00,0x00,0x00,0x01,0x08,0x08,0x0F,0x00,
//��
	0xFC,0x92,0x54,0xFF,0x54,0x92,0x00,0xFE,0x12,0xF2,0x11,0x00,0x07,0x04,0x04,0x07,0x04,0x04,0x08,0x07,0x00,0x0F,0x00,0x00,
//��
	0x08,0x08,0xFF,0x08,0xFC,0x24,0xE4,0x3F,0x24,0xE4,0x0C,0x00,0x02,0x02,0x01,0x09,0x07,0x08,0x05,0x02,0x05,0x08,0x08,0x00,
//��
	0x20,0xA4,0x24,0xFF,0x24,0x00,0xF2,0x12,0x12,0x1E,0x80,0x00,0x08,0x07,0x04,0x0F,0x09,0x08,0x09,0x0A,0x0A,0x0A,0x0B,0x00,
//��
	0x9E,0x12,0xF2,0x9E,0x08,0xF4,0x97,0x94,0xF4,0x04,0xFC,0x00,0x0F,0x08,0x07,0x04,0x00,0x07,0x08,0x08,0x08,0x09,0x0D,0x00,
//��
	0x11,0xF2,0x00,0x7A,0x4A,0xCA,0xFF,0xCA,0x4A,0x7A,0x02,0x00,0x08,0x07,0x08,0x0A,0x09,0x08,0x0F,0x08,0x09,0x0A,0x08,0x00,
//��
	0x04,0x04,0x04,0xFC,0x25,0x26,0x24,0x24,0x24,0xE4,0x04,0x00,0x08,0x04,0x03,0x00,0x00,0x00,0x08,0x08,0x08,0x07,0x00,0x00,
//��
	0x46,0x4A,0x4A,0x5A,0x2E,0xAB,0x2A,0x5A,0x4A,0x4A,0x06,0x00,0x09,0x09,0x05,0x03,0x01,0x0F,0x01,0x03,0x05,0x09,0x09,0x00,
//ѡ
	0x10,0x11,0xF2,0x00,0x28,0x26,0xE4,0x3F,0xE4,0x24,0x20,0x00,0x08,0x04,0x03,0x04,0x0A,0x09,0x08,0x08,0x09,0x0A,0x0B,0x00,
//��
	0x88,0x88,0xFF,0x48,0x21,0xA3,0x95,0xE9,0x95,0xA3,0x20,0x00,0x00,0x08,0x0F,0x00,0x02,0x02,0x02,0x0F,0x02,0x02,0x02,0x00,
	};

void delay_1ms(void)                  //1ms��ʱ����
{
	unsigned int i;
	for (i=0;i<600;i++)	  ;
;
}
void delay_nms(unsigned int n)        //N ms��ʱ����
  {
   unsigned int i=0;
   for (i=0;i<n;i++)
   delay_1ms();
  }

/*--------------------------------------------
LCD_write_byte: ʹ��SPI�ӿ�д���ݵ�LCD
���������dt��д������ݣ�
command ��д����/����ѡ��
��д���ڣ�20080918 
----------------------------------------------*/
void LCD_write_byte(unsigned char dt, unsigned char command)
{
	unsigned char i; 
	SCE=0;	
	DC=command;	
	for(i=0;i<8;i++)
	{ 
		if(dt&0x80)
			SDIN=1;
		else
			SDIN=0;
		dt=dt<<1;		
		SCLK=0; 		
		SCLK=1; 
	}	
	DC=1;	
	SCE=1;	
	SDIN=1;
}
/*-------------------------------------------
LCD_set_XY: ����LCD���꺯��
���������X��0��83  Y��0��5
��д���ڣ�20080918 
---------------------------------------------*/
void LCD_set_XY(unsigned char X, unsigned char Y)
{
	LCD_write_byte(0x40 | Y, 0);// column
	LCD_write_byte(0x80 | X, 0);// row
} 

/*------------------------------------------
LCD_clear: LCD��������
��д���ڣ�20080918 
--------------------------------------------*/
void LCD_clear(void)
{
	unsigned char t;
	unsigned char k;
	LCD_set_XY(0,0);
	for(t=0;t<6;t++)
	{ 
		for(k=0;k<84;k++)
		{ 
			LCD_write_byte(0x00,1);
				
		} 
	}
	lcdx=0,lcdy=0;
}

/*---------------------------------------------
LCD_position: ��ʾLCD�ַ���ǰλ��
˵�����жϵ�ǰλ�ò����ص�lcdx��lcdy������ȫ�ֱ�����lcdx���У�lcdy����
��д���ڣ�20110410
-----------------------------------------------*/
void LCD_position(unsigned char row, unsigned char line)
 {

  int i;
  row++;
  i=row;
  if(i%13==0&&i!=0)
 {
  line++;
  row=0; 
 }
 lcdx=line;
 lcdy=row;
}
/*---------------------------------------------
LCD_write_zi: ��ʾ5����*8���ߣ�������������ĸ���ŵȰ����
���������c����ʾ���ַ���
��д���ڣ�20110409 
-----------------------------------------------*/
void LCD_write_zi(unsigned char row, unsigned char line,unsigned char c) //row:�� line:�� dd:�ַ�
{
unsigned char i=0;     
unsigned int No;     
No=c-32;                 //��ģ�������ɿո�ʼ,�ո��ַ���ASCII��ֵ����32  
No*=5;  
	LCD_set_XY(row, line);// �У���
while(i<5)                     //һ���ַ�����ģ��5���ֽ�,����5*8����     
  {     
    LCD_write_byte(data[No],1);       
    i++;     
   No++;
  } 
}
/*---------------------------------------------
LCD_write_cizu: ��ʾ5����*8���ߣ�������������ĸ���ŵȰ�����ַ���
���������c����ʾ���ַ���
��д���ڣ�20110410
-----------------------------------------------*/
 void LCD_write_cizu(unsigned char row, unsigned char line,char a[]) //row:�� line:�� dd:�ַ� 
 {
 int i;
 row=row-6;
 for(i=0;i<strlen(a);i++) {
 if(i%13==0&&i!=0)
 {
  line++;
  row=-6; 
 }
 LCD_write_zi( row+=6,line,a[i]);
 }
 LCD_position(row,line);
 }
 
/*---------------------------------------------
LCD_write_shuzi: ��ʾ5����*8���ߣ�����������
���������a����ʾ������
��д���ڣ�20110410
-----------------------------------------------*/
 void LCD_write_shuzi(unsigned char row, unsigned char line,int a) //row:�� line:�� dd:�ַ� 
 {
 char b[10];
 (void)sprintf(b,"%d",a);
 LCD_write_cizu(row,line,b);
 }
 
/*---------------------------------------------
LCD_write_hanzi: ��ʾ16����*16���ߣ������к��ֵȰ����
���������c����ʾ���ַ���
��д���ڣ�20110707 
-----------------------------------------------*/
void LCD_write_hanzi_16(unsigned char row, unsigned char line,unsigned char c) //row:�� line:�� dd:�ַ�
{
	unsigned char i;  	
	
	LCD_set_XY(row*4, line);// �У��� 
	for(i=0; i<16;i++) 
	{
		LCD_write_byte(hanzi_16[c*32+i],1); 
	}
	
    LCD_set_XY(row*4, line+1);// �У��� 
	for(i=16; i<32;i++) 
	{
		LCD_write_byte(hanzi_16[c*32+i],1);
	}	
}

/*---------------------------------------------
LCD_write_hanzi: ��ʾ16����*16���ߣ������к��ֵȰ����
���������c����ʾ���ַ���
��д���ڣ�20110707 
-----------------------------------------------*/
void LCD_write_hanzi_12(unsigned char row, unsigned char line,unsigned char c) //row:�� line:�� dd:�ַ�
{
	unsigned char i;  	
	
	LCD_set_XY(row*3, line);// �У��� 
	for(i=0; i<12;i++) 
	{
		LCD_write_byte(hanzi_12[c*24+i],1); 
	}
	
    LCD_set_XY(row*3, line+1);// �У��� 
	for(i=12; i<24;i++) 
	{
		LCD_write_byte(hanzi_12[c*24+i],1);
	}	}

/*---------------------------------------
LCD_init: 5110LCD��ʼ��
��д���ڣ�20110707 
-----------------------------------------  */
void LCD_init(void)
{
  DDRM = 0XFF;        //��ʼ��M7~M3��
  DDRH = 0X0F;        //��ʼ��H7~M4�ڣ�����������ʹ��
	RST=0;  	
  delay_1ms();
  RST=1;  
	LCD_write_byte(0x21,0);//��ʼ��Lcd,�����趨ʹ������ָ��
	LCD_write_byte(0xd0,0);//�趨Һ��ƫ�õ�ѹ
	LCD_write_byte(0x20,0);//ʹ�û���ָ��
	LCD_write_byte(0x0C,0);//�趨��ʾģʽ��������ʾ
	LCD_clear(); //����Ļ
}

/*---------------------------------------
LCD_checkkey: �����û�м�����
��д���ڣ�20110707
-----------------------------------------  */
uchar LCD_checkkey()						//�����û�м�����
{uchar i ;
 uchar j ;
 j=0x1F&PTM;
 PTM=j;
 i=PTH&0xF0;
 if(i==0xF0) return (0);
  else return (0xFF);
  }
  
/*---------------------------------------
LCD_keyscan:����ɨ�����
��д���ڣ�20110707
-----------------------------------------  */  
uchar LCD_keyscan()						//����ɨ�����
{
	uchar scancode;
	uchar codevalue;
	uchar a;
	uchar m=0;
	uchar k;
	uchar i,j;
	if (LCD_checkkey()==0) return (0xFF);
    else 
   {delay_nms(50);
    if (LCD_checkkey()==0) return (0xFF);
	else 
	 {
      scancode=0B11100000;
      a=scancode|PTM;
	    PTM=a;
	    scancode=0B01111111;
	    a=scancode&PTM;
	    PTM=a;        m=0x41;   		//������ɨ���ֵ��MΪ����
 	  for (i=1;i<=3;i++)
	      {
            k=0x10;              
	 	    for (j=0;j<4;j++)			//JΪ����
	 		{
              if ((PTH&k)==0)
			  {
                codevalue = m+j;
			    while (LCD_checkkey()!=0);
			    return (codevalue);
			  }          else  k=k<<1;
	        }
	        m=m+4;                  
	        if(PTM_PTM7==0){PTM_PTM5=1;PTM_PTM6=0;PTM_PTM7=1;} 
	        else if(PTM_PTM6==0){PTM_PTM5=0;PTM_PTM6=1;PTM_PTM7=1;}
	        else if(PTM_PTM5==0){PTM_PTM5=1;PTM_PTM6=1;PTM_PTM7=0;}
	      }
	  }
  }
}

/*---------------------------------------------
LCD_start: ��ʾ������ʱ��ʾ"���Ŵ�ѧ�θ�ѧԺ���һ��"
��д���ڣ�20110409
-----------------------------------------------*/
void LCD_start(void) 
{
	LCD_clear();
	LCD_write_hanzi_16(1,0,0);   //��
	LCD_write_hanzi_16(6,0,1);   //��
	LCD_write_hanzi_16(11,0,2);  //��
	LCD_write_hanzi_16(16,0,3);  //ѧ
	
	LCD_write_hanzi_16(1,2,4);   //��
	LCD_write_hanzi_16(6,2,5);   //��
	LCD_write_hanzi_16(11,2,6);  //ѧ
	LCD_write_hanzi_16(16,2,7);  //Ժ
	
	LCD_write_hanzi_16(1,4,8);   //��
	LCD_write_hanzi_16(6,4,9);   //��
	LCD_write_hanzi_16(11,4,10); //��
	LCD_write_hanzi_16(16,4,11); //��
	}
/*---------------------------------------------
LCD_show: ��ʾ����ʾ������
��д���ڣ�20110707
-----------------------------------------------*/
	void LCD_show(void) {
	LCD_clear();
	LCD_flag=0;
	LCD_write_hanzi_12(2,0,0);  //��
	LCD_write_hanzi_12(6,0,1);  //��
	LCD_write_hanzi_12(10,0,2); //��
	LCD_write_hanzi_12(14,0,3); //��
	LCD_write_hanzi_12(18,0,4); //��
	LCD_write_hanzi_12(22,0,5); //��
	
	LCD_write_hanzi_12(6,2,6);  //��
	LCD_write_hanzi_12(10,2,7); //��
	LCD_write_hanzi_12(14,2,8); //��
	LCD_write_hanzi_12(18,2,9); //��
	
	LCD_write_hanzi_12(6,4,20);  //��
	LCD_write_hanzi_12(10,4,21); //��
	LCD_write_hanzi_12(14,4,22); //ѡ
	LCD_write_hanzi_12(18,4,23); //��
	}
/*---------------------------------------------
LCD_T_JG: ��⼤��
��д���ڣ�20110707
-----------------------------------------------*/	
void LCD_T_JG(byte temp_laser_array[]) {
  uchar i; 
  byte LCD_temp_data;
	LCD_clear();
	LCD_write_hanzi_12(8,0,4);    //��
	LCD_write_hanzi_12(12,0,10);  //��
	LCD_write_hanzi_12(16,0,11);  //��
  for(i=0;i<LASER_MAX;i++)
  {
  LCD_temp_data=temp_laser_array[i];
   if(LCD_temp_data == 0&& i<11)
   { 
   LCD_write_zi(i*7,2,'0');
   }
   else if(LCD_temp_data == 1&& i<11)
   {
      LCD_write_zi(i*7,2,'1');  
   }
   else if(LCD_temp_data == 0&& i>=11)
   { 
   LCD_write_zi((i-11)*7,3,'0');
   }
   else if(LCD_temp_data == 1&& i>=11)
   {
      LCD_write_zi((i-11)*7,3,'1');  
   }
  }
	LCD_write_cizu(0,5,"<-");
	LCD_write_cizu(73,5,"->");  
}
/*---------------------------------------------
LCD_T_IR: ������
��д���ڣ�20110707
-----------------------------------------------*/	
void LCD_T_IR(void) {
  int i=0;
	LCD_clear();
	LCD_write_hanzi_12(8,0,4);    //��
	LCD_write_hanzi_12(12,0,12);  //��
	LCD_write_hanzi_12(16,0,13);  //��
	do{ 
	LCD_write_shuzi(i*8+12,3,IR_temp_laser_array[i]);
    i++;
    }while(i<7);
	LCD_write_cizu(0,5,"<-");
	LCD_write_cizu(73,5,"->"); 
}
/*---------------------------------------------
LCD_T_podao: ����µ�
��д���ڣ�20110707
-----------------------------------------------*/	
void LCD_T_podao(void) {
	LCD_clear();
	LCD_write_hanzi_12(6,0,14);   //��
	LCD_write_hanzi_12(10,0,15);  //��
	LCD_write_hanzi_12(14,0,16);  //��
	LCD_write_hanzi_12(18,0,3);   //��
	if(slope_flag==0){
  LCD_write_cizu(14,3,"Not Podao");}
  else if(slope_flag==1)
  {LCD_write_cizu(10,3,"It's Podao");}
	LCD_write_cizu(0,5,"<-");
	LCD_write_cizu(73,5,"->"); 
}
/*---------------------------------------------
LCD_T_qipao: �������
��д���ڣ�20110707
-----------------------------------------------*/	
void LCD_T_qipao(void) {
	LCD_clear();
	LCD_write_hanzi_12(8,0,4);    //��
	LCD_write_hanzi_12(12,0,17);  //��
	LCD_write_hanzi_12(16,0,18);  //��
	if(start_flag==0){
  LCD_write_cizu(14,3,"Not QiPao");}
  else if(start_flag==1)
  {LCD_write_cizu(10,3,"It's QiPao");}
	LCD_write_cizu(0,5,"<-");
	LCD_write_cizu(73,5,"->");  
}
/*---------------------------------------------
LCD_T_qipao: ������
��д���ڣ�20110707
-----------------------------------------------*/	
void LCD_T_cesu(void) {
	LCD_clear();
	LCD_write_hanzi_12(8,0,4);    //��
	LCD_write_hanzi_12(12,0,4);   //��
	LCD_write_hanzi_12(16,0,19);  //��
  LCD_write_shuzi(35,3,(int)speed_clear[1]);
	LCD_write_cizu(0,5,"<-");
	LCD_write_cizu(73,5,"->"); 
}
	/*---------------------------------------------
LCD_para: �޸Ĳ�������ҳ��
�����a��Ҫ�ĵ�ֵ
��д���ڣ�20110708
-----------------------------------------------*/
  void LCD_para(uint a) {
  	int num;
	LCD_clear();

	switch(a)
    {
    case 20:     //�޸Ĳ�������ҳ��0
 {
  LCD_write_cizu(0,0,"Mod Sped Ctr");
  LCD_write_cizu(0,1,"Kp:");
  LCD_write_shuzi(25,1,(int)Kp);
       if ((int)Kp>9999)  num=5;
  else if ((int)Kp>999)   num=4;
  else if ((int)Kp>99)    num=3;
  else if ((int)Kp>9)     num=2;
  else num=1;  
  LCD_write_zi(25+num*6,1,'.');
  LCD_write_shuzi(31+num*6,1,(int)(Kp*10)%10);
  LCD_write_shuzi(37+num*6,1,(int)(Kp*100)%10);
  LCD_write_shuzi(43+num*6,1,(int)(Kp*1000)%10);
  LCD_write_cizu(0,2,"Ki:");
  LCD_write_shuzi(25,2,(int)Ki);
       if ((int)Ki>9999)  num=5;
  else if ((int)Ki>999)   num=4;
  else if ((int)Ki>99)    num=3;
  else if ((int)Ki>9)     num=2;
  else num=1;
  LCD_write_zi(25+num*6,2,'.');
  LCD_write_shuzi(31+num*6,2,(int)(Ki*10)%10);
  LCD_write_shuzi(37+num*6,2,(int)(Ki*100)%10);
  LCD_write_shuzi(43+num*6,2,(int)(Ki*1000)%10); 
  LCD_write_cizu(0,3,"Kd:");
  LCD_write_shuzi(25,3,(int)Kd);
       if ((int)Kd>9999)  num=5;
  else if ((int)Kd>999)   num=4;
  else if ((int)Kd>99)    num=3;
  else if ((int)Kd>9)     num=2;
  else num=1;
  LCD_write_zi(25+num*6,3,'.');
  LCD_write_shuzi(31+num*6,3,(int)(Kd*10)%10);
  LCD_write_shuzi(37+num*6,3,(int)(Kd*100)%10);
  LCD_write_shuzi(43+num*6,3,(int)(Kd*1000)%10); 
	LCD_write_cizu(0,5,"<-");
	LCD_write_cizu(73,5,"->");
 }
    break;
    case 21:     //�޸Ĳ�������ҳ��1
 {
  LCD_write_cizu(0,0,"Modify Page 2");
	LCD_write_cizu(0,5,"<-");
	LCD_write_cizu(73,5,"->");
 }
    break;
    case 22:     //�޸Ĳ�������ҳ��2
  {
    LCD_write_cizu(0,0,"Modify Page 3");
	LCD_write_cizu(0,5,"<-");
	LCD_write_cizu(73,5,"->"); 
  }
    break;
    } 
	}
/*---------------------------------------------
LCD_para_modify: �޸Ĳ�����ҳ��
�����a��Ҫ�ĵ�ֵ
��д���ڣ�20110708
-----------------------------------------------*/
void LCD_para_modify(uint a) {
LCD_write_cizu(0,0,"Modify");
 switch(a)
 {
    case 11:     //�޸Ĳ���ҳ��11
  LCD_write_cizu(40,0,"Kp");
  LCD_write_cizu(0,5,"YES");
	LCD_write_cizu(73,5,"NO");   
    break;
    case 12:     //�޸Ĳ���ҳ��12
  LCD_write_cizu(40,0,"Ki");
  LCD_write_cizu(0,5,"YES");
	LCD_write_cizu(73,5,"NO"); 
    break;
    case 13:     //�޸Ĳ���ҳ��13
  LCD_write_cizu(40,0,"Kd");
  LCD_write_cizu(0,5,"YES");
	LCD_write_cizu(73,5,"NO"); 
    break;
    } 
	 }
/*---------------------------------------------
LCD_temp_confirm: ȷ�Ϻ��޸�ֵ
��д���ڣ�20110708
-----------------------------------------------*/
void LCD_temp_confirm(uint num,uint zhi) {
 switch(num)
 {
    case 21:     //�޸Ĳ���1
  Kp=(float)zhi;
  LCD_temp=0; 
    break;
    case 22:     //�޸Ĳ���2
  Ki=(float)zhi;
  LCD_temp=0;
    break;
    case 23:     //�޸Ĳ���3
  Kd=(float)zhi;
  LCD_temp=0;
    break;
   } 
	}
/*---------------------------------------------
LCD_temp_float_confirm: ȷ�Ϻ��޸�ֵ
��д���ڣ�20110713
-----------------------------------------------*/
void LCD_temp_float_confirm(uint num,float zhi) {
 switch(num)
 {
    case 11:     //�޸Ĳ���1
  Kp=zhi;
  LCD_temp=0;
  float_num=0;
  LCD_float_flag=0; 
    break;
    case 12:     //�޸Ĳ���2
  Ki=zhi;
  LCD_temp=0;
  float_num=0;
  LCD_float_flag=0;
    break;
    case 13:     //�޸Ĳ���3
  Kd=zhi;
  LCD_temp=0;
  float_num=0;
  LCD_float_flag=0;
    break;
   } 
	}
/*---------------------------------------------
LCD_keytran: ����ת����
��д���ڣ�20110708
-----------------------------------------------*/
 uchar LCD_keytran(uchar a) {
   int temp;
   temp=(int)a-16;
   if(temp==58)return '0';
   else if(temp==59)return 'Y';
   else if(temp==60)return 'N';
   else return (uchar)temp;
	}
/*---------------------------------------------
LCD_temp_zhi: Ҫ�ĵ�ֵ
��д���ڣ�20110708
-----------------------------------------------*/
void LCD_temp_zhi(uchar a) {
   int int_tmp;
   int_tmp=(int)a-48;
   if(int_tmp==10)int_tmp=0;
   LCD_temp=LCD_temp*10+int_tmp;
   LCD_write_shuzi(5,3,LCD_temp); 
	}
/*---------------------------------------------
LCD_tmp_float: Ҫ�ĵ�ֵ(Float��)
��д���ڣ�20110713
-----------------------------------------------*/	
	void LCD_tmp_float(uchar a){
	 int tmp,i;
	 float float_tmp;
	 char b[10];
	 if(a=='Y') 
	 {  
	 (void)sprintf(b,"%.5f",float_num);
    LCD_write_cizu(5,3,b);
    } 
    else{
    	  tmp=(int)a-48;
	 if(tmp==10)tmp=0;
	 
   float_tmp=(float)tmp;  
	 for(i=LCD_float_flag;i>1;i--) float_tmp=float_tmp/10;
	 
	 float_num=float_num+float_tmp;
	 (void)sprintf(b,"%.5f",float_num);
    LCD_write_cizu(5,3,b);
	 }
 }
	/*---------------------------------------------
LCD_plan_choose: ����ѡ��ҳ�� 
��д���ڣ�20110711
-----------------------------------------------*/
void LCD_plan_choose(uint a) {
	switch(a) {
	 case 40:     //����ѡ�����ҳ��0
   { LCD_write_cizu(5,0,"Plan Choose 1");
  	LCD_write_cizu(15,1,"Xu-Da-S");
    if(LCD_plan_xudas==1)LCD_write_zi(5,1,'*');
    else if(LCD_plan_xudas==0)LCD_write_zi(5,1,' ');
  	LCD_write_cizu(15,2,"Xu-Xiao-S");
  	if(LCD_plan_xuxiaos==1)LCD_write_zi(5,2,'*');
    else if(LCD_plan_xuxiaos==0)LCD_write_zi(5,2,' ');
  	LCD_write_cizu(15,3,"Da-S");
  	if(LCD_plan_das==1)LCD_write_zi(5,3,'*');
    else if(LCD_plan_das==0)LCD_write_zi(5,3,' ');
  	LCD_write_cizu(15,4,"Xiao-S");
  	if(LCD_plan_xiaos==1)LCD_write_zi(5,4,'*');
    else if(LCD_plan_xiaos==0)LCD_write_zi(5,4,' ');
	  LCD_write_cizu(0,5,"<-");
	  LCD_write_cizu(73,5,"->"); 
	}
	break;
    case 41:     //����ѡ�����ҳ��1
  {
  LCD_write_cizu(5,0,"Plan Choose 2");
  LCD_write_cizu(15,1,"Podao");
  if(LCD_plan_podao==1)LCD_write_zi(5,1,'*');
  else if(LCD_plan_podao==0)LCD_write_zi(5,1,' ');
  LCD_write_cizu(15,2,"Start Line");
  if(LCD_plan_qipao==1)LCD_write_zi(5,2,'*');
  else if(LCD_plan_qipao==0)LCD_write_zi(5,2,' ');
	LCD_write_cizu(0,5,"<-");
	LCD_write_cizu(73,5,"->");
  }break;
    case 42:     //����ѡ�����ҳ��2
    {
  LCD_write_cizu(5,0,"Plan Choose 3");
	LCD_write_cizu(0,5,"<-");
	LCD_write_cizu(73,5,"->");  
   }break; 
	} 
}
	/*---------------------------------------------
LCD_close_plan:�رշ���ѡ��
��д���ڣ�20110711             
-----------------------------------------------*/
void LCD_close_plan(uint a){
	switch(a) {
  	case 11: {
	  if(LCD_plan_xudas==0)LCD_plan_xudas=1;
	  else if(LCD_plan_xudas==1)LCD_plan_xudas=0; 
	}	break; 
		case 12: {
	  if(LCD_plan_xuxiaos==0)LCD_plan_xuxiaos=1;
	  else if(LCD_plan_xuxiaos==1)LCD_plan_xuxiaos=0; 
	}	break; 
		case 13: {
	  if(LCD_plan_das==0)LCD_plan_das=1;
	  else if(LCD_plan_das==1)LCD_plan_das=0; 
	}	break; 
		case 14: {
	  if(LCD_plan_xiaos==0)LCD_plan_xiaos=1;
	  else if(LCD_plan_xiaos==1)LCD_plan_xiaos=0; 
	}	break; 
		case 21: {
	  if(LCD_plan_podao==0)LCD_plan_podao=1;
	  else if(LCD_plan_podao==1)LCD_plan_podao=0; 
	}	break; 
		case 22: {
	  if(LCD_plan_qipao==0)LCD_plan_qipao=1;
	  else if(LCD_plan_qipao==1)LCD_plan_qipao=0; 
	}	break;   
}  
}
/*---------------------------------------------
LCD_determine: �����жϲ�ִ�ж���
��д���ڣ�20110707
-----------------------------------------------*/	
void LCD_determine(uchar x) {
	uint result;
	
/*��������������*/
if(LCD_flag==0&&x=='1')LCD_flag=10;
else if(LCD_flag>10&&LCD_flag<=14&&x=='Y')LCD_flag--;
else if(LCD_flag>=10&&LCD_flag<14&&x=='N')LCD_flag++;
else if(LCD_flag==10&&x=='Y')LCD_flag=0;
else if(LCD_flag==14&&x=='N')LCD_flag=0;
/*���ڲ���ҳ��*/
else if(LCD_flag==0&&x=='5')LCD_flag=20;
else if(LCD_flag>20&&LCD_flag<=22&&x=='Y')LCD_flag--;
else if(LCD_flag>=20&&LCD_flag<22&&x=='N')LCD_flag++;
else if(LCD_flag==20&&x=='Y')LCD_flag=0;
else if(LCD_flag==22&&x=='N')LCD_flag=0;    
else if(LCD_flag>=20&&LCD_flag<=22&&x>'0'&&x<='4'){LCD_para_num=(uint)((LCD_flag-20)*10+x-38);LCD_flag=3;LCD_clear();}
/*�޸Ĳ���ҳ��*/
else if(LCD_flag==3&&x>='0'&&x<='9'&&LCD_float_flag!=0){LCD_float_flag++;LCD_tmp_float(x);}
else if(LCD_flag==3&&x>='0'&&x<='9'&&LCD_float_flag==0){LCD_temp_zhi(x);}
else if(LCD_flag==3&&x=='Y'&&(uchar)(LCD_para_num/10+19)==20&&LCD_float_flag==0) {LCD_float_flag=1;float_num=(float)LCD_temp;LCD_temp=0;LCD_tmp_float(x);}
else if(LCD_flag==3&&x=='Y'&&(uchar)(LCD_para_num/10+19)==20&&LCD_float_flag!=0) {LCD_temp_float_confirm(LCD_para_num,float_num);LCD_flag=20;}  
else if(LCD_flag==3&&x=='Y'&&(uchar)(LCD_para_num/10+19)!=20){LCD_temp_confirm(LCD_para_num,LCD_temp);LCD_flag=(uchar)(LCD_para_num/10+19);}
else if(LCD_flag==3&&x=='N'){  LCD_temp=0;float_num=0;LCD_float_flag=0;LCD_flag=(uchar)(LCD_para_num/10+19);}
/*����ѡ��ҳ��*/
else if(LCD_flag==0&&x=='9'){LCD_clear();LCD_flag=40;}
else if(LCD_flag>40&&LCD_flag<=42&&x=='Y'){LCD_clear();LCD_flag--;}
else if(LCD_flag>=40&&LCD_flag<42&&x=='N'){LCD_clear();LCD_flag++;}
else if(LCD_flag==40&&x=='Y')LCD_flag=0;
else if(LCD_flag==42&&x=='N')LCD_flag=0; 
else if(LCD_flag>=40&&LCD_flag<=42&&x>'0'&&x<='4'){LCD_close_plan(((int)LCD_flag-39)*10+(int)x-48);}


   result= LCD_flag;
    switch(result)
    {
    /*С����ҳ��*/
    case 0:   	/*����С����ҳ��*/
    LCD_show();							
    break;   
    /*����������*/
    case 10:    /*�����⼤��״̬ҳ��*/
    LCD_T_JG(light_temp_laser_array);								
    break;
    case 11:    /*���������״̬ҳ��*/
    LCD_T_IR();						
    break;
    case 12:    /*�������µ�״̬ҳ��*/
    LCD_T_podao();						
    break;
    case 13:    /*����������״̬ҳ��*/
    LCD_T_qipao();						
    break;
    case 14:    /*���������״̬ҳ��*/
    LCD_T_cesu();						
    break;
    /*����С������*/
    case 20:    /*������ڲ���״̬��ҳ��0*/
    LCD_para(20);						
    break;
    case 21:    /*������ڲ���״̬��ҳ��1*/
    LCD_para(21);						
    break;
    case 22:    /*������ڲ���״̬��ҳ��2*/
    LCD_para(22);						
    break;
    /*�޸�С������*/
    case 3:    /*������ڲ���״̬ҳ��*/
    LCD_para_modify(LCD_para_num);						
    break;
    /*����ѡ��*/
    case 40:    /*���뷽��ѡ��ҳ��0*/
    LCD_plan_choose(40);						
    break;
    case 41:    /*���뷽��ѡ��ҳ��1*/
    LCD_plan_choose(41);						
    break;
    case 42:    /*���뷽��ѡ��ҳ��2*/
    LCD_plan_choose(42);						
    break;
    }
}
void LCD_xianshi(){ 
   uchar key; 
  	if (LCD_checkkey()!=0x00){
    key= LCD_keyscan();
          LCD_determine(LCD_keytran(key));
    delay_nms(100);
    	} 
    else if (LCD_checkkey()==0x00&&LCD_flag==10) {
    LCD_T_JG(light_temp_laser_array);
    delay_nms(400);
    }
    else if (LCD_checkkey()==0x00&&LCD_flag==11) {
    LCD_T_IR();	
    delay_nms(400);
    }
    else if (LCD_checkkey()==0x00&&LCD_flag==12) {
    LCD_T_podao();
    delay_nms(400);
    }
    else if (LCD_checkkey()==0x00&&LCD_flag==13) {
    LCD_T_qipao();
    delay_nms(400);
    }
    else if (LCD_checkkey()==0x00&&LCD_flag==14) {
    LCD_T_cesu();	
    delay_nms(400);
    }

}