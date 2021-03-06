/*--------------------------------------------
	Written by:	林震
	Modify by: 	林震
    Date:       2011.04.09
    Update:     2011.07.07             
	说明：LCD显示初始化及相关函数调用
----------------------------------------------*/        
uint LCD_flag=0,LCD_temp=0,LCD_para_num=0,LCD_float_flag=0;
byte LCD_plan_xudas,LCD_plan_xuxiaos,LCD_plan_das,LCD_plan_xiaos,LCD_plan_podao,LCD_plan_qipao;
float float_num;

//float Kp,Ki,Kd;

#define RST PTM_PTM0     		//复位用M7口   
#define SCE PTM_PTM1          //片选用M6口
#define DC PTM_PTM2           //DC用M5口
#define SDIN PTM_PTM3         //数据用M4口
#define SCLK PTM_PTM4       	//时钟用M3口
unsigned char lcdx=0,lcdy=0;
/*
sbit    \SCE = SCE;  //片选		
sbit    \RST = RST;  //复位,0复位
sbit    D/C  = DC;  //1写数据，0写指令
sbit    SDIN = SDIN;  //数据
sbit    SCLK = SCLK;  //时钟
*/

/*--------------------------------------------
data: 5*8字符
说明：根据ASCII码排列，字模数据是由空格(sp)开始,空格字符的ASCII的值就是32  
编写日期：20110409 
----------------------------------------------*/
unsigned char data[]={
0x00, 0x00, 0x00, 0x00, 0x00,   // sp     
0x00, 0x00, 0x2f, 0x00, 0x00,   // !     
0x00, 0x07, 0x00, 0x07, 0x00,   // "     
0x14, 0x7f, 0x14, 0x7f, 0x14,   // #     
0x24, 0x2a, 0x7f, 0x2a, 0x12,   // $     
0x62, 0x64, 0x08, 0x13, 0x23,   // %     
0x36, 0x49, 0x55, 0x22, 0x50,   // &     
0x00, 0x05, 0x03, 0x00, 0x00,   // ’     
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
0x00, 0x01, 0x02, 0x04, 0x00,   // ’     
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
hanzi_16: 自定义汉字16*16字库
说明：如需添加汉字，在最后面按顺序添加，切勿中间插入
编写日期：20110707 
----------------------------------------------*/
unsigned char hanzi_16[]=
{
/*--  文字:  厦  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x00,0x00,0xFF,0x05,0x05,0xF5,0x55,0x5D,0x55,0x55,0x55,0x55,0xF5,0x05,0x01,0x00,
0x40,0x30,0x0F,0x80,0xA0,0x97,0xBD,0x55,0x55,0x55,0x55,0x55,0xB7,0x80,0x80,0x00,

/*--  文字:  门  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x00,0xF8,0x01,0x06,0x00,0x00,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0xFE,0x00,0x00,
0x00,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x40,0x80,0x7F,0x00,0x00,

/*--  文字:  大  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x20,0x20,0x20,0x20,0x20,0x20,0x20,0xFF,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x00,
0x80,0x80,0x40,0x20,0x10,0x0C,0x03,0x00,0x03,0x0C,0x10,0x20,0x40,0x80,0x80,0x00,

/*--  文字:  学  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x40,0x30,0x11,0x96,0x90,0x90,0x91,0x96,0x90,0x90,0x98,0x14,0x13,0x50,0x30,0x00,
0x04,0x04,0x04,0x04,0x04,0x44,0x84,0x7E,0x06,0x05,0x04,0x04,0x04,0x04,0x04,0x00,

/*--  文字:  嘉  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x02,0x02,0x0A,0xEA,0xAA,0xAA,0xAA,0xAF,0xAA,0xAA,0xAA,0xEA,0x0A,0x02,0x02,0x00,
0x82,0x4A,0x2A,0x1E,0x0B,0x4A,0x8A,0x7A,0x02,0xFA,0x4B,0x4A,0x4A,0xFA,0x02,0x00,

/*--  文字:  庚 --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x00,0x00,0xFC,0x04,0x24,0x24,0x24,0x25,0xF6,0x24,0x24,0x24,0xE4,0x04,0x04,0x00,
0x40,0x30,0x8F,0x81,0x49,0x49,0x29,0x19,0x0F,0x19,0x29,0x49,0x4F,0x81,0x81,0x00,

/*--  文字:  学  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x40,0x30,0x10,0x12,0x5C,0x54,0x50,0x51,0x5E,0xD4,0x50,0x18,0x57,0x32,0x10,0x00,
0x00,0x02,0x02,0x02,0x02,0x02,0x42,0x82,0x7F,0x02,0x02,0x02,0x02,0x02,0x02,0x00,

/*--  文字:  院  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0xFE,0x02,0x32,0x4A,0x86,0x0C,0x24,0x24,0x25,0x26,0x24,0x24,0x24,0x0C,0x04,0x00,
0xFF,0x00,0x02,0x04,0x83,0x41,0x31,0x0F,0x01,0x01,0x7F,0x81,0x81,0x81,0xF1,0x00,

/*--  文字:  光  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x40,0x40,0x42,0x44,0x58,0xC0,0x40,0x7F,0x40,0xC0,0x50,0x48,0x46,0x40,0x40,0x00,
0x80,0x80,0x40,0x20,0x18,0x07,0x00,0x00,0x00,0x3F,0x40,0x40,0x40,0x40,0x78,0x00,

/*--  文字:  电  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x00,0x00,0xF8,0x88,0x88,0x88,0x88,0xFF,0x88,0x88,0x88,0x88,0xF8,0x00,0x00,0x00,
0x00,0x00,0x1F,0x08,0x08,0x08,0x08,0x7F,0x88,0x88,0x88,0x88,0x9F,0x80,0xF0,0x00,

/*--  文字:  谷  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x00,0x10,0x88,0x84,0x43,0x20,0x10,0x0C,0x10,0x20,0x41,0x82,0x84,0x08,0x00,0x00,
0x01,0x01,0x00,0xFE,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0xFE,0x00,0x01,0x01,0x00,

/*--  文字:  风  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x00,0x00,0xFE,0x02,0x12,0x22,0xC2,0x02,0xC2,0x32,0x02,0xFE,0x00,0x00,0x00,0x00,
0x80,0x60,0x1F,0x00,0x20,0x10,0x0C,0x03,0x0C,0x30,0x00,0x0F,0x30,0x40,0xF8,0x00,

};

/*--------------------------------------------
hanzi_12: 自定义汉字12*12字库
说明：如需添加汉字，在最后面按顺序添加，切勿中间插入
编写日期：20110707 
----------------------------------------------*/
	unsigned char hanzi_12[]=
{
//进
	0x10,0x11,0xF2,0x40,0x44,0xFF,0x44,0x44,0xFF,0x44,0x40,0x00,0x08,0x04,0x03,0x04,0x0A,0x09,0x08,0x08,0x0B,0x08,0x08,0x00,
//入
	0x00,0x00,0x01,0x81,0x72,0x0C,0x70,0x80,0x00,0x00,0x00,0x00,0x08,0x04,0x02,0x01,0x00,0x00,0x00,0x01,0x02,0x04,0x08,0x00,
//赛
	0x26,0xAA,0xEA,0xBE,0xAA,0xAB,0xAA,0xBE,0xEA,0xAA,0x26,0x00,0x01,0x00,0x0B,0x08,0x04,0x03,0x04,0x04,0x0B,0x00,0x01,0x00,
//道
	0x10,0x11,0xF2,0x00,0xFA,0xAB,0xAE,0xAA,0xAA,0xAB,0xFA,0x00,0x08,0x04,0x03,0x04,0x0B,0x0A,0x0A,0x0A,0x0A,0x0A,0x0B,0x00,
//测
	0x22,0x44,0xFE,0x02,0xFA,0x02,0xFE,0x00,0xFC,0x00,0xFF,0x00,0x04,0x02,0x09,0x04,0x03,0x04,0x09,0x00,0x01,0x08,0x0F,0x00,
//试
	0x11,0xF2,0x00,0x00,0x24,0xE4,0x24,0x04,0xFF,0x04,0x05,0x00,0x00,0x0F,0x04,0x00,0x04,0x07,0x02,0x00,0x03,0x04,0x0E,0x00,
//调
	0x11,0xF2,0x00,0x00,0xFF,0x21,0xA9,0xBD,0xA9,0x21,0xFF,0x00,0x00,0x07,0x02,0x08,0x07,0x00,0x03,0x02,0x0B,0x08,0x0F,0x00,
//节
	0x24,0x24,0x24,0x2F,0xE4,0x24,0x24,0x2F,0x24,0xE4,0x04,0x00,0x00,0x00,0x00,0x00,0x0F,0x00,0x00,0x00,0x02,0x03,0x00,0x00,
//参
	0x90,0x54,0xB6,0x95,0x5C,0x54,0x34,0x94,0x36,0x54,0x90,0x00,0x00,0x0A,0x0A,0x0A,0x0A,0x09,0x05,0x04,0x04,0x02,0x00,0x00,
//数
	0x48,0x2A,0x98,0x7F,0x28,0x4A,0x10,0xEF,0x08,0xF8,0x08,0x00,0x09,0x0B,0x05,0x05,0x0B,0x00,0x08,0x05,0x02,0x05,0x08,0x00,
//激
	0x22,0x44,0x80,0xBE,0xEB,0xBE,0x10,0xEC,0x0B,0xF8,0x08,0x00,0x04,0x02,0x08,0x07,0x0A,0x0E,0x08,0x04,0x03,0x04,0x08,0x00,
//光
	0x20,0x22,0x24,0xE8,0x20,0x3F,0x20,0xE8,0x24,0x22,0x20,0x00,0x08,0x04,0x02,0x01,0x00,0x00,0x00,0x07,0x08,0x08,0x0E,0x00,
//红
	0x98,0xD4,0xB3,0x88,0x00,0x02,0x02,0xFE,0x02,0x02,0x00,0x00,0x04,0x04,0x02,0x02,0x08,0x08,0x08,0x0F,0x08,0x08,0x08,0x00,
//外
	0x40,0x30,0x4F,0x88,0x78,0x00,0x00,0xFF,0x10,0x20,0xC0,0x00,0x08,0x04,0x02,0x01,0x00,0x00,0x00,0x0F,0x00,0x00,0x00,0x00,
//判
	0x80,0x92,0x94,0xFF,0x94,0x92,0x80,0xFC,0x00,0x00,0xFF,0x00,0x00,0x08,0x06,0x01,0x00,0x00,0x00,0x01,0x08,0x08,0x0F,0x00,
//断
	0xFC,0x92,0x54,0xFF,0x54,0x92,0x00,0xFE,0x12,0xF2,0x11,0x00,0x07,0x04,0x04,0x07,0x04,0x04,0x08,0x07,0x00,0x0F,0x00,0x00,
//坡
	0x08,0x08,0xFF,0x08,0xFC,0x24,0xE4,0x3F,0x24,0xE4,0x0C,0x00,0x02,0x02,0x01,0x09,0x07,0x08,0x05,0x02,0x05,0x08,0x08,0x00,
//起
	0x20,0xA4,0x24,0xFF,0x24,0x00,0xF2,0x12,0x12,0x1E,0x80,0x00,0x08,0x07,0x04,0x0F,0x09,0x08,0x09,0x0A,0x0A,0x0A,0x0B,0x00,
//跑
	0x9E,0x12,0xF2,0x9E,0x08,0xF4,0x97,0x94,0xF4,0x04,0xFC,0x00,0x0F,0x08,0x07,0x04,0x00,0x07,0x08,0x08,0x08,0x09,0x0D,0x00,
//速
	0x11,0xF2,0x00,0x7A,0x4A,0xCA,0xFF,0xCA,0x4A,0x7A,0x02,0x00,0x08,0x07,0x08,0x0A,0x09,0x08,0x0F,0x08,0x09,0x0A,0x08,0x00,
//方
	0x04,0x04,0x04,0xFC,0x25,0x26,0x24,0x24,0x24,0xE4,0x04,0x00,0x08,0x04,0x03,0x00,0x00,0x00,0x08,0x08,0x08,0x07,0x00,0x00,
//案
	0x46,0x4A,0x4A,0x5A,0x2E,0xAB,0x2A,0x5A,0x4A,0x4A,0x06,0x00,0x09,0x09,0x05,0x03,0x01,0x0F,0x01,0x03,0x05,0x09,0x09,0x00,
//选
	0x10,0x11,0xF2,0x00,0x28,0x26,0xE4,0x3F,0xE4,0x24,0x20,0x00,0x08,0x04,0x03,0x04,0x0A,0x09,0x08,0x08,0x09,0x0A,0x0B,0x00,
//择
	0x88,0x88,0xFF,0x48,0x21,0xA3,0x95,0xE9,0x95,0xA3,0x20,0x00,0x00,0x08,0x0F,0x00,0x02,0x02,0x02,0x0F,0x02,0x02,0x02,0x00,
	};

void delay_1ms(void)                  //1ms延时函数
{
	unsigned int i;
	for (i=0;i<600;i++)	  ;
;
}
void delay_nms(unsigned int n)        //N ms延时函数
  {
   unsigned int i=0;
   for (i=0;i<n;i++)
   delay_1ms();
  }

/*--------------------------------------------
LCD_write_byte: 使用SPI接口写数据到LCD
输入参数：dt：写入的数据；
command ：写数据/命令选择；
编写日期：20080918 
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
LCD_set_XY: 设置LCD坐标函数
输入参数：X：0－83  Y：0－5
编写日期：20080918 
---------------------------------------------*/
void LCD_set_XY(unsigned char X, unsigned char Y)
{
	LCD_write_byte(0x40 | Y, 0);// column
	LCD_write_byte(0x80 | X, 0);// row
} 

/*------------------------------------------
LCD_clear: LCD清屏函数
编写日期：20080918 
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
LCD_position: 显示LCD字符当前位置
说明：判断当前位置并返回到lcdx和lcdy这两个全局变量，lcdx是行，lcdy是列
编写日期：20110410
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
LCD_write_zi: 显示5（宽）*8（高）点阵列数字字母符号等半角类
输入参数：c：显示的字符；
编写日期：20110409 
-----------------------------------------------*/
void LCD_write_zi(unsigned char row, unsigned char line,unsigned char c) //row:列 line:行 dd:字符
{
unsigned char i=0;     
unsigned int No;     
No=c-32;                 //字模数据是由空格开始,空格字符的ASCII的值就是32  
No*=5;  
	LCD_set_XY(row, line);// 列，行
while(i<5)                     //一个字符的字模是5个字节,就是5*8点阵     
  {     
    LCD_write_byte(data[No],1);       
    i++;     
   No++;
  } 
}
/*---------------------------------------------
LCD_write_cizu: 显示5（宽）*8（高）点阵列数字字母符号等半角类字符串
输入参数：c：显示的字符串
编写日期：20110410
-----------------------------------------------*/
 void LCD_write_cizu(unsigned char row, unsigned char line,char a[]) //row:列 line:行 dd:字符 
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
LCD_write_shuzi: 显示5（宽）*8（高）点阵列数字
输入参数：a：显示的数字
编写日期：20110410
-----------------------------------------------*/
 void LCD_write_shuzi(unsigned char row, unsigned char line,int a) //row:列 line:行 dd:字符 
 {
 char b[10];
 (void)sprintf(b,"%d",a);
 LCD_write_cizu(row,line,b);
 }
 
/*---------------------------------------------
LCD_write_hanzi: 显示16（宽）*16（高）点阵列汉字等半角类
输入参数：c：显示的字符；
编写日期：20110707 
-----------------------------------------------*/
void LCD_write_hanzi_16(unsigned char row, unsigned char line,unsigned char c) //row:列 line:行 dd:字符
{
	unsigned char i;  	
	
	LCD_set_XY(row*4, line);// 列，行 
	for(i=0; i<16;i++) 
	{
		LCD_write_byte(hanzi_16[c*32+i],1); 
	}
	
    LCD_set_XY(row*4, line+1);// 列，行 
	for(i=16; i<32;i++) 
	{
		LCD_write_byte(hanzi_16[c*32+i],1);
	}	
}

/*---------------------------------------------
LCD_write_hanzi: 显示16（宽）*16（高）点阵列汉字等半角类
输入参数：c：显示的字符；
编写日期：20110707 
-----------------------------------------------*/
void LCD_write_hanzi_12(unsigned char row, unsigned char line,unsigned char c) //row:列 line:行 dd:字符
{
	unsigned char i;  	
	
	LCD_set_XY(row*3, line);// 列，行 
	for(i=0; i<12;i++) 
	{
		LCD_write_byte(hanzi_12[c*24+i],1); 
	}
	
    LCD_set_XY(row*3, line+1);// 列，行 
	for(i=12; i<24;i++) 
	{
		LCD_write_byte(hanzi_12[c*24+i],1);
	}	}

/*---------------------------------------
LCD_init: 5110LCD初始化
编写日期：20110707 
-----------------------------------------  */
void LCD_init(void)
{
  DDRM = 0XFF;        //初始化M7~M3口
  DDRH = 0X0F;        //初始化H7~M4口，供按键的列使用
	RST=0;  	
  delay_1ms();
  RST=1;  
	LCD_write_byte(0x21,0);//初始化Lcd,功能设定使用扩充指令
	LCD_write_byte(0xd0,0);//设定液晶偏置电压
	LCD_write_byte(0x20,0);//使用基本指令
	LCD_write_byte(0x0C,0);//设定显示模式，正常显示
	LCD_clear(); //清屏幕
}

/*---------------------------------------
LCD_checkkey: 检测有没有键按下
编写日期：20110707
-----------------------------------------  */
uchar LCD_checkkey()						//检测有没有键按下
{uchar i ;
 uchar j ;
 j=0x1F&PTM;
 PTM=j;
 i=PTH&0xF0;
 if(i==0xF0) return (0);
  else return (0xFF);
  }
  
/*---------------------------------------
LCD_keyscan:键盘扫描程序
编写日期：20110707
-----------------------------------------  */  
uchar LCD_keyscan()						//键盘扫描程序
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
	    PTM=a;        m=0x41;   		//键盘行扫描初值，M为列数
 	  for (i=1;i<=3;i++)
	      {
            k=0x10;              
	 	    for (j=0;j<4;j++)			//J为行数
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
LCD_start: 显示屏启动时显示"厦门大学嘉庚学院光电一队"
编写日期：20110409
-----------------------------------------------*/
void LCD_start(void) 
{
	LCD_clear();
	LCD_write_hanzi_16(1,0,0);   //厦
	LCD_write_hanzi_16(6,0,1);   //门
	LCD_write_hanzi_16(11,0,2);  //大
	LCD_write_hanzi_16(16,0,3);  //学
	
	LCD_write_hanzi_16(1,2,4);   //嘉
	LCD_write_hanzi_16(6,2,5);   //庚
	LCD_write_hanzi_16(11,2,6);  //学
	LCD_write_hanzi_16(16,2,7);  //院
	
	LCD_write_hanzi_16(1,4,8);   //光
	LCD_write_hanzi_16(6,4,9);   //电
	LCD_write_hanzi_16(11,4,10); //谷
	LCD_write_hanzi_16(16,4,11); //风
	}
/*---------------------------------------------
LCD_show: 显示屏显示主界面
编写日期：20110707
-----------------------------------------------*/
	void LCD_show(void) {
	LCD_clear();
	LCD_flag=0;
	LCD_write_hanzi_12(2,0,0);  //进
	LCD_write_hanzi_12(6,0,1);  //入
	LCD_write_hanzi_12(10,0,2); //赛
	LCD_write_hanzi_12(14,0,3); //道
	LCD_write_hanzi_12(18,0,4); //测
	LCD_write_hanzi_12(22,0,5); //试
	
	LCD_write_hanzi_12(6,2,6);  //调
	LCD_write_hanzi_12(10,2,7); //节
	LCD_write_hanzi_12(14,2,8); //参
	LCD_write_hanzi_12(18,2,9); //数
	
	LCD_write_hanzi_12(6,4,20);  //方
	LCD_write_hanzi_12(10,4,21); //案
	LCD_write_hanzi_12(14,4,22); //选
	LCD_write_hanzi_12(18,4,23); //择
	}
/*---------------------------------------------
LCD_T_JG: 检测激光
编写日期：20110707
-----------------------------------------------*/	
void LCD_T_JG(byte temp_laser_array[]) {
  uchar i; 
  byte LCD_temp_data;
	LCD_clear();
	LCD_write_hanzi_12(8,0,4);    //测
	LCD_write_hanzi_12(12,0,10);  //激
	LCD_write_hanzi_12(16,0,11);  //光
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
  LCD_write_shuzi(35,4,position);
	LCD_write_cizu(0,5,"<-");
	LCD_write_cizu(73,5,"->");  
}
/*---------------------------------------------
LCD_T_IR: 检测红外
编写日期：20110707
-----------------------------------------------*/	
void LCD_T_IR(void) {
  int i=0;
	LCD_clear();
	LCD_write_hanzi_12(8,0,4);    //测
	LCD_write_hanzi_12(12,0,12);  //红
	LCD_write_hanzi_12(16,0,13);  //外
	do{ 
	LCD_write_shuzi(i*8+12,3,IR_temp_laser_array[i]);
    i++;
    }while(i<7);
	LCD_write_cizu(0,5,"<-");
	LCD_write_cizu(73,5,"->"); 
}
/*---------------------------------------------
LCD_T_podao: 检测坡道
编写日期：20110707
-----------------------------------------------*/	
void LCD_T_podao(void) {
	LCD_clear();
	LCD_write_hanzi_12(6,0,14);   //判
	LCD_write_hanzi_12(10,0,15);  //断
	LCD_write_hanzi_12(14,0,16);  //坡
	LCD_write_hanzi_12(18,0,3);   //道
	if(slope_flag==0){
  LCD_write_cizu(14,3,"Not Podao");}
  else if(slope_flag==1)
  {LCD_write_cizu(10,3,"It's Podao");}
	LCD_write_cizu(0,5,"<-");
	LCD_write_cizu(73,5,"->"); 
}
/*---------------------------------------------
LCD_T_qipao: 检测起跑
编写日期：20110707
-----------------------------------------------*/	
void LCD_T_qipao(void) {
	LCD_clear();
	LCD_write_hanzi_12(8,0,4);    //测
	LCD_write_hanzi_12(12,0,17);  //起
	LCD_write_hanzi_12(16,0,18);  //跑
	if(start_flag==0){
  LCD_write_cizu(14,3,"Not QiPao");}
  else if(start_flag==1)
  {LCD_write_cizu(10,3,"It's QiPao");}
	LCD_write_cizu(0,5,"<-");
	LCD_write_cizu(73,5,"->");  
}
/*---------------------------------------------
LCD_T_qipao: 检测测速
编写日期：20110707
-----------------------------------------------*/	
void LCD_T_cesu(void) {
	LCD_clear();
	LCD_write_hanzi_12(8,0,4);    //测
	LCD_write_hanzi_12(12,0,4);   //测
	LCD_write_hanzi_12(16,0,19);  //速
  LCD_write_shuzi(35,3,(int)speed_clear[1]);
	LCD_write_cizu(0,5,"<-");
	LCD_write_cizu(73,5,"->"); 
}
	/*---------------------------------------------
LCD_para: 修改参数的主页面
参数是要改的值
编写日期：20110708
-----------------------------------------------*/
  void LCD_para(uint a) {
  	int num;
	LCD_clear();

	switch(a)
    {
    case 20:     //修改参数的主页面0
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
    case 21:     //修改参数的主页面1
 {
  LCD_write_cizu(0,0,"Modify Page 2");
  LCD_write_cizu(0,1,"Subu:");
  LCD_write_shuzi(30,1,Subu);
  LCD_write_cizu(0,2,"ZhiSp:");
  LCD_write_shuzi(37,2,ZhiSpeed);
  LCD_write_cizu(0,3,"WanSp:");
  LCD_write_shuzi(37,3,WanSpeed);
	LCD_write_cizu(0,5,"<-");
	LCD_write_cizu(73,5,"->");
 }
    break;
    case 22:     //修改BD参数的主页面1
  {
    LCD_write_cizu(0,0,"Modify BD PG1");
  LCD_write_cizu(0,1,"BD1:");
  LCD_write_shuzi(30,1,BD1);
  LCD_write_cizu(0,2,"BD2:");
  LCD_write_shuzi(30,2,BD2);
  LCD_write_cizu(0,3,"BD3:");
  LCD_write_shuzi(30,3,BD3);
  LCD_write_cizu(0,4,"BD4:");
  LCD_write_shuzi(30,4,BD4);
	LCD_write_cizu(0,5,"<-");
	LCD_write_cizu(73,5,"->"); 
  }
    break;
        case 23:     //修改BD参数的主页面2
  {
    LCD_write_cizu(0,0,"Modify BD PG2");
  LCD_write_cizu(0,1,"BD5:");
  LCD_write_shuzi(30,1,BD5);
  LCD_write_cizu(0,2,"BD6:");
  LCD_write_shuzi(30,2,BD6);
  LCD_write_cizu(0,3,"BD7:");
  LCD_write_shuzi(30,3,BD7);
  LCD_write_cizu(0,4,"BD8:");
  LCD_write_shuzi(30,4,BD8);
	LCD_write_cizu(0,5,"<-");
	LCD_write_cizu(73,5,"->"); 
  }
    break;
        case 24:     //修改BD参数的主页面3
  {
    LCD_write_cizu(0,0,"Modify BD PG3");
  LCD_write_cizu(0,1,"BD9:");
  LCD_write_shuzi(30,1,BD9);
  LCD_write_cizu(0,2,"BD10:");
  LCD_write_shuzi(30,2,BD10);
	LCD_write_cizu(0,5,"<-");
	LCD_write_cizu(73,5,"->"); 
  }
    break;
    } 
	}
/*---------------------------------------------
LCD_para_modify: 修改参数的页面
参数是要改的值
编写日期：20110708
-----------------------------------------------*/
void LCD_para_modify(uint a) {
LCD_write_cizu(0,0,"Modify");
 switch(a)
 {
    case 11:     //修改Kp参数
  LCD_write_cizu(40,0,"Kp");
  LCD_write_cizu(0,5,"YES");
	LCD_write_cizu(73,5,"NO");   
    break;
    case 12:     //修改Ki参数
  LCD_write_cizu(40,0,"Ki");
  LCD_write_cizu(0,5,"YES");
	LCD_write_cizu(73,5,"NO"); 
    break;
    case 13:     //修改Kd参数
  LCD_write_cizu(40,0,"Kd");
  LCD_write_cizu(0,5,"YES");
	LCD_write_cizu(73,5,"NO"); 
    break;
    case 21:     //修改Subu参数
  LCD_write_cizu(40,0,"Subu");
  LCD_write_cizu(0,5,"YES");
	LCD_write_cizu(73,5,"NO");   
    break;
    case 22:     //修改ZhiSpeed参数
  LCD_write_cizu(40,0,"ZhiS");
  LCD_write_cizu(0,5,"YES");
	LCD_write_cizu(73,5,"NO"); 
    break;
    case 23:     //修改WanSpeed参数
  LCD_write_cizu(40,0,"WanS");
  LCD_write_cizu(0,5,"YES");
	LCD_write_cizu(73,5,"NO"); 
    break;
    case 31:     //修改BD1参数
  LCD_write_cizu(40,0,"BD1");
  LCD_write_cizu(0,5,"YES");
	LCD_write_cizu(73,5,"NO"); 
    break;
    case 32:     //修改BD2参数
  LCD_write_cizu(40,0,"BD2");
  LCD_write_cizu(0,5,"YES");
	LCD_write_cizu(73,5,"NO"); 
    break;
    case 33:     //修改BD3参数
  LCD_write_cizu(40,0,"BD3");
  LCD_write_cizu(0,5,"YES");
	LCD_write_cizu(73,5,"NO"); 
    break;
    case 34:     //修改BD4参数
  LCD_write_cizu(40,0,"BD4");
  LCD_write_cizu(0,5,"YES");
	LCD_write_cizu(73,5,"NO"); 
    break;
  case 41:     //修改BD5参数
  LCD_write_cizu(40,0,"BD5");
  LCD_write_cizu(0,5,"YES");
	LCD_write_cizu(73,5,"NO"); 
    break;
  case 42:     //修改BD6参数
  LCD_write_cizu(40,0,"BD6");
  LCD_write_cizu(0,5,"YES");
	LCD_write_cizu(73,5,"NO"); 
    break;
  case 43:     //修改BD7参数
  LCD_write_cizu(40,0,"BD7");
  LCD_write_cizu(0,5,"YES");
	LCD_write_cizu(73,5,"NO"); 
    break;
  case 44:     //修改BD8参数
  LCD_write_cizu(40,0,"BD8");
  LCD_write_cizu(0,5,"YES");
	LCD_write_cizu(73,5,"NO"); 
    break;
  case 51:     //修改BD9参数
  LCD_write_cizu(40,0,"BD9");
  LCD_write_cizu(0,5,"YES");
	LCD_write_cizu(73,5,"NO"); 
    break;
  case 52:     //修改BD10参数
  LCD_write_cizu(40,0,"BD10");
  LCD_write_cizu(0,5,"YES");
	LCD_write_cizu(73,5,"NO"); 
    break;
    } 
	 }
/*---------------------------------------------
LCD_temp_confirm: 确认后修改值
编写日期：20110708
-----------------------------------------------*/
void LCD_temp_confirm(uint num,uint zhi) {
 switch(num)
 {
    case 21:     //修改Subu参数
  Subu=zhi;
  LCD_temp=0; 
    break;
    case 22:     //修改ZhiSpeed参数
  ZhiSpeed=zhi;
  LCD_temp=0;
    break;
    case 23:     //修改WanSpeed参数
  WanSpeed=zhi;
  LCD_temp=0;
    break;
        case 31:     //修改BD1参数
      BD1=zhi;
      LCD_temp=0;
    break;
    case 32:     //修改BD2参数
      BD2=zhi;
      LCD_temp=0; 
    break;
    case 33:     //修改BD3参数
      BD3=zhi;
      LCD_temp=0; 
    break;
    case 34:     //修改BD4参数
      BD4=zhi;
      LCD_temp=0;
    break;
  case 41:     //修改BD5参数
      BD5=zhi;
      LCD_temp=0; 
    break;
  case 42:     //修改BD6参数
      BD6=zhi;
      LCD_temp=0; 
    break;
  case 43:     //修改BD7参数
      BD7=zhi;
      LCD_temp=0; 
    break;
  case 44:     //修改BD8参数
      BD8=zhi;
      LCD_temp=0;
    break;
  case 51:     //修改BD9参数
      BD9=zhi;
      LCD_temp=0; 
    break;
  case 52:     //修改BD10参数
      BD10=zhi;
      LCD_temp=0;
    break;
   } 
	}
/*---------------------------------------------
LCD_temp_float_confirm: 确认后修改值
编写日期：20110713
-----------------------------------------------*/
void LCD_temp_float_confirm(uint num,float zhi) {
 switch(num)
 {
    case 11:     //修改参数1
  Kp=zhi;
  LCD_temp=0;
  float_num=0;
  LCD_float_flag=0; 
    break;
    case 12:     //修改参数2
  Ki=zhi;
  LCD_temp=0;
  float_num=0;
  LCD_float_flag=0;
    break;
    case 13:     //修改参数3
  Kd=zhi;
  LCD_temp=0;
  float_num=0;
  LCD_float_flag=0;
    break;
   } 
	}
/*---------------------------------------------
LCD_keytran: 按键转数字
编写日期：20110708
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
LCD_temp_zhi: 要改的值
编写日期：20110708
-----------------------------------------------*/
void LCD_temp_zhi(uchar a) {
   int int_tmp;
   int_tmp=(int)a-48;
   if(int_tmp==10)int_tmp=0;
   LCD_temp=LCD_temp*10+int_tmp;
   LCD_write_shuzi(5,3,LCD_temp); 
	}
/*---------------------------------------------
LCD_tmp_float: 要改的值(Float型)
编写日期：20110713
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
LCD_plan_choose: 方案选择页面 
编写日期：20110711
-----------------------------------------------*/
void LCD_plan_choose(uint a) {
	switch(a) {
	 case 40:     //方案选择的主页面0
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
    case 41:     //方案选择的主页面1
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
    case 42:     //方案选择的主页面2
    {
  LCD_write_cizu(5,0,"Plan Choose 3");
	LCD_write_cizu(0,5,"<-");
	LCD_write_cizu(73,5,"->");  
   }break; 
	} 
}
	/*---------------------------------------------
LCD_close_plan:关闭方案选择
编写日期：20110711             
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
LCD_determine: 按键判断并执行动作
编写日期：20110707
-----------------------------------------------*/	
void LCD_determine(uchar x) {
	uint result;
	
/*进入赛道测试向导*/
if(LCD_flag==0&&x=='1')LCD_flag=10;
else if(LCD_flag>10&&LCD_flag<=14&&x=='Y')LCD_flag--;
else if(LCD_flag>=10&&LCD_flag<14&&x=='N')LCD_flag++;
else if(LCD_flag==10&&x=='Y')LCD_flag=0;
else if(LCD_flag==14&&x=='N')LCD_flag=0;
/*调节参数页面*/
else if(LCD_flag==0&&x=='5')LCD_flag=20;
else if(LCD_flag>20&&LCD_flag<=24&&x=='Y')LCD_flag--;
else if(LCD_flag>=20&&LCD_flag<24&&x=='N')LCD_flag++;
else if(LCD_flag==20&&x=='Y')LCD_flag=0;
else if(LCD_flag==24&&x=='N')LCD_flag=0;    
else if(LCD_flag>=20&&LCD_flag<=24&&x>'0'&&x<='4'){LCD_para_num=(uint)((LCD_flag-20)*10+x-38);LCD_flag=3;LCD_clear();}
/*修改参数页面*/
else if(LCD_flag==3&&x>='0'&&x<='9'&&LCD_float_flag!=0){LCD_float_flag++;LCD_tmp_float(x);}
else if(LCD_flag==3&&x>='0'&&x<='9'&&LCD_float_flag==0){LCD_temp_zhi(x);}
else if(LCD_flag==3&&x=='Y'&&(uchar)(LCD_para_num/10+19)==20&&LCD_float_flag==0) {LCD_float_flag=1;float_num=(float)LCD_temp;LCD_temp=0;LCD_tmp_float(x);}
else if(LCD_flag==3&&x=='Y'&&(uchar)(LCD_para_num/10+19)==20&&LCD_float_flag!=0) {LCD_temp_float_confirm(LCD_para_num,float_num);LCD_flag=20;}  
else if(LCD_flag==3&&x=='Y'&&(uchar)(LCD_para_num/10+19)!=20){LCD_temp_confirm(LCD_para_num,LCD_temp);LCD_flag=(uchar)(LCD_para_num/10+19);}
else if(LCD_flag==3&&x=='N'){  LCD_temp=0;float_num=0;LCD_float_flag=0;LCD_flag=(uchar)(LCD_para_num/10+19);}
/*方案选择页面*/
else if(LCD_flag==0&&x=='9'){LCD_clear();LCD_flag=40;}
else if(LCD_flag>40&&LCD_flag<=42&&x=='Y'){LCD_clear();LCD_flag--;}
else if(LCD_flag>=40&&LCD_flag<42&&x=='N'){LCD_clear();LCD_flag++;}
else if(LCD_flag==40&&x=='Y')LCD_flag=0;
else if(LCD_flag==42&&x=='N')LCD_flag=0; 
else if(LCD_flag>=40&&LCD_flag<=42&&x>'0'&&x<='4'){LCD_close_plan(((int)LCD_flag-39)*10+(int)x-48);}


   result= LCD_flag;
    switch(result)
    {
    /*小车主页面*/
    case 0:   	/*进入小车主页面*/
    LCD_show();							
    break;   
    /*赛道测试向导*/
    case 10:    /*进入检测激光状态页面*/
    LCD_T_JG(light_temp_laser_array);								
    break;
    case 11:    /*进入检测红外状态页面*/
    LCD_T_IR();						
    break;
    case 12:    /*进入检测坡道状态页面*/
    LCD_T_podao();						
    break;
    case 13:    /*进入检测起跑状态页面*/
    LCD_T_qipao();						
    break;
    case 14:    /*进入检测测速状态页面*/
    LCD_T_cesu();						
    break;
    /*调节小车参数*/
    case 20:    /*进入调节参数状态主页面0*/
    LCD_para(20);						
    break;
    case 21:    /*进入调节参数状态主页面1*/
    LCD_para(21);						
    break;
    case 22:    /*进入调节BD1参数状态页面*/
    LCD_para(22);						
    break;
    case 23:    /*进入调节BD2参数状态页面*/
    LCD_para(23);						
    break;
    case 24:    /*进入调节BD3参数状态页面*/
    LCD_para(24);						
    break;
    /*修改小车参数*/
    case 3:    /*进入调节参数状态页面*/
    LCD_para_modify(LCD_para_num);						
    break;
    /*方案选择*/
    case 40:    /*进入方案选择页面0*/
    LCD_plan_choose(40);						
    break;
    case 41:    /*进入方案选择页面1*/
    LCD_plan_choose(41);						
    break;
    case 42:    /*进入方案选择页面2*/
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