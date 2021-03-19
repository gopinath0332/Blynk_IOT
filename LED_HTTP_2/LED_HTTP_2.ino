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

String header;
String LED1State = "off";

WiFiServer server(80);

void setup()
{
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass, "192.168.1.107", 8080);
  pixels.begin();
  mode = 1;

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

BLYNK_WRITE(V2)
{
  pixels.clear();
  int R = param[0].asInt();
  int G = param[1].asInt();
  int B = param[2].asInt();
  Serial.println(R);
  Serial.println(G);
  Serial.println(B);
  for(int i=0;i<NUMPIXELS;i++){
    pixels.setPixelColor(i, pixels.Color(R,G,B));
    pixels.show();
  }
}

BLYNK_WRITE(V3)
{
  mode = param.asInt();
}

BLYNK_WRITE(V4)
{
  Serial.println("Writing V4 Pin");
  mode = 0;
}

void loop()
{
  Blynk.run(); 

  WiFiClient client = server.available();
  if (client) {                            
    Serial.println("new client connected");         
    String currentLine = ""; 
    client.println("HTTP/1.1 200 OK");
    client.println("Content-type:text/html");
    client.println("Connection: close");
    client.println();
  }
}
