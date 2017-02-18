//#include"LCD1602.h"

//sbit SCLK=P1^0;
//sbit IO=P1^1;
//sbit RST=P1^2;

//#define DS_W 0x80
//#define DS_R 0x81

//uchar timedata[7]={50,58,23,15,2,1,16};

////????
//void delayms(uint xms)
//{
//	uint i;
//	do{
//		i=11059200UL/96000;
//		while(--i);
//	}while(--xms);
//}
//void ds_w_byte(uchar dat)
//{
//	uchar i;
//	for(i=0;i<8;i++)
//	{
//		SCLK=0;
//		IO=dat&0x01;
//		SCLK=1;
//		dat>>=1;
//	}
//}
//uchar ds_r_byte()
//{
//	uchar i,dat;
//	for(i=0;i<8;i++)
//	{
//		SCLK=0;
//		dat>>=1;
//		if(IO)
//			dat|=0x80;
//		SCLK=1;
//	}
//	return dat;
//}
//void write_ds(uchar cmd,uchar dat)
//{
//	RST=0;
//	SCLK=0;
//	RST=1;
//	ds_w_byte(cmd);
//	ds_w_byte(dat);
//}
//uchar read_ds(uchar cmd)
//{
//	uchar dat;
//	RST=0;
//	SCLK=0;
//	RST=1;
//	ds_w_byte(cmd);
//	dat=ds_r_byte();
//	return dat;
//}
///* //DS??????
//void write_ds(uchar cmd,uchar dat)
//{
//	uchar i;
//	RST=0;
//	SCLK=0;
//	RST=1;
//	for(i=0;i<8;i++)
//	{
//		SCLK=0;
//		IO=cmd&0x01;
//		SCLK=1;
//		cmd>>=1;
//	}
//	for(i=0;i<8;i++)
//	{
//		SCLK=0;
//		IO=dat&0x01;
//		SCLK=1;
//		dat>>=1;
//	}
//}
////?DS??
//uchar read_ds(uchar cmd)
//{
//	uchar i,dat;
//	RST=0;
//	SCLK=0;
//	RST=1;
//	for(i=0;i<8;i++)
//	{
//		SCLK=0;
//		IO=cmd&0x01;
//		SCLK=1;
//		cmd>>=1;
//	}
//	for(i=0;i<8;i++)
//	{
//		SCLK=0;
//		dat>>=1;
//		if(IO)
//			dat|=0x80;
//		SCLK=1;
//	}
//	return dat;
//} */
////??DS???
//void ds_clear_wp()
//{
//	write_ds(0x8e,0x80);
//}
////?????
//void ds_set_wp()
//{
//	write_ds(0x8e,0x80);
//	RST=0;
//	SCLK=0;
//}
////????????
//void set_ds_time(uchar addr)
//{
//	uchar i,j;
//	ds_clear_wp();
//	for(i=0;i<7;i++)
//	{
//		j=timedata[i]/10;
//		timedata[i]%=10;
//		timedata[i]+=j*16;
//		write_ds(addr,timedata[i]);
//		addr+=2;
//	}
//	ds_set_wp();
//}
////??DS????,???????
//void read_ds_time(uchar addr)
//{
//	uchar i;
//	ds_clear_wp();    	
//	for(i = 0; i < 7; i++)	
//	{
//		timedata[i] = read_ds(addr);
//		addr += 2;						 
//	}
//	ds_set_wp();   //?????
//} 
//uchar bcd_dat(uchar dat)
//{
//	uchar dat1,dat2;
//	dat1=dat/16;
//	dat2=dat%16;
//	dat2=dat2+dat1*10;
//	return dat2;
//} 
//void main()
//{
//	lcdinit();
//	set_ds_time(DS_W);
//	LcdShowStr(0,0,"Data:");
//	LcdShowStr(0,1,"Time:");
//	while(1)
//	{
//		read_ds_time(DS_R);
//		timedata[6]=bcd_dat(read_ds(0x8d));
//		displayonestr(5,0,timedata[6]); //?
//		displayonechar (7,0,'-');		 //-
//		displayonestr (8,0,timedata[4]); //?
//		displayonechar (10,0,'-');		 //-
//		displayonestr (11,0,timedata[3]);//?
//		displayonechar (13,0,'-');		 //-
//		displayonestr (14,0,timedata[5]);//??

//		displayonestr (6,1,timedata[2]); //?
//		displayonechar (8,1,':');		 //:
//		displayonestr (9,1,timedata[1]); //?
//		displayonechar(11,1,':');		 //:
//		displayonestr (12,1,timedata[0]);//?
//		delayms(1000);				
//	}
//}

