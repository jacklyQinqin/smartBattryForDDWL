#ifndef  _DDWL_485_H
#define _DDWL_485_H
#include "sys.h"


/**
滴咚未来485通信引脚分配
PB11	Rx
PB12	Tx
PB13	De	
**/

extern unsigned char RS485RxBuff[100];
extern unsigned char RS485TxBuff[100];

void RS485_Init(unsigned int bound);
void RS485_TxData(unsigned char * pTxDat);
void RS485_RxData(unsigned char * pRxdat);



#endif
