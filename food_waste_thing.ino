#include <TM1637Display.h>

void nullall(void);

//led function prototype
void greenpart(void);
void yellowpart(void);
void redpart(void);

//buzzer function
void buzzerpart(int,int);

const int CLK = 10;
const int DIO = 11;

TM1637Display display(CLK, DIO);

const int potpin = 0;

const int buzzer = 3;
const int redled = 4;
const int yellowled = 7;
const int greenled = 5;

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

void setup() {
  Serial.begin(9600);

  pinMode(potpin, INPUT);

  pinMode(buzzer, OUTPUT);
  pinMode(redled, OUTPUT);
  pinMode(yellowled, OUTPUT);
  pinMode(greenled, OUTPUT);

  display.setBrightness(7);
}

void loop() {
  int potv = analogRead(potpin)*2;

  //print my values dawgg
  Serial.println(potv);
  display.showNumberDec(potv);

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
  else if (potv > thresholdv[4] && potv <= thresholdv[5]) {
    nullall();
    digitalWrite(redled, HIGH);
    delay(wait);
    digitalWrite(redled, LOW);
    delay(wait);
  }

  //Buzzer
  else if (potv > thresholdv[5]) {
    nullall();
    tone(buzzer, 1000);
    delay(wait);
    tone(buzzer, 500);
    delay(wait);
  }
  else {
    nullall();
  }
}

void nullall() {
  digitalWrite(redled, LOW);
  digitalWrite(yellowled, LOW);
  digitalWrite(greenled, LOW);
  noTone(buzzer);
}
