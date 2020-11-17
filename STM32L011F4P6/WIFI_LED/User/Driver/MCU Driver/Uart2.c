/********************** Copyright(c)***************************
** Shenzhen Yuejiang Technology Co., Ltd.
**
** http:// www.dobot.cc
**
**------File Info----------------------------------------------
** File name:               Uart2.c
** Latest modified date:    2020-06-12
** Latest version:          V1.0.0
** Description:             串口1初始化
**
**------------------------------------------------------------
** Created by:              liu xiang
** Created date:            2020-06-12
** Version:                 V1.0.0
** Descriptions:            串口1初始化
**
**------------------------------------------------------------
** Modified by:
** Modified date:
** Version:
** Description:
**
*************************************************************/

#include "Uart2.h"
#include "main.h"
#include "string.h"
#include "stdio.h"

extern UART_HandleTypeDef huart2;


struct Uart2Buffer gUart2 = {0};
/*************************************************************
** Function name:       Uart2_IT_RxTxHandle
** Descriptions:        串口中断接收和发送处理
** Input parameters:    no
** Output parameters:   no
** min:                 no
** Returned             no
*************************************************************/
void Uart2_IT_RxTxHandle(void)
{
    uint8_t data = 0;
    if(__HAL_UART_GET_FLAG(&huart2,UART_FLAG_RXNE)){
		if (gUart2.rxIndex < Uart2_RINGBUFLENGTH) {
			data = (uint8_t)huart2.Instance->RDR;
			if (data) {
				gUart2.rxBuffer[gUart2.rxIndex++] = data;
			}

		} else {
			Uart2_ClearData();
		}
    }
    if(__HAL_UART_GET_FLAG(&huart2,UART_FLAG_TXE)){
		if (gUart2.txIndex < gUart2.txLen) {
			data = gUart2.txBuffer[gUart2.txIndex++];
			huart2.Instance->TDR = data;
        }else{
            __HAL_UART_DISABLE_IT(&huart2,UART_IT_TXE);
        }
    }
}
/*************************************************************
** Function name:       Uart2_SendData
** Descriptions:        串口5数据发送
** Input parameters:    packet：发送数据指针
**                      length：发送数据长度
** Output parameters:   no
** min：                no
** Returned             no
*************************************************************/
void Uart2_SendData(uint8_t *pData,uint16_t length)
{
    uint16_t cir = 0;
	gUart2.txLen = 0;
	gUart2.txIndex = 0;
    for(cir = 0;cir < length;cir++){	
		if (cir < Uart2_RINGBUFLENGTH) {
			gUart2.txBuffer[cir] = pData[cir];
			gUart2.txLen ++;
		} else {
            break;
        }
    }
    if(length != 0){
        __HAL_UART_ENABLE_IT(&huart2,UART_IT_TXE);
    }
}
/*************************************************************
** Function name:       Uart2_ClearData
** Descriptions:        清空接收数据数组
** Input parameters:    no
** Output parameters:   no
** min：                no
** Returned             no
*************************************************************/
void Uart2_ClearData(void)
{
	memset(gUart2.rxBuffer,0,sizeof(gUart2.rxBuffer));
	gUart2.rxIndex = 0;
}


uint8_t Uart2_IsReceive(char* str)
{
	if(strstr(gUart2.rxBuffer,str)){
		Uart2_ClearData();
		return 1;	
	} else {
		return 0;
	}
}

