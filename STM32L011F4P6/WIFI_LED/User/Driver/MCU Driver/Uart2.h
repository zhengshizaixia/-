/********************** Copyright(c)***************************
** Shenzhen Yuejiang Technology Co., Ltd.
**
** http:// www.dobot.cc
**
**------File Info----------------------------------------------
** File name:               Uart2.h
** Latest modified date:    2020-06-12
** Latest version:          V1.0.0
** Description:             串口一配置
**
**------------------------------------------------------------
** Created by:              liu xiang
** Created date:            2020-06-12
** Version:                 V1.0.0
** Descriptions:            串口一配置
**
**------------------------------------------------------------
** Modified by:
** Modified date:
** Version:
** Description:
**
*************************************************************/

#ifndef Uart2_h
#define Uart2_h
#include "stdint.h"


#define Uart2_RINGBUFLENGTH 50
struct Uart2Buffer{
	char rxBuffer[Uart2_RINGBUFLENGTH];
	char txBuffer[1];
	uint16_t rxIndex;
	uint16_t txIndex;
	uint16_t txLen;
};
extern struct Uart2Buffer gUart2;
extern void Uart2_IT_RxTxHandle(void);
extern void Uart2_SendData(uint8_t *pData,uint16_t length);
extern void Uart2_ClearData(void);
extern uint8_t Uart2_IsReceive(char* str);
#endif /* Uart2_h */
