#include <Arduino.h>
#include <NMEASentence.h>

// Sleep Counter
#define sleepCounterInitialisedValue 22
#define sleepCounterMin 0
#define sleepCounterMax 1
int sleepCounter __attribute__((section(".noinit")));
short sleepCounterInitialised __attribute__((section(".noinit")));

#define ledPin 8

// GPS NMEA Processing
String nmeaSentence = ""; // a String to hold incoming data
bool waitingForStart = true;

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

  // reserve 200 bytes for the nmeaSentence:
  nmeaSentence.reserve(100);

  // enable watchdog timer with maximum prescaler
  WDTCSR |= (1 << WDE) | (1 << WDP3) | (1 << WDP0);
}

void loop()
{
  if (sleepCounterInitialised != sleepCounterInitialisedValue)
  {
    // perform first initialisation of sleep counter
    sleepCounter = sleepCounterMin;
    // indicate that sleep counter has been initialised
    sleepCounterInitialised = sleepCounterInitialisedValue;
  }

  if (sleepCounter < sleepCounterMin || sleepCounter > sleepCounterMax)
  {
    // sleepConter is out of it's bounds and so
    // the sleep is complete

    // run the program
    Serial.println("program run!");

    // reset the sleep counter
    sleepCounter = sleepCounterMin;
  }
  else
  {
    // sleep counter is still between sleepCounterMin and sleepCounterMax
    // and so the sleep is not over, do not allow the program to run
    // increment sleep counter
    sleepCounter++;
  }

  // set device to sleep in power down mode
  PRR |= (1 << SE) | (1 << SM1);
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