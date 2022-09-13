/*
 * Jailhouse, a Linux-based partitioning hypervisor
 *
 * Copyright (c) ARM Limited, 2014
 *
 * Authors:
 *  Jean-Philippe Brucker <jean-philippe.brucker@arm.com>
 *
 * This work is licensed under the terms of the GNU GPL, version 2.  See
 * the COPYING file in the top-level directory.
 */

#include <inmate.h>
#define GPIO_BASE_ADDRESS 0x02200000
#define GPIO_PIN_J21_12_OFFSET 0x15000
#define GPIO_PIN_J21_13_OFFSET 0x150a0
#define GPIO_PIN_ADDRESS(offset) (GPIO_BASE_ADDRESS + (offset))
#define GPIO_PAGE_SIZE 0x100000

#define PADCTL_BASE_ADDRESS 0x02430000
#define PADCTL_SIZE	0x15000
#define PADCTL_PIN_OFFSET 0x1040
#define PADCTL_ADDRESS(offset) (PADCTL_BASE_ADDRESS + (offset))

#define IVSHMEM_BASE_ADDRESS 0x275000000
#define IVSHMEM_SIZE 0x1000

typedef volatile struct {
    u32 ENABLE_CONFIG;		//offset 0x00
    u32 DEBOUNCE_THRESHOLD;	//offset 0x04
    u32 INPUT;			//offset 0x08
    u32 OUTPUT_CONTROL;		//offset 0x0c
    u32 OUTPUT_VALUE;		//offset 0x10
    u32 INTERRUPT_CLEAR;	//offset 0x14
}  GPIO_pin;


void inmate_main(void)
{
	unsigned volatile int i = 0, j;
	u8 led_status = 0;
	map_range((void*)GPIO_BASE_ADDRESS, GPIO_PAGE_SIZE, MAP_UNCACHED);
	map_range((void*)PADCTL_BASE_ADDRESS, PADCTL_SIZE, MAP_UNCACHED);
	map_range((void*)IVSHMEM_BASE_ADDRESS, IVSHMEM_SIZE, MAP_UNCACHED);
	
	mmio_write8((void*)PADCTL_ADDRESS(PADCTL_PIN_OFFSET), 0);
	GPIO_pin * gpio_pin = (GPIO_pin *)GPIO_PIN_ADDRESS(GPIO_PIN_J21_12_OFFSET);
	gpio_pin->OUTPUT_CONTROL = 0x0;
	gpio_pin->ENABLE_CONFIG = 0x3;
	gpio_pin->OUTPUT_VALUE = led_status;

	mmio_write8((void*)IVSHMEM_BASE_ADDRESS, led_status);			// setta a 0 lo stato del led condiviso
	
	while(++i) {
		for (j = 0; j < 1000; j++);
		//printk("Hello %d from cell!\n", i);
		heartbeat();
		if (i>=10000) {
			i=1;
			led_status = mmio_read8((void*)IVSHMEM_BASE_ADDRESS);
			printk("VALORE LETTO: %u\n", led_status);
			//accendi led
			gpio_pin->OUTPUT_VALUE = led_status;
			printk("SETTATO GPIO : %u\n", led_status);
		}
	}
}
