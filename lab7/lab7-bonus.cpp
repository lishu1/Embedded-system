#include<cstdio>
#include<iostream>
#include<string>
#include<unistd.h>
#include<cstdlib>
#include<cstring>
#include<sstream>
#include<linux/types.h>
#include<linux/spi/spidev.h>
#include<sys/ioctl.h>
#include<fcntl.h>
#include<getopt.h>
using namespace std;
int main(){
    char *cmd[4];
    int fd,read_pin;
    fd = open("/dev/io_control",O_RDWR);	//use io_control
    for(int i=0;i<4;i++)
		cmd[i]=new char[10];
    while(1){
        read(fd,&read_pin,4);				//io_control is modified when last lab
		if(read_pin == 128)					//if key0 is pressed
			break;
    }
    printf("take photo start\n");
    cmd[0]="./v4l2grab";
    cmd[1]="-o";
    cmd[2]="image.jpg";
    cmd[3]=0;
    execvp(cmd[0],cmd); 					//use execvp to deliver command
    printf("take photo finish\n");
    return 0;
}
