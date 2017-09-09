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

//����2���ȼ�
#define KEYSCAN_TASK_PRIO		2
//�����ջ��С	
#define KEYSCAN_STK_SIZE 		50  
//������
TaskHandle_t KEYSCANTask_Handler;
//������
void keyscan_task(void *pvParameters);

//����3���ȼ�
#define MC20_TASK_PRIO		3
//�����ջ��С	
#define MC20_STK_SIZE 		128  
//������
TaskHandle_t MC20Task_Handler;
//������
void mc20_task(void *pvParameters);

//����4���ȼ�
#define FLOAT_TASK_PRIO		4
//�����ջ��С	
#define FLOAT_STK_SIZE 		128
//������
TaskHandle_t FLOATTask_Handler;
//������
void float_task(void *pvParameters);

//����5���ȼ�
#define TASK5_TASK_PRIO		5
//�����ջ��С	
#define TASK5_STK_SIZE 		128
//������
TaskHandle_t TASK5Task_Handler;
//������
void task5_task(void *pvParameters);

//����6���ȼ�
#define TASK6_TASK_PRIO		6
//�����ջ��С	
#define TASK6_STK_SIZE 		128
//������
TaskHandle_t TASK6Task_Handler;
//������
void task6_task(void *pvParameters);


//����7���ȼ�
#define TASK7_TASK_PRIO		7
//�����ջ��С	
#define TASK7_STK_SIZE 		128
//������
TaskHandle_t TASK7Task_Handler;
//������
void task7_task(void *pvParameters);


int main(void)
{ 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);//����ϵͳ�ж����ȼ�����4
	delay_init(168);		//��ʼ����ʱ����
	uart_init(115200);     	//��ʼ������
	LED_Init();		        //��ʼ��LED�˿�
	KEY_Init(); //��ʼ�����˿�
    
    REL_Init();     //�̵�����ʼ��
    MOTOR_Init();   //�����ʼ��
    MC20_Init();        //MC20�˿ڳ�ʼ��

    
	//������ʼ����
    xTaskCreate((TaskFunction_t )start_task,            //������
                (const char*    )"start_task",          //��������
                (uint16_t       )START_STK_SIZE,        //�����ջ��С
                (void*          )NULL,                  //���ݸ��������Ĳ���
                (UBaseType_t    )START_TASK_PRIO,       //�������ȼ�
                (TaskHandle_t*  )&StartTask_Handler);   //������              
    vTaskStartScheduler();          //�����������
}
 
//��ʼ����������
void start_task(void *pvParameters)
{
    taskENTER_CRITICAL();           //�����ٽ���
    //����LED0����
    xTaskCreate((TaskFunction_t )keyscan_task,     	
                (const char*    )"keyscan_task",   	
                (uint16_t       )KEYSCAN_STK_SIZE, 
                (void*          )NULL,				
                (UBaseType_t    )KEYSCAN_TASK_PRIO,	
                (TaskHandle_t*  )&KEYSCANTask_Handler);   
    //����LED1����
    xTaskCreate((TaskFunction_t )mc20_task,     
                (const char*    )"mc20_task",   
                (uint16_t       )MC20_STK_SIZE, 
                (void*          )NULL,
                (UBaseType_t    )MC20_TASK_PRIO,
                (TaskHandle_t*  )&MC20Task_Handler);        
    //�����������
    xTaskCreate((TaskFunction_t )float_task,     
                (const char*    )"float_task",   
                (uint16_t       )FLOAT_STK_SIZE, 
                (void*          )NULL,
                (UBaseType_t    )FLOAT_TASK_PRIO,
                (TaskHandle_t*  )&FLOATTask_Handler);  

    //����5
    xTaskCreate((TaskFunction_t )task5_task,     
                (const char*    )"task5_task",   
                (uint16_t       )TASK5_STK_SIZE, 
                (void*          )NULL,
                (UBaseType_t    )TASK5_TASK_PRIO,
                (TaskHandle_t*  )&TASK5Task_Handler); 
    //����6
    xTaskCreate((TaskFunction_t )task6_task,     
                (const char*    )"task6_task",   
                (uint16_t       )TASK6_STK_SIZE, 
                (void*          )NULL,
                (UBaseType_t    )TASK6_TASK_PRIO,
                (TaskHandle_t*  )&TASK6Task_Handler); 
    //����7
    xTaskCreate((TaskFunction_t )task7_task,     
                (const char*    )"task7_task",   
                (uint16_t       )TASK7_STK_SIZE, 
                (void*          )NULL,
                (UBaseType_t    )TASK7_TASK_PRIO,
                (TaskHandle_t*  )&TASK7Task_Handler); 

				
    vTaskDelete(StartTask_Handler); //ɾ����ʼ����
    taskEXIT_CRITICAL();            //�˳��ٽ���
}

//����ع���״̬����
void keyscan_task(void *pvParameters)
{
    while(1)
    {
        KEY_Scan();
        vTaskDelay(10);
    }
}   


//MC20����.�������ӵĴ�

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


//����5
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


//����6
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

//����7
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



