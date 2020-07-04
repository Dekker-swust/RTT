/*
* Copyright (c) 2006-2018, RT-Thread Development Team
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date           Author       Notes
* 2018-10-17     flybreak      the first version
*/

#include <rtdevice.h>

#define LED_thread_PRIORITY   	  	20   //define LED thread PRIORITY is 20


void led_init(void)
{
    rt_pin_mode(LED1_PIN, PIN_MODE_OUTPUT);
		rt_pin_mode(LED2_PIN, PIN_MODE_OUTPUT);

}


static void led_shine_entry(void *parameter) 
{

		while (1)
    {
//			rt_pin_write(LED1_PIN, LED_STA);
//			rt_pin_write(LED2_PIN, LED_STA);
//			LED_STA = !LED_STA;
			rt_thread_mdelay(500);
    }
}

static int LED_Thread_Init()
{
	  rt_err_t tid = RT_EOK;
	
		rt_thread_t thread = rt_thread_create("ledshine" , led_shine_entry , RT_NULL , 1024 , LED_thread_PRIORITY ,20);

		if(thread != RT_NULL)
			rt_thread_startup(thread);
		else tid = RT_ERROR;
		
		return tid;
}

INIT_APP_EXPORT(LED_Thread_Init);
