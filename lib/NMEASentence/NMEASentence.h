/*
NMEASentence

A library to process and manipulate NMEA Sentences as defined by the
The NMEA 0183 Protocol.

The National Marine Electronics Association (NMEA) is a non-profit association of manufacturers,
distributors, dealers, educational institutions, and others interested in peripheral marine electronics
occupations. The NMEA 0183 standard defines an electrical interface and data protocol for
communications between marine instrumentation.
 */
#include <stdbool.h>

#ifndef NMEASentence_h
#define NMEASentence_h

#define maxSentenceStringSize 75

#define NMEASentenceErr_NoError '0'
#define NMEASentenceErr_MessageDidntStart '1'
#define NMEASentenceErr_MessageDidntEnd '2'
#define NMEASentenceErr_StringOutOfMemory '3'
#define NMEASentenceErr_ParseError_SentenceNotLongEnough '4'
#define NMEASentenceErr_ParseError_ChecksumNotFound '5'
#define NMEASentenceErr_ParseError_ChecksumNotLongEnough '6'
#define NMEASentenceErr_ParseError_ChecksumIncorrect '7'
#define NMEASentenceErr_ParseError_TalkerDecoding '8'

#define NMEASentenceErr_processGPSNMEASentence_NoError '9'
#define NMEASentenceErr_processGPSNMEASentence_BlankReading '10'

typedef struct NMEASentence
{
    char sentenceString[70];
    int sentenceStringUsedSize;
    char talkerIdentifier[3];
    char sentenceIdentifier[4];

    bool readingStarted;
    bool readingComplete;
    char errorCode;
} NMEASentence;

void initialiseNMEASentence(NMEASentence *nmeaSentence);
void addCharToNMEASentence(NMEASentence *sentence, char c);
void readCharForNMEASentence(NMEASentence *sentence, char c);
void parseNMEASentence(NMEASentence *sentence);

typedef struct gpsReading
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
} gpsReading;

void process_GNRMC_NMEASentence(NMEASentence *sentence, gpsReading *reading);

#endif