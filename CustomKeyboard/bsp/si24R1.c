#include "si24R1.h"
#include "global.h"

unsigned char spi_send_rec_dat(unsigned char dat)
{
	SPI0_DATA = dat;                                                           
  while(S0_FREE == 0);													   //等待传输完成	
	return SPI0_DATA;
}

void SI24R1_Write_Reg(unsigned char regaddr,unsigned char dat)
{
	rf_CSN = 0;
	spi_send_rec_dat(regaddr);
	spi_send_rec_dat(dat);
	rf_CSN = 1;
}

void SI24R1_Write_Buf(unsigned char regaddr, unsigned char *pBuf, unsigned char datalen)
{
	unsigned char icnt = 0;
	rf_CSN = 0;
	spi_send_rec_dat(regaddr);
	for(icnt=0;icnt<datalen;icnt++)
	{
		spi_send_rec_dat(*pBuf++);
	}
	rf_CSN = 1;
}

void SI24R1_Read_Buf(unsigned char regaddr,unsigned char *pBuf,unsigned char datlen)
{
	unsigned char icnt = 0;
	rf_CSN = 0;
	spi_send_rec_dat(regaddr);
	for(icnt=0;icnt<datlen;icnt++)
	{
		pBuf[icnt] = spi_send_rec_dat(0xff);
	}
	rf_CSN = 1;
}


unsigned char SI24R1_Test(void)
{
	unsigned char icnt;
	unsigned char Addr[5]={0,0,0,0,0};
	unsigned char buf[5]={0XA1,0XA2,0XA3,0XA4,0XA5};
	SI24R1_Write_Buf(TX_ADDR|SPI_WRITE_REG,buf,5);
	SI24R1_Read_Buf(TX_ADDR,Addr,5);
	
	for(icnt=0;icnt<5;icnt++)
	{
		if(Addr[icnt] != buf[icnt])
		{
			return 1;
		}
	}
	return 0;
}
/************
 * 设定地址宽度
 ***********/
void SI24R1_SETUP_AW(unsigned char Widht)
{
	rf_CE = 0;
	SI24R1_Write_Reg(SPI_WRITE_REG|SETUP_AW,Widht);
}

/************
 * 设定发送地址
 ***********/
void SI24R1_SETUP_TXAddr(unsigned char *Addr)
{
	rf_CE = 0;
	SI24R1_Write_Buf(SPI_WRITE_REG|TX_ADDR,Addr,5);
}

/************
 * 设定接收地址
 ***********/
void SI24R1_SETUP_RXAddr(unsigned char *Addr,unsigned char Channel)
{
	rf_CE = 0;
	switch(Channel)
	{
		case 0: SI24R1_Write_Buf(SPI_WRITE_REG|RX_ADDR_P0,Addr,5); break;
		case 1: SI24R1_Write_Buf(SPI_WRITE_REG|RX_ADDR_P1,Addr,5); break;
		case 2: SI24R1_Write_Buf(SPI_WRITE_REG|RX_ADDR_P2,Addr,5); break;
		case 3: SI24R1_Write_Buf(SPI_WRITE_REG|RX_ADDR_P3,Addr,5); break;
		case 4: SI24R1_Write_Buf(SPI_WRITE_REG|RX_ADDR_P4,Addr,5); break;
		case 5: SI24R1_Write_Buf(SPI_WRITE_REG|RX_ADDR_P5,Addr,5); break;
	}
}

/************
 * 自动ACK通道
 ***********/
void SI24R1_Enable_Channel(unsigned char Channel)
{
	rf_CE = 0;
	SI24R1_Write_Reg(SPI_WRITE_REG|EN_AA,Channel);
}

/************
 * 接收通道使能
 ***********/
void SI24R1_Enable_RXChannel(unsigned char Channel)
{
	rf_CE = 0;
	SI24R1_Write_Reg(SPI_WRITE_REG|EN_RXADDR,Channel);
}

/************
 * 自动重传次数
 ***********/
void SI24R1_Auto_retrans(unsigned char retrans)
{
	rf_CE = 0;
	SI24R1_Write_Reg(SPI_WRITE_REG|SETUP_RETR,retrans);
}

/************
 * 射频信道
 ***********/
void SI24R1_RF_Channel(unsigned char Channel)
{
	rf_CE = 0;
	SI24R1_Write_Reg(SPI_WRITE_REG|RF_CH,Channel);
}

/************
 * 数据宽度
 * Widht：接收数据包长度
 * Channel ：配置的通道
 * 使用不定长长度需要提前配置动态负荷包
 ***********/
void SI24R1_Data_Widht(unsigned char Widht,unsigned char Channel)
{
	rf_CE = 0;
    switch(Channel)
	{
		case 0: SI24R1_Write_Reg(SPI_WRITE_REG|RX_PW_P0,Widht); break;
		case 1: SI24R1_Write_Reg(SPI_WRITE_REG|RX_PW_P1,Widht); break;
		case 2: SI24R1_Write_Reg(SPI_WRITE_REG|RX_PW_P2,Widht); break;
		case 3: SI24R1_Write_Reg(SPI_WRITE_REG|RX_PW_P3,Widht); break;
		case 4: SI24R1_Write_Reg(SPI_WRITE_REG|RX_PW_P4,Widht); break;
		case 5: SI24R1_Write_Reg(SPI_WRITE_REG|RX_PW_P5,Widht); break;
	}
}

/************
 * 空速，发射功率
 ***********/
void SI24R1_RF_Speed(unsigned char Speed,unsigned char dBm)
{
	rf_CE = 0;
	SI24R1_Write_Reg(SPI_WRITE_REG|RF_SETUP,(Speed|dBm));
}

/************
 * 清除中断
 * Status：当前获取到的中断位
 * 需要先调用SI24R1_Read_IRQ_Status() API以获取中断状态
 ***********/
void SI24R1_RF_ClearIRQ(unsigned char Status)
{
	rf_CE = 0;
	SI24R1_Write_Reg(SPI_WRITE_REG|uSTATUS,Status);
}

/************
 * 发送模式
 ***********/
void SI24R1_RF_TxMode(void)
{
	rf_CE = 0;
	SI24R1_Write_Reg(SPI_WRITE_REG|CONFIG,0x0e);
	rf_CE = 1;
}

/************
 * 接收模式
 ***********/
void SI24R1_RF_RxMode(void)
{
	rf_CE = 0;
	SI24R1_Write_Reg(SPI_WRITE_REG|CONFIG,0x0f);
	rf_CE = 1;
}

/************
 * 数据包特征设置
 ***********/
void SI24R1_RF_FEATURE(unsigned char Config)
{
	rf_CE = 0;
	SI24R1_Write_Reg((SPI_WRITE_REG|0x1D),Config);
}

/************
 * 获取中断标志
 ***********/
unsigned char SI24R1_Read_IRQ_Status(void)
{
	unsigned char IRQStatus=0;
	SI24R1_Read_Buf(uSTATUS,&IRQStatus,1);
	return IRQStatus;
}

/************
 * 清除发送缓存
 ***********/
void SI24R1_Clear_TXfifo(void)
{
	SI24R1_Write_Reg(FLUSH_TX,0xff);
}

/************
 * 清除接收缓存
 ***********/
void SI24R1_Clear_RXfifo(void)
{
	SI24R1_Write_Reg(FLUSH_RX,0xff);
}

/************
 * 发送数据包
 * padta:数据返回指针地址
 * Len:读取的长度
 * Ackflag:true自动回应ACK，false禁止回复ACK
 ***********/
void SI24R1_SendData(unsigned char* pdat,unsigned char Len,unsigned char Ackflag)
{
	rf_CE = 0;
	SI24R1_Clear_TXfifo();
	if(Ackflag == 1)
	{
		SI24R1_RF_FEATURE(0x00);
		SI24R1_Write_Buf(WR_TX_PLOAD,pdat,Len);
	}
	else
	{
		SI24R1_RF_FEATURE(0x01);
		SI24R1_Write_Buf(WR_TX_PLOAD_NOACK,pdat,Len);
	}
	SI24R1_RF_TxMode();
}

/************
 * 接收数据包
 * padta:数据返回指针地址
 * Len:读取的长度
 ***********/
void SI24R1_RecData(unsigned char* pdat,unsigned char Len)
{
	rf_CE = 0;
	SI24R1_Read_Buf(RD_RX_PLOAD,pdat,Len);
	SI24R1_Write_Reg(FLUSH_RX,0xff);
}



void SI24R1_Config_Init(void)
{
	unsigned char Addr[5] = {ADDRESS,0x02,0x03,0x04,0x05};
	SI24R1_SETUP_AW(0x03);
	SI24R1_SETUP_TXAddr((unsigned char*)&Addr);
	SI24R1_SETUP_RXAddr((unsigned char*)&Addr,0);
	SI24R1_Enable_Channel(0x01);
	SI24R1_Enable_RXChannel(0x01);
	SI24R1_Auto_retrans(0x15);
	SI24R1_RF_Channel(0x10);
	SI24R1_Data_Widht(RX_PLOAD_WIDTH,0);
	SI24R1_RF_Speed(0x20,0x06);
	SI24R1_RF_ClearIRQ(0x70);
	SI24R1_RF_RxMode();
}


