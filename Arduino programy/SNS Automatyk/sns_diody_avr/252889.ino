#define F_CPU 16000000UL  // 16 MHz
//#define F_CPU 14.7456E6
#include <util/delay.h>
#include <avr/io.h>
/*Dodatkowo skorzystalem z linku ponizej, zeby wykonac zadanie z biblioteką AVR a nie arduino*/
/*http://mirekk36.blogspot.com/2012/01/avr-porty-wewy-dir-podstawy.html */
void delay_ms( int ms)
  {
  volatile long unsigned int i;
  for(i=0;i<ms;i++)
    _delay_ms(1);
  }
void setup()
{
  DDRD=0b00000111;  //ustalenie kierunku pinow
  PORTD = 0b11111000; //ustalenie stanu początkowego portu
}
int main(void)
{
setup();
//zdefiniowanie zmiennej odpowiadajacej za opoznienia
int ms=1000;

while(1) //nieskończona pętla
  {
  //dioda czerwona
  if(!(PIND & (1<<PD3))){   //Jeśli przycisk wciśnięty
      PORTD |=(1<<PD0); //Włącz diodę
  }
  else { //Jeśli warunek nie został spełniony (przycisk nie jest wciśnięty)
    PORTD &=~(1<<PD0); //Wyłącz diodę
  }
  //dioda zielona
   while (!(PIND & (1<<PD4))) { //Jeśli przycisk jest wciśnięty 
     PORTD |=(1<<PD1); //Czerwona włącz
      delay_ms(500);
      PORTD &=~(1<<PD1); //Czerwona wyłącz
      delay_ms(500);
   }
   //dioda pomaranczowa
  if (!(PIND & (1<<PD5))) { //Jeśli przycisk wciśnięty
     PORTD |= (1<<PD2); //Włącz diodę
  }
  if(!(PIND & (1<<PD6)) && (PIND & (1<<PD3))){ //po co wysyłać sygnał, jeśli dioda 
     PORTD &= ~(1<<PD2); //Wyłącz diodę              //jest już wyłączona
  }
  
  };

return(0);
}

//kod arduino poniżej, żeby nie było że nie mam
//void setup() {
//  //diody
//  pinMode(0, OUTPUT); //Dioda czerwona jako wyjście
//  pinMode(1, OUTPUT); //Dioda zielona jako wyjście
//  pinMode(2, OUTPUT); //Dioda pomaranczowa jako wyjście
//  //przyciski
//  pinMode(3, INPUT_PULLUP); //Przycisk czerwony jako wejście
//  pinMode(4, INPUT_PULLUP); //Przycisk zielony jako wejście
//  pinMode(5, INPUT_PULLUP); //Przycisk pomaranczowy_1 jako wejście
//  pinMode(6, INPUT_PULLUP); //Przycisk pomaranczowy_2 jako wejście
//  //ustawienie wyjsc diod na niskie
//  digitalWrite(0, LOW); //Wyłączenie diody
//  digitalWrite(1, LOW); //Wyłączenie diody
//  digitalWrite(2, LOW); //Wyłączenie diody
//}
// 
//void loop()
//{
//  //dioda czerwona
//  if (digitalRead(3) == LOW) { //Jeśli przycisk wciśnięty
//      digitalWrite(0, HIGH); //Włącz diodę
//  }
//  else { //Jeśli warunek nie został spełniony (przycisk nie jest wciśnięty)
//    digitalWrite(0, LOW); //Wyłącz diodę
//  }
//  //dioda zielona
//   while (digitalRead(4) == LOW) { //Jeśli przycisk jest wciśnięty 
//     digitalWrite(1, HIGH); //Czerwona włącz
//      delay(500);
//      digitalWrite(1, LOW); //Czerwona wyłącz
//      delay(500);
//   }
//   //dioda pomaranczowa
//  if (digitalRead(5) == LOW) { //Jeśli przycisk wciśnięty
//      digitalWrite(2, HIGH); //Włącz diodę
//  }
//  if(digitalRead(6)==LOW && digitalRead(2)==HIGH){ //po co wysyłać sygnał, jeśli dioda 
//  digitalWrite(2, LOW); //Wyłącz diodę              //jest już wyłączona
//  }
//   
//}
