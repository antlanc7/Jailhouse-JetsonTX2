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

void inmate_main(void)
{
	unsigned volatile int i = 0, j;
	u32 led_status = 0;
	map_range((void*)GPIO_BASE_ADDRESS, GPIO_PAGE_SIZE, MAP_UNCACHED);
	map_range((void*)PADCTL_BASE_ADDRESS, PADCTL_SIZE, MAP_UNCACHED);
	
	mmio_write8((void*)PADCTL_ADDRESS(PADCTL_PIN_OFFSET), 0);
	mmio_write8((void*)(GPIO_PIN_ADDRESS(GPIO_PIN_J21_12_OFFSET) + 0xc), 0);	//OUTPUT_CONTROL
	mmio_write8((void*)GPIO_PIN_ADDRESS(GPIO_PIN_J21_12_OFFSET), 0x3);		//ENABLE_CONFIG
	
	/*
	 * The cell config can set up a mapping to access UARTx instead of UART0
	 */
	while(++i) {
		for (j = 0; j < 1000; j++);
		printk("Hello %d from cell!\n", i);
		heartbeat();
		if (i>=1000) {
			i=1;
			led_status = 1 - led_status;
			//accendi led
			mmio_write8((void*)(GPIO_PIN_ADDRESS(GPIO_PIN_J21_12_OFFSET) + 0x10), led_status);
			printk("Written led_status : %u\n", led_status);
		}
	}

	/* lr should be 0, so a return will go back to the reset vector */
}
