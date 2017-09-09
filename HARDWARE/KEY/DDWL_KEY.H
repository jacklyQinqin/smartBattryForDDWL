#ifndef  _DDWL_KEY_H
#define _DDWL_KEY_H
#include "sys.h"

#define KEY1        PF14
#define KEY2        PF15
#define KEY3        PG0
#define KEY4        PG1
#define KEY5        PE7
#define KEY6        PE8
#define KEY7        PE9
#define KEY8        PE11
#define KEY9        PE12
#define KEY10        PE13
#define KEY11        PE14
#define KEY12        PE15

typedef     unsigned int    KeyValueType_t;

void KEY_Init(void);
KeyValueType_t KEY_Scan(void);


#endif
