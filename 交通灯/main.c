#include <reg52.h>
unsigned char code left[]={0x00,0x00,0x8f,0x9f,0xb0,0xe0,0xc0,0xfc};//ͼ����ʾ��ת
unsigned char code front[]={0x18,0x30,0x60,0xff,0xff,0x60,0x30,0x18};//ͼ����ʾǰ��
unsigned char code right[]={0xfc,0xc0,0xe0,0xb0,0x9f,0x8f,0x00,0x00};//ͼ����ʾ��ת
unsigned char code stop[]={0x3C,0x42,0xa5,0x99,0x99,0xa5,0x42,0x3C};//ͼ����ʾֹͣ
unsigned char i,buff,second1=10,second2=2,aa,written=0;
void write7219one(unsigned char,unsigned char,unsigned char,unsigned char,unsigned char,unsigned char);
void write7219two(unsigned char,unsigned char,unsigned char,unsigned char,unsigned char,unsigned char);
void write7219three(unsigned char,unsigned char);
void init7219();
void write_onechar(unsigned char);
void main()
{
	TMOD=0x01;
	TH0=(65536-50000)/256; 
	TL0=(65536-50000)%256;
	EA=1; //�����ж�
	ET0=1; //��ʱ��0����
	TR0=1; //��ʱ����ʼ����
	init7219();
	while(1)
	{
		if(buff==0&&written==0)
		{
			for(i=1;i<9;i++)
			{
				write7219one(i,stop[i-1],i,stop[i-1],i,right[i-1]);
				write7219two(i,left[i-1],i,front[i-1],i,right[i-1]);
			}
			written=1;
		}
		if(buff==2&&written==0)
		{
			for(i=1;i<9;i++)
			{
				write7219one(i,left[i-1],i,front[i-1],i,right[i-1]);
				write7219two(i,left[i-1],i,stop[i-1],i,stop[i-1]);
			}
			written=1;
		}
	}
}
void timer0() interrupt 1
{
	TH0=(65536-50000)/256;
	TL0=(65536-50000)%256;
	aa++;
	if(aa==20)
	{
		if(buff==0)
		{
			P0=0x41;
			write7219three(1,second1/10);
			write7219three(2,second1%10);
			write7219three(3,(second1-2)/10);
			write7219three(4,(second1-2)%10);
			second1--;
			if(second1==2)
			{
				buff=1;
				second1=10;
				written=0;
			}
		}
	
		else if(buff==1)
		{
			P0=0x21;
			write7219three(1,second2/10);
			write7219three(2,second2%10);
			write7219three(3,second2/10);
			write7219three(4,second2%10);
			second2--;
			if(second2==0)
			{
				buff=2;
				second2=2;
				written=0;
			}
		}

		else if(buff==2)
		{
			P0=0x14;
			write7219three(1,(second1-2)/10);
			write7219three(2,(second1-2)%10);
			write7219three(3,second1/10);
			write7219three(4,second1%10);
			second1--;
			if(second1==2)
			{
				buff=3;
				second1=10;
				written=0;
			}
		}

		else if(buff==3)
		{
			P0=0x12;
			write7219three(1,second2/10);
			write7219three(2,second2%10);
			write7219three(3,second2/10);
			write7219three(4,second2%10);
			second2--;
			if(second2==0)
			{
				buff=0;
				second2=2;
				written=0;
			}
		}
		aa=0;
	}
}
