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
#define sleepCounterMax 90
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
char transmitToSigfoxModem(String &message);
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
        String sigfoxMessage = String("AT");
        char transmitErr = transmitToSigfoxModem(sigfoxMessage);

        dSerial.begin(9600);
        if (transmitErr != sigfoxErr_NoError)
        {
          dSerial.print("AT error: ");
          dSerial.println(transmitErr);
          programStep = programStepDone;
          break;
        }

        // send data
        if (programError == programErr_NoError)
        {
          sigfoxMessage = String("AT$SF=ABC123456789");
          transmitErr = transmitToSigfoxModem(sigfoxMessage);
        }
        else
        {
          // Send could not get fix message
          sigfoxMessage = String("AT$SF=01");
          transmitErr = transmitToSigfoxModem(sigfoxMessage);
        }
        if (transmitErr == sigfoxErr_NoError)
        {
          dSerial.println("success!!");
        }
        else
        {
          dSerial.print("err: ");
          dSerial.println(transmitErr);
        }

        dSerial.end();
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
char transmitToSigfoxModem(String &message)
{
  // [4.1] initialise send message variables
  String sigfoxResponse = String();
  bool waitingForResponse = true;
  char waitingForResponseStep = waitingForSigfoxResponseStart;
  int waitForResponseStartTimeout = 0;
  int waitForResponseEndTimeout = 0;

  // [4.2] send message
  Serial.print(String(message) + "\r\n");

  // [4.3] waiting for response?
  while (waitingForResponse)
  {
    // [4.4] waiting for response step?
    switch (waitingForResponseStep)
    {
    case waitingForSigfoxResponseStart:
      // [4.5] waiting for start timeout?
      if (waitForResponseStartTimeout > 50)
      {
        // [4.6] Yes, timeout waiting for start
        return sigfoxErr_NoStart;
        break;
      }
      // Not timed out

      // [4.8] new character to read?
      if (Serial.available())
      {
        // [4.9] Yes, read new char into response
        sigfoxResponse += (char)Serial.read();
        waitForResponseStartTimeout++;
      }
      else
      {
        // no, go back to start of step
        waitForResponseStartTimeout++;
        delay(100);
        break;
      }

      // [4.10] response started?
      if ((sigfoxResponse.length() > 0) && sigfoxResponse[0] == 'O')
      {
        waitingForResponseStep = waitingForSigfoxResponseEnd;
      }

      break; // case waitingForSigfoxResponseStart

    case waitingForSigfoxResponseEnd:
      // [4.11] waiting for end timeout?
      if (waitForResponseEndTimeout > 200)
      {
        // [4.12] Yes, timeout waiting for end
        return sigfoxErr_NoEnd;
        break;
      }
      // Not timed out

      // [4.13] increment waiting for end timeout
      waitForResponseEndTimeout++;

      // [4.14] new character to read?
      if (Serial.available())
      {
        // [4.15] Yes, read new char into response
        sigfoxResponse += (char)Serial.read();
      }
      else
      {
        // no, go back to start of step
        break;
      }

      // [4.16] response ended?
      if ((sigfoxResponse.length() > 0) &&
          (sigfoxResponse[sigfoxResponse.length() - 1] == '\n'))
      {
        waitingForResponse = false;
      }

      break;

    default:
      waitingForResponse = false;
      break;
    }
  }

  return sigfoxErr_NoError;
}