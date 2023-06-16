const int ledPin = 13;
const int vibrPinL = 5;
const int vibrPinR = 6;
const int buttonPinL = 8;
const int buttonPinR = 7;
const int modePin = 2;

String side = "none";
int sideNr = 0;

float intensity;
const int max_intensity = 208;
const int min_intensity = 25;

long int time = 0;
long int vibrateTime = 0;
bool vibrating = false;
int step = 0;
int order = 1;
int count = 0;
int randomCount = 0;

bool running = false;
bool communication = true;
long int startTime = 0;

// Here set the times at which each turn is indicated in the video
// also set the amount of communication waves should happen,
// and the side to which the video turns
long int turn1 = 3000;
const String side1 = "left";
const int wave1 = 2;
long int turn2 = 18400;
const String side2 = "right";
const int wave2 = 2;
long int turn3 = 31300;
const String side3 = "left";
const int wave3 = 5;
long int turn4 = 47000;
const String side4 = "left";
const int wave4 = 1;
long int turn5 = 63000;
const String side5 = "left";
const int wave5 = 4;
long int turn6 = 78600;
const String side6 = "right";
const int wave6 = 1;
long int turn7 = 91000;
const String side7 = "both";
const int wave7 = 3;
long int turn8 = 105000;
const String side8 = "right";
const int wave8 = 1;
long int turn9 = 116200;
const String side9 = "left";
const int wave9 = 4;
long int turn10 = 130000;
const String side10 = "left";
const int wave10 = 3;

int stepsDone = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(vibrPinR, OUTPUT);
  pinMode(vibrPinL, OUTPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPinL, INPUT);
  pinMode(buttonPinR, INPUT);
  pinMode(modePin, INPUT);
}

/* Two (or maybe three) variations for haptic feedback are compared:
1. Received intention & Communication & Confirm turn
2. Received intention & Confirm turn
(3. Confirm turn)
*/

void loop() {
  // put your main code here, to run repeatedly:
  buttonState();
  if (running) {
    if (millis() >= startTime + turn1 && millis() < startTime + turn2) {
      if (stepsDone < 1) {
        side = side1;
        turn(wave1);
      }
    } else if (millis() >= startTime + turn2 && millis() < startTime + turn3) {
      if (stepsDone < 2) {
        side = side2;
        turn(wave2);
      }
    } else if (millis() >= startTime + turn3 && millis() < startTime + turn4) {
      if (stepsDone < 3) {
        side = side3;
        turn(wave3);
      }
    } else if (millis() >= startTime + turn4 && millis() < startTime + turn5) {
      if (stepsDone < 4) {
        side = side4;
        turn(wave4);
      }
    } else if (millis() >= startTime + turn5 && millis() < startTime + turn6) {
      if (stepsDone < 5) {
        side = side5;
        turn(wave5);
      }
    } else if (millis() >= startTime + turn6 && millis() < startTime + turn7) {
      if (stepsDone < 6) {
        side = side6;
        turn(wave6);
      }
    } else if (millis() >= startTime + turn7 && millis() < startTime + turn8) {
      if (stepsDone < 7) {
        side = side7;
        turn(wave7);
      }
    } else if (millis() >= startTime + turn8 && millis() < startTime + turn9) {
      if (stepsDone < 8) {
        side = side8;
        turn(wave8);
      }
    } else if (millis() >= startTime + turn9 && millis() < startTime + turn10) {
      if (stepsDone < 9) {
        side = side9;
        turn(wave9);
      }
    } else if (millis() >= startTime + turn10) {// && millis() < startTime + turn11) {
      if (stepsDone < 10) {
        side = side10;
        turn(wave10);
      }
    }
  } else {
    if (vibrating) setVibrate("both", 0);
    if (order != 1) order = 1;
    if (count != 0) count = 0;
    if (stepsDone != 0) stepsDone = 0;
    startTime = millis();
    // Serial.println("Not running now");
  }
  
}

void turn(int setWaitCount) { // ALWAYS set "setWaitCount" higher than 0!
  // this mode is the regular usage mode, to indicate a turn:
  switch (order) {
    case 1: // Confirmation of user action:
      Serial.print("Step 1 of turn ");
      Serial.println(stepsDone + 1);
      vibrateOnce(side, 70, 100);
      while(vibrating) vibrateOnce(side, 70, 100);
      delay(100);
      vibrateOnce(side, 70, 100);
      while(vibrating) vibrateOnce(side, 70, 100);
      delay(100);
      vibrateOnce(side, 70, 100);
      while(vibrating) vibrateOnce(side, 70, 100);
      order = 2;
      delay(500);
      time = millis();
      break;
    case 2: // Waiting during communication:
      Serial.print("Step 2 of turn ");
      Serial.println(stepsDone + 1);
      if (communication) {
        if (millis() >= time + 300) {               //THEN after 400ms do this:
          vibrateCurve("both", 15, 5, 350, 150);     //gradually go down,
          if(!vibrating) {                            //IF finished vibrating,
            time = millis();                            //set time so it will vibrate up again,
            count++;
            if (count >= setWaitCount) {                //and after a few times, move to next step
              order = 3;
              count = 0;
              delay(200);
            }
          }
        } else {
          vibrateCurve("both", 5, 15, 350, 0);     //FIRST gradually go up.
        }
      } else if (!communication) {
        while (count < setWaitCount) {              // make sure it takes the same amount of time,
          delay(850);                               // without actually vibrating.
          count++;
        }
        order = 3;
        count = 0;
        delay(200);
      }
      break;
    case 3: // Confirm safe to go:
      Serial.print("Step 3 of turn ");
      Serial.println(stepsDone + 1);
      vibrateOnce(side, 60, 200);
      while (vibrating) vibrateOnce(side, 60, 200);
      delay(100);
      vibrateOnce(side, 100, 500);
      while (vibrating) vibrateOnce(side, 100, 500);
      delay(50);
      order = 1;
      stepsDone++;
      delay(50);
      break;
  }
}


void buttonState() {
  int leftButton = digitalRead(buttonPinL);
  int rightButton = digitalRead(buttonPinR);
  if (leftButton == HIGH && rightButton == LOW) {
    communication = true;
    if (!running) {
      startTime = millis();
      time = millis();
      running = true;
    }
  } else if (leftButton == LOW && rightButton == HIGH) {
    communication = false;
    if (!running) {
      startTime = millis();
      time = millis();
      running = true;
    }
  } else running = false;
}

void vibrateOnce(String direction, int strength, int duration) {
  if (!vibrating) {
    vibrating = true;
    setVibrate(direction, strength);
    digitalWrite(ledPin, HIGH);
    vibrateTime = millis();
  }
  if (millis() >= vibrateTime + duration) {
    setVibrate(direction, 0);
    digitalWrite(ledPin, LOW);
    vibrating = false;
    step = 0;
  }
}

void vibrateCurve(String direction, int startStrength, int endStrength, int duration, int timeAfter) {
  float stepDuration = 10;
  float stepSize = (endStrength - startStrength) / (duration / stepDuration);
  float strength;
  if (millis() >= vibrateTime + stepDuration) {
    if (step < duration / stepDuration) vibrateTime = millis();
    strength = startStrength + stepSize * step;
    if (vibrating) setVibrate(direction, strength);
    if (step == 0) {
      vibrating = true;
      digitalWrite(ledPin, HIGH);
      step+=1;
    } else if (step >= duration / stepDuration) {
      // delay(stepDuration);
      vibrateOnce(direction, endStrength, timeAfter);
      // vibrating = false;
      // setVibrate(direction, 0);
      // digitalWrite(ledPin, LOW);
      // step = 0;
    } else step+=1;
  }
}

void setVibrate(String direction, float strength) {
  intensity = map(strength, 1, 100, min_intensity, max_intensity);
  if (intensity > max_intensity) intensity = max_intensity;
  else if (strength == 0) intensity = 0;

  if (direction == "right") {
    analogWrite(vibrPinR, intensity);
  } else if (direction == "left") {
    analogWrite(vibrPinL, intensity);
  } else if (direction == "both") {
    analogWrite(vibrPinR, intensity);
    analogWrite(vibrPinL, intensity);
  }
}