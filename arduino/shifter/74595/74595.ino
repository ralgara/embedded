
int RCLK_PIN = 8;
int SRCLK_PIN = 9;
int SER_PIN = 10;
int OE_PIN = 13;

void setup() {
  //set pins to output because they are addressed in the main loop
  pinMode(RCLK_PIN, OUTPUT);
  pinMode(SRCLK_PIN, OUTPUT);
  pinMode(SER_PIN, OUTPUT);
  pinMode(OE_PIN, OUTPUT);
  digitalWrite(OE_PIN, HIGH);
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
}

void shiftOut(byte value) {
  int i=0;
  int pinState;
  digitalWrite(SER_PIN, LOW);
  digitalWrite(RCLK_PIN, LOW);
  for (i=7; i>=0; i--) {
    digitalWrite(SRCLK_PIN, LOW);
    digitalWrite(SER_PIN, value & (HIGH<<i));
    digitalWrite(SRCLK_PIN, HIGH);
    digitalWrite(SER_PIN, LOW); //ground data pin after shift to prevent bleed-through
  }
  digitalWrite(RCLK_PIN, HIGH);
}

const int BITS = 8;
const int N = 3;
const byte PERIODS[N] = {1,3,4};

int t = 0;  // Object clock: argument to oscillators
int tz = 0; // Hardware clock: CPU loop counter, basis for PCM intensity control via register OE
const int R = 2000;  // Object ratio = CPU loops between register updates
const float Z = 100; // Inverse duty cycle
boolean oe = LOW;
boolean oep = HIGH;
void loop() {
  if (oep != oe) {
    oe = oep;
    digitalWrite(OE_PIN, oe);
    //Serial.print("\noep=");Serial.print(oep);Serial.print("\n");    
  }
  oep = sin(tz/Z) > 0;
  
  //iterate objects and evolve position
  if (tz % R == 0) {
    byte out = 0;
    for (int i=0; i < N; i++) { // output bits
      float s = (BITS/2) * (1 + sin(float(t) / PERIODS[i])); //
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
