#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "FreeRTOS.h"
#include "task.h"

#include "DDWL_KEY.H"
#include "DDWL_REL.H"
#include "DDWL_MOTOR.H"
#include "DDWL_MC20.H"
/************************************************
Function:	DDWL main Loop.
Author: 	Qxd.
Time:		2017-9-4 14:45:24
************************************************/




//TASK0. par
//task0. priority 1.is the lowest.
#define START_TASK_PRIO		1
//Stack SIZE	
#define START_STK_SIZE 		128  
//task1. handler.
TaskHandle_t StartTask_Handler;
//Task1 Function.
void start_task(void *pvParameters);

//任务2优先级
#define KEYSCAN_TASK_PRIO		2
//任务堆栈大小	
#define KEYSCAN_STK_SIZE 		50  
//任务句柄
TaskHandle_t KEYSCANTask_Handler;
//任务函数
void keyscan_task(void *pvParameters);

//任务3优先级
#define MC20_TASK_PRIO		3
//任务堆栈大小	
#define MC20_STK_SIZE 		128  
//任务句柄
TaskHandle_t MC20Task_Handler;
//任务函数
void mc20_task(void *pvParameters);

//任务4优先级
#define FLOAT_TASK_PRIO		4
//任务堆栈大小	
#define FLOAT_STK_SIZE 		128
//任务句柄
TaskHandle_t FLOATTask_Handler;
//任务函数
void float_task(void *pvParameters);

//任务5优先级
#define TASK5_TASK_PRIO		5
//任务堆栈大小	
#define TASK5_STK_SIZE 		128
//任务句柄
TaskHandle_t TASK5Task_Handler;
//任务函数
void task5_task(void *pvParameters);

//任务6优先级
#define TASK6_TASK_PRIO		6
//任务堆栈大小	
#define TASK6_STK_SIZE 		128
//任务句柄
TaskHandle_t TASK6Task_Handler;
//任务函数
void task6_task(void *pvParameters);


//任务7优先级
#define TASK7_TASK_PRIO		7
//任务堆栈大小	
#define TASK7_STK_SIZE 		128
//任务句柄
TaskHandle_t TASK7Task_Handler;
//任务函数
void task7_task(void *pvParameters);


int main(void)
{ 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);//设置系统中断优先级分组4
	delay_init(168);		//初始化延时函数
	uart_init(115200);     	//初始化串口
	LED_Init();		        //初始化LED端口
	KEY_Init(); //初始化检测端口
    
    REL_Init();     //继电器初始化
    MOTOR_Init();   //电机初始化
    MC20_Init();        //MC20端口初始化

    
	//创建开始任务
    xTaskCreate((TaskFunction_t )start_task,            //任务函数
                (const char*    )"start_task",          //任务名称
                (uint16_t       )START_STK_SIZE,        //任务堆栈大小
                (void*          )NULL,                  //传递给任务函数的参数
                (UBaseType_t    )START_TASK_PRIO,       //任务优先级
                (TaskHandle_t*  )&StartTask_Handler);   //任务句柄              
    vTaskStartScheduler();          //开启任务调度
}
 
//开始任务任务函数
void start_task(void *pvParameters)
{
    taskENTER_CRITICAL();           //进入临界区
    //创建LED0任务
    xTaskCreate((TaskFunction_t )keyscan_task,     	
                (const char*    )"keyscan_task",   	
                (uint16_t       )KEYSCAN_STK_SIZE, 
                (void*          )NULL,				
                (UBaseType_t    )KEYSCAN_TASK_PRIO,	
                (TaskHandle_t*  )&KEYSCANTask_Handler);   
    //创建LED1任务
    xTaskCreate((TaskFunction_t )mc20_task,     
                (const char*    )"mc20_task",   
                (uint16_t       )MC20_STK_SIZE, 
                (void*          )NULL,
                (UBaseType_t    )MC20_TASK_PRIO,
                (TaskHandle_t*  )&MC20Task_Handler);        
    //浮点测试任务
    xTaskCreate((TaskFunction_t )float_task,     
                (const char*    )"float_task",   
                (uint16_t       )FLOAT_STK_SIZE, 
                (void*          )NULL,
                (UBaseType_t    )FLOAT_TASK_PRIO,
                (TaskHandle_t*  )&FLOATTask_Handler);  

    //任务5
    xTaskCreate((TaskFunction_t )task5_task,     
                (const char*    )"task5_task",   
                (uint16_t       )TASK5_STK_SIZE, 
                (void*          )NULL,
                (UBaseType_t    )TASK5_TASK_PRIO,
                (TaskHandle_t*  )&TASK5Task_Handler); 
    //任务6
    xTaskCreate((TaskFunction_t )task6_task,     
                (const char*    )"task6_task",   
                (uint16_t       )TASK6_STK_SIZE, 
                (void*          )NULL,
                (UBaseType_t    )TASK6_TASK_PRIO,
                (TaskHandle_t*  )&TASK6Task_Handler); 
    //任务7
    xTaskCreate((TaskFunction_t )task7_task,     
                (const char*    )"task7_task",   
                (uint16_t       )TASK7_STK_SIZE, 
                (void*          )NULL,
                (UBaseType_t    )TASK7_TASK_PRIO,
                (TaskHandle_t*  )&TASK7Task_Handler); 

				
    vTaskDelete(StartTask_Handler); //删除开始任务
    taskEXIT_CRITICAL();            //退出临界区
}

//检测电池柜锁状态函数
void keyscan_task(void *pvParameters)
{
    while(1)
    {
        KEY_Scan();
        vTaskDelay(10);
    }
}   


//MC20任务.保持连接的打开

void mc20_task(void *pvParameters)
{
    while(1)
    {
        GPIO_SetBits(GPIOE,GPIO_Pin_2 );
        vTaskDelay(200);
        GPIO_ResetBits(GPIOE,GPIO_Pin_2);
        vTaskDelay(800);
    }
}

void	float_task(void *pvParameters)
{
    while(1)
    {
        GPIO_SetBits(GPIOE, GPIO_Pin_3);
        vTaskDelay(200);
        GPIO_ResetBits(GPIOE, GPIO_Pin_3);
        vTaskDelay(200);
    }
}


//任务5
void task5_task(void *pvParameters)
{

	while(1)
    {
        GPIO_SetBits(GPIOE, GPIO_Pin_3);
        vTaskDelay(100);
        GPIO_ResetBits(GPIOE, GPIO_Pin_2);
        vTaskDelay(100);
    }

}


//任务6
void task6_task(void *pvParameters)
{

	while(1)
    {
        GPIO_SetBits(GPIOE, GPIO_Pin_3);
        vTaskDelay(500);
        GPIO_ResetBits(GPIOE, GPIO_Pin_2);
        vTaskDelay(500);
    }

}

//任务7
void task7_task(void *pvParameters)
{

	while(1)
    {
        REL_Control(1,0);
        REL_Control(1,0);
        REL_Control(1,0);
        REL_Control(1,0);
        REL_Control(1,0);
        REL_Control(1,0);
        REL_Control(1,0);
        REL_Control(1,0);
        REL_Control(1,0);
        REL_Control(1,0);
        REL_Control(1,0);
        REL_Control(1,0);
                   
        vTaskDelay(500);
        GPIO_ResetBits(GPIOE, GPIO_Pin_2);
        vTaskDelay(500);
    }

}



