/*
 * Copyright (C) 2018 Shanghai Eastsoft Microelectronics Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2019-01-28     wangyq        the first version
 */

#include <rtthread.h>
#include <rtdevice.h>


extern void led_init(void);

int main(void)
{
    /* set PC08 pin mode to output */
	  int LED_STA = 1;
	
		led_init();
	
    while (1)
    {

			rt_pin_write(LED1_PIN, LED_STA);
			LED_STA = !LED_STA;
			rt_thread_mdelay(500);
    }
    return RT_EOK;
}
