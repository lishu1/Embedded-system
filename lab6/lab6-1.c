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
int write_on = 7;
int write_off = 15;	//all LED off
int write_ret;

int main(int argc, char *argv[])
{
	unsigned int i;

	fd = open("/dev/io_control",O_RDWR);	//read io_control
	if(fd < 0)
	{
		perror("error to open /dev/io_control_dev");
		exit(1);
	}
	
	while(1)
	{
		ret = read(fd, &read_pin,4);		//read_pin is for key
        	if(ret < 0)
        	{
				perror("error to read\n");
            	exit(1);
        	} 
  			
		if(read_pin > 6 && read_pin < 10){		//key&led 0-2 (read_pin 7-9 write_on 7-9)
			printf("read the PIN: PI%d-(key%d)\n",read_pin,read_pin-7);
			write_on = read_pin;
		}
		else if(read_pin <= 6 && read_pin >=4){	//key&led 5-7 (read_pin 4-6 write_on 12-14)
			printf("read the PIN: PI%d-(key%d)\n",read_pin,read_pin+1);
			write_on = read_pin+8;
		}
		else if(read_pin==10){					//key&led 10 (read_pin 10 write_on 10)
			printf("read the PIN: PG9-(key3)\n");
			write_on = read_pin;
		}
		else if(read_pin==11){					//key&led 11 (read_pin 11 write_on 11)
			printf("read the PIN: PG11-(key4)\n");
			write_on = read_pin;
		}
		else									//turn off LEDs
			write_on = write_off;
		write_ret = write(fd,&write_on,4);		//write_on for led
	}
	close(fd);
	return 0;
}