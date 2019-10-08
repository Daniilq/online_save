#include "Stepper.h"
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

#define STEPS  32 
int32_t  Steps2Take;
Stepper small_stepper(STEPS, 5, 7, 6, 8);	// In1, In2, In3, In4 в последовательности 1-3-2-4


void setup()
{ 
	pinMode(RELE_PIN, OUTPUT);
  	digitalWrite(13, LOW);
  	Serial.begin(9600); 
  	irrecv.enableIRIn();
}
void loop()
{
if (irrecv.decode(&results)) 
 
  {
    switch(results.value)
 
    {
case (K_UP):
small_stepper.setSpeed(600); 
Steps2Take  =  -18480; 
small_stepper.step(Steps2Take);
delay(1500); 
digitalWrite(5,LOW);
digitalWrite(6,LOW);
digitalWrite(7,LOW);
digitalWrite(8,LOW);
// Serial.println("down");
break;
case (K_DOWN): 
small_stepper.setSpeed(600);
Steps2Take  =  18480;
small_stepper.step(Steps2Take);
delay(1500); 
digitalWrite(5,LOW);
digitalWrite(6,LOW);
digitalWrite(7,LOW);
digitalWrite(8,LOW);
// Serial.println("up");
break;  
case(K_OK) :
digitalWrite(RELE_PIN, !digitalRead(RELE_PIN));
Serial.print("light");
Serial.print("   ");
Serial.println(digitalRead(RELE_PIN));
break;
	} 
irrecv.resume(); // принимаем следующую команду
}  
}
