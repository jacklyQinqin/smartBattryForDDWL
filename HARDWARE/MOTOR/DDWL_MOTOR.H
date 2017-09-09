#ifndef  __DDWL_MOTOR_H__
#define  __DDWL_MOTOR_H__
#include "sys.h"
#define     PC15   GPIO_Pin_15
#define     PF0     GPIO_Pin_0
#define     PF1     GPIO_Pin_1
#define     PF2     GPIO_Pin_2
#define     PF3     GPIO_Pin_3            
#define     PF4     GPIO_Pin_4
#define     PF5     GPIO_Pin_5
#define     PA5     GPIO_Pin_5
#define     PA4     GPIO_Pin_4
#define     PA6    GPIO_Pin_6     
#define     PA7     GPIO_Pin_7
#define     PC4     GPIO_Pin_4


#define RLY1    PC15
#define RLY2    PF0
#define RLY3    PF1
#define RLY4    PF2
#define RLY5    PF3
#define RLY6    PF4
#define RLY7    PF5
#define RLY8    PA5
#define RLY9    PA4
#define RLY10    PA6
#define RLY11    PA7
#define RLY12    PC4


//继电器引脚分配

//继电器引脚初始化
void MOTOR_Init(void);

//打开或者关闭任意一个继电器
void MOTOR_Control(unsigned char numOfMotor);


#endif
