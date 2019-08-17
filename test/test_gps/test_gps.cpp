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
        .inputTestString = "$GNRMC,112738.000,A,3413.8132,S,08313.6519,E,0.00,0.00,090619,,,A*6b\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = -34.2302,
            .latDirection = 'S',
            .lon = 83.2275,
            .lonDirection = 'E',
        },
    },
    {
        .inputTestString = "$GNRMC,112738.000,A,8245.6935,S,13451.4700,W,0.00,0.00,090619,,,A*75\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = -82.7616,
            .latDirection = 'S',
            .lon = -134.8578,
            .lonDirection = 'W',
        },
    },
    {
        .inputTestString = "$GNRMC,112738.000,A,1519.2452,S,07555.3304,W,0.00,0.00,090619,,,A*7d\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = -15.3208,
            .latDirection = 'S',
            .lon = -75.9222,
            .lonDirection = 'W',
        },
    },
    {
        .inputTestString = "$GNRMC,112738.000,A,1329.0227,N,03505.6532,W,0.00,0.00,090619,,,A*64\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = 13.4837,
            .latDirection = 'N',
            .lon = -35.0942,
            .lonDirection = 'W',
        },
    },
    {
        .inputTestString = "$GNRMC,112738.000,A,2333.9179,N,03646.7816,W,0.00,0.00,090619,,,A*63\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = 23.5653,
            .latDirection = 'N',
            .lon = -36.7797,
            .lonDirection = 'W',
        },
    },
    {
        .inputTestString = "$GNRMC,112738.000,A,1806.8409,N,03329.2635,E,0.00,0.00,090619,,,A*7a\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = 18.114,
            .latDirection = 'N',
            .lon = 33.4877,
            .lonDirection = 'E',
        },
    },
    {
        .inputTestString = "$GNRMC,112738.000,A,3825.0610,N,03143.6958,E,0.00,0.00,090619,,,A*75\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = 38.4177,
            .latDirection = 'N',
            .lon = 31.7283,
            .lonDirection = 'E',
        },
    },
    {
        .inputTestString = "$GNRMC,112738.000,A,6733.5522,N,11105.6996,W,0.00,0.00,090619,,,A*6e\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = 67.5592,
            .latDirection = 'N',
            .lon = -111.095,
            .lonDirection = 'W',
        },
    },
    {
        .inputTestString = "$GNRMC,112738.000,A,8055.2882,N,05359.9767,W,0.00,0.00,090619,,,A*66\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = 80.9215,
            .latDirection = 'N',
            .lon = -53.9996,
            .lonDirection = 'W',
        },
    },
    {
        .inputTestString = "$GNRMC,112738.000,A,2843.3230,N,09128.9508,E,0.00,0.00,090619,,,A*70\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = 28.7221,
            .latDirection = 'N',
            .lon = 91.4825,
            .lonDirection = 'E',
        },
    },
    {
        .inputTestString = "$GNRMC,112738.000,A,3542.5647,N,03421.0223,E,0.00,0.00,090619,,,A*7e\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = 35.7094,
            .latDirection = 'N',
            .lon = 34.3504,
            .lonDirection = 'E',
        },
    },
    {
        .inputTestString = "$GNRMC,112738.000,A,3137.8368,N,04540.2129,E,0.00,0.00,090619,,,A*77\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = 31.6306,
            .latDirection = 'N',
            .lon = 45.6702,
            .lonDirection = 'E',
        },
    },
    {
        .inputTestString = "$GNRMC,112738.000,A,1726.8303,S,09210.0964,W,0.00,0.00,090619,,,A*7d\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = -17.4472,
            .latDirection = 'S',
            .lon = -92.1683,
            .lonDirection = 'W',
        },
    },
    {
        .inputTestString = "$GNRMC,112738.000,A,4115.8677,S,05411.9238,W,0.00,0.00,090619,,,A*78\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = -41.2645,
            .latDirection = 'S',
            .lon = -54.1987,
            .lonDirection = 'W',
        },
    },
    {
        .inputTestString = "$GNRMC,112738.000,A,5556.9504,N,01940.8401,W,0.00,0.00,090619,,,A*61\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = 55.9492,
            .latDirection = 'N',
            .lon = -19.6807,
            .lonDirection = 'W',
        },
    },
    {
        .inputTestString = "$GNRMC,112738.000,A,7524.8012,S,06430.0513,E,0.00,0.00,090619,,,A*6d\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = -75.4134,
            .latDirection = 'S',
            .lon = 64.5009,
            .lonDirection = 'E',
        },
    },
    {
        .inputTestString = "$GNRMC,112738.000,A,6607.9070,N,09758.3978,E,0.00,0.00,090619,,,A*76\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = 66.1318,
            .latDirection = 'N',
            .lon = 97.9733,
            .lonDirection = 'E',
        },
    },
    {
        .inputTestString = "$GNRMC,112738.000,A,4850.4108,N,16844.3774,E,0.00,0.00,090619,,,A*75\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = 48.8402,
            .latDirection = 'N',
            .lon = 168.7396,
            .lonDirection = 'E',
        },
    },
    {
        .inputTestString = "$GNRMC,112738.000,A,7508.0772,N,12202.4687,E,0.00,0.00,090619,,,A*7f\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = 75.1346,
            .latDirection = 'N',
            .lon = 122.0411,
            .lonDirection = 'E',
        },
    },
    {
        .inputTestString = "$GNRMC,112738.000,A,5002.8963,N,15620.7275,E,0.00,0.00,090619,,,A*7d\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = 50.0483,
            .latDirection = 'N',
            .lon = 156.3455,
            .lonDirection = 'E',
        },
    },
    {
        .inputTestString = "$GNRMC,112738.000,A,4856.1049,N,03431.3685,E,0.00,0.00,090619,,,A*77\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = 48.9351,
            .latDirection = 'N',
            .lon = 34.5228,
            .lonDirection = 'E',
        },
    },
    {
        .inputTestString = "$GNRMC,112738.000,A,5540.0369,N,07403.3806,W,0.00,0.00,090619,,,A*6e\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = 55.6673,
            .latDirection = 'N',
            .lon = -74.0563,
            .lonDirection = 'W',
        },
    },
    {
        .inputTestString = "$GNRMC,112738.000,A,3755.1415,N,03639.0033,W,0.00,0.00,090619,,,A*61\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = 37.919,
            .latDirection = 'N',
            .lon = -36.6501,
            .lonDirection = 'W',
        },
    },
    {
        .inputTestString = "$GNRMC,112738.000,A,2007.8921,S,13321.1194,W,0.00,0.00,090619,,,A*7e\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = -20.1315,
            .latDirection = 'S',
            .lon = -133.352,
            .lonDirection = 'W',
        },
    },
    {
        .inputTestString = "$GNRMC,112738.000,A,4802.5875,S,10135.1544,W,0.00,0.00,090619,,,A*75\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = -48.0431,
            .latDirection = 'S',
            .lon = -101.5859,
            .lonDirection = 'W',
        },
    },
    {
        .inputTestString = "$GNRMC,112738.000,A,6220.9431,N,15512.3331,W,0.00,0.00,090619,,,A*62\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = 62.3491,
            .latDirection = 'N',
            .lon = -155.2056,
            .lonDirection = 'W',
        },
    },
    {
        .inputTestString = "$GNRMC,112738.000,A,1538.5625,S,13029.1046,E,0.00,0.00,090619,,,A*65\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = -15.6427,
            .latDirection = 'S',
            .lon = 130.4851,
            .lonDirection = 'E',
        },
    },
    {
        .inputTestString = "$GNRMC,112738.000,A,2858.0892,S,15439.2734,E,0.00,0.00,090619,,,A*68\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = -28.9682,
            .latDirection = 'S',
            .lon = 154.6546,
            .lonDirection = 'E',
        },
    },
    {
        .inputTestString = "$GNRMC,112738.000,A,5300.0481,N,04236.6522,W,0.00,0.00,090619,,,A*60\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = 53.0008,
            .latDirection = 'N',
            .lon = -42.6109,
            .lonDirection = 'W',
        },
    },
    {
        .inputTestString = "$GNRMC,112738.000,A,5010.3120,N,03608.0049,E,0.00,0.00,090619,,,A*7d\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = 50.1719,
            .latDirection = 'N',
            .lon = 36.1334,
            .lonDirection = 'E',
        },
    },
    {
        .inputTestString = "$GNRMC,112738.000,A,6238.4483,N,11809.1045,W,0.00,0.00,090619,,,A*6e\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = 62.6408,
            .latDirection = 'N',
            .lon = -118.1517,
            .lonDirection = 'W',
        },
    },
    {
        .inputTestString = "$GNRMC,112738.000,A,6616.1082,N,02828.9734,E,0.00,0.00,090619,,,A*7c\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = 66.2685,
            .latDirection = 'N',
            .lon = 28.4829,
            .lonDirection = 'E',
        },
    },
    {
        .inputTestString = "$GNRMC,112738.000,A,8651.5776,N,05605.2240,E,0.00,0.00,090619,,,A*72\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = 86.8596,
            .latDirection = 'N',
            .lon = 56.0871,
            .lonDirection = 'E',
        },
    },
    {
        .inputTestString = "$GNRMC,112738.000,A,5517.1719,S,15429.5020,W,0.00,0.00,090619,,,A*72\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = -55.2862,
            .latDirection = 'S',
            .lon = -154.4917,
            .lonDirection = 'W',
        },
    },
    {
        .inputTestString = "$GNRMC,112738.000,A,6208.6591,S,13846.2927,E,0.00,0.00,090619,,,A*65\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = -62.1443,
            .latDirection = 'S',
            .lon = 138.7715,
            .lonDirection = 'E',
        },
    },
    {
        .inputTestString = "$GNRMC,112738.000,A,4307.2414,S,09402.9132,E,0.00,0.00,090619,,,A*61\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = -43.1207,
            .latDirection = 'S',
            .lon = 94.0486,
            .lonDirection = 'E',
        },
    },
    {
        .inputTestString = "$GNRMC,112738.000,A,6516.3321,N,02838.5430,W,0.00,0.00,090619,,,A*6f\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = 65.2722,
            .latDirection = 'N',
            .lon = -28.6424,
            .lonDirection = 'W',
        },
    },
    {
        .inputTestString = "$GNRMC,112738.000,A,1236.8539,S,12944.7528,W,0.00,0.00,090619,,,A*75\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = -12.6142,
            .latDirection = 'S',
            .lon = -129.7459,
            .lonDirection = 'W',
        },
    },
    {
        .inputTestString = "$GNRMC,112738.000,A,7907.4858,S,08556.7810,W,0.00,0.00,090619,,,A*7e\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = -79.1248,
            .latDirection = 'S',
            .lon = -85.9463,
            .lonDirection = 'W',
        },
    },
    {
        .inputTestString = "$GNRMC,112738.000,A,8208.6252,S,03617.8535,E,0.00,0.00,090619,,,A*6d\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = -82.1438,
            .latDirection = 'S',
            .lon = 36.2976,
            .lonDirection = 'E',
        },
    },
    {
        .inputTestString = "$GNRMC,112738.000,A,2040.4420,S,09217.6834,W,0.00,0.00,090619,,,A*76\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = -20.674,
            .latDirection = 'S',
            .lon = -92.2947,
            .lonDirection = 'W',
        },
    },
    {
        .inputTestString = "$GNRMC,112738.000,A,1935.2982,S,05348.1107,E,0.00,0.00,090619,,,A*66\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = -19.5883,
            .latDirection = 'S',
            .lon = 53.8018,
            .lonDirection = 'E',
        },
    },
    {
        .inputTestString = "$GNRMC,112738.000,A,6405.3188,S,08420.7069,E,0.00,0.00,090619,,,A*67\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = -64.0886,
            .latDirection = 'S',
            .lon = 84.3451,
            .lonDirection = 'E',
        },
    },
    {
        .inputTestString = "$GNRMC,112738.000,A,7429.7112,N,08459.8814,E,0.00,0.00,090619,,,A*71\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = 74.4952,
            .latDirection = 'N',
            .lon = 84.998,
            .lonDirection = 'E',
        },
    },
    {
        .inputTestString = "$GNRMC,112738.000,A,7017.3103,S,09424.7916,W,0.00,0.00,090619,,,A*74\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = -70.2885,
            .latDirection = 'S',
            .lon = -94.4132,
            .lonDirection = 'W',
        },
    },
    {
        .inputTestString = "$GNRMC,112738.000,A,2943.6402,N,12645.7878,E,0.00,0.00,090619,,,A*71\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = 29.7273,
            .latDirection = 'N',
            .lon = 126.7631,
            .lonDirection = 'E',
        },
    },
    {
        .inputTestString = "$GNRMC,112738.000,A,4542.0378,N,02627.4789,W,0.00,0.00,090619,,,A*63\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = 45.7006,
            .latDirection = 'N',
            .lon = -26.458,
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
        TEST_ASSERT_EQUAL_INT_MESSAGE(cases[caseIdx].expectedGPSReading.latDirection,
                                      test.latDirection,
                                      "GPS Reading Latitude Direction");
        TEST_ASSERT_EQUAL_FLOAT_MESSAGE(cases[caseIdx].expectedGPSReading.lat.f,
                                        test.lat.f,
                                        "GPS Reading Latitude Float");
        TEST_ASSERT_EQUAL_INT_MESSAGE(cases[caseIdx].expectedGPSReading.lonDirection,
                                      test.lonDirection,
                                      "GPS Reading Longitude Direction");
        TEST_ASSERT_EQUAL_FLOAT_MESSAGE(cases[caseIdx].expectedGPSReading.lon.f,
                                        test.lon.f,
                                        "GPS Reading Longitude Float");
    }
}

int main(int argc, char **argv)
{
    UNITY_BEGIN();
    RUN_TEST(test_function_make_gps);
    UNITY_END();

    return 0;
}