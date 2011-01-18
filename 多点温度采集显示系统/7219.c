#include <reg52.h>
#define decode_mode 0x09 //����ģʽ��0xffȫ�����룬0x0f��ǰ�ĸ�
#define intensity 0x0a
#define scan_limit 0x0b//ɨ���޶ȣ�0x00-0x07
#define shut_down 0x0c//�ر�ģʽ��0x00Ϊ�ػ�,0x01Ϊ����
#define display_test 0x0f//��ʾģʽ
sbit load=P2^1;//load
sbit din=P2^0;//data in
sbit clk=P2^2;//clock
//��7219дһ���ֽ�
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
//��7219д�������
void write7219(unsigned char address,unsigned char dat)
{
	load=0;
	write7219onechar(address);
	write7219onechar(dat);
	load=1;
}
//7219��ʼ��
void init7219()
{
	unsigned char i;
	write7219(shut_down,0x01);
	write7219(display_test,0x00);
	write7219(decode_mode,0x7a);//��1��3��8λ������
	write7219(scan_limit,0x07);
	write7219(intensity,0x04);
	for(i=0;i<8;i++)
		write7219(i+1,15);
}
