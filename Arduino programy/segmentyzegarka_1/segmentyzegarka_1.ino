/*
74HC595 Shift Register with 7-segment LED display
  74hc595-7segdisplay.ino
  Count in hex from 0-F and display on 7-segment Common Cathode LED display
 
  DroneBot Workshop 2020
  https://dronebotworkshop.com
*/
//Biblioteki ESP
#ifdef ESP8266
#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#else
#include <WiFi.h>
#endif
#include <time.h>
// #include <credentials.h>

/*
  The credentials.h file at least has to contain:
  char mySSID[]="your SSID";
  char myPASSWORD[]="your Password";
  It has to be placed in the libraries folder
  If you do not want a credentials file. delete the line: #include <credentials.h>
*/

#ifdef CREDENTIALS
const char* ssid = mySSID;
const char* password = myPASSWORD;
#else
const char* ssid = "UPC279E7A2";
const char* password = "6PajheTberkw";
#endif

const char* NTP_SERVER = "ch.pool.ntp.org";
const char* TZ_INFO    = "CET-1CEST-2,M3.5.0/02:00:00,M10.5.0/03:00:00";  // enter your time zone (https://remotemonitoringsystems.ca/time-zone-abbreviations.php)

tm timeinfo;
time_t now;
long unsigned lastNTPtime;
unsigned long lastEntryTime;

//Zdefiniowanie polaczenia ESP8266 do Arduino UNO
SoftwareSerial myEsp(8, 9); // RX, TX 
 
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
int numArray[16] = {B11111100, B01100000, B11011010, B11110010, B01100110, B10110110, B10111110, B11100000, B11111110, B11110110};
int digArray[6] = {7,6,5,4,3,2};
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

  Serial.begin(9600);
  //ESP setup
  myEsp.begin(9600);
  myEsp.println("\n\nNTP Time Test\n");
  WiFi.begin(ssid, password);

  int counter = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(200);
    if (++counter > 100) ESP.restart();
    myEsp.print ( "." );
  }
  myEsp.println("\n\nWiFi connected\n\n");

  configTime(0, 0, NTP_SERVER);
  // See https://github.com/nayarsystems/posix_tz_db/blob/master/zones.csv for Timezone codes for your region
  setenv("TZ", TZ_INFO, 1);

  if (getNTPtime(10)) {  // wait up to 10sec to sync
  } else {
    myEsp.println("Time not set");
    ESP.restart();
  }
  //showTime(timeinfo);
  lastNTPtime = time(&now);
  lastEntryTime = millis();
}



void print(int digit)
{
    // ST_CP LOW to keep LEDs from changing while reading serial data
    digitalWrite(latchPin, LOW);
    // Shift out the bits
    shiftOut(dataPin, clockPin, MSBFIRST, digit);
    // ST_CP HIGH change LEDs
    digitalWrite(latchPin, HIGH);
}

void printTime(int hours, int minutes, int seconds) // moze wypisywac czas albo date
{
  // #1
  print(~numArray[hours/10]);
  digitalWrite(digArray[0],HIGH); //zalaczenie wyswiwietlacza #1 (tu high/low na odwrot bo NPN zamiast PNP)
  delay(TIME);
  digitalWrite(digArray[0],LOW); //wylaczenie wyswietlacza #1
  // #2
  print(~(numArray[hours%10] | 0x01)); // dziesiata czesc godziny + separator
  digitalWrite(dig_2,LOW); //zalaczenie wyswiwietlacza #2
  delay(TIME);
  digitalWrite(dig_2,HIGH); //wylaczenie wyswietlacza #2
  // #3
  print(~numArray[minutes/10]);
  digitalWrite(dig_3,LOW);
  delay(TIME);
  digitalWrite(dig_3,HIGH);
  //#4
  print(~(numArray[minutes%10]| 0x01));// dziesiata czesc minuty + separator
  digitalWrite(dig_4,LOW);
  delay(TIME);
  digitalWrite(dig_4,HIGH);
  //#5
  print(~numArray[seconds/10]);
  digitalWrite(dig_5,LOW);
  delay(TIME);
  digitalWrite(dig_5,HIGH);
  //#6
  print(~numArray[seconds%10]);
  digitalWrite(dig_6,LOW);
  delay(TIME);
  digitalWrite(dig_6,HIGH);
  
}


void loop()
{
  getNTPtime(10);
  printTime(timeinfo.tm_hour,timeinfo.tm_min,timeinfo.tm_sec);
  delay(1000);
}

bool getNTPtime(int sec) {

  {
    uint32_t start = millis();
    do {
      time(&now);
      localtime_r(&now, &timeinfo);
      myEsp.print(".");
      delay(10);
    } while (((millis() - start) <= (1000 * sec)) && (timeinfo.tm_year < (2016 - 1900)));
    if (timeinfo.tm_year <= (2016 - 1900)) return false;  // the NTP call was not successful
    myEsp.print("now ");  myEsp.println(now);
    char time_output[30];
    strftime(time_output, 30, "%a  %d-%m-%y %T", localtime(&now));
    myEsp.println(time_output);
    myEsp.println();
  }
  return true;
}
