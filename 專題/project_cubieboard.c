#include<stdio.h>
#include<iostream>
#include<fcntl.h>
#include<unistd.h>
#include<termios.h>
#include<stdlib.h>
#include<sys/ioctl.h>
#include<ctime>
#include<fstream>
#include<sys/types.h>
#include<sys/wait.h>
int num=6;
using namespace std;
int main (){
	struct termios toptions;
	time_t t1,t2;
	int fd,state;
	char a[2],buf[2];
	fstream fs;				//a file to record photo's number
	fs.open("count.txt",fstream::out);
	fs << 0;
	fs.close();
	fd = open("/dev/ttyS0", O_RDWR | O_NOCTTY);	//uart's correlation
	speed_t brate=115200;	//bound rate
	cfsetispeed(&toptions, brate);
	cfsetospeed(&toptions, brate);
	t1=time(NULL);			//record now time
	while(1){
		fs.open("/var/www/project/web/state.txt",fstream::in);
		fs >> state;		//read state from web
		fs.close();
		if(state==0){		//state==0 photo mode
			read(fd,buf,1);	//read from arduino
			cout << "buf:" << buf[0] << endl;
			if(buf[0]=='A'){//someone is in the house
				pid_t pid;
				pid=fork();
				if(pid==0){
					char *cmd[2];
					cmd[0]="./command1";
					cmd[1]=0;
					execvp(cmd[0],cmd);
					sleep(1000);
				}
				else{
					wait(NULL);
				}
				t1=time(NULL);
			}
			else if(buf[0]=='U'){
				num++;
				cout << "num:" << num << endl;
			}
			else if(buf[0]=='D'){
				if(num!=1){
					num--;
					cout << "num:" << num << endl;
				}
			}
			t2=time(NULL);
			cout << (t2-t1) << endl;
			if((t2-t1)>=10*num){
				pid_t pid;
				pid=fork();
				if(pid==0){
					char *cmd[2];
					cmd[0]="./command2";
					cmd[1]=0;
					execvp(cmd[0],cmd);
					sleep(1000);
				}
				else{
					wait(NULL);
				}
				cout << "time:" << (t2-t1) << endl;
				t1=time(NULL);
			}
		}
		else{				//state==1 real time mode
			cout << "someone uses now" << endl;
		}
	}
	close(fd);
}