#include<SoftwareSerial.h>
#include <Servo.h>
Servo myservo;
SoftwareSerial mySerial(2,3);	//uart serial ports
int red=5;						//Infrared sensor
int button1=10;					//button up sensor
int button2=11;					//button down sensor
int alarm=12;					//buzzer sensor
int led=13;						//led
int sensorstate,button1state,button2state;
int pos = 180;

void setup(){
	Serial.begin(115200);
	mySerial.begin(115200);		//bound rate=115200
	pinMode(2, INPUT);
	pinMode(3, OUTPUT);
	pinMode(alarm,OUTPUT);
	pinMode(led,OUTPUT);
	pinMode(button1,INPUT);
	pinMode(button2,INPUT);
	pinMode(red,INPUT);
	myservo.attach(9);
}

void loop() {
	sensorstate=digitalRead(red);
	button1state=digitalRead(button1);
	button2state=digitalRead(button2);
	if(sensorstate==HIGH){		//if someone is in the house
		mySerial.write("A");	//tell cubieboard
		Serial.write("A\n");
		for(;pos>0;pos--){
			myservo.write(pos);
			delay(10);
		};
		for(int i=0;i<6;i++){
			digitalWrite(led,HIGH);	//turn led on
			tone(12,33,1000);	   	//turn buzzer on
			delay(100);
			digitalWrite(led,LOW); 	//sparkle
		}
    }
	else if(button1state==HIGH){   	//press up button
		mySerial.write("U");		//tell cubieboard
		Serial.write("U\n");
	}
	else if(button2state==HIGH){	//press down button
		mySerial.write("D");		//tell cubieboard
		Serial.write("D\n");
	}
    delay(100);
}
