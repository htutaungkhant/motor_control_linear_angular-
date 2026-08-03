#include <Arduino.h>

#define IN1  0
#define IN2  1
#define IN3  3
#define IN4  4

void setup() {
  Serial.begin(115200);
  delay(1000);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // Stop motors
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);

  Serial.println("ESP32-C3 Ready!");
}

void setMotors(float linear, float angular) {

  float leftSpeed  = linear - angular;
  float rightSpeed = linear + angular;

  // -------- LEFT MOTOR --------
  if (leftSpeed > 0.05) {
    // Forward
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
  }
  else if (leftSpeed < -0.05) {
    // Reverse
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
  }
  else {
    // Stop
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
  }

  // -------- RIGHT MOTOR --------
  // Right motor direction is reversed
  if (rightSpeed > 0.05) {
    // Forward
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
  }
  else if (rightSpeed < -0.05) {
    // Reverse
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
  }
  else {
    // Stop
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
  }
}

void loop() {

  if (Serial.available()) {

    String data = Serial.readStringUntil('\n');
    data.trim();

    int commaIndex = data.indexOf(',');

    if (commaIndex != -1) {

      float linear  = data.substring(0, commaIndex).toFloat();
      float angular = data.substring(commaIndex + 1).toFloat();

      setMotors(linear, angular);

      Serial.print("Linear : ");
      Serial.print(linear);

      Serial.print("   Angular : ");
      Serial.println(angular);
    }
  }
}
