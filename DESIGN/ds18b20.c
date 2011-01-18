#include<reg52.h>
#include<stdio.h>
#define uint unsigned int
#define uchar unsigned char
#define decode_mode 0X09
sbit DQ =P1^6;   //����ͨ�Ŷ˿�
unsigned char A1,A2,A3,A2t,dispno;
unsigned int temp1;
//unsigned char code table[]={0x7e,0x30,0x6d,0x79,0x33,0x5b,0x5f,0x70,0x7f,0x7b,0x31,0x01};
//unsigned char code point[]={0xfe,0xb0,0xed,0xf9,0xb3,0xdb,0xdf,0xf0,0xff,0xfb};
int num1=0,d=0,fu;
void delay(int z);
void write7219two(unsigned char,unsigned char);
void delayus(unsigned int i)
{
	 while(i--);
}
Init_DS18B20(void)
{
	// unsigned char x=0;
	 DQ = 1;    //DQ��λ
	 delayus(8);  //������ʱ
	 DQ = 0;    //��Ƭ����DQ����
	 delayus(80); //��ȷ��ʱ ���� 480us
	 DQ = 1;    //��������
	 delayus(14);
//	 x=DQ;      //������ʱ�� ���x=0���ʼ���ɹ� x=1���ʼ��ʧ��
	 delayus(20);
}
ReadOneChar(void)
{
unsigned char i=0;
unsigned char dat = 0;
for (i=8;i>0;i--)
 {
	  DQ = 0; // �������ź�
	  dat>>=1;
	  DQ = 1; // �������ź�
	  if(DQ)
	   dat|=0x80;
	  delayus(4);
 }
 return(dat);
}
//дһ���ֽ�
WriteOneChar(unsigned char dat)
{
 unsigned char i=0;
 for (i=8; i>0; i--)
 {
  DQ = 0;
  DQ = dat&0x01;
  delayus(5);
  DQ = 1;
  dat>>=1;
 }
delayus(4);
}
//��ȡ�¶�
unsigned int readtemp()
{
	unsigned char a=0;
	unsigned char b=0;
	unsigned int t=0;
	float tt=0;
	Init_DS18B20();
	WriteOneChar(0xCC); // ����������кŵĲ���
	WriteOneChar(0x44); // �����¶�ת��
	Init_DS18B20();
	WriteOneChar(0xCC); //����������кŵĲ���
	WriteOneChar(0xBE); //��ȡ�¶ȼĴ����ȣ����ɶ�9���Ĵ����� ǰ���������¶�
	a=ReadOneChar();
	b=ReadOneChar();
	t=b;
	if(t<8)
	{
		fu=0;
		t<<=8;
		t=t|a;
	}
	else
	{
		fu=1;
		t<<=8;
    		  t=t|a;
		t=~t;
		t=t+1;
	}
	tt=t*0.0625;
	t= tt*10 ;//�Ŵ�10���������������---����û��
	return(t);
}
void display18b20()
{
	int bai,shi,ge;
   num1=readtemp();
	if(d!=num1)
	{
		d=num1;
		bai=num1/100;shi=num1/10%10;ge=num1%10;
		if(fu==1)
		{
			if(bai<2)
			{
				if(bai==0)
				{
					write7219two(decode_mode,0xff);
					write7219two(6,0x0a);
				}
				if(bai==1)
				{
					write7219two(decode_mode,0xdf);
					write7219two(6,0x31);
				}
				write7219two(7,shi|0x80);
				write7219two(8,ge);
			}
			else
			{
				write7219two(decode_mode,0xff);
				write7219two(6,0x0a);
				write7219two(7,bai);
				write7219two(8,shi);
			}
		}
		if(fu==0)
		{
			if(bai==0)
			{
				write7219two(decode_mode,0xff);
				write7219two(6,0x0f);
			}
			else
			{
			write7219two(decode_mode,0xff);
			write7219two(6,bai);
			}
			write7219two(7,shi|0x80);
			write7219two(8,ge);
			d=num1;
		}
	} 
}