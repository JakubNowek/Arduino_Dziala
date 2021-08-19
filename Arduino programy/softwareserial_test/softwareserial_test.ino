#include <SoftwareSerial.h>
SoftwareSerial mySerial(9, 8); // RX, TX
 
void setup()
{
 Serial.begin(9600);
 mySerial.begin(9600);
 delay(1000);
 }
 
void loop(){
  while(mySerial.available()) //czytanie calej informacji o aktualnej dacie
  {
  Serial.print(mySerial.read()-48);
  }
 //String IncomingString="";
 //boolean StringReady = false;
 //while(mySerial.available()){
   //IncomingString=mySerial.readString();
   //StringReady= true;
  //}
       //if (StringReady){
   // Serial.println("Received String: " + IncomingString);
 // }
 delay(1000);
   Serial.print('\n');
 }
