
/*******************************************************************************
* Function Name  : WriteDataFlash(UINT16 Addr,PUINT8 buf,UINT8 len)
* Description    : DataFlash–¥
* Input          : UINT16 Addr£¨PUINT16 buf,UINT8 len 
* Output         : None 
* Return         : 
*******************************************************************************/
UINT8 WriteDataFlash(UINT8 Addr,PUINT8 buf,UINT8 len);

/*******************************************************************************
* Function Name  : ReadDataFlash(UINT8 Addr,UINT8 len,PUINT8 buf)
* Description    : ∂¡DataFlash
* Input          : UINT16 Addr PUINT8 buf
* Output         : None
* Return         : UINT8 l
*******************************************************************************/
UINT8 ReadDataFlash(UINT8 Addr,UINT8 len,PUINT8 buf);