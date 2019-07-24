#include <USART.h>
#include <avr/io.h>

//
// Constructors
//
USART::USART(int baud, char usartNo)
{
    _baud = baud;
    _usartNo = usartNo;
};

//
// Destructor
//
USART::~USART(){};

//
// Other Methods
//
void USART::Start()
{
    switch (_usartNo)
    {
    case '0':
        start0();
        break;

    case '1':
        start1();
        break;

    default:
        break;
    }
};

void USART::start0(void)
{
    // Set baud rate
    UBRR0H = (unsigned char)(((F_CPU / (16UL * _baud)) - 1) >> 8);
    UBRR0L = (unsigned char)((F_CPU / (16UL * _baud)) - 1);
    // Enable receiver and transmitter as well as RX complete interrupt
    UCSR0B = (1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0);
    // Set frame format: 8data, 2stop bit
    UCSR0C = (1 << USBS0) | (3 << UCSZ00);
};

void USART::start1(void){

};

void USART::Stop()
{
    switch (_usartNo)
    {
    case '0':
        stop0();
        break;

    case '1':
        stop1();
        break;

    default:
        break;
    }
};

void USART::stop0(void)
{
    // Disable receiver and transmitter as well as RX complete interrupt
    UCSR0B &= ~((1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0));
};

void USART::stop1(void)
{
    // Disable receiver and transmitter as well as RX complete interrupt
    UCSR1B &= ~((1 << RXEN1) | (1 << TXEN1) | (1 << RXCIE1));
};

void USART::Flush(void)
{
    switch (_usartNo)
    {
    case '0':
        flush0();
        break;

    case '1':
        flush1();
        break;

    default:
        break;
    }
};

void USART::flush0(void)
{
    unsigned char dummy;
    while (UCSR0A & (1 << RXC0))
    {
        dummy = UDR0;
    }
};

void USART::flush1(void)
{
    unsigned char dummy;
    while (UCSR1A & (1 << RXC1))
    {
        dummy = UDR1;
    }
};

void USART::Transmit(char data)
{
    switch (_usartNo)
    {
    case '0':
        transmit0(data);
        break;

    case '1':
        transmit1(data);
        break;

    default:
        break;
    }
};

void USART::transmit0(char data)
{
    // Wait for empty transmit buffer
    while (!(UCSR0A & (1 << UDRE0)))
    {
    }
    // Put data into buffer, sends the data
    UDR0 = data;
};

void USART::transmit1(char data)
{
    // Wait for empty transmit buffer
    while (!(UCSR1A & (1 << UDRE1)))
    {
    }
    // Put data into buffer, sends the data
    UDR1 = data;
};