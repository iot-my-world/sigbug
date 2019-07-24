#include <avr/io.h>

void setupWDT(void)
{
    // Set up watchdog timer prescaler
    // WDTCSR |= ((1 << WDP3) | (1 << WDP2) | (1 << WDP1) | (1 << WDP0)); // 8.0 s
    WDTCSR |= ((1 << WDP2) | (1 << WDP1) | (1 << WDP0)); // 2.0 s
};

void enableWDT(void)
{
    // enable watchdog timer with interrupt and maximum clock cycle
    WDTCSR |= ((1 << WDE) | (1 << WDIE));
};

void disableWDT(void)
{
    // clear WDRF in MCUSR
    MCUSR &= ~(1 << WDRF);
    // write signature for change enable of protected IO register
    CCP = 0xD8;
    // within four instruction cycles turn off WDT
    WDTCSR &= ~((1 << WDE) | (1 << WDIE));
};