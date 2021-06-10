#include <LiquidCrystal.h>
LiquidCrystal lcd(8,9,5,4,3,2);
int numRows = 2;
int numCols = 16;

void setup()
{
  Serial.begin(9600);
  lcd.begin(numRows,numCols);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Arduinooooo");
  lcd.setCursor(0,1);
  lcd.print("ES"); 
 // lcd.cursor();
 //lcd.blink();
}

void loop() {}

//wyswietlanie zawartosci portu szeregowego


//tylko dlaczego tu  się pokazują 3 kreski po wyrazie???


// void loop()
//{
//  static char ch[] = {0,1,2};
//  if(Serial.available()>0)
//  {
//   ch[0] = Serial.read();
//    
//    if(ch[0] == '#')
//    {
//      lcd.clear();
//    }
//    
//    else if(ch[0] == '/')
//    {
//      lcd.setCursor(0,1);
//    }
//    
//    else if(ch[0] == '.')
//    {
//      lcd.setCursor(1,0);
//    }
//    
//    else
//    {
//      lcd.print(ch[0]);
//    }
//  }
//}
