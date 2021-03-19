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
  This example runs directly on ESP8266 chip.

  Note: This requires ESP8266 support package:
    https://github.com/esp8266/Arduino

  Please be sure to select the right ESP8266 module
  in the Tools -> Board menu!

  Change WiFi ssid, pass, and Blynk auth token to run :)
  Feel free to apply it to any other example. It's simple!
 *************************************************************/

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "srGI9O6B8srQH8yBUt1WIp5Ff1hL5ZYI";
char ssid[] = "Alpha_Home";
char pass[] = "Home123*";

 
#define RELAY1 D1
#define BUTTON1 D2
#define BUTTON2 D3

int switch_ON_Flag1_previous_I = 0;


BLYNK_CONNECTED() {
    Blynk.syncAll();
}

BLYNK_WRITE(V1){
  int pinValue = param.asInt();
  digitalWrite(RELAY1, pinValue);
}

void singleswitch(){
  if (digitalRead(BUTTON1) == LOW){
    if (switch_ON_Flag1_previous_I == 0 ){
      digitalWrite(RELAY1, LOW);
      Blynk.virtualWrite(V1, 0);
      switch_ON_Flag1_previous_I = 1;
    }
  }else if (digitalRead(BUTTON1) == HIGH ){
     if (switch_ON_Flag1_previous_I == 1){
      digitalWrite(RELAY1, HIGH);
      Blynk.virtualWrite(V1, 1);
      switch_ON_Flag1_previous_I = 0;
     }
  }
}

void twoWaySwitch(){
  if (digitalRead(BUTTON1) == LOW){
    if (switch_ON_Flag1_previous_I == 0 ){
      digitalWrite(RELAY1, LOW);
      Blynk.virtualWrite(V1, 0);
      switch_ON_Flag1_previous_I = 1;
    }
  }else if (digitalRead(BUTTON1) == HIGH ){
     if (switch_ON_Flag1_previous_I == 1){
      digitalWrite(RELAY1, HIGH);
      Blynk.virtualWrite(V1, 1);
      switch_ON_Flag1_previous_I = 0;
     }
  }   

  
//  if (digitalRead(BUTTON2) == LOW){
//    if (switch_ON_Flag1_previous_I == 0 ){
//      digitalWrite(RELAY1, LOW);
//      Blynk.virtualWrite(V1, 0);
//      switch_ON_Flag1_previous_I = 1;
//    }
//  }else if (digitalRead(BUTTON2) == HIGH ){
//     if (switch_ON_Flag1_previous_I == 1){
//      digitalWrite(RELAY1, HIGH);
//      Blynk.virtualWrite(V1, 1);
//      switch_ON_Flag1_previous_I = 0;
//     }
//  }
  
}

void setup()
{
  // Debug console
  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass, "192.168.1.107", 8080);

  pinMode(RELAY1, OUTPUT);
  pinMode(BUTTON1, INPUT);
  pinMode(BUTTON2, INPUT);
}

void loop()
{
  
//  if(digitalRead(BUTTON1) == 1){
//    digitalWrite(RELAY1, HIGH);
//  }else if (digitalRead(BUTTON1) == 0){
//    digitalWrite(RELAY1, LOW);
//  }

  Blynk.run();

   singleswitch();
//  twoWaySwitch();
//  Serial.println("Button 1");
//  Serial.println(digitalRead(BUTTON1));
//  Serial.println("Button 2");
//  Serial.println(digitalRead(BUTTON2));
   
}
