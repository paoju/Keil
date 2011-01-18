#include <reg52.h>
#include "declare.h"
sbit  DS1302_CLK = P2^0;              //ʵʱʱ��ʱ�������� 
sbit  DS1302_IO  = P2^1;              //ʵʱʱ������������ 
sbit  DS1302_RST = P2^2;              //ʵʱʱ�Ӹ�λ������
sbit  ACC0 = ACC^0;
sbit  ACC7 = ACC^7;
void delay(int);
void write7219twochar(unsigned char,unsigned char);
void write7219one(unsigned char,unsigned char);
unsigned char bcdconvert(unsigned char bcd)
{
	unsigned char target;
	target=bcd>>4;
	target=target*10+(bcd&=0x0f);
	return(target);
}
unsigned char convertbcd(unsigned char ten)
{
	unsigned char bcd,a,b;
	a=ten/10;
	b=ten%10;
	a=a<<4;
	bcd=(a&=0xf0)+(b&=0x0f);
	return(bcd);
}
void DS1302InputByte(unsigned char d) 	//ʵʱʱ��д��һ�ֽ�(�ڲ�����)
{ 
    unsigned char i;
    ACC = d;
    for(i=8; i>0; i--)
    {
        DS1302_IO = ACC0;           	//�൱�ڻ���е� RRC
        DS1302_CLK = 1;
        DS1302_CLK = 0;
        ACC = ACC >> 1; 
    } 
}
unsigned char DS1302OutputByte(void) 	//ʵʱʱ�Ӷ�ȡһ�ֽ�(�ڲ�����)
{ 
    unsigned char i;
    for(i=8; i>0; i--)
    {
        ACC = ACC >>1;         			//�൱�ڻ���е� RRC 
        ACC7 = DS1302_IO;
        DS1302_CLK = 1;
        DS1302_CLK = 0;
    } 
    return(ACC); 
}
void write_clock(unsigned char ucAddr, unsigned char ucDa)	//ucAddr: DS1302��ַ, ucData: Ҫд������
{
    DS1302_RST = 0;
    DS1302_CLK = 0;
    DS1302_RST = 1;
    DS1302InputByte(ucAddr);       	// ��ַ������ 
    DS1302InputByte(convertbcd(ucDa));       	// д1Byte����
    DS1302_CLK = 1;
    DS1302_RST = 0;
} 
unsigned char read_clock(unsigned char ucAddr)	//��ȡDS1302ĳ��ַ������
{
    unsigned char ucData;
    DS1302_RST = 0;
    DS1302_CLK = 0;
    DS1302_RST = 1;
    DS1302InputByte(ucAddr|0x01);        // ��ַ������ 
    ucData = DS1302OutputByte();         // ��1Byte����
    DS1302_CLK = 1;
    DS1302_RST = 0;
    return(bcdconvert(ucData));
	delay(5);
}
void init_ds1302()
{
	year=10; writeyear;
	month=3; writemonth;
	day=15; writeday;
	hour=17; writehour;
	minute=41; writeminute;
	second=55; writesecond;
}
void refreshtime()
{
	year=readyear; month=readmonth; day=readday;
	hour=readhour; minute=readminute; second=readsecond;
	write7219one(5,year/10); write7219one(6,year%10);
	write7219one(8,month/10); write7219one(1,month%10);
	write7219one(3,day/10);write7219one(4,day%10);
	write7219one(13,hour/10);write7219one(14,hour%10);
	write7219one(16,minute/10);write7219one(9,minute%10);
	write7219one(11,second/10);write7219one(12,second%10);
}