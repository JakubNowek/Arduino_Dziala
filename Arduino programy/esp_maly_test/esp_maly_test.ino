void setup()
{
 Serial.begin(9600);
}
void loop() {
  //Write '123' to Serial
  Serial.write("123");
  delay(1000);
}
