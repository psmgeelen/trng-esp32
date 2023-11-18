#include <Arduino.h>

void setup() {
  Serial.begin(9600);
}
 
void loop() {
 
  Serial.println("-----------");
  Serial.println(esp_random());
  Serial.println(random(10));
  Serial.println(random(10,20));
 
  delay(1000);
}