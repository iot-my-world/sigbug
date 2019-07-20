#include <Arduino.h>
#include <NMEASentence.h>

// Sleep Management
#define sleepCounterInitialisedValue 22
#define sleepCounterMin 0
#define sleepCounterMax 1
int sleepCounter __attribute__((section(".noinit")));
short sleepCounterInitialised __attribute__((section(".noinit")));
bool goBackToSleep = true;

#define ledPin 8

// GPS NMEA Processing
String nmeaSentence = ""; // a String to hold incoming data
bool waitingForStart = true;

// Program steps
#define stepInitialising 0
#define stepWaitingForGPSFix 1
#define stepGotGPSFix 2
#define stepFailedToGetFix 3
#define stepTransmittingData 4
#define stepGoBackToSleep 5

void program();

struct state
{
  int step;
};
state programState;

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

  Serial.begin(9600);
  Serial.println("d");

  // reserve 200 bytes for the nmeaSentence:
  nmeaSentence.reserve(100);

  // enable watchdog timer with maximum prescaler
  WDTCSR |= (1 << WDE) | (1 << WDP3) | (1 << WDP0);

  // unless the sleep counter has overflown
  // default behaviour is to go back to sleep
  goBackToSleep = true;

  // this should only run once and is to initialise the
  // sleep counter in ram
  if (sleepCounterInitialised != sleepCounterInitialisedValue)
  {
    // perform first initialisation of sleep counter
    sleepCounter = sleepCounterMin;
    // indicate that sleep counter has been initialised
    sleepCounterInitialised = sleepCounterInitialisedValue;
  }

  // this should never be true
  if (sleepCounter < sleepCounterMin)
  {
    sleepCounter = sleepCounterMin;
  }
}

void loop()
{
  Serial.println("asd");
  // check if the sleep counter has overflown
  if (sleepCounter > sleepCounterMax)
  {
    Serial.println("wake up!");
    // if the sleep counter has overflown the device must wake up
    goBackToSleep = false;
  }
  else
  {
    Serial.println("increment");
    // otherwise the device should still be sleeping
    // increment the sleep counter and allow it to go back to sleep
    sleepCounter++;
  }

  if (goBackToSleep)
  {
    // reset the sleep counter
    sleepCounter = sleepCounterMin;

    // set device to sleep in power down mode
    PRR |= (1 << SE) | (1 << SM1);
  }
  else
  {
    // device is awake, run the progrm
    program();
  }
}

void program()
{
  switch (programState.step)
  {
  case stepInitialising:
    Serial.println("init");
    programState.step = stepWaitingForGPSFix;
    break;

  case stepWaitingForGPSFix:
    Serial.println("waiting for fix...");
    programState.step = stepGotGPSFix;
    break;

  case stepGotGPSFix:
    Serial.println("got fix!");
    programState.step = stepTransmittingData;
    break;

  case stepTransmittingData:
    Serial.println("transmit data");
    programState.step = stepGoBackToSleep;
    break;

  case stepGoBackToSleep:
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