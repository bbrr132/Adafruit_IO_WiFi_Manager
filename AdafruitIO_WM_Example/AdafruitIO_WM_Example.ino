#include "config.h"
#include <WiFiManager.h>
#define TRIGGER_PIN 1
#define WIFISSID "EXAMPLE"
int timeout = 120; // seconds to run for

AdafruitIO_Feed *counter = io.feed("counter");

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA); // explicitly set mode, esp defaults to STA+AP  
  // put your setup code here, to run once:
  pinMode(TRIGGER_PIN, INPUT_PULLUP);
  WiFiManager wm;
  //wm.resetSettings();
  bool res;
  res = wm.autoConnect(WIFISSID);
  if(!res) {
     Serial.println("Failed to connect");
     // ESP.restart();
  io.connect();
  counter->onMessage(handleMessage);
  while(io.mqttStatus() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  counter->get();
  Serial.println();
  Serial.println(io.statusText());

}

void loop() {
  io.run();
  checkWM();
}

void checkWM(){
  if ( digitalRead(TRIGGER_PIN) == LOW) {
    WiFiManager wm;    
    //wm.resetSettings();
    wm.setConfigPortalTimeout(timeout);
    if (!wm.startConfigPortal(apName)) {
      Serial.println("failed to connect and hit timeout");
      delay(3000);
      ESP.restart();
      delay(5000);
    }
    Serial.println("connected...yeey :)");
}
}

void handleMessage(AdafruitIO_Data *data) {
  Serial.print("received <- ");
  Serial.println(data->value());
}
