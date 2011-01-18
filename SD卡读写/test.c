#include <reg52.H>
sbit cs=P2^0;
sbit dati=P2^1;
sbit dato=P2^2;
sbit clk=P2^3;
unsigned char byte[8];
void delay()
{
 int c;
 for(c=0;c<10;c++)
 {;}
}
void select()//ѡƬ
{
 cs=0;
}
void deselect()//���Ƭѡ
{
 cs=1;
}
void send0()//���ͱ���0
{
 clk=0;
 delay();
 dati=0;
 delay();
 clk=1;
 delay();
}
void send1()//���ͱ���1
{
 clk=0;
 delay();
 dati=1;
 delay();
 clk=1;
 delay();
}
void sendbit(unsigned char num)//����һ�����ص�����
{
 if(num==1)
 send1();
 if(num==0)
 send0();
}
void sendbyte(unsigned char m)//���з���һ���ֽڵ�����
 {
  unsigned char bits[8];
  unsigned char  temp=m;
  int k;
  for(k=0;k<=7;k++)
  {
   bits[k]=temp%2;
   temp=temp/2;
  }
  for(k=7;k>=0;k--)
  sendbit(bits[k]);
 }
 ////////////////////////////////////////////////////////////////////////////////////////////////////////////
 void cmd(unsigned char index)//��������
 {
  unsigned char dits[8];
  unsigned char  temp=index;
  int k;
  for(k=0;k<=7;k++)
  {
   dits[k]=temp%2;
   temp=temp/2;
  }
  for(k=7;k>=0;k--)
  sendbit(dits[k]);
 }
void busclock()
{
 clk=1;
 delay();
 clk=0;
 delay();
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void main()
{
int a;
/********************************************************************************************************/
deselect();
dati=1;
for(a=0;a<=100;a++)
busclock();//74 pulses

select();//chip select

 sendbyte(0x40); 

 for(a=0;a<=31;a++)
 send0();//argument								//�˶γ���MMC���ɹ�Ӧ��0x01

 sendbyte(0x95);
 dati=1;
// sendbyte(0x34);
//  sendbyte(0x34);
 //sendbyte(a);

for(a=0;a<=31;a++)
busclock();
deselect();
/*****************************************************************************************************/
dati=1;
select();

 sendbyte(0x4a);

 for(a=0;a<=31;a++)
 send0();//argument
												//�˶γ���MMC���ɹ�Ӧ��CID��
 sendbyte(0xff);
 
 dati=1;

 for(a=0;a<=223;a++)
 busclock();
/*********************************************************************************************************/
/* cs=1;
 dati=1;
 cs=0;
 sendbyte(0x51);
  for(a=0;a<=31;a++)							//�˶γ���MMC���ɹ�����0x00000000��һ����������
 send0();//argument
 sendbyte(0xff);
  for(a=0;a<=4400;a++)
 busclock();*/
 /*********************************************************************************************************/
 cs=1;
 dati=1;
 cs=0;
 sendbyte(0x58);
 
 sendbyte(0x00);
  sendbyte(0x01);
   sendbyte(0x00);
    sendbyte(0x00);

 sendbyte(0xff);
 dati=1;
 while(dato==1)
 busclock();
 while(dato==0)
 busclock();

 sendbyte(0xfe);
 for(a=0;a<=513;a++)
 sendbyte(0x5a);
 
  while(1);
}
