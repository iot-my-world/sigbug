#include <NMEASentence.h>
#include <stdlib.h>
#include <string.h>

//
// Constructors and Destructor
//
NMEASentence::NMEASentence(void)
{
    initialiseSentenceString();

    // initialise processing variables
    readingStarted = false;
    readingComplete = false;

    // initialise error code
    errorCode = NMEASentenceErr_NoError;
}

NMEASentence::~NMEASentence(void)
{
}

//
// Private Methods
//
void NMEASentence::initialiseSentenceString(void)
{
    // initialise string data
    sentenceString[0] = '\0';
    sentenceStringUsedSize = 0;
}

void NMEASentence::addSentenceStringChar(char c)
{
    if (sentenceStringNoSpaceLeft())
    {
        return;
    }
    sentenceString[sentenceStringUsedSize] = c;
    sentenceStringUsedSize++;
    sentenceString[sentenceStringUsedSize] = '\0';
}

bool NMEASentence::sentenceStringNoSpaceLeft(void)
{
    return sentenceStringUsedSize == maxSentenceStringSize;
}

//
// Getters and Setters
//
char *NMEASentence::string(void)
{
    return sentenceString;
}

//
// Other Methods
//
void NMEASentence::reset(void)
{
    initialiseSentenceString();

    readingStarted = false;
    readingComplete = false;
    errorCode = NMEASentenceErr_NoError;
}

void NMEASentence::readChar(char c)
{
    if (readingComplete)
    {
        // if reading is already complete, do not do anything
        // the sentence needs to be reset before more reading can take place
        return;
    }

    if (readingStarted)
    {
        // if reading has already started

        // check that there is space left in the string
        if (sentenceStringNoSpaceLeft())
        {
            // if there is no space left at this point,
            // then we have run out of space while the
            // message is being read and so the message didn't
            // end in the alloted memory of 75 bytes
            errorCode = NMEASentenceErr_MessageDidntEnd;
            return;
        }

        if (!(c == '\n' | c == '\r'))
        {
            // if the new character is not an end of sentence marker
            // add the new character to the sentence string
            addSentenceStringChar(c);
        }

        if (c == '\n')
        {
            // mark if this is the end of the sentence
            readingComplete = true;

            // parse the read sentence
            parse();
        }
    }
    else
    {
        // otherwise reading has not yet started,
        // check for the start string character
        if (c == '$')
        {
            // check that there is space left in the string
            if (sentenceStringNoSpaceLeft())
            {
                // if there is no space in the string at this point
                // then the reading cannot start
                errorCode = NMEASentenceErr_StringOutOfMemory;
                return;
            }

            // if this is the sentence start character
            // mark that reading has started
            readingStarted = true;

            // add new character to string
            addSentenceStringChar(c);
        }
    }
}

void NMEASentence::parse(void)
{
    // check for minimum length
    if (strlen(sentenceString) < 9)
    {
        errorCode = NMEASentenceErr_ParseError_SentenceNotLongEnough;
        return;
    }

    // get a pointer to start of the checksum
    char *prtToChecksumStart = strchr(sentenceString, '*');
    if (prtToChecksumStart == nullptr)
    {
        errorCode = NMEASentenceErr_ParseError_ChecksumNotFound;
        return;
    }

    // confirm that the checksum is 2 characters long and at end of string
    if ((prtToChecksumStart - sentenceString) != (strlen(sentenceString) - 3))
    {
        errorCode = NMEASentenceErr_ParseError_ChecksumNotLongEnough;
        return;
    }

    // increment prtToChecksumStart to point at first checksum char
    prtToChecksumStart++;

    // calculate checksum
    int calculatedChecksum = 0;
    for (int i = 1; i < strlen(sentenceString) - 3; i++)
    {
        calculatedChecksum ^= sentenceString[i];
    }

    // compare checksum
    if (calculatedChecksum != (int)strtol(prtToChecksumStart, NULL, 16))
    {
        errorCode = NMEASentenceErr_ParseError_ChecksumIncorrect;
        return;
    }

    // get pointer to first separator
    char *ptrToFirstSeparator = strchr(sentenceString, ',');
    if (ptrToFirstSeparator == nullptr)
    {
        errorCode = NMEASentenceErr_ParseError_TalkerDecoding;
        return;
    }

    // check talker length
    if ((ptrToFirstSeparator - sentenceString) != 6)
    {
        errorCode = NMEASentenceErr_ParseError_TalkerDecoding;
        return;
    }

    // set talker and sentence identifiers
    talkerIdentifier[0] = sentenceString[1];
    talkerIdentifier[1] = sentenceString[2];
    talkerIdentifier[2] = '\0';
    sentenceIdentifier[0] = sentenceString[3];
    sentenceIdentifier[1] = sentenceString[4];
    sentenceIdentifier[2] = sentenceString[5];
    sentenceIdentifier[3] = '\0';
}

/*
    process_GNRMC_NMEASentence processes sentences with the following format:
    $GNRMC,160830.000,V,2608.9781,S,02808.0972,E,0.00,0.00,,,,A*73
    returns a gpsReading
*/
gpsReading process_GNRMC_NMEASentence(NMEASentence &sentence)
{
    gpsReading reading;
    reading.error = NMEASentenceErr_processGPSNMEASentence_NoError;
    reading.lat.f = 0;
    reading.lon.f = 0;

    char *nextCommaPointer;

    nextCommaPointer = strtok(sentence.string(), ",");
    int idx = 0;
    while (nextCommaPointer != NULL)
    {
        switch (idx)
        {
        case 3:
            reading.lat.f = atof(nextCommaPointer);
            break;

        case 4:
            reading.latDirection = nextCommaPointer[0];
            break;

        case 5:
            reading.lon.f = atof(nextCommaPointer);
            break;

        case 6:
            reading.lonDirection = nextCommaPointer[0];
            break;

        default:
            break;
        }
        idx++;
        nextCommaPointer = strtok(NULL, ",");
    }

    if ((reading.lat.f == 0) || (reading.lon.f == 0))
    {
        reading.error = NMEASentenceErr_processGPSNMEASentence_BlankReading;
        return reading;
    }

    if (reading.latDirection == 'S')
    {
        reading.lat.f *= -1;
    }

    if (reading.lonDirection == 'W')
    {
        reading.lon.f *= -1;
    }

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