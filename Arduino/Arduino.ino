const int buttonPin = 2;     // the number of the pushbutton pin
const int ledPin =  3;      // the number of the LED pin

// variable for reading the pushbutton status
int buttonState = 0;
// variable to hold sensor value
int sensorValue;
// variable to calibrate low value
int sensorLow = 1023;
// variable to calibrate high value
int sensorHigh = 0;

void setup() {
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);

  // calibrate for the first five seconds after program runs
  digitalWrite(ledPin, HIGH);
  while (millis() < 5000) {
    // record the maximum sensor value
    sensorValue = analogRead(A0);
    if (sensorValue > sensorHigh) {
      sensorHigh = sensorValue;
    }
    // record the minimum sensor value
    if (sensorValue < sensorLow) {
      sensorLow = sensorValue;
    }
  }
  // turn the LED off, signaling the end of the calibration period
  digitalWrite(ledPin, LOW);

  Serial.begin(9600);
}

void loop() {
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);

  //read the input from A0 and store it in a variable
  sensorValue = analogRead(A0);
  int mappedValue = map(sensorValue, sensorLow, sensorHigh, 0, 1023);
  int constrValue = constrain(mappedValue, 0, 1023);

  Serial.print(buttonState);
  Serial.print(" ");
  Serial.println(constrValue);

  delay(100);
}

