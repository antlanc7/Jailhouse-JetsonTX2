#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/fcntl.h>
#include <sys/mman.h>

#define GPIO_PIN    0x02215000 // J.00 GPIO address (GPIO 392)
//#define GPIO_PIN    0x022150a0 // J.05 GPIO address (GPIO 397)
#define DAP1_SCLK   0x02431040 // Control pad register address

typedef volatile struct {
    uint32_t ENABLE_CONFIG;		//offset 0x00
    uint32_t DEBOUNCE_THRESHOLD;	//offset 0x04
    uint32_t INPUT;			//offset 0x08
    uint32_t OUTPUT_CONTROL;		//offset 0x0c
    uint32_t OUTPUT_VALUE;		//offset 0x10
    uint32_t INTERRUPT_CLEAR;		//offset 0x14
}  GPIO_pin;

int main(void) {
    int fd = open("/dev/mem", O_RDWR | O_SYNC);
    if (fd < 0) {
        perror("/dev/mem");
        fprintf(stderr, "Please run this program as root (for example with sudo)\n");
        exit(1);
    }

    uint32_t pagesize = getpagesize();
    uint32_t pagemask = pagesize - 1;

    printf("PAGESIZE: %u\n", pagesize);
	
    void *gpio_address = mmap(0, pagesize, PROT_READ | PROT_WRITE, MAP_SHARED, fd, (GPIO_PIN & ~pagemask));

    void *pad_ctl_address = mmap(0, pagesize, PROT_READ | PROT_WRITE, MAP_SHARED, fd, (DAP1_SCLK & ~pagemask));

    if (gpio_address == NULL || pad_ctl_address == NULL) {
        perror("mmap()");
        exit(1);
    }
    
    GPIO_pin *gpio_pin = ((GPIO_pin *)gpio_address + (GPIO_PIN & pagemask));

    volatile char *pad_ctl = ((char *)pad_ctl_address + (DAP1_SCLK & pagemask));

    *pad_ctl = 0x00000000; // Select GPIO

    gpio_pin->OUTPUT_CONTROL = 0x00000000; // Driven
    gpio_pin->ENABLE_CONFIG  = 0x00000003; // GPIO Enable, Out

    uint32_t val = 0x00000001;
    
    for(int i=0; i<10000; i++) {
	printf("CICLO %02d\t", i);
        usleep(1000000);
        val = val ^ 0x00000001;
        gpio_pin->OUTPUT_VALUE = val;
	printf("%d\n", val);
    }

    gpio_pin->OUTPUT_VALUE = 0x00000000;

    munmap(gpio_address, pagesize);
    munmap(pad_ctl_address, pagesize);
    close(fd);

    return 0 ;
}
