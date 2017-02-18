#include<reg52.h>

typedef unsigned char uchar;
typedef unsigned int uint;

sbit RS=P3^5;
sbit RW=P3^6;
sbit EN=P3^4;
sbit DU=P2^6;
sbit WE=P2^7;

void read_busy()
{
	uchar i;
	P0=0XFF;
	RS=0;
	RW=1;
	do{
		EN=1;
		i=P0;
		EN=0;
	}while(i&0x80);
}
void lcd_write_cmd(uchar cmd)
{
	read_busy();
	RS=0;
	RW=0;
	P0=cmd;
	EN=1;
	EN=0;
}
void lcd_write_dat(uchar dat)
{
	read_busy();
	RS=1;
	RW=0;
	P0=dat;
	EN=1;
	EN=0;
}
/* void LcdSetCursor(uchar x,uchar y)
{
	uchar addr;
	if(y)
		addr|=0x40;
	lcd_write_cmd(addr|0x80);
} */
void display_char(uchar x,uchar y,uchar dat)
{
	if(y)
		x|=0x40;
	x|=0x80;
	lcd_write_cmd(x);
	lcd_write_dat(dat);
}
void display_str(uchar x,uchar y,uchar *str)
{
	if(y)
		x|=0x40;
	x|=0x80;
	lcd_write_cmd(x);
	while(*str!='\0')
		lcd_write_dat(*str++);
}
/* void display_str(uchar x,uchar y,uchar dat)
{
	display_char(x++,y,dat/16+'0');
	display_char(x,y,dat%16+'0');
}
void LcdShowStr(uchar x,uchar y,uchar *str)
{
	LcdSetCursor(x,y);
	while(*str!='\0')
	{
		lcd_write_dat(*str++);
	}
} */
void init()
{
	lcd_write_cmd(0x38);
	lcd_write_cmd(0x0c);
	lcd_write_cmd(0x06);
	lcd_write_cmd(0x01);
}
void main()
{
	uchar string[]={"hello!"};
	DU=0;
	WE=0;
	init();
	display_str(0,0,&string[0]);
	display_char(10,0,65);
	while(1);
}

