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
    char _sentenceString[70];
    int _sentenceStringUsedSize;
    void _initialiseSentenceString(void);
    void _addSentenceStringChar(char c);
    bool _sentenceStringNoSpaceLeft(void);
    char _talkerIdentifier[3];
    char _sentenceIdentifier[4];

    bool _readingStarted;
    bool _readingComplete;
    char _errorCode;
    void _parse(void);

public:
    //
    // Constructors and Destructor
    //
    NMEASentence(void);
    ~NMEASentence(void);

    //
    // Getters and Setters
    //
    char *string(void);
    bool readingStarted(void);
    bool readingComplete(void);
    char errorCode(void);
    char *talkerIdentifier(void);
    char *sentenceIdentifier(void);

    //
    // Other Methods
    //
    void reset(void);
    void readChar(char c);
};

struct gpsReading
{
    union {
        float f;
        unsigned char b[4];
    } lat;
    union {
        float f;
        unsigned char b[4];
    } lon;
    char error;
};

gpsReading processGPSNMEASentence(NMEASentence &inputSentence);

#endif