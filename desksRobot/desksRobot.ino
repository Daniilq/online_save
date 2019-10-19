#define LEFT_SENSOR_PIN  2
#define RIGHT_SENSOR_PIN 3

#define LEFT_MOTOR_A_PIN 4 
#define LEFT_MOTOR_B_PIN 5
#define LEFT_MOTOR_PWM_PIN 6

#define RIGHT_MOTOR_A_PIN 8
#define RIGHT_MOTOR_B_PIN 9
#define RIGHT_MOTOR_PWM_PIN 10 

#define MAX_SPEED 180
#define MIN_SPEED 100

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

void carTransmision(int8_t _direction){
    if(_direction == 0){  // stop
        digitalWrite(LEFT_MOTOR_A_PIN, HIGH);
        digitalWrite(LEFT_MOTOR_B_PIN, LOW);
        digitalWrite(LEFT_MOTOR_PWM_PIN, LOW);

        digitalWrite(RIGHT_MOTOR_A_PIN, HIGH);
        digitalWrite(RIGHT_MOTOR_B_PIN, LOW);
        digitalWrite(RIGHT_MOTOR_PWM_PIN, LOW);    
    } 
    else if(_direction == 1){  // forward
        digitalWrite(LEFT_MOTOR_A_PIN, HIGH);
        digitalWrite(LEFT_MOTOR_B_PIN, LOW);
        analogWrite(LEFT_MOTOR_PWM_PIN, MAX_SPEED);

        digitalWrite(RIGHT_MOTOR_A_PIN, HIGH);
        digitalWrite(RIGHT_MOTOR_B_PIN, LOW);
        analogWrite(RIGHT_MOTOR_PWM_PIN, MAX_SPEED);    
    } 
    else if(_direction == 2){  // left
        digitalWrite(LEFT_MOTOR_A_PIN, HIGH);
        digitalWrite(LEFT_MOTOR_B_PIN, LOW);
        analogWrite(LEFT_MOTOR_PWM_PIN, MIN_SPEED);

        digitalWrite(RIGHT_MOTOR_A_PIN, HIGH);
        digitalWrite(RIGHT_MOTOR_B_PIN, LOW);
        analogWrite(RIGHT_MOTOR_PWM_PIN, MAX_SPEED);    
    } 
    else if(_direction == 3){  // right
        digitalWrite(LEFT_MOTOR_A_PIN, HIGH);
        digitalWrite(LEFT_MOTOR_B_PIN, LOW);
        analogWrite(LEFT_MOTOR_PWM_PIN, MAX_SPEED);

        digitalWrite(RIGHT_MOTOR_A_PIN, HIGH);
        digitalWrite(RIGHT_MOTOR_B_PIN, LOW);
        analogWrite(RIGHT_MOTOR_PWM_PIN, MIN_SPEED);    
    } 
    else if(_direction == 4){  // back
        digitalWrite(LEFT_MOTOR_A_PIN, LOW);
        digitalWrite(LEFT_MOTOR_B_PIN, HIGH);
        analogWrite(LEFT_MOTOR_PWM_PIN, MAX_SPEED);

        digitalWrite(RIGHT_MOTOR_A_PIN, LOW);
        digitalWrite(RIGHT_MOTOR_B_PIN, HIGH);
        analogWrite(RIGHT_MOTOR_PWM_PIN, MAX_SPEED);    
    } 
}

void voditelMashine(){
    left_sensor_state = digitalRead(LEFT_SENSOR_PIN);
    right_sensor_state = digitalRead(RIGHT_SENSOR_PIN);
    if(left_sensor_state == 1 && right_sensor_state == 1){  // forward
    
    }
} 

void loop(){
    voditelMashine();    
}