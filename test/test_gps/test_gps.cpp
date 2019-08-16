#include <NMEASentence.h>
#include <unity.h>
#include <stdio.h>
#include <string.h>
#include "TestCase.h"

// void setUp(void) {
// // set stuff up here
// }

// void tearDown(void) {
// // clean stuff up here
// }

testCase cases[] = {
    {
        .inputTestString = "$GNRMC,112738.000,A,2608.9935,S,02808.1064,E,0.00,0.00,090619,,,A*6F\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = -26.1499,
            .latDirection = 'S',
            .lon = 28.1351,
            .lonDirection = 'E',
        },
    },

};

void test_function_make_gps(void)
{

    for (int caseIdx = 0; caseIdx < sizeof(cases) / sizeof(*cases); caseIdx++)
    {
        NMEASentence nmeaSentence;
        gpsReading test;
        initialiseNMEASentence(&nmeaSentence);
        for (int i = 0; i < strlen(cases[caseIdx].inputTestString); i++)
        {
            readCharForNMEASentence(&nmeaSentence, cases[caseIdx].inputTestString[i]);
        }
        TEST_ASSERT_EQUAL_INT_MESSAGE(cases[caseIdx].expectedReadingStartIndication, nmeaSentence.readingStarted, "Reading Started Indication");
        TEST_ASSERT_EQUAL_INT_MESSAGE(cases[caseIdx].expectedReadingCompleteIndication, nmeaSentence.readingComplete, "Reading Ended Indication");
        TEST_ASSERT_EQUAL_INT_MESSAGE(cases[caseIdx].expectedPostReadingNMEASentenceErr, nmeaSentence.errorCode, "Post NMEA Sentence Reading Error");

        parseNMEASentence(&nmeaSentence);
        TEST_ASSERT_EQUAL_INT_MESSAGE(cases[caseIdx].expectedPostParse_NMEASentenceErr, nmeaSentence.errorCode, "Post Parse NMEA Sentence Error");
        TEST_ASSERT_EQUAL_STRING_MESSAGE(cases[caseIdx].expectedNMEATalkerIdentifier, nmeaSentence.talkerIdentifier, "NMEA Talker Identifier");
        TEST_ASSERT_EQUAL_STRING_MESSAGE(cases[caseIdx].expectedNMEASentenceIdentifier, nmeaSentence.sentenceIdentifier, "NMEA Sentence Identifier");

        process_GNRMC_NMEASentence(&nmeaSentence, &test);
        TEST_ASSERT_EQUAL_INT_MESSAGE(cases[caseIdx].expectedGPSReading.error, test.error, "GPS Reading Error");
        TEST_ASSERT_EQUAL_FLOAT_MESSAGE(cases[caseIdx].expectedGPSReading.lat.f, test.lat.f, "GPS Reading Latitude Float");
        TEST_ASSERT_EQUAL_INT_MESSAGE(cases[caseIdx].expectedGPSReading.latDirection, test.latDirection, "GPS Reading Latitude Direction");
        TEST_ASSERT_EQUAL_FLOAT_MESSAGE(cases[caseIdx].expectedGPSReading.lon.f, test.lon.f, "GPS Reading Longitude Float");
        TEST_ASSERT_EQUAL_INT_MESSAGE(cases[caseIdx].expectedGPSReading.lonDirection, test.lonDirection, "GPS Reading Longitude Direction");
    }
}

int main(int argc, char **argv)
{
    UNITY_BEGIN();
    RUN_TEST(test_function_make_gps);
    UNITY_END();

    return 0;
}