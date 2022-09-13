package main
import (
	"fmt"
	"syscall"
	"os"
	"github.com/gin-gonic/gin"
        "net/http"
)

const IVSHMEM_PAGE_ADDRESS = 0x275000000;
const IVSHMEM_PAGE_SIZE = 0x1000

func main(){
	fmt.Println("Helo wolr");
	devmem, err := syscall.Open("/dev/mem", syscall.O_RDWR | syscall.O_SYNC, 0);
	if (err != nil) {
		fmt.Println(err);
		os.Exit(1);
	}
	mem, _ := syscall.Mmap(devmem, IVSHMEM_PAGE_ADDRESS, IVSHMEM_PAGE_SIZE, syscall.PROT_READ | syscall.PROT_WRITE, syscall.MAP_SHARED);

	router := gin.Default();
	router.LoadHTMLGlob("*.html");
	router.GET("/", func(c *gin.Context) {
		c.HTML(http.StatusOK, "index.html", nil);
	});
	router.GET("/toggle",func(c *gin.Context) {
		mem[0x00] = 1 - mem[0x00];	//OUTPUT_VALUE
	});
	router.Run(":8000");
	
}
