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

void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass, "192.168.1.107", 8080);
  pixels.begin();
//  mode = 1;
}

//BLYNK_CONNECTED() {
//  Serial.println("Device connected");
//  Blynk.syncAll();
//}

BLYNK_WRITE(V2)
{
  pixels.clear();
  mode = 0;
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
  Serial.println("V2 mode");
  Serial.println(mode);
}

BLYNK_WRITE(V4)
{
  mode = param.asInt();
}

void loop()
{
  Blynk.run();
  switch(mode){
    case 1: {
      Serial.println("Item 1 selected");
      rainbow(20);
      break;
    }
    case 2: {
      Serial.println("Item 2 selected");
      theaterChaseRainbow(100);
      break;
    }
  }
}

// Rainbow-enhanced theater marquee. Pass delay time (in ms) between frames.
void theaterChaseRainbow(int wait) {
  int firstPixelHue = 0;     // First pixel starts at red (hue 0)
  for(int a=0; a<30; a++) {  // Repeat 30 times...
    for(int b=0; b<3; b++) { //  'b' counts from 0 to 2...
      pixels.clear();         //   Set all pixels in RAM to 0 (off)
      // 'c' counts up from 'b' to end of pixels in increments of 3...
      for(int c=b; c<pixels.numPixels(); c += 3) {
        // hue of pixel 'c' is offset by an amount to make one full
        // revolution of the color wheel (range 65536) along the length
        // of the pixels (pixels.numPixels() steps):
        int      hue   = firstPixelHue + c * 65536L / pixels.numPixels();
        uint32_t color = pixels.gamma32(pixels.ColorHSV(hue)); // hue -> RGB
        pixels.setPixelColor(c, color); // Set pixel 'c' to value 'color'
      }
      pixels.show();                // Update pixels with new contents
      delay(wait);                 // Pause for a moment  
      firstPixelHue += 65536 / 90; // One cycle of color wheel over 90 frames
    }
  }
}

// Rainbow cycle along whole pixels. Pass delay time (in ms) between frames.
void rainbow(int wait) {
  Serial.println("Rainbow mode");
  Serial.println(mode);
  // Hue of first pixel runs 3 complete loops through the color wheel.
  // Color wheel has a range of 65536 but it's OK if we roll over, so
  // just count from 0 to 3*65536. Adding 256 to firstPixelHue each time
  // means we'll make 3*65536/256 = 768 passes through this outer loop:
  for(long firstPixelHue = 0; firstPixelHue < 3*65536; firstPixelHue += 256) {
    Serial.println("Inside for cool ");
    Serial.println(mode);
    for(int i=0; i<pixels.numPixels(); i++) { // For each pixel in pixels...
      // Offset pixel hue by an amount to make one full revolution of the
      // color wheel (range of 65536) along the length of the pixels
      // (pixels.numPixels() steps):
      int pixelHue = firstPixelHue + (i * 65536L / pixels.numPixels());
      // pixels.ColorHSV() can take 1 or 3 arguments: a hue (0 to 65535) or
      // optionally add saturation and value (brightness) (each 0 to 255).
      // Here we're using just the single-argument hue variant. The result
      // is passed through pixels.gamma32() to provide 'truer' colors
      // before assigning to each pixel:
      pixels.setPixelColor(i, pixels.gamma32(pixels.ColorHSV(pixelHue)));
    }
    pixels.show(); // Update pixels with new contents
    delay(wait);  // Pause for a moment
  }
}
