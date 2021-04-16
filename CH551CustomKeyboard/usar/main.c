#include "CH552.H"                                                      
#include "Debug.H"
#include <string.h>
#include <CH552.H>

//#include "pn297_L.h"
//#include "DataFlash.h"
//#include <stdio.h>

#define Fullspeed
#define THIS_ENDP0_SIZE         DEFAULT_ENDP0_SIZE

UINT8X  Ep0Buffer[8>(THIS_ENDP0_SIZE+2)?8:(THIS_ENDP0_SIZE+2)] _at_ 0x0000;    //端点0 OUT&IN缓冲区，必须是偶地址
UINT8X  Ep1Buffer[64>(MAX_PACKET_SIZE+2)?64:(MAX_PACKET_SIZE+2)] _at_ 0x000a;  //端点1 IN缓冲区,必须是偶地址
UINT8X  Ep2Buffer[64>(MAX_PACKET_SIZE+2)?64:(MAX_PACKET_SIZE+2)] _at_ 0x0050;  //端点2 IN缓冲区,必须是偶地址
UINT8   SetupReq,SetupLen,Ready,Count,FLAG,UsbConfig;
PUINT8  pDescr;                                                                //USB配置标志
USB_SETUP_REQ   SetupReqBuf;                                                   //暂存Setup包


#define UsbSetupBuf     ((PUSB_SETUP_REQ)Ep0Buffer)
#define DEBUG 0

#pragma  NOAREGS
/*设备描述符*/
UINT8C DevDesc[18] = {
	0x12,
	0x01,	/* 设备描述符 */
	
	0x10,	/*bcdUSB 1.1*/
	0x01,
	
	0x00,
	0x00,
	0x00,
	THIS_ENDP0_SIZE,
	0x3d,	/* VID idVendor (0x0483)*/
	0x40,
	
	0x07,	/* PID idProduct = 0x5710*/
	0x20,
	
	0x00,	/*bcdDevice rel. 2.00*/
	0x00,
	
	0x00,
	0x00,
	0x00,
	0x01
};

UINT8C CfgDesc[] =		//34
{
//    0x09,0x02,0x3b,0x00,0x02,0x01,0x00,0xA0,0x32,             //配置描述符
//    0x09,0x04,0x00,0x00,0x01,0x03,0x01,0x01,0x00,             //接口描述符,键盘
//    0x09,0x21,0x11,0x01,0x00,0x01,0x22,0x3e,0x00,             //HID类描述符
//    0x07,0x05,0x81,0x03,0x08,0x00,0x0a,                       //端点描述符
//    0x09,0x04,0x01,0x00,0x01,0x03,0x01,0x02,0x00,             //接口描述符,鼠标
//    0x09,0x21,0x10,0x01,0x00,0x01,0x22,0x34,0x00,             //HID类描述符
//    0x07,0x05,0x82,0x03,0x04,0x00,0x0a                        //端点描述符
//////////////////////////////////////////////////
/***************** 配置描述符 *******************/
	0x09,	/* bLength: 长度，设备字符串的长度为9字节 */
	0x02,	/* 类型，表明配置描述符类型 */
	0x3b,	//配置描述符总长度
	0x00,
	0x02,	/* 接口数量  接口和端点是不用的*/
	0x01,	/*bConfigurationValue: Configuration value*/
	0x00,	/* 该配置的字符串的索引值，该值为0表示没有字符串 */
	0xA0,	/*bmAttributes: Self powered */
	0x32,	/* 从总线上获得电源大小，最大配置100ma */
	
//////////////////////////////////////////////////
/************** 键盘接口的描述符 ****************/
	0x09,	/* 接口描述符的长度为9字节 */
	0x04,	/* 表面接口描述符 */
	0x00,	/* 该接口编号 */
	0x00,	/* 该接口得备用编号 */
	0x01,	/* 该接口所使用端点数量 */
	0x03,	/* 该接口所使用的类   键盘属于HID */
	0x01,	/* 该接口所用的子类 1=BOOT, 0=no boot */
	0x01,	/* 键盘是1   鼠标是2  0是自定义设备 */
	0x00,   /* 该接口字符串的索引  一般都为0 */

//////////////////////////////////////////////////
/************** 键盘HID的描述符 *****************/
	0x09,	/* bLength: 长度，HID描述符的长度为9字节 */
	0x21,	/* HID的描述符类型 */
	0x11,	/* HID协议的版本 */
	0x01,
	0x00,	/* 国家代号 */
	0x01,	/* 下级描述符的数量 */
	0x22,	/* 下级描述符的类型 */
	0x3e,	/* 下一级描述符的长度 */
	0x00,

/////////////////////////////////////////////////////////////////
/************** 键盘输入端口描述符(端点描述符) *****************/
	0x07,	/* 端点描述符的长度为7字节 */
	0x05,	/* 端点描述符的类型 */
	0x81,	/* 该端点(输入)的地址,D7:0(OUT),1(IN),D6~D4:保留,D3~D0:端点号 */
	0x03,	/* 端点的属性为为中断端点. D0~D1表示传输类型:0(控制传输),
			 1(等时传输),2(批量传输),3(中断传输) 非等时传输端点:D2~D7:保留为0 等时传输端点： 
			 D2~D3表示同步的类型:0(无同步),1(异步),2(适配),3(同步) D4~D5表示用途:0(数据端点),
			 1(反馈端点),2(暗含反馈的数据端点),3(保留)，D6~D7:保留 */
	0x08,	/* 该端点支持的最大包长度 */
	0x00,
	0x01,	/* 轮询间隔 bInterval: Polling Interval (6 ms)*/

//////////////////////////////////////////////////
/************** 鼠标接口的描述符 ****************/
	0x09,	/* 接口描述符的长度为9字节 */
	0x04,	/* 表面接口描述符 */
	0x01,	/* 该接口编号 */
	0x00,	/* 该接口得备用编号 */
	0x01,	/* 该接口所使用端点数量 */
	0x03,	/* 该接口所使用的类   鼠标属于HID */
	0x01,	/* 该接口所用的子类 1=BOOT, 0=no boot */
	0x02,	/* 键盘是1   鼠标是2  0是自定义设备 */
	0x00,   /* 该接口字符串的索引  一般都为0 */

/////////////////////////////////////////////
/************** 鼠标HID描述符 ****************/
	0x09,	/* bLength: 长度，HID描述符的长度为9字节 */
	0x21,	/* HID的描述符类型 */
	0x10,	/* HID协议的版本 */
	0x01,
	0x00,	/* 国家代号 */
	0x01,	/* 下级描述符的数量 */
	0x22,	/* 下级描述符的类型 */
	0x34,	/* 下一集描述符的长度 */ //0x34  0x36
	0x00,

///////////////////////////////////////////////////////////////
/************** 鼠标输入端口描述符(端点描述符) *****************/
	0x07,	/* 端点描述符的长度为7字节 */
	0x05,	/* 端点描述符的类型 */
	0x82,	/* 该端点(输入)的地址,D7:0(OUT),1(IN),D6~D4:保留,D3~D0:端点号 */
	0x03,	/*端点的属性为为中断端点. D0~D1表示传输类型:0(控制传输),
			 1(等时传输),2(批量传输),3(中断传输) 非等时传输端点:D2~D7:保留为0 等时传输端点： 
			 D2~D3表示同步的类型:0(无同步),1(异步),2(适配),3(同步) D4~D5表示用途:0(数据端点),
			 1(反馈端点),2(暗含反馈的数据端点),3(保留)，D6~D7:保留*/
	0x04,	/* 该端点支持的最大包长度 */
	0x00,
	0x01    /* 轮询间隔 bInterval: Polling Interval (32 ms)*/	
	
};
/*字符串描述符*/
/*HID类报表描述符*/
UINT8C KeyRepDesc[62] =
{
	0x05,0x01,	// USAGE_PAGE (Generic Desktop)	//62
	0x09,0x06,	// USAGE (Keyboard)
	0xA1,0x01,	// COLLECTION (Application)

	0x05,0x07,	//   USAGE_PAGE (Keyboard)
	0x19,0xe0,	//   USAGE_MINIMUM (Keyboard LeftControl)
	0x29,0xe7,	//   USAGE_MAXIMUM (Keyboard Right GUI)
	0x15,0x00,	//   LOGICAL_MINIMUM (0)
	0x25,0x01,	//   LOGICAL_MAXIMUM (1)
	0x75,0x01,	//   REPORT_SIZE (1)
	0x95,0x08,	//   REPORT_COUNT (8)
	0x81,0x02,	//   INPUT (Data,Var,Abs)

	0x95,0x01,	//   REPORT_COUNT (1)
	0x75,0x08,	//   REPORT_SIZE (8)
	//
	0x81,0x01,	//   INPUT (Cnst,Var,Abs) 
	0x95,0x03,	//   REPORT_COUNT (3)	   

	0x75,0x01,	//   REPORT_SIZE (1)	  
	0x05,0x08,	//   USAGE_PAGE (LEDs)
	0x19,0x01,	//   USAGE_MINIMUM (Num Lock)
	0x29,0x03,	//   USAGE_MAXIMUM (Kana)
	0x91,0x02,	//   Output (Data,Var,Abs,NWrp,Lin,Pref,NNul,NVol,Bit)
	0x95,0x05,	//   REPORT_COUNT (1)
	0x75,0x01,	//   REPORT_SIZE (3)
	0x91,0x01,	//   Output (Cnst,Ary,Abs,NWrp,Lin,Pref,NNul,NVol,Bit)
	0x95,0x06,	//   REPORT_COUNT (6)
	0x75,0x08,	//   REPORT_SIZE (8)
	0x26,0xff,0x00,		//Logical Maximum (255)
	0x05,0x07,	//   USAGE_PAGE (Keyboard/Keypad)
	0x19,0x00,	//   USAGE_MINIMUM (Undefined)
	0x29,0x91,	//   USAGE_MAXIMUM (Keyboard LANG2)
	0x81,0x00,	//   INPUT (Data,Ary,Abs)
	0xC0		//	 End Collection
};
UINT8C MouseRepDesc[52] =
{
    0x05,0x01,0x09,0x02,0xA1,0x01,0x09,0x01,
    0xA1,0x00,0x05,0x09,0x19,0x01,0x29,0x03,
    0x15,0x00,0x25,0x01,0x75,0x01,0x95,0x03,
    0x81,0x02,0x75,0x05,0x95,0x01,0x81,0x01,
    0x05,0x01,0x09,0x30,0x09,0x31,0x09,0x38,
    0x15,0x81,0x25,0x7f,0x75,0x08,0x95,0x03,
    0x81,0x06,0xC0,0xC0
};
/*鼠标数据*/
UINT8 HIDMouse[4] = {0x0,0x0,0x0,0x0};
/*键盘数据*/
UINT8 HIDKey[8] = {0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0};

/*******************************************************************************
* Function Name  : CH552SoftReset()
* Description    : CH552软复位
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
//void CH552SoftReset( )
//{
//    SAFE_MOD = 0x55;
//    SAFE_MOD = 0xAA;
//    GLOBAL_CFG	|=bSW_RESET;
//}

/*******************************************************************************
* Function Name  : CH552USBDevWakeup()
* Description    : CH552设备模式唤醒主机，发送K信号
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
//void CH552USBDevWakeup( )
//{
//#ifdef Fullspeed
//	UDEV_CTRL |= bUD_LOW_SPEED;
//	mDelaymS(2);
//	UDEV_CTRL &= ~bUD_LOW_SPEED;		
//#else
//	UDEV_CTRL &= ~bUD_LOW_SPEED;
//	mDelaymS(2);
//	UDEV_CTRL |= bUD_LOW_SPEED;	
//#endif
//}

/*******************************************************************************
* Function Name  : USBDeviceInit()
* Description    : USB设备模式配置,设备模式启动，收发端点配置，中断开启
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void USBDeviceInit()
{
	IE_USB = 0;	//关闭USB中断
	USB_CTRL = 0x00;          // 先设定USB设备模式
	UDEV_CTRL = bUD_PD_DIS;   // 禁止DP/DM下拉电阻
#ifndef Fullspeed
    UDEV_CTRL |= bUD_LOW_SPEED;                                                //选择低速1.5M模式
    USB_CTRL |= bUC_LOW_SPEED;
#else
    UDEV_CTRL &= ~bUD_LOW_SPEED;                                               //选择全速12M模式，默认方式
    USB_CTRL &= ~bUC_LOW_SPEED;
#endif
	
    UEP2_DMA = Ep2Buffer;                                                      //端点2数据传输地址
    UEP2_3_MOD = UEP2_3_MOD & ~bUEP2_BUF_MOD | bUEP2_TX_EN;                    //端点2发送使能 64字节缓冲区
    UEP2_CTRL = bUEP_AUTO_TOG | UEP_T_RES_NAK;                                 //端点2自动翻转同步标志位，IN事务返回NAK
    UEP0_DMA = Ep0Buffer;                                                      //端点0数据传输地址
    UEP4_1_MOD &= ~(bUEP4_RX_EN | bUEP4_TX_EN);                                //端点0单64字节收发缓冲区
    UEP0_CTRL = UEP_R_RES_ACK | UEP_T_RES_NAK;                                 //OUT事务返回ACK，IN事务返回NAK
    UEP1_DMA = Ep1Buffer;                                                      //端点1数据传输地址
    UEP4_1_MOD = UEP4_1_MOD & ~bUEP1_BUF_MOD | bUEP1_TX_EN;                    //端点1发送使能 64字节缓冲区
    UEP1_CTRL = bUEP_AUTO_TOG | UEP_T_RES_NAK;                                 //端点1自动翻转同步标志位，IN事务返回NAK	
		
	USB_DEV_AD = 0x00;
	USB_CTRL |= bUC_DEV_PU_EN | bUC_INT_BUSY | bUC_DMA_EN;                      // 启动USB设备及DMA，在中断期间中断标志未清除前自动返回NAK
	UDEV_CTRL |= bUD_PORT_EN;                                                  // 允许USB端口
	USB_INT_FG = 0xFF;                                                         // 清中断标志
	USB_INT_EN = bUIE_SUSPEND | bUIE_TRANSFER | bUIE_BUS_RST;
	IE_USB = 1;
}
/*******************************************************************************
* Function Name  : Enp1IntIn()
* Description    : USB设备模式端点1的中断上传
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void Enp1IntIn( )
{
    memcpy( Ep1Buffer, HIDKey, sizeof(HIDKey));                              //加载上传数据
    UEP1_T_LEN = sizeof(HIDKey);                                             //上传数据长度
    UEP1_CTRL = UEP1_CTRL & ~ MASK_UEP_T_RES | UEP_T_RES_ACK;                //有数据时上传数据并应答ACK
}
/*******************************************************************************
* Function Name  : Enp2IntIn()
* Description    : USB设备模式端点2的中断上传
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void Enp2IntIn( )
{
    memcpy( Ep2Buffer, HIDMouse, sizeof(HIDMouse));                              //加载上传数据
    UEP2_T_LEN = sizeof(HIDMouse);                                              //上传数据长度
    UEP2_CTRL = UEP2_CTRL & ~ MASK_UEP_T_RES | UEP_T_RES_ACK;                  //有数据时上传数据并应答ACK
}
/*******************************************************************************
* Function Name  : DeviceInterrupt()
* Description    : CH552USB中断处理函数
*******************************************************************************/
void    DeviceInterrupt( void ) interrupt INT_NO_USB                     //USB中断服务程序,使用寄存器组1
{
    UINT8 len = 0;
    if(UIF_TRANSFER)                                                            //USB传输完成标志
    {
        switch (USB_INT_ST & (MASK_UIS_TOKEN | MASK_UIS_ENDP))
        {
        case UIS_TOKEN_IN | 2:                                                  //endpoint 2# 中断端点上传
            UEP2_T_LEN = 0;                                                     //预使用发送长度一定要清空
//            UEP1_CTRL ^= bUEP_T_TOG;                                          //如果不设置自动翻转则需要手动翻转
            UEP2_CTRL = UEP2_CTRL & ~ MASK_UEP_T_RES | UEP_T_RES_NAK;           //默认应答NAK
		FLAG = 1;
            break;
        case UIS_TOKEN_IN | 1:                                                  //endpoint 1# 中断端点上传
            UEP1_T_LEN = 0;                                                     //预使用发送长度一定要清空
//            UEP2_CTRL ^= bUEP_T_TOG;                                          //如果不设置自动翻转则需要手动翻转
            UEP1_CTRL = UEP1_CTRL & ~ MASK_UEP_T_RES | UEP_T_RES_NAK;           //默认应答NAK
            FLAG = 1;                                                           /*传输完成标志*/
            break;
        case UIS_TOKEN_SETUP | 0:                                                //SETUP事务
            len = USB_RX_LEN;
            if(len == (sizeof(USB_SETUP_REQ)))
            {
                SetupLen = UsbSetupBuf->wLengthL;
                if(UsbSetupBuf->wLengthH || SetupLen > 0x7F )
                {
                    SetupLen = 0x7F;    // 限制总长度
                }
                len = 0;                                                        // 默认为成功并且上传0长度
                SetupReq = UsbSetupBuf->bRequest;								
                if ( ( UsbSetupBuf->bRequestType & USB_REQ_TYP_MASK ) != USB_REQ_TYP_STANDARD )/* HID类命令 */
                {
					switch( SetupReq ) 
					{
						case 0x01://GetReport
							break;
						case 0x02://GetIdle
							break;	
						case 0x03://GetProtocol
							break;				
						case 0x09://SetReport										
							break;
						case 0x0A://SetIdle
							break;	
						case 0x0B://SetProtocol
							break;
						default:
							len = 0xFF;  								   /*命令不支持*/					
							break;
					}	
                }
                else
                {                                                           //标准请求
                    switch(SetupReq)                                        //请求码
                    {
                    case USB_GET_DESCRIPTOR:
                        switch(UsbSetupBuf->wValueH)
                        {
                        case 1:                                             //设备描述符
                            pDescr = DevDesc;                               //把设备描述符送到要发送的缓冲区
                            len = sizeof(DevDesc);
                            break;
                        case 2:                                             //配置描述符
                            pDescr = CfgDesc;                               //把设备描述符送到要发送的缓冲区
                            len = sizeof(CfgDesc);
                            break;
                        case 0x22:                                          //报表描述符
                            if(UsbSetupBuf->wIndexL == 0)                   //接口0报表描述符
                            {
                                pDescr = KeyRepDesc;                        //数据准备上传
                                len = sizeof(KeyRepDesc);
                            }
//不枚举鼠标
                            else if(UsbSetupBuf->wIndexL == 1)              //接口1报表描述符
                            {
                                pDescr = MouseRepDesc;                      //数据准备上传
                                len = sizeof(MouseRepDesc);                                
                            }
                            else
                            {
                                len = 0xff;                                 //本程序只有2个接口，这句话正常不可能执行
                            }
                            break;
                        default:
                            len = 0xff;                                     //不支持的命令或者出错
                            break;
                        }
                        if ( SetupLen > len )
                        {
                            SetupLen = len;    //限制总长度
                        }
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
#ifdef DE_PRINTF 							
							//printf("SET CONFIG.\n");
#endif
							Ready = 1;                                      //set config命令一般代表usb枚举完成的标志
						}
						break;
                    case 0x0A:
                        break;
                    case USB_CLEAR_FEATURE:                                            //Clear Feature
                        if ( ( UsbSetupBuf->bRequestType & USB_REQ_RECIP_MASK ) == USB_REQ_RECIP_ENDP )// 端点
                        {
                            switch( UsbSetupBuf->wIndexL )
                            {
                            case 0x82:
                                UEP2_CTRL = UEP2_CTRL & ~ ( bUEP_T_TOG | MASK_UEP_T_RES ) | UEP_T_RES_NAK;
                                break;
                            case 0x81:
                                UEP1_CTRL = UEP1_CTRL & ~ ( bUEP_T_TOG | MASK_UEP_T_RES ) | UEP_T_RES_NAK;
                                break;
                            case 0x01:
                                UEP1_CTRL = UEP1_CTRL & ~ ( bUEP_R_TOG | MASK_UEP_R_RES ) | UEP_R_RES_ACK;
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
            else if(len)                                                //上传数据或者状态阶段返回0长度包
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
            case USB_SET_ADDRESS:
                USB_DEV_AD = USB_DEV_AD & bUDA_GP_BIT | SetupLen;
                UEP0_CTRL = UEP_R_RES_ACK | UEP_T_RES_NAK;
                break;
            default:
                UEP0_T_LEN = 0;                                              //状态阶段完成中断或者是强制上传0长度数据包结束控制传输
                UEP0_CTRL = UEP_R_RES_ACK | UEP_T_RES_NAK;
                break;
            }
            break;
        case UIS_TOKEN_OUT | 0:  // endpoint0 OUT
            len = USB_RX_LEN;
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
        UEP1_CTRL = bUEP_AUTO_TOG | UEP_R_RES_ACK;
        UEP2_CTRL = bUEP_AUTO_TOG | UEP_R_RES_ACK | UEP_T_RES_NAK;
        USB_DEV_AD = 0x00;
        UIF_SUSPEND = 0;
        UIF_TRANSFER = 0;
        UIF_BUS_RST = 0;                                                 //清中断标志
    }
    if (UIF_SUSPEND)                                                     //USB总线挂起/唤醒完成
    {
        UIF_SUSPEND = 0;
        if ( USB_MIS_ST & bUMS_SUSPEND )                                 //挂起
        {
#if DEBUG
           // printf( "zz" );                                              //睡眠状态
#endif
//             while ( XBUS_AUX & bUART0_TX );                              //等待发送完成
//             SAFE_MOD = 0x55;
//             SAFE_MOD = 0xAA;
//             WAKE_CTRL = bWAK_BY_USB | bWAK_RXD0_LO;                      //USB或者RXD0有信号时可被唤醒
//             PCON |= PD;                                                  //睡眠
//             SAFE_MOD = 0x55;
//             SAFE_MOD = 0xAA;
//             WAKE_CTRL = 0x00;
        }
    }
    else {                                                               //意外的中断,不可能发生的情况
        USB_INT_FG = 0xFF;                                               //清中断标志
//      printf("UnknownInt  N");
    }
}



/*
	上报按键数据
*/

void HIDValueHandle(UINT8 i)
{
	switch(i)
	{
		//键盘数据上传示例
		case '1':
			FLAG = 0;
//			HIDKey[0] = 0x3D;   //F4
//			HIDKey[3] = 0;
//			Enp1IntIn();
			HIDMouse[0] = 0x01;
			HIDMouse[1] = 0x0;
			HIDMouse[2] = 0x0;
			HIDMouse[3] = 0x0;
			Enp2IntIn();
			while(FLAG == 0)
			{
				;    /*等待上一包传输完成*/
			}
			break;
		case '2':
			FLAG = 0;
//			HIDKey[0] = 0x3D;   //F4
//			HIDKey[3] = 0;
//			Enp1IntIn();
			HIDMouse[0] = 0x02;
			HIDMouse[1] = 0x0;
			HIDMouse[2] = 0x0;
			HIDMouse[3] = 0x0;
			Enp2IntIn();
			while(FLAG == 0)
			{
				;    /*等待上一包传输完成*/
			}
			break;
		case '7':
			FLAG = 0;
//			HIDKey[0] = 0;      //按键结束
//			HIDKey[3] = 0;
//			Enp1IntIn();
			HIDMouse[0] = 0x0;
			HIDMouse[1] = 0x0;
			HIDMouse[2] = 0x0;
			HIDMouse[3] = 0x0;
			Enp2IntIn();
			while(FLAG == 0)
			{
				;    /*等待上一包传输完成*/
			}
			break;
		default:                                                          //其他
			UEP1_CTRL = UEP1_CTRL & ~ MASK_UEP_T_RES | UEP_T_RES_NAK;     //默认应答NAK
			UEP2_CTRL = UEP2_CTRL & ~ MASK_UEP_T_RES | UEP_T_RES_NAK;     //默认应答NAK
			break;
	}
}


//sbit Key1 = P3^3;
sbit Key1 = P3^2;
sbit Key2 = P1^4;


void main()
{
    CfgFsys( );                    //CH552时钟选择配置
    mDelaymS(50);                 //修改主频等待内部晶振稳定,必加

	/* 设置P1口为准双向IO口 */
	P1_MOD_OC = 0xff;
	P1_DIR_PU = 0xff;
	
	P3_MOD_OC = 0xFF;
	P3_DIR_PU = 0xFF;

	USBDeviceInit();              //USB设备模式初始化
    EA = 1;                       //允许单片机中断
    
	UEP1_T_LEN = 0;               //预使用发送长度一定要清空
    FLAG = 0;
    Ready = 0;
	
	//等待USB枚举成功
	while(Ready == 0);
	
    while(1)
    {

		if(Ready)
		{

			if(!Key1)
			{
				mDelaymS(6);
				if(!Key1)
				{
					HIDValueHandle('1');
					while(!Key1);
					HIDValueHandle('7');
				}
			}
			
			if(!Key2)
			{
				mDelaymS(6);
				if(!Key2)
				{
					HIDValueHandle('2');
					while(!Key2);
					HIDValueHandle('7');
				}
			}
			
			FLAG = 0;
		
		}

    }
}
