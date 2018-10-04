#include<SoftwareSerial.h>
SoftwareSerial mySerial(2,3);	//uart serial ports
char msg_byte;
int check_G = 0;
int get_H = 0;
int get_G = 0;
void setup(){
	pinMode(2, INPUT);
	pinMode(3, OUTPUT);
	mySerial.begin(9600);		//bound rate=115200
	Serial.begin(9600);
}
void loop(){
	if(mySerial.available() ){
        msg_byte = mySerial.read();	//read uart message
        Serial.write(msg_byte);
		if( msg_byte == 'H'  && get_H == 0 ){	//if get H first time
			get_H = 1;							//record
			mySerial.write("HHHHHH");			//send many Hs to let cubieboard receive easier
			Serial.write("Cubie Say Hello!\n");	 
		}else if( msg_byte != 'G' && get_G == 0  && get_H ==1){	//if get H but not get G
			mySerial.write("HHHHHH");			//send many Hs to let cubieboard receive easier
		}else if(  msg_byte == 'G'  && g++ get_G ==0  && get_H ==1){//if get G first time
			get_G = 1;
			mySerial.write("GGGGGG");			//send many Gs to let cubieboard receive easier
			Serial.write("Cubie Say Goodbye!\n");
		}else if(get_G == 1 ){					//if get G
			mySerial.write("GGGGGG");			//send many Gs to let cubieboard receive easier
		}
	}	
}
