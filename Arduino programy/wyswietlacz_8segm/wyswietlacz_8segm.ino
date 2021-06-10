#define F_CPU 16000000UL // Ustawienie czestotliwosci zegara uC

#include <avr/io.h> //Dolaczenie biblioteki wejscia wyjscia 
#include <util/delay.h> //Dolaczenie biblioteki opoznien 
#define TIME 4  //Zmienna okreslajaca czas pa, ktorym ma nastapic przelaczenie wyswietlacza 
#define TIME_DISP 50 // razy 25ms
void PortInitialization(void)
{
 DDRD |=0xFF; //Ustawienie calego portu D jako wyjscia
 PORTD |=0xFF; //Ustawienie calego portu D na stan wysoki 
 DDRB |=0xFF; //Ustawienie portu B0, B1, B2, B3 jako wyjscia 
 PORTB |=0xFF; //Ustawienie calego portu B na stan wysoki  


}

void Print(unsigned char f,unsigned char i,unsigned char v,unsigned char e,unsigned char r)
{
 while(1) {  

  
    //Wystwieltenie cyfry na 5 wyswietlaczu liczab od lewej 
    PORTB = 0xEF;  
    PORTD = r; //number[4]; 
    _delay_ms(TIME);
    
    //Wystwieltenie cyfry na 4 wyswietlaczu liczab od prawej 
    PORTB = 0xFE;
    PORTD =e; //number[4]; 
    _delay_ms(TIME); 
    
    //Wystwieltenie cyfry na 3 wyswietlaczu liczab od prawej
    PORTB = 0xFD; 
    PORTD = v;//number[3]; 
    _delay_ms(TIME);
    
    //Wystwieltenie cyfry na 2 wyswietlaczu liczab od prawej
    PORTB = 0xFB; 
    PORTD = i;//number[2]; 
    _delay_ms(TIME);
    
    //Wystwieltenie cyfry na 1 wyswietlaczu liczab od prawej
    PORTB = 0xF7;
    PORTD = f;//number[1]; 
    _delay_ms(TIME);
  }  
}


int main() { 
  PortInitialization(); //Wywolanie funkcji odpowiedzialnej za inicjalizacje portow 
unsigned char number[10] = {0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90};
unsigned char d = ~0x5E, u = ~0x3E, p = ~0x73, a = ~0x77, c = ~0x39, h = ~0x76, j = ~0x1F;
unsigned char e = ~0x79, n = ~0x37, i = ~0x06, s = ~0x6D, z = ~0x5B, t = ~0x78, r = ~0x50, y = ~0x6E;
unsigned char dash = ~0x40, nul = 0xFF;


 // while(1){    //zakomenyuj while w Print
    //for(int i = 0;i<TIME_DISP;i++)
      //Print(number[2],number[1],dash,number[3],number[7]);
    //for(int i = 0;i<TIME_DISP;i++)
      //Print(p,a,p,a,j);
    //for(int i = 0;i<TIME_DISP;i++)
      //Print(z,d,e,h,nul);
  //}
//Print(p,u,t,i,n);
Print(number[1],number[2],number[3],number[4],number[5]);

}
