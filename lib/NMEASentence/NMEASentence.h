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
    bool _logErr;
    void (*_logError)(String);

    // called by the various constructors to perform
    // initialisation of the NMEA Message
    void _initFromRaw();

    // NMEA sentence data
    String _raw;
    String _checkSum;
    String _talkerIdentifier;
    String _sentenceIdentifier;
    String _sentenceData;

    bool _valid;

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
    String talkerIdentifier();
    String sentenceIdentifier();
    String sentenceData();
    bool valid();
};

#endif