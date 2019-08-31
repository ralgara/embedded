
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
const int N = 1;
const byte PERIODS[N] = {18};
byte c[N];
int t = 0;
void loop() {
      byte out = 0;
      //iterate objects and evolve position
      for (int i=0; i < N; i++) { // output bits
          int p = pow(-1, t / PERIODS[i]);
          c[i] += p;
          out += 1 << c[i];
          Serial.print(t);Serial.print(" ");Serial.print(i);Serial.print(" ");
          Serial.print(p);Serial.print(" ");Serial.print(c[i]);Serial.print(" ");
          Serial.print(out);Serial.print(" ");
          Serial.println();
      }
      shiftOut(out);
      Serial.print("---");Serial.print(out);Serial.print(" ");Serial.print(out);
      Serial.println();
      t += 1;
      delay(200);
}
