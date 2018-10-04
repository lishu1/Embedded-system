float tempC;
int reading;
int tempPin=0;
void setup() {
  // put your setup code here, to run once:
    Serial.begin(9600);
    analogReference(INTERNAL);
}

void loop() {
  // put your main code here, to run repeatedly:
    reading=analogRead(tempPin);
    tempC=reading/9.31;
    Serial.print("Temp:");
    Serial.print(tempC);
    Serial.println("C");
    delay(500);
}
