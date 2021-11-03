void setup() {
  //diody
  pinMode(0, OUTPUT); //Dioda czerwona jako wyjście
  pinMode(1, OUTPUT); //Dioda zielona jako wyjście
  pinMode(2, OUTPUT); //Dioda pomaranczowa jako wyjście
  //przyciski
  pinMode(3, INPUT_PULLUP); //Przycisk czerwony jako wejście
  pinMode(4, INPUT_PULLUP); //Przycisk zielony jako wejście
  pinMode(5, INPUT_PULLUP); //Przycisk pomaranczowy_1 jako wejście
  pinMode(6, INPUT_PULLUP); //Przycisk pomaranczowy_2 jako wejście
  //ustawienie wyjsc diod na niskie
  digitalWrite(0, LOW); //Wyłączenie diody
  digitalWrite(1, LOW); //Wyłączenie diody
  digitalWrite(2, LOW); //Wyłączenie diody
}
 
void loop()
{
  //dioda czerwona
  if (digitalRead(3) == LOW) { //Jeśli przycisk wciśnięty
      digitalWrite(0, HIGH); //Włącz diodę
  }
  else { //Jeśli warunek nie został spełniony (przycisk nie jest wciśnięty)
    digitalWrite(0, LOW); //Wyłącz diodę
  }
  //dioda zielona
   while (digitalRead(4) == LOW) { //Jeśli przycisk jest wciśnięty 
     digitalWrite(1, HIGH); //Czerwona włącz
      delay(500);
      digitalWrite(1, LOW); //Czerwona wyłącz
      delay(500);
   }
   //dioda pomaranczowa
  if (digitalRead(5) == LOW) { //Jeśli przycisk wciśnięty
      digitalWrite(2, HIGH); //Włącz diodę
  }
  if(digitalRead(6)==LOW && digitalRead(2)==HIGH){ //po co wysyłać sygnał, jeśli dioda 
  digitalWrite(2, LOW); //Wyłącz diodę              //jest już wyłączona
  }
   
}
