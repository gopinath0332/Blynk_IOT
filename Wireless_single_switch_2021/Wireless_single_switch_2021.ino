/** 
 *  Reference url
 *  https://www.viralsciencecreativity.com/post/home-automation-2-modes-switch-and-application-control
 *  
 *  https://www.viralsciencecreativity.com/post/blynk-home-automation-physical-button-feedback-status
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
  digitalWrite(RELAY_PIN_1, relay1State);
}

void checkPhysicalButton()
{

  if (digitalRead(PUSH_BUTTON_1) == LOW)
  {
    // Serial.println("LOW state");
    if (pushButton1State == 0)
    {
      digitalWrite(RELAY_PIN_1, LOW);
      Blynk.virtualWrite(VPIN_BUTTON_1, 0);
      pushButton1State = 1;
    }
  }
  else if (digitalRead(PUSH_BUTTON_1) == HIGH)
  {
    // Serial.println("HIGH State");
    if (pushButton1State == 1)
    {
      digitalWrite(RELAY_PIN_1, HIGH);
      Blynk.virtualWrite(VPIN_BUTTON_1, 1);
      pushButton1State = 0;
    }
  }
  /*if (digitalRead(PUSH_BUTTON_1) == LOW)
  {
    // pushButton1State is used to avoid sequential toggles
    if (pushButton1State != LOW)
    {

      // Toggle Relay state
      relay1State = !relay1State;
      digitalWrite(RELAY_PIN_1, relay1State);

      // Update Button Widget
      Blynk.virtualWrite(VPIN_BUTTON_1, relay1State);
    }
    pushButton1State = LOW;
  }
  else
  {
    pushButton1State = HIGH;
  }*/
}

void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass, IPAddress(192, 168, 1, 5), 8080);

  pinMode(RELAY_PIN_1, OUTPUT);
  pinMode(PUSH_BUTTON_1, INPUT_PULLUP);
  digitalWrite(RELAY_PIN_1, relay1State);

  // Setup a function to be called every 100 ms
  timer.setInterval(500L, checkPhysicalButton);
}

void loop()
{
  Blynk.run();
  timer.run();
}
