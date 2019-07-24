#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <util/delay.h>
#include <USART.h>

// ********************* Sleep *********************
void enableWDT(void);
void disableWDT(void);
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

void enableWDT(void)
{
    // enable watchdog timer with interrupt and maximum clock cycle
    WDTCSR |= ((1 << WDE) | (1 << WDIE));
}

void disableWDT(void)
{
    // clear WDRF in MCUSR
    MCUSR &= ~(1 << WDRF);
    // write signature for change enable of protected IO register
    CCP = 0xD8;
    // within four instruction cycles turn off WDT
    WDTCSR &= ~((1 << WDE) | (1 << WDIE));
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
    // Set up watchdog timer prescaler
    // WDTCSR |= ((1 << WDP3) | (1 << WDP2) | (1 << WDP1) | (1 << WDP0)); // 8.0 s
    WDTCSR |= ((1 << WDP2) | (1 << WDP1) | (1 << WDP0)); // 2.0 s

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
    /* Get and return received data from buffer */
    char data = UDR0;
    USART0.Transmit(data);
    if (data == '$')
    {
        gpsFixDone = true;
    }
}