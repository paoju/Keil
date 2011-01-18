#include <reg52.h>
sbit DQ =P3^5;   //����ͨ�Ŷ˿�
unsigned char A1,A2,A3,A2t,dispno;
unsigned int temp1;
void delayus(unsigned int i)
{
	 while(i--);
}
Init_DS18B20(void)
{
	 unsigned char x=0;
	 DQ = 1;    //DQ��λ
	 delayus(8);  //������ʱ
	 DQ = 0;    //��Ƭ����DQ����
	 delayus(80); //��ȷ��ʱ ���� 480us
	 DQ = 1;    //��������
	 delayus(14);
	 x=DQ;      //������ʱ�� ���x=0���ʼ���ɹ� x=1���ʼ��ʧ��
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
unsigned int readtemp(void)
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
	t<<=8;
	t=t|a;
	tt=t*0.0625;
	t= tt*10+0.5; //�Ŵ�10���������������---����û��
	return(t);
}