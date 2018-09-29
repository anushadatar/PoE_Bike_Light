// Anusha Datar
// Principles of Engineering Lab 1 : Bike Light

// Number of possible modes. While the cases and
// incremements are 0 indexed, this should just be
// the counting number of cases.
int numberOfPossibleCases = 5;

// Pin Definitons.
// LED Pins.
int redPin = 9;
int yellowPin = 10;
int greenPin = 11;
// Input values from distance sensor.
int distPin = A0;
// Counter for modes based on input from switch.
int switchCount = 0;


void setup() {
  Serial.begin(9600);
  // Set up pins
  pinMode(switchPin, INPUT);
  pinMode(redPin, OUTPUT);
  pinMode(yellowPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(switchPin, INPUT);
  pinMode(distPin, INPUT);
  // Kick off interrupts to make it easier to switch modes.
  interrupts();
  // Interrupt on switch on pin two.
  attachInterrupt(digitalPinToInterrupt(2), loopSwitch, HIGH);
  
}

void loop() {
  /*
   * Allows for mode selection based on a simple counter and 
   * then kicks off relevant functions. 
   */
  switch (switchCount) {
    case 0:
      allHigh();
      break;
    case 1:
      allLow();
      break;
    case 2:
      distanceSensorResponse();
      break;
    case 3:
      distanceSensorOppositeResponse();
      break;
    case 4:
      blinking();
      break;
  }
 }

void allHigh() {
  /*
   * Mode 0 :Sets all of the LEDs to high.
   */
  Serial.print("Mode 0: All LEDs High. \n");
  digitalWrite(redPin, HIGH);
  digitalWrite(yellowPin, HIGH);
  digitalWrite(greenPin, HIGH);
}

void allLow() {
  /*
   * Mode 1 : Sets all of the LEDs to low.
   */
  Serial.print("Mode 1: All LEDs Low. \n");
  digitalWrite(redPin, LOW);
  digitalWrite(yellowPin, LOW);
  digitalWrite(greenPin, LOW);
}

void distanceSensorResponse() {
  /*
   * Mode 2 : Adjusts brightness and color (from green for farther
   * and red for closer) of LEDs based on distance sensor reading.
   */
  Serial.print("Mode 2: Lights incremement and become brighter ");
  Serial.print("based on distance sensor results. \n");
  allLow();
  int distanceRead = analogRead(distPin);
  // Tolerances are based on empirical testing.
  if (distanceRead > 150) {
    if (distanceRead > 255) {
      distanceRead = 255;
    }
    analogWrite(greenPin, distanceRead); 
  }
  else if (distanceRead > 75) {
    analogWrite(yellowPin, distanceRead);
  }
  else {
    analogWrite(redPin, distanceRead);
  }
}

void distanceSensorOppositeResponse() {
  /*
   * Mode 3 : Adjusts brightness and color (from green for farther
   * and red for closer) of LEDs based on distance sensor reading.
  */
  Serial.print("Mode 3 : Lights decremement and become brighter ");
  Serial.print("based on distance sensor results. \n");
  allLow();
  int distanceRead = analogRead(distPin);
  // Tolerances are based on empirical testing.
  if (distanceRead > 150) {
    if (distanceRead > 255) {
      distanceRead = 255;
    }
    analogWrite(redPin, distanceRead); 
  }
  else if (distanceRead > 75) {
    analogWrite(yellowPin, distanceRead);
  }
  else {
    analogWrite(greenPin, distanceRead);
  }
}

void blinking() {
   /*
   * Mode 4 : Blinks LEDs from red to green and then resets.
  */
  Serial.print("Mode 4 : Blinking \n");
  digitalWrite(redPin, HIGH);
  delay(500);
  digitalWrite(yellowPin, HIGH);
  delay(500);
  digitalWrite(greenPin, HIGH);
  delay(500);
  digitalWrite(redPin, LOW);
  delay(500);
  digitalWrite(yellowPin, LOW);
  delay(500);
  digitalWrite(greenPin, LOW);  
}

void loopSwitch() {
  /*
   * Interrupt handler for when the button is pushed.  
   * 
   * Uses timer for debounce protection (mainly due to  
   * mechanical limitations of the button) and then 
   * incremements the switch counter. If the switch 
   * counter has exceeded the number of cases, the value 
   * resets to 0.
  */
  static unsigned long prior_interrupt_time = 0;
  unsigned long current_interrupt_time = millis();
  // 
  if (current_interrupt_time - prior_interrupt_time > 200) {
    if (switchCount < (numberOfPossibleCases - 1)) {
      switchCount++;
    }
    else {
      switchCount = 0;
   }
  }
  prior_interrupt_time = current_interrupt_time;
}
