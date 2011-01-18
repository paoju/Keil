#include<reg52.h>
#define uchar unsigned char
#define uint unsigned int 
sbit ce=P2^7;
sbit rw=P3^6;
sbit rd=P3^7;
sbit cd=P2^6;
sbit rst=P2^5;
uint address;
uchar data1,data2,cmd;
void clear();
void delay(uint z)
{
	uint i,j;
	for(i=z;i>0;i--)
		for(j=110;j>0;j--);
}
//void delayus(uint z)
//{
//	while(z--);
//}
void writedata(uchar dat)           //д����    
{    ce=1;
     cd=0;
    rw=0;
     P0=dat; 
 //  delayus(10);

	ce=0;
     rw=1;
}   
void writecommand(uchar cmd)           //д����    
{   ce=1;
     cd=1;
     rw=0;
     P0=cmd;
//delayus(10);
	ce=0;
     rw=1;
} 
/*void writedc(uchar dat,uchar cmd)      //дһ�����ݺ�һ��ָ�� 
{   
     writedata(dat);   
     writecommand(cmd);   
} */
void writeddc(uchar data1, uchar data2, uchar cmd)   //д�������ݺ�һ��ָ�� 
{   
     writedata(data1);         
     writedata(data2);   
     writecommand(cmd);     
}   
void LCD_Init(void)         //Һ����ʼ�� 
{   
     uchar data1,data2,cmd;    
   		rw=1;
		rst=0;
	delay(5);
	rst=1;
	rd=1;  
        
     
     data1 = 0x00;   
     data2 = 0x10;              //ͼ����ʾռ��32*128=0xfff�����ı���0x1000��ʼ
     cmd = 0x40;                //�����ı���ʾ���׵�ַ    
     writeddc(data1,data2,cmd);   
     data1 = 0x20;              //����������ʾ
     data2 = 0x00;   
     cmd = 0x41;                //�����ı���ʾ�����    
     writeddc(data1,data2,cmd);   
     data1 = 0x00;   
     data2 = 0x00;   
     cmd = 0x42;                //����ͼ����ʾ���׵�ַ    
     writeddc(data1,data2,cmd);   
     data1 = 0x1e;   
     data2 = 0x00;   
     cmd = 0x43;                //����ͼ����ʾ�����    
     writeddc(data1,data2,cmd); 
   cmd =0xa2;                 //���ù����״ 
   writecommand(cmd); 
     cmd = 0x80;                //��ʾ��ʽ����
                              //�����ⲿ�ַ�������,��ʾ��ʽ���ı���ͼ���� 
     writecommand(cmd); 
     cmd = 0x9e;                //���ù����˸,��겻��ʾ,�ı���ʾ��ͼ����ʾ    
     writecommand(cmd);   
}



/*void writeonechinese(uchar *codes)
{
	uchar i=0,j=0;
	for(i=0;i<32;i++)
	{
		writedata(codes[i]);
		j++;
		if(j==2)
		{
			writecommand(0xb2);           //�˳��Զ�дģʽ
		    address=address+30;
		    data1 = address;                 //ȡ��ַ�Ͱ�λ    
		    data2 = address>>8;                //ȡ��ַ�߰�λ    
		    cmd = 0x24; 
		    writeddc(data1,data2,cmd);
		    j=0;
		    writecommand(0xb0);         //�����Զ�дģʽ		
		}
	}
}*/
void clearlcd()
{
	uint i;
	writecommand(0xb2);
	data1 = 0x00;                 //ȡ��ַ�Ͱ�λ    
	data2 = 0x00;                //ȡ��ַ�߰�λ    
	cmd = 0x24; 
	writeddc(data1,data2,cmd);
	writecommand(0xb0);//�Զ�дģʽ
	for(i=0;i<5000;i++)
	{
		writedata(0x00);
	}
		writecommand(0xb2);
}
