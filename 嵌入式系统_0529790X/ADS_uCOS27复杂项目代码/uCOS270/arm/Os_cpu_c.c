/****************************************Copyright (c)**************************************************
**                               ������������Ƭ����չ���޹�˾
**                                     ��    ��    ��
**                                        ��Ʒһ�� 
**
**                                 http://www.zlgmcu.com
**
**--------------�ļ���Ϣ--------------------------------------------------------------------------------
**��   ��   ��: os_cpu_c.c
**��   ��   ��: ������
**����޸�����: 2003��7��8��
**��        ��: ��COS-II��lpc210x�ϵ���ֲ����C���Բ��֣����������ջ��ʼ������͹��Ӻ�����
**              ��ads1.2���룬����ʹ��ARM��ʽ����
**
**--------------��ʷ�汾��Ϣ----------------------------------------------------------------------------
** ������: ������
** ��  ��: 1.0
** �ա���: 2003��6��5��
** �衡��: ԭʼ�汾
**
**------------------------------------------------------------------------------------------------------
** �޸���: ������
** ��  ��: 1.1
** �ա���: 2003��6��13��
** �衡��: ���Ӻ���IsrEnIRQ��ʹ����OSTaskStkInit��������
**
**------------------------------------------------------------------------------------------------------
** �޸���: ������
** ��  ��: 1.2
** �ա���: 2003��6��19��
** �衡��: �������жϷ�����
**
**------------------------------------------------------------------------------------------------------
** �޸���: ������
** ��  ��: 1.3
** �ա���: 2003��7��8��
** �衡��: ȥ������Ҫ�ĺ���IsrEnIRQ
**
**--------------��ǰ�汾�޶�------------------------------------------------------------------------------
** �޸���: 
** �ա���: 
** �衡��: 
**
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
#define  OS_CPU_GLOBALS
#include "config.h"


/*********************************************************************************************************
** ��������: OSTaskStkInit
** ��������: �����ջ��ʼ�����룬����������ʧ�ܻ�ʹϵͳ����
** �䡡��: task  : ����ʼִ�еĵ�ַ
**         pdata �����ݸ�����Ĳ���
**         ptos  ������Ķ�ջ��ʼλ��
**         opt   �����Ӳ�������ǰ�汾���ڱ��������ã���������μ�OSTaskCreateExt()��opt����
** �䡡��: ջ��ָ��λ��
** ȫ�ֱ���:
** ����ģ��: 
**
** ������: ������
** �ա���: 2003��6��5��
**-------------------------------------------------------------------------------------------------------
** �޸���: ������
** �ա���: 2003��6��13��
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/

        OS_STK *OSTaskStkInit (void (*task)(void *pd), void *pdata, OS_STK *ptos, INT16U opt)
{
    OS_STK *stk;

    opt    = opt;                           /* 'opt'  û��ʹ�á������Ǳ������������    */
    stk    = ptos;                          /* ��ȡ��ջָ��                                       */

                                            /* �������񻷾���ADS1.2ʹ�����ݼ���ջ       */
    *stk = (OS_STK) task;                   /*  pc  */
    *--stk = (OS_STK) task;                 /*  lr  */

    *--stk = 0;                             /*  r12  */
    *--stk = 0;                             /*  r11  */
    *--stk = 0;                             /*  r10  */
    *--stk = 0;                             /*  r9   */
    *--stk = 0;                             /*  r8   */
    *--stk = 0;                             /*  r7   */
    *--stk = 0;                             /*  r6   */
    *--stk = 0;                             /*  r5   */
    *--stk = 0;                             /*  r4   */
    *--stk = 0;                             /*  r3   */
    *--stk = 0;                             /*  r2   */
    *--stk = 0;                             /*  r1   */
    *--stk = (unsigned int) pdata;          /*  r0,��һ������ʹ��R0����   */
    *--stk = (USER_USING_MODE|0x00);	    /*  spsr������ IRQ, FIQ �ж�   */
    *--stk = 0;                             /*  ���жϼ�����OsEnterSum;    */

    return (stk);
}


/*********************************************************************************************************
** ��������: SWI_Exception
** ��������: ���ж��쳣��������ṩһЩϵͳ����
**           
** �䡡��:  SWI_Num:���ܺ�
**          Regs[0] Ϊ��һ��������Ҳ�Ƿ���ֵ
**          Regs[1] Ϊ�ڶ�������
**          Regs[2] Ϊ����������
**          Regs[3] Ϊ���ĸ�����
** �䡡��: ���ݹ��ܶ���
**         
** ȫ�ֱ���: ��
** ����ģ��: ��
**
** ������: ������
** �ա���: 2003��6��5��
**-------------------------------------------------------------------------------------------------------
** �޸���: ������
** �ա���: 2003��6��19��
**-------------------------------------------------------------------------------------------------------
** �޸���: ������
** �ա���: 2003��6��24��
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
#if OS_SELF_EN > 0 
extern int const _OSFunctionAddr[];
extern int const _UsrFunctionAddr[];
#endif
        void SWI_Exception(int SWI_Num, int *Regs)
{
    OS_TCB   *ptcb;
    
    switch(SWI_Num)
    {
        //case 0x00:                    /* �����л�����OS_TASK_SW���ο�os_cpu_s.s�ļ�     */
        //    break;
        //case 0x01:                    /* ����������OSStartHighRdy���ο�os_cpu_s.s�ļ� */
        //    break;
        case 0x02:                      /* ���жϺ���OS_ENTER_CRITICAL()���ο�os_cpu.h�ļ� */
            __asm
            {
                MRS     R0, SPSR
                ORR     R0, R0, #NoInt
                MSR     SPSR_c, R0
            }
            OsEnterSum++;
            break;
        case 0x03:                      /* ���жϺ���OS_EXIT_CRITICAL()���ο�os_cpu.h�ļ� */
            if (--OsEnterSum == 0)
            {
                __asm
                {
                    MRS     R0, SPSR
                    BIC     R0, R0, #NoInt
                    MSR     SPSR_c, R0
                }
            }
            break;
#if OS_SELF_EN > 0 
        case 0x40:
                                        /* ����ָ��ϵͳ�������ĵ�ַ       */
                                        /* ������ַ��������_OSFunctionAddr��*/
                                        /* ����_OSFunctionAddr��Ҫ���ⶨ��  */
                                        /* Regs[0] Ϊ��һ��������Ҳ�Ƿ���ֵ */
                                        /* Regs[1] Ϊ�ڶ�������             */
                                        /* Regs[2] Ϊ����������             */
                                        /* Regs[3] Ϊ���ĸ�����             */
                                        /* ����һ������Ϊϵͳ������������ */
            Regs[0] =  _OSFunctionAddr[Regs[0]];
            break;
        case 0x41:
                                        /* ����ָ���û��ķ������ĵ�ַ     */
                                        /* ������ַ��������_UsrFunctionAddr��*/
                                        /* ����_UsrFunctionAddr��Ҫ���ⶨ�� */
                                        /* Regs[0] Ϊ��һ��������Ҳ�Ƿ���ֵ */
                                        /* Regs[1] Ϊ�ڶ�������             */
                                        /* Regs[2] Ϊ����������             */
                                        /* Regs[3] Ϊ���ĸ�����             */
                                        /* ����һ������Ϊ�û������������� */
            Regs[0] =  _UsrFunctionAddr[Regs[0]];
            break;
        case 0x42:                      /* �жϿ�ʼ���� */
            OSIntNesting++;
            break;
        case 0x43:                      /*  �ж��ж��Ƿ���Ҫ�л�             */
            if (OSTCBHighRdy == OSTCBCur)
            {
                Regs[0] = 0;
            }
            else
            {
                Regs[0] = 1;
            }
            break;
#endif
        case 0x80:                      /* �����л���ϵͳģʽ */
            __asm
            {
                MRS     R0, SPSR
                BIC     R0, R0, #0x1f
                ORR     R0, R0, #SYS32Mode    
                MSR     SPSR_c, R0
            }
            break;
        case 0x81:                      /* �����л����û�ģʽ */
            __asm
            {
                MRS     R0, SPSR
                BIC     R0, R0, #0x1f
                ORR     R0, R0, #USR32Mode    
                MSR     SPSR_c, R0
            }
            break;
        case 0x82:                      /* ������ARM���� */
            if (Regs[0] <= OS_LOWEST_PRIO)
            {
                ptcb = OSTCBPrioTbl[Regs[0]];
                if (ptcb != NULL)
                {
                    ptcb -> OSTCBStkPtr[1] &= ~(1 << 5);
                }
            }
            break;
        case 0x83:                      /* ������THUMB���� */
            if (Regs[0] <= OS_LOWEST_PRIO)
            {
                ptcb = OSTCBPrioTbl[Regs[0]];
                if (ptcb != NULL)
                {
                    ptcb -> OSTCBStkPtr[1] |= (1 << 5);
                }
            }
            break;
        default:
            break;
    }
}

/*********************************************************************************************************
** ��������: OSStartHighRdy
** ��������: uC/OS-II����ʱʹ��OSStartHighRdy���е�һ������,
**           ʵ���ǲ���swi 1ָ��
** �䡡��:   ��
** �䡡�� :  ��
** ȫ�ֱ���: ��
** ����ģ��: ��
** 
** ������: ������
** �ա���: 2003��6��5��
**-------------------------------------------------------------------------------------------------------
** �ޡ���: 
** �ա���: 
**-------------------------------------------------------------------------------------------------------
********************************************************************************************************/

        void OSStartHighRdy(void)
{
    _OSStartHighRdy();
}


/* ����ΪһЩ���Ӻ�����ȫ��Ϊ�պ���������˵���뿴������� */

#if OS_CPU_HOOKS_EN
/*
*********************************************************************************************************
*                                       OS INITIALIZATION HOOK
*                                            (BEGINNING)
*
* Description: This function is called by OSInit() at the beginning of OSInit().
*
* Arguments  : none
*
* Note(s)    : 1) Interrupts should be disabled during this call.
*********************************************************************************************************
*/
#if OS_VERSION > 203
void OSInitHookBegin (void)
{
}
#endif

/*
*********************************************************************************************************
*                                       OS INITIALIZATION HOOK
*                                               (END)
*
* Description: This function is called by OSInit() at the end of OSInit().
*
* Arguments  : none
*
* Note(s)    : 1) Interrupts should be disabled during this call.
*********************************************************************************************************
*/
#if OS_VERSION > 203
void OSInitHookEnd (void)
{
}
#endif


/*
*********************************************************************************************************
*                                          TASK CREATION HOOK
*
* Description: This function is called when a task is created.
*
* Arguments  : ptcb   is a pointer to the task control block of the task being created.
*
* Note(s)    : 1) Interrupts are disabled during this call.
*********************************************************************************************************
*/
void OSTaskCreateHook (OS_TCB *ptcb)
{
    ptcb = ptcb;                       /* Prevent compiler warning                                     */
}


/*
*********************************************************************************************************
*                                           TASK DELETION HOOK
*
* Description: This function is called when a task is deleted.
*
* Arguments  : ptcb   is a pointer to the task control block of the task being deleted.
*
* Note(s)    : 1) Interrupts are disabled during this call.
*********************************************************************************************************
*/
void OSTaskDelHook (OS_TCB *ptcb)
{
    ptcb = ptcb;                       /* Prevent compiler warning                                     */
}

/*
*********************************************************************************************************
*                                           TASK SWITCH HOOK
*
* Description: This function is called when a task switch is performed.  This allows you to perform other
*              operations during a context switch.
*
* Arguments  : none
*
* Note(s)    : 1) Interrupts are disabled during this call.
*              2) It is assumed that the global pointer 'OSTCBHighRdy' points to the TCB of the task that
*                 will be 'switched in' (i.e. the highest priority task) and, 'OSTCBCur' points to the 
*                 task being switched out (i.e. the preempted task).
*********************************************************************************************************
*/
void OSTaskSwHook (void)
{
}

/*
*********************************************************************************************************
*                                           STATISTIC TASK HOOK
*
* Description: This function is called every second by uC/OS-II's statistics task.  This allows your 
*              application to add functionality to the statistics task.
*
* Arguments  : none
*********************************************************************************************************
*/
void OSTaskStatHook (void)
{
}

/*
*********************************************************************************************************
*                                           OSTCBInit() HOOK
*
* Description: This function is called by OSTCBInit() after setting up most of the TCB.
*
* Arguments  : ptcb    is a pointer to the TCB of the task being created.
*
* Note(s)    : 1) Interrupts may or may not be ENABLED during this call.
*********************************************************************************************************
*/
#if OS_VERSION > 203
void OSTCBInitHook (OS_TCB *ptcb)
{
    ptcb = ptcb;                                           /* Prevent Compiler warning                 */
}
#endif


/*
*********************************************************************************************************
*                                               TICK HOOK
*
* Description: This function is called every tick.
*
* Arguments  : none
*
* Note(s)    : 1) Interrupts may or may not be ENABLED during this call.
*********************************************************************************************************
*/
void OSTimeTickHook (void)
{
}


/*
*********************************************************************************************************
*                                             IDLE TASK HOOK
*
* Description: This function is called by the idle task.  This hook has been added to allow you to do  
*              such things as STOP the CPU to conserve power.
*
* Arguments  : none
*
* Note(s)    : 1) Interrupts are enabled during this call.
*********************************************************************************************************
*/
#if OS_VERSION >= 251
void OSTaskIdleHook (void)
{
}
#endif
#endif
/*********************************************************************************************************
**                            End Of File
********************************************************************************************************/

