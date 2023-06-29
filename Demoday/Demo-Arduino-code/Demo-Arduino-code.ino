/* June 2023
 * Code by Jochem Verstegen for Final Bachelor Project
 * Eindhoven University of Technology, faculty of Industrial Design
 *
 * This code can be used to demonstrate the haptic feedback.
 * The left button activates the left vibration motor, the right button the right motor.
 * Technically, it is possible for both buttons to trigger both motors.
 * For the electronics needed, please see the "Electronics.png" file in the demoday folder.
 * Note the presence of a switch connected to pin 2.
 * This switch can toggle between the regular mode and navigation mode.
 * When this switch is not included, it will default to the regular mode.
 *
 * The regular mode contains the feedback when indicating a turn (in this case pressing a button).
 * The navigation mode indicates upcoming turns when following turn-by-turn nagivation.
 */

const int ledPin = 13;
const int vibrPinL = 6;
const int vibrPinR = 5;
const int buttonPinL = 7;
const int buttonPinR = 8;
const int modePin = 2;

String side = "none";
int sideNr = 0;

float intensity;
const int max_intensity = 208; // set the max PWM rate for the max voltage. Max 4V = 0.8 * 255 = 204.
const int min_intensity = 25; // set the min PWM rate at which the motors still vibrate. Trial and error.

long int time = 0;
long int vibrateTime = 0;
bool vibrating = false;
int step = 0;
int order = 0;
int count = 0;
int randomCount = 0;

void setup() {
  pinMode(vibrPinR, OUTPUT);
  pinMode(vibrPinL, OUTPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPinL, INPUT);
  pinMode(buttonPinR, INPUT);
  pinMode(modePin, INPUT);
}

/* Two "modes" needed: Free turning (feedback) and navigation
### Free turning:
User can determine when to turn. Before the turn, they indicate their intention.
This will be communicated to the AVs around the user, and feedback will be given
to the user through vibrations. Blinkers can activate too, but not in this prototype.
________________________________

- Before turn, user pulls handle
- Handle vibrates a few times as comfirmation (2 quick short vibrations?)
- (Optional: Vibrate to indicate safety to take turn)
  - Waiting: Keep vibrating both weak
  - Safe to go: Vibrate side stronger

### Navigation:
User can set a destination, or a full route. Each turn will be communicated to the
user using vibrations. User can confirm a turn, which will make the vibrations less
frequent / intense.
________________________________

- Long before turn, indicate turn with a couple short vibrations
- After, indicate using less vibrations, but longer and stronger
- Right before turning, confirm again with 2 strong vibrations (long - short)
- When comfirmed by user, perhaps only do final alert (still confirm intention)
*/

void loop() {
  if (digitalRead(modePin) == HIGH) navigationMode();
  else turningMode();
}

void turningMode() {
  // this mode is the regular usage mode, to indicate a turn:
  switch (order) {
    case 0: // Checking for user action:
      if (buttonState() != "none") {          //when handle is slided out:
        side = buttonState();                   //register which side it was,
        order = 1;                              //go to next step,
        time = millis();                        //and already start timer.
      }
      break;
    case 1: // Confirmation of user action:
      if (millis() >= time + 400) {           //THEN after 500ms do this:
        vibrateOnce(side, 75, 300);             //similar short vibration,
        if (!vibrating) {
          order = 2;                            //and go to next step.
          time = millis();
          randomCount = random(4,8);
          delay(500);
        }
      } else {                                //FIRST do this:
        vibrateOnce(side, 75, 300);             //short vibration.
        if (!vibrating) delay(100);
      }
      break;
    case 2: // Waiting during communication:
      if (millis() >= time + 400) {               //THEN after 400ms do this:
        vibrateCurve("both", 15, 1, 400, 400);     //gradually go down,
        if(!vibrating) {                            //IF finished vibrating,
          time = millis();                            //set time so it will vibrate up again,
          count++;
          if (count >= randomCount) {                 //and after a few times, move to next step
            order = 3;
            count = 0;
            delay(200);
          }
        }
      } else {
        vibrateCurve("both", 1, 15, 400, 0);     //FIRST gradually go up.
      }
      break;
    case 3: // Confirm safe to go:
      vibrateOnce(side, 70, 200);
      while (vibrating) vibrateOnce(side, 60, 200);
      delay(100);
      vibrateOnce(side, 100, 600);
      while (vibrating) vibrateOnce(side, 100, 500);
      order = 0;
      break;
  }
}

void navigationMode() {
  // this mode will navigate the user around, using haptic feedback:
  switch (order) {
    case 0: // Wait random amount until next turn:
      delay(random(3000,5000));
      sideNr = random(1,3);
      Serial.println(sideNr);
      if (sideNr == 1) side = "left";
      else side = "right";
      order = 1;
      break;
    case 1: // First alert of upcoming turn:
      for (int i = 0; i < 4; i++) {
        vibrateOnce(side, 30, 100);
        while(vibrating) vibrateOnce(side, 30, 100);
        delay(100);
      }
      order = 2;
      delay(3000);
      break;
    case 2: // Second alert of upcoming turn:
      for (int i = 0; i < 3; i++) {
        vibrateOnce(side, 50, 200);
        while(vibrating) vibrateOnce(side, 50, 200);
        delay(200);
      }
      order = 3;
      delay(2000);
      break;
    case 3: // Confirm safe to go:
      vibrateCurve(side, 1, 80, 400, 200);
      while (vibrating) vibrateCurve(side, 1, 80, 400, 200);
      delay(200);
      vibrateOnce(side, 100, 200);
      while (vibrating) vibrateOnce(side, 100, 200);
      order = 0;
      break;
  }
}

String buttonState() {
  String result;
  int leftButton = digitalRead(buttonPinL);
  int rightButton = digitalRead(buttonPinR);
  if (leftButton == HIGH && rightButton == LOW) result = "left";
  else if (leftButton == LOW && rightButton == HIGH) result = "right";
  else if (leftButton == HIGH && rightButton == HIGH) result = "both";
  else result = "none";
  return result;
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
      vibrateOnce(direction, endStrength, timeAfter);
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
