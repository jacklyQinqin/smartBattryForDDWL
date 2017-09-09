#include "DDWL_MC20.H"

/**********
���ŷ���
PC6	Usart6Tx
PC7	Usart6Rx
**/

void MC20_Init(unsigned int bound)
{
	 GPIO_InitTypeDef GPIO_InitStructure;
	 USART_InitTypeDef USART_InitStructure;
	 //NVIC_InitTypeDef NVIC_InitStructure;
	 
	 RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);	 //ʹ��GPIOCʱ��
	
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART6,ENABLE);//ʹ��USART6ʱ��
	
	
	 //����6��Ӧ���Ÿ���ӳ��
	 GPIO_PinAFConfig(GPIOC,GPIO_PinSource6,GPIO_AF_USART6); //GPIOC6����ΪUSART6
	 GPIO_PinAFConfig(GPIOC,GPIO_PinSource7,GPIO_AF_USART6); //GPIOC7����ΪUSART6
	
	 //USART3�˿�����
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7; //GPIOB11��GPIOB12
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//���ù���
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 //�ٶ�50MHz
	 GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //���츴�����
	 GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //����
	 GPIO_Init(GPIOC,&GPIO_InitStructure); //��ʼ��PC6,PC7
	
	//USART6 ��ʼ������
	 USART_InitStructure.USART_BaudRate = bound;//����������
	 USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	 USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	 USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	 USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	 USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; //�շ�ģʽ
	 USART_Init(USART6, &USART_InitStructure); //��ʼ������6
	 
	 USART_Cmd(USART6, ENABLE);  //ʹ�ܴ���3 

}
void    KEY_Server(void)
{
    ;
}
//end of file   mc20.c