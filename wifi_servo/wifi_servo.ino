#include <ESP32Servo.h>
#include <WiFi.h>

#include "WemoSwitch.h"
#include "WemoManager.h"
#include "CallbackFunction.h"

Servo servo;

// prototypes
boolean connectWifi();

//on/off callbacks
void lightOn();
void lightOff();

//------- Replace the following! ------
char ssid[] = "TP-Link_CC8F";       // your network SSID (name)
char password[] = "";  // your network key

WemoManager wemoManager;
WemoSwitch *light = NULL;

int servoPin = 4;

void setup()
{
  Serial.begin(115200);

  // Set WiFi to station mode and disconnect from an AP if it was Previously
  // connected
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  // Attempt to connect to Wifi network:
  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  IPAddress ip = WiFi.localIP();
  Serial.println(ip);

  wemoManager.begin();
  // Format: Alexa invocation name, local port no, on callback, off callback
  light = new WemoSwitch("light", 80, lightOn, lightOff);
  wemoManager.addDevice(*light);
  servo.attach(servoPin);
}

void loop()
{
  wemoManager.serverLoop();
}

void lightOn() {
    servo.write(174);
    delay(800);
    servo.write(20);
    delay(1000);
}

void lightOff() {
    servo.write(174);
    delay(800);
    servo.write(20);
    delay(1000);
}
