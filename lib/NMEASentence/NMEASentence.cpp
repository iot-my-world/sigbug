#include <Arduino.h>
#include <NMEASentence.h>

NMEASentence::NMEASentence(String rawNMEASentence)
{
    _raw = rawNMEASentence;
};

NMEASentence::~NMEASentence(){};

String NMEASentence::raw()
{
    return _raw;
};