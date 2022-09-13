package main
import (
	"fmt"
	"syscall"
	"os"
	"github.com/gin-gonic/gin"
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

	mem[0x00] = 0x03;	//ENABLE_CONFIG
	mem[0x0c] = 0x00;	//OUTPUT_CONTROL
	router := gin.Default();
	router.GET("/toggle",func(c *gin.Context) {
		mem[0x10] = 1 - mem[0x10];	//OUTPUT_VALUE
	});
	router.Run(":8000");
	
}
