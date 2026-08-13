  #include "RichShieldTM1637.h"
  #include "RichShieldPassiveBuzzer.h"

  #define CLK 10
  #define DIO 11

  TM1637 disp(CLK, DIO);

  #define potpin A0
  #define LDRpin A2
  #define buzzer 3
  PassiveBuzzer buz(buzzer);

  const int ledpin[] = {5, 7, 4}; //green, yellow, red; dong xuan
  const int buzzerv[] = {1000, 1250, 1500}; //luke chua
  const int thresholdv[] = {600, 800, 900, 1000, 1100, 1200}; //values for the pot to determind the level of waste and approprate action

  /*
  green < 600
  blink > 600 <= 800
  yellow > 800 <= 900
  blink > 900 <= 1000
  red  > 1000 <= 1100
  blink > 1100 <= 1200
  red > 1200 */

  //set blinking interval)
  const int wait = 80;

  
  void nullall(void); //by Wilson Lim: P2603278
  void warning(int potv); //by wilson lim:P2603278
  void alarm(void); //by Luke Chua
  void blink(char colour); //by dong xuan

  void setup() {
    Serial.begin(9600);

    pinMode(potpin, INPUT);
    pinMode(LDRpin, INPUT);

    pinMode(buzzer, OUTPUT);
    for (int i=0; i<3; i++) {
      pinMode(ledpin[i], OUTPUT);
    }
    

    disp.init();
  }

  void loop() {
    int potv = analogRead(potpin)*2;
    int LDR = analogRead(LDRpin);
    //print my values dawgg
    Serial.print(potv);
    Serial.print(" : ");
    Serial.println(LDR);
    disp.display(potv);

    if (LDR > 800) {
      warning(potv);
    }
    else {
      nullall();
    }
  }

  void nullall() {
    for (int i = 0; i<3; i++) {
      digitalWrite(ledpin[i], LOW);
    }
    digitalWrite(buzzer, LOW);
  }
  void warning(int potv) { //by wilson lim

    //Green
    if (potv <= thresholdv[0]) {
      nullall();
      digitalWrite(ledpin[0], HIGH);
    }
    else if (potv > thresholdv[0] && potv <= thresholdv[1]) {
      blink('g');
    }

    //Yellow
    else if (potv > thresholdv[1] && potv <= thresholdv[2]) {
      nullall();
      digitalWrite(ledpin[1], HIGH);
    }
    else if (potv > thresholdv[2] && potv <= thresholdv[3]) {
      blink('y');
    }

    //Red
    else if (potv > thresholdv[3] && potv <= thresholdv[4]) {
      nullall();
      digitalWrite(ledpin[2], HIGH);
    }
    else if (potv > thresholdv[4] && potv < thresholdv[5]) {
      blink('r');
    }

    //Buzzer
    else if (potv >= thresholdv[5]) {
      nullall();
      alarm();
    }
    else {
      nullall();
    }
  }


  void blink(char colour) { //by dong xuan
    nullall();
    switch (colour) {
      case 'g':
        digitalWrite(ledpin[0], HIGH);
        delay(wait);
        digitalWrite(ledpin[0], LOW);
        delay(wait);
        break;
      case 'y':
        digitalWrite(ledpin[1], HIGH);
        delay(wait);
        digitalWrite(ledpin[1], LOW);
        delay(wait);
        break;
      case 'r':
        digitalWrite(ledpin[2], HIGH);
        delay(wait);
        digitalWrite(ledpin[2], LOW);
        delay(wait);
        break;

    }
  }

  void alarm() { //by luke chua
    int buzzarray_size = sizeof(buzzerv) / sizeof(buzzerv[0]);
    for (int i = 0; i<buzzarray_size; i++) {
      buz.playTone(buzzerv[i], wait);
    }
  }
