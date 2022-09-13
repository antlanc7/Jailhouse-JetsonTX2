package main
import (
	"fmt"
	"time"
	"syscall"
	"os"
)

const GPIO_CTL_PAGE_ADDRESS = 0x2200000;

func main(){
	fmt.Println("Helo wolr");
	devmem, err := syscall.Open("/dev/mem", syscall.O_RDWR | syscall.O_SYNC, 0);
	if (err != nil) {
		fmt.Println(err);
		os.Exit(1);
	}
	mem, _ := syscall.Mmap(devmem, GPIO_CTL_PAGE_ADDRESS + 0x15000, 0x18, syscall.PROT_READ | syscall.PROT_WRITE, syscall.MAP_SHARED);
	time.Sleep(1 * time.Second);

	mem[0x00] = 0x03;	//ENABLE_CONFIG
	mem[0x0c] = 0x00;	//OUTPUT_CONTROL
	var val byte = 0;
	for {
		val = 1 - val;
		mem[0x10] = val;	//OUTPUT_VALUE
		fmt.Println("Set Led status: " , val);
		time.Sleep(1 * time.Second);
	}
	
}
