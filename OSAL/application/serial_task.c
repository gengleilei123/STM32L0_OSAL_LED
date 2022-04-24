/****************************************************************************************
 * 文件名  ：serial_task.c
 * 描述    ：系统串口通信任务
 * 开发平台：
 * 库版本  ：
 ***************************************************************************************/
#include "application.h"

#include <string.h>
#include <stdarg.h>
#include <stdio.h>

#include "gpio.h"
//#include "usart.h"
//#include "led.h"

uint8 LED_TaskID; //系统串口通信任务ID
uint8 LED0_TaskID;//LED0任务ID

/*********************************************************************
 * LOCAL FUNCTION PROTOTYPES
 */
typedef enum
{
	LED_OFF,
	LED_ON,
} Led_State;

typedef struct sLed_State
{
	unsigned char led_states;
} Led_States;

/*********************************************************************
 * FUNCTIONS
 *********************************************************************/
// LED任务初始化（LED硬件初始化）
static Led_States ledstates;
static Led_States ledstates0;

void led_on(void)
{
	LED3(0);
}

void led_off(void)
{
	LED3(1);
}

void led_on0(void)
{
	LED4(0);
}

void led_off0(void)
{
	LED4(1);
}

void Serial_Task_Init(uint8 task_id)
{
	LED_TaskID = task_id;

	//串口配置初始化
	//MX_GPIO_Init();
	// Usart_Init(COM1,115200,STOP_1_B,WROD_LEN_8B,PARITY_NO,HARD_NO);
	// LED_Init();
	ledstates.led_states = LED_OFF;
	//ledstates0.led_states = LED_OFF;
}

void LED4_Task_Init(uint8 task_id)
{
	LED0_TaskID = task_id;

	//串口配置初始化
	MX_GPIO_Init();
	// Usart_Init(COM1,115200,STOP_1_B,WROD_LEN_8B,PARITY_NO,HARD_NO);
	// LED_Init();
	ledstates0.led_states = LED_OFF;
}
//串口通信任务

uint16 LED4_Task_EventProcess(uint8 task_id,uint16 task_event)
{
	Led_States *const led0 = &ledstates0;
	if (task_event & SYS_EVENT_MSG) //判断SYSCLK消息事件
	{
		osal_sys_msg_t *MSGpkt; //定义一个指向接受系统消息结构体的指针
		//从消息队列获取消息
		MSGpkt = (osal_sys_msg_t *)osal_msg_receive(task_id);

		while (MSGpkt)
		{
			switch (led0->led_states)
			{
			case LED_ON:
				switch (MSGpkt->hdr.event) //判断消息事件
				{
				case OSAL_LED0:
					led_off0();
					led0->led_states = LED_OFF;
					break;
				default:
					break;
				}
				break;
			case LED_OFF:
				switch (MSGpkt->hdr.event) //判断消息事件
				{
				case OSAL_LED0:
					led_on0();
					led0->led_states = LED_ON;
					break;
				default:
					break;
				}
				break;

				break;
			default:
				break;
			}

			// Release the memory
			osal_msg_deallocate((uint8 *)MSGpkt);

			// Next  获取下一个消息
			MSGpkt = (osal_sys_msg_t *)osal_msg_receive(task_id);
		}

		// return unprocessed events
		return (task_event ^ SYS_EVENT_MSG);
	}

	return 0;
}


uint16 Serial_Task_EventProcess(uint8 task_id, uint16 task_event)
{
	Led_States *const led = &ledstates;
	if (task_event & SYS_EVENT_MSG) //判断SYSCLK消息事件
	{
		osal_sys_msg_t *MSGpkt; //定义一个指向接受系统消息结构体的指针
		//从消息队列获取消息
		MSGpkt = (osal_sys_msg_t *)osal_msg_receive(task_id);

		while (MSGpkt)
		{
			switch (led->led_states)
			{
			case LED_ON:
				switch (MSGpkt->hdr.event) //判断消息事件
				{
				case SYSCLK:
					led_off();
					led->led_states = LED_OFF;
					break;
				default:
					break;
				}
				break;
			case LED_OFF:
				switch (MSGpkt->hdr.event) //判断消息事件
				{
				case SYSCLK:
					led_on();
					led->led_states = LED_ON;
					break;
				default:
					break;
				}
				break;

				break;
			default:
				break;
			}

			// Release the memory
			osal_msg_deallocate((uint8 *)MSGpkt);

			// Next  获取下一个消息
			MSGpkt = (osal_sys_msg_t *)osal_msg_receive(task_id);
		}

		// return unprocessed events
		return (task_event ^ SYS_EVENT_MSG);
	}

	return 0;
}
