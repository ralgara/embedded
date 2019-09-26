#include "DHT.h"

#define SER_PIN 7
#define _OE_PIN 6
#define RCLK_PIN 5
#define SRCLK_PIN 4
#define _SRCLR_PIN 3

#define DHTPIN 2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // First 74595 serial register, others daisy-chained
  pinMode(SER_PIN, OUTPUT);
  pinMode(_OE_PIN, OUTPUT);
  pinMode(RCLK_PIN, OUTPUT);
  pinMode(SRCLK_PIN, OUTPUT);
  pinMode(_SRCLR_PIN, OUTPUT);
  
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  Serial.println("DHTxx test!");
  dht.begin();
}

char sbuf[255];
byte v[4];
void loop() {
  digitalWrite(_OE_PIN, LOW);
  digitalWrite(_SRCLR_PIN, HIGH);
  for (int i=0; i<4; i++) {

    // Read DHT11
    // Reading time: ~250ms
    // Reading latency/age: 2s
    float h = dht.readHumidity();
    float t = dht.readTemperature();
    Serial.println(h);
    Serial.println(t);
    sprintf(sbuf, "temp: %f, hum: %f\n", h, t);
    //Serial.print(sbuf);

    
    if (i % 10 == 0) v[i] = random(255);
    if (i % 10 == 5) v[i] = random(255);
    if (i % 10 < 3) v[i]  = random(255);
    if (i % 10 > 7) v[i]  = random(255);
    shiftOut(v[i]);
  }
}

void shiftOut(byte value) {
  const int DELAY=3 ;
  int i = 0;
  int pinState;
  // Ground state for display matrix
  digitalWrite(SER_PIN, LOW);
  digitalWrite(RCLK_PIN, LOW);
  //Serial.print("v: "); Serial.println(value, HEX);
  for (i = 8; i >= 0; i--) {
    digitalWrite(SRCLK_PIN, LOW);
    delay(DELAY);
    boolean bitValue = value & (HIGH << i);
    digitalWrite(SER_PIN, bitValue);
    delay(DELAY);
    digitalWrite(SRCLK_PIN, HIGH);
    delay(DELAY);
    digitalWrite(SER_PIN, LOW); //ground data pin after shift to prevent bleed-through
  }
  delay(DELAY);
  digitalWrite(RCLK_PIN, HIGH);
}
