#define SENS_PIN 8

void setup() {
	// pinMode(SENS_PIN, INPUT);
	Serial.begin(115200);
}
void loop() {
	Serial.print("value   ");
	Serial.println(digitalRead(SENS_PIN));
	delay(10);
}