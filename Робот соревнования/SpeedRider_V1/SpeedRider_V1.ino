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
#define MAX_MOTOR_SPEED 200
#define MIN_MOTOR_SPEED 100
#define TOTAL_SENSORS 11        // всего сенсоров

#define SER_DEBUG_ENABLE 1 

static int16_t sensor[11]={0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
static int16_t line_vector_val = 0;

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
int16_t light_correction = 0;   // поправка на освещенность

int16_t left_sens_val = 0;      // переменная для накопления значения левой ошибки
int16_t center_sens_val = 0;    // переменная для накопления значения ширины линии
int16_t right_sens_val = 0;     // переменная для накопления значения правой ошибки
int8_t convers_oper_flag = 0;   // флаг операции преобразования

static inline int32_t lineCheck(int _sens_type = 0){
	left_sens_val = 0;
	center_sens_val = 0;
	right_sens_val = 0;
	convers_oper_flag = 0;
	white_color_val = 1023;  // значение черного цвета
	black_color_val = 0;  // значение белого цвета
	if(_sens_type == 0){            // analog
		for(int i=0; i<TOTAL_SENSORS; i++){
	        // sensor_a[i] = analogRead(ANALOG_SENS_PIN + i);
	        sensor_a[i] = analogRead(ANALOG_SENS_PIN + i) + sensor_correction[i];
	        if(sensor_a[i] < white_color_val){white_color_val = sensor_a[i];}  // определяем белый
	        if(sensor_a[i] > black_color_val){black_color_val = sensor_a[i];} // определяем черный
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

	        if(sensor_a[i] >= (white_color_val + 7)){
	        	sensor[i] = 1;
	        }
	        else{
	        	sensor[i] = 0;
	        }
	        Serial.print(String(sensor[i]));
	    }
	}
	// else if(_sens_type == 1){  // digital
	//     for(int i=0; i<TOTAL_SENSORS; i++){
	//         sensor[i] = digitalRead(STRT_SENS_PIN+i);
	//         Serial.print(String(sensor[i]) + ",");
	//     }
	//     Serial.print("   ");
	// }
	// line_vector_val = left_sens_val - right_sens_val;
	line_vector_val = lineCheckAnalizerSS();
	Serial.print("  ");
	Serial.print(line_vector_val);
	Serial.println(" >");
	    // delay(1000);
	return line_vector_val;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



static int32_t lineCheckAnalizerSS(){
 	int16_t _left = 0;
 	int16_t _right = 0;
 	int32_t _line_vector_val_SS = 0;
 	for(int i=0; i<11; i++){
 		if(sensor[i] == 0 ){_left ++;}
 		else {break;}
 	}
 	for(int i=10; i>=0; i--){
 		if(sensor[i] == 0 ){_right ++;}
 		else {break;}	
 	}

	_line_vector_val_SS = _left - _right;
	// Serial.print("   ");
	// Serial.print(_line_vector_val_SS);
	// Serial.print("   ");
	return _line_vector_val_SS;
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

	int16_t _line_veexp = line_vector_val * 6;
	int16_t _required_servo_pos = map(_line_veexp, -60, 60, ZERO_POS + MAX_SERVO_ANGLE, ZERO_POS - MAX_SERVO_ANGLE);
	int16_t _required_motor_speed;
	if(line_vector_val >= 0){
		_required_motor_speed = map(_line_veexp, 0, 60, MAX_MOTOR_SPEED, MIN_MOTOR_SPEED);
	}else{
		_required_motor_speed = map(_line_veexp, 0, -60, MAX_MOTOR_SPEED, MIN_MOTOR_SPEED);
	}

	servo.write(_required_servo_pos);

	digitalWrite(MOTORIN1_PIN, HIGH);
	digitalWrite(MOTORIN2_PIN, LOW);
	analogWrite(PWM_PIN, _required_motor_speed);

	Serial.print("   ");
	Serial.print(_required_servo_pos);
	Serial.print("   ");
	Serial.println(_required_motor_speed);
}

static inline void generalDriver(){
	lineCheck();
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

	generalDriver();

}