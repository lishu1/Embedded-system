#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<fstream>
using namespace std;

int write_ret;
int write_on = 7;
int write_off = 15;

int main(int argc,char *argv[])
{
	int fd,input;
	fstream fs;
	fd = open("/dev/io_control",O_RDWR);	//read io_control
	if(fd < 0)
	{
		perror("error to open /dev/io_control\n");
		exit(1);
	}
	while(1)
	{
		fs.open("/root/lab6/Data.txt",fstream::in);
		fs >> input;						//read number from txt
		fs.close();
		write_on = input+7;					//input.led 0-7 write_on 7-14
		write_ret = write(fd,&write_on,4);
		write_ret = write(fd,&write_off,4);	//if change need off and turn on another
	}
	close(fd);
	return 0;
}