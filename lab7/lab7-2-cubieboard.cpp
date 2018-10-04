#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<termios.h>
#include<stdlib.h>
#include<sys/ioctl.h>
#include<iostream>
using namespace std;
int main (){
	struct termios toptions;
	int fd;
	fd = open("/dev/ttyS0", O_RDWR | O_NOCTTY);	//uart's correlation
	speed_t brate=115200;	//bound rate
	cfsetispeed(&toptions, brate);
	cfsetospeed(&toptions, brate);
	char buf;
	while(buf!='H'){		//break until read H from arduino
		write(fd,"HHHHHHHHHHHHH",12);	//give many Hs to let arduino receive easier
		read(fd,buf,1);
	}
	cout << "Arduino say hello!" << endl;
	while(buf!='G'){		//break until read G from arduino
		write(fd,"GGGGGGGGGGGG",12);	//give many Gs to let arduino receive easier
		read(fd,buf,1);
	}
	cout << "Arduino say goodbye!" << endl;
	close(fd);
}
