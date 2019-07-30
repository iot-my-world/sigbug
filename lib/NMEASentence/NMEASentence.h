/*
NMEASentence

A library to process and manipulate NMEA Sentences as defined by the
The NMEA 0183 Protocol.

The National Marine Electronics Association (NMEA) is a non-profit association of manufacturers,
distributors, dealers, educational institutions, and others interested in peripheral marine electronics
occupations. The NMEA 0183 standard defines an electrical interface and data protocol for
communications between marine instrumentation.
 */

#ifndef NMEASentence_h
#define NMEASentence_h

#define maxSentenceStringSize 75

#define NMEASentenceErr_NoError '0'
#define NMEASentenceErr_StringOutOfMemory '1'
#define NMEASentenceErr_MessageDidntEnd '2'
#define NMEASentenceErr_ParseError_SentenceNotLongEnough '3'
#define NMEASentenceErr_ParseError_ChecksumNotFound '4'
#define NMEASentenceErr_ParseError_ChecksumNotLongEnough '5'
#define NMEASentenceErr_ParseError_ChecksumIncorrect '6'
#define NMEASentenceErr_ParseError_TalkerDecoding '7'

#define NMEASentenceErr_processGPSNMEASentence_NoError '8'
#define NMEASentenceErr_processGPSNMEASentence_BlankReading '9'

class NMEASentence
{
private:
public:
    char sentenceString[70];
    int sentenceStringUsedSize;
    void initialiseSentenceString(void);
    char talkerIdentifier[3];
    char sentenceIdentifier[4];

    bool readingStarted;
    bool readingComplete;
    char errorCode;
    void parse(void);

    //
    // Constructors and Destructor
    //
    NMEASentence(void);
    ~NMEASentence(void);

    //
    // Other Methods
    //
};

void resetNMEASentence(NMEASentence *sentence);
void addCharToNMEASentence(NMEASentence *sentence, char c);
void readCharForNMEASentence(NMEASentence *sentence, char c);

struct gpsReading
{
    union {
        float f;
        unsigned char b[4];
    } lat;
    char latDirection;
    union {
        float f;
        unsigned char b[4];
    } lon;
    char lonDirection;
    char error;
};

gpsReading process_GNRMC_NMEASentence(NMEASentence &inputSentence);

#endif