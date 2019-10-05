#include <Servo.h>
Servo servo;

#define SERVO_PIN 12
#define MAX_SERVO_ANGLE 40
#define ZERO_POS 95

int16_t servo_pos = ZERO_POS; 


void setup(){

	Serial.begin(9600);

	servo.attach(SERVO_PIN);
	delay(50);
	servo.write(ZERO_POS);
}

void loop(){
	if (Serial.available() > 0) {
	    servo_pos = Serial.parseInt();
	    
	    if(servo_pos > ZERO_POS + MAX_SERVO_ANGLE){servo_pos = ZERO_POS + MAX_SERVO_ANGLE;}
	    else if(servo_pos < ZERO_POS - MAX_SERVO_ANGLE){servo_pos = ZERO_POS - MAX_SERVO_ANGLE;}

	    servo.write(servo_pos);
	    Serial.print("  Angle = ");
	    Serial.println(servo_pos);
	}
}