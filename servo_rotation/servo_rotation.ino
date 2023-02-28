#include <Servo.h>

Servo servo;
int pos = 0;
int increment = 1;

void setup() {
  servo.attach(5); // attach the servo to pin 5
}

void loop() {
  // move the servo back and forth
  for (pos = 0; pos <= 180; pos += increment) {
    servo.write(pos);
    delay(15);
  }
  for (pos = 180; pos >= 0; pos -= increment) {
    servo.write(pos);
    delay(15);
  }

  delay(5000); // wait 5 seconds before repeating
}
