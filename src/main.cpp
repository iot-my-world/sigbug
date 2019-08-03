#include <Arduino.h>
#include <SoftwareSerial.h>
#include <avr/interrupt.h> // library for interrupts handling
#include <avr/sleep.h>     // library for sleep
#include <avr/power.h>     // library for power control
#include <avr/wdt.h>
#include <WDT.h>

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
      programStep = programStepWaitingForGPSFix;
      break;

    case programStepWaitingForGPSFix:
      if (sSerial.available())
      {
        // get the new byte:
        char inChar = (char)sSerial.read();
        if (inChar == '$')
        {
          programStep = programStepTransmit;
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

  sSerial.begin(9600);
}

void recurringHardwareTeardown(void)
{
  // turn led off to show device is off
  digitalWrite(awakeLEDPin, LOW);
  // turn off GPS
  digitalWrite(gpsSwitchPin, LOW);

  sSerial.end();
}