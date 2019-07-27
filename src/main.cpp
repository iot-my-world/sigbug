#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <util/delay.h>
#include <USART.h>
#include <WDT.h>
#include <String.h>
#include <NMEASentence.h>

// ********************* Sleep *********************
void goToSleep(void);
char sleepCounterInitialised __attribute__((section(".noinit")));
int sleepCounter __attribute__((section(".noinit")));
#define sleepCounterInitialisedValue '!'
#define sleepCounterMin 0
#define sleepCounterMax 1

// ******************** Program Loop ********************
void program(void);
bool runProgram;
#define programStepStart 'a'
NMEASentence nmeaSentence = NMEASentence();
#define programStepWaitingForGPSFix 'b'
bool gpsFixDone;
bool waitingForStartOfNMEAWord;
#define programStepGPSFixSuccess 'c'
#define programStepGPSFixFailure 'd'
#define programStepTransmit 'e'
#define programStepDone 'f'
char programStep;

// ********************* Hardware Setup/Teardown *********************
void onceOffSetup(void);
void recurringHardwareSetup(void);
void recurringHardwareTeardown(void);

// ********************* Pin Definitions *********************
#define awakeLedPin PB2
#define gpsSwitchPin PA7

int main(void)
{
    onceOffSetup();

    while (1)
    {
        if (sleepCounter <= sleepCounterMax)
        {
            // the device should go back to sleep
            sleepCounter++;
            goToSleep();
        }
        else
        {
            // the device should wake up and run the program
            recurringHardwareSetup();
            runProgram = true;
            programStep = programStepStart;
            sei();
            while (runProgram)
            {
                program();
            }
            cli();
            // todo, find a way to remove this
            _delay_ms(100);
            recurringHardwareTeardown();
            sleepCounter = sleepCounterMin;
        }
    }

    return 0;
}

// ********************* Sleep *********************
void goToSleep(void)
{
    cli();

    // set sleep mode to complete power down
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);

    // enable sleep mode
    sleep_enable();

    enableWDT();

    sei(); // ensure interrupts enabled so that the device can wake up again

    // put processor to sleep
    sleep_cpu();

    // when processor wakes execution will continue from here
    sleep_disable();

    disableWDT();

    cli();
}

ISR(WDT_vect)
{
}

// ******************** Program Loop ********************
void program(void)
{
    switch (programStep)
    {
    case programStepStart:
        programStep = programStepWaitingForGPSFix;
        gpsFixDone = false;
        waitingForStartOfNMEAWord = true;
        nmeaSentence.reset();

    case programStepWaitingForGPSFix:
        if (gpsFixDone)
        {
            flushSigfoxUSART();
            programStep = programStepGPSFixSuccess;
        }
        break;

    case programStepGPSFixSuccess:
        programStep = programStepTransmit;
        break;

    case programStepTransmit:
        programStep = programStepDone;
        break;

    case programStepDone:
        runProgram = false;
        break;

    default:
        break;
    }
}

// ********************* Hardware Setup/Teardown *********************
void onceOffSetup(void)
{
    setupWDT();
    initGPSUSART();
    initSigfoxUSART();

    // initialise sleep counter if it hasn't been yet
    if (sleepCounterInitialised != sleepCounterInitialisedValue)
    {
        sleepCounter = sleepCounterMin;
    }

    // set up led pin as output
    DDRB |= (1 << awakeLedPin);
    // set gps switch pin as output
    DDRA |= (1 << gpsSwitchPin);
}

void recurringHardwareSetup(void)
{
    // turn led on to show device is on
    PORTB |= (1 << awakeLedPin);

    // turn gps on
    PORTA |= (1 << gpsSwitchPin);

    // start USARTs
    startSigfoxUSART();
    startGPSUSART();
}

void recurringHardwareTeardown(void)
{
    // turn led off to show device is off
    PORTB &= ~((1 << awakeLedPin));

    // turn gps off
    PORTA &= ~((1 << gpsSwitchPin));

    // stop USARTs
    stopSigfoxUSART();
    startGPSUSART();
}

ISR(USART1_RX_vect)
{
    cli();
    nmeaSentence.readChar(UDR1);

    // check for error in sentence
    if ((nmeaSentence.errorCode()) != NMEASentenceErr_NoError)
    {
        // TODO: deal with error
        transmitCharSigfoxUSART(nmeaSentence.errorCode());
        transmitCharSigfoxUSART('\n');
        gpsFixDone = true;
        return;
    }

    if (nmeaSentence.readingComplete())
    {
        transmitStringSigfoxUSART(nmeaSentence.string().Value());
        stopGPSUSART();
        flushGPSUSART();
        gpsFixDone = true;
    }
}

ISR(USART0_RX_vect)
{
    cli();
    char data = UDR0;
}