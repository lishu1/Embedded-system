#include<cstdio>
#include<iostream>
#include<string>
#include<unistd.h>
#include<cstdlib>
#include<cstring>
#include<fstream>
using namespace std;

int main(){
    string str;
    string msg;
    fstream fileout;
    str=getenv("QUERY_STRING");	//read input from website
    if(str.length() >= 4){		//only read number
        str=str.substr(4);
    }
    if(str.length() == 1 ){		//read number between 0-7
    	if(str[0] <= '7' && str[0] >= '0'){
    		fileout.open("/root/lab6/Data.txt",fstream::out);
			fileout << str;		//write to txt;
			fileout.close();
			msg="OK<br>";
    	}else{
			msg="error <br>";
    	}
    }
    cout << "Content-Type: text/html\n\n" << endl;	//website information
    cout << "<form method=\"GET\">" << endl;
    cout << "Command:" << msg << endl;
    cout << "<input type=\"text\" name=\"cmd\"></form>" << endl;
    return 0;
}
