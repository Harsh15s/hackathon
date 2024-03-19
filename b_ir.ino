#define BLYNK_TEMPLATE_ID "TMPL3plUe1YOs"
#define BLYNK_TEMPLATE_NAME "Trafficcongestion"
#define BLYNK_AUTH_TOKEN "7cmkqBOtSgWa15np691zU_vgE6_uSmQq"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

char ssid[] = ""; // Your WiFi SSID
char pass[] = ""; // Your WiFi password

WidgetLED led1(V1); // Virtual LED widget for the first IR sensor
WidgetLED led2(V2); // Virtual LED widget for the second IR sensor

const int IR_PIN = 4; // Define the pin for the first IR sensor
const int Ir_PIN = 5; // Define the pin for the second IR sensor

void setup() {
  Serial.begin(9600);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  pinMode(IR_PIN, INPUT);
  pinMode(Ir_PIN, INPUT);
}

void loop() {
  Blynk.run();

  int irValue = digitalRead(IR_PIN);
  int IrValue = digitalRead(Ir_PIN);

  if (irValue == LOW) {
    Serial.println("IR sensor 1 detected an object!");
    led1.on(); // Turn on virtual LED for sensor 1
    Blynk.virtualWrite(V1, 1023); // Set graph value high for sensor 1
  } else {
    Serial.println("No object detected in sensor 1");
    led1.off(); // Turn off virtual LED for sensor 1
    Blynk.virtualWrite(V1, 0); // Set graph value low for sensor 1
  }

  if (IrValue == LOW) {
    Serial.println("IR sensor 2 detected an object!");
    led2.on(); // Turn on virtual LED for sensor 2
    Blynk.virtualWrite(V2, 1023); // Set graph value high for sensor 2
  } else {
    Serial.println("No object detected in sensor 2");
    led2.off(); // Turn off virtual LED for sensor 2
    Blynk.virtualWrite(V2, 0); // Set graph value low for sensor 2
  }

  delay(500); // Wait for 500 milliseconds before reading again
}
