//#include "Lcd1602.h"

//void read_busy()
//{
//	uchar i;
//	P0=0xff;
//	RS=0;
//	RW=1;
//	do{
//		EN=1;
//		i=P0;
//		EN=0;
//	}while(i&0x80);
//}
////LCD???
//void lcd_write_cmd(uchar cmd)
//{
//	read_busy();
//	RS=0;
//	RW=0;
//	P0=cmd;
//	EN=1;
//	EN=0;
//}
////LCD???
//void lcd_write_dat(uchar dat)
//{
//	read_busy();
//	RS=1;
//	RW=0;
//	P0=dat;
//	EN=1;
//	EN=0;
//}
////????
//void LcdSetCursor(uchar x,uchar y)
//{
//	uchar address;
//	if(y==0)
//		address=0x00+x;
//	else
//		address=0x40+x;
//	lcd_write_cmd(address|0x80);
//}
////????????
//void displayonechar(uchar x,uchar y,uchar dat)
//{
//	if(y)
//		x|=0x40;
//	x|=0x80;
//	lcd_write_cmd(x);
//	lcd_write_dat(dat);
//}
////????????
//void displayonestr(uchar x,uchar y,uchar dat)
//{
//	displayonechar(x++,y,dat/16+'0');
//	displayonechar(x,y,dat%16+'0');
//}
////?????
//void LcdShowStr(uchar x,uchar y,uchar *str)
//{
//	LcdSetCursor(x,y);
//	while(*str!='\0')
//		lcd_write_dat(*str++);
//}
////lcd???
//void lcdinit()
//{
//	lcd_write_cmd(0x38);
//	lcd_write_cmd(0x0c);
//	lcd_write_cmd(0x06);
//	lcd_write_cmd(0x01);
//}
