#ifndef APPLICATION_H
#define APPLICATION_H

#include "osal.h"
#include "osal_timer.h"
#include "osal_event.h"
#include "osal_memory.h"
#include "osal_msg.h"

//全局变量声明
/*****************************************************************************/

typedef struct
{
	osal_event_hdr_t hdr; //操作系统事件结构
	unsigned char *Data;  //命令帧操作数
} General_SerialData_t;	  // OSAL中通用串口打印消息的格式结构体

/*****************************************************************************/

//所有任务的任务ID、初始化函数、事件处理函数、任务事件都统一在此文件声明或定义
/*****************************************************************************/

//任务ID声明
extern uint8 LED_TaskID;
extern uint8 LED0_TaskID;

//任务初始化函数声明
extern void Serial_Task_Init(uint8 task_id);
extern void LED4_Task_Init(uint8 task_id);

//任务事件处理函数声明
extern uint16 LED4_Task_EventProcess(uint8 task_id,uint16 task_event);
extern uint16 Serial_Task_EventProcess(uint8 task_id, uint16 task_event);

extern void osal_printf(char *format, ...); //打印通用串口数据

//任务事件定义
//系统消息事件
#define SYS_EVENT_MSG 0x8000

// SYSTIC事件定义
#define SYSCLK 0X0001 // SYSCLK2秒事件
// LED任务事件定义
//#define LED_LIGHT 0X0001 // LED事件事件
//串口通信任务系统消息事件定义
#define OSAL_LED0 0X0002 // LED0事件

/*****************************************************************************/
void osal_main(void);
#endif
