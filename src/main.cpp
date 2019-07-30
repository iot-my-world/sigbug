#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <avr/cpufunc.h>
#include <util/delay.h>
#include <string.h>
#include <USART.h>
#include <WDT.h>
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
char programStep;
#define programStepStart 'a'
#define programStepWaitingForGPSFix 'b'
NMEASentence nmeaSentence = NMEASentence();
int noNMEASentencesRead;
gpsReading readingToTransmit;
char sigfoxMessage[11];
#define programStepTransmit 'c'
#define programStepDone 'd'

// ********************* Hardware Setup/Teardown *********************
void onceOffSetup(void);
void recurringHardwareSetup(void);
void recurringHardwareTeardown(void);

// ********************* Pin Definitions *********************
#define awakeLedPin PB2
#define gpsSwitchPin PA7
#define debugLedPin PA3

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
        startGPSUSART();
        noNMEASentencesRead = 0;
        resetNMEASentence(&nmeaSentence);
        programStep = programStepWaitingForGPSFix;
        break;

    case programStepWaitingForGPSFix:
        _NOP();
        break;

    case programStepTransmit:
        startSigfoxUSART();
        if (readingToTransmit.error == NMEASentenceErr_processGPSNMEASentence_NoError)
        {
            for (int i = 0; i < 4; i++)
            {
                sigfoxMessage[i] = readingToTransmit.lat.b[i];
            }
            for (int i = 4; i < 8; i++)
            {
                sigfoxMessage[i] = readingToTransmit.lon.b[i - 4];
            }
            sigfoxMessage[8] = '\r';
            sigfoxMessage[9] = '\n';
            sigfoxMessage[10] = '\0';
            transmitStringSigfoxUSART(sigfoxMessage);
        }
        else
        {
            transmitCharSigfoxUSART('F');
            transmitCharSigfoxUSART('\n');
        }
        stopSigfoxUSART();
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
    DDRA |= (1 << debugLedPin);
}

void recurringHardwareSetup(void)
{
    // turn led on to show device is on
    PORTB |= (1 << awakeLedPin);

    // turn gps on
    PORTA |= (1 << gpsSwitchPin);
}

void recurringHardwareTeardown(void)
{
    // turn led off to show device is off
    PORTB &= ~((1 << awakeLedPin));

    // turn gps off
    PORTA &= ~((1 << gpsSwitchPin));
}

// on receipt of new character from gps chip
ISR(GPS_USART_RX_INT)
{
    // disable interrupts while this routine executes
    cli();

    // read the new char into the nmeaSentence
    nmeaSentence.readChar(UDR1);

    // check if any errors arose from reading the next char
    if (nmeaSentence.errorCode != NMEASentenceErr_NoError)
    {
        // if there is an error

        // increase the number of sentences read
        noNMEASentencesRead++;
        // reset the nmea sentence
        resetNMEASentence(&nmeaSentence);
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
                readingToTransmit = process_GNRMC_NMEASentence(nmeaSentence);

                // check for an error in the reading returned
                if (readingToTransmit.error == NMEASentenceErr_processGPSNMEASentence_NoError)
                {
                    // if there is no error, this step is done
                    programStep = programStepTransmit;
                }
                else
                {
                    // if there is an error

                    // increase the number of sentences read
                    noNMEASentencesRead++;
                    // reset the nmea sentence
                    resetNMEASentence(&nmeaSentence);
                }

                // increase the number of sentences read
                noNMEASentencesRead++;
                // reset the nmea sentence
                resetNMEASentence(&nmeaSentence);
            }
            else
            {
                // done - no

                // increase the number of sentences read
                noNMEASentencesRead++;
                // reset the nmea sentence
                resetNMEASentence(&nmeaSentence);
            }
        }
    }

    if (noNMEASentencesRead == 200)
    {
        programStep = programStepTransmit;
    }

    if (programStep != programStepWaitingForGPSFix)
    {
        noNMEASentencesRead = 0;
        stopGPSUSART();
    }
}

ISR(USART0_RX_vect)
{
    cli();
    char data = UDR0;
    // transmitCharSigfoxUSART('#');
}