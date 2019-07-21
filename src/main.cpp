#include <Arduino.h>
#include <NMEASentence.h>

// Sleep Management
#define sleepCounterInitialisedValue 22
#define sleepCounterMin 0
#define sleepCounterMax 1
int sleepCounter __attribute__((section(".noinit")));
short sleepCounterInitialised __attribute__((section(".noinit")));
bool goBackToSleep;

#define ledPin 8

// GPS NMEA Processing
String nmeaSentence = ""; // a String to hold incoming data
bool waitingForStart = true;

// Program state
#define stepSetup 0
#define stepWaitingForGPSFix 1
#define stepGotGPSFix 2
#define stepFailedToGetFix 3
#define stepTransmitting 4
#define stepGoBackToSleep 5

struct state
{
  int activeStep;
};
state programState;

void program(void);

void setup()
{
  // union {
  //   float f;
  //   unsigned char b[4];
  // } lat;

  // union {
  //   float f;
  //   unsigned char b[4];
  // } lon;

  // lat.f = -1 * (String("26").toFloat() + String("08.9986").toFloat() / 60.0);
  // lon.f = String("028").toFloat() + String("08.1069").toFloat() / 60.0;

  // for (int i = 0; i < 4; i++)
  // {
  //   sSerial.print((char)lat.b[i]);
  // }
  // for (int i = 0; i < 4; i++)
  // {
  //   sSerial.print((char)lon.b[i]);
  // }

  // reserve 200 bytes for the nmeaSentence:
  // nmeaSentence.reserve(100);

  Serial.begin(9600);

  // watchdog timer always enabled with maximum prescaler
  WDTCSR |= (1 << WDE) | (1 << WDP3) | (1 << WDP0);

  // sleep counter initialisation in ram
  // this should only happen once
  if (sleepCounterInitialised != sleepCounterInitialisedValue)
  {
    Serial.println("I!");
    // perform first initialisation of sleep counter
    sleepCounter = sleepCounterMin;
    // indicate that sleep counter has been initialised
    sleepCounterInitialised = sleepCounterInitialisedValue;
  }

  // this check is to ensure that sleepCounter
  // never ends up below sleep counter min
  if (sleepCounter < sleepCounterMin)
  {
    // this should never happen
    Serial.println("!");
    sleepCounter = sleepCounterMin;
  }

  // programState.activeStep = stepSetup;
}

void loop()
{
  if (sleepCounter > sleepCounterMax)
  {
    // sleep counter has grown greater than sleepCounterMax
    // the device should be awake and the program should run
    goBackToSleep = false;

    Serial.println("program runs...");

    // reset sleep counter and set flag for retun to sleep
    sleepCounter = sleepCounterMin;
    goBackToSleep = true;
  }
  else
  {
    Serial.println("+");
    // otherwise sleep counter is still below sleepCounterMax
    // and so the device should continue to sleep
    goBackToSleep = true;
    sleepCounter++;
  }

  if (goBackToSleep)
  {
    Serial.println("z");
    // set device to sleep in power down mode
    PRR |= (1 << SE) | (1 << SM1);
  }
}

void program(void)
{
  Serial.println("p");
  switch (programState.activeStep)
  {
  case stepSetup:
    Serial.println(0);
    programState.activeStep = stepWaitingForGPSFix;
    break;

  case stepWaitingForGPSFix:
    Serial.println(1);
    programState.activeStep = stepGotGPSFix;
    break;

  case stepGotGPSFix:
    Serial.println(2);
    programState.activeStep = stepTransmitting;
    break;

  case stepFailedToGetFix:
    Serial.println(3);
    programState.activeStep = stepWaitingForGPSFix;
    break;

  case stepTransmitting:
    Serial.println(4);
    programState.activeStep = stepGoBackToSleep;
    break;

  case stepGoBackToSleep:
    sleepCounter = sleepCounterMin;
    goBackToSleep = true;
    break;

  default:
    break;
  }
}

// ISR(TIMER1_OVF_vect)
// {
// Serial.println("hello!");
// }

void logError(String error)
{
  // sSerial.print("Error: ");
  // sSerial.println(error);
}

void processNMEASentence(String nmeaSentence)
{
  // NMEASentence msg = NMEASentence(nmeaSentence, &logError);
  NMEASentence msg = NMEASentence(nmeaSentence);
  if (msg.valid())
  {
    // sSerial.println(
    //     msg.talkerIdentifier() + " - " +
    //     msg.sentenceIdentifier() + " - " +
    //     msg.sentenceData() + " - " +
    //     msg.checkSum());
  }
}

void serialEvent()
{
}

// void serialEvent()
// {

//   return;

//   while (Serial.available())
//   {
//     // get next byte from available input
//     char inChar = (char)Serial.read();

//     if (waitingForStart)
//     {
//       // if we are waiting for the start of a sentence
//       if (inChar == '$')
//       {
//         // if input is $ a sentence has started
//         nmeaSentence += inChar;
//         waitingForStart = false;
//       } // otherwise do nothing while waiting for start
//     }
//     else
//     {
//       // otherwise we are not waiting for a start
//       nmeaSentence += inChar; // consume next char of input
//       if (inChar == '\n')
//       {
//         // if the input is \n then this is the end of a sentence
//         processNMEASentence(nmeaSentence);
//         nmeaSentence = "";
//         waitingForStart = true;
//       }
//     }
//   }
// }