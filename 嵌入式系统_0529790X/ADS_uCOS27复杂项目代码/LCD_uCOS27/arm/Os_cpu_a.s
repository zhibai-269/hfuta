;/****************************************Copyright (c)**************************************************
;
;**------------------------------------------------------------------------------------------------------
;********************************************************************************************************/
;����ϵͳģʽ��ջ�Ĵ�С
SVC_STACK_LEGTH     EQU         32

NoInt       EQU 0x80

USR32Mode   EQU 0x10
SVC32Mode   EQU 0x13
SYS32Mode   EQU 0x1f
IRQ32Mode   EQU 0x12
FIQ32Mode   EQU 0x11

;T_bit���ڼ������쳣ǰcpu�Ƿ���THUMB״̬
T_bit               EQU         0x20

    CODE32
    PRESERVE8
    AREA    |subr|, CODE, READONLY

            IMPORT  OSTCBCur                    ;ָ��ǰ����TCB��ָ��
            IMPORT  OSTCBHighRdy                ;ָ��Ҫ���е�����TCB��ָ��
            IMPORT  OSPrioCur                   ;��ǰ��������ȼ�
            IMPORT  OSPrioHighRdy               ;��Ҫ���е���������ȼ�
            IMPORT  OSTaskSwHook                ;�����л��Ĺ��Ӻ���
            IMPORT  OSRunning                   ;uC/OS-II���б�־

            IMPORT  OsEnterSum                  ;���жϼ����������ж��ź�����
            IMPORT  SWI_Exception               ;���ж��쳣�������
            
            EXPORT  __OSStartHighRdy            
            EXPORT  OSIntCtxSw                  ;�ж��˳�ʱ����ڣ��μ�startup.s�е�IRQ_Handler
            EXPORT  SoftwareInterrupt           ;���ж����


;/*********************************************************************************************************
;** ��������: SoftwareInterrupt
;** ��������: ����жϣ������ṩһЩϵͳ���񣬹��ܲο�os_cpu_c.c�ļ�
;** �䡡��:   �����ܶ���
;** �䡡�� :  �����ܶ���
;** ȫ�ֱ���: ��
;** ����ģ��: SWI_Exception

;**-------------------------------------------------------------------------------------------------------
;********************************************************************************************************/

;����ж�
SoftwareInterrupt
        LDR     SP, StackSvc            ; �������ö�ջָ��
        STMFD   SP!, {R0-R3, R12, LR}
        MOV     R1, SP                  ; R1ָ������洢λ��

        MRS     R3, SPSR
        TST     R3, #T_bit              ; �ж�ǰ�Ƿ���Thumb״̬
        LDRNEH  R0, [LR,#-2]            ; ��: ȡ��Thumb״̬SWI��
        BICNE   R0, R0, #0xff00
        LDREQ   R0, [LR,#-4]            ; ��: ȡ��arm״̬SWI��
        BICEQ   R0, R0, #0xFF000000
                                        ; r0 = SWI�ţ�R1ָ������洢λ��
        CMP     R0, #1
        LDRLO   PC, =OSIntCtxSw
        LDREQ   PC, =__OSStartHighRdy   ; SWI 0x01Ϊ��һ�������л�

        BL      SWI_Exception
        
        LDMFD   SP!, {R0-R3, R12, PC}^
        
StackSvc           DCD     (SvcStackSpace + SVC_STACK_LEGTH * 4 - 4)

;/*********************************************************************************************************
;** ��������: OSIntCtxSw
;** ��������: �ж��˳�ʱ�����
;** �䡡��:   R3    :��ǰ�����״̬�Ĵ���CPSR����SPSR��ֵ��
;**           R4-R12:��ǰ�����R4-R11
;**           ��ǰ������ģʽ�Ķ�ջ�ṹ����ջ���򣩣�R0-R3��R12��PC����ǰ����ģ�
;** �䡡�� :  ��
;** ȫ�ֱ���: OSPrioCur,OSPrioHighRdy,OSPrioCur,OSPrioHighRdy
;** ����ģ��: ��

;**-------------------------------------------------------------------------------------------------------
;********************************************************************************************************/
OSIntCtxSw
                                                    ;����Ϊ�������񻷾�
        LDR     R2, [SP, #20]                       ;��ȡPC
        LDR     R12, [SP, #16]                      ;��ȡR12
        MRS     R0, CPSR

        MSR     CPSR_c, #(NoInt | SYS32Mode)
        MOV     R1, LR
        STMFD   SP!, {R1-R2}                        ;����LR,PC
        STMFD   SP!, {R4-R12}                       ;����R4-R12

        MSR     CPSR_c, R0
        LDMFD   SP!, {R4-R7}                        ;��ȡR0-R3
        ADD     SP, SP, #8                          ;��ջR12,PC
        
        MSR     CPSR_c, #(NoInt | SYS32Mode)
        STMFD   SP!, {R4-R7}                        ;����R0-R3
        
        LDR     R1, =OsEnterSum                     ;��ȡOsEnterSum
        LDR     R2, [R1]
        STMFD   SP!, {R2, R3}                       ;����CPSR,OsEnterSum

                                                    ;���浱ǰ�����ջָ�뵽��ǰ�����TCB
        LDR     R1, =OSTCBCur
        LDR     R1, [R1]
        STR     SP, [R1]

        BL      OSTaskSwHook                        ;���ù��Ӻ���
                                                    ;OSPrioCur <= OSPrioHighRdy
        LDR     R4, =OSPrioCur
        LDR     R5, =OSPrioHighRdy
        LDRB    R6, [R5]
        STRB    R6, [R4]
                                                    ;OSTCBCur <= OSTCBHighRdy
        LDR     R6, =OSTCBHighRdy
        LDR     R6, [R6]
        LDR     R4, =OSTCBCur
        STR     R6, [R4]
OSIntCtxSw_1
                                                    ;��ȡ�������ջָ��
        LDR     R4, [R6]
        ADD     SP, R4, #68                         ;17�Ĵ���CPSR,OsEnterSum,R0-R12,LR,SP
        LDR     LR, [SP, #-8]
        MSR     CPSR_c, #(NoInt | SVC32Mode)        ;�������ģʽ
        MOV     SP, R4                              ;���ö�ջָ��

        LDMFD   SP!, {R4, R5}                       ;CPSR,OsEnterSum
                                                    ;�ָ��������OsEnterSum
        LDR     R3, =OsEnterSum
        STR     R4, [R3]
    
        MSR     SPSR_cxsf, R5                       ;�ָ�CPSR
        LDMFD   SP!, {R0-R12, LR, PC }^             ;����������

;/*********************************************************************************************************
;** ��������: __OSStartHighRdy
;** ��������: uC/OS-II����ʱʹ��OSStartHighRdy���е�һ������,
;**           OSStartHighRdy�����__OSStartHighRdy
;** �䡡��:   ��
;** �䡡�� :  ��
;** ȫ�ֱ���: OSRunning,OSTCBCur,OSTCBHighRdy,OsEnterSum
;** ����ģ��: OSTaskSwHook
;** 
;** ������: ������
;** �ա���: 2003��6��5��
;**-------------------------------------------------------------------------------------------------------
;** �ޡ���: ������
;** �ա���: 2003��6��13��
;**-------------------------------------------------------------------------------------------------------
;********************************************************************************************************/

__OSStartHighRdy
        MSR     CPSR_c, #(NoInt | SYS32Mode)
                                                ;����uC/OS-II�����Ѿ�����
        LDR     R4, =OSRunning
        MOV     R5, #1
        STRB    R5, [R4]

        BL      OSTaskSwHook                    ;���ù��Ӻ���

        LDR     R6, =OSTCBHighRdy
        LDR     R6, [R6]
        B       OSIntCtxSw_1

        AREA    SWIStacks, DATA, NOINIT
;,ALIGN=2
SvcStackSpace      SPACE   SVC_STACK_LEGTH * 4  ;����ģʽ��ջ�ռ�

    END
;/*********************************************************************************************************
;**                            End Of File
;********************************************************************************************************/
