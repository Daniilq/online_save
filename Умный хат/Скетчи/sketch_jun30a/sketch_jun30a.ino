#include "ESP8266WiFi.h"
IPAddress apIP(192, 168, 4, 1);

String _ssid ="TP-LINK_0D6E";
String _password = "1978oksana";
String _ssidAP = "WiFi";
String _passwordAP = "";
void setup() {
Serial.begin(115200);
Serial.print("");
Serial.print("Start 1-WIFI");
WIFIinit();
}

void loop() {
  delay(1);

}
