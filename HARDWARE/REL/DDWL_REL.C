#include "DDWL_REL.H"
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

//继电器初始化   
void REL_Init(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;
    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);	//使能GPIOA时钟
	//GPIOF9,F10初始化设置
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;			//推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;		//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;			//上拉
	GPIO_Init(GPIOA, &GPIO_InitStructure);					//初始化GPIO
    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);	//使能GPIOC时钟
	//GPIOF9,F10初始化设置
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_15; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;			//推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;		//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;			//上拉
	GPIO_Init(GPIOC, &GPIO_InitStructure);					//初始化GPIO
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);	//使能GPIOF时钟
	//GPIOF9,F10初始化设置
	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3| GPIO_Pin_4| GPIO_Pin_5; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;			//推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;		//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;			//上拉
	GPIO_Init(GPIOF, &GPIO_InitStructure);					//初始化GPIO
}

	
void REL_Control(unsigned char numOfREL,unsigned char statusOfREL)
{
	
	switch(numOfREL)
	{
		case 1:	statusOfREL>0?GPIO_SetBits(GPIOC,RLY1):GPIO_ResetBits(GPIOC,RLY1);break;
		case 2:	statusOfREL>0?GPIO_SetBits(GPIOF,RLY2):GPIO_ResetBits(GPIOF,RLY2);break;
		case 3:	statusOfREL>0?GPIO_SetBits(GPIOF,RLY3):GPIO_ResetBits(GPIOF,RLY3);break;
		case 4:	statusOfREL>0?GPIO_SetBits(GPIOF,RLY4):GPIO_ResetBits(GPIOF,RLY4);break;
		case 5:	statusOfREL>0?GPIO_SetBits(GPIOF,RLY5):GPIO_ResetBits(GPIOF,RLY5);break;
		case 6:	statusOfREL>0?GPIO_SetBits(GPIOF,RLY6):GPIO_ResetBits(GPIOF,RLY6);break;
		case 7:	statusOfREL>0?GPIO_SetBits(GPIOF,RLY7):GPIO_ResetBits(GPIOF,RLY7);break;
		case 8:	statusOfREL>0?GPIO_SetBits(GPIOA,RLY8):GPIO_ResetBits(GPIOA,RLY8);break;
		case 9:	statusOfREL>0?GPIO_SetBits(GPIOA,RLY9):GPIO_ResetBits(GPIOA,RLY9);break;
		case 10:statusOfREL>0?GPIO_SetBits(GPIOA,RLY10):GPIO_ResetBits(GPIOA,RLY10);break;
		case 11:statusOfREL>0?GPIO_SetBits(GPIOA,RLY11):GPIO_ResetBits(GPIOA,RLY11);break;
		case 12:statusOfREL>0?GPIO_SetBits(GPIOC,RLY12):GPIO_ResetBits(GPIOC,RLY12);break;
		default:
			break; 
	}
    
}
