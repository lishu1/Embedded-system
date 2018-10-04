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
int write_off = 15;
int write_all_on = 16;
int write_ret;
int sel_pin(int read_pin){	//same as basic1
	int write_pin;
	if(read_pin > 6 && read_pin < 10){
        printf("read the PIN: PI%d-(key%d)",read_pin,read_pin-7);
        write_pin = read_pin-7;
    }else if(read_pin <= 6 && read_pin >=4){
        printf("read the PIN: PI%d-(key%d)",read_pin,read_pin+1);
        write_pin = read_pin+1;
    }else if(read_pin==10){
        printf("read the PIN: PG9-(key3)");
        write_pin = 3;
    }else if(read_pin==11){
		printf("read the PIN: PG11-(key4)");
        write_pin = 4;
    }else
        write_pin = write_off;
	return write_pin;
}

int main(int argc, char *argv[])
{
	unsigned int i;
	int num_pin = 0;
	fd = open("/dev/io_control",O_RDWR);	//open io_control
	if(fd < 0){
		perror("error to open /dev/io_control_dev");
		exit(1);
	}
	while(1){
		ret = read(fd, &read_pin,4);		//read_pin is a10_driver->rval
        if(ret < 0){
			perror("error to read\n");
            exit(1);
        } 
		read_pin=read_pin;
		for(num_pin = 0 ; num_pin < 12 ; num_pin++ ){
			if(read_pin&0x00000001){
				write_on  = sel_pin(num_pin);
				if( write_on==3 )			//set key3=turn off all
					write_on=write_off;
				else if( write_on==4 )		//set key4=trun on all
					write_on=write_all_on;
				else
					write_on+=7;
				write(fd , &write_on ,4  );
			}
			read_pin>>=1;
		}
		printf("\n");
	}
	close(fd);
	return 0;
}

