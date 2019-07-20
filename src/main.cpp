#include <Arduino.h>
// #include <SoftwareSerial.h>
#include <NMEASentence.h>

/*
  TODO:
- disable watchdog counter
- brown out detection on low voltage?
*/

// #define rxPin 7
// #define txPin 8

// Sleep counter definitions
#define sleepCounterInitialisedValue 22
#define sleepCounterMin 0
#define sleepCounterMax 2

#define ledPin 8

// SoftwareSerial sSerial = SoftwareSerial(rxPin, txPin, false);

String nmeaSentence = ""; // a String to hold incoming data
bool waitingForStart = true;

void setup()
{
  // // disable all interrupts
  // noInterrupts();

  // // setup 16 bit timer to create maximum delay
  // // Normal Mode of Operation
  // TCCR1A &= ~((1 << WGM11) | (1 << WGM10));
  // TCCR1B &= ~((1 << WGM13) | (1 << WGM12));
  // // Internal clock with 1024 prescaler
  // TCCR1B &= ~((1 << CS11));
  // TCCR1B |= (1 << CS12) | (1 << CS10);
  // // enable overflow interrupt
  // TIMSK1 |= (1 << TOIE1);

  // // setup timer for led toggling
  // pinMode(ledPin, OUTPUT);

  // // reenable interrupts
  // interrupts();

  // define pin modes for tx, rx pins:
  // pinMode(rxPin, INPUT);
  // pinMode(txPin, OUTPUT);

  // set the data rate for the SoftwareSerial port
  // sSerial.begin(9600);
  // sSerial.println("Software Serial Initialised");

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

  // 200518.000,2608.9986,S,02808.1069,E,1,06,3.8,1640.3,M,0.0,M,, - 52
  // -26.1499766667, 28.135115
  // initialize serial:

  // 27 33 D1 C1
  // B7 14 E1 41
  // 27 33 d1 c1
  // b7 14 e1 41
  // 41542453463d2733d1c1b714e1a
  // 41542453463d2733d1c1b714a
  // 41542453463d2733d1a

  // 0110 1011 1011 1010

  Serial.begin(9600);

  // reserve 200 bytes for the nmeaSentence:
  nmeaSentence.reserve(100);

  // enable watchdog timer with maximum prescaler
  WDTCSR |= (1 << WDE) | (1 << WDP3) | (1 << WDP0);
}

int sleepCounter __attribute__((section(".noinit")));
short sleepCounterInitialised __attribute__((section(".noinit")));

void loop()
{
  if (sleepCounterInitialised != sleepCounterInitialisedValue)
  {
    // perform first initialisation of sleep counter
    sleepCounter = sleepCounterMin;
  }
  if (sleepCounter < sleepCounterMin || sleepCounter > sleepCounterMax)
  {
    // reset sleep counter
    sleepCounter = sleepCounterMin;
  }

  // Do something
  Serial.println(sleepCounter);

  // increment sleep counter
  sleepCounter++;

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