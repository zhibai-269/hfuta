/****************************************************************************************
* ���ܣ�  �����ۺϼ���ǵĲ���ϵͳ�������ʵ��
* ���ߣ�  ����ΰ
* ���ڣ�  2008.09.05
* �� ���� 1.0
* ��ע��  

      ������Ϣ��ʾ������������LCD��ʾ����������Ӧ��Щʵʱ��Ҫ�󲻸ߵ�
      �ֱ����ڵ����������д�����ʵʱ�Ըߵĺ���ͳ��������������
      �ж��н��У�ͨ��ȫ�ֱ������ź�����ͨ�Ż��ƻ�����ϵ

****************************************************************************************/


#include "Includes.h"
#include "DIALOG.h"//GUI

/*
*********************************************************************************************************
*                                           �ⲿ����
*********************************************************************************************************
*/
extern int consoleNum;
extern const GUI_BITMAP bmmain_pic ;
extern const GUI_BITMAP bmbaosi;
extern const GUI_BITMAP bmmain_pic;
extern const GUI_BITMAP bmdahua;
extern const GUI_BITMAP bmkanke;
extern const GUI_BITMAP bmnining;
extern volatile float hightest_speed;
extern volatile float ave_speed;
extern volatile int xdata, ydata;
volatile extern TouchPos TouchXY;
extern volatile float steady;


/*
*********************************************************************************************************
*                                           ȫ�ֱ���
*********************************************************************************************************
*/
volatile U8 i_menu = 0;
volatile U8 dis_rev =0;
volatile U8 alarm_on = 0;
volatile U8 speed_front_on = 0;
volatile U8 dahua_on = 1;
volatile U8 baosi_on = 1;
volatile U8 kanke_on = 1;
volatile U8 nining_on = 1;
U8 wave_going = 0;
U8 clear = 0;

  #if OS_CRITICAL_METHOD == 3 					 /* Allocate storage for CPU status register		   */
    static OS_CPU_SR  cpu_sr = 0;
  #endif

/*
*********************************************************************************************************
*                                            ����ԭ��         
*********************************************************************************************************
*/
void PlayMusic(unsigned char *wave_arr, int len);
void DemoScale(float tDiff);
void DemoProgBar(float value) ;




/*
*********************************************************************************************
*                                       WDTInterrupt
*   ʱ�ӽ����жϷ�����
*********************************************************************************************
*/
static void WDTInterrupt()
{
	
        rSRCPND |= BIT_WDT_AC97;                  // Clear pending bit -- Watchdog timer
        rINTPND |= BIT_WDT_AC97;
		rSUBSRCPND |= BIT_SUB_WDT;     
        OSTimeTick();
}



/*
*********************************************************************************************
*                                       StartTicker
*	���ò�����ϵͳ����(����Ŀ�ÿ��Ź��ж�)
*********************************************************************************************
*/
void StartTicker(U32 wTicksPerSec)
{

#if OS_CRITICAL_METHOD == 3                         /* Allocate storage for CPU status register           */
        OS_CPU_SR  cpu_sr;
#endif

        OS_ENTER_CRITICAL();

        rWTCON = 0;                                 // Disable watchdog

        pISR_WDT_AC97 = (U32)WDTInterrupt;

        rWTDAT = rWTCNT = PCLK / 16 / wTicksPerSec; //set up the WDT for wTicksPerSec

        rWTCON = (0<<8)|(1<<5)|(0<<3)|(1<<2)|(0<<0);// Enable: WD, WD interrupts, prescaler value=0+1, divider value=16 
        
		BIT_CLR(rINTMSK, BIT_WDT_AC97);               // Enable WatchDog interrupts
        BIT_CLR(rINTSUBMSK, BIT_SUB_WDT);               // Enable WatchDog interrupts
        OS_EXIT_CRITICAL();
}

/*
*********************************************************************************************
*                                       ARMTargetInit
* ��ʼ��Ŀ���
*
*********************************************************************************************
*/

void ARMTargetInit() 				
{
	Port_Init();
	Isr_Init();

    consoleNum = 0;	// Uart 1 select for debug.
	Uart_Init( 0,115200 );
	Uart_Select( consoleNum );
		
    pISR_IRQ = (U32)UCOS_IRQHandler;       

}

/*
*********************************************************************************************
*                                       ARMTargetInit
* ����Ŀ���
*
*********************************************************************************************
*/

void ARMTargetStart() 				//�����ж���������������ϵͳ��Ӳ����ʱ���ж�
{

   StartTicker(OS_TICKS_PER_SEC);
   
}
     


		void check_return_to_main_menu()
		{

			if(0!=TouchXY.TouchX) //�������˵�
			{
			
				//GUI_Clear();
				TouchXY.TouchX = TouchXY.TouchY = 0;
				i_menu = 0;
			}
		}


/****************************************************************************************
* ���ܣ�  UCOS ������
* ���ߣ�  ����ΰ
* ���ڣ�  2008.08.05
* �� ���� 1.0
* ��ע��  
****************************************************************************************/

///******************����ջ��С����***************///

#define	TASK_STACK_SIZE	256


///******************������***************///

void Main_Task		(void *pdata);                 //���ȼ�������Ϊ���
void Task1			(void *pdata);
void Task2			(void *pdata);
void GUI_Task		(void *pdata);
//void Touch_Task		(void *pdata);


///******************�����ջ***************///

OS_STK Main_Stack [TASK_STACK_SIZE]				= {0, };
OS_STK Task1_Stack[TASK_STACK_SIZE]				= {0, };
OS_STK Task2_Stack[TASK_STACK_SIZE]			    = {0, };
OS_STK GUI_Task_Stack[TASK_STACK_SIZE]		    = {0, };
//OS_STK Touch_Task_Stack[TASK_STACK_SIZE]	    = {0, };



///**************�Ѿ������OS����*************///

#define Main_PRIO    				 1
#define Task1_PRIO    			     3
#define Task2_PRIO        	 	     5
#define GUI_Task_PRIO        	 	 15
//#define Touch_Task_PRIO        	 	 15


///*****************�¼�����*****************///

//�����ź���
OS_EVENT *Sem1; 			 //

extern volatile float cur_speed_front;
extern volatile U32 u_wave_receive_times;


/*******************************************************************
*
*        						 Main_Task
*	�����������񲢸����ٶȵ�ʵʱ��ʾ
* 
*********************************************************************/

void Main_Task(void *pdata)
{   
	int i=0;
 	pdata = pdata;

    ARMTargetStart();  				//�����ж���������������ϵͳ��Ӳ����ʱ���ж� 

     GUI_Init()
     WM_SetCreateFlags(WM_CF_MEMDEV);  /* Use memory devices on all windows to avoid flicker */

    //����ϵͳ������ 
    OSTaskCreate(Task1,(void *)0,&Task1_Stack[TASK_STACK_SIZE - 1],Task1_PRIO); 	 					  
    OSTaskCreate(Task2,(void *)0,&Task2_Stack[TASK_STACK_SIZE - 1],Task2_PRIO); 
    OSTaskCreate(GUI_Task,(void *)0,&GUI_Task_Stack[TASK_STACK_SIZE - 1],GUI_Task_PRIO); 
  
    ir_timer_init();
    EINT_init();
	ultrasonic_wave_check_init();
    ultrasonic_wave_pwm_out();
    
	GUI_SetFont(&GUI_FontD24x32);
  while(1) 
  {
    if((1 == i_menu)&&(0 == dis_rev))
    { 	
    
    	    GUI_SetFont(&GUI_FontD24x32);
    		GUI_SetColor(GUI_BLUE);
    		GUI_DispDecAt((I32)cur_speed_rear, 100, 170 ,3);
    		
    		if(speed_front_on)//ǰ���ٶ�
    		GUI_DispDecAt((I32)cur_speed_front, 100, 3 ,3);
       }
    
    if(5 == i_menu)
    {
        GUI_SetFont(&GUI_FontD24x32);
        GUI_SetColor(GUI_YELLOW);
        
    	GUI_DispDecAt((U32)hightest_speed, 100, 140 ,3);
    	GUI_DispDecAt((U32)ave_speed, 100, 190 ,3);
    	
    	if(steady > 50)GUI_SetColor(GUI_GREEN);
  	    else GUI_SetColor(GUI_RED);
    	GUI_DispDecAt((U32)steady, 120, 240 ,2);
    
    }
    
     if(6 == i_menu)
    {
     if(3 == dis_rev)//��Ţ·
   	 {
     	GUI_SetColor(GUI_WHITE); 
     	GUI_SetFont(& GUI_FontHZ16);
     	GUI_DispStringAt("��Ţ", 100, 40);
     }
     
     if(4 == dis_rev) //����·
   {
     GUI_SetColor(GUI_WHITE); 
     GUI_SetFont(& GUI_FontHZ16);
     GUI_DispStringAt("����", 100, 40);
   }
   
     if((3 != dis_rev)&&(4 != dis_rev))//ƽ̹·
   	 {
     	GUI_SetColor(GUI_WHITE); 
     	GUI_SetFont(& GUI_FontHZ16);
     	GUI_DispStringAt("ƽ̹", 100, 40);
     }
    
   }// if(6 == i_menu) 
     OSTimeDly(50);
  } 
}


extern volatile int  cou5nt_pingtan ;
extern volatile int  count_nining ;
extern volatile int  count_kanke ;


/*
*********************************************************************************************
*                                      Task1
* ��������
*
*********************************************************************************************
*/

void Task1(void *pdata)						
{	
    //int i;
   
   /*    for(i = 0;i <= 5;i ++)
    {
    	WaveOut(i);
    }
	*/
    pdata = pdata;
    
    for (;;)
    {

		
		OSTimeDly(400);
    }
}


/*
*********************************************************************************************
*                                      Task2
* �����������
*
*********************************************************************************************
*/


void Task2(void *pdata)						
{
    
    pdata = pdata;
    
    WaveOut(0);
    OSTimeDly(950);
    
    for (;;)
    {	
    
		if(wave_going)
		{
			WaveOut(dis_rev);
			wave_going = 0;
		}
		OSTimeDly(10);
    }
}


/* USE Int
void Touch_Task(void *pdata)						
{

	 pdata = pdata;
	  for (;;)
	  {
	  GUI_TOUCH_Exec();
	  OSTimeDly(1);
	  }
}
*/

extern volatile int steady_count;

/*******************************************************************
*
*          GUI background processing
*
* ����LCD��ʾ����������Ӧ
*********************************************************************/

void GUI_Task(void *pdata) {

  
  S8 num;
  pdata = pdata;
  while(1) 
  {
  
    if(0 == i_menu)	//���˵�
    	
    {
    	GUI_DrawBitmap(&bmmain_pic,0,0);
    	i_menu = match_state_menu(&TouchXY) + 1;
    	TouchXY.TouchX = TouchXY.TouchY = 0;
    	
    	if(0 != i_menu)
    	{
    		if((1 == i_menu)||(5 == i_menu)||(6 == i_menu))//�ٶ�,��־,·�� ������
    			{
    				GUI_Clear();
    			}
    	}
    }
    	 
    switch (i_menu)
    {
    
        case 1://�ٶ�
       {
        //��ʾ����
    	GUI_SetBkColor(GUI_BLACK);
    	DemoScale(cur_speed_rear);
		//��ӡ�ٶ�
    	GUI_SetColor(GUI_GREEN);
        GUI_SetFont(& GUI_FontHZ16);
		GUI_DispStringAt("��ǰ�ٶ�:" , 20, 180 );
		GUI_DispStringAt("km/h" , 180, 180 );
		DemoProgBar(cur_speed_rear);
		DemoProgBar2(steady_count);

			{
				
				if((0 != dis_rev)&&(1 == alarm_on))
				{
				 alarm();
				GUI_SetBkColor(GUI_BLACK);
				GUI_Clear();
				}
			}
		//����
		check_return_to_main_menu();
			
		break;
	    }
		
  
  
        case 2://�¶�
        {
       	    Temp_Messagebox();
       	    check_return_to_main_menu();
			break;
	    }  
  
  
        case 3://����
        {
         
   		 show_setting_dialog3();  
   		 while(0 != i_menu);
   		 break;
		
  	    }
  
  
        case 4://����
        {
         Weight_Messagebox();
		 check_return_to_main_menu();
		 break;
  	    }
  
         case 5://��־
        {
         rizhi();
         TouchXY.TouchX = TouchXY.TouchY = 0;
 		 i_menu = 0;
		 break;
  	    }
 
 
         case 6://·��
        {
         DemoBandingMemdev();
		 break;
  	    }
  	  
         case 7://
        {
         not_use_Messagebox();
		 check_return_to_main_menu();
		 break;
  	    }
 	  
  	  
        case 8://����
        {
        
		 GUIDEMO_Navigation();
		 break;
  	    }
  	   
  	   
  	   
        case 9://����
        {
		 tankProgBar();
		 check_return_to_main_menu();
		 break;
  	    }
  	    
  	    
        case 10://����
        {
        
		 return_Messagebox();
		 check_return_to_main_menu();
		 break;
  	    }
 	   
   		case 11://����
   		{
   		 show_setting_dialog2();
   		 while(0 != i_menu);
   		 break;
   				
   		} 
  	 } 
  
    GUI_Exec();           /* Do the background work ... Update windows etc.) */
    GUI_X_ExecIdle();     /* Nothing left to do for the moment ... Idle processing */
    
  }
}


/*******************************************************************
*
*        						 Main
*��ʼ��������OS
* 
*********************************************************************/

void UCOSMain(void)
{

    Uart_Printf("UCOSMain runing!\n");

	ARMTargetInit();  //��ʼ��Ŀ���

	GUI_Init();
	GUI_Clear();

    OSInit();		  //��ʼ������ϵͳ   
    //OSSchedLock();
 
    OSTaskCreate( Main_Task, (void *)0, &Main_Stack[TASK_STACK_SIZE - 1], Main_PRIO);      
    OSStart();        //���в���ϵͳ
    //���򲻻��������� 
 
}      
