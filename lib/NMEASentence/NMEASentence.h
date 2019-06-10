/*
NMEASentence.h

A library to process and manipulate NMEA Sentences as defined by the
The NMEA 0183 Protocol.

The National Marine Electronics Association (NMEA) is a non-profit association of manufacturers,
distributors, dealers, educational institutions, and others interested in peripheral marine electronics
occupations. The NMEA 0183 standard defines an electrical interface and data protocol for
communications between marine instrumentation.
 */

#ifndef NMEASentence_h
#define NMEASentence_h

#include <Arduino.h>

class NMEASentence
{
private:
    // optional error logger
    void (*_logError)(String);

    // called by the various constructors
    void _initFromRaw();

    // raw nmea sentence data
    String _raw;
    String _checkSum;

public:
    //
    // Constructors and Destructor
    //
    NMEASentence(String rawNMEASentence);
    NMEASentence(String rawNMEASentence, void (*logError)(String));
    ~NMEASentence();

    //
    // Getters and Setters
    //
    String raw();
    String checkSum();
};

#endif