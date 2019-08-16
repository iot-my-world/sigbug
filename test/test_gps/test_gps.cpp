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

const char *testString = "$GNRMC,112738.000,A,2608.9935,S,02808.1064,E,0.00,0.00,090619,,,A*6F\r\n";

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
    NMEASentence nmeaSentence;

    initialiseNMEASentence(&nmeaSentence);
    for (int i = 0; i < strlen(testString); i++)
    {
        readCharForNMEASentence(&nmeaSentence, testString[i]);
    }
    TEST_ASSERT_EQUAL_INT_MESSAGE(1, nmeaSentence.readingStarted, "Reading Started Indication");
    TEST_ASSERT_EQUAL_INT_MESSAGE(1, nmeaSentence.readingComplete, "Reading Ended Indication");
    TEST_ASSERT_EQUAL_INT(NMEASentenceErr_NoError, nmeaSentence.errorCode);

    parseNMEASentence(&nmeaSentence);
    TEST_ASSERT_EQUAL_INT(NMEASentenceErr_NoError, nmeaSentence.errorCode);
    TEST_ASSERT_EQUAL_STRING("GN", nmeaSentence.talkerIdentifier);
    TEST_ASSERT_EQUAL_STRING("RMC", nmeaSentence.sentenceIdentifier);

    process_GNRMC_NMEASentence(&nmeaSentence, &test);
    TEST_ASSERT_EQUAL_INT(expected.error, test.error);
    TEST_ASSERT_EQUAL_FLOAT(expected.lat.f, test.lat.f);
    TEST_ASSERT_EQUAL_INT(expected.latDirection, test.latDirection);
    TEST_ASSERT_EQUAL_FLOAT(expected.lon.f, test.lon.f);
    TEST_ASSERT_EQUAL_INT(expected.lonDirection, test.lonDirection);
}

int main(int argc, char **argv)
{
    UNITY_BEGIN();
    RUN_TEST(test_function_make_gps);
    UNITY_END();

    return 0;
}