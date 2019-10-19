#define LEFT_SENSOR_PIN  2
#define RIGHT_SENSOR_PIN 3

#define LEFT_MOTOR_A_PIN 4 
#define LEFT_MOTOR_B_PIN 5
#define LEFT_MOTOR_PWM_PIN 6

#define RIGHT_MOTOR_A_PIN 8
#define RIGHT_MOTOR_B_PIN 9
#define RIGHT_MOTOR_PWM_PIN 10 

#define MAX_SPEED 90
#define MIN_SPEED 20

bool left_sensor_state = 0; 
bool right_sensor_state = 0; 

void setup(){
    pinMode(LEFT_SENSOR_PIN, INPUT);
    pinMode(RIGHT_SENSOR_PIN, INPUT);

    pinMode(LEFT_MOTOR_A_PIN, OUTPUT);
    pinMode(LEFT_MOTOR_B_PIN, OUTPUT);
    pinMode(LEFT_MOTOR_PWM_PIN, OUTPUT);

    pinMode(RIGHT_MOTOR_A_PIN, OUTPUT);
    pinMode(RIGHT_MOTOR_B_PIN, OUTPUT);
    pinMode(RIGHT_MOTOR_PWM_PIN, OUTPUT);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////ПЕРЕДВИЖЕНИЕ МАШИНЫ////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
void runStop(){				//СТОП
    digitalWrite(LEFT_MOTOR_A_PIN, HIGH);
    digitalWrite(LEFT_MOTOR_B_PIN, LOW);
    digitalWrite(LEFT_MOTOR_PWM_PIN, LOW);

    digitalWrite(RIGHT_MOTOR_A_PIN, HIGH);
    digitalWrite(RIGHT_MOTOR_B_PIN, LOW);
    digitalWrite(RIGHT_MOTOR_PWM_PIN, LOW);
    delay(1000); 
}
void runForward(){				//ВПЕРЕД
	digitalWrite(LEFT_MOTOR_A_PIN, LOW);
    digitalWrite(LEFT_MOTOR_B_PIN, HIGH);
    analogWrite(LEFT_MOTOR_PWM_PIN, MAX_SPEED);

    digitalWrite(RIGHT_MOTOR_A_PIN, LOW);
    digitalWrite(RIGHT_MOTOR_B_PIN, HIGH);
    analogWrite(RIGHT_MOTOR_PWM_PIN, MAX_SPEED);    
}
void runLeft(){				//ЛЕВО
	digitalWrite(LEFT_MOTOR_A_PIN, HIGH);
    digitalWrite(LEFT_MOTOR_B_PIN, LOW);
    analogWrite(LEFT_MOTOR_PWM_PIN, MIN_SPEED);

    digitalWrite(RIGHT_MOTOR_A_PIN, HIGH);
    digitalWrite(RIGHT_MOTOR_B_PIN, LOW);
    analogWrite(RIGHT_MOTOR_PWM_PIN, MAX_SPEED);    
    delay(800);    	
}
void runRight(){				//ПРАВО
    digitalWrite(LEFT_MOTOR_A_PIN, HIGH);
    digitalWrite(LEFT_MOTOR_B_PIN, LOW);
    analogWrite(LEFT_MOTOR_PWM_PIN, MAX_SPEED);

    digitalWrite(RIGHT_MOTOR_A_PIN, HIGH);
    digitalWrite(RIGHT_MOTOR_B_PIN, LOW);
    analogWrite(RIGHT_MOTOR_PWM_PIN, MIN_SPEED);
    delay(800);    	
}
void runBack(){				//НАЗАД
    digitalWrite(LEFT_MOTOR_A_PIN, HIGH);
    digitalWrite(LEFT_MOTOR_B_PIN, LOW);
    analogWrite(LEFT_MOTOR_PWM_PIN, MAX_SPEED);

    digitalWrite(RIGHT_MOTOR_A_PIN, HIGH);
    digitalWrite(RIGHT_MOTOR_B_PIN, LOW);
    analogWrite(RIGHT_MOTOR_PWM_PIN, MAX_SPEED);
    delay(500); 
}
void traffic(){
	left_sensor_state = digitalRead(LEFT_SENSOR_PIN);
    right_sensor_state = digitalRead(RIGHT_SENSOR_PIN);
    if((left_sensor_state == 0) && (right_sensor_state == 0)){  // forward
    	runForward();
    }
    if((left_sensor_state == 0) && (right_sensor_state == 1)){
    	runBack();
    	runRight();
    	// return;
    }
    if((left_sensor_state == 1) && (right_sensor_state == 0)){
    	runBack();
    	runLeft();
    }
    if((left_sensor_state == 1) && (right_sensor_state == 1)){
    	runBack();
    	runRight();
    }    	

}
void loop(){
	traffic();
}
