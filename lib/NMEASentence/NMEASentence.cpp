#include <Arduino.h>
#include <NMEASentence.h>

//
// Constructors
//
NMEASentence::NMEASentence(String rawNMEASentence)
{
    _raw = rawNMEASentence;
    _initFromRaw();
};

NMEASentence::NMEASentence(String rawNMEASentence, void (*logError)(String))
{
    _logError = logError;
    _raw = rawNMEASentence;
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

void NMEASentence::_initFromRaw(){

};