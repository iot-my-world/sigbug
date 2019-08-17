#include <NMEASentence.h>

#ifndef TestCase_h
#define TestCase_h

typedef struct testCase
{
    const char *id;
    const char *inputTestString;
    bool expectedReadingStartIndication;
    bool expectedReadingCompleteIndication;
    char expectedPostReadingNMEASentenceErr;

    char expectedPostParse_NMEASentenceErr;
    const char *expectedNMEATalkerIdentifier;
    const char *expectedNMEASentenceIdentifier;

    gpsReading expectedGPSReading;
} testCase;

#endif