#include <Arduino.h>
#include <NMEASentence.h>

//
// Constructors
//
NMEASentence::NMEASentence(String rawNMEASentence)
{
    _raw = rawNMEASentence;
    _logErr = false;
    _initFromRaw();
};

NMEASentence::NMEASentence(String rawNMEASentence, void (*logError)(String))
{
    _logError = logError;
    _raw = rawNMEASentence;
    _logErr = true;
    _initFromRaw();
};

//
// Destructor
//
NMEASentence::~NMEASentence(){};

//
// Getters and Setters
//
String NMEASentence::raw()
{
    return _raw;
};

String NMEASentence::checkSum()
{
    return _checkSum;
};

bool NMEASentence::valid()
{
    return _valid;
};

void NMEASentence::_initFromRaw()
{
    // assume that the NMEA sentence is invalid to start off with
    _valid = false;

    // confirm presence of standard NMEA start character
    if (!_raw.startsWith("$"))
    {
        if (_logErr)
        {
            (*_logError)("NMEA Message init error, input does not start with $");
            return;
        }
    }

    // confirm presence of standard NMEA end characters
    if (!_raw.endsWith("\r\n"))
    {
        if (_logErr)
        {
            (*_logError)("NMEA Message init error, input does not end with <CR><LF>");
            return;
        }
    }
};