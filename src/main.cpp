#include <Arduino.h>
#include <SoftwareSerial.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <avr/power.h>
#include <avr/wdt.h>
#include <WDT.h>
#include <NMEASentence.h>

// ********************* Sleep *********************
int sleepCounter;
void goToSleep(void);
#define sleepCounterMax 2
#define sleepCounterMin 0

// ********************* Hardware Setup/Teardown *********************
void hardwareSetup(void);
void hardwareTeardown(void);

// ********************* Pin Definitions *********************
#define awakeLEDPin 13
#define gpsSwitchPin 12
#define gpsUSARTRXPin 7
#define gpsUSARTTXPin 8
SoftwareSerial sSerial = SoftwareSerial(gpsUSARTRXPin, gpsUSARTTXPin, false);

// ******************** Program ********************
void program(void);
bool runProgram;
char programStep;
#define programStepStart 'a'
#define programStepWaitingForGPSFix 'b'
void waitForNMEASentence(void);
NMEASentence nmeaSentence;
int noNMEASentencesRead;
#define programStepTransmit 'c'
#define programStepDone 'd'

// ******************** Waiting for NMEA Sentence ********************
#define waitingForSentenceStartStep 'a'
#define waitingForSentenceEndStep 'b'

void setup()
{
  // set awake LED pin as output
  pinMode(awakeLEDPin, OUTPUT);
  // set gps switch pin as output
  pinMode(gpsSwitchPin, OUTPUT);

  // define pin modes GPS usart pins
  pinMode(gpsUSARTRXPin, INPUT);
  pinMode(gpsUSARTTXPin, OUTPUT);

  // configure the watchdog
  wdtSetup();
}

void loop()
{
  // [1.6] Sleep
  goToSleep();

  // [1.1] Device Wakes Up

  // [1.2] Hardware Setup
  hardwareSetup();

  // [1.3] Program Setup
  runProgram = true;
  programStep = programStepStart;

  // [1.4] Run Program
  program();

  // [1.5] Hardware Teardown
  hardwareTeardown();
}

// Handle watchdog timer interrupt
ISR(WDT_vect)
{
  // reset watchdog timer
  wdt_reset();
}

void goToSleep(void)
{
  // reset sleep counter
  sleepCounter = sleepCounterMin;

  // set sleep to full power down mode
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);

  // turn off the ADC while asleep
  power_adc_disable();

  while (sleepCounter < sleepCounterMax)
  {
    // enable sleep and enter sleep mode.
    sleep_mode();

    // cpu will sleep util woken by WDT interrupt
    // after executing the WDT ISR execution will
    // continue from here

    // disable sleep mode
    sleep_disable();

    // increment sleep counter
    sleepCounter++;
  }

  // put everything on again
  power_all_enable();
}

// ********************* Hardware Setup/Teardown *********************
void hardwareSetup(void)
{
  // turn led on to show device is on
  digitalWrite(awakeLEDPin, HIGH);
  // turn on GPS
  digitalWrite(gpsSwitchPin, HIGH);

  Serial.begin(9600);
  sSerial.begin(9600);

  // wait a little for gps to start
  delay(1000);
}

void hardwareTeardown(void)
{
  // turn led off to show device is off
  digitalWrite(awakeLEDPin, LOW);
  // turn off GPS
  digitalWrite(gpsSwitchPin, LOW);

  Serial.end();
  sSerial.end();
}

// ******************** Program ********************
void program(void)
{
  // [2.1] Run Program?
  while (runProgram)
  {
    // Yes - Run the program

    // [2.2] What is the program step?
    switch (programStep)
    {
    // [2.3] Program Step is 'Program Step Start'
    case programStepStart:
      initialiseNMEASentence(&nmeaSentence);
      noNMEASentencesRead = 0;
      // Transition to waiting for GPS Fix
      programStep = programStepWaitingForGPSFix;
      break;

    case programStepWaitingForGPSFix:
      // [2.4] wait for NMEA Sentence
      waitForNMEASentence();
      if (nmeaSentence.errorCode != NMEASentenceErr_NoError)
      {
        Serial.print("done error!");
        Serial.println(nmeaSentence.errorCode);
      }
      else
      {
        Serial.print("done no error!: ");
        Serial.println(nmeaSentence.sentenceString);
      }
      programStep = programStepTransmit;
      break;

    case programStepTransmit:
      programStep = programStepDone;
      break;

    case programStepDone:
      runProgram = false;
      break;

    default:
      runProgram = false;
      break;
    }
  }
}

void waitForNMEASentence(void)
{
  // [3.1] initialise waiting for NMEA Sentence variables
  bool waitingForSentence = true;
  int waitForStartTimeout = 0;
  int waitForEndTimeout = 0;
  initialiseNMEASentence(&nmeaSentence);
  char waitingForSentenceStep = waitingForSentenceStartStep;

  // [3.2] Waiting for sentence?
  while (waitingForSentence)
  {
    // [3.3] Waiting for sentence step?
    switch (waitingForSentenceStep)
    {
    case waitingForSentenceStartStep:
      // [3.4] Waiting for start timeout?
      if (waitForStartTimeout > 200)
      {
        // [3.5] Yes, timeout waiting for start
        nmeaSentence.errorCode = NMEASentenceErr_MessageDidntStart;
        waitingForSentence = false;
        break;
      }
      // Not timed out

      // [3.6] Increment waiting for start timeout
      waitForStartTimeout++;

      // [3.7] New Character to read?
      if (sSerial.available())
      {
        // [3.8] Yes read new char into sentence
        readCharForNMEASentence(&nmeaSentence, (char)sSerial.read());
      }
      else
      {
        // no, go back to start of step
        break;
      }

      // [3.9] Sentence Started?
      if (nmeaSentence.readingStarted)
      {
        // [3.10] Yes, sentence started. Transition to waiting for sentence end
        waitingForSentenceStep = waitingForSentenceEndStep;
        break;
      }

      break; // case waitingForSentenceStartStep

    case waitingForSentenceEndStep:
      // [3.11] NMEA Sentence read error?
      if (nmeaSentence.errorCode != NMEASentenceErr_NoError)
      {
        // [3.12] Yes
        waitingForSentence = false;
        break;
      }
      // No

      // [3.13] Waiting for end timeout?
      if (waitForEndTimeout > 255)
      {
        // [3.14] Yes, timeout waiting for end
        nmeaSentence.errorCode = NMEASentenceErr_MessageDidntEnd;
        waitingForSentence = false;
        break;
      }
      // Not timed out

      // [3.15] Increment waiting for end timeout
      waitForEndTimeout++;

      // [3.16] New Character to read?
      if (sSerial.available())
      {
        // [3.17] Yes read new char into sentence
        readCharForNMEASentence(&nmeaSentence, (char)sSerial.read());
      }
      else
      {
        // no, go back to start of step
        break;
      }

      // [3.18] Sentence ended?
      if (nmeaSentence.readingComplete)
      {
        // yes ended!
        waitingForSentence = false;
        break;
      }

      break; // case waitingForSentenceEndStep

    default:
      break;
    }
  }
}