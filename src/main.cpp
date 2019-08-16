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
#define debugUSARTRXPin 2
#define debugUSARTTXPin 3
SoftwareSerial sSerial = SoftwareSerial(gpsUSARTRXPin, gpsUSARTTXPin, false);
SoftwareSerial dSerial = SoftwareSerial(debugUSARTRXPin, debugUSARTTXPin, false);

// ******************** Program ********************
void program(void);
char programError;
#define programErr_NoError '0'
#define programErr_UnexpecedError '!'
#define programErr_WaitingForNMEASentence '1'
#define programErr_UnableToGetFix '2'
bool runProgram;
char programStep;
#define programStepStart 'a'
#define programStepWaitingForGPSFix 'b'
int noNMEASentencesRead;
#define programStepTransmit 'c'
#define programStepDone 'd'
gpsReading gpsReadingToTransmit;

// ******************** Waiting for NMEA Sentence ********************
#define waitingForSentenceStartStep 'a'
#define waitingForSentenceEndStep 'b'
void waitForNMEASentence(void);
NMEASentence nmeaSentence;

// ******************** Transmit To Sigfox Modem ********************
char transmitToSigfoxModem(const char *message, const char *desiredResponse = "OK");
#define waitingForSigfoxResponseStart 'a'
#define waitingForSigfoxResponseEnd 'b'
#define sigfoxErr_NoError '0'
#define sigfoxErr_NoStart '1'
#define sigfoxErr_NoEnd '2'

void setup()
{
  // set awake LED pin as output
  pinMode(awakeLEDPin, OUTPUT);
  // set gps switch pin as output
  pinMode(gpsSwitchPin, OUTPUT);

  // define pin modes GPS usart pins
  pinMode(gpsUSARTRXPin, INPUT);
  pinMode(gpsUSARTTXPin, OUTPUT);

  // define pin modes debug usart pins
  pinMode(debugUSARTRXPin, INPUT);
  pinMode(debugUSARTTXPin, OUTPUT);

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
  programError = programErr_NoError;
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

    // flash led
    digitalWrite(awakeLEDPin, HIGH);
    delay(500);
    digitalWrite(awakeLEDPin, LOW);

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
  dSerial.begin(9600);

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
  dSerial.end();
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
      // [2.4] has max allowed number of nmea messages been read
      // without getting a valid gps fix?
      if (noNMEASentencesRead > 250)
      {
        // [2.5] could not get valid fix
        programError = programErr_UnableToGetFix;
        programStep = programStepTransmit;
        break;
      }
      // max number of sentences not reached

      // [2.6] increment number of sentences
      noNMEASentencesRead++;

      // [2.7] wait for NMEA Sentence
      waitForNMEASentence();

      // [2.8] is there an error with the nmea sentence?
      if (nmeaSentence.errorCode != NMEASentenceErr_NoError)
      {
        // Yes, there is an error, go back to start of step
        break;
      }
      // No, there is no error
      Serial.println(nmeaSentence.sentenceString);

      // [2.9] is this a gps sentence?
      if ((strcmp(nmeaSentence.talkerIdentifier, "GN") != 0) ||
          (strcmp(nmeaSentence.sentenceIdentifier, "RMC") != 0))
      {
        // No, this is not a gps sentence, go back to start of step
        break;
      }
      // Yes, this is a gps sentence

      // [2.10] process the sentence
      process_GNRMC_NMEASentence(&nmeaSentence, &gpsReadingToTransmit);

      // [2.11] is the reading valid?
      if (gpsReadingToTransmit.error != NMEASentenceErr_processGPSNMEASentence_NoError)
      {
        // the reading is not valid, go back to start of step
        break;
      }

      // the reading is valid, transition to transmit step
      programStep = programStepTransmit;
      break;

    case programStepTransmit:
      switch (programError)
      {
      case programErr_NoError:
        break;

      case programErr_UnableToGetFix:

        // transmit dummy AT command to ensure modem is awake and operating
        if (transmitToSigfoxModem("AT") != sigfoxErr_NoError)
        {
          // if an error is returned, end program
          programStep = programStepDone;
          break;
        }

        // if there is no program error, i.e. gps data parsed successfully
        if (programError == programErr_NoError)
        {
          // transmit the data
          transmitToSigfoxModem("AT$SF=ABC123456789");
        }
        else
        {
          // otherwise, there was a program error
          // transmit could not get fix
          transmitToSigfoxModem("AT$SF=01");
        }

        break;

      default:
        programStep = programStepDone;
        break;
      }
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
      if (waitForEndTimeout > 200)
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
        // [3.19] sentence ended, parse
        parseNMEASentence(&nmeaSentence);
        waitingForSentence = false;
        break;
      }
      // No sentence not ended

      break; // case waitingForSentenceEndStep

    // other case
    default:
      // [3.20] Unexpeced error
      nmeaSentence.errorCode = NMEASentenceErr_UnexpectedError;
      waitingForSentence = false;
      break;
    }
  }
}

// ******************** Transmit To Sigfox Modem ********************
char transmitToSigfoxModem(const char *message, const char *desiredResponse = "OK")
{
  // [4.1] initialise send message variables
  String sigfoxResponse = String();
  int waitForStartResponseTimeout = 0;
  int waitForEndTimeout = 0;

  // clear serial buffer
  Serial.flush();

  // [4.2] send message
  Serial.print(message);
  Serial.print("\r\n");

  // wait for serial data to become available
  while (!Serial.available())
  {
    waitForStartResponseTimeout++;
    delay(30);
    if (waitForStartResponseTimeout > 400)
    {
      // if no data after allowed time, return error
      return sigfoxErr_NoStart;
    }
  }
  // serial data is now available

  while (waitForEndTimeout < 300)
  {
    // read all availabe serial data
    while (Serial.available())
    {
      sigfoxResponse += (char)Serial.read();
      if (sigfoxResponse.length() > 20)
      {
        // if serial still available after max
        // allowed length, return error
        return sigfoxErr_NoEnd;
      }
    }

    // check if desired response is in what was received
    if (sigfoxResponse.indexOf(desiredResponse) >= 0)
    {
      // it was found, return success
      return sigfoxErr_NoError;
    }

    // it was not found, wait a bit and then keep trying
    delay(30);
    waitForEndTimeout++;
  }

  return sigfoxErr_NoEnd;
}