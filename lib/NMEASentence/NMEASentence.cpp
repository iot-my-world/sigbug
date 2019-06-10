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
    // assume that the nmea sentence is invalid to start off with
    _valid = false;
    if (_raw.indexOf('$') != 0)
    {
    }
};