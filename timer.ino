const int A = 4;
const int B = 5;
const int C = 6;
const int D = 7;
const int E = 8;
const int F = 9;
const int G = 10;

const int secondsUnitDigit = 13, secondsTensDigit = 3, minutesUnitDigit = 2;
const int buzzer = A0;

int second, secondStore = 0;
int minute, minuteStore = 0;
int tenth = 9;

unsigned long lastResetButton, lastPlayButton, lastPlusButton;
int resetButtonState, playButtonState, plusButtonState;
int currentResetButtonState, currentPlayButtonState, currentPlusButtonState;

const int playButtonPin = 12;
const int plusButtonPin = 11;
const int resetButtonPin = 1;

const int displayDelay = 6;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;

bool run = false;
unsigned long timer = 0;


void setup()
{
  DDRD = 0B11111100;
  DDRB = 0B00100111;

  pinMode(1, INPUT_PULLUP);
  pinMode(11, INPUT_PULLUP);
  pinMode(12, INPUT_PULLUP);
  pinMode(buzzer, OUTPUT);
}

void loop()
{
  resetButtonState = digitalRead(resetButtonPin);
  playButtonState = digitalRead(playButtonPin);
  plusButtonState = digitalRead(plusButtonPin);

  tickClock();
  updateDisplay();
  checkReset();
  checkStart();
  checkPlus();
}


void checkPlus() {
  if (plusButtonState != currentPlusButtonState) {   //Check if the button state has changed
    if (plusButtonState == LOW && (millis() - lastPlusButton) > 100 || lastPlusButton == HIGH) {
      lastPlusButton = millis();
      if (second >= 50 && minute == 9) {
        second++;
      } else {
        second += 10;
      }

      if (second > 59) {
        second = 0;
        minute ++;
        if (minute > 9)
          minute = 0;
      }
    }
  }
  currentPlusButtonState = plusButtonState;
}

void checkStart() {
  if (playButtonState != currentPlayButtonState) {   //Check if the button state has changed
    if (playButtonState == LOW && (millis() - lastPlayButton) > 100 || lastPlayButton == HIGH) {
      lastPlayButton = millis();
      //minuteStore = minute;
      //secondStore = second;
      run = !run;
    }
  }
  currentPlayButtonState = playButtonState;
}

void checkReset() {
  if (resetButtonState != currentResetButtonState) {   //Check if the button state has changed
    if (resetButtonState == LOW && (millis() - lastResetButton) > 100 || lastResetButton == HIGH) {
      lastResetButton = millis();
      minute = 0;
      second = 0;
      run = false;
    }
  }
  currentResetButtonState = resetButtonState;
}

void tick() {
  if (run == true) {
    if (tenth == 0) {
      tenth = 9;
      if (second == 0) {
        second = 59;
        minute--;
      } else {
        second--;
      }
    } else {
      tenth--;
    }
    if (minute == 0 && second == 0) {
      while (1) {
        blink();
        break;
      }
      run = !run;
    }
  }
}

void tickClock() {
  if ((timer - millis() / 100) >= 100 || timer == 0) {
    tick();
    timer = millis() / 100;
  }
}

void updateDisplay() {
  int tens = second / 10;
  int seconds = second % 10;

  displayMinutesUnitDigit(minute);
  delay(displayDelay);
  displaySecondsTensDigit(tens);
  delay(displayDelay);
  displaySecondsUnitDigit(seconds);
  delay(displayDelay);
}

void blink() {
  setNumberFromInt(0);
  for (int i = 0; i < 5; i++) {
    digitalWrite(minutesUnitDigit, LOW);
    digitalWrite(secondsTensDigit, LOW);
    digitalWrite(secondsUnitDigit, LOW);
    analogWrite(buzzer, 0);
    delay(125);
    digitalWrite(minutesUnitDigit, HIGH);
    digitalWrite(secondsTensDigit, HIGH);
    digitalWrite(secondsUnitDigit, HIGH);
    analogWrite(buzzer, 1024);
    delay(125);
  }

  analogWrite(buzzer, 0);
}

void displayMinutesUnitDigit(int minutesUnit)
{
  setNumberFromInt(minutesUnit);
  digitalWrite(minutesUnitDigit, HIGH);
  digitalWrite(secondsTensDigit, LOW);
  digitalWrite(secondsUnitDigit, LOW);
}

void displaySecondsTensDigit(int secondsTens)
{
  setNumberFromInt(secondsTens);
  digitalWrite(minutesUnitDigit, LOW);
  digitalWrite(secondsTensDigit, HIGH);
  digitalWrite(secondsUnitDigit, LOW);
}

void displaySecondsUnitDigit(int secondsUnit)
{
  setNumberFromInt(secondsUnit);
  digitalWrite(minutesUnitDigit, LOW);
  digitalWrite(secondsTensDigit, LOW);
  digitalWrite(secondsUnitDigit, HIGH);
}

void setNumberFromInt (int number) {
  switch (number)
  {
    case 0:
      digitalWrite(A, LOW);
      digitalWrite(B, LOW);
      digitalWrite(C, LOW);
      digitalWrite(D, LOW);
      digitalWrite(E, LOW);
      digitalWrite(F, LOW);
      digitalWrite(G, HIGH);
      break;
    case 1:

      digitalWrite(A, HIGH);
      digitalWrite(B, LOW);
      digitalWrite(C, LOW);
      digitalWrite(D, HIGH);
      digitalWrite(E, HIGH);
      digitalWrite(F, HIGH);
      digitalWrite(G, HIGH);
      break;

    case 2:
      digitalWrite(A, LOW);
      digitalWrite(B, LOW);
      digitalWrite(C, HIGH);
      digitalWrite(D, LOW);
      digitalWrite(E, LOW);
      digitalWrite(F, HIGH);
      digitalWrite(G, LOW);
      break;

    case 3:
      digitalWrite(A, LOW);
      digitalWrite(B, LOW);
      digitalWrite(C, LOW);
      digitalWrite(D, LOW);
      digitalWrite(E, HIGH);
      digitalWrite(F, HIGH);
      digitalWrite(G, LOW);
      break;

    case 4:
      digitalWrite(A, HIGH);
      digitalWrite(B, LOW);
      digitalWrite(C, LOW);
      digitalWrite(D, HIGH);
      digitalWrite(E, HIGH);
      digitalWrite(F, LOW);
      digitalWrite(G, LOW);
      break;

    case 5:
      digitalWrite(A, LOW);
      digitalWrite(B, HIGH);
      digitalWrite(C, LOW);
      digitalWrite(D, LOW);
      digitalWrite(E, HIGH);
      digitalWrite(F, LOW);
      digitalWrite(G, LOW);
      break;

    case 6:
      digitalWrite(A, LOW);
      digitalWrite(B, HIGH);
      digitalWrite(C, LOW);
      digitalWrite(D, LOW);
      digitalWrite(E, LOW);
      digitalWrite(F, LOW);
      digitalWrite(G, LOW);
      break;

    case 7:
      digitalWrite(A, LOW);
      digitalWrite(B, LOW);
      digitalWrite(C, LOW);
      digitalWrite(D, HIGH);
      digitalWrite(E, HIGH);
      digitalWrite(F, HIGH);
      digitalWrite(G, HIGH);
      break;

    case 8:
      digitalWrite(A, LOW);
      digitalWrite(B, LOW);
      digitalWrite(C, LOW);
      digitalWrite(D, LOW);
      digitalWrite(E, LOW);
      digitalWrite(F, LOW);
      digitalWrite(G, LOW);
      break;

    case 9:
      digitalWrite(A, LOW);
      digitalWrite(B, LOW);
      digitalWrite(C, LOW);
      digitalWrite(D, LOW);
      digitalWrite(E, HIGH);
      digitalWrite(F, LOW);
      digitalWrite(G, LOW);
      break;
  }
}
