#include<iostream>
#include<cstdlib>
#include<fstream>
using namespace std;
int main(){
	int number;
	fstream fs;
	fs.open("Data.txt",fstream::in);				//open the file
	fs >> number;									//read the number
	fs.close();										//close the file
	cout << "Content-Type: text/html\n\n" << endl;	//http header of cgi
	cout << "You are the " << number;
	cout << " to this websites!!" << endl;  		//print on the website
	number += 1;									//plus 1 time
	fs.open("Data.txt",fstream::out);				//reopen the file
	fs << number;									//write the next number into the file
    fs.close();
	return 0;
}
