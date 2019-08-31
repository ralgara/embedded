
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

void loop() {
    byte v = 0;
    for (int i=0; i < 1000; i++) {
      v += pow(-1, i / 7);
      shiftOut(1 << v);
      Serial.print(i); Serial.print(" "); Serial.println(v);
      //(-1) ** (s // 8)
      delay(60);
    }
}
