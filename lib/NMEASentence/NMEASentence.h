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

#define NMEA_MaxSentenceStringSize 75

#define NMEASentenceErr_NoError 0
#define NMEASentenceErr_UnexpectedError 1
#define NMEASentenceErr_MessageDidntStart 2
#define NMEASentenceErr_MessageDidntEnd 3
#define NMEASentenceErr_StringOutOfMemory 4
#define NMEASentenceErr_ParseError_SentenceNotLongEnough 5
#define NMEASentenceErr_ParseError_ChecksumNotFound 6
#define NMEASentenceErr_ParseError_ChecksumNotCorrectLength 7
#define NMEASentenceErr_ParseError_ChecksumIncorrect 8
#define NMEASentenceErr_ParseError_TalkerDecoding 9

#define NMEASentenceErr_processGPSNMEASentence_NoError 10
#define NMEASentenceErr_processGPSNMEASentence_BlankReading 11

typedef struct NMEASentence
{
    char sentenceString[NMEA_MaxSentenceStringSize + 1];
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