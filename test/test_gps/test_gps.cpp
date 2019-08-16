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

const char *testString = "$GNRMC,112738.000,A,2608.9935,S,02808.1064,E,0.00,0.00,090619,,,A*6F";

void test_function_make_gps(void)
{
    gpsReading test;
    gpsReading expected;
    int test2;
    NMEASentence nmeaSentence;

    initialiseNMEASentence(&nmeaSentence);
    for (int i = 0; i < strlen(testString); i++)
    {
        readCharForNMEASentence(&nmeaSentence, testString[i]);
    }

    TEST_ASSERT_EQUAL_INT(NMEASentenceErr_NoError, nmeaSentence.errorCode);
}

int main(int argc, char **argv)
{
    UNITY_BEGIN();
    RUN_TEST(test_function_make_gps);
    UNITY_END();

    return 0;
}