#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/fcntl.h>
#include <sys/mman.h>

#define IVSHMEM_BASE_ADDRESS 0x275000000
#define IVSHMEM_SIZE 0x1000

int main(void) {
    int fd = open("/dev/mem", O_RDWR | O_SYNC);
    if (fd < 0) {
        perror("/dev/mem");
        fprintf(stderr, "Please run this program as root (for example with sudo)\n");
        exit(1);
    }

    uint8_t *comm_region_address = (uint8_t*)mmap(NULL, IVSHMEM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, IVSHMEM_BASE_ADDRESS);

    if (comm_region_address == NULL) {
        perror("mmap()");
        exit(1);
    }

    uint8_t val = 1;
    
    for(int i=0; i<10000; i++) {
	printf("CICLO %02d\t", i);
        usleep(1000000);
        val = 1 - val;
        comm_region_address[0] = val;
	printf("%u\n", comm_region_address[0]);
    }

    munmap(comm_region_address, IVSHMEM_SIZE);
    close(fd);

    return 0 ;
}
