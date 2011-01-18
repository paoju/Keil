#include <reg52.h>
#define decode_mode 0X09 //����ģʽ��0xffȫ�����룬0x0f��ǰ�ĸ�
#define intensity 0x0a
#define scan_limit 0x0b//ɨ���޶ȣ�0x00-0x07
#define shut_down 0x0c//�ر�ģʽ��0x00Ϊ�ػ�,0x01Ϊ����
#define display_test 0x0f//��ʾģʽ

sbit load=P2^1;
sbit din=P2^0;//data in
sbit clk=P2^2;//clock

void write7219onechar(unsigned char temp)
{
	unsigned char i;
	for(i=0;i<8;i++)
	{
		clk=0;
		din=(bit)(temp&0x80);
		temp<<=1;
		clk=1;
	}
}

void write7219(unsigned char address,unsigned char dat)
{
	load=0;
	write7219onechar(address);
	write7219onechar(dat);
	load=1;
}


void init7219()
{
	write7219(shut_down,0x01);
	write7219(display_test,0x00);
	write7219(decode_mode,0xff);
	write7219(scan_limit,0x07);
	write7219(intensity,0x04);
}
