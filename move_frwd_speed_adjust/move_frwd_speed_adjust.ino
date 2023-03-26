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
#define MAX_DISTANCE 30 // in cm

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

#define SPEED 512

void right_forward()
{
  analogWrite(RIGHT_MOTOR_FORWARD_PIN, 0);
  analogWrite(RIGHT_MOTOR_BACKWARD_PIN, 255);
}

void right_backward()
{
  analogWrite(RIGHT_MOTOR_FORWARD_PIN, 255);
  analogWrite(RIGHT_MOTOR_BACKWARD_PIN, 0);
}

void right_stop()
{
  analogWrite(RIGHT_MOTOR_FORWARD_PIN, 0);
  analogWrite(RIGHT_MOTOR_BACKWARD_PIN, 0);
}

void left_forward()
{
  analogWrite(LEFT_MOTOR_FORWARD_PIN, 255);
  analogWrite(LEFT_MOTOR_BACKWARD_PIN, 0);
}

void left_backward()
{
  analogWrite(LEFT_MOTOR_FORWARD_PIN, 0);
  analogWrite(LEFT_MOTOR_BACKWARD_PIN, 255);
}

void left_stop()
{
  analogWrite(LEFT_MOTOR_FORWARD_PIN, 0);
  analogWrite(LEFT_MOTOR_BACKWARD_PIN, 0);
}

void loop() {
  long duration, distance;
  right_forward();
  left_forward();
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
  if (0)
  {
  // Move the car forward at a speed of almost 80% of maximum
  analogWrite(LEFT_MOTOR_FORWARD_PIN, 255);
  analogWrite(RIGHT_MOTOR_FORWARD_PIN, 255);
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
    
    // Back up and turn at almost 80% of maximum speed
    //digitalWrite(LEFT_MOTOR_FORWARD_PIN, HIGH);
    //digitalWrite(RIGHT_MOTOR_FORWARD_PIN, HIGH);
    analogWrite(LEFT_MOTOR_BACKWARD_PIN, 255);
    analogWrite(RIGHT_MOTOR_BACKWARD_PIN, 255);
    delay(1000);
    analogWrite(LEFT_MOTOR_BACKWARD_PIN, 0); //digitalWrite    
    //analogWrite(RIGHT_MOTOR_FORWARD_PIN, 255);
    //digitalWrite(LEFT_MOTOR_FORWARD_PIN, LOW);
    //digitalWrite(RIGHT_MOTOR_BACKWARD_PIN, LOW);
    delay(1000);
    analogWrite(LEFT_MOTOR_FORWARD_PIN, 0);
    analogWrite(RIGHT_MOTOR_FORWARD_PIN, 0);
    digitalWrite(LEFT_MOTOR_BACKWARD_PIN, LOW);
    digitalWrite(RIGHT_MOTOR_BACKWARD_PIN, LOW);
  }
  }
  
  //delay(100);
}