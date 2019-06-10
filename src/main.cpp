#include <Arduino.h>
#include <SoftwareSerial.h>
#include <NMEASentence.h>

#define rxPin 7
#define txPin 8

#define ledPin 13

SoftwareSerial sSerial = SoftwareSerial(rxPin, txPin, false);

String nmeaSentence = ""; // a String to hold incoming data

void setup()
{
  // setup timer for led toggling
  pinMode(ledPin, OUTPUT);

  // define pin modes for tx, rx, led pins:
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);

  // set the data rate for the SoftwareSerial port
  sSerial.begin(9600);
  sSerial.println("Software Serial Initialised");

  // initialize serial:
  Serial.begin(9600);

  // reserve 200 bytes for the nmeaSentence:
  nmeaSentence.reserve(100);
}

void loop()
{
}

void logError(String error)
{
  sSerial.print("Error: ");
  sSerial.println(error);
}

void processNMEASentence(String nmeaSentence)
{
  NMEASentence msg = NMEASentence(nmeaSentence, &logError);
  sSerial.print(msg.raw());
}

void serialEvent()
{
  while (Serial.available())
  {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the nmeaSentence:
    nmeaSentence += inChar;
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == '\n')
    {
      processNMEASentence(nmeaSentence);
      nmeaSentence = "";
    }
  }
}