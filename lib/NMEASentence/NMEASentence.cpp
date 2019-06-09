#include <Arduino.h>
#include <NMEASentence.h>

NMEASentence::NMEASentence(String rawNMEASentence)
{
    _raw = rawNMEASentence;
};

String NMEASentence::raw()
{
    return _raw;
};