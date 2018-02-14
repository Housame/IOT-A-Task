/*
 Name:		UsingMillis.ino
 Created:	2/14/2018 11:33:01 AM
 Author:	Housame Oueslati
*/

int sensorPin = A0; // select the input pin for LDR
int sensorValue = 0; // variable to store the value coming from the sensor

int inPin = 2;      // the number of the input pin
int outPinBlink = 12;    // the number of the ouput pin for LED that will blink
int outPinBtn = 13;    // the number of the output pin for the LED depended on the button

int state = HIGH;      // the current state of the output pin for button
int ledState = LOW;    // ledState used to set the blinking LED

int reading;           // the current reading from the input pin
int previous = LOW;    // the previous reading from the input pin
long previousMillis = 0;  // will store last time LED was used
long interval = 1000;  // interval at which to blink (milliseconds)

					   // the follow variables are long's because the time, measured in miliseconds,
					   // will quickly become a bigger number than can be stored in an int.
long time = 0;         // the last time the output pin was toggled  
long debounce = 200;

void setup()
{
	Serial.begin(9600); //sets serial port for communication
	pinMode(inPin, INPUT_PULLUP);
	pinMode(outPinBlink, OUTPUT);
	pinMode(outPinBtn, OUTPUT);
}

void loop()
{
	// -----------Button on/off------------
	reading = digitalRead(inPin);

	// if the input just went from LOW and HIGH and we've waited long enough
	// to ignore any noise on the circuit, toggle the output pin and remember
	// the time
	if (reading == LOW && previous == HIGH && millis() - time > debounce) {
		if (state == HIGH)
		{
			// The LED connected to button turn OFF
			state = LOW;
			Serial.println("LED OFF");
		}
		else
		{
			state = HIGH;
			Serial.println("LED ON");
		}
		time = millis();
	}
	digitalWrite(outPinBtn, state);

	previous = reading;
	// ------------ LED && Sensor ---------
	long currentMillis = millis();
	sensorValue = analogRead(sensorPin); // read the value from the sensor

	if (currentMillis - previousMillis >= sensorValue) {
		Serial.println(sensorValue);
		// save the last time you blinked the LED
		previousMillis = currentMillis;

		// if the LED is off turn it on and vice-versa:
		if (ledState == LOW) {
			ledState = HIGH;
		}
		else {
			ledState = LOW;
		}

		// set the LED with the ledState of the variable:
		digitalWrite(outPinBlink, ledState);
	}
}