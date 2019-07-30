#include <USART.h>
#include <avr/io.h>
#include <string.h>

// ******************** GPS USART ********************
void initGPSUSART(void)
{
    // Set baud rate
    UBRR1H = (unsigned char)(((F_CPU / (16UL * 9600)) - 1) >> 8);
    UBRR1L = (unsigned char)((F_CPU / (16UL * 9600)) - 1);
    // Set frame format: 8data, 1 stop bit
    UCSR1C = (3 << UCSZ10);
}

void startGPSUSART(void)
{
    // Enable receiver and RX complete interrupt
    UCSR1B = (1 << RXEN0) | (1 << RXCIE0);
}

void stopGPSUSART(void)
{
    // Disable receiver and RX complete interrupt
    UCSR1B &= ~((1 << RXEN1) | (1 << RXCIE1));
}

void flushGPSUSART(void)
{
    unsigned char dummy;
    while (UCSR1A & (1 << RXC1))
    {
        dummy = UDR1;
    }
};

// ******************** Sigfox USART ********************
void initSigfoxUSART(void)
{
    // Set baud rate
    UBRR0H = (unsigned char)(((F_CPU / (16UL * 9600)) - 1) >> 8);
    UBRR0L = (unsigned char)((F_CPU / (16UL * 9600)) - 1);
    // Set frame format: 8data, 2stop bit
    UCSR0C = (1 << USBS0) | (3 << UCSZ00);
}

void startSigfoxUSART(void)
{
    // Enable receiver and transmitter as well as RX complete interrupt
    // UCSR0B = (1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0);
    UCSR0B = (1 << TXEN0);
}

void stopSigfoxUSART(void)
{
    // Disable receiver and transmitter as well as RX complete interrupt
    UCSR0B &= ~((1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0));
}

void flushSigfoxUSART(void)
{
    unsigned char dummy;
    while (UCSR0A & (1 << RXC0))
    {
        dummy = UDR0;
    }
};

void transmitStringSigfoxUSART(char *data)
{
    for (int i = 0; i < strlen(data); i++)
    {
        transmitCharSigfoxUSART(data[i]);
    }
}

void transmitCharSigfoxUSART(char data)
{
    // Wait for empty transmit buffer
    while (!(UCSR0A & (1 << UDRE0)))
    {
    }
    // Put data into buffer, sends the data
    UDR0 = data;
};