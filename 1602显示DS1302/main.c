#include<reg52.h>
#include<intrins.h>

typedef unsigned char uchar;
typedef unsigned int uint;
//DS
sbit SCLK=P1^0;
sbit IO=P1^1;
sbit RST=P1^2;
//LCD
sbit RS=P3^5;
sbit RW=P3^6;
sbit EN=P3^4;
sbit DU=P2^6;
sbit WE=P2^7;
//时间
uchar timedata[7]={50,58,23,15,2,1,16};
//延时函数
void delayms(xms)
{
	uint i,j;
	for(i=xms;i>0;i--)
		for(j=114;j>0;j--);
}
//lcd部分
void read_busy()	//检测忙
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
void lcd_write_cmd(uchar cmd)	//LCD写命令
{
	read_busy();
	RS=0;
	RW=0;
	P0=cmd;
	EN=1;
	EN=0;
}
void lcd_write_dat(uchar dat)//LCD写数据
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
void display_char(uchar x,uchar y,uchar dat)//LCD显示字符
{
	if(y)
		x|=0x40;
	x|=0x80;
	lcd_write_cmd(x);
	lcd_write_dat(dat);
}
void lcdshow_str(uchar x,uchar y,uchar *str)//LCD显示字符串
{
	if(y)
		x|=0x40;
	x|=0x80;
	lcd_write_cmd(x);
	while(*str!='\0')
		lcd_write_dat(*str++);
}
void display_str(uchar x,uchar y,uchar dat)//LCD显示字符串
{
	display_char (x++,y,dat/16 + '0');
//	x=x+1;
	display_char (x,y,dat%16 + '0');
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
void init()	//LCD初始化
{
	lcd_write_cmd(0x38);
	lcd_write_cmd(0x0c);
	lcd_write_cmd(0x06);
	lcd_write_cmd(0x01);
}
//DS写数据
void write_ds(uchar cmd, uchar dat)
{
	uchar i;
	RST = 0; 
	SCLK = 0;
	RST = 1; 
	for(i = 0; i < 8; i++)
	{
		SCLK = 0;		  
		IO = cmd & 0x01; 
		SCLK = 1;		  
		cmd >>=1;		  
	}
	for(i = 0; i < 8; i++)
	{
		SCLK = 0;		  
		IO = dat & 0x01; 
		SCLK = 1;		 
		dat >>= 1;		
	}
}
//DS读数据
uchar read_ds(uchar cmd)
{
	uchar i,dat;
	RST=0;
	SCLK=0;
	RST=1;
	for(i=0;i<8;i++)
	{
		SCLK=0;
		IO=cmd&0x01;
		SCLK=1;
		cmd>>=1;
	}
	for(i=0;i<8;i++)
	{
		SCLK=0;
		dat>>=1;
		if(IO)
			dat|=0x80;
		SCLK=1;
	}
	return dat;
}
//dat-bcd
uchar dat_bcd(uchar dat)
{
	uchar dat1,dat2;
	dat1=dat/10;
	dat2=dat%10;
	dat2=dat2+dat1*16;
	return dat2;
}
//bcd-dat
uchar bcd_dat(uchar dat)
{
	uchar dat1,dat2;
	dat1=dat/16;
	dat2=dat%16;
	dat2=dat2+dat1*10;
	return dat2;
}
//设置DS时间
/* void set_ds_time()
{
	write_ds(0x8e,0);
	write_ds(0x80,dat_bcd(timedata[0]));
	write_ds(0x82,dat_bcd(timedata[1]));
	write_ds(0x84,dat_bcd(timedata[2]));
	write_ds(0x86,dat_bcd(timedata[3]));
	write_ds(0x88,dat_bcd(timedata[4]));
	write_ds(0x8a,dat_bcd(timedata[5]));
	write_ds(0x8c,dat_bcd(timedata[6]));
} */
void set_ds()
{
	write_ds(0x80,0);
	uchar addr=0x81;
	for(i=0;i<7;i++)
	{
		write_ds(addr,dat_bcd(timedata[i]));
		addr+=2;
	}
	write_ds(0x8e,0x80);
}
void read_ds_time(uchar addr)
{
	uchar i;
	write_ds(0x8e,0);
	for(i=0;i<7;i++)
	{
		timedata[i]=read_ds(addr);
		addr+=2;
	}
	write_ds(0x8e,0x80);
}
void show_time()
{
	display_char(7,0,'-');
	display_char(10,0,'-');
	display_char(13,0,'-');
	display_char(8,1,':');
	display_char(11,1,':');
	display_str(12,1,timedata[0]);
	display_str(9,1,timedata[1]);
	display_str(6,1,timedata[2]);
	display_str(14,0,timedata[3]);
	display_str(11,0,timedata[4]);
	display_str(8,0,timedata[5]);
	display_str(5,0,timedata[6]);
}	
void main()
{
	uchar test[]={"hello"};
	set_ds_time();
	DU=0;
	WE=0;
	init();
	lcdshow_str(0,0,"Date:");
	lcdshow_str(0,1,"Time:");
	while(1)
	{
		read_ds_time(0x81);
		show_time();
		delayms(1000);
	}
}