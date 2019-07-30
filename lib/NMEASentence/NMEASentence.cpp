#include <NMEASentence.h>
#include <stdlib.h>
#include <string.h>

void resetNMEASentence(NMEASentence *sentence)
{
    (*sentence).sentenceIdentifier[0] = '\0';
    (*sentence).sentenceStringUsedSize = 0;
    (*sentence).readingStarted = false;
    (*sentence).readingComplete = false;
    (*sentence).errorCode = NMEASentenceErr_NoError;
}

void addCharToNMEASentence(NMEASentence *sentence, char c)
{
    if ((*sentence).sentenceStringUsedSize == maxSentenceStringSize)
    {
        return;
    }
    (*sentence).sentenceString[(*sentence).sentenceStringUsedSize] = c;
    (*sentence).sentenceStringUsedSize++;
    (*sentence).sentenceString[(*sentence).sentenceStringUsedSize] = '\0';
}

void readCharForNMEASentence(NMEASentence *sentence, char c)
{
    if ((*sentence).readingComplete)
    {
        // if reading is already complete, do not do anything
        // the sentence needs to be reset before more reading can take place
        return;
    }

    if ((*sentence).readingStarted)
    {
        // if reading has already started

        // check that there is space left in the string
        if ((*sentence).sentenceStringUsedSize == maxSentenceStringSize)
        {
            // if there is no space left at this point,
            // then we have run out of space while the
            // message is being read and so the message didn't
            // end in the alloted memory of 75 bytes
            (*sentence).errorCode = NMEASentenceErr_MessageDidntEnd;
            return;
        }

        if (!(c == '\n' | c == '\r'))
        {
            // if the new character is not an end of sentence marker
            // add the new character to the sentence string
            addCharToNMEASentence(sentence, c);
        }

        if (c == '\n')
        {
            // mark if this is the end of the sentence
            (*sentence).readingComplete = true;

            // parse the read sentence
            parseNMEASentence(sentence);
        }
    }
    else
    {
        // otherwise reading has not yet started,
        // check for the start string character
        if (c == '$')
        {
            // check that there is space left in the string
            if ((*sentence).sentenceStringUsedSize == maxSentenceStringSize)
            {
                // if there is no space in the string at this point
                // then the reading cannot start
                (*sentence).errorCode = NMEASentenceErr_StringOutOfMemory;
                return;
            }

            // if this is the sentence start character
            // mark that reading has started
            (*sentence).readingStarted = true;

            // add new character to string
            addCharToNMEASentence(sentence, c);
        }
    }
}

void parseNMEASentence(NMEASentence *sentence)
{
    // check for minimum length
    if (strlen((*sentence).sentenceString) < 9)
    {
        (*sentence).errorCode = NMEASentenceErr_ParseError_SentenceNotLongEnough;
        return;
    }

    // get a pointer to start of the checksum
    char *prtToChecksumStart = strchr((*sentence).sentenceString, '*');
    if (prtToChecksumStart == nullptr)
    {
        (*sentence).errorCode = NMEASentenceErr_ParseError_ChecksumNotFound;
        return;
    }

    // confirm that the checksum is 2 characters long and at end of string
    if ((prtToChecksumStart - (*sentence).sentenceString) != (strlen((*sentence).sentenceString) - 3))
    {
        (*sentence).errorCode = NMEASentenceErr_ParseError_ChecksumNotLongEnough;
        return;
    }

    // increment prtToChecksumStart to point at first checksum char
    prtToChecksumStart++;

    // calculate checksum
    int calculatedChecksum = 0;
    for (int i = 1; i < strlen((*sentence).sentenceString) - 3; i++)
    {
        calculatedChecksum ^= (*sentence).sentenceString[i];
    }

    // compare checksum
    if (calculatedChecksum != (int)strtol(prtToChecksumStart, NULL, 16))
    {
        (*sentence).errorCode = NMEASentenceErr_ParseError_ChecksumIncorrect;
        return;
    }

    // get pointer to first separator
    char *ptrToFirstSeparator = strchr((*sentence).sentenceString, ',');
    if (ptrToFirstSeparator == nullptr)
    {
        (*sentence).errorCode = NMEASentenceErr_ParseError_TalkerDecoding;
        return;
    }

    // check talker length
    if ((ptrToFirstSeparator - (*sentence).sentenceString) != 6)
    {
        (*sentence).errorCode = NMEASentenceErr_ParseError_TalkerDecoding;
        return;
    }

    // set talker and sentence identifiers
    (*sentence).talkerIdentifier[0] = (*sentence).sentenceString[1];
    (*sentence).talkerIdentifier[1] = (*sentence).sentenceString[2];
    (*sentence).talkerIdentifier[2] = '\0';
    (*sentence).sentenceIdentifier[0] = (*sentence).sentenceString[3];
    (*sentence).sentenceIdentifier[1] = (*sentence).sentenceString[4];
    (*sentence).sentenceIdentifier[2] = (*sentence).sentenceString[5];
    (*sentence).sentenceIdentifier[3] = '\0';
}

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

//
// Other Methods
//

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

    nextCommaPointer = strtok(sentence.sentenceString, ",");
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