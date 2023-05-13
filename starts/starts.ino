

#include <MPU6050_tockn.h>
#include <Servo.h>

// Pin Definitions
const int LED_PIN_G = 7;
const int LED_PIN_R = 6;
const int BUZZER_PIN = 5;
const int SERVO_PIN_1 = 9;
const int SERVO_PIN_2 = 10;
const int SERVO_PIN_3 = 11;
const int SERVO_PIN_4 = 12;

// Object Declarations
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;

MPU6050 mpu6050(Wire);

// Time Variables
unsigned long timer = 0;
const unsigned long interval = 1000;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);

  servo1.attach(SERVO_PIN_1);
  servo2.attach(SERVO_PIN_2);
  servo3.attach(SERVO_PIN_3);
  servo4.attach(SERVO_PIN_4);

  pinMode(LED_PIN_G, OUTPUT);
  pinMode(LED_PIN_R, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
}

void loop() {
  digitalWrite(LED_PIN_R, HIGH);
  digitalWrite(LED_PIN_G, HIGH);
  digitalWrite(BUZZER_PIN, HIGH);
  mpu6050.update();

  if (millis() - timer > interval) {
    Serial.print("angleX: ");
    Serial.print(mpu6050.getAngleX());
    Serial.print("  angleY: ");
    Serial.println(mpu6050.getAngleY());

    timer = millis();
  }

  // x-axis / roll
  int angleX = mpu6050.getAngleX();
  int angleY = mpu6050.getAngleY();
  servo2.write(90 - angleY); // unstable angle
  servo1.write(90 + angleY); // unstable angle

  // y-axis / pitch
  servo3.write(90 + angleX); // unstable angle
  servo4.write(90 - angleX); // unstable angle

  delay(10); // Small delay to reduce processing load
}
