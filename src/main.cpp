#include <avr/io.h>
#include <avr/interrupt.h>

#define BAUD 9600
#define UBRR ((F_CPU / (16UL * BAUD)) - 1)

void USART_Init(unsigned int baud);
void USART_Transmit(unsigned char data);

int main(void)
{
    // make the LED pin an output for PORTB5
    DDRB |= (1 << PB2);

    // Setup 16 bit timer/counter 1
    // Normal Mode of Operation
    // Internal clock with 1024 prescaler
    // TCCR1B |= (1 << CS12) | (1 << CS10);
    TCCR1B |= (1 << CS12);
    // Enable overflow interrupt
    TIMSK1 |= (1 << TOIE1);

    // initialise usart
    USART_Init(UBRR);

    sei();

    while (1)
    {
    }

    return 0;
}

ISR(TIMER1_OVF_vect)
{
    PORTB ^= (1 << PB2);
    USART_Transmit('!');
}

void USART_Init(unsigned int ubrr)
{
    /* Set baud rate */
    UBRR0H = (unsigned char)(ubrr >> 8);
    UBRR0L = (unsigned char)ubrr;
    /* Enable receiver and transmitter */
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);
    /* Set frame format: 8data, 2stop bit */
    UCSR0C = (1 << USBS0) | (3 << UCSZ00);
}

void USART_Transmit(unsigned char data)
{
    /* Wait for empty transmit buffer */
    while (!(UCSR0A & (1 << UDRE0)))
    {
    }
    /* Put data into buffer, sends the data */
    UDR0 = data;
}