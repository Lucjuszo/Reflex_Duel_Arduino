#include <LedControl.h>

LedControl lc = LedControl(12, 10, 11, 1);  // data, clk, CS, number of displays

const int btn1 = 2;
const int btn2 = 3;
const int btnStart = 9;
const int ledStart = 4;
const int p1_led1 = 5;
const int p1_led2 = 6;
const int p2_led1 = 7;
const int p2_led2 = 8;

int score1 = 0;
int score2 = 0;

bool myDelay(unsigned long ms) {
  unsigned long start = millis();
  while (millis() - start < ms) {
    if (digitalRead(btnStart) == LOW) return true;
    delay(1);
  }
  return false;
}

void showNumber(unsigned long num, int startDigit) {
  if (num > 9999) num = 9999;
  for (int i = 0; i < 4; i++) {
    if (num == 0 && i > 0) {
      lc.setChar(0, startDigit + i, ' ', false);
    } else {
      lc.setDigit(0, startDigit + i, num % 10, false);
      num /= 10;
    }
  }
}

void updateLeds() {
  digitalWrite(p1_led1, score1 >= 1);
  digitalWrite(p1_led2, score1 >= 2);
  digitalWrite(p2_led1, score2 >= 1);
  digitalWrite(p2_led2, score2 >= 2);
}

void setup() {
  // btn default high
  pinMode(btn1, INPUT_PULLUP);
  pinMode(btn2, INPUT_PULLUP);
  pinMode(btnStart, INPUT_PULLUP);
  pinMode(ledStart, OUTPUT);
  pinMode(p1_led1, OUTPUT);
  pinMode(p1_led2, OUTPUT);
  pinMode(p2_led1, OUTPUT);
  pinMode(p2_led2, OUTPUT);

  lc.shutdown(0, false);  // wake up display
  lc.setIntensity(0, 8);
  lc.clearDisplay(0);
  
  randomSeed(analogRead(0));
}

void loop() {
  while (digitalRead(btnStart) == HIGH) {
    delay(10);
  }
  while (digitalRead(btnStart) == LOW) {
    delay(10);
  }

doReset:
  score1 = 0;
  score2 = 0;
  updateLeds();
  lc.clearDisplay(0);
  digitalWrite(ledStart, LOW);

  lc.setRow(0, 7, 0x05);  //r
  lc.setRow(0, 6, 0x4F);  //E
  lc.setRow(0, 5, 0x5B);  //S
  lc.setRow(0, 4, 0x4F);  //E
  lc.setRow(0, 3, 0x0F);  //t

  while (digitalRead(btnStart) == LOW) {
    delay(10);
  }
  while (digitalRead(btnStart) == HIGH) {
    delay(10);
  }
  while (digitalRead(btnStart) == LOW) {
    delay(10);
  }

  while (score1 < 2 && score2 < 2) {
    lc.clearDisplay(0);
    lc.setRow(0, 7, 0x5B);  //StArt
    lc.setRow(0, 6, 0x0F);
    lc.setRow(0, 5, 0x77);
    lc.setRow(0, 4, 0x05);
    lc.setRow(0, 3, 0x0F);

    if (myDelay(2000)) goto doReset;
    lc.clearDisplay(0);

    for (int i = 3; i >= 1; i--) {
      lc.setDigit(0, 7, i, false);
      if (myDelay(1000)) goto doReset;
    }
    lc.clearDisplay(0);

    unsigned long waitTime = random(2000, 5000);
    unsigned long startWait = millis();
    bool falseStart = false;

    while (millis() - startWait < waitTime) {
      if (digitalRead(btn1) == LOW) {
        score2++;
        falseStart = true;
        break;
      }
      if (digitalRead(btn2) == LOW) {
        score1++;
        falseStart = true;
        break;
      }
      if (digitalRead(btnStart) == LOW) goto doReset;
    }

    if (falseStart) {
      updateLeds();
      if (myDelay(2000)) goto doReset;
      while (digitalRead(btn1) == LOW || digitalRead(btn2) == LOW) {
        if (digitalRead(btnStart) == LOW) goto doReset;
        delay(10);
      }
      continue;
    }

    digitalWrite(ledStart, HIGH);
    unsigned long startT = millis();
    unsigned long t1 = 0;
    unsigned long t2 = 0;
    while (t1 == 0 || t2 == 0) {
      if (digitalRead(btn1) == LOW && t1 == 0) {
        t1 = millis() - startT;
      }
      if (digitalRead(btn2) == LOW && t2 == 0) {
        t2 = millis() - startT;
      }
      if (digitalRead(btnStart) == LOW) {
        digitalWrite(ledStart, LOW);
        goto doReset;
      }
    }

    digitalWrite(ledStart, LOW);
    if (t1 < t2) {
      score1++;
    } else if (t2 < t1) {
      score2++;
    }

    showNumber(t1, 4);
    showNumber(t2, 0);
    updateLeds();

    if (myDelay(3000)) goto doReset;
    
    while (digitalRead(btn1) == LOW || digitalRead(btn2) == LOW) {
      if (digitalRead(btnStart) == LOW) goto doReset;
      delay(10);
    }
  }

  lc.clearDisplay(0);
  lc.setRow(0, 7, 0x67);  //P
  lc.setDigit(0, 6, (score1 >= 2) ? 1 : 2, false);
  while (digitalRead(btnStart) == HIGH) {
    delay(10);
  }
  while (digitalRead(btnStart) == LOW) {
    delay(10);
  }
  goto doReset;
}