#ifndef USART_h
#define USART_h

#ifndef F_CPU
/* prevent compiler error by supplying a default */
#warning "F_CPU not defined for <USART.h>"
/*
    this is required to perform baud rate calculation
 */
#define F_CPU 1000000UL
#endif

class USART
{
private:
    char _usartNo;
    int _baud;
    void start0(void);
    void stop0(void);
    void start1(void);
    void stop1(void);
    void flush0(void);
    void flush1(void);
    void transmit0(char data);
    void transmit1(char data);

public:
    //
    // Constructors and Destructor
    //
    USART(int baud, char usartNo);
    ~USART();

    void Start(void);
    void Stop(void);
    void Flush(void);
    void Transmit(char data);
};

#endif