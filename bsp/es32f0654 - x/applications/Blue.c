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

#define BLE_thread_PRIORITY   	  	11   //define LED thread PRIORITY is 20
#define UART_NAME					    "uart0"
#define RX_NUM_MAX		4

static struct rt_semaphore rx_sem;
rt_device_t serial; 

uint8_t tx_buf[4] = {0xAA,0x00,0x00,0xEE};//定义数据帧格式，包头为AA ,包尾为BB
uint8_t Rx_buf[RX_NUM_MAX];
uint8_t rx_num = 0;


static void Clear_uart_buff()
{
	rx_num = 0;
}

static void RX_ANA()
{
	 //rt_pin_write(LED1_PIN, Rx_buf[1]);
	 rt_pin_write(LED2_PIN, Rx_buf[2]);
	 Clear_uart_buff();
}
/*********recive return *********/
static rt_err_t uart_input(rt_device_t dev, rt_size_t size)
{
    rt_sem_release(&rx_sem);
    return RT_EOK;
}


void Bluetooth_init(void)
{
//		rt_pin_write(LED1_PIN, PIN_HIGH);
//		rt_pin_write(LED2_PIN, PIN_HIGH);
}


static void Ble_thread_entry(void *parameter) 
{
	
		char ch;

    rt_thread_mdelay(100);
	
		while (1)
    {
						
				while (rt_device_read(serial, -1, &ch, 1) != 1)
				{						
						rt_sem_take(&rx_sem, RT_WAITING_FOREVER);
				}

//				rt_kprintf("%02x",ch);
				
				if(ch == '\xBB' && rx_num == 0)
					Rx_buf[rx_num++] = ch;
				else if(rx_num > 0 && rx_num  < RX_NUM_MAX-1)
					Rx_buf[rx_num++] = ch;
				else if(ch == '\xEE' && rx_num  == RX_NUM_MAX-1)
				{
					Rx_buf[rx_num] = ch;
//					rt_kprintf("\r\nover\r\n");
					RX_ANA();
				}
				
//				rt_device_write(serial,0,"123",3);
//				rt_thread_mdelay(500);
    }
}

static int BLE_Thread_Init()
{
	  rt_err_t tid = RT_EOK;
	
	  serial = rt_device_find (UART_NAME);
	  if(!serial)
			return RT_ERROR;
		
    rt_sem_init(&rx_sem, "rx_sem", 0, RT_IPC_FLAG_FIFO);
    rt_device_open(serial, RT_DEVICE_FLAG_INT_RX);
    rt_device_set_rx_indicate(serial, uart_input);

		rt_thread_t thread = rt_thread_create("BLE_thread" , Ble_thread_entry , RT_NULL , 1024 , BLE_thread_PRIORITY ,20);

		if(thread != RT_NULL)
			rt_thread_startup(thread);
		else tid = RT_ERROR;
		
		return tid;
}

INIT_APP_EXPORT(BLE_Thread_Init);
