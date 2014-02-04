// Adafruit Motor shield library
// copyright Adafruit Industries LLC, 2009
// this code is public domain, enjoy!

#include <AFMotor.h>


const int CORKY = 2;
const int WHEELBERT = 1;

const int MIN_SPEED = 50;
const int MAX_SPEED = 255;
const int INIT_SPEED = 75;
const int DELAY = 100;

const int SPEED_STEP = 50;

int currentSpeed = 0;

AF_DCMotor winder(CORKY);
AF_DCMotor wheeler(WHEELBERT);

void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Motor test!");

  // turn on motor
  winder.setSpeed(INIT_SPEED);
  currentSpeed = INIT_SPEED;
  Serial.println(currentSpeed);
  winder.run(RELEASE);
}

void forwardCycle(AF_DCMotor motor) {
  uint8_t i;  
  Serial.println("FORWARD - ACCELERATE");  
  motor.run(FORWARD);
  for (i=MIN_SPEED; i<MAX_SPEED; i++) {
    motor.setSpeed(i);  
    currentSpeed = i;
    Serial.println(currentSpeed);
    delay(SPEED_STEP);
 }

  Serial.println("FORWARD - DECCELERATE"); 
  for (i=MAX_SPEED; i!=MIN_SPEED; i--) {
    motor.setSpeed(i);  
    currentSpeed = i;
    Serial.println(currentSpeed);
    delay(SPEED_STEP);
 }
  

}

void backwardCycle(AF_DCMotor motor) {
  uint8_t i;

  Serial.println("BACKWARD - ACCELERATE");

  winder.run(BACKWARD);
  for (i=MIN_SPEED; i<MAX_SPEED; i++) {
    winder.setSpeed(i);  
    currentSpeed = i;
    Serial.println(currentSpeed);
    delay(SPEED_STEP);
 }

 Serial.println("BACKWARD - DECCELERATE");
 
  for (i=MAX_SPEED; i!=MIN_SPEED; i--) {
    winder.setSpeed(i);  
    currentSpeed = i;
    Serial.println(currentSpeed);
    delay(SPEED_STEP);
 }

}


void loop() {
  uint8_t i;
  forwardCycle(winder);
  forwardCycle(wheeler);
  backwardCycle(winder);
  backwardCycle(wheeler);
  Serial.println("RELEASE");
  winder.run(RELEASE);
  wheeler.run(RELEASE);
  delay(DELAY);
}
