#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>

int fd;
int ret = 0;
int read_pin;

void sel_pin(int read_pin){	//same as original read_pin
	int write_pin;
	if(read_pin > 6 && read_pin < 10)
        printf("read the PIN: PI%d-(key%d)",read_pin,read_pin-7);
    else if(read_pin <= 6 && read_pin >=4)
        printf("read the PIN: PI%d-(key%d)",read_pin,read_pin+1);
    else if(read_pin==10)
        printf("read the PIN: PG9-(key3)");
    else if(read_pin==11)
		printf("read the PIN: PG11-(key4)");
}

int main(int argc, char *argv[])
{
	unsigned int i;
	int num_pin = 0;
	fd = open("/dev/io_control",O_RDWR);	//open io_control
	if(fd < 0)
	{
		perror("error to open /dev/io_control_dev");
		exit(1);
	}
	while(1)
	{
		ret = read(fd, &read_pin,4);		//read_pin is a10_driver->rval
        	if(ret < 0)
        	{
				perror("error to read\n");
            	exit(1);
        	} 
		for(num_pin = 0 ; num_pin < 12 ; num_pin++ ){	//find the bits' value
			if(read_pin&0x00000001)
				sel_pin(num_pin)+7;
			read_pin>>=1;
		}
		printf("\n");
	}
	close(fd);
	return 0;
}