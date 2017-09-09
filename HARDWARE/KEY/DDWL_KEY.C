#include "DDWL_KEY.H"

//初始化按键GPIO.
//DDWL  按键GPIO.
#define PF14    GPIO_Pin_14
#define PF15    GPIO_Pin_15
#define PG0      GPIO_Pin_0   
#define PG1      GPIO_Pin_1 
#define PE7       GPIO_Pin_7  
#define PE8         GPIO_Pin_8
#define PE9         GPIO_Pin_9
#define PE11        GPIO_Pin_11
#define PE12        GPIO_Pin_12
#define PE13        GPIO_Pin_13
#define PE14        GPIO_Pin_14
#define PE15        GPIO_Pin_15



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

#define KEY1_PRESS          (0X00000001<<0)
#define KEY2_PRESS          (0X00000001<<1)
#define KEY3_PRESS          (0X00000001<<2)
#define KEY4_PRESS          (0X00000001<<3)
#define KEY5_PRESS          (0X00000001<<4)
#define KEY6_PRESS          (0X00000001<<5)
#define KEY7_PRESS          (0X00000001<<6)
#define KEY8_PRESS          (0X00000001<<7)
#define KEY9_PRESS          (0X00000001<<8)
#define KEY10_PRESS        (0X00000001<<9)
#define KEY11_PRESS        (0X00000001<<10)
#define KEY12_PRESS        (0X00000001<<11)   


//开关初始化
void KEY_Init(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;
    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);	//使能GPIOE时钟
	//GPIOF9,F10初始化设置
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;			//普通输出模式
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;		//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;			//上拉
	GPIO_Init(GPIOE, &GPIO_InitStructure);					//初始化GPIO
    
   
    
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);	//使能GPIOF时钟      
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_14|GPIO_Pin_15; 
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN;  //推挽输出
    GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;          //上拉
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_100MHz;     //高速
    GPIO_Init(GPIOF, &GPIO_InitStructure);					//初始化GPIO

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);	//使能GPIOG时钟      
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1; 
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN;  //推挽输出
    GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;          //上拉
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_100MHz;  
    GPIO_Init(GPIOG, &GPIO_InitStructure);					//初始化GPIO
}

//检测开关.是否已经打开.或者关闭.
KeyValueType_t KEY_Scan(void)
{
        KeyValueType_t   keyValue = 0;
        if(GPIO_ReadInputDataBit(GPIOF,KEY1) == RESET)
        {
            keyValue |= KEY1_PRESS;
        }
        if(GPIO_ReadInputDataBit(GPIOF,KEY2) == RESET)
        {
            keyValue |= KEY2_PRESS;
        }
        if(GPIO_ReadInputDataBit(GPIOG,KEY3) == RESET)
        {
            keyValue |= KEY3_PRESS;
        }
        if(GPIO_ReadInputDataBit(GPIOG,KEY4) == RESET)
        {
            keyValue |= KEY4_PRESS;
        }
        if(  GPIO_ReadInputDataBit(GPIOE,KEY5) == RESET)
        {
            keyValue |= KEY5_PRESS;
        }
        if(GPIO_ReadInputDataBit(GPIOE,KEY6) == RESET)
        {
            keyValue |= KEY6_PRESS;
        }
        if(GPIO_ReadInputDataBit(GPIOE,KEY7)== RESET)
        {
            keyValue |= KEY7_PRESS;
        }
        if(GPIO_ReadInputDataBit(GPIOE,KEY8) == RESET)
        {
            keyValue |= KEY8_PRESS;
        }
        if(GPIO_ReadInputDataBit(GPIOE,KEY9)== RESET)
        {
            keyValue |= KEY9_PRESS;
        }    
        if( GPIO_ReadInputDataBit(GPIOE,KEY10) == RESET)
        {
            keyValue |= KEY10_PRESS;
        }
        if(GPIO_ReadInputDataBit(GPIOE,KEY11) == RESET)
        {
            keyValue |= KEY11_PRESS;
        }
        if( GPIO_ReadInputDataBit(GPIOE,KEY12) == RESET)
        {
            keyValue |= KEY12_PRESS;
        }
        
        return keyValue;
}

//end of file key.c
