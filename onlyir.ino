const int IR_PIN = 4; // Define the pin for the IR sensor
const int Ir_PIN = 5;
void setup() {
  Serial.begin(9600);
  pinMode(IR_PIN, INPUT);
  pinMode(Ir_PIN, INPUT);
}

void loop() {
  int irValue = digitalRead(IR_PIN);
  int IrValue = digitalRead(Ir_PIN);
  
  if (irValue == LOW) {
    Serial.println("IR sensor detected an object()!");
  } else {
    Serial.println("No object detected.");
  }

  if (IrValue == LOW) {
    Serial.println("IR sensor detected an object{}!");
  } else {
    Serial.println("No object detected.");
  }

  delay(500); // Wait for 500 milliseconds before reading again
}
