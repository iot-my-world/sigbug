#include <Arduino.h>
#include <SoftwareSerial.h>
#include <NMEASentence.h>

#define rxPin 7
#define txPin 8

#define ledPin 13

SoftwareSerial sSerial = SoftwareSerial(rxPin, txPin, false);

String nmeaSentence = ""; // a String to hold incoming data
bool waitingForStart = true;

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
  // NMEASentence msg = NMEASentence(nmeaSentence, &logError);
  NMEASentence msg = NMEASentence(nmeaSentence);
  if (msg.valid())
  {
    sSerial.println(
        msg.talkerIdentifier() + " - " +
        msg.sentenceIdentifier() + " - " +
        msg.sentenceData() + " - " +
        msg.checkSum());
  }
}

void serialEvent()
{
  while (Serial.available())
  {
    // get next byte from available input
    char inChar = (char)Serial.read();

    if (waitingForStart)
    {
      // if we are waiting for the start of a sentence
      if (inChar == '$')
      {
        // if input is $ a sentence has started
        nmeaSentence += inChar;
        waitingForStart = false;
      } // otherwise do nothing while waiting for start
    }
    else
    {
      // otherwise we are not waiting for a start
      nmeaSentence += inChar; // consume next char of input
      if (inChar == '\n')
      {
        // if the input is \n then this is the end of a sentence
        processNMEASentence(nmeaSentence);
        nmeaSentence = "";
        waitingForStart = true;
      }
    }
  }
}