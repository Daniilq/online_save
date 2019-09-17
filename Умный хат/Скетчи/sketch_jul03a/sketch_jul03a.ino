#define pirPin 7
int in1 = 11;
int in2 = 10;
int in3 = 9;
int in4 = 8;

void setup() {
    pinMode(in1, OUTPUT);
    pinMode(in2, OUTPUT);
    pinMode(in3, OUTPUT);
    pinMode(in4, OUTPUT);
    Serial.begin(9600); // Объявляем работу com порта со скоростью 9600
  pinMode(pirPin, INPUT); //Объявляем пин, к которому подключен датчик движения, входом
}

void loop() {
  int pirVal = digitalRead(pirPin); //Считываем значения с датчика движения. Если обнаружили движение, 
                                    //то транслируем сигнал тревоги в монитор порта и включаем светодиод
  if(pirVal == HIGH)
  {
     digitalWrite( in1, HIGH ); 
    digitalWrite( in2, HIGH ); 
    digitalWrite( in3, LOW ); 
    digitalWrite( in4, LOW );
    delay(500);
    Serial.print("Тревога ");
    delay(2000);
  }
else
{
  Serial.print("Сканирую ");
     digitalWrite( in1, LOW ); 
    digitalWrite( in2, LOW ); 
    digitalWrite( in3, LOW ); 
    digitalWrite( in4, LOW );
  delay(1000);
}
}
