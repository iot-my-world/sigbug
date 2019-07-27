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

String NMEASentence::talkerIdentifier()
{
    return _talkerIdentifier;
};

String NMEASentence::sentenceIdentifier()
{
    return _sentenceIdentifier;
};

String NMEASentence::sentenceData()
{
    return _sentenceData;
};

bool NMEASentence::valid()
{
    return _valid;
};

//
// Other Methods
//

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
        }
        return;
    }

    // confirm presence of standard NMEA end characters
    if (!_raw.endsWith("\r\n"))
    {
        if (_logErr)
        {
            (*_logError)("NMEA Message init error, input does not end with <CR><LF>");
        }
        return;
    }

    // check if this is a proprietary message
    // this is not supported right now
    if (_raw.startsWith("$P"))
    {
        if (_logErr)
        {
            (*_logError)("NMEA Message init error, unsupported proprietary message");
        }
        return;
    }

    String sentenceBody = _raw.substring(1, _raw.indexOf('\r'));

    // check for checksum
    int checkSumIdx = sentenceBody.lastIndexOf("*");
    if (checkSumIdx > -1)
    {
        // confirm that sentence is long enough
        if (sentenceBody.length() != (unsigned int)(checkSumIdx + 3))
        {
            if (_logErr)
            {
                (*_logError)("NMEA Message init error, sentence body not long enough for checksum");
            }
            return;
        }
        // remove check sum
        _checkSum = sentenceBody.substring(checkSumIdx + 1);
        // update sentence body
        sentenceBody = sentenceBody.substring(0, checkSumIdx);

        // calculate required checksum
        caluclatedCheckSum = 0;
        for (uint8_t i = 0; i < sentenceBody.length(); i++)
        {
            caluclatedCheckSum ^= sentenceBody.charAt(i);
        }
        String checkSumString = String(caluclatedCheckSum, HEX);
        if (checkSumString.length() != 2)
        {
            checkSumString = "0" + checkSumString;
        }
        if (checkSumString != _checkSum)
        {
            if (_logErr)
            {
                (*_logError)("NMEA Message init error, checksum validation failed");
            }
            return;
        }
    }

    // check that there is at least 1 comma
    if (sentenceBody.indexOf(",") < 0)
    {
        if (_logErr)
        {
            (*_logError)("NMEA Message init error, no comma separator found");
        }
        return;
    }

    // separate string into id and data parts
    String ids = sentenceBody.substring(0, sentenceBody.indexOf(","));
    _sentenceData = sentenceBody.substring(sentenceBody.indexOf(",") + 1);

    // confirm that identifier length is correct
    if (ids.length() != 5)
    {
        if (_logErr)
        {
            (*_logError)("NMEA Message init error, ids string not long enough");
        }
        return;
    }
    // set talker and sentence identifier
    _talkerIdentifier = ids.substring(0, 2);
    _sentenceIdentifier = ids.substring(2);

    // decoding complete, mark message valid
    _valid = true;
};