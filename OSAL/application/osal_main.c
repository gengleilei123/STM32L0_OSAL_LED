/****************************************************************************************
 * �ļ���  ��osal_main.c
 * ����    ��osal����ϵͳ��������������������ڴ��ļ������
 * ����ƽ̨��
 * ��汾  ��
 ***************************************************************************************/
#include "application.h"

/******************************************************************************
 * @fn      main
 *
 * @brief   
 *
 * @param   
 *
 * @return
 *****************************************************************************/
void osal_main(void)
{    
	//ϵͳӲ��������ȳ�ʼ��
	
	//��ֹ�ж�
    HAL_DISABLE_INTERRUPTS();

    //osal����ϵͳ��ʼ��
    osal_init_system();

	//�������
	osal_add_Task(Serial_Task_Init,Serial_Task_EventProcess,1);
	osal_add_Task(LED4_Task_Init,LED4_Task_EventProcess,2);	
	//��ӵ�����ͳһ���г�ʼ��
	osal_Task_init();

	osal_mem_kick();

	//�����ж�
	HAL_ENABLE_INTERRUPTS();	

	//���ó�ʼ�����¼����ϵ����Ҫ�Զ���ѯ�������¼����ڴ����
	osal_start_reload_timer( LED_TaskID, SYSCLK, 20);
	osal_start_reload_timer( LED0_TaskID, OSAL_LED0, 10);
	//osal_start_timerEx( LED_TaskID, SYSCLK, 20 );//����һ����ʱ��
	

	//����osalϵͳ�������ٷ���
	osal_start_system();

	//osal_update_timers();

}
