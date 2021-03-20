/**
   Reference:
   https://www.viralsciencecreativity.com/post/home-automation-2-modes-switch-and-application-control
*/

#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include "credential.h"

char auth[] = "Jy_XFCLNaCuNfQIkhpiwXQFSDH9XowgV";

char ssid[] = WIFI_SSID;
char pass[] = WIFI_PASSWD;

BlynkTimer timer;

void checkPhysicalButton();

int relay1State = LOW;
int pushButton1State = HIGH;

#define RELAY_PIN_1 16 //D0

#define PUSH_BUTTON_1 5 //D1

#define VPIN_BUTTON_1 V0

BLYNK_CONNECTED()
{
  Serial.println("connected to Blynk");

  // Request the latest state from the server

  Blynk.syncVirtual(VPIN_BUTTON_1);
}

// When App button is pushed - switch the state
BLYNK_WRITE(VPIN_BUTTON_1)
{
  relay1State = param.asInt();
  Serial.println(relay1State);
  digitalWrite(RELAY_PIN_1, relay1State);
}

void checkPhysicalButton()
{

  Serial.println(digitalRead(PUSH_BUTTON_1));

   Blynk.virtualWrite(VPIN_BUTTON_1, digitalRead(PUSH_BUTTON_1));

  /*if (digitalRead(PUSH_BUTTON_1) == LOW)
  {
    // Serial.println("LOW state");
    if (pushButton1State == 0)
    {
      // digitalWrite(RELAY_PIN_1, LOW);
      Blynk.virtualWrite(VPIN_BUTTON_1, 0);
      pushButton1State = 1;
    }
  }
  else if (digitalRead(PUSH_BUTTON_1) == HIGH)
  {
    // Serial.println("HIGH State");
    if (pushButton1State == 1)
    {
      // digitalWrite(RELAY_PIN_1, HIGH);
      Blynk.virtualWrite(VPIN_BUTTON_1, 1);
      pushButton1State = 0;
    }
  }*/
}

void setup()
{
  // Debug console
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass, IPAddress(192, 168, 1, 5), 8080);

  // Setup a function to be called every 100 ms
  timer.setInterval(500L, checkPhysicalButton);
}

void loop()
{
  Blynk.run();
  timer.run();
}
