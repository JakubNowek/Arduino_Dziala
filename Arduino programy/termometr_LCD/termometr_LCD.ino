#include "DHT.h"
#include <LiquidCrystal.h>
#define DHT11_PIN 13 
#define LED 12
DHT dht;
LiquidCrystal lcd(8,9,2,3,4,5);

int numRows = 2;
int numCols = 16;

byte celsDeg[8]={ //tworzenie nowego znaku
  B00111,
  B00101,
  B00111,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};

void setup()
{
  Serial.begin(9600);
  lcd.begin(numRows,numCols);
  lcd.createChar(0,celsDeg);
  lcd.home();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("STACJA POGODOWA");
  lcd.setCursor(0,1);
  lcd.print("Uruchamianie..."); 
  dht.setup(DHT11_PIN);
  pinMode(LED,OUTPUT); // normalnie bym robił DDRD = 0xFF , żeby ustawić cały port jako wyjścia
                     // ale tu trzeba użyć metody arduino, żeby nie zepsuć odczytu
}

void loop()
{
  static int tempW;
  static int tempT;
    //Pobranie informacji o wilgotnosci
  int wilgotnosc = dht.getHumidity();
  //Pobranie informacji o temperaturze
  int temperatura = dht.getTemperature();
  if (dht.getStatusString() == "OK") {
    Serial.print("Wilgotnosc: ");
    Serial.print(wilgotnosc);
    Serial.print("%RH [+-5 % ] | ");
    Serial.print("Temperatura: ");
    Serial.print(temperatura);
    Serial.println("*C [+-2 *C ] ");
      if(tempW != wilgotnosc || tempT!=temperatura ) //jeśli zmiła się wilgotność, to wyświetlam wartość
      {
        lcd.clear();
        lcd.print("Wilgotnosc:");
        lcd.print(wilgotnosc);
        lcd.print(" %");
        lcd.setCursor(0,1);
        lcd.print("Temperatura:");
        lcd.print(temperatura);
        lcd.write(byte(0));
        lcd.print("C");
        tempW = wilgotnosc;
        tempT = temperatura;
      }
      
      if (wilgotnosc>=55)
      {
        digitalWrite(LED,HIGH);
      }
      else {digitalWrite(LED,LOW);}
    }

  //Odczekanie wymaganego czasugo
  delay(dht.getMinimumSamplingPeriod());
}
