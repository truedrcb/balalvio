
const int PIN_MUX_SIG = 4;
const int PIN_MUX_EN = 9;
const int PINS_MUX_SELECT[4] = {5, 6, 7, 8};

void setup() {
  pinMode(PIN_MUX_SIG, INPUT);
  pinMode(PIN_MUX_EN, OUTPUT);
  for (int i = 0; i < 4; i++) {
    pinMode(PINS_MUX_SELECT[i], OUTPUT);
  }

  Serial.begin(9600);
  Serial.println(F("Testing!"));

}

void loop() {
  Serial.print("[");
  for (int b = 0; b < 16; b++) {
    digitalWrite(PIN_MUX_EN, HIGH);
    for (int i = 0; i < 4; i++) {
      digitalWrite(PINS_MUX_SELECT[i], (b & (1 << i)) ? HIGH : LOW);
    }
    digitalWrite(PIN_MUX_EN, LOW);
    Serial.print((digitalRead(PIN_MUX_SIG) == HIGH) ? "1" : "0");
  }
  Serial.println("]");
  delay(500);
}
