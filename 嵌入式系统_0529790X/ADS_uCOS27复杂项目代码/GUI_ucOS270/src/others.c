#include "Includes.h"

//�ж���ʹ�õ�ȫ�ֱ���,������������Ҫʹ��ʱһ��Ҫ�����ٽ�����Ҳ���ǹر��жϣ���
//�����ʹ�ò���ϵͳ�Ļ�,��������ʹ�õ��������� 
//�����ȫ�ֱ����ĵط���Ҫ���ٽ���




#define TIME0_CLK_FRE	  195312	// time0ʱ��Ƶ��
#define TIME0_TCNTB       39062     // time0����ֵ
#define IR_DETECT_CTCLE     0.05		// time0�ж�����

#define U_WAVE_SPEED       340

#define WHEEL_LENGTH       1.5     
#define IR_WHEEL_NUMBER     9  
   
#define  IR_CONST     ( WHEEL_LENGTH / IR_WHEEL_NUMBER ) //���㹫ʽ�еĳ���//???????????

void printf_float(float value);
void cal_cpu_bus_clk(void);
static void EINT_ISR(void);



//����
volatile U32 ir_front_count = 0;//������������
volatile U32 ir_rear_count  = 0;

volatile float cur_speed_front = 0;//�ٶ�
volatile float cur_speed_rear = 0;


//������
volatile U32 u_wave_send_time = 0;	 //��¼����ʱTimer0��ʱ��
volatile U32 u_wave_receive_times = 0;//��¼����ʱTimer0��ʱ��
U32 u_wave_receive_time2 = 0;
U32 u_wave_receive_time3 = 0;

volatile float u_wave_length1 = 0; //�߶�
volatile float u_wave_length2 = 0;
volatile float u_wave_length3 = 0;
volatile float weightst  = 400.000;

volatile float temperature = 32.5;
volatile float kt_temperature = 37;

volatile float weight  = 200;


volatile float hightest_speed = 0;
volatile float ave_speed = 0;

volatile int count_pingtan = 0;
volatile int count_nining = 0;
volatile int count_kanke = 0;


volatile float hightest_speed_pingtan = 120;
volatile float hightest_speed_ningling = 75;
volatile float hightest_speed_kanke = 60;

volatile float height  = 27;
 U16 height_pingtan;
 U16 height_ningling ;
 U16 height_kanke ;

volatile  int ir_cur_time,ir_pre_time;

volatile float steady = 0;
volatile int steady_count;

  #if OS_CRITICAL_METHOD == 3 					 /* Allocate storage for CPU status register		   */
    static OS_CPU_SR  cpu_sr = 0;
  #endif


//�������˵�λ��
MenuTouchPos stateTouchPos[11] = 
{
	{513,136,443,351},
	{513,389,443,606},
	{513,633,443,867},
		
	{425,139,364,351},
	{425,386,364,602},
	{425,640,364,863},
		
	{333,136,265,366},
	{333,394,265,603},
	{333,646,265,873},

	{242,139,153,484},
	{242,523,153,865}
	
} ;



//�������˵�ƥ��
S8 match_state_menu(PtTouchPos pt_pos)
{
	S8 i;
	for(i=0;i<11;i++)
	{
		if((pt_pos->TouchX < stateTouchPos[i].TouchX1)&&(pt_pos->TouchX > stateTouchPos[i].TouchX2) && (pt_pos->TouchY > stateTouchPos[i].TouchY1)&&(pt_pos->TouchY < stateTouchPos[i].TouchY2))
	  	{
			return i;
		}
	}
	return -1;
}


//��ʼ��������
void ultrasonic_wave_check_init()
{	//EINT 4
	rGPFCON &= ~(0x3<<8);//clear
	rGPFCON |=  (0x0<<8);//input
	
	rGPFUP &= ~(0x1<<4);//pull up
	
}


//�ⲿ�жϳ�ʼ��
void EINT_init()
{
    // set EINT8,11,13,14,15,19
	rGPGCON &= ~((0x3<<22)|(0x3<<6)|(0x3<<0)|(0x3<<10)|(0x3<<12)|(0x3<<14)|(0x3<<18));
	rGPGCON |=   (0x2<<22)|(0x2<<6)|(0x2<<0)|(0x2<<10)|(0x2<<12)|(0x2<<14)|(0x2<<18);
    // set EINT0,2
	rGPFCON = rGPFCON & (~((0x3<<4)|(0x3<<0))) | ((0x2<<4)|(0x2<<0)) ;		
	
	
	//set eint0,2 falling edge int
	rEXTINT0 &= ~((0x7<<0)|(0x7<<8));	//clear
	rEXTINT0 |=  ((0x3<<0)|(0x3<<8));	
	
	//set EINT8,11,13,14,15 falling edge int
	rEXTINT1 &= ~((0x7<<12)|(0x7<<0)|(0x7<<20)|(0x7<<24)|(0x7<<28));//clear
	rEXTINT1 |=   (0x02<<12)|(0x02<<0)|(0x02<<20)|(0x02<<24)|(0x02<<28);
	
	rEXTINT2 &= ~(0x7<<4);
	rEXTINT2 |=  (0x02<<4);
	
	//set eint19 falling edge int
	rEXTINT2 &= ~(0x7<<12); //clear
	rEXTINT2 |=  (0x3<<12);	


	rEINTPEND |= (1<<11)|(1<<19)|(1<<8)|(1<<13)|(1<<14)|(1<<15)|(1<<17);		//clear eint 8,11,13,14,15,19
	rEINTMASK &= ~((1<<8)|(1<<15));//ʹ�ܺ����ⲿ�ж�
	ClearPending(BIT_EINT0|BIT_EINT2|BIT_EINT8_23);

	pISR_EINT8_23 = (U32)EINT_ISR;
	EnableIrq(BIT_EINT8_23);
}


//�ⲿ�жϷ�����
static void EINT_ISR(void)
{
	U32 r;
	static U16 count = 0;
	EnterCritical(&r);
	
	//EINT8_23 
	if(rINTPND==BIT_EINT8_23) 
	{
	
		//eint8  �����
		if(rEINTPEND&(1<<8)) 
		{	 
		    ir_cur_time = rTCNTO0; 
		    
		    if(ir_cur_time < ir_pre_time )//ȥ��
		    {
		    	if(ir_pre_time - ir_cur_time > 50) 
		    	{
		    		OS_ENTER_CRITICAL();
		    		ir_rear_count ++;
		    		OS_EXIT_CRITICAL();
		    	}
		    }
		    
		    else
		    {
		    	if(TIME0_TCNTB - ir_cur_time + ir_pre_time > 50)//ȥ��
		    	{
		    		OS_ENTER_CRITICAL();
		    		ir_rear_count ++;
		    		OS_EXIT_CRITICAL();

		    	}
		    }    
		    ir_pre_time = ir_cur_time;
			rEINTPEND |= 1<< 8;
		}

		//eint11 ǰ����   & ����
		 if(rEINTPEND&(1<<15)) 
		 {
			OS_ENTER_CRITICAL();
			ir_front_count ++;
			OS_EXIT_CRITICAL();
			
			Uart_Printf("\n ir_front_count %d",ir_front_count);
			   
			rEINTPEND |= 1<< 15;	 
		 }

		ClearPending(BIT_EINT8_23);

	}

	ExitCritical(&r);
	
}


#define MY_ABS(Number)    (((Number) < 0)?(-(Number)):(Number)) //ȡ����ֵ
#define MAX(a,b)  (((a) > (b)) ? (a) : (b))

extern U8 dis_rev;
extern U16 height_pingtan;
extern U16 height_ningling ;
extern U16 height_kanke ;

//����0.2���Ӵ���һ���ж�
void Timer0_Handle(void)
{
	static U8 i,j;
	static float k;
	static float speed_add = 0;
	float temp;
	
	i ++;
	j ++;
	
	//�������
	if(i == 10 )//1�����һ��
	//if(i == 20 ) //1�����һ��
	{    
	  i = 0; 
	 
	OS_ENTER_CRITICAL();
	//�˲� 

	temp =   ((float)ir_front_count) * IR_CONST * 3.6;
	if(temp < 50) cur_speed_front = temp;
	  
	temp =   ((float)ir_rear_count ) * IR_CONST * 3.6;
	if(temp < 50) cur_speed_rear = temp;
    hightest_speed = MAX(cur_speed_rear, hightest_speed);//����ٶ�
    
    
    if(0 != cur_speed_rear)
    {
    	k ++;
    	speed_add = speed_add + cur_speed_rear;
		ave_speed = (float)(speed_add / k);	     //ƽ���ٶ�
	}
	
	temp = cur_speed_front - cur_speed_rear;
	
	
	//if( MY_ABS(temp) > 3 )
	if( temp >= hightest_speed_pingtan )//2
	{

		 if( temp >=hightest_speed_ningling )//7
			{
			 		//����
			 	dis_rev = 1;
			}

		    else if(cur_speed_front >= 18)
			{
				   //��
				
				dis_rev = 2;
			}
	}
	ir_front_count = 0;
	ir_rear_count  = 0;
	OS_EXIT_CRITICAL();
    }


   //���������
	if( !(rGPFDAT & (0x01<<4)) ){ u_wave_receive_times ++; }
	
		if( height_pingtan == j  )
	{

		if( u_wave_receive_times >= height_ningling)		
		{
			if((cur_speed_rear >= 5)&&((cur_speed_rear <= 10)))
			{
				if(0 != cur_speed_rear)count_kanke ++;
				dis_rev = 4;//����
			}
			else if((cur_speed_rear >= 11)&&((cur_speed_rear <= 15)))
			{
				if(0 != cur_speed_rear)count_nining ++;
				dis_rev = 3;//��Ţ
			}
		}
		else
		{
			dis_rev = 0;//ƽ̹
			if(0 != cur_speed_rear)count_pingtan ++;
		}

		j = 0;
		steady_count = u_wave_receive_times;
		u_wave_receive_times = 0;
	}	
	
    rSRCPND = 1 << rINTOFFSET;
    rINTPND = rINTPND;     
}



/*
 * Timer input clock Frequency = PCLK / {prescaler value+1} / {divider value}
 * {prescaler value} = 0~255
 * {divider value} = 2, 4, 8, 16
 * ��ʵ���Timer0��ʱ��Ƶ��=50MHz/(15+1)/(16)=195312.5Hz(һ���������)
 * ����Timer0  0.2���Ӵ���һ���жϣ�
 */
void ir_timer_init(void)
{
	
	rTCFG0 = rTCFG0 & (~0xff) | 15;	   //prescaler = 15+1
    rTCFG1 = rTCFG1 & (~0x0f) | (0x03);  // ѡ��16��Ƶ
	rTCNTB0 = 19531;
    rTCON   |= (1<<1);   // �ֶ�����
    pISR_TIMER0 = (int)Timer0_Handle;
    rINTMSK   &= (~BIT_TIMER0);// ��ʱ��0�ж�ʹ��
    rTCON   = rTCON & (~0x0f) | 0x09;      // �Զ����أ��塰�ֶ����¡�λ��������ʱ��0
    										//Timer 0 manual update bit has to be cleared at next writing.
}


//����Ƶ��40k�ķ���
void Timer1_Handle(void)
{
    rSRCPND = 1 << rINTOFFSET;
    rINTPND = rINTPND;        
}


//��ʼ��TOUT1
void ultrasonic_wave_pwm_out()
{

     
    rGPBCON = rGPBCON & (~(0x3<<2)) | (0x2<<2) ;		//GPB1����ΪTOUT1
    rTCON = rTCON & (~(0xf<<8)) ;			// clear manual update bit, stop Timer1
    
    rTCFG0 &= ~(0xff);
	rTCFG0 |= 15;			//set Timer 0/1 prescaler = 15+1
	rTCFG1 &= ~(0xf<<4);
	rTCFG1 |= 0<<4;		// set Timer 2 MUX 1/2

  // ����ֵ = PCLK / {prescaler value+1} / {divider value} / (f/2) 
	rTCNTB1 = 42;	//if set inverter off, when TCNT2<=TCMP2, TOUT is high, TCNT2>TCMP2, TOUT is low
	rTCMPB1 = 21 ;	//ռ�ձ�1:1
	
	
    pISR_TIMER1 = (int)Timer1_Handle;
    rINTMSK    &= (~BIT_TIMER1);// ��ʱ��1�ж�ʹ��  

	rTCON = rTCON & (~(0xf<<8)) | (0x0e<<8) ;
	//�Զ���װ,���ȡ���ر�,����TCNTBn��TCMPBn,�����������ر�
	
	rTCON &= ~(0x01 << 9);	//Timer 1 manual update bit has to be cleared at next writing.
	rTCON |= 0x01 << 8;	    //����
	
	u_wave_send_time = rTCNTO0; //��¼����ʱTimer0��ʱ��
}



extern const GUI_BITMAP bmmain_pic ;
extern const GUI_BITMAP bmbaosi;
extern const GUI_BITMAP bmmain_pic;
extern const GUI_BITMAP bmdahua;
extern const GUI_BITMAP bmkanke;
extern const GUI_BITMAP bmnining;
extern U8 wave_going;
extern volatile U8 dahua_on ;
extern volatile U8 baosi_on ;
extern volatile U8 kanke_on ;
extern volatile U8 nining_on ;


//��������
		void alarm()
		{
			
			U8 i,j;

			//����
			wave_going = 1;
			//LCD��ʾ
			if(baosi_on)
			while(1 == dis_rev) //����
			{
				
			 for(j = 0; j <= 3 ;j++)
			  {
				GUI_DrawBitmap(&bmbaosi,0,0);
				for(i = 0;i < 100; i++)
				{
					OSTimeDly(1);
				}	
				GUI_SetBkColor(GUI_RED);
				GUI_Clear();
				GUI_SetBkColor(GUI_RED);
				for(i = 0;i < 50; i++)
				{
					OSTimeDly(1);
				}	
				GUI_Clear();
				
			  }
			}
			
			if(dahua_on)
			while(2 == dis_rev) //��
			{
				
			  for(j = 0; j <= 3 ;j++)
			  {
				GUI_DrawBitmap(&bmdahua,0,0);
				for(i = 0;i < 100; i++)
				{
					OSTimeDly(1);
				}	
				GUI_SetBkColor(GUI_RED);
				GUI_Clear();
				GUI_SetBkColor(GUI_RED);
				for(i = 0;i < 50; i++)
				{
					OSTimeDly(1);
				}	
				GUI_Clear();
				}
			}
			
			if(nining_on)
			while(3 == dis_rev) //��Ţ·
			{
				
			  for(j = 0; j <= 3 ;j++)
			  {
				GUI_DrawBitmap(&bmnining,0,0);
				for(i = 0;i < 100; i++)
				{
					OSTimeDly(1);
				}	
				GUI_SetBkColor(GUI_RED);
				GUI_Clear();
				GUI_SetBkColor(GUI_RED);
				for(i = 0;i < 50; i++)
				{
					OSTimeDly(1);
				}	
				GUI_Clear();
				
				}
			}
			
			if(kanke_on)
			while(4 == dis_rev) //����·
			{
				
			  for(j = 0; j <= 3 ;j++)
			  {
				GUI_DrawBitmap(&bmkanke,0,0);
				for(i = 0;i < 100; i++)
				{
					OSTimeDly(1);
				}	
				GUI_SetBkColor(GUI_RED);
				GUI_Clear();
				GUI_SetBkColor(GUI_RED);
				for(i = 0;i < 50; i++)
				{
					OSTimeDly(1);
				}	
				GUI_Clear();
				}
			}
		}

