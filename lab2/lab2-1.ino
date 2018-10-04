void setup() {
  // put your setup code here, to run once:
    Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
    int l,r;
    l=analogRead(0);
    r=analogRead(1);
    if(l>r){
      
    }
    else{
      
    }
    Serial.print("L:");
    Serial.println(l,DEC);
    Serial.print("R:");
    Serial.println(r,DEC);
    delay(100);
}
