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




//TASK1. par
//task1. priority 1.is the lowest.
#define START_TASK_PRIO		1
//Stack SIZE	
#define START_STK_SIZE 		128  
//task1. handler.
TaskHandle_t StartTask_Handler;
//Task1 Function.
void start_task(void *pvParameters);

//�������ȼ�
#define KEYSCAN_TASK_PRIO		2
//�����ջ��С	
#define KEYSCAN_STK_SIZE 		50  
//������
TaskHandle_t KEYSCANTask_Handler;
//������
void keyscan_task(void *pvParameters);

//�������ȼ�
#define LED1_TASK_PRIO		3
//�����ջ��С	
#define LED1_STK_SIZE 		50  
//������
TaskHandle_t LED1Task_Handler;
//������
void led1_task(void *pvParameters);

//�������ȼ�
#define FLOAT_TASK_PRIO		4
//�����ջ��С	
#define FLOAT_STK_SIZE 		128
//������
TaskHandle_t FLOATTask_Handler;
//������
void float_task(void *pvParameters);

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
    xTaskCreate((TaskFunction_t )led1_task,     
                (const char*    )"led1_task",   
                (uint16_t       )LED1_STK_SIZE, 
                (void*          )NULL,
                (UBaseType_t    )LED1_TASK_PRIO,
                (TaskHandle_t*  )&LED1Task_Handler);        
    //�����������
    xTaskCreate((TaskFunction_t )float_task,     
                (const char*    )"float_task",   
                (uint16_t       )FLOAT_STK_SIZE, 
                (void*          )NULL,
                (UBaseType_t    )FLOAT_TASK_PRIO,
                (TaskHandle_t*  )&FLOATTask_Handler);  
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

//LED1������
void led1_task(void *pvParameters)
{
    while(1)
    {
        GPIO_SetBits(GPIOE,GPIO_Pin_2 | GPIO_Pin_3);
        vTaskDelay(200);
        GPIO_ResetBits(GPIOE,GPIO_Pin_2 | GPIO_Pin_3);
        vTaskDelay(800);
    }
}

//�����������
void float_task(void *pvParameters)
{
	static float float_num=0.00;
	while(1)
	{
		float_num+=0.01f;
		printf("float_num��ֵΪ: %.4f\r\n",float_num);
        vTaskDelay(1000);
	}
}


