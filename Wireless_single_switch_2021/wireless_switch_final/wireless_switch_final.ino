/**
 * Ref: https://iotcircuithub.com/nodemcu-esp8266-blynk-home-automation/
 * 
 * 
 * Note: 
 * Low stage relay latch switch used, 0 - ON, 1 - OFF
 * Hence, reverse the Virtual Pin values in Blynk App swtich, 1 - 0
 * 
 */


#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include "credential.h"

char auth[] = "Jy_XFCLNaCuNfQIkhpiwXQFSDH9XowgV";

char ssid[] = WIFI_SSID;
char pass[] = WIFI_PASSWD;

// define the GPIO connected with Relays and switches
#define RelayPin1 5 //D1

#define SwitchPin1 10 //SD3

#define wifiLed 16 //D0

#define VPIN_BUTTON_1 V1

int wifiFlag = 0;

int toggleState_1 = 1; //Define integer to remember the toggle state for relay 1

BlynkTimer timer;

BLYNK_CONNECTED()
{
  // Request the latest state from the server
  Blynk.syncVirtual(VPIN_BUTTON_1);
}

BLYNK_WRITE(VPIN_BUTTON_1)
{
  toggleState_1 = param.asInt();
  digitalWrite(RelayPin1, toggleState_1);
}

void checkBlynkStatus()
{ // called every 3 seconds by SimpleTimer

  bool isconnected = Blynk.connected();
  if (isconnected == false)
  {
    wifiFlag = 1;
    digitalWrite(wifiLed, HIGH); //Turn off WiFi LED
  }
  if (isconnected == true)
  {
    wifiFlag = 0;
    digitalWrite(wifiLed, LOW); //Turn on WiFi LED
  }
}

void with_internet()
{
  int switchState = digitalRead(SwitchPin1);
  if (digitalRead(SwitchPin1) == LOW) {
    // delay(200);
    if(toggleState_1 == 1){
      toggleState_1 = 0;
      digitalWrite(RelayPin1, HIGH);
      Blynk.virtualWrite(VPIN_BUTTON_1, 1);
    }

  }else{
    // delay(200);
    if(toggleState_1 == 0 ){
      toggleState_1 = 1;
      digitalWrite(RelayPin1, LOW);
      Blynk.virtualWrite(VPIN_BUTTON_1, 0);
    }
  }
}

void without_internet()
{
  //  Serial.println("without internet");
}

void setup()
{
  // Debug console
  Serial.begin(9600);

  pinMode(RelayPin1, OUTPUT);

  pinMode(wifiLed, OUTPUT);

  pinMode(SwitchPin1, INPUT_PULLUP);

  //During Starting all Relays should TURN OFF
  digitalWrite(RelayPin1, toggleState_1);

  Blynk.begin(auth, ssid, pass, IPAddress(192, 168, 1, 5), 8080);

  timer.setInterval(3000L, checkBlynkStatus); // check if Blynk server is connected every 3 seconds
}

void loop()
{
  if (WiFi.status() != WL_CONNECTED)
  {
    //    Serial.println("WiFi Not Connected");
  }
  else
  {
    //    Serial.println("WiFi Connected");
    Blynk.run();
  }

  timer.run(); // Initiates SimpleTimer

  if (wifiFlag == 0)
    with_internet();
  else
    without_internet();
}
