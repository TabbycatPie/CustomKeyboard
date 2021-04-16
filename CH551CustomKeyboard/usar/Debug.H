/* 调试 */
/* 提供printf子程序和延时函数 */

#ifndef	__DEBUG_H__
#define __DEBUG_H__

//定义函数返回值
#ifndef  SUCCESS
#define  SUCCESS  0
#endif
#ifndef  FAIL
#define  FAIL    0xFF
#endif

//定义定时器起始
#ifndef  START
#define  START  1
#endif
#ifndef  STOP
#define  STOP    0
#endif

#define	 FREQ_SYS	     12000000	         //系统主频12MHz
#define  OSC_EN_XT     0                 //外部晶振使能，默认开启内部晶振
#ifndef  UART0_BUAD
#define  UART0_BUAD    57600
#define  UART1_BUAD    57600
#endif
#ifndef  DE_PRINTF                      //程序Pirntf输出开启
#define  DE_PRINTF     0
#endif

void	CfgFsys( );                        //CH552时钟选择和配置
void	mDelayuS( UINT16 n );              // 以uS为单位延时
void	mDelaymS( UINT16 n );              // 以mS为单位延时

//void    CH554WDTModeSelect(UINT8 mode);     //CH554看门狗模式设置 
//void    CH554WDTFeed(UINT8 tim);            //CH554看门狗喂狗

// void CH554SoftReset( );                  //CH554软复位
// void CH554USBDevWakeup( );               //CH554做USB设备唤醒主机
//  
#endif
