#include <Adafruit_NeoPixel.h>

// TMP36 Pin Variables
int tempPin = A0;  // the output pin of the TMP36
#define PIN 6       // Define the pin where the data line is connected
#define NUMPIXELS 12 // Number of NeoPixels in the ring

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

const float temperatureThreshold = 0.5;  // Threshold for temperature ranges
float averageTemperature = 0.0;  // Variable to store average temperature

void setup() {
  Serial.begin(9600);
  strip.begin();
  strip.show();  // Initialize all pixels to 'off'

  // Calculate the initial average temperature
  for (int i = 0; i < 10; i++) {
    averageTemperature += readTemperature();
    delay(100);
  }
  averageTemperature /= 10;
}

void loop() {
  float currentTemperature = readTemperature();
  Serial.println(currentTemperature);

  // Check the temperature range and display the corresponding light pattern
  if (currentTemperature < averageTemperature - temperatureThreshold) {
    Serial.println("Cold");
    displayColdPattern();
  } else if (currentTemperature > averageTemperature + temperatureThreshold) {
    Serial.println("Hot");
    displayHotPattern();
  } else {
    Serial.println("Medium");
    displayMediumPattern();
  }

  delay(1000);
}

float readTemperature() {
  int reading = analogRead(tempPin);  
  float voltage = reading * 3.3;
  voltage /= 1024.0; 
  float temperatureC = (voltage - 0.5) * 100;
  return temperatureC;
}

void displayColdPattern() {
  // Calm blue color
  uint32_t color = strip.Color(0, 0, 128);
  applyFadeEffect(color);
}

void displayHotPattern() {
  // Bright red color
  uint32_t color = strip.Color(255, 0, 0);
  applyFadeEffect(color);
}

void displayMediumPattern() {
  // Color in between blue and red, like purple
  uint32_t color = strip.Color(128, 0, 128);
  applyFadeEffect(color);
}

void applyFadeEffect(uint32_t color) {
  for (int brightness = 0; brightness <= 255; brightness++) {
    for (int i = 0; i < NUMPIXELS; i++) {
      strip.setPixelColor(i, dimColor(color, brightness));
    }
    strip.show();
    delay(10);
  }
  for (int brightness = 255; brightness >= 0; brightness--) {
    for (int i = 0; i < NUMPIXELS; i++) {
      strip.setPixelColor(i, dimColor(color, brightness));
    }
    strip.show();
    delay(10);
  }
}

// Function to apply brightness to a color
uint32_t dimColor(uint32_t color, uint8_t brightness) {
  uint8_t r = (uint8_t)(color >> 16);
  uint8_t g = (uint8_t)(color >> 8);
  uint8_t b = (uint8_t)color;
  r = (r * brightness) / 255;
  g = (g * brightness) / 255;
  b = (b * brightness) / 255;
  return strip.Color(r, g, b);
}
