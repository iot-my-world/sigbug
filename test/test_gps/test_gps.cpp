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

/*
const char *testString = "$GNRMC,112738.000,A,2608.9935,S,02808.1064,E,0.00,0.00,090619,,,A*6F";

void test_function_make_gps(void)
{
    gpsReading test;
    struct gpsReading expected = {
        .error = NMEASentenceErr_processGPSNMEASentence_NoError,
        .lat = -26.1499,
        .latDirection = 'S',
        .lon = 28.1351,
        .lonDirection = 'E',
    };
*/

testCase cases[] = {
    {
        .inputTestString = "$GNRMC,112738.000,A,1024.8696,S,11338.0173,E,0.00,0.00,090619,,,A*6f\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = -10.4145,
            .latDirection = 'S',
            .lon = 113.6336,
            .lonDirection = 'E',
        },
    },
    {
        .inputTestString = "$GNRMC,112738.000,A,8839.0276,N,06316.7489,E,0.00,0.00,090619,,,A*07\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = 88.6505,
            .latDirection = 'N',
            .lon = 63.2791,
            .lonDirection = 'E',
        },
    },
    {
        .inputTestString = "$GNRMC,112738.000,A,1825.7489,S,11710.4031,E,0.00,0.00,090619,,,A*68\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = -18.4291,
            .latDirection = 'S',
            .lon = 117.1734,
            .lonDirection = 'E',
        },
    },
    {
        .inputTestString = "$GNRMC,112738.000,A,7528.8625,S,08311.9673,W,0.00,0.00,090619,,,A*77\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = -75.481,
            .latDirection = 'S',
            .lon = -83.1995,
            .lonDirection = 'W',
        },
    },
    {
        .inputTestString = "$GNRMC,112738.000,A,4429.9547,N,08150.6602,E,0.00,0.00,090619,,,A*73\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = 44.4992,
            .latDirection = 'N',
            .lon = 81.8443,
            .lonDirection = 'E',
        },
    },
    {
        .inputTestString = "$GNRMC,112738.000,A,7606.5822,S,01641.7824,E,0.00,0.00,090619,,,A*65\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = -76.1097,
            .latDirection = 'S',
            .lon = 16.6964,
            .lonDirection = 'E',
        },
    },
    {
        .inputTestString = "$GNRMC,112738.000,A,5920.3893,N,04216.9185,E,0.00,0.00,090619,,,A*72\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = 59.3398,
            .latDirection = 'N',
            .lon = 42.282,
            .lonDirection = 'E',
        },
    },
    {
        .inputTestString = "$GNRMC,112738.000,A,8034.0672,N,16346.9775,E,0.00,0.00,090619,,,A*7f\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = 80.5678,
            .latDirection = 'N',
            .lon = 163.783,
            .lonDirection = 'E',
        },
    },
    {
        .inputTestString = "$GNRMC,112738.000,A,1833.2617,S,04118.7367,W,0.00,0.00,090619,,,A*74\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = -18.5544,
            .latDirection = 'S',
            .lon = -41.3123,
            .lonDirection = 'W',
        },
    },
    {
        .inputTestString = "$GNRMC,112738.000,A,3754.4189,N,02300.0702,W,0.00,0.00,090619,,,A*6e\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = 37.907,
            .latDirection = 'N',
            .lon = -23.0012,
            .lonDirection = 'W',
        },
    },
};

void test_function_make_gps(void)
{

    for (int caseIdx = 0; caseIdx < sizeof(cases) / sizeof(*cases); caseIdx++)
    {
        printf("Test Idx: %d\n", caseIdx);
        NMEASentence nmeaSentence;
        gpsReading test;
        initialiseNMEASentence(&nmeaSentence);
        for (int i = 0; i < strlen(cases[caseIdx].inputTestString); i++)
        {
            readCharForNMEASentence(&nmeaSentence, cases[caseIdx].inputTestString[i]);
        }
        TEST_ASSERT_EQUAL_INT_MESSAGE(cases[caseIdx].expectedReadingStartIndication,
                                      nmeaSentence.readingStarted,
                                      "Reading Started Indication");
        TEST_ASSERT_EQUAL_INT_MESSAGE(cases[caseIdx].expectedReadingCompleteIndication,
                                      nmeaSentence.readingComplete,
                                      "Reading Ended Indication");
        TEST_ASSERT_EQUAL_INT_MESSAGE(cases[caseIdx].expectedPostReadingNMEASentenceErr,
                                      nmeaSentence.errorCode,
                                      "Post NMEA Sentence Reading Error");

        parseNMEASentence(&nmeaSentence);
        TEST_ASSERT_EQUAL_INT_MESSAGE(cases[caseIdx].expectedPostParse_NMEASentenceErr,
                                      nmeaSentence.errorCode,
                                      "Post Parse NMEA Sentence Error");
        TEST_ASSERT_EQUAL_STRING_MESSAGE(cases[caseIdx].expectedNMEATalkerIdentifier,
                                         nmeaSentence.talkerIdentifier,
                                         "NMEA Talker Identifier");
        TEST_ASSERT_EQUAL_STRING_MESSAGE(cases[caseIdx].expectedNMEASentenceIdentifier,
                                         nmeaSentence.sentenceIdentifier,
                                         "NMEA Sentence Identifier");

        process_GNRMC_NMEASentence(&nmeaSentence, &test);
        TEST_ASSERT_EQUAL_INT_MESSAGE(cases[caseIdx].expectedGPSReading.error,
                                      test.error,
                                      "GPS Reading Error");
        TEST_ASSERT_EQUAL_FLOAT_MESSAGE(cases[caseIdx].expectedGPSReading.lat.f,
                                        test.lat.f,
                                        "GPS Reading Latitude Float");
        TEST_ASSERT_EQUAL_INT_MESSAGE(cases[caseIdx].expectedGPSReading.latDirection,
                                      test.latDirection,
                                      "GPS Reading Latitude Direction");
        TEST_ASSERT_EQUAL_FLOAT_MESSAGE(cases[caseIdx].expectedGPSReading.lon.f,
                                        test.lon.f,
                                        "GPS Reading Longitude Float");
        TEST_ASSERT_EQUAL_INT_MESSAGE(cases[caseIdx].expectedGPSReading.lonDirection,
                                      test.lonDirection,
                                      "GPS Reading Longitude Direction");
    }
}

int main(int argc, char **argv)
{
    UNITY_BEGIN();
    RUN_TEST(test_function_make_gps);
    UNITY_END();

    return 0;
}