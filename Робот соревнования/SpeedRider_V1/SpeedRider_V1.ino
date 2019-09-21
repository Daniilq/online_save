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
#define ANALOG_SENS_PIN 54      // пин первого сенсора
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#define SERVO_PIN 12
#define ZERO_POS 85
#define MAX_SERVO_ANGLE 30
#define MAX_MOTOR_SPEED 150
#define TOTAL_SENSORS 11        // всего сенсоров

#define SER_DEBUG_ENABLE 1 

static int16_t _line_check_analizer;

static int16_t sensor[11]={0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
static int16_t lineVectorVal = 0;

// static inline void lineCheck(int _sens_type = 1){
// 	if(_sens_type == 1){  // digital
// 	    for(int i=0; i<11; i++){
// 	        sensor[i] = digitalRead(DIGITAL_SENS_PIN+i);
// 	        Serial.print(String(sensor[i]) + ",");
// 	    }
// 	    // sensor[0] = digitalRead(43);
// 	    // sensor[2] = digitalRead(45);
// 	    // sensor[4] = digitalRead(47);
// 	    Serial.print("   ");
// 	}
// 	else{            // analog

// 	}
// }





////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int16_t white_color_val = 70;  // значение черного цвета
int16_t black_color_val = 1000;  // значение белого цвета
int16_t sensor_a[TOTAL_SENSORS]={0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};  // массив с аналоговыми значениями
int16_t sensor_correction[TOTAL_SENSORS]={1, 1, 3, 2, 2, 3, -3, 1, 0, -8, -2};  // массив со значениями коррекции датчиков, для выравнивания их значений между собой

// 25,25,23,24,24,23,29,24,25,34,28,

int16_t light_correction = 0;   // поправка на освещенность
int16_t left_sens_val = 0;      // переменная для накопления значения левой ошибки
int16_t right_sens_val = 0;     // переменная для накопления значения правой ошибки
int8_t convers_oper_flag = 0;   // флаг операции преобразования
static inline int32_t lineCheck(int _sens_type = 0){
	left_sens_val = 0;
	right_sens_val = 0;
	convers_oper_flag = 0;
	white_color_val = 1023;  // значение черного цвета
	black_color_val = 0;  // значение белого цвета
	if(_sens_type == 0){            // analog
		for(int i=0; i<TOTAL_SENSORS; i++){
	        // sensor_a[i] = analogRead(ANALOG_SENS_PIN + i);
	        sensor_a[i] = analogRead(ANALOG_SENS_PIN + i) + sensor_correction[i];
	        if(sensor_a[i] < white_color_val){white_color_val = sensor_a[i];}
	        if(sensor_a[i] > black_color_val){black_color_val = sensor_a[i];}
	        Serial.print(String(sensor_a[i]) + ",");
	    }
	    Serial.print("   ");
	    Serial.print("b ");
	    Serial.print(black_color_val);
	    Serial.print("  ");
	    Serial.print("w ");
	    Serial.print(white_color_val);
	    Serial.print("  ");


	    for(int i=0; i<TOTAL_SENSORS; i++){
	        // if((sensor_a[i] >= (black_color_val - (black_color_val - white_color_val) / 4)) ){
	        // 	sensor[i] = 1;
	        // }
	        // else{
	        // 	sensor[i] = 0;
	        // }

	        if(sensor_a[i] >= (white_color_val * 5)){
	        	sensor[i] = 1;
	        }
	        else{
	        	sensor[i] = 0;
	        }
	        Serial.print(String(sensor[i]));
	    }
	    Serial.println("!");
	}
	// else if(_sens_type == 1){  // digital
	//     for(int i=0; i<TOTAL_SENSORS; i++){
	//         sensor[i] = digitalRead(STRT_SENS_PIN+i);
	//         Serial.print(String(sensor[i]) + ",");
	//     }
	//     Serial.print("   ");
	// }
	lineVectorVal = left_sens_val - right_sens_val;
	    // delay(1000);
	return lineVectorVal;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////





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

	Serial.begin(115200);

	servo.attach(SERVO_PIN);
	delay(50);
	servo.write(ZERO_POS);
}

void loop(){

	// generalDriver();
	// lineCheckAnalizerMaxim();
	// lineCheckAnalizerSS();
	lineCheck();
}