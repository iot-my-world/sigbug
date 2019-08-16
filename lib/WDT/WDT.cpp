#include <WDT.h>
#include <avr/wdt.h>
#include <avr/interrupt.h>

/*
  wdtSetup is a set up function for the watchdog timer
*/
void wdtSetup(void)
{
  cli(); // disable interrupts

  MCUSR &= ~(1 << WDRF); // clear watchdog system reset flag

  wdt_reset(); // reset watchdog timer

  // Set WDCE and WDE bits to allow WDT configuration
  // (To clear the WDE bit, and/or change the prescaler bits, WDCE must be set.)
  WDTCSR |= (1 << WDCE) | (1 << WDE);

  // Apply WDT Configuration:
  // Interrupt enabled: WDIE = 1
  // Reset Disabled:    WDE = 0
  // 8 second interval: WDP3,2,1,0 = 1001
  // WDTCSR = (1 << WDIE) | (1 << WDP3) | (1 << WDP0); // 8 second - WDP3,2,1,0 = 1001
  WDTCSR = (1 << WDIE) | (1 << WDP2) | (1 << WDP1) | (1 << WDP0); // 2 second - WDP3,2,1,0 = 0111

  sei(); // re-enable interrupts
}