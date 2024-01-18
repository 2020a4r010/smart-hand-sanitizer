#include <Servo.h>

const int trigPin = 9;  // Ultrasonic sensor trigger pin
const int echoPin = 10; // Ultrasonic sensor echo pin
const int servoPin = 3; // Servo motor pin
const int dispenseDuration = 2000; // Dispensing time in milliseconds

Servo dispenserServo;

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  dispenserServo.attach(servoPin);
}

void loop() {
  long duration, distance;

  // Trigger ultrasonic sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read echo pulse duration
  duration = pulseIn(echoPin, HIGH);

  // Calculate distance in centimeters
  distance = duration * 0.034 / 2;

  Serial.print("Distance: ");
  Serial.println(distance);

  // Check if hands are within a certain range
  if (distance < 10) {
    dispenseSanitizer();
  }

  delay(500); // Adjust the delay as needed
}

void dispenseSanitizer() {
  dispenserServo.write(90); // Activate the servo to dispense sanitizer
  delay(dispenseDuration);
  dispenserServo.write(0); // Move the servo back to the initial position
}
