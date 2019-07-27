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

// ******************** GPS USART ********************
void initGPSUSART(void);
void startGPSUSART(void);
void stopGPSUSART(void);
void flushGPSUSART(void);

// ******************** Sigfox USART ********************
void initSigfoxUSART(void);
void startSigfoxUSART(void);
void stopSigfoxUSART(void);
void flushSigfoxUSART(void);
void transmitStringSigfoxUSART(char *data);
void transmitCharSigfoxUSART(char data);

#endif