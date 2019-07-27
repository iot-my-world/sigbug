/*
NMEASentence

A library to process and manipulate NMEA Sentences as defined by the
The NMEA 0183 Protocol.

The National Marine Electronics Association (NMEA) is a non-profit association of manufacturers,
distributors, dealers, educational institutions, and others interested in peripheral marine electronics
occupations. The NMEA 0183 standard defines an electrical interface and data protocol for
communications between marine instrumentation.
 */

#ifndef NMEASentence_h
#define NMEASentence_h

#include <String.h>

#define NMEASentenceErr_NoError '0'
#define NMEASentenceErr_StringOutOfMemory '1'
#define NMEASentenceErr_MessageDidntEnd '2'

class NMEASentence
{
private:
    String _string = String(75);
    bool _readingStarted;
    bool _readingComplete;
    char _errorCode;

public:
    //
    // Constructors and Destructor
    //
    NMEASentence(void);
    ~NMEASentence(void);

    //
    // Getters and Setters
    //
    String string(void);
    bool readingStarted(void);
    bool readingComplete(void);
    char errorCode(void);

    //
    // Other Methods
    //
    void reset(void);
    void readChar(char c);
};

#endif