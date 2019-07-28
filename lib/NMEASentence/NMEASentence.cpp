#include <NMEASentence.h>
#include <stdlib.h>
#include <string.h>

//
// Constructors and Destructor
//
NMEASentence::NMEASentence(void)
{
    _initialiseSentenceString();

    // initialise processing variables
    _readingStarted = false;
    _readingComplete = false;

    // initialise error code
    _errorCode = NMEASentenceErr_NoError;
}

NMEASentence::~NMEASentence(void)
{
    _freeSentenceString();
}

//
// Private Methods
//
void NMEASentence::_freeSentenceString(void)
{
    // clear memory occupied by string
    free(_sentenceString);
    _sentenceString = NULL;
    _sentenceStringUsedSize = 0;
}

void NMEASentence::_initialiseSentenceString(void)
{
    // initialise string data
    _sentenceString = (char *)malloc(maxSentenceStringSize * sizeof(char));
    _sentenceString[0] = '\0';
    _sentenceStringUsedSize = 0;
}

void NMEASentence::_addSentenceStringChar(char c)
{
    if (_sentenceStringNoSpaceLeft())
    {
        return;
    }
    _sentenceString[_sentenceStringUsedSize] = c;
    _sentenceStringUsedSize++;
    _sentenceString[_sentenceStringUsedSize] = '\0';
}

bool NMEASentence::_sentenceStringNoSpaceLeft(void)
{
    return _sentenceStringUsedSize == maxSentenceStringSize;
}

//
// Getters and Setters
//
char *NMEASentence::string(void)
{
    return _sentenceString;
}
bool NMEASentence::readingStarted(void)
{
    return _readingStarted;
}

bool NMEASentence::readingComplete(void)
{
    return _readingComplete;
}

char NMEASentence::errorCode(void)
{
    return _errorCode;
}

char *NMEASentence::talkerIdentifier(void)
{
    return _talkerIdentifier;
};
char *NMEASentence::sentenceIdentifier(void)
{
    return _sentenceIdentifier;
};

//
// Other Methods
//
void NMEASentence::reset(void)
{
    _freeSentenceString();
    _initialiseSentenceString();

    _readingStarted = false;
    _readingComplete = false;
    _errorCode = NMEASentenceErr_NoError;
}

void NMEASentence::readChar(char c)
{
    if (_readingComplete)
    {
        // if reading is already complete, do not do anything
        // the sentence needs to be reset before more reading can take place
        return;
    }

    if (_readingStarted)
    {
        // if reading has already started

        // check that there is space left in the string
        if (_sentenceStringNoSpaceLeft())
        {
            // if there is no space left at this point,
            // then we have run out of space while the
            // message is being read and so the message didn't
            // end in the alloted memory of 75 bytes
            _errorCode = NMEASentenceErr_MessageDidntEnd;
            return;
        }

        if (!(c == '\n' | c == '\r'))
        {
            // if the new character is not an end of sentence marker
            // add the new character to the sentence string
            _addSentenceStringChar(c);
        }

        if (c == '\n')
        {
            // mark if this is the end of the sentence
            _readingComplete = true;

            // parse the read sentence
            _parse();
        }
    }
    else
    {
        // otherwise reading has not yet started,
        // check for the start string character
        if (c == '$')
        {
            // check that there is space left in the string
            if (_sentenceStringNoSpaceLeft())
            {
                // if there is no space in the string at this point
                // then the reading cannot start
                _errorCode = NMEASentenceErr_StringOutOfMemory;
                return;
            }

            // if this is the sentence start character
            // mark that reading has started
            _readingStarted = true;

            // add new character to string
            _addSentenceStringChar(c);
        }
    }
}

void NMEASentence::_parse(void)
{
    // check for minimum length
    if (strlen(_sentenceString) < 9)
    {
        _errorCode = NMEASentenceErr_ParseError_SentenceNotLongEnough;
        return;
    }

    // get a pointer to start of the checksum
    char *prtToChecksumStart = strchr(_sentenceString, '*');
    if (prtToChecksumStart == nullptr)
    {
        _errorCode = NMEASentenceErr_ParseError_ChecksumNotFound;
        return;
    }

    // confirm that the checksum is 2 characters long and at end of string
    if ((prtToChecksumStart - _sentenceString) != (strlen(_sentenceString) - 3))
    {
        _errorCode = NMEASentenceErr_ParseError_ChecksumNotLongEnough;
        return;
    }

    // increment prtToChecksumStart to point at first checksum char
    prtToChecksumStart++;

    // calculate checksum
    int calculatedChecksum = 0;
    for (int i = 1; i < strlen(_sentenceString) - 3; i++)
    {
        calculatedChecksum ^= _sentenceString[i];
    }

    // compare checksum
    if (calculatedChecksum != (int)strtol(prtToChecksumStart, NULL, 16))
    {
        _errorCode = NMEASentenceErr_ParseError_ChecksumIncorrect;
        return;
    }

    // get pointer to first separator
    char *ptrToFirstSeparator = strchr(_sentenceString, ',');
    if (ptrToFirstSeparator == nullptr)
    {
        _errorCode = NMEASentenceErr_ParseError_TalkerDecoding;
        return;
    }

    // check talker length
    if ((ptrToFirstSeparator - _sentenceString) != 6)
    {
        _errorCode = NMEASentenceErr_ParseError_TalkerDecoding;
        return;
    }

    // set talker and sentence identifiers
    _talkerIdentifier[0] = _sentenceString[1];
    _talkerIdentifier[1] = _sentenceString[2];
    _talkerIdentifier[2] = '\0';
    _sentenceIdentifier[0] = _sentenceString[3];
    _sentenceIdentifier[1] = _sentenceString[4];
    _sentenceIdentifier[2] = _sentenceString[5];
    _sentenceIdentifier[3] = '\0';
}

// Typical sentence format:
// $GNGGA,112738.000,2608.9935,S,02808.1064,E,1,06,1.7,1640.8,M,0.0,M,,*51
gpsReading processGPSNMEASentence(NMEASentence &sentence)
{
    gpsReading reading;
    reading.error = NMEASentenceErr_processGPSNMEASentence_NoError;

    // reading.error = NMEASentenceErr_processGPSNMEASentence_BlankReading;

    return reading;
}

/**

  union {
    float f;
    unsigned char b[4];
  } lat;

  union {
    float f;
    unsigned char b[4];
  } lon;

  lat.f = -1 * (String("26").toFloat() + String("08.9986").toFloat() / 60.0);
  lon.f = String("028").toFloat() + String("08.1069").toFloat() / 60.0;

  for (int i = 0; i < 4; i++)
  {
    sSerial.print((char)lat.b[i]);
  }
  for (int i = 0; i < 4; i++)
  {
    sSerial.print((char)lon.b[i]);
  }

  // 200518.000,2608.9986,S,02808.1069,E,1,06,3.8,1640.3,M,0.0,M,, - 52
  // -26.1499766667, 28.135115
  // initialize serial:

  // 27 33 D1 C1
  // B7 14 E1 41
  // 27 33 d1 c1
  // b7 14 e1 41
  // 41542453463d2733d1c1b714e1a
  // 41542453463d2733d1c1b714a
  // 41542453463d2733d1a

  // 0110 1011 1011 1010


 */