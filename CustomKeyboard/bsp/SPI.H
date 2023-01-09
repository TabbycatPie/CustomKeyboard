
// #define SPI_INTERRUPT   1

#define  SPI_CK_SET( n ) (SPI0_CK_SE = n)                                     //SPI时钟设置函数 

/*******************************************************************************
* Function Name  : SPIMasterModeSet( UINT8 mode ) 
* Description    : SPI主机模式初始化
* Input          : UINT8 mode						 
* Output         : None
* Return         : None
*******************************************************************************/
void SPIMasterModeSet(UINT8 mode);

/*******************************************************************************
* Function Name  : CH554SPIInterruptInit()
* Description    : CH554SPI中断初始化
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void CH554SPIInterruptInit();

/*******************************************************************************
* Function Name  : CH554SPIMasterWrite(UINT8 dat)
* Description    : CH554硬件SPI写数据，主机模式
* Input          : UINT8 dat   数据
* Output         : None
* Return         : None
*******************************************************************************/
void CH554SPIMasterWrite(UINT8 dat);

/*******************************************************************************
* Function Name  : CH554SPIMasterRead( )
* Description    : CH554硬件SPI0读数据，主机模式
* Input          : None
* Output         : None
* Return         : UINT8 ret   
*******************************************************************************/
UINT8 CH554SPIMasterRead();

/*******************************************************************************
* Function Name  : SPISlvModeSet( ) 
* Description    : SPI从机模式初始化
* Input          : None						 
* Output         : None
* Return         : None
*******************************************************************************/
void SPISlvModeSet( );

/*******************************************************************************
* Function Name  : CH554SPISlvWrite(UINT8 dat)
* Description    : CH554硬件SPI写数据，从机模式
* Input          : UINT8 dat   数据
* Output         : None
* Return         : None
*******************************************************************************/
void CH554SPISlvWrite(UINT8 dat);

/*******************************************************************************
* Function Name  : CH554SPISlvRead( )
* Description    : CH554硬件SPI0读数据，从机模式
* Input          : None
* Output         : None
* Return         : UINT8 ret   
*******************************************************************************/
UINT8 CH554SPISlvRead();