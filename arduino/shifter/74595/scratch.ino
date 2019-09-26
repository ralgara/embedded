/* Blink control pins */
boolean s;
void _loop() {
  digitalWrite(SER_PIN, s);
  digitalWrite(_OE_PIN, s);
  digitalWrite(RCLK_PIN, s);
  digitalWrite(SRCLK_PIN, s);
  digitalWrite(_SRCLR_PIN, s);
  digitalWrite(LED_BUILTIN, s);
  Serial.print(s);
  Serial.println("@");
  s = !s;
  delay(500);
}


const int BITS = 8;
const int N = 3;
const byte PERIODS[N] = {1, 3, 4};

int t = 0;  // Object clock: argument to oscillators
int tz = 0; // Hardware clock: CPU loop counter, basis for PCM intensity control via register OE
const int R = 2000;  // Object ratio = CPU loops between register updates
const float Z = 100; // Inverse duty cycle
boolean oe = LOW;
boolean oep = HIGH;

void __loop() {
  if (oep != oe) {
    oe = oep;
    digitalWrite(_OE_PIN, oe);
    //Serial.print("\noep=");Serial.print(oep);Serial.print("\n");
  }
  oep = sin(tz / Z) > 0;

  //iterate objects and evolve position
  if (tz % R == 0) {
    byte out = 0;
    for (int i = 0; i < N; i++) { // output bits
      float s = (BITS / 2) * (1 + sin(float(t) / PERIODS[i])); //
      byte ss = 1 << int(s);
      out |= ss;
    }
    shiftOut(out);
    //    Serial.print("tz=");Serial.print(tz);
    //    Serial.print(",t=");Serial.print(t);
    //    Serial.print(",oe=");Serial.print(oe);
    //    Serial.print(",oep=");Serial.print(oep);
    //    Serial.println();
    t++;
  }
  tz++;
}
