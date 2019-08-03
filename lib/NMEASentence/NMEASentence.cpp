#include <NMEASentence.h>
#include <stdlib.h>
#include <string.h>

void initialiseNMEASentence(NMEASentence *nmeaSentence)
{
    // initialise processing variables
    (*nmeaSentence).readingStarted = false;
    (*nmeaSentence).readingComplete = false;

    // initialise error code
    (*nmeaSentence).errorCode = NMEASentenceErr_NoError;

    // initialise string data
    (*nmeaSentence).sentenceString[0] = '\0';
    (*nmeaSentence).sentenceStringUsedSize = 0;

    (*nmeaSentence).sentenceIdentifier[0] = '\0';
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
    if (prtToChecksumStart == NULL)
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
    if (ptrToFirstSeparator == NULL)
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

/*
    process_GNRMC_NMEASentence processes sentences with the following format:
    $GNRMC,160830.000,V,2608.9781,S,02808.0972,E,0.00,0.00,,,,A*73
    returns a gpsReading
*/
void process_GNRMC_NMEASentence(NMEASentence *sentence, gpsReading *reading)
{
    // reset reading
    reading->error = NMEASentenceErr_processGPSNMEASentence_NoError;
    reading->lat.f = 0;
    reading->lon.f = 0;

    // pointer a part of the sentence separated by ,
    char *sentencePart;
    // pointer to . in coordinate
    char *coordinateDot = NULL;
    // counter to keep track of part of sentence
    int sentencePartIdx = 0;
    // difference between start of sentence part and .
    int diff;

    // start tokenisation at first ,
    sentencePart = strtok(sentence->sentenceString, ",");
    while (sentencePart != NULL)
    {
        // to parse degree value
        char degrees[] = "000";
        switch (sentencePartIdx)
        {
        case 3: // latitude value
        case 5: // longitude value
            coordinateDot = strchr(sentencePart, '.');
            if (coordinateDot != NULL)
            {
                diff = coordinateDot - sentencePart;
                for (int i = 0; i < diff - 2; i++)
                {
                    degrees[i + (5 - diff)] = sentencePart[i];
                }
                if (sentencePartIdx == 3)
                {
                    reading->lat.f = atof(degrees) + atof(coordinateDot - 2) / 60;
                }
                else
                {
                    reading->lon.f = atof(degrees) + atof(coordinateDot - 2) / 60;
                }
            }
            break;

        case 4: // latitude direction
            reading->latDirection = sentencePart[0];
            break;

        case 6: // longitude direction
            reading->lonDirection = sentencePart[0];
            break;

        default:
            break;
        }
        sentencePart = strtok(NULL, ",");
        sentencePartIdx++;
    }

    if (reading->latDirection == 'S')
    {
        reading->lat.f *= -1;
    }
    if (reading->lonDirection == 'W')
    {
        reading->lat.f *= -1;
    }

    if ((reading->lat.f == 0) || (reading->lon.f == 0))
    {
        reading->error = NMEASentenceErr_processGPSNMEASentence_BlankReading;
    }
}