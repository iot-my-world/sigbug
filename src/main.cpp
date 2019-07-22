#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>

#define BAUD 9600
#define UBRR ((F_CPU / (16UL * BAUD)) - 1)

void USART_Init(unsigned int baud);
void USART_Transmit(unsigned char data);

// https://www.microchip.com/webdoc/AVRLibcReferenceManual/mem_sections_1sec_dot_noinit.html
void goToSleep(void);
char sleepCounterInitialised __attribute__((section(".noinit")));
int sleepCounter __attribute__((section(".noinit")));
#define sleepCounterInitialisedValue '!'
#define sleepCounterMin 0
#define sleepCounterMax 1

#define programStepSetup 'a'
#define programStepWaitingForGPSFix 'b'
#define programStepGPSFixSuccess 'c'
#define programStepTransmit 'd'
#define programStepGoBackToSleep 'e'
char programStep;

int main(void)
{
    // check if the sleep counter has been initialised
    if (sleepCounterInitialised != sleepCounterInitialisedValue)
    {
        sleepCounter = sleepCounterMin;
    }

    // make the LED pin an output for PORTB5
    DDRB |= (1 << PB2);

    // // Setup 16 bit timer/counter 1
    // // Normal Mode of Operation
    // // Internal clock with 1024 prescaler
    // // TCCR1B |= (1 << CS12) | (1 << CS10);
    // // TCCR1B |= (1 << CS12);
    // // // Enable overflow interrupt
    // // TIMSK1 |= (1 << TOIE1);

    // // initialise usart
    // USART_Init(UBRR);

    // sei();

    while (1)
    {
        goToSleep();
        // if (sleepCounter <= sleepCounterMax)
        // {
        //     sleepCounter++;
        //     // device should go back to sleep
        //     goToSleep();
        //     // execution continues here after sleep
        // }
        // else
        // {
        //     // device should wake up

        //     // do some stuff
        // DDRB |= (1 << PB2);
        // PORTB ^= (1 << PB2);

        //     sleepCounter = sleepCounterMin;
        // }
    }

    return 0;
}

void goToSleep(void)
{
    // set sleep mode to complete power down
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    // enable sleep mode
    sleep_enable();

    // enable watchdog timer with interrupt and maximum clock cycle
    WDTCSR |= (1 << WDE) | (1 << WDIE) | (1 << WDP3) | (1 << WDP2) | (1 << WDP1) | (1 << WDP0);

    sei(); // ensure interrupts enabled so that the device can wake up again

    // put processor to sleep
    sleep_cpu();

    // when processor wakes execution will continue from here
    sleep_disable();
}

ISR(WDT_vect)
{
    DDRB |= (1 << PB2);
    PORTB ^= (1 << PB2);
}

// ISR(TIMER1_OVF_vect)
// {
//     PORTB ^= (1 << PB2);
//     USART_Transmit('!');
// }

ISR(USART0_RX_vect)
{
    /* Get and return received data from buffer */
    char data = UDR0;
    USART_Transmit(data);
    PORTB ^= (1 << PB2);
}

void USART_Init(unsigned int ubrr)
{
    // Set baud rate
    UBRR0H = (unsigned char)(ubrr >> 8);
    UBRR0L = (unsigned char)ubrr;
    // Enable receiver and transmitter as well as RX complete interrupt
    UCSR0B = (1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0);
    // Set frame format: 8data, 2stop bit
    UCSR0C = (1 << USBS0) | (3 << UCSZ00);
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