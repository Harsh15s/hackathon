#define BLYNK_TEMPLATE_ID "TMPL3Qu6QKcdF"
#define BLYNK_TEMPLATE_NAME "TrafficcongestionCopy"
#define BLYNK_AUTH_TOKEN "k05dICZR88KUlPIn2PzmzAk0U8lsnBTR"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

char ssid[] = "Tech1704"; // Your WiFi SSID
char pass[] = "Ddgtechfifa1704#"; // Your WiFi password

WidgetLED led1(V1); // Virtual LED widget for LED 1
WidgetLED led2(V2); // Virtual LED widget for LED 2
WidgetLED led3(V3); // Virtual LED widget for LED 3
WidgetLED led4(V4); // Virtual LED widget for LED 4

const int IR_PIN_1 = 4; // Define the pin for IR sensor 1
const int IR_PIN_2 = 5; // Define the pin for IR sensor 2

bool switch1State = false;
bool switch2State = false;

unsigned long lastSensor1Time = 0; // Time when sensor 1 last stopped
unsigned long lastSensor2Time = 0; // Time when sensor 2 last stopped
const unsigned long sensorStopTime = 10000; // Stop sensor input for 10 seconds

void setup() {
  Serial.begin(9600);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  pinMode(IR_PIN_1, INPUT);
  pinMode(IR_PIN_2, INPUT);

  led1.off();
  led2.off();
  led3.off();
  led4.off();
}

void loop() {
  Blynk.run();
  Blynk.syncVirtual(V3, V4); // Sync virtual pins for switches

  // Read IR sensor 1 if not stopped
  if (millis() - lastSensor1Time > sensorStopTime || !switch1State) {
    int irValue1 = digitalRead(IR_PIN_1);
    if (irValue1 == LOW) {
      led1.on(); // Turn on LED 1 when sensor 1 detects an object
      led3.off(); // Turn off LED 3 when sensor 1 detects an object
    } else {
      led1.off(); // Turn off LED 1 when sensor 1 does not detect an object
    }
  }

  // Read IR sensor 2 if not stopped
  if (millis() - lastSensor2Time > sensorStopTime || !switch2State) {
    int irValue2 = digitalRead(IR_PIN_2);
    if (irValue2 == LOW) {
      led2.on(); // Turn on LED 2 when sensor 2 detects an object
      led4.off(); // Turn off LED 4 when sensor 2 detects an object
    } else {
      led2.off(); // Turn off LED 2 when sensor 2 does not detect an object
    }
  }

  // Check virtual switch 1 state
  if (switch1State) {
    led3.on(); // Turn on LED 3 when switch 1 is toggled
    led1.off(); // Turn off LED 1 when switch 1 is toggled
    lastSensor1Time = millis(); // Update last stop time for sensor 1
  } else {
    led3.off(); // Turn off LED 3 when switch 1 is not toggled
  }

  // Check virtual switch 2 state
  if (switch2State) {
    led4.on(); // Turn on LED 4 when switch 2 is toggled
    led2.off(); // Turn off LED 2 when switch 2 is toggled
    lastSensor2Time = millis(); // Update last stop time for sensor 2
  } else {
    led4.off(); // Turn off LED 4 when switch 2 is not toggled
  }

  delay(100); // Delay for stability
}

BLYNK_WRITE(V3) { // Called when virtual switch 1 state changes
  switch1State = param.asInt(); // Update switch 1 state
}

BLYNK_WRITE(V4) { // Called when virtual switch 2 state changes
  switch2State = param.asInt(); // Update switch 2 state
}
