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
void recurringHardwareSetup(void);
void recurringHardwareTeardown(void);

// ********************* Pin Definitions *********************
#define awakeLEDPin 13
#define gpsSwitchPin 12
#define gpsUSARTRXPin 7
#define gpsUSARTTXPin 8
SoftwareSerial sSerial = SoftwareSerial(gpsUSARTRXPin, gpsUSARTTXPin, false);

// ******************** Program Loop ********************
bool runProgram;
char programStep;
#define programStepStart 'a'
#define programStepWaitingForGPSFix 'b'
NMEASentence nmeaSentence;
int noNMEASentencesRead;
#define programStepTransmit 'c'
#define programStepDone 'd'

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
  // sleep
  goToSleep();

  // run program

  recurringHardwareSetup();
  runProgram = true;
  programStep = programStepStart;
  while (runProgram)
  {
    switch (programStep)
    {
    case programStepStart:
      initialiseNMEASentence(&nmeaSentence);
      noNMEASentencesRead = 0;
      programStep = programStepWaitingForGPSFix;
      break;

    case programStepWaitingForGPSFix:
      if (sSerial.available())
      {
        // get the new byte:
        char nextChar = (char)sSerial.read();

        // read the new char into the nmeaSentence
        readCharForNMEASentence(&nmeaSentence, nextChar);

        // check if any errors arose from reading the next char
        if (nmeaSentence.errorCode != NMEASentenceErr_NoError)
        {
          // if there is an error

          // increase the number of sentences read
          noNMEASentencesRead++;
          // reset the nmea sentence
          initialiseNMEASentence(&nmeaSentence);
        }
        else
        {
          // otherwise no error has arisen from reading the new char

          // check if the reading is complete
          if (nmeaSentence.readingComplete)
          {

            // if the reading is complete

            // process reading
            if ((strcmp(nmeaSentence.talkerIdentifier, "GN") == 0) &&
                (strcmp(nmeaSentence.sentenceIdentifier, "RMC") == 0))
            {
              // process the reading sententence
              Serial.println(nmeaSentence.sentenceString);
              programStep = programStepTransmit;
            }
            else
            {
              // done - no

              // increase the number of sentences read
              noNMEASentencesRead++;
              // reset the nmea sentence
              initialiseNMEASentence(&nmeaSentence);
            }
          }
        }
      }
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
  recurringHardwareTeardown();
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
void recurringHardwareSetup(void)
{
  // turn led on to show device is on
  digitalWrite(awakeLEDPin, HIGH);
  // turn on GPS
  digitalWrite(gpsSwitchPin, HIGH);

  Serial.begin(9600);
  sSerial.begin(9600);
}

void recurringHardwareTeardown(void)
{
  // turn led off to show device is off
  digitalWrite(awakeLEDPin, LOW);
  // turn off GPS
  digitalWrite(gpsSwitchPin, LOW);

  Serial.end();
  sSerial.end();
}