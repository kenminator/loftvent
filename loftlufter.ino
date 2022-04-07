#include <DHT.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET 4
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

//TEMP- OG RHSENSOR:
#define DHTPIN 13
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

float t = 0;
int rh = 0;

int period = 2000;
unsigned long time_now = 0;

#define relPin 7
#define zpunktpot A0
int zpunkt = 0;

void setup() {
  Wire.begin();
  Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3D);

  pinMode(relPin, OUTPUT);
  digitalWrite(relPin, 0);

  displayText();
}

void displayText() {
    rh = dht.readHumidity();
    t = dht.readTemperature();
    zpunkt = map(analogRead(zpunktpot), 1023, 0, 0, 100);

    display.clearDisplay();
    display.setTextColor(WHITE);
    display.setTextSize(2);
    display.setCursor(0, 0);
    display.print(String("RH:") + rh + String("/") + zpunkt);
    display.setCursor(0,32);
    display.print(String("Temp:") + t);
    display.display();
}

void loop() {

  // put your main code here, to run repeatedly:
  if (millis() >= (time_now + period)) {
    time_now += period;

    displayText();

    Serial.println(rh);
    if (rh > map(analogRead(zpunktpot), 1023, 0, 0, 100)) {
      digitalWrite(relPin, HIGH);
    }
    else if (rh < map(analogRead(zpunktpot), 1023, 0, 0, 100)) {
      digitalWrite(relPin, LOW);
    }
  }


}
