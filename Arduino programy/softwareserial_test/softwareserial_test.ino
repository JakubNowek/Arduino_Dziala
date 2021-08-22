#include <SoftwareSerial.h>
SoftwareSerial mySerial(9, 8); // RX, TX
String ASCII = "ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz";
int buff;
void setup()
{
 Serial.begin(9600);
 mySerial.begin(9600);
 delay(1000);
 }
 
void loop(){
  while(mySerial.available()>0) //czytanie calej informacji o aktualnej dacie
  {
    buff = mySerial.read();
    if(buff<48 || buff>57)
    Serial.print(ASCII[buff-65]);
    else {Serial.print(buff - 48);}
    //Serial.print('t');
    //for(int i = 26;i<40;i++)
    //Serial.print(ASCII[i]);
    
    
    
    //Serial.print(mySerial.read());
    //else{Serial.print(mySerial.read());}
  //}
 //String IncomingString="";
 //boolean StringReady = false;
 //while(mySerial.available()){
   //IncomingString=mySerial.readString();
   //StringReady= true;
  //}
       //if (StringReady){
   // Serial.println("Received String: " + IncomingString);
 }
 delay(1000);
   Serial.print('\n');
 }
