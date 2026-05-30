/*
====================================================
 AUTONOMOUS SEED DISPENSER ROVER - FINAL DEBUGGED CODE
====================================================
*/

#include <Servo.h>

#define IN1 2
#define IN2 3
#define IN3 4
#define IN4 5

#define TRIG_PIN 9
#define ECHO_PIN 10

#define SERVO_PIN 11

Servo seedServo;

long duration;
int distance;

unsigned long lastSeedTime = 0;

void setup()
{
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  seedServo.attach(SERVO_PIN);
  seedServo.write(0);

  Serial.begin(9600);

  delay(1000);
}

void loop()
{
  distance = getDistance();

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  if (distance > 0 && distance < 20)
  {
    stopMotors();
    delay(300);

    moveBackward();
    delay(800);

    stopMotors();
    delay(300);

    turnRight();
    delay(700);

    moveForward();
    delay(500);
  }
  else
  {
    moveForward();

    if (millis() - lastSeedTime >= 3000)
    {
      dispenseSeed();
      lastSeedTime = millis();
    }
  }
}

int getDistance()
{
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);

  digitalWrite(TRIG_PIN, LOW);

  duration = pulseIn(ECHO_PIN, HIGH, 30000);

  if (duration == 0)
  {
    return 999;
  }

  int dist = duration * 0.034 / 2;

  return dist;
}

void moveForward()
{
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void moveBackward()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void turnRight()
{
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void stopMotors()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void dispenseSeed()
{
  seedServo.write(60);
  delay(300);

  seedServo.write(0);
  delay(300);
}
