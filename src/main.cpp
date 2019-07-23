#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <util/delay.h>

// ********************* Sleep *********************
void goToSleep(void);
char sleepCounterInitialised __attribute__((section(".noinit")));
int sleepCounter __attribute__((section(".noinit")));
#define sleepCounterInitialisedValue '!'
#define sleepCounterMin 0
#define sleepCounterMax 1

// ******************** Program Loop ********************
void program(void);
#define programStepWaitingForGPSFix 'a'
#define programStepGPSFixSuccess 'b'
#define programStepGPSFixFailure 'c'
#define programStepTransmit 'd'
char programStep;

// ********************* Setup/Teardown *********************
void onceOffSetup(void);
void recurringHardwareSetup(void);
void recurringHardwareTeardown(void);

// ********************* USART *********************
#define BAUD 9600
#define UBRR ((F_CPU / (16UL * BAUD)) - 1)
void USART_Setup(unsigned int baud);
void USART_Teardown();
void USART_Transmit(unsigned char data);

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
            USART_Transmit('t');
            USART_Transmit('t');
            _delay_ms(1); // todo, find a way to remove this
            recurringHardwareTeardown();
            sleepCounter = sleepCounterMin;
        }
    }

    return 0;
}

// ******************** Program Loop ********************
void program(void)
{
}

// ********************* Sleep *********************
void goToSleep(void)
{
    // set sleep mode to complete power down
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    // enable sleep mode
    sleep_enable();

    // enable watchdog timer with interrupt and maximum clock cycle
    // WDTCSR |= (1 << WDE) | (1 << WDIE) | (1 << WDP3) | (1 << WDP2) | (1 << WDP1) | (1 << WDP0); // 8.0 s
    WDTCSR |= (1 << WDE) | (1 << WDIE) | (1 << WDP2) | (1 << WDP1) | (1 << WDP0); // 2.0 s

    sei(); // ensure interrupts enabled so that the device can wake up again

    // put processor to sleep
    sleep_cpu();

    // when processor wakes execution will continue from here
    sleep_disable();
}
ISR(WDT_vect)
{
}

// ********************* Setup/Teardown *********************
void onceOffSetup(void)
{
    // check if the sleep counter has been initialised
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

    USART_Setup(UBRR);
}

void recurringHardwareTeardown(void)
{
    // turn led off to show device is off
    PORTB &= ~((1 << PB2));

    USART_Teardown();
}

// ********************* USART *********************
void USART_Setup(unsigned int ubrr)
{
    // Set baud rate
    UBRR0H = (unsigned char)(ubrr >> 8);
    UBRR0L = (unsigned char)ubrr;
    // Enable receiver and transmitter as well as RX complete interrupt
    UCSR0B = (1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0);
    // Set frame format: 8data, 2stop bit
    UCSR0C = (1 << USBS0) | (3 << UCSZ00);
}

void USART_Teardown(void)
{
    // Disable receiver and transmitter as well as RX complete interrupt
    UCSR0B &= ~((1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0));
}

void USART_Transmit(unsigned char data)
{
    // Wait for empty transmit buffer
    while (!(UCSR0A & (1 << UDRE0)))
    {
    }
    // Put data into buffer, sends the data
    UDR0 = data;
}

ISR(USART0_RX_vect)
{
    /* Get and return received data from buffer */
    char data = UDR0;
    USART_Transmit(data);
    PORTB ^= (1 << PB2);
}