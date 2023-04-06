#include <ESP8266WiFi.h>
#include <TridentTD_LineNotify.h>
#include "SHTC3.h"
const char* ssid = "WIFI NAME"; 
const char* password = "WIFI PASS" ;
#define LINE_TOKEN  "LINE TOKEN" 
SHTC3 s(Wire);
void setup() {
  Wire.begin();
  Serial.begin(115200); Serial.println();
  Serial.println(LINE.getVersion());

  WiFi.begin(ssid, password);
  Serial.printf("WiFi connecting to %s\n",  ssid);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(400);
  }
  Serial.printf("\nWiFi connected\nIP : ");
  Serial.println(WiFi.localIP());

  
  LINE.setToken(LINE_TOKEN);
  LINE.notify("แจ้ง");
}

void loop() {
  delay(2000);
   float t = s.readTempC();
s.begin(true);
s.sample();
Serial.print("อุณหภูมิ(Temp) ");
Serial.print(s.readTempC());
Serial.print(" °C    ความชื้น(Humidity) ");
Serial.print(s.readHumidity());
Serial.println(" %");
  if (t > 40) {
    String LineText;
    String string1 = "อุณหภูมิ เกินกำหนด ";
    String string2 = " °C";
    LineText = string1 + t + string2;
    Serial.print("Line ");
    Serial.println(LineText);
    LINE.notify(LineText);
  }


}
