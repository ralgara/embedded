
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

void loop() {
    Serial.println("=== LOOP");
    const int idle_ms=100;
    digitalWrite(LED_BUILTIN, LOW);
    delay(idle_ms * 4);
    digitalWrite(RCLK_PIN, LOW);
    Serial.println("RCLK_PIN: 0");
    byte v = 0;
    for (int i=0; i<8; i++) {
      digitalWrite(SRCLK_PIN, LOW);
      Serial.println("SRCLK_PIN: 0");
      digitalWrite(SER_PIN, i % 2);
      Serial.print("SER_PIN: ");
      Serial.println(i%2);      
      delay(idle_ms * 2);
      digitalWrite(SRCLK_PIN, HIGH);
      Serial.println("SRCLK_PIN: 1");
      delay(idle_ms);
    }
    digitalWrite(LED_BUILTIN, HIGH);
    delay(idle_ms * 4);
    digitalWrite(RCLK_PIN, HIGH);
    Serial.println("RCLK_PIN: 1");
}
