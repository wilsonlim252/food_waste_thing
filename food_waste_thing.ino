#include "RichShieldTM1637.h"
#include "RichShieldPassiveBuzzer.h"

#define CLK 10
#define DIO 11

TM1637 disp(CLK, DIO);

#define potpin A0

#define buzzer 3
#define redled 4
#define yellowled 7
#define greenled 5

PassiveBuzzer buz(buzzer);

int thresholdv[] = {600, 800, 900, 1000, 1100, 1200};
/*
green < 600
blink > 600 <= 800
yellow > 800 <= 900
blink > 900 <= 1000
red  > 1000 <= 1100
blink > 1100 <= 1200
red > 1200 */

//set blinking interval)
const int wait = 100;

void nullall(void);

void setup() {
  Serial.begin(9600);

  pinMode(potpin, INPUT);

  pinMode(buzzer, OUTPUT);
  pinMode(redled, OUTPUT);
  pinMode(yellowled, OUTPUT);
  pinMode(greenled, OUTPUT);

  disp.init();
}

void loop() {
  int potv = analogRead(potpin)*2;

  //print my values dawgg
  Serial.println(potv);
  disp.display(potv);

  //Green
  if (potv <= thresholdv[0]) {
    nullall();
    digitalWrite(greenled, HIGH);
  }
  else if (potv > thresholdv[0] && potv <= thresholdv[1]) {
    nullall();
    digitalWrite(greenled, HIGH);
    delay(wait);
    digitalWrite(greenled, LOW);
    delay(wait);
  }

  //Yellow
  else if (potv > thresholdv[1] && potv <= thresholdv[2]) {
    nullall();
    digitalWrite(yellowled, HIGH);
  }
  else if (potv > thresholdv[2] && potv <= thresholdv[3]) {
    nullall();
    digitalWrite(yellowled, HIGH);
    delay(wait);
    digitalWrite(yellowled, LOW);
    delay(wait);
  }

  //Red
  else if (potv > thresholdv[3] && potv <= thresholdv[4]) {
    nullall();
    digitalWrite(redled, HIGH);
  }
  else if (potv >= thresholdv[4] && potv < thresholdv[5]) {
    nullall();
    digitalWrite(redled, HIGH);
    delay(wait);
    digitalWrite(redled, LOW);
    delay(wait);
  }

  //Buzzer
  else if (potv > thresholdv[5]) {
    nullall();
    buz.playTone(1000, 100);
    digitalWrite(buzzer, LOW);
    buz.playTone(500, 100);
    digitalWrite(buzzer, LOW);
  }
  else {
    nullall();
  }
}

void nullall() {
  digitalWrite(redled, LOW);
  digitalWrite(yellowled, LOW);
  digitalWrite(greenled, LOW);
  digitalWrite(buzzer, LOW);
}
