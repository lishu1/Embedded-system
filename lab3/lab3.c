#include <Servo.h> 
 
Servo myservo;  // create servo object to control a servo 
                // twelve servo objects can be created on most boards
 
int pos = 0;    // variable to store the servo position 
int magneticpin =4 ;  //megnetic sensor pin
int vibratepin = 3;   //vibrate sensor pin
int touchpin = 5;     //touch sensor pin
unsigned state = 0;   //for servo usage
void setup() 
{ 
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object 
  attachInterrupt(1 , blink , FALLING); //interrupt (need pin3)
  pinMode(magneticpin , INPUT );
  pinMode(vibratepin , INPUT );
  pinMode(touchpin , INPUT );
  Serial.begin(9600);
} 
void loop() 
{ 
  int dir =2;  		  //0:counter clockwise 1:clockwise 2:stop
  int val_magnetic;
  int val_touch;
  int val_vibrate;
  int flag = 0;       //record last turn
  while(1){
    val_magnetic = digitalRead(magneticpin);
    val_touch = digitalRead(touchpin);
    
    if(val_touch == 1){	//touch sensor is HIGH or not
		if(state != 0 ){//vibrate sensor is used or not
			state =0;
			if(flag == 0){
				flag = 1;
				dir = 1;
			}
		}else if(val_magnetic ==1 ){ //magentic sensor is HIGH or not
			if(flag == 0){
				flag = 1;
				dir = 0;
			}
		}else{
			dir = 2;
			flag = 0;
		}
    }else{
		dir = 2;
		flag = 0;
	}
	
	if(pos == 0 && dir == 0 ){		 	//counter clockwise end and change direction
		dir = 1;
	}else if( pos == 180 && dir == 1){  //clockwise end and change direction
		dir = 0;
	}
     
	if(dir == 1){						//when clockwise plus pos
		pos++;
	}else if(dir == 0){					//when counter clockwise minus pos
		pos--;
	}
	myservo.write(pos);					//write value to motor
	delay(15);
	}

} 

void blink(){
  state++;
}