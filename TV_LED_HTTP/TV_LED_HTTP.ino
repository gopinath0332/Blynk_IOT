#include <Adafruit_NeoPixel.h>
#include <SPI.h>
#include <BlynkSimpleEsp8266.h>
#include <ESP8266WiFi.h>

#define PIN D2
#define NUMPIXELS 30
#define BLYNK_PRINT Serial
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

char auth[] = "bpyChErG39Ob_MWPksW8sZnNC6DBin7U";
char ssid[] = "Alpha_Home";
char pass[] = "Home123*";
int mode = 0;
int R = 1023;
int G = 1023;
int B = 1023;
String header;
WiFiServer server(80);

void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass, "192.168.1.107", 8080);
  pixels.begin();
  
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
   Serial.print(".");
 }
 Serial.println("");
 Serial.println("WiFi connected-->");
 Serial.println("Copy this IP address: ");
 Serial.println(WiFi.localIP());
 server.begin();
}

void loop()
{
  Blynk.run();

  WiFiClient client = server.available();   
  if (client) {                             // If a new client connects,
    Serial.println("new client connected");
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected())
      if (client.available()) { 
        char c = client.read();             
        Serial.write(c);                    
        header += c;
        if (c == '\n') {
          if (currentLine.length() == 0) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();

            if (header.indexOf("GET /LED/on") >= 0) {
                pixels.clear();
                for(int i=0;i<NUMPIXELS;i++){
                  pixels.setPixelColor(i, pixels.Color(R,G,B));
                  pixels.show();
                }
                client.println("Turned on");
              }else if (header.indexOf("GET /LED/off") >= 0) {
                  pixels.clear();
                  for(int i=0;i<NUMPIXELS;i++){
                    pixels.setPixelColor(i, pixels.Color(0,0,0));
                    pixels.show();
                  }
                  client.println("Turned off");
                }
                break;
            } else {
              currentLine = "";
            }
          } else if (c != '\r') {  
            currentLine += c;      
          }
      }
  }

  header = "";
  client.stop();
  Serial.println("Client disconnected");
  Serial.println("");
}

BLYNK_WRITE(V2)
{
  pixels.clear();
  R = param[0].asInt();
  G = param[1].asInt();
  B = param[2].asInt();
  Serial.println(R);
  Serial.println(G);
  Serial.println(B);
  for(int i=0;i<NUMPIXELS;i++){
    pixels.setPixelColor(i, pixels.Color(R,G,B));
    pixels.show();
  }
}
