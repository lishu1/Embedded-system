void setup() {
  // put your setup code here, to run once:
    Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
    int val;
    int dat;
    val=analogRead(0);
    dat=(500*val)/1024;
    Serial.print("Temp:");
    Serial.print(dat);
    Serial.println("C");
    delay(500);
}
