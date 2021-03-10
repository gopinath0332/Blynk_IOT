/*************************************************************
  Download latest Blynk library here:
    https://github.com/blynkkk/blynk-library/releases/latest

  Blynk is a platform with iOS and Android apps to control
  Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build graphic interfaces for all your
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: http://www.blynk.cc
    Sketch generator:           http://examples.blynk.cc
    Blynk community:            http://community.blynk.cc
    Follow us:                  http://www.fb.com/blynkapp
                                http://twitter.com/blynk_app

  Blynk library is licensed under MIT license
  This example code is in public domain.

 *************************************************************
  This example runs directly on NodeMCU.

  Note: This requires ESP8266 support package:
    https://github.com/esp8266/Arduino

  Please be sure to select the right NodeMCU module
  in the Tools -> Board menu!

  For advanced settings please follow ESP examples :
   - ESP8266_Standalone_Manual_IP.ino
   - ESP8266_Standalone_SmartConfig.ino
   - ESP8266_Standalone_SSL.ino

  Change WiFi ssid, pass, and Blynk auth token to run :)
  Feel free to apply it to any other example. It's simple!
 *************************************************************/

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include "credential.h"
#include <BlynkSimpleEsp8266.h>
#include <SPI.h>
#define FASTLED_ESP8266_RAW_PIN_ORDER
#include "FastLED.h"

#define NUM_LEDS1 30
#define LED_TYPE    WS2812
#define COLOR_ORDER GRB
CRGB leds1[NUM_LEDS1];
char auth[] = "tLTYZXlx0FIfTrMr7tSaPdYBqGIqNDFY";
char ssid[] = WIFI_SSID;
char pass[] = WIFI_PASSWD;
#define PIN1 D1
int data=255;
int r,g,b;
void setup()
{
  Serial.begin(9600);
//  Blynk.begin(auth, ssid, pass, "192.168.1.107", 8080);
  Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,5), 8080);
  FastLED.addLeds<LED_TYPE, PIN1, COLOR_ORDER>(leds1, NUM_LEDS1).setCorrection( TypicalLEDStrip );
}

BLYNK_WRITE(V3) // RGB Zerbra control pin
{
  r = param[0].asInt();
  g = param[1].asInt();
  b = param[2].asInt();
  static1(r, g, b);
//  static1(r, g, b,data);
}

void loop()
{
  Blynk.run();
}

BLYNK_WRITE(V2) // brightness control slider pin
{
  data = param.asInt();
  FastLED.setBrightness(data);
}

void static1(int r, int g, int b)
{
//  FastLED.setBrightness(brightness);
  for (int i = 0; i < NUM_LEDS1; i++ )
  {
    leds1[i] = CRGB(r, g, b);
  }
  FastLED.show();
}
