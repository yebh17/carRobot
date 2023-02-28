#include <Servo.h>

// DC Gear Motors for wheels
#define LEFT_MOTOR_FORWARD_PIN 9
#define LEFT_MOTOR_BACKWARD_PIN 6
#define RIGHT_MOTOR_FORWARD_PIN 11
#define RIGHT_MOTOR_BACKWARD_PIN 10

// SG90 9G Mini Servo
#define SERVO_PIN 5
Servo servo;

// HC-SR04 Ultrasonic Sensor
#define SONAR_TRIG_PIN A1
#define SONAR_ECHO_PIN A0
#define MAX_DISTANCE 40 // in cm

void setup() {
  pinMode(LEFT_MOTOR_FORWARD_PIN, OUTPUT);
  pinMode(LEFT_MOTOR_BACKWARD_PIN, OUTPUT);
  pinMode(RIGHT_MOTOR_FORWARD_PIN, OUTPUT);
  pinMode(RIGHT_MOTOR_BACKWARD_PIN, OUTPUT);

  servo.attach(SERVO_PIN);

  pinMode(SONAR_TRIG_PIN, OUTPUT);
  pinMode(SONAR_ECHO_PIN, INPUT);
  
  Serial.begin(9600);
}

void loop() {
  long duration, distance;
  
  // Move the car forward at a speed of 50% of maximum
  analogWrite(LEFT_MOTOR_FORWARD_PIN, 127);
  analogWrite(RIGHT_MOTOR_FORWARD_PIN, 127);
  digitalWrite(LEFT_MOTOR_BACKWARD_PIN, LOW);
  digitalWrite(RIGHT_MOTOR_BACKWARD_PIN, LOW);

  // Scan for obstacles
  for(int i = 0; i < 180; i += 60) {
    servo.write(i); // set servo to current angle
    delay(250); // wait for servo to move
    digitalWrite(SONAR_TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(SONAR_TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(SONAR_TRIG_PIN, LOW);
    duration = pulseIn(SONAR_ECHO_PIN, HIGH);
    distance = duration / 58.2;
  }

  if (distance <= MAX_DISTANCE) {
    // Stop the car
    analogWrite(LEFT_MOTOR_FORWARD_PIN, 0);
    analogWrite(RIGHT_MOTOR_FORWARD_PIN, 0);
    digitalWrite(LEFT_MOTOR_BACKWARD_PIN, LOW);
    digitalWrite(RIGHT_MOTOR_BACKWARD_PIN, LOW);
    
    // Back up and turn
    digitalWrite(LEFT_MOTOR_FORWARD_PIN, LOW);
    digitalWrite(RIGHT_MOTOR_FORWARD_PIN, LOW);
    analogWrite(LEFT_MOTOR_BACKWARD_PIN, 127);
    analogWrite(RIGHT_MOTOR_BACKWARD_PIN, 127);
    delay(1000);
    digitalWrite(LEFT_MOTOR_FORWARD_PIN, LOW);
    analogWrite(RIGHT_MOTOR_FORWARD_PIN, 127);
    digitalWrite(LEFT_MOTOR_BACKWARD_PIN, 127);
    digitalWrite(RIGHT_MOTOR_BACKWARD_PIN, LOW);
    delay(1000);
    analogWrite(LEFT_MOTOR_FORWARD_PIN, 0);
    analogWrite(RIGHT_MOTOR_FORWARD_PIN, 0);
    digitalWrite(LEFT_MOTOR_BACKWARD_PIN, LOW);
    digitalWrite(RIGHT_MOTOR_BACKWARD_PIN, LOW);
  }
  
  delay(100);
}