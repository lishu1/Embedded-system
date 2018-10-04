#include<SoftwareSerial.h>
SoftwareSerial mySerial(2,3);	//uart serial ports
int red=5;
int button=11;
int alarm=12;
int led=13;
int sensorstate,buttonstate;
int melody[] = {33};
int a=0;

void setup(){
	Serial.begin(115200);
	mySerial.begin(115200);		//bound rate=115200
	pinMode(2, INPUT);
	pinMode(3, OUTPUT);
	pinMode(alarm,OUTPUT);
	pinMode(led,OUTPUT);
	pinMode(button,INPUT);
	pinMode(red,INPUT);
}

void loop() {
	sensorstate=digitalRead(red);
	buttonstate=digitalRead(button);
	if(sensorstate==HIGH){
		mySerial.write("A");
		Serial.write("A\n");
		for(int i=0;i<6;i++){
			digitalWrite(led,HIGH);
			tone(12,melody[0],1000);
			delay(100);
			digitalWrite(led,LOW);
		}
    }
	else if(buttonstate==HIGH){
		a=0;
		mySerial.write("D");
		Serial.write("D\n");
	}
    else{
		a=0;
		mySerial.write("Z");
        Serial.write("Z\n");
    }
    delay(100);
}