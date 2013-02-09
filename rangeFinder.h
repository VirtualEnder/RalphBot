
void getInches() {
  digitalWrite(rangeActivePin, LOW);
  float sensorvalue = analogRead(rangePin); //get analog sensor value from pin 0
  float inchvalue = 0.49609375* sensorvalue; //convert to inches
  lcd.clear();
  lcd.print("Dist: ");
  lcd.print(inchvalue);
  //Serial.print("Dist: ");
  //Serial.print(inchvalue);
  digitalWrite(rangeActivePin, HIGH);
}
