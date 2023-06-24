// This program is used to demonstrate activation/deactivation of sending JSON data from Arduino board
// through the Serial Port on the Windows PC.
// To activate sending JSON data to the PC, send 'a'(activate) from console program json_receiver.
// To pause sending JSON data to the PC, send 'p'(pause) from console program json_receiver.
// When sending is active all received messages are logged to the file.

#include <Arduino.h>
#include <ArduinoJson.h>

constexpr size_t DELAY_ms = 1000;
constexpr size_t RESPONSE_SIZE = 256;
uint32_t timestamp;
uint32_t cnt;
char command;
bool send_flag;

void setup() {
  Serial.begin(9600);
  Serial.println("Setup....");
  timestamp = millis();
}

void loop() {
  if (Serial.available())   { command = Serial.read();}
  if      (command == 'a')  { send_flag = true; }
  else if (command == 'p')  { send_flag = false; }
  
  if (DELAY_ms <= millis() - timestamp){
    if (send_flag){
      DynamicJsonDocument response(RESPONSE_SIZE);
      response["count"] = cnt;
      response["timestamp"] = timestamp;
      serializeJson(response, Serial); Serial.println();
      //Serial.println(cnt);
    }
    //Serial.print("timestamp = "); Serial.println(timestamp);
    timestamp = millis();
    ++cnt;
  }
}
