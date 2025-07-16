#include "usb.h"

#define THIS_ENDP0_SIZE		0x08

static UINT8X Ep0Buffer[THIS_ENDP0_SIZE+2] _at_ 0x0000;
static UINT8X Ep1Buffer[MAX_PACKET_SIZE] _at_ 0x0080;
static UINT8X Ep2Buffer[2 * MAX_PACKET_SIZE] _at_ 0x00c0;
static UINT8X Ep3Buffer[MAX_PACKET_SIZE] _at_ 0x0140;
static UINT8X Ep4Buffer[1] _at_ 0x0040;


UINT8   SetupReq,SetupLen,Ready = 0,Count,FLAG,UsbConfig;
PUINT8  pDescr;
USB_SETUP_REQ   SetupReqBuf;
UINT8	EnumOK,sleepOK = 0;

#define UsbSetupBuf     ((PUSB_SETUP_REQ)Ep0Buffer)

#pragma  NOAREGS

/*�豸������*/
UINT8C DevDesc[] = 
{
	0x12,0x01,0x10,0x01,0x00,0x00,0x00,
    THIS_ENDP0_SIZE,
    (VID & 0xff), (VID >> 8),
    (PID & 0xff), (PID >> 8),
    0x01, 0x01,0x00, 0x00,0x00, 0x01
};

UINT8C CfgDesc[] =
{
	0x09,0x02,0x74,0x00,0x04,0x01,0x00,0xA0,0x64,	//����������
	
	0x09,0x04,0x00,0x00,0x01,0x03,0x01,0x01,0x00,	//���� �ӿڵ������� 
	0x09,0x21,0x10,0x01,0x00,0x01,0x22,0x2b,0x00,	//���� HID��������
	0x07,0x05,0x81,0x03,0x08,0x00,0x01,				//���� ����˿�������
	
	0x09,0x04,0x01,0x00,0x02,0x03,0x00,0x00,0x00,	//�Զ���HID�豸 �ӿ�������
	0x09,0x21,0x10,0x01,0x21,0x01,0x22,0x22,0x00,	//�Զ���HID�豸 HID������
	0x07,0x05,0x82,0x03,0x40,0x00,0x32,				//�Զ���HID�豸 �˵�������
	0x07,0x05,0x02,0x03,0x40,0x00,0x0a,				//�Զ���HID�豸 �˵�������
	
	0x09,0x04,0x02,0x00,0x01,0x03,0x01,0x02,0x00,	//��� �ӿ������� 
	0x09,0x21,0x10,0x01,0x00,0x01,0x22,0x34,0x00,	//��� HID������
	0x07,0x05,0x83,0x03,0x04,0x00,0x0a,				//��� �˵�������
	
	0x09,0x04,0x03,0x00,0x01,0x03,0x01,0x02,0x00,	//��ý�� �ӿ�������
	0x09,0x21,0x10,0x01,0x00,0x01,0x22,0x29,0x00,	//��ý�� HID������
	0x07,0x05,0x84,0x03,0x02,0x00,0x0a 				//��ý�� �˵�������
};


/*HID�౨��������*/
UINT8C KeyRepDesc[] =
{
	0x05,0x01,// USAGE_PAGE  : Global Generic Desktop
	0x09,0x06,// USAGE       : Local KeyBoard
	0xA1,0x01,// COLLECTION  : Main app collection
	0x05,0x07,// USAGE_PAGE  : Global KeyBoard
	//first byte
	0x19,0xe0,// USAGE_MIN   : Local Usage Min (KeyBoard LeftControl)
	0x29,0xe7,// USAGE_MAX   : Local Usage Max (KeyBoard Right GUI)
	0x15,0x00,// LOGICAL_MIN : 0
	0x25,0x01,// LOGICAL_MAX : 1
	0x75,0x01,// REPORT_SIZE : 1
	0x95,0x08,// REPORT_COUNT: 8
	0x81,0x02,// INPUT       : Main Input(Data,Var,Abs)
	//second byte
	0x95,0x01,// Global ReportCount
	0x75,0x08,// Global ReportSize
	0x81,0x03,// Main Input(Cnst,Var,Abs)
	// 3rd~8th byte
//	0x95,0x05,
//	0x75,0x01,  
//	0x05,0x08,
//	0x19,0x01,
//	0x29,0x05,
//	0x91,0x02,
//	0x95,0x01,
//	0x75,0x03,
//	0x91,0x03,
//	0x95,0x06,
//	0x75,0x08,
//	0x15,0x00,
//	0x25,0xff,
//	0x05,0x07,//USAGE_PAGE  : 
	//end
	0x19,0x00,// Global ReportCount
	0x2A,0xff,0x00,// Global ReportSize
	0x15,0x00,// INPUT :
	0x26,0xff,0x00,
	0x95,0x06,
	0x81,0x00,
	0xC0      // END_COLLECTION
};
UINT8C HID_RepDesc[] =
{
	0x06, 0x00,0xff,
    0x09, 0x01,
    0xa1, 0x01,
    0x09, 0x02,
    0x15, 0x00,
    0x26, 0x00,0xff,
    0x75, 0x08,
    0x95, MAX_PACKET_SIZE,
    0x81, 0x06,
    0x09, 0x02,
    0x15, 0x00,
    0x26, 0x00,0xff,
    0x75, 0x08,
    0x95, MAX_PACKET_SIZE,
    0x91, 0x06,
    0xC0
};
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
	0x95,0x03,
	0x75,0x01,
    0x81,0x02,
	0x95,0x01,
	0x75,0x05,
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
UINT8C MultimediaRepDesc[] =
{
	0x05, 0x0C,
	0x09, 0x01,
	0xA1, 0x01,
	0x15, 0x00, 
	0x25, 0x01,
	0x0A, 0xEA, 0x00,
	0x0A, 0xE9, 0x00,
	0x0A, 0xCD, 0x00,
	0x0A, 0xB6, 0x00,
	0x0A, 0xB5, 0x00,
	0x0A, 0xE2, 0x00,
	0x0A, 0x92, 0x01,
	0x0A, 0x34, 0x00,
	0x75, 0x01,
	0x95, 0x08,
	0x81, 0x02,
	0xC0
};




/* �Զ���HID���ݻ����� */
UINT8X User_Ep2Buf_send[64] = {0x0};
UINT8X User_Ep2Buf_rev[64] = {0x0};

UINT8 HID_Busy = 0;			//�Զ���HID���ͱ�־
UINT8 HID_Rev = 0;			//�Զ���HID���ձ�־


/*��������*/
UINT8 HIDKey[8] = {0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0};
/* ������� */
UINT8 HIDMouse[4] = {0x0,0x0,0x0,0x0};
/* ��ý������ */
UINT8 HIDMultimedia[1] = {0x0};


/*******************************************************************************
* Description    : USB�豸ģʽ����,�豸ģʽ�������շ��˵����ã��жϿ���
*******************************************************************************/
void USBDeviceInit(void)
{
	P1_MOD_OC = 0xff;
    P1_DIR_PU = 0xff;
	P1 = 0xff;
	P3 = 0xff;
    P3_MOD_OC = 0xFF;
    P3_DIR_PU = 0xFF;

	
	UEP1_T_LEN = 0;      //Ԥʹ�÷��ͳ���һ��Ҫ���
	UEP2_T_LEN = 0;      //Ԥʹ�÷��ͳ���һ��Ҫ���
    UEP3_T_LEN = 0;
	UEP4_T_LEN = 0;
	
	FLAG = 0;
	Ready = 0;
	
	IE_USB = 0;					// �ر�USB�ж�
	USB_CTRL = 0x00;          	// ���趨USB�豸ģʽ
	UDEV_CTRL = bUD_PD_DIS;   	// ��ֹDP/DM��������

    UDEV_CTRL &= ~bUD_LOW_SPEED;
    USB_CTRL &= ~bUC_LOW_SPEED;
	
	UEP3_DMA = Ep3Buffer;
	UEP2_3_MOD |= bUEP3_TX_EN;
	UEP2_3_MOD &= ~bUEP3_RX_EN;
    UEP2_3_MOD &= ~bUEP3_BUF_MOD;
    UEP3_CTRL = bUEP_AUTO_TOG | UEP_T_RES_NAK;
    UEP2_DMA = Ep2Buffer;                              	//�˵�2��ַ
	UEP2_3_MOD |= bUEP2_TX_EN | bUEP2_RX_EN;           	//�˵�2���ͽ���ʹ��
    UEP2_3_MOD &= ~bUEP2_BUF_MOD;                      	//�˵�2�շ���64�ֽڻ�����
    UEP2_CTRL = bUEP_AUTO_TOG | UEP_T_RES_NAK | UEP_R_RES_ACK;
	UEP1_DMA = Ep1Buffer;
    UEP4_1_MOD = bUEP1_TX_EN;
	UEP4_1_MOD &= ~bUEP1_RX_EN;
	UEP4_1_MOD &= ~bUEP1_BUF_MOD;
    UEP1_CTRL = bUEP_AUTO_TOG | UEP_T_RES_NAK;
	UEP0_DMA = Ep0Buffer;
    UEP0_CTRL = UEP_R_RES_ACK | UEP_T_RES_NAK;
	UEP4_1_MOD |= bUEP4_TX_EN;
    UEP4_1_MOD &= ~bUEP4_RX_EN;    
	UEP4_CTRL = bUEP_AUTO_TOG | UEP_T_RES_NAK;

	USB_DEV_AD = 0x00;
	USB_CTRL |= bUC_DEV_PU_EN | bUC_INT_BUSY | bUC_DMA_EN;// ����USB�豸��DMA�����ж��ڼ��жϱ�־δ���ǰ�Զ�����NAK
	UDEV_CTRL |= bUD_PORT_EN;                             // ����USB�˿�
	USB_INT_FG = 0xFF;                                    // ���жϱ�־
	USB_INT_EN = bUIE_SUSPEND | bUIE_TRANSFER | bUIE_BUS_RST;
	IE_USB = 1;
//	T2MOD &= ~bT0_CLK;
//	TMOD &= 0xf1;
//	TL0 = 0x3CB0 & 0xff;
//	TH0 = (0x3CB0>>8) & 0xff;
//    TR0 = 0;ET0 = 1;
	EA = 1;
	memcpy( Ep1Buffer, HIDKey, sizeof(HIDKey));//clear buffer 
}

void USBDevWakeup(void)
{
	UDEV_CTRL |= bUD_LOW_SPEED;
	mDelaymS(2);
	UDEV_CTRL &= ~bUD_LOW_SPEED;		
}


void Keyboard_Send(UINT8 len)
{
	if(sleepOK != 0)
	{
		USBDevWakeup();
	}
	while((UEP1_CTRL & MASK_UEP_T_RES) == UEP_T_RES_ACK); 
	if(len==0)
		memcpy( Ep1Buffer, HIDKey, sizeof(HIDKey)); 
	else
		memcpy( Ep1Buffer, HIDKey, len); 
  UEP1_T_LEN = sizeof(HIDKey);                                           
  UEP1_CTRL = UEP1_CTRL & ~ MASK_UEP_T_RES | UEP_T_RES_ACK; 
}

void HID_Send(void)
{
	while((UEP2_CTRL & MASK_UEP_T_RES) == UEP_T_RES_ACK); 
    memcpy( Ep2Buffer + MAX_PACKET_SIZE, User_Ep2Buf_send, sizeof(User_Ep2Buf_send)); 	
    UEP2_T_LEN = sizeof(User_Ep2Buf_send);                 
    UEP2_CTRL = UEP2_CTRL & ~ MASK_UEP_T_RES | UEP_T_RES_ACK;   
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
void Multimedia_Send(void)
{
	while((UEP4_CTRL & MASK_UEP_T_RES) == UEP_T_RES_ACK);
    memcpy( Ep4Buffer, HIDMultimedia, sizeof(HIDMultimedia));
    UEP4_T_LEN = sizeof(HIDMultimedia);
    UEP4_CTRL = UEP4_CTRL & ~ MASK_UEP_T_RES | UEP_T_RES_ACK;
}


void DeviceInterrupt( void ) interrupt INT_NO_USB using 1
{
    UINT8 len,i;
    if(UIF_TRANSFER)     //USB������ɱ�־
    {
        switch (USB_INT_ST & (MASK_UIS_TOKEN | MASK_UIS_ENDP))
        {
		case UIS_TOKEN_OUT | 2:
            if(U_TOG_OK)
			{
				len = USB_RX_LEN;
				for(i=0;i<len;i++)
				{
					User_Ep2Buf_rev[i] = Ep2Buffer[i];
					User_Ep2Buf_send[i] = 0;
					Ep2Buffer[MAX_PACKET_SIZE + i] = 0;
				}
				HID_Rev = 1;
			}
			UEP2_CTRL = UEP2_CTRL & ~ MASK_UEP_R_RES | UEP_T_RES_NAK;//
            break; 
			
		case UIS_TOKEN_IN | 2:
            UEP2_T_LEN = 0;
            UEP2_CTRL = UEP2_CTRL & ~ MASK_UEP_T_RES | UEP_T_RES_NAK;          //Ĭ��Ӧ��NAK
			memcpy( User_Ep2Buf_send, 0, sizeof(User_Ep2Buf_send));
			HID_Busy = 1;//�ϱ����
            break;
			
		case UIS_TOKEN_IN | 4:                                                 //endpoint 4# �ж϶˵��ϴ�
            UEP4_T_LEN = 0;                                                    //Ԥʹ�÷��ͳ���һ��Ҫ���
			UEP4_CTRL ^= bUEP_T_TOG;                                           //�˵�4ֻ���ֶ���ת
			UEP4_CTRL = UEP4_CTRL & ~ MASK_UEP_T_RES | UEP_T_RES_NAK;          //Ĭ��Ӧ��NAK
            FLAG = 1;
            break;
		
		case UIS_TOKEN_IN | 3:        //endpoint 3# �˵������ϴ�
            UEP3_T_LEN = 0;           //Ԥʹ�÷��ͳ���һ��Ҫ���
            UEP3_CTRL = UEP3_CTRL & ~ MASK_UEP_T_RES | UEP_T_RES_NAK;          //Ĭ��Ӧ��NAK
			FLAG = 1; 
            break;

        case UIS_TOKEN_IN | 1:                                                  //endpoint 1# �ж϶˵��ϴ�
            UEP1_T_LEN = 0;                                                     //Ԥʹ�÷��ͳ���һ��Ҫ���
            UEP1_CTRL = UEP1_CTRL & ~ MASK_UEP_T_RES | UEP_T_RES_NAK;           //Ĭ��Ӧ��NAK
            FLAG = 1;                                                           /*������ɱ�־*/
            break;
		
        case UIS_TOKEN_SETUP | 0:  //SETUP����  USB�ϱ�
            len = USB_RX_LEN;
            if(len == (sizeof(USB_SETUP_REQ)))
            {
                SetupLen = UsbSetupBuf->wLengthL;
				if(UsbSetupBuf->wLengthH || SetupLen > 0x7F )
                    SetupLen = 0x7F;   // �����ܳ���
                len = 0;    // Ĭ��Ϊ�ɹ������ϴ�0����
                SetupReq = UsbSetupBuf->bRequest;
				
                if ( ( UsbSetupBuf->bRequestType & USB_REQ_TYP_MASK ) != USB_REQ_TYP_STANDARD )/* HID������ */
                {
					len  = 0;///
					switch( SetupReq ) //HID����
					{
						case 0x01:
							pDescr = User_Ep2Buf_send;
							if(SetupLen >= THIS_ENDP0_SIZE)
								len = THIS_ENDP0_SIZE;
							else
								len = SetupLen;
							break;
						case 0x02:	break;
						case 0x03:	break;
						case 0x09:	if(UsbSetupBuf->bRequestType == 0x21) EnumOK = 1;	break;
						case 0x0A:	UEP0_T_LEN = 0;		break;
						case 0x0B:	break;
						default:	len = 0xFF; /*���֧��*/					
							break;
					}
					
                }
                else	  //��׼����
                {
                    switch(SetupReq)          //������
                    {
                    case USB_GET_DESCRIPTOR:
                        switch(UsbSetupBuf->wValueH)
                        {
                        case USB_DESCR_TYP_DEVICE:    //�豸������
                            pDescr = DevDesc;         //���豸�������͵�Ҫ���͵Ļ�����
                            len = sizeof(DevDesc);
                            break;
                        case USB_DESCR_TYP_CONFIG:    //����������
                            pDescr = CfgDesc;         //���豸�������͵�Ҫ���͵Ļ�����
                            len = sizeof(CfgDesc);
                            break;
                        case USB_DESCR_TYP_REPORT:    //����������
                            if(UsbSetupBuf->wIndexL == 0)
                            {
                                pDescr = KeyRepDesc;
                                len = sizeof(KeyRepDesc);
                            }
                            else if(UsbSetupBuf->wIndexL == 1)
                            {
                                pDescr = HID_RepDesc;
                                len = sizeof(HID_RepDesc);                                
                            }
							else if(UsbSetupBuf->wIndexL == 2)
                            {
                                pDescr = MouseRepDesc;
                                len = sizeof(MouseRepDesc);                                
                            }
							else if(UsbSetupBuf->wIndexL == 3)
                            {
                                pDescr = MultimediaRepDesc;
                                len = sizeof(MultimediaRepDesc);                                
                            }
                            else
                            {
                                len = 0xff;                                 //������ֻ��3���ӿڣ���仰����������ִ��
                            }
                            break;
							
                        default:
                            len = 0xff;                //��֧�ֵ�������߳���
                            break;
                        }
						if ( len == 0xff )
							break;	
                        if ( SetupLen > len )
                            SetupLen = len;    //�����ܳ���
                        len = SetupLen >= THIS_ENDP0_SIZE ? THIS_ENDP0_SIZE : SetupLen; //���δ��䳤��
                        memcpy(Ep0Buffer,pDescr,len);                        //�����ϴ�����
                        SetupLen -= len;
                        pDescr += len;
                        break;
                    case USB_SET_ADDRESS:
                        SetupLen = UsbSetupBuf->wValueL;                     //�ݴ�USB�豸��ַ
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
                        if ( ( UsbSetupBuf->bRequestType & USB_REQ_RECIP_MASK ) == USB_REQ_RECIP_ENDP )// �˵�
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
									len = 0xFF;                                            // ��֧�ֵĶ˵�
									break;
                            }
                        }
                        if ( ( UsbSetupBuf->bRequestType & USB_REQ_RECIP_MASK ) == USB_REQ_RECIP_DEVICE )// �豸
                        {
							break;
                        }													
                        else
                        {
                            len = 0xFF;                                                // ���Ƕ˵㲻֧��
                        }
                        break;
                    case USB_SET_FEATURE:                                              /* Set Feature */
                        if( ( UsbSetupBuf->bRequestType & 0x1F ) == 0x00 )             /* �����豸 */
                        {
                            if( ( ( ( UINT16 )UsbSetupBuf->wValueH << 8 ) | UsbSetupBuf->wValueL ) == 0x01 )
                            {
                                if( CfgDesc[ 7 ] & 0x20 )
                                {
                                    /* ���û���ʹ�ܱ�־ */
                                }
                                else
                                {
                                    len = 0xFF;                                        /* ����ʧ�� */
                                }
                            }
                            else
                            {
                                len = 0xFF;                                            /* ����ʧ�� */
                            }
                        }
                        else if( ( UsbSetupBuf->bRequestType & 0x1F ) == 0x02 )        /* ���ö˵� */
                        {
                            if( ( ( ( UINT16 )UsbSetupBuf->wValueH << 8 ) | UsbSetupBuf->wValueL ) == 0x00 )
                            {
                                switch( ( ( UINT16 )UsbSetupBuf->wIndexH << 8 ) | UsbSetupBuf->wIndexL )
                                {
									case 0x84:
										UEP4_CTRL = UEP4_CTRL & (~bUEP_T_TOG) | UEP_T_RES_STALL;/* ���ö˵�3 IN STALL */
										break;
									case 0x83:
										UEP3_CTRL = UEP3_CTRL & (~bUEP_T_TOG) | UEP_T_RES_STALL;/* ���ö˵�3 IN STALL */
										break;
									case 0x82:
										UEP2_CTRL = UEP2_CTRL & (~bUEP_T_TOG) | UEP_T_RES_STALL;/* ���ö˵�2 IN STALL */
										break;
									case 0x02:
										UEP2_CTRL = UEP2_CTRL & (~bUEP_R_TOG) | UEP_R_RES_STALL;/* ���ö˵�2 OUT Stall */
										break;
									case 0x81:
										UEP1_CTRL = UEP1_CTRL & (~bUEP_T_TOG) | UEP_T_RES_STALL;/* ���ö˵�1 IN STALL */
										break;
									default:
										len = 0xFF;                               //����ʧ��
										break;
                                }
                            }
                            else
                            {
                                len = 0xFF;                                   //����ʧ��
                            }
                        }
                        else
                        {
                            len = 0xFF;                                      //����ʧ��
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
                        len = 0xff;                                           //����ʧ��
                        break;
                    }
                }
            }
            else
            {
                len = 0xff;                                                   //�����ȴ���
            }
            if(len == 0xff)
            {
                SetupReq = 0xFF;
                UEP0_CTRL = bUEP_R_TOG | bUEP_T_TOG | UEP_R_RES_STALL | UEP_T_RES_STALL;//STALL
            }
            else if(len <= THIS_ENDP0_SIZE)       //�ϴ����ݻ���״̬�׶η���0���Ȱ�
            {
                UEP0_T_LEN = len;
                UEP0_CTRL = bUEP_R_TOG | bUEP_T_TOG | UEP_R_RES_ACK | UEP_T_RES_ACK;//Ĭ�����ݰ���DATA1������Ӧ��ACK
            }
            else
            {
                UEP0_T_LEN = 0;  //��Ȼ��δ��״̬�׶Σ�������ǰԤ���ϴ�0�������ݰ��Է�������ǰ����״̬�׶�
                UEP0_CTRL = bUEP_R_TOG | bUEP_T_TOG | UEP_R_RES_ACK | UEP_T_RES_ACK;//Ĭ�����ݰ���DATA1,����Ӧ��ACK
            }
            break;
        case UIS_TOKEN_IN | 0:                                               //endpoint0 IN
            switch(SetupReq)
            {
			case USB_GET_DESCRIPTOR:
				len = SetupLen >= THIS_ENDP0_SIZE ? THIS_ENDP0_SIZE : SetupLen;    //���δ��䳤��
				memcpy( Ep0Buffer, pDescr, len );                            //�����ϴ�����
				SetupLen -= len;
				pDescr += len;
				UEP0_T_LEN = len;
				UEP0_CTRL ^= bUEP_T_TOG;                                     //ͬ����־λ��ת
			break;
			case HID_GET_REPORT:
                len = SetupLen >= THIS_ENDP0_SIZE ? THIS_ENDP0_SIZE : SetupLen; //���δ��䳤��
                memcpy(Ep0Buffer, pDescr, len);                                 //�����ϴ�����
                SetupLen -= len;
                pDescr += len;
                UEP0_T_LEN = len;
                UEP0_CTRL ^= bUEP_T_TOG; //ͬ����־λ��ת
                break;
            case USB_SET_ADDRESS:
                USB_DEV_AD = USB_DEV_AD & bUDA_GP_BIT | SetupLen;
                UEP0_CTRL = UEP_R_RES_ACK | UEP_T_RES_NAK;
                break;
            default:
                UEP0_T_LEN = 0;           //״̬�׶�����жϻ�����ǿ���ϴ�0�������ݰ��������ƴ���
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
            UEP0_CTRL ^= bUEP_R_TOG;                                     //ͬ����־λ��ת						
            break;
        default:
            break;
        }
        UIF_TRANSFER = 0;                                                 //д0����ж�
    }
    if(UIF_BUS_RST)                                                       //�豸ģʽUSB���߸�λ�ж�
    {
        UEP0_CTRL = UEP_R_RES_ACK | UEP_T_RES_NAK;
        UEP1_CTRL = bUEP_AUTO_TOG | UEP_R_RES_ACK | UEP_T_RES_NAK;
        UEP2_CTRL = bUEP_AUTO_TOG | UEP_R_RES_ACK | UEP_T_RES_NAK;
		UEP3_CTRL = bUEP_AUTO_TOG | UEP_R_RES_ACK | UEP_T_RES_NAK;
		UEP4_CTRL = bUEP_AUTO_TOG | UEP_R_RES_ACK | UEP_T_RES_NAK;
        USB_DEV_AD = 0x00;
        UIF_SUSPEND = 0;
        UIF_TRANSFER = 0;
		UIF_BUS_RST = 0;                                                 //���жϱ�־
    }
    if (UIF_SUSPEND)                                                     //USB���߹���/�������
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

//void mTimer0Interrupt( void ) interrupt INT_NO_TMR0
//{
//	static char con = 0;
//	
//	TL0 = 0x3CB0 & 0xff;
//	TH0 = (0x3CB0>>8) & 0xff; 
//	
//	if(con++ >= 30)
//	{
//		if(Ready == 0)
//		{
//			TR0 = 0;
//			FLAG = 0;Ready = 0;
//			IE_USB = 0;USB_CTRL = 0x00;UDEV_CTRL = bUD_PD_DIS;
//			USB_DEV_AD = 0x00;
//			USB_CTRL |= bUC_DEV_PU_EN | bUC_INT_BUSY | bUC_DMA_EN;
//			UDEV_CTRL |= bUD_PORT_EN;USB_INT_FG = 0xFF;
//			USB_INT_EN = bUIE_SUSPEND | bUIE_TRANSFER | bUIE_BUS_RST;
//			IE_USB = 1;
//			TR0 = 1;
//		}
//		con = 0;
//	}      
//}

