
;/********************************************************************************************************/

;�����ջ�Ĵ�С��������Ҫ�ı�
FIQ_STACK_LEGTH     EQU         0
IRQ_STACK_LEGTH     EQU         64
ABT_STACK_LEGTH     EQU         0
UND_STACK_LEGTH     EQU         0
VICVectAddr         EQU         0xFFFFF030
NoInt       EQU 0x80


;������ⲿ�����������
        IMPORT  FIQ_Exception                   ;�����ж��쳣�������
        IMPORT  SoftwareInterrupt               ;���ж����
        IMPORT  Reset                           ;��λ�������
        IMPORT  OSIntCtxSw                      ;�ж��������л�����
        IMPORT  OSIntExit                       ;�ж��˳�����
        IMPORT  OSTCBCur                        ;ָ��ǰ����TCB��ָ��
        IMPORT  OSTCBHighRdy                    ;ָ��Ҫ���е�����TCB��ָ��
  
        IMPORT  OSIntNesting                    ;�ж�Ƕ�׼�����


;���ⲿʹ�õı������������InitStack�Ǳ����
        EXPORT  InitStack                       
        EXPORT  Vectors


    CODE32
    PRESERVE8
    AREA    StartUp,CODE,READONLY

    ENTRY
;�ж�������
Vectors
        LDR     PC, ResetAddr
        LDR     PC, UndefinedAddr
        LDR     PC, SWI_Addr
        LDR     PC, PrefetchAddr
        LDR     PC, DataAbortAddr
        DCD     0xb9205f80
        LDR     PC, [PC, #-0xff0]
        LDR     PC, FIQ_Addr

ResetAddr           DCD     Reset
UndefinedAddr       DCD     Undefined
SWI_Addr            DCD     SoftwareInterrupt
PrefetchAddr        DCD     PrefetchAbort
DataAbortAddr       DCD     DataAbort
nouse               DCD     0
IRQ_Addr            DCD     IRQ_Handler
FIQ_Addr            DCD     FIQ_Handler


    MACRO
$IRQ_Label HANDLER $IRQ_Exception

        EXPORT  $IRQ_Label                      ; ����ı��
        IMPORT  $IRQ_Exception                  ; ���õ��ⲿ���

$IRQ_Label
        SUB     LR, LR, #4                      ; ���㷵�ص�ַ
        STMFD   SP!, {R0-R3, R12, LR}           ; �������񻷾�
        MRS     R3, SPSR                        ; ����״̬
        STMFD   SP!, {R3}

        LDR     R2,  =OSIntNesting              ; OSIntNesting++
        LDRB    R1, [R2]
        ADD     R1, R1, #1
        STRB    R1, [R2]
        
        BL      $IRQ_Exception                  ; ����c���Ե��жϴ������

        MSR     CPSR_c, #0x92
        BL      OSIntExit

        LDR     R0, =OSTCBHighRdy
        LDR     R0, [R0]
        LDR     R1, =OSTCBCur
        LDR     R1, [R1]
        CMP     R0, R1
        
        LDMFD   SP!, {R3}
        MSR     SPSR_cxsf, R3

        LDMEQFD SP!, {R0-R3, R12, PC}^          ; �����������л�
        LDR     PC, =OSIntCtxSw                 ; ���������л�
    MEND

;δ����ָ��
Undefined
        b       Undefined

;ȡָ����ֹ
PrefetchAbort
        b       PrefetchAbort

;ȡ������ֹ
DataAbort
        b       DataAbort

;�ж�
IRQ_Handler	HANDLER IRQ_Exception

;�����ж�
FIQ_Handler
        STMFD   SP!, {R0-R3, LR}
        BL      FIQ_Exception
        LDMFD   SP!, {R0-R3, LR}
        SUBS    PC,  LR,  #4

;��ʱ��0�ж�
Timer0_Handler  HANDLER Timer0

;/*********************************************************************************************************
;** ��������: InitStack
;** ��������: ��ʼ����ջ
;********************************************************************************************************/
InitStack    
        MOV     R0, LR
;�����ж�ģʽ��ջ
        MSR     CPSR_c, #0xd2
        LDR     SP, StackIrq
;���ÿ����ж�ģʽ��ջ
        MSR     CPSR_c, #0xd1
        LDR     SP, StackFiq
;������ֹģʽ��ջ
        MSR     CPSR_c, #0xd7
        LDR     SP, StackAbt
;����δ����ģʽ��ջ
        MSR     CPSR_c, #0xdb
        LDR     SP, StackUnd
;����ϵͳģʽ��ջ
        MSR     CPSR_c, #0xdf
        LDR     SP, StackIrq
        MOV     PC, R0

StackIrq           DCD     (IrqStackSpace + IRQ_STACK_LEGTH * 4 - 4)
StackFiq           DCD     (FiqStackSpace + FIQ_STACK_LEGTH * 4 - 4)
StackAbt           DCD     (AbtStackSpace + ABT_STACK_LEGTH * 4 - 4)
StackUnd           DCD     (UndtStackSpace + UND_STACK_LEGTH * 4 - 4)

;/* �����ջ�ռ� */
        AREA    MyStacks, DATA, NOINIT
IrqStackSpace      SPACE   IRQ_STACK_LEGTH * 4  ;�ж�ģʽ��ջ�ռ�
FiqStackSpace      SPACE   FIQ_STACK_LEGTH * 4  ;�����ж�ģʽ��ջ�ռ�
AbtStackSpace      SPACE   ABT_STACK_LEGTH * 4  ;��ֹ��ģʽ��ջ�ռ�
UndtStackSpace     SPACE   UND_STACK_LEGTH * 4  ;δ����ģʽ��ջ




    END
;/*********************************************************************************************************
;**                            End Of File
;********************************************************************************************************/
