
#include  "config.h"

#define rs (1<<8)
#define rw (1<<9)
#define en (1<<10)
#define busy (1<<7)

#define  TASK_STK_SIZE                  64
OS_STK        TaskStartStk[TASK_STK_SIZE];

void  TaskStart(void *data);
uint8 txt[]={"A LPC2124 Example!"};
/****************************************************************************
* ���ƣ�ChkBusy()
* ���ܣ���������Ƿ�æ
****************************************************************************/
void ChkBusy()
{
	PINSEL0=0xffc00000;
	IO0DIR=0x700;
	while(1)
	{
		IO0CLR=rs;
		IO0SET=rw;
		IO0SET=en;
		if(!(IO0PIN & busy))break;
		IO0CLR=en;
	}
	IO0DIR=0x7ff;
}
/****************************************************************************
* ���ƣ�WrOp()
* ���ܣ�д����
****************************************************************************/
void WrOp(uint8 dat)
{
	
	ChkBusy();
	IO0CLR=rs;		//ȫ������
	IO0CLR=rw;
	IO0CLR=0xff;		//������
	IO0SET=dat;		//������
	IO0SET=en;
	IO0CLR=en;
}
/****************************************************************************
* ���ƣ�WrDat()
* ���ܣ�д���ݺ���
****************************************************************************/
void WrDat(uint8 dat)	//������
{
   
	ChkBusy();
	IO0SET=rs;
	IO0CLR=rw;
	IO0CLR=0xff;		//������
	IO0SET=dat;		//������
	IO0SET=en;
	IO0CLR=en;
}

/****************************************************************************
* ���ƣ�DisText()
* ���ܣ���ʾ�ı�����
****************************************************************************/

void DisplayText(uint8 addr,uint8 *p)
{
	WrOp(addr);
	while(*p !='\0')WrDat(*(p++));
}
/****************************************************************************
* ���ƣ�main()
* ���ܣ���ʾ�ı�
****************************************************************************/

 int main (void)
{
    OSInit();

    OSTaskCreate(TaskStart, (void *)0, &TaskStartStk[TASK_STK_SIZE - 1], 3);
    OSStart();
    return 0;
}
/****************************************************************************
* ���ƣ�TaskStart()
* ���ܣ�����
****************************************************************************/

void  TaskStart(void *pdata)
{   pdata=pdata;
	TargetInit();
    WrOp(0x0c);
	IO0DIR=0x7ff;		//����Ϊ���
	IO0CLR=0x7ff;
	DisplayText(0x80,txt);
	while(1);
}
