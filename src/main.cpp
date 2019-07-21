#include <Arduino.h>
// #include <NMEASentence.h>

// Sleep Management
#define sleepCounterInitialisedValue 22
#define sleepCounterMin 0
#define sleepCounterMax 1
int sleepCounter __attribute__((section(".noinit")));
int sleepCounterInitialised __attribute__((section(".noinit")));
bool goBackToSleep;

#define ledPin 8

// GPS NMEA Processing
String nmeaSentence = ""; // a String to hold incoming data
bool waitingForStart;

// Program State
#define stepSetup 'A'
#define stepWaitingForGPSFix 'B'
#define stepGotGPSFix 'C'
#define stepFailedToGetFix 'D'
#define stepTransmitting 'E'
#define stepGoBackToSleep 'F'
char activeProgramStep;

// waiting for gps fix
bool gpsFixDone = false;
void checkSerial();

void runProgram(void);

void setup()
{
  Serial.begin(9600);
  Serial1.begin(9600);
  Serial.print('}');
  waitingForStart = true;

  // sleep counter initialisation in ram
  // this should only happen once
  if (sleepCounterInitialised != sleepCounterInitialisedValue)
  {
    Serial.println('I');
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
    sleepCounter = sleepCounterMin;
  }

  // initialise program state in case it is
  // time for the device to wake up
  activeProgramStep = stepSetup;
}

void loop()
{
  if (sleepCounter > sleepCounterMax)
  {
    // sleep counter has grown greater than sleepCounterMax
    // the device should be awake and the program should run
    goBackToSleep = false;
    runProgram();
  }
  else
  {
    // otherwise sleep counter is still below sleepCounterMax
    // and so the device should continue to sleep
    goBackToSleep = true;
    sleepCounter++;
  }

  if (goBackToSleep)
  {
    Serial.print('z');
    // watchdog timer always enabled with maximum prescaler
    WDTCSR |= (1 << WDE) | (1 << WDP3) | (1 << WDP0);
    // set device to sleep in power down mode
    PRR |= (1 << SE) | (1 << SM1);
  }
}

void runProgram(void)
{
  // Serial.print(activeProgramStep);
  Serial.print('4');

  switch (activeProgramStep)
  {
  case stepSetup:
    activeProgramStep = stepWaitingForGPSFix;
    break;

  case stepWaitingForGPSFix:
    checkSerial();
    if (gpsFixDone)
    {
      activeProgramStep = stepGotGPSFix;
    }
    break;

  case stepGotGPSFix:
    activeProgramStep = stepTransmitting;
    break;

  case stepFailedToGetFix:
    activeProgramStep = stepGoBackToSleep;
    break;

  case stepTransmitting:
    activeProgramStep = stepGoBackToSleep;
    break;

  case stepGoBackToSleep:
  default:
    goBackToSleep = true;
    sleepCounter = sleepCounterMin;
    break;
  }

  return;
}

void checkSerial()
{
  // while there is data available at the given port
  while (Serial.available())
  {
    // get next byte from available
    char inChar = (char)Serial.read();
    Serial.print("In ");
    Serial.print(inChar);
    bool start = inChar == '$';
    bool end = inChar == '\n';

    if (waitingForStart)
    {
      Serial.println('w');
      if (start)
      {
        Serial.println('s');
        // if input is $ a sentence has started
        // nmeaSentence += inChar;
        waitingForStart = false;
      }
    }
    else
    {
      Serial.println('c');
      // otherwise we are not waiting for a start
      // nmeaSentence += inChar; // consume next char of input

      if (end)
      {
        Serial.println('d');
        gpsFixDone = true;
        waitingForStart = true;
      }
    }

    // if (waitingForStart)
    // {
    //   // if we are waiting for the start of a sentence
    // if (inChar == '$')
    // {
    //   // if input is $ a sentence has started
    // nmeaSentence += inChar;
    //   waitingForStart = false;
    // } // otherwise do nothing while waiting for start
    // }
    // else
    // {
    // // otherwise we are not waiting for a start
    // nmeaSentence += inChar; // consume next char of input
    //   if (inChar == '\n')
    //   {
    //     // if the input is \n then this is the end of a sentence
    //     Serial.print("process: " + nmeaSentence);
    //     gpsFixDone = true;
    //     nmeaSentence = "";

    //     // indicate that we are waiting for start again
    //     waitingForStart = true;
    //   }
    // }
  }
}

// void serialEvent()
// {

//   return;

//   while (Serial.available())
//   {
// // get next byte from available input
// char inChar = (char)Serial.read();

// if (waitingForStart)
// {
//   // if we are waiting for the start of a sentence
//   if (inChar == '$')
//   {
//     // if input is $ a sentence has started
//     nmeaSentence += inChar;
//     waitingForStart = false;
//   } // otherwise do nothing while waiting for start
// }
// else
// {
//   // otherwise we are not waiting for a start
//   nmeaSentence += inChar; // consume next char of input
//   if (inChar == '\n')
//   {
//     // if the input is \n then this is the end of a sentence
//     processNMEASentence(nmeaSentence);
//     nmeaSentence = "";
//     waitingForStart = true;
//   }
// }
//   }
// }

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

// ISR(TIMER1_OVF_vect)
// {
// Serial.println("hello!");
// }

// void logError(String error)
// {
//   // sSerial.print("Error: ");
//   // sSerial.println(error);
// }

// void processNMEASentence(String nmeaSentence)
// {
//   // NMEASentence msg = NMEASentence(nmeaSentence, &logError);
//   NMEASentence msg = NMEASentence(nmeaSentence);
//   if (msg.valid())
//   {
//     // sSerial.println(
//     //     msg.talkerIdentifier() + " - " +
//     //     msg.sentenceIdentifier() + " - " +
//     //     msg.sentenceData() + " - " +
//     //     msg.checkSum());
//   }
// }