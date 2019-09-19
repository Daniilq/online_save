// #include <Arduino.h>
#include <Servo.h>

Servo servo;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// PINOUT:
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define DEBUG_RIDER 0

#define PWM_PIN 8
#define MOTORIN1_PIN 7
#define MOTORIN2_PIN 6
#define DIGITAL_SENS_PIN 40
#define ANALOG_SENS_PIN 54
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#define SERVO_PIN 12
#define ZERO_POS 85
#define MAX_SERVO_ANGLE 30
#define MAX_MOTOR_SPEED 150

#define SER_DEBUG_ENABLE 1 

static int16_t _line_check_analizer;

static int16_t sensor[11]={0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
static int16_t lineVectorVal = 0;

static inline void lineCheck(int _sens_type = 1){
	if(_sens_type == 1){  // digital
	    for(int i=0; i<11; i++){
	        sensor[i] = digitalRead(DIGITAL_SENS_PIN+i);
	        Serial.print(String(sensor[i]) + ",");
	    }
	    // sensor[0] = digitalRead(43);
	    // sensor[2] = digitalRead(45);
	    // sensor[4] = digitalRead(47);
	    Serial.print("   ");
	}
	else{            // analog

	}
}
static int32_t lineCheckAnalizer1(){ 
	if(sensor[3] == 0 && sensor[5] > 0 && sensor[7] == 0){lineVectorVal = 0;}  // центр
	else if(sensor[3] > 0 && sensor[5] > 0 && sensor[7] > 0){lineVectorVal = 0;}  // центр центр

	else if(sensor[3] > 0 && sensor[5] > 0 && sensor[7] == 0){lineVectorVal = -1;}  // лево центр
	else if(sensor[3] > 0 && sensor[5] == 0 && sensor[7] == 0){lineVectorVal = -2;}  // лево

	else if(sensor[3] == 0 && sensor[5] > 0 && sensor[7] > 0){lineVectorVal = 1;}  // право центр
	else if(sensor[3] == 0 && sensor[5] == 0 && sensor[7] > 0){lineVectorVal = 2;}  // право

	// else if(sensor[1] == 0 && sensor[3] == 0 && sensor[5] == 0){lineVectorVal = 99;}  // потеря трассы
	// else {lineVectorVal = 100;}
	// else if(sensor[1] > 0 && sensor[3] > 0 && sensor[5] > 0){lineVectorVal = 98;}  // потеря трассы
	Serial.print(String(sensor[3]) + String(sensor[5]) + String(sensor[7]));
	Serial.print("   ");
	Serial.print(lineVectorVal);

	return lineVectorVal;
}

static int32_t lineCheckAnalizerMaxim(){
 	int16_t _left = 0;
 	int16_t _right = 0;
 	int32_t _lineVectorValMaxim = 0;
 	for(int i=0; i<11; i++){
 	    if(sensor[i] == 1 && i <= 5 ){ _left ++; }
		if(sensor[i] == 1 && i >= 5 && i <=11 ){  _right ++; }
 	}
	_lineVectorValMaxim = _right -  _left ;
	Serial.print("   ");
	Serial.print(_lineVectorValMaxim);
	Serial.print("   ");
	return _lineVectorValMaxim;
}
static int32_t lineCheckAnalizerSS(){
 	int16_t _left = 0;
 	int16_t _right = 0;
 	int32_t _lineVectorValSS = 0;
 	for(int i=0; i<11; i++){
 		if(sensor[i] == 0 ){_left ++;}
 		else {break;}
 	}
 	for(int i=10; i>=0; i--){
 		if(sensor[i] == 0 ){_right ++;}
 		else {break;}	
 	}

	_lineVectorValSS = _left - _right;
	Serial.print("   ");
	Serial.print(_lineVectorValSS);
	Serial.print("   ");
	return _lineVectorValSS;
}


/*//////////////////////////////////////////////////////////////////////////////////////////////////

int32_t avgSpeed = 150; // средняя скорость моторов
int32_t kP = 10; // коэффициент пропорциональной обратной связи
int32_t kD = 5;  // коэффициент дифференциальной обратной связи
int32_t kI = 5;  // коэффициент интегральной обратной связи

int32_t correction;
int32_t err;

int32_t err_arr[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int32_t err_p = -1;

prevErr = bot_position();

int32_t pidRegulator()
{
err = bot_position();
err_p = (err_p + 1) % 10;
err_arr[err_p] = err;

P = err * KP;
D = (err_arr[err_p] - err_arr[(err_p+11) % 10])*KD;
int err_sum = 0;
for (int i = 0; i < 10; i++) err_sum += err_arr[i];
I = err_sum/10*KI;

correction = P + I + D;
return correction;

// motor1.move(avgSpeed*(1+correction));
// motor2.move(avgSpeed*(1-correction));

delay(2);
}

//////////////////////////////////////////////////////////////////////////////////////////////////*/

static inline void voditelServ(){

	int16_t required_servo_pos = map(_line_check_analizer, -2, 2, ZERO_POS + MAX_SERVO_ANGLE, ZERO_POS - MAX_SERVO_ANGLE);
	servo.write(required_servo_pos);

	digitalWrite(MOTORIN1_PIN, HIGH);
	digitalWrite(MOTORIN2_PIN, LOW);
	analogWrite(PWM_PIN, MAX_MOTOR_SPEED);
	Serial.print("   ");
	Serial.println(required_servo_pos);
}

static inline void generalDriver(){
	lineCheck();
	_line_check_analizer = lineCheckAnalizer1();
	voditelServ();
}
void setup(){
	pinMode(PWM_PIN, OUTPUT);
	pinMode(MOTORIN1_PIN, OUTPUT);
	pinMode(MOTORIN2_PIN, OUTPUT);

	Serial.begin(250000);

	servo.attach(SERVO_PIN);
	delay(50);
	servo.write(ZERO_POS);
}

void loop(){

	generalDriver();
	lineCheckAnalizerMaxim();
	lineCheckAnalizerSS();
}