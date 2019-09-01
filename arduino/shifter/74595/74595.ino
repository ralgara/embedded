
int RCLK_PIN = 8;
int SRCLK_PIN = 9;
int SER_PIN = 10;

void setup() {
  //set pins to output because they are addressed in the main loop
  pinMode(RCLK_PIN, OUTPUT);
  pinMode(SRCLK_PIN, OUTPUT);
  pinMode(SER_PIN, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
}

int IDLE_MS = 100;

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
const byte PERIODS[N] = {2,3,4};

int t = 0;
void loop() {
      //iterate objects and evolve position
      byte out = 0;
      for (int i=0; i < N; i++) { // output bits
          float s = (BITS/2) * (1 + sin(float(t) / PERIODS[i])); //
          byte ss = 1 << int(s);
          out |= ss;
          Serial.print("t=");Serial.print(t);Serial.print(",i= ");Serial.print(i);
          Serial.print(",s=");Serial.print(s);Serial.print(",ss=");Serial.print(ss);
          Serial.print(",out=");Serial.print(out);
          Serial.println();
      }
      shiftOut(out);
      Serial.print("---");Serial.print(out);Serial.print(" ");Serial.print(out);
      Serial.println();
      t += 1;
      delay(200);
}
