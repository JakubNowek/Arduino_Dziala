/*
74HC595 Shift Register with 7-segment LED display
  74hc595-7segdisplay.ino
  Count in hex from 0-F and display on 7-segment Common Cathode LED display
 
  DroneBot Workshop 2020
  https://dronebotworkshop.com
*/
 
// Define Connections to 74HC595
#define TIME 3  //Zmienna okreslajaca czas na, ktorym ma nastapic przelaczenie wyswietlacza 
// ST_CP pin 12
const int latchPin = 10;
// SH_CP pin 11
const int clockPin = 11;
// DS pin 14
const int dataPin = 12;

const int dig_1 = 7;
const int dig_2 = 6;
const int dig_3 = 5;
const int dig_4 = 4;
const int dig_5 = 3;
const int dig_6 = 2;

 
// Patterns for characters 0,1,2,3,4,5,6,7,8,9
int datArray[16] = {~B11111100, ~B01100000, ~B11011010, ~B11110010, ~B01100110, ~B10110110, ~B10111110, ~B11100000, ~B11111110, ~B11110110};
 
void setup ()
{
  // Setup pins as Outputs
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(dig_1, OUTPUT);
  pinMode(dig_2, OUTPUT);
  pinMode(dig_3, OUTPUT);
  pinMode(dig_4, OUTPUT);
  pinMode(dig_5, OUTPUT);
  pinMode(dig_6, OUTPUT);
  digitalWrite(dig_1,LOW);
  digitalWrite(dig_2,HIGH);
  digitalWrite(dig_3,HIGH);
  digitalWrite(dig_4,HIGH);
  digitalWrite(dig_5,HIGH);
  digitalWrite(dig_6,HIGH);
  
}

void print(int digit)
{

/*--------------------ONE DIGIT DISPLAY-----------------------*/
    // ST_CP LOW to keep LEDs from changing while reading serial data
    digitalWrite(latchPin, LOW);
    // Shift out the bits
    shiftOut(dataPin, clockPin, MSBFIRST, digit);
    // ST_CP HIGH change LEDs
    digitalWrite(latchPin, HIGH);
    //delay(2000);
/*------------------------------------------------------------*/
//delay(TIME);

}


void loop()
{
//dig1
print(datArray[1]);
digitalWrite(dig_1,HIGH); //zalaczenie wyswiwietlacza #1
delay(TIME);
digitalWrite(dig_1,LOW); //wylaczenie wyswietlacza #1


//dig2 
print(datArray[2]);
digitalWrite(dig_2,LOW); //zalaczenie wyswiwietlacza #2
delay(TIME);
digitalWrite(dig_2,HIGH); //wylaczenie wyswietlacza #2


//dig3
print(datArray[3]);
digitalWrite(dig_3,LOW);
delay(TIME);
digitalWrite(dig_3,HIGH);

//dig4
print(datArray[4]);
digitalWrite(dig_4,LOW);
delay(TIME);
digitalWrite(dig_4,HIGH);

//dig5
print(datArray[5]);
digitalWrite(dig_5,LOW);
delay(TIME);
digitalWrite(dig_5,HIGH);

//dig6
print(datArray[6]);
digitalWrite(dig_6,LOW);
delay(TIME);
digitalWrite(dig_6,HIGH);


}
