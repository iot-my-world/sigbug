#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <util/delay.h>
#include <USART.h>
#include <WDT.h>
#include <string.h>

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

// ********************* USART *********************
USART USART0(9600, '0');
USART USART1(9600, '1');

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

    case programStepWaitingForGPSFix:
        if (gpsFixDone)
        {
            USART0.Flush();
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

    // initialise sleep counter if it hasn't been yet
    if (sleepCounterInitialised != sleepCounterInitialisedValue)
    {
        sleepCounter = sleepCounterMin;
    }

    // set up led pin as output
    DDRB |= (1 << PB2);
}

void recurringHardwareSetup(void)
{
    // turn led on to show device is on
    PORTB |= (1 << PB2);

    USART0.Start();
}

void recurringHardwareTeardown(void)
{
    // turn led off to show device is off
    PORTB &= ~((1 << PB2));

    USART0.Stop();
}

ISR(USART0_RX_vect)
{
    cli();
    char data = UDR0;

    if (waitingForStartOfNMEAWord)
    {
        // we are waiting for '$' which is the first character of an nmea word
        if (data == '$')
        {
            // this is the start of a word, mark that we are no longer waiting
            waitingForStartOfNMEAWord = false;

            // consume first char here
        }
    }
    else
    {
        // we are not waiting for the start of an NMEA word and so are busy consuming

        // consume next char here

        if (data == '\n')
        {
            // new line character indicates end of NMEA word
            gpsFixDone = true;
        }
    }
}