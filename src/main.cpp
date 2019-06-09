#include <Arduino.h>
#include <SoftwareSerial.h>

#define rxPin 7
#define txPin 8

#define ledPin 13

SoftwareSerial sSerial = SoftwareSerial(rxPin, txPin, false);

String inputString = "";     // a String to hold incoming data
bool stringComplete = false; // whether the string is complete

void setup()
{
  // setup timer for led toggling
  pinMode(ledPin, OUTPUT);

  // define pin modes for tx, rx, led pins:
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);

  // set the data rate for the SoftwareSerial port
  sSerial.begin(9600);
  sSerial.println("Hello World - SoftwareSerial");

  // initialize serial:
  Serial.begin(9600);

  // reserve 200 bytes for the inputString:
  inputString.reserve(200);
}

void loop()
{
  // print the string when a newline arrives:
  if (stringComplete)
  {
    sSerial.print(inputString);
    // clear the string:
    inputString = "";
    stringComplete = false;
  }
}

void serialEvent()
{
  while (Serial.available())
  {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == '\n')
    {
      stringComplete = true;
    }
  }
}