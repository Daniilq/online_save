
#include "IRremote.h"

#define K1 0xFFA25D
#define K2 0xFF629D
#define K3 0xFFE21D
#define K4 0xFF22DD
#define K5 0xFF02FD
#define K6 0xFFC23D
#define K7 0xFFE01F
#define K8 0xFFA857
#define K9 0xFF906F
#define K0 0xFF9867
#define kZ 0xF6897
#define kR 0xFFB04F
#define K_UP 0xFF18E7
#define K_DOWN 0xFF4AB5
#define K_LEFT 0xFF10EF
#define K_RIGHT 0xFF5AA5
#define K_OK 0xFF38C7


#define RELE_PIN 4

IRrecv irrecv(3);
decode_results results;

void setup() {
	pinMode(RELE_PIN, OUTPUT);
  digitalWrite(13, LOW);
  Serial.begin(9600); // выставляем скорость COM порта
  irrecv.enableIRIn(); // запускаем прием
}

void loop() {
  if ( irrecv.decode( &results )) { // если данные пришли
switch (results.value) {
    case(K0) :
    Serial.println(0);
      break;
    case(K1) :
    Serial.println(1);
    digitalWrite(RELE_PIN, !digitalRead(RELE_PIN));
      break;
    case(K2) :
    Serial.println(2);
      break;
    case(K3) :
    Serial.println(3);
      break;
    case(K4) :
    Serial.println(4);
      break;
    case(K5) :
    Serial.println(5);
      break;
    case(K6) :
    Serial.println(6);
      break;
    case(K7) :
    Serial.println(7);
      break;
    case(K8) :
    Serial.println(8);
      break;
    case(K9) :
    Serial.println(9);
      break;      
}
    irrecv.resume(); // принимаем следующую команду
  }
}