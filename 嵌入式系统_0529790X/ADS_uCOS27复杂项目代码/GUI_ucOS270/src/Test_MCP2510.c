/****************************************************************************
����  ��  ��  �ơ�Test_MCP2510.C
����  ��  ��  ��������S3C2410A��demo�������
����  ��  ��  ����4.0
�������˼��������ڡ�����( gongjun98@sohu.com )//2002��11��19��19:26
���޸��˼��޸����ڡ�����( gongjun98@sohu.com )//2004-12-8 17:25
****************************************************************************/

//***************************************************************************
#include "def.h"
#include "option.h"
#include "2440addr.h"
#include "2440lib.h"
#include "2440slib.h" 
#include "MCP2510.h"


/****************************************************************************
MCP2510_CS		GPG2		output		( nSS0 )
MCP2510_SI		GPE12		output		( SPIMOSI0 )
MCP2510_SO		GPE11		input		( SPIMISO0 )
MCP2510_SCK		GPE13		output		( SPICLK0 )
MCP2510_INT		GPG0		input		( EINT8 )
****************************************************************************/
#define MCP2510_DEBUG    1
#define DELAY_TIME		500

#define MCP2510_CS_OUT		( rGPGCON = rGPGCON & (~(3<<4)) | (1<<4) )		//GPG2
#define MCP2510_CS_H		( rGPGDAT = rGPGDAT | (1<<2) )
#define MCP2510_CS_L		( rGPGDAT = rGPGDAT & (~(1<<2))  )

#define MCP2510_SI_OUT		( rGPECON = rGPECON & (~(3<<24)) | (1<<24) )		//GPE12
#define MCP2510_SI_H		( rGPEDAT = rGPEDAT | (1<<12) )
#define MCP2510_SI_L		( rGPEDAT = rGPEDAT & (~(1<<12)) )

#define MCP2510_SCK_OUT		( rGPECON = rGPECON & (~(3<<26)) | (1<<26) )		//GPE13
#define MCP2510_SCK_H		( rGPEDAT = rGPEDAT | (1<<13) )
#define MCP2510_SCK_L		( rGPEDAT = rGPEDAT & (~(1<<13)) )

#define MCP2510_SO_IN		( rGPECON = rGPECON & (~(3<<22)) | (0<<22) )		//GPE11
#define MCP2510_SO_GET		( rGPEDAT & (1<<11) )	
#define MCP2510_SO_PULLUP		( rGPEUP = rGPEUP & (~(1<<11)) )
#define MCP2510_SO_DISPULLUP		( rGPEUP = rGPEUP | (1<<11) )

#define MCP2510_INT_IN		( rGPGCON = rGPGCON & (~(3<<0)) )		//GPG0
#define MCP2510_INT_GET		( rGPGDAT & 0x01 )	
/********************** MCP2510 Instruction *********************************/
#define MCP2510INSTR_RESET		0xc0		//��λΪȱʡ״̬�����趨Ϊ����ģʽ
#define MCP2510INSTR_READ		0x03		//�ӼĴ����ж�������
#define MCP2510INSTR_WRITE		0x02		//��Ĵ���д������
#define MCP2510INSTR_RTS		0x80		//����һ���������ͻ������ı��ķ���
#define MCP2510INSTR_RDSTAT		0xa0		//��ȡ״̬
#define MCP2510INSTR_BITMDFY	0x05		//λ�޸�
//***************************************************************************

/****************************************************************************
������˵����SPI�ӿ�IOƬѡ��ʼ��
****************************************************************************/
void MCP2510_IO_CS_Init( void ) 
{
   MCP2510_CS_OUT ;
   MCP2510_SI_OUT ;
   MCP2510_SCK_OUT ;
   MCP2510_SO_IN ;
   MCP2510_SO_PULLUP ;		//��������
   //MCP2510_SO_DISPULLUP ;		//��ֹ����

   MCP2510_SI_L ;		//SI put 0
   MCP2510_SCK_L ;		//SCK put 0
   { U16 k=0; for( ; k <= DELAY_TIME; k++ ) ;  }  //��ʱ����300ns
   MCP2510_CS_H ;			// unselect the MCP2510
   { U16 k=0; for( ; k <= DELAY_TIME; k++ ) ;  }  //��ʱ����300ns
}

/****************************************************************************
������˵����SPI�ӿڶ�д��ʼ��Ƭѡ��Ч
****************************************************************************/
void MCP2510_RW_Start( void ) 
{
   MCP2510_SI_L ;		//SI put 0
   MCP2510_SCK_L ;		//SCK put 0
   { U16 k=0; for( ; k <= DELAY_TIME; k++ ) ;  }  //��ʱ����300ns
   MCP2510_CS_L ;			// Select the MCP2510
   { U16 k=0; for( ; k <= DELAY_TIME; k++ ) ;  }  //��ʱ����300ns
}

/****************************************************************************
������˵����SPI�ӿ�д������
****************************************************************************/
void Spi_Write( U8 Data ) 
{
	U8 m ;

	for( m = 0; m < 8; m++ )
	{
		if( (Data&0x80)==0x80 )
			MCP2510_SI_H;		//SI put 1
		else
			MCP2510_SI_L;		//SI put 0

		{ U16 k=0; for( ; k <= DELAY_TIME; k++ ) ;  }  //��ʱ����300ns
		MCP2510_SCK_H ;		//SCK put 1
		Data = Data<<1 ;
		MCP2510_SCK_L ;		//SCK put 0
		{ U16 k=0; for( ; k <= DELAY_TIME; k++ ) ;  }  //��ʱ����300ns
	}
}

/****************************************************************************
������˵����SPI�ӿڶ�������
****************************************************************************/
U8 Spi_Read( )
{
	U8 m ;
	U8 data = 0 ;

	for( m = 0; m < 8; m++ )
	{
		MCP2510_SCK_H ;		//SCK put 1
		{ U16 k=0; for( ; k <= DELAY_TIME; k++ ) ;  }  //��ʱ����300ns
		data = data<<1;
		if( MCP2510_SO_GET != 0 )
			data |= 0x01 ;
		else
			data &= 0xfe;

		{ U16 k=0; for( ; k <= DELAY_TIME; k++ ) ;  }  //��ʱ����300ns
		MCP2510_SCK_L ;		//SCK put 0
		{ U16 k=0; for( ; k <= DELAY_TIME; k++ ) ;  }  //��ʱ����300ns
	}

	return (data);
}

/****************************************************************************
������˵���� Send Command to MCP2510 via SPI 
****************************************************************************/
void SendCMDMCP2510( U8 CMD )
{
   MCP2510_RW_Start() ;		//Initial IO port and CS is select
   Spi_Write( CMD );
   MCP2510_CS_H ;			// Deselect the MCP2510
}

/****************************************************************************
������˵���������λMCP2510
****************************************************************************/
void MCP2510_Reset()
{
	MCP2510_RW_Start() ;
	Spi_Write( MCP2510INSTR_RESET );
	MCP2510_CS_H ;
}

/****************************************************************************
������˵������MCP2510ָ����ַд��һ���ֽ�
****************************************************************************/
void MCP2510_Write( U8 address, U8 value)
{
	MCP2510_RW_Start() ;

	Spi_Write(MCP2510INSTR_WRITE);
	Spi_Write( address );
	Spi_Write( value );

	MCP2510_CS_H ;
}

/****************************************************************************
������˵�����޸�ָ����ַ�Ĵ�����ĳЩλ
****************************************************************************/
void MCP2510_WriteBits( U8 address, U8 data, U8 mask )
{
	MCP2510_RW_Start() ;

	Spi_Write( MCP2510INSTR_BITMDFY );
	Spi_Write( address);
	Spi_Write( mask);
	Spi_Write( data);

	MCP2510_CS_H ;
}

/****************************************************************************
������˵����              Read often used status
//Status 	 7    	6    	5    	4    	3    	2  	1	0
//		|	|	|	|	|	|	|	|									
//		|	|	|	|	|	|	|	|___CANINTF.RX0IF
//		|	|	|	|	|	|	|_______CANINTF.RX1IF
//		|	|	|	|	|	|___________TXB0CTRL.TXREQ
//		|	|	|	|	|_______________CANINTF.TX0IF
//		|	|	|	|___________________TXB1CTRL.TXREQ
//		|	|	|_______________________CANINTF.TX1IF
//		|	|___________________________TXB2CTRL.TXREQ
//		|_______________________________CANINTF.TX2IF
****************************************************************************/
unsigned char MCP2510_ReadStatus()
{
	unsigned char result;

	MCP2510_RW_Start() ;

	Spi_Write(MCP2510INSTR_RDSTAT);
	result = Spi_Read() ;
	Spi_Write( 0 ) ;		//�����ظ����
	MCP2510_CS_H ;

	//if( MCP2510_DEBUG )		Uart_Printf( "StatusREG = 0x%x\n", result ) ;
	return result;
}

/****************************************************************************
������˵������MCP2510ָ����ַ�ж���һ���ֽ�
****************************************************************************/
unsigned char MCP2510_Read( U8 address )
{
	unsigned char result;

	MCP2510_RW_Start() ;

	Spi_Write(MCP2510INSTR_READ) ;		//0x03
	Spi_Write( address ) ;
	result = Spi_Read() ;

	MCP2510_CS_H ;

	return result ;
}

/****************************************************************************
������˵�������ж�ȡMCP2510����	
****************************************************************************/
void MCP2510_SRead( U8 address, unsigned char* pdata, U8 nlength )
{
	int i;

	MCP2510_RW_Start() ;
	Spi_Write(MCP2510INSTR_READ);
	Spi_Write( address );

	for (i=0; i<nlength; i++)
	{
		*pdata=Spi_Read();
		//if( MCP2510_DEBUG )    Uart_Printf( "  0x%x\n", (unsigned char)*pdata ) ;
		pdata++;
	}
	MCP2510_CS_H ;
}


/****************************************************************************
������˵��������д��MCP2510����	
****************************************************************************/
void MCP2510_Swrite( U8 address, unsigned char* pdata, U8 nlength)
{
	int i;
	MCP2510_RW_Start() ;

	Spi_Write(MCP2510INSTR_WRITE);
	Spi_Write((unsigned char)address);

	for (i=0; i < nlength; i++) 
	{
		Spi_Write( (unsigned char)*pdata );
		//if( MCP2510_DEBUG )    Uart_Printf( "0x%x\n", (unsigned char)*pdata ) ;
		pdata++;
	}
	MCP2510_CS_H ;
}

/****************************************************************************
������˵����
****************************************************************************/
void MCP2510_SetBandRate(CanBandRate bandrate, int IsBackNormal)
{
	U8 value=0;
	U8 ReadBackCNT = 0;

	// Bit rate calculations.
	//
	//Input clock fre=16MHz
	// In this case, we'll use a speed of 125 kbit/s, 250 kbit/s, 500 kbit/s.
	// If we set the length of the propagation segment to 7 bit time quanta,
	// and we set both the phase segments to 4 quanta each,
	// one bit will be 1+7+4+4 = 16 quanta in length.
	//
	// setting the prescaler (BRP) to 0 => 500 kbit/s.
	// setting the prescaler (BRP) to 1 => 250 kbit/s.
	// setting the prescaler (BRP) to 3 => 125 kbit/s.
	//
	// If we set the length of the propagation segment to 3 bit time quanta,
	// and we set both the phase segments to 1 quanta each,
	// one bit will be 1+3+2+2 = 8 quanta in length.
	// setting the prescaler (BRP) to 0 => 1 Mbit/s.

	// Go into configuration mode
	MCP2510_Write(MCP2510REG_CANCTRL, MODE_CONFIG);

	if( MCP2510_DEBUG )  Uart_Printf( "MCP2510REG_CANCTRL =  0x%x\n", MCP2510_Read(MCP2510REG_CANCTRL) );

	while( ReadBackCNT<8 )
	{
		value = ( MCP2510_Read( MCP2510REG_CANSTAT ) & 0xe0 );
		if(value == MODE_CONFIG ){
			//Uart_Printf( "ReadBackCNT = 0x%x\n", ReadBackCNT );
			break;
		}
		ReadBackCNT++ ;
	}
	
	if( ReadBackCNT == 8 ) 			//Set mcp2510's mode failed,redo it again
	{
		Uart_Printf( "Set config mode is failed! CANCTRL = 0x%x\n", value );
		MCP2510_Reset();
		MCP2510_Write(MCP2510REG_CANCTRL, MODE_CONFIG);		//redo to set mcp2510 mode
		Delay( 150 );
		value = ( MCP2510_Read(MCP2510REG_CANCTRL) & 0xe0 );	//read back mode from CANSTAT Register
		Uart_Printf( "Set is 0x%x , Read is 0x%x\n", MODE_CONFIG, value ) ;
	}

	switch(bandrate){
	case BandRate_10kbps:
		MCP2510_Write(CNF1, 0x31);	//10k	16TQ
		MCP2510_Write(CNF2, 0xb0);  //PS1=7 TQ  PSeg=1 TQ
		MCP2510_Write(CNF3, 0x06);  //PS2=7 TQ SYNC=1 TQ	
		//if( MCP2510_DEBUG )  Uart_Printf( "CNF1 =  0x%x\n", MCP2510_Read(CNF1) );
		//if( MCP2510_DEBUG )  Uart_Printf( "CNF2 =  0x%x\n", MCP2510_Read(CNF2) );
		//if( MCP2510_DEBUG )  Uart_Printf( "CNF3 =  0x%x\n", MCP2510_Read(CNF3) );
		break;
	case BandRate_125kbps:
		MCP2510_Write(CNF1, SJW1|BRP4);	//Synchronization Jump Width Length =1 TQ
		MCP2510_Write(CNF2, BTLMODE_CNF3|(SEG4<<3)|SEG7); // Phase Seg 1 = 4, Prop Seg = 7
		MCP2510_Write(CNF3, SEG4);// Phase Seg 2 = 4
		break;
	case BandRate_250kbps:
		MCP2510_Write(CNF1, SJW1|BRP2);	//Synchronization Jump Width Length =1 TQ
		MCP2510_Write(CNF2, BTLMODE_CNF3|(SEG4<<3)|SEG7); // Phase Seg 1 = 4, Prop Seg = 7
		MCP2510_Write(CNF3, SEG4);// Phase Seg 2 = 4
		break;
	case BandRate_500kbps:
		MCP2510_Write(CNF1, SJW1|BRP1);	//Synchronization Jump Width Length =1 TQ
		MCP2510_Write(CNF2, BTLMODE_CNF3|(SEG4<<3)|SEG7); // Phase Seg 1 = 4, Prop Seg = 7
		MCP2510_Write(CNF3, SEG4);// Phase Seg 2 = 4
		break;
	case BandRate_1Mbps:
		MCP2510_Write(CNF1, SJW1|BRP1);	//Synchronization Jump Width Length =1 TQ
		MCP2510_Write(CNF2, BTLMODE_CNF3|(SEG3<<3)|SEG2); // Phase Seg 1 = 2, Prop Seg = 3
		MCP2510_Write(CNF3, SEG2);// Phase Seg 2 = 1
		break;
	}

	if( IsBackNormal == TRUE  )
	{
		//Enable clock output
		MCP2510_Write(CLKCTRL, MODE_NORMAL | CLKEN | CLK8);
	}

}

/****************************************************************************
������˵������ȡMCP2510 CAN����ID
����: addressΪMCP2510�Ĵ�����ַ
	can_idΪ���ص�IDֵ
����ֵ
TRUE����ʾ����չID(29λ)
FALSE����ʾ����չID(11λ)
****************************************************************************/
int MCP2510_Read_Can_ID( U8 address, U32* can_id)
{
	U32 tbufdata;
	unsigned char* p=(unsigned char*)&tbufdata;

	MCP2510_SRead(address, p, 4);
	*can_id = (tbufdata<<3)|((tbufdata>>13)&0x7);
	*can_id &= 0x7ff;

	if ( (p[MCP2510LREG_SIDL] & TXB_EXIDE_M) ==  TXB_EXIDE_M ) {
		*can_id = (*can_id<<2) | (p[MCP2510LREG_SIDL] & 0x03);
		*can_id <<= 16;
		*can_id |= tbufdata>>16;
		return TRUE;
	}
	return FALSE;
}

/***********************************************************\
*	��ȡMCP2510 ���յ�����							*
*	����: nbufferΪ�ڼ�������������Ϊ3����4	*
*			can_idΪ���ص�IDֵ							*
*			rxRTR��ʾ�Ƿ���RXRTR						*
*			data��ʾ��ȡ������						*
*			dlc��ʾdata length code							*
*	����ֵ												*
*		TRUE����ʾ����չ����						*
*		FALSE����ʾ����չ����						*
\***********************************************************/
int MCP2510_Read_Can(U8 nbuffer, int* rxRTR, U32* can_id, U8* data , U8* dlc)
{

	U8 mcp_addr = (nbuffer<<4) + 0x31, ctrl;
	int IsExt;

	IsExt=MCP2510_Read_Can_ID( mcp_addr, can_id);

	ctrl=MCP2510_Read(mcp_addr-1);
	*dlc=MCP2510_Read( mcp_addr+4);
	if ((ctrl & 0x08)) {
		*rxRTR = TRUE;
	}
	else{
		*rxRTR = FALSE;
	}
	*dlc &= DLC_MASK;
	//MCP2510_SRead(mcp_addr+5, data, *dlc);
	MCP2510_SRead(mcp_addr+5, data, 8);

	return IsExt;
}


/***********************************************************\
*	д��MCP2510 ���͵�����							*
*	����: nbufferΪ�ڼ�������������Ϊ0��1��2	*
*			ext��ʾ�Ƿ�����չ����					*
*			can_idΪ���ص�IDֵ							*
*			rxRTR��ʾ�Ƿ���RXRTR						*
*			data��ʾ��ȡ������						*
*			dlc��ʾdata length code							*
*		FALSE����ʾ����չ����						*
\***********************************************************/
void MCP2510_Write_Can( U8 nbuffer, int ext, U32 can_id, int rxRTR, U8* data,U8 dlc )
{
	U8 mcp_addr = (nbuffer<<4) + 0x31;
	MCP2510_Swrite(mcp_addr+5, data, dlc );  // write data bytes
	MCP2510_Write_Can_ID( mcp_addr, can_id,ext);  // write CAN id
	if (rxRTR)
		dlc |= RTR_MASK;  // if RTR set bit in byte
	MCP2510_Write((mcp_addr+4), dlc);            // write the RTR and DLC
}

/*******************************************\
*	����MCP2510 CAN����ID				*
*	����: addressΪMCP2510�Ĵ�����ַ*
*			can_idΪ���õ�IDֵ			*
*			IsExt��ʾ�Ƿ�Ϊ��չID	*
\*******************************************/
void MCP2510_Write_Can_ID(U8 address, U32 can_id, int IsExt)
{
	U32 tbufdata;

	if (IsExt) {
		can_id&=0x1fffffff;	//29λ
		tbufdata=can_id &0xffff;
		tbufdata<<=16;
		tbufdata|=(can_id>>(18-5)&(~0x1f));
		tbufdata |= TXB_EXIDE_M;
	}
	else{
		can_id&=0x7ff;	//11λ
		tbufdata= (can_id>>3)|((can_id&0x7)<<13);
	}
	MCP2510_Swrite(address, (unsigned char*)&tbufdata, 4);
}

/***********************************************************************************\
								��������
	����:
		data����������

	Note: ʹ������������ѭ�����ͣ�û������������Ч���
\***********************************************************************************/
void Can_Write(U32 id, U8 *pdata, unsigned char dlc, int IsExt, int rxRTR)
{
	unsigned char err ;
	static int ntxbuffer=0;
	MCP2510_Write_Can(ntxbuffer, IsExt, id, rxRTR, pdata, dlc);

	switch(ntxbuffer){
	case 0:
		MCP2510_WriteBits(TXB0CTRL, (TXB_TXREQ_M|TXB_TXP10_M), 0xff) ;
		do { err = MCP2510_Read(TXB0CTRL) ; }
		while( (err &0x08)==0x08 )  ;
		if( (err &0x70) != 0 )  Uart_Printf( "  Can Send Err = 0x%x\n", err  );
		ntxbuffer=1;
		break;
	case 1:
		MCP2510_WriteBits(TXB1CTRL, (TXB_TXREQ_M|TXB_TXP10_M), 0xff) ;
		do { err = MCP2510_Read(TXB1CTRL) ; }
		while( (err &0x08)==0x08 )  ;
		if( (err &0x70) != 0 )  Uart_Printf( "  Can Send Err = 0x%x\n", err  );
		ntxbuffer=2;
		break;
	case 2:
		MCP2510_WriteBits(TXB2CTRL, (TXB_TXREQ_M|TXB_TXP10_M), 0xff) ;
		do { err = MCP2510_Read(TXB2CTRL) ; }
		while( (err &0x08)==0x08 )  ;
		if( (err &0x70) != 0 )  Uart_Printf( "  Can Send Err = 0x%x\n", err  );
		ntxbuffer=0;
		break;
	}

}


/***********************************************************************************\
								��ѯ�Ƿ��յ�����
	����ֵ:���û�����ݣ��򷵻�-1��
			���򣬷����յ����ݵĻ�������
	Note: ����������������յ����ݣ��򷵻ص�һ��������
\***********************************************************************************/
int Can_Poll()
{
	if( MCP2510_ReadStatus()&RX0INT )
		return 0;
	
	if( MCP2510_ReadStatus()&RX1INT )
		return 1;

	return -1;
}

/****************************************************************************
������˵����
****************************************************************************/
int Can_Read(int n, U32* id, U8 *pdata,  U8*dlc, int* rxRTR, int *isExt)
{
	U8 byte;
	byte = MCP2510_Read(CANINTF);

	if(n==0)
	{
		if(byte & RX0INT)
		{
			*isExt=MCP2510_Read_Can(n+3, rxRTR, id, pdata, dlc);
			MCP2510_WriteBits(CANINTF, (U8)(~(RX0INT)), RX0INT); // Clear interrupt
			return TRUE ;
		}
		Uart_Printf( "Error! 0 bytes is Read!!! CANINTF=0x%x\n", byte ) ;
		return FALSE;
	}
	else if(n ==1 )
	{
		if(byte & RX1INT)
		{
			*isExt=MCP2510_Read_Can(n+4, rxRTR, id, pdata, dlc);
			MCP2510_WriteBits(CANINTF, (U8)(~(RX1INT)), RX1INT); // Clear interrupt
			return TRUE ;
		}
		Uart_Printf( "0 bytes is Read!!! CANINTF=0x%x\n", byte ) ;
		return FALSE;
	}

	Uart_Printf( "Error! Receive channel=0x%x\n", n ) ;
	return FALSE;
}

/****************************************************************************
������˵����
****************************************************************************/
// Setup the CAN buffers used by the application.
// We currently use only one for reception and one for transmission.
// It is possible to use several to get a simple form of queue.
//
// We setup the unit to receive all CAN messages.
// As we only have at most 4 different messages to receive, we could use the
// filters to select them for us.
//
// Init_MCP2510() should already have been called.
void Can_Setup(void)
{
    // As no filters are active, all messages will be stored in RXB0 only if
    // no roll-over is active. We want to recieve all CAN messages (standard and extended)
    // (RXM<1:0> = 11).
    //SPI_mcp_write_bits(RXB0CTRL, RXB_RX_ANY, 0xFF);
    //SPI_mcp_write_bits(RXB1CTRL, RXB_RX_ANY, 0xFF);

    // But there is a bug in the chip, so we have to activate roll-over.
	MCP2510_WriteBits(RXB0CTRL, (RXB_BUKT+RXB_RX_ANY), 0xFF);		//�ر������˲����ܣ��������б��ģ�������� 
	MCP2510_WriteBits(RXB1CTRL, RXB_RX_ANY, 0xFF);		//�ر������˲����ܣ��������б���
}

/****************************************************************************
������˵����
****************************************************************************/
void Init_MCP2510(CanBandRate bandrate)
{
	unsigned char i,j,a;

	MCP2510_IO_CS_Init() ;
	MCP2510_Reset();

	MCP2510_SetBandRate(bandrate,FALSE);		//���ò�����

	// Disable interrups.
	MCP2510_Write(CANINTE, NO_IE);  		//��ֹ�����ж�

	// Mark all filter bits as don't care:
	MCP2510_Write_Can_ID(RXM0SIDH, 0,0);
	MCP2510_Write_Can_ID(RXM1SIDH, 0,0);
	// Anyway, set all filters to 0:
	MCP2510_Write_Can_ID(RXF0SIDH, 0, 0);
	MCP2510_Write_Can_ID(RXF1SIDH, 0, 0);
	MCP2510_Write_Can_ID(RXF2SIDH, 0, 0);
	MCP2510_Write_Can_ID(RXF3SIDH, 0, 0);
	MCP2510_Write_Can_ID(RXF4SIDH, 0, 0);
	MCP2510_Write_Can_ID(RXF5SIDH, 0, 0);

	MCP2510_Write(CLKCTRL, MODE_LOOPBACK| CLKEN | CLK8);//�ػ�ģʽ
    //�����������̨�豸����ʵ��Ļ�������ѡ��ػ�ģʽ
	//MCP2510_Write(CLKCTRL, MODE_NORMAL| CLKEN | CLK8);//��׼ģʽ
  
	// Clear, deactivate the three transmit buffers
	a = TXB0CTRL;
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 14; j++) {
			MCP2510_Write(a, 0);
			a++;
	        }
       	a += 2; // We did not clear CANSTAT or CANCTRL
	}
	// and the two receive buffers.
	MCP2510_Write(RXB0CTRL, 0);
	MCP2510_Write(RXB1CTRL, 0);

	// The two pins RX0BF and RX1BF are used to control two LEDs; set them as outputs and set them as 00.
	MCP2510_Write(BFPCTRL, 0x3C);
	
	//Open Interrupt
	MCP2510_Write(CANINTE, RX0IE|RX1IE);
}

/****************************************************************************
������˵����MCP2510ʵ�����
****************************************************************************/
void Test_MCP2510(void)
{
	int i;
	U32 id;
	unsigned char dlc;
	int rxRTR, isExt;
	int temp;
	
	U8 data_write[8]={1,2,3,4,5,6,7,8};
	U8 data_read[8] ;
	
   	Uart_Printf( "\nCAN BUS Test[ MCP2510 ], press ESC key to exit !\n" ) ;

	Init_MCP2510(BandRate_10kbps);
	Can_Setup();

    while( Uart_GetKey() != ESC_KEY )
    {
		Can_Write( 0x5a5, data_write, 8, FALSE, FALSE);
		
		while( (i=Can_Poll())==-1 ) ;
	
		for( temp=0; temp<8; temp++)  data_read[temp] = 0 ;
		temp = Can_Read(i, &id, data_read, &dlc, &rxRTR, &isExt);
		
		Uart_Printf( "  ID=0x%x\n",id );
		Uart_Printf( "Data=%x,%x,%x,%x,%x,%x,%x,%x\n",data_read[0],data_read[1],data_read[2],data_read[3],data_read[4],data_read[5],data_read[6],data_read[7] );
/*
		for( temp=0; temp<8; temp++)  data_read[temp] = 0 ;
		temp = Can_Read(1, &id, data_read, &dlc, &rxRTR, &isExt);
		Uart_Printf( "  ID=0x%x\n",id );
		Uart_Printf( "Data=%x,%x,%x,%x,%x,%x,%x,%x\n",data_read[0],data_read[1],data_read[2],data_read[3],data_read[4],data_read[5],data_read[6],data_read[7] );
*/		
		Delay(500);
	}

}
