#include "usb.h"

#define Fullspeed
#define THIS_ENDP0_SIZE 		8
#define ENDP3_IN_SIZE 		    4


UINT8X	Ep0Buffer[THIS_ENDP0_SIZE+2]	_at_	0x0000;  // OUT&IN
UINT8X	Ep3Buffer[ENDP3_IN_SIZE+2] 	_at_ (0x0040);    // IN



UINT8   SetupReq,SetupLen,Ready = 0,Count,FLAG,UsbConfig;
PUINT8  pDescr;
USB_SETUP_REQ   SetupReqBuf;
UINT8	EnumOK,sleepOK = 0;

#define UsbSetupBuf     ((PUSB_SETUP_REQ)Ep0Buffer)

#pragma  NOAREGS

/*设备描述符*/
UINT8C DevDesc[] = 
{
	0x12,0x01,0x10,0x01,0x00,0x00,0x00,
    THIS_ENDP0_SIZE,
    (VID & 0xff), (VID >> 8),
    (PID & 0xff), (PID >> 8),
    0x01, 0x01,0x00, 0x00,0x00, 0x01
};


/*报表描述符*/
UINT8C MouseRepDesc[] =
{	
    0x05,0x01,
	0x09,0x02,
	0xA1,0x01,
	0x09,0x01,
    0xA1,0x00,
	0x05,0x09,
	0x19,0x01,
	0x29,0x03,
    0x15,0x00,
	0x25,0x01,
    0x75,0x01,
	0x95,0x03,
    0x81,0x02,
    0x75,0x05,
	0x95,0x01,
	0x81,0x03,
    0x05,0x01,
	0x09,0x30,
	0x09,0x31,
	0x09,0x38,
	0x15,0x81,
	0x25,0x7f,
	0x75,0x08,
	0x95,0x03,
    0x81,0x06,
	0xC0,
	0xC0
};

UINT8C CfgDesc[] =
{
	0x09,0x02,0x22,0x00,0x01,0x01,0x00,0xa0,0x32,	//配置描述符
	0x09,0x04,0x00,0x00,0x01,0x03,0x01,0x02,0x00,	//鼠标 接口描述符 
	0x09,0x21,0x10,0x01,0x00,0x01,0x22,sizeof(MouseRepDesc),0x00,	//鼠标 HID描述符
	0x07,0x05,0x83,0x03,0x04,0x00,0x01,				//鼠标 端点描述符
};

/* 鼠标数据 */
UINT8 HIDMouse[4] = {0x0,0x0,0x0,0x0};


/*******************************************************************************
* Description    : USB设备模式配置,设备模式启动，收发端点配置，中断开启
*******************************************************************************/
void USBDeviceInit(void)
{
	P1_MOD_OC = 0xff;
    P1_DIR_PU = 0xff;
	P1 = 0xff;
	P3 = 0xff;
    P3_MOD_OC = 0xFF;
    P3_DIR_PU = 0xFF;

	
	UEP1_T_LEN = 0;      //预使用发送长度一定要清空
	UEP2_T_LEN = 0;      //预使用发送长度一定要清空
    UEP3_T_LEN = 0;
	UEP4_T_LEN = 0;
	
	FLAG = 0;
	Ready = 0;
	
	IE_USB = 0;					// 关闭USB中断
	USB_CTRL = 0x00;          	// 先设定USB设备模式
	UDEV_CTRL = bUD_PD_DIS;   	// 禁止DP/DM下拉电阻

    UDEV_CTRL &= ~bUD_LOW_SPEED;
    USB_CTRL &= ~bUC_LOW_SPEED;
	
    UEP3_DMA = Ep3Buffer;
	UEP2_3_MOD |= bUEP3_TX_EN;
	UEP2_3_MOD &= ~bUEP3_RX_EN;
    UEP2_3_MOD &= ~bUEP3_BUF_MOD;
    UEP3_CTRL = bUEP_AUTO_TOG | UEP_T_RES_NAK;
	
	UEP0_DMA = Ep0Buffer;
    UEP0_CTRL = UEP_R_RES_ACK | UEP_T_RES_NAK;
 
	USB_DEV_AD = 0x00;
	USB_CTRL |= bUC_DEV_PU_EN | bUC_INT_BUSY | bUC_DMA_EN;// 启动USB设备及DMA，在中断期间中断标志未清除前自动返回NAK
	UDEV_CTRL |= bUD_PORT_EN;                             // 允许USB端口
	USB_INT_FG = 0xFF;                                    // 清中断标志
	USB_INT_EN = bUIE_SUSPEND | bUIE_TRANSFER | bUIE_BUS_RST;
	IE_USB = 1;

	T2MOD &= ~bT0_CLK;
	TMOD &= 0xf0;
	TMOD |= 0x01;
	TL0 = 0x3CB0 & 0xff;
	TH0 = (0x3CB0>>8) & 0xff;
	TR0 = 1;ET0 = 1;

	EA = 1;
}

void USBDevWakeup(void)
{
	UDEV_CTRL |= bUD_LOW_SPEED;
	mDelaymS(2);
	UDEV_CTRL &= ~bUD_LOW_SPEED;		
}

void Mouse_Send(void)
{
	if(sleepOK != 0)
	{
		USBDevWakeup();
	}
    
	while((UEP3_CTRL & MASK_UEP_T_RES) == UEP_T_RES_ACK);  
    memcpy( Ep3Buffer, HIDMouse, sizeof(HIDMouse)); 
    UEP3_T_LEN = sizeof(HIDMouse);                    
    UEP3_CTRL = UEP3_CTRL & ~ MASK_UEP_T_RES | UEP_T_RES_ACK;  
}

void DeviceInterrupt( void ) interrupt INT_NO_USB using 1
{
    UINT8 len;
    if(UIF_TRANSFER)     //USB传输完成标志
    {
        switch (USB_INT_ST & (MASK_UIS_TOKEN | MASK_UIS_ENDP))
        {
        case UIS_TOKEN_IN | 3:                                                  //endpoint 1# 中断端点上传
            UEP3_T_LEN = 0;                                                     //预使用发送长度一定要清空
			UEP3_CTRL = UEP3_CTRL & ~ MASK_UEP_T_RES | UEP_T_RES_NAK;           //默认应答NAK
            FLAG = 1;                                                           /*传输完成标志*/
            break;
		
        case UIS_TOKEN_SETUP | 0:  //SETUP事务  USB上报
            len = USB_RX_LEN;
            if(len == (sizeof(USB_SETUP_REQ)))
            {
                SetupLen = UsbSetupBuf->wLengthL;
				if(UsbSetupBuf->wLengthH || SetupLen > 0x7F )
                    SetupLen = 0x7F;   // 限制总长度
                len = 0;    // 默认为成功并且上传0长度
                SetupReq = UsbSetupBuf->bRequest;
				
                if ( ( UsbSetupBuf->bRequestType & USB_REQ_TYP_MASK ) != USB_REQ_TYP_STANDARD )/* HID类命令 */
                {
					len  = 0;///
					switch( SetupReq ) //HID请求
					{
						case 0x01:
							break;
						case 0x02:	break;
						case 0x03:	break;
						case 0x09:	if(UsbSetupBuf->bRequestType == 0x21) EnumOK = 1;	break;
						case 0x0A:	UEP0_T_LEN = 0;		break;
						case 0x0B:	break;
						default:	len = 0xFF; /*命令不支持*/					
							break;
					}
					
                }
                else	  //标准请求
                {
                    switch(SetupReq)          //请求码
                    {
                    case USB_GET_DESCRIPTOR:
                        switch(UsbSetupBuf->wValueH)
                        {
                        case USB_DESCR_TYP_DEVICE:    //设备描述符
                            pDescr = DevDesc;         //把设备描述符送到要发送的缓冲区
                            len = sizeof(DevDesc);
                            break;
                        case USB_DESCR_TYP_CONFIG:    //配置描述符
                            pDescr = CfgDesc;         //把设备描述符送到要发送的缓冲区
                            len = sizeof(CfgDesc);
                            break;
                        case USB_DESCR_TYP_REPORT:    //报表描述符
                            if(UsbSetupBuf->wIndexL == 0)
                            {
                                pDescr = MouseRepDesc;
                                len = sizeof(MouseRepDesc); 
                            }
                            else
                            {
                                len = 0xff;                                 //本程序只有3个接口，这句话正常不可能执行
                            }
                            break;
							
                        default:
                            len = 0xff;                //不支持的命令或者出错
                            break;
                        }
						if ( len == 0xff )
							break;	
                        if ( SetupLen > len )
                            SetupLen = len;    //限制总长度
                        len = SetupLen >= THIS_ENDP0_SIZE ? THIS_ENDP0_SIZE : SetupLen; //本次传输长度
                        memcpy(Ep0Buffer,pDescr,len);                        //加载上传数据
                        SetupLen -= len;
                        pDescr += len;
                        break;
                    case USB_SET_ADDRESS:
                        SetupLen = UsbSetupBuf->wValueL;                     //暂存USB设备地址
                        break;
                    case USB_GET_CONFIGURATION:
                        Ep0Buffer[0] = UsbConfig;
                        if ( SetupLen >= 1 )
                        {
                            len = 1;
                        }
                        break;
                    case USB_SET_CONFIGURATION:
                        UsbConfig = UsbSetupBuf->wValueL;
						if(UsbConfig)
						{
							Ready = 1;
						}
						else
							Ready = 0;
						break;
                    case 0x0A:
                        break;
                    case USB_CLEAR_FEATURE:                                            //Clear Feature
                        if ( ( UsbSetupBuf->bRequestType & USB_REQ_RECIP_MASK ) == USB_REQ_RECIP_ENDP )// 端点
                        {
                            switch( UsbSetupBuf->wIndexL )
                            {
								case 0x84:
									UEP4_CTRL = UEP4_CTRL & ~ ( bUEP_T_TOG | MASK_UEP_T_RES ) | UEP_T_RES_NAK;
									break;
								case 0x83:
									UEP3_CTRL = UEP3_CTRL & ~ ( bUEP_T_TOG | MASK_UEP_T_RES ) | UEP_T_RES_NAK;
									break;
								case 0x82:
									UEP2_CTRL = UEP2_CTRL & ~ ( bUEP_T_TOG | MASK_UEP_T_RES ) | UEP_T_RES_NAK;
									break;
								case 0x81:
									UEP1_CTRL = UEP1_CTRL & ~ ( bUEP_T_TOG | MASK_UEP_T_RES ) | UEP_T_RES_NAK;
									break;
								case 0x01:
									UEP1_CTRL = UEP1_CTRL & ~ ( bUEP_R_TOG | MASK_UEP_R_RES ) | UEP_R_RES_ACK;
									break;
								case 0x02:
									UEP2_CTRL = UEP2_CTRL & ~ ( bUEP_R_TOG | MASK_UEP_R_RES ) | UEP_R_RES_ACK;
									break;
								case 0x03:
									UEP3_CTRL = UEP3_CTRL & ~ ( bUEP_R_TOG | MASK_UEP_R_RES ) | UEP_R_RES_ACK;
									break;
								case 0x04:
									UEP4_CTRL = UEP4_CTRL & ~ ( bUEP_R_TOG | MASK_UEP_R_RES ) | UEP_R_RES_ACK;
									break;
								default:
									len = 0xFF;                                            // 不支持的端点
									break;
                            }
                        }
                        if ( ( UsbSetupBuf->bRequestType & USB_REQ_RECIP_MASK ) == USB_REQ_RECIP_DEVICE )// 设备
                        {
							break;
                        }													
                        else
                        {
                            len = 0xFF;                                                // 不是端点不支持
                        }
                        break;
                    case USB_SET_FEATURE:                                              /* Set Feature */
                        if( ( UsbSetupBuf->bRequestType & 0x1F ) == 0x00 )             /* 设置设备 */
                        {
                            if( ( ( ( UINT16 )UsbSetupBuf->wValueH << 8 ) | UsbSetupBuf->wValueL ) == 0x01 )
                            {
                                if( CfgDesc[ 7 ] & 0x20 )
                                {
                                    /* 设置唤醒使能标志 */
                                }
                                else
                                {
                                    len = 0xFF;                                        /* 操作失败 */
                                }
                            }
                            else
                            {
                                len = 0xFF;                                            /* 操作失败 */
                            }
                        }
                        else if( ( UsbSetupBuf->bRequestType & 0x1F ) == 0x02 )        /* 设置端点 */
                        {
                            if( ( ( ( UINT16 )UsbSetupBuf->wValueH << 8 ) | UsbSetupBuf->wValueL ) == 0x00 )
                            {
                                switch( ( ( UINT16 )UsbSetupBuf->wIndexH << 8 ) | UsbSetupBuf->wIndexL )
                                {
									case 0x84:
										UEP4_CTRL = UEP4_CTRL & (~bUEP_T_TOG) | UEP_T_RES_STALL;/* 设置端点3 IN STALL */
										break;
									case 0x83:
										UEP3_CTRL = UEP3_CTRL & (~bUEP_T_TOG) | UEP_T_RES_STALL;/* 设置端点3 IN STALL */
										break;
									case 0x82:
										UEP2_CTRL = UEP2_CTRL & (~bUEP_T_TOG) | UEP_T_RES_STALL;/* 设置端点2 IN STALL */
										break;
									case 0x02:
										UEP2_CTRL = UEP2_CTRL & (~bUEP_R_TOG) | UEP_R_RES_STALL;/* 设置端点2 OUT Stall */
										break;
									case 0x81:
										UEP1_CTRL = UEP1_CTRL & (~bUEP_T_TOG) | UEP_T_RES_STALL;/* 设置端点1 IN STALL */
										break;
									default:
										len = 0xFF;                               //操作失败
										break;
                                }
                            }
                            else
                            {
                                len = 0xFF;                                   //操作失败
                            }
                        }
                        else
                        {
                            len = 0xFF;                                      //操作失败
                        }
                        break;
                    case USB_GET_STATUS:
                        Ep0Buffer[0] = 0x00;
                        Ep0Buffer[1] = 0x00;
                        if ( SetupLen >= 2 )
                        {
                            len = 2;
                        }
                        else
                        {
                            len = SetupLen;
                        }
                        break;
                    default:
                        len = 0xff;                                           //操作失败
                        break;
                    }
                }
            }
            else
            {
                len = 0xff;                                                   //包长度错误
            }
            if(len == 0xff)
            {
                SetupReq = 0xFF;
                UEP0_CTRL = bUEP_R_TOG | bUEP_T_TOG | UEP_R_RES_STALL | UEP_T_RES_STALL;//STALL
            }
            else if(len <= THIS_ENDP0_SIZE)       //上传数据或者状态阶段返回0长度包
            {
                UEP0_T_LEN = len;
                UEP0_CTRL = bUEP_R_TOG | bUEP_T_TOG | UEP_R_RES_ACK | UEP_T_RES_ACK;//默认数据包是DATA1，返回应答ACK
            }
            else
            {
                UEP0_T_LEN = 0;  //虽然尚未到状态阶段，但是提前预置上传0长度数据包以防主机提前进入状态阶段
                UEP0_CTRL = bUEP_R_TOG | bUEP_T_TOG | UEP_R_RES_ACK | UEP_T_RES_ACK;//默认数据包是DATA1,返回应答ACK
            }
            break;
        case UIS_TOKEN_IN | 0:                                               //endpoint0 IN
            switch(SetupReq)
            {
			case USB_GET_DESCRIPTOR:
				len = SetupLen >= THIS_ENDP0_SIZE ? THIS_ENDP0_SIZE : SetupLen;    //本次传输长度
				memcpy( Ep0Buffer, pDescr, len );                            //加载上传数据
				SetupLen -= len;
				pDescr += len;
				UEP0_T_LEN = len;
				UEP0_CTRL ^= bUEP_T_TOG;                                     //同步标志位翻转
			break;
			case HID_GET_REPORT:
                len = SetupLen >= THIS_ENDP0_SIZE ? THIS_ENDP0_SIZE : SetupLen; //本次传输长度
                memcpy(Ep0Buffer, pDescr, len);                                 //加载上传数据
                SetupLen -= len;
                pDescr += len;
                UEP0_T_LEN = len;
                UEP0_CTRL ^= bUEP_T_TOG; //同步标志位翻转
                break;
            case USB_SET_ADDRESS:
                USB_DEV_AD = USB_DEV_AD & bUDA_GP_BIT | SetupLen;
                UEP0_CTRL = UEP_R_RES_ACK | UEP_T_RES_NAK;
                break;
            default:
                UEP0_T_LEN = 0;           //状态阶段完成中断或者是强制上传0长度数据包结束控制传输
                UEP0_CTRL = UEP_R_RES_ACK | UEP_T_RES_NAK;
                break;
            }
            break;
        case UIS_TOKEN_OUT | 0:  // endpoint0 OUT
            len = USB_RX_LEN;
			UEP0_T_LEN = 0;
            if(SetupReq == 0x09)
            {
                if(Ep0Buffer[0])
                {
                    //printf("Light on Num Lock LED!\n");
                }
                else if(Ep0Buffer[0] == 0)
                {
                    //printf("Light off Num Lock LED!\n");
                }				
            }
            UEP0_CTRL ^= bUEP_R_TOG;                                     //同步标志位翻转						
            break;
        default:
            break;
        }
        UIF_TRANSFER = 0;                                                 //写0清空中断
    }
    if(UIF_BUS_RST)                                                       //设备模式USB总线复位中断
    {
        UEP0_CTRL = UEP_R_RES_ACK | UEP_T_RES_NAK;
        UEP1_CTRL = bUEP_AUTO_TOG | UEP_R_RES_ACK | UEP_T_RES_NAK;
        UEP2_CTRL = bUEP_AUTO_TOG | UEP_R_RES_ACK | UEP_T_RES_NAK;
		UEP3_CTRL = bUEP_AUTO_TOG | UEP_R_RES_ACK | UEP_T_RES_NAK;
		UEP4_CTRL = bUEP_AUTO_TOG | UEP_R_RES_ACK | UEP_T_RES_NAK;
        USB_DEV_AD = 0x00;
        UIF_SUSPEND = 0;
        UIF_TRANSFER = 0;
		UIF_BUS_RST = 0;                                                 //清中断标志
    }
    if (UIF_SUSPEND)                                                     //USB总线挂起/唤醒完成
    {
        UIF_SUSPEND = 0;
        if ( USB_MIS_ST & bUMS_SUSPEND )
        {
			sleepOK = 1;
			WAKE_CTRL = 0x00;
        }
		else
		{
			//Ready = 1;
			sleepOK = 0;
			WAKE_CTRL = 0x00;
		}
    }
    else
        USB_INT_FG = 0xFF;
}


extern void run_timer_50ms(void);

void mTimer0Interrupt( void ) interrupt INT_NO_TMR0 using 1
{
	

	
	if(Ready == 1)
	{
		run_timer_50ms();
	}
	
	TL0 = 0x3CB0 & 0xff;
	TH0 = (0x3CB0>>8) & 0xff; 

}

