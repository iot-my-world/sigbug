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
    //
    // Success tests
    //
    {
        .id = "2823bad1b76444db93fa75e8dcde04d5",
        .inputTestString = "$GNRMC,112738.000,A,2645.6826,N,15642.8687,E,0.00,0.00,090619,,,A*73\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = 26.7614,
            .latDirection = 'N',
            .lon = 156.7145,
            .lonDirection = 'E',
        },

        .expectedLatitudeHexData = "5917d641",
        .expectedLongitudeHexData = "e9b61c43",
    },
    {
        .id = "d83f395a7c4545e59e5747fea1b4f7cf",
        .inputTestString = "$GNRMC,112738.000,A,8102.0709,N,10204.6761,W,0.00,0.00,090619,,,A*6f\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = 81.0345,
            .latDirection = 'N',
            .lon = -102.0779,
            .lonDirection = 'W',
        },

        .expectedLatitudeHexData = "aa11a242",
        .expectedLongitudeHexData = "e327ccc2",
    },
    {
        .id = "1de31492da2245d8b9229195f9d6e667",
        .inputTestString = "$GNRMC,112738.000,A,2528.9582,N,08926.7998,W,0.00,0.00,090619,,,A*6a\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = 25.4826,
            .latDirection = 'N',
            .lon = -89.4467,
            .lonDirection = 'W',
        },

        .expectedLatitudeHexData = "5ddccb41",
        .expectedLongitudeHexData = "b6e4b2c2",
    },
    {
        .id = "77f462ee0aaa410db2e5e43a8173c469",
        .inputTestString = "$GNRMC,112738.000,A,6500.7603,S,11931.4035,E,0.00,0.00,090619,,,A*6c\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = -65.0127,
            .latDirection = 'S',
            .lon = 119.5234,
            .lonDirection = 'E',
        },

        .expectedLatitudeHexData = "810682c2",
        .expectedLongitudeHexData = "fb0bef42",
    },
    {
        .id = "5b6ef9ba6a6e469491cbd50c83f096f4",
        .inputTestString = "$GNRMC,112738.000,A,7207.8291,S,03342.5858,W,0.00,0.00,090619,,,A*70\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = -72.1305,
            .latDirection = 'S',
            .lon = -33.7098,
            .lonDirection = 'W',
        },

        .expectedLatitudeHexData = "d14209c2",
        .expectedLongitudeHexData = "d6d606c2",
    },
    {
        .id = "6902afa2fbb44ab9933c7028c4569493",
        .inputTestString = "$GNRMC,112738.000,A,6618.9381,N,14619.9557,E,0.00,0.00,090619,,,A*76\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = 66.3156,
            .latDirection = 'N',
            .lon = 146.3326,
            .lonDirection = 'E',
        },

        .expectedLatitudeHexData = "96a18442",
        .expectedLongitudeHexData = "25551243",
    },
    {
        .id = "1c5049def0ac499ea7a6db340c7fc5bf",
        .inputTestString = "$GNRMC,112738.000,A,6441.2926,N,07301.9830,E,0.00,0.00,090619,,,A*76\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = 64.6882,
            .latDirection = 'N',
            .lon = 73.0331,
            .lonDirection = 'E',
        },

        .expectedLatitudeHexData = "5c068142",
        .expectedLongitudeHexData = "f2019242",
    },
    {
        .id = "d9522d9e03274370b4f2b62f0f256b88",
        .inputTestString = "$GNRMC,112738.000,A,8517.7328,S,08241.1987,W,0.00,0.00,090619,,,A*7b\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = -85.2955,
            .latDirection = 'S',
            .lon = -82.6866,
            .lonDirection = 'W',
        },

        .expectedLatitudeHexData = "4c97aac2",
        .expectedLongitudeHexData = "8a5fa5c2",
    },
    {
        .id = "a6d6e9f4f7a947ce949a75ffa04e9db4",
        .inputTestString = "$GNRMC,112738.000,A,2432.8624,S,10132.4564,W,0.00,0.00,090619,,,A*7b\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = -24.5477,
            .latDirection = 'S',
            .lon = -101.5409,
            .lonDirection = 'W',
        },

        .expectedLatitudeHexData = "b161c4c1",
        .expectedLongitudeHexData = "f114cbc2",
    },
    {
        .id = "65439a93f06f417e9ca75e2830559cc3",
        .inputTestString = "$GNRMC,112738.000,A,8852.9518,S,07527.8476,E,0.00,0.00,090619,,,A*6c\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = -88.8825,
            .latDirection = 'S',
            .lon = 75.4641,
            .lonDirection = 'E',
        },

        .expectedLatitudeHexData = "d7c3b1c2",
        .expectedLongitudeHexData = "9fed9642",
    },
    {
        .id = "9a730f588cc44bb291e8071bbf5b4ec7",
        .inputTestString = "$GNRMC,112738.000,A,1854.2504,N,10227.1902,E,0.00,0.00,090619,,,A*7e\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = 18.9042,
            .latDirection = 'N',
            .lon = 102.4532,
            .lonDirection = 'E',
        },

        .expectedLatitudeHexData = "cd3b9741",
        .expectedLongitudeHexData = "0ae8cc42",
    },
    {
        .id = "b279e4822e3f4a20bd728e17dcc370e4",
        .inputTestString = "$GNRMC,112738.000,A,7320.4858,N,13220.6808,W,0.00,0.00,090619,,,A*68\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = 73.3414,
            .latDirection = 'N',
            .lon = -132.3447,
            .lonDirection = 'W',
        },

        .expectedLatitudeHexData = "ccae9242",
        .expectedLongitudeHexData = "3e5804c3",
    },
    {
        .id = "c28349f42e9341ecbee185077c2487fe",
        .inputTestString = "$GNRMC,112738.000,A,2922.1161,N,01014.6441,E,0.00,0.00,090619,,,A*76\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = 29.3686,
            .latDirection = 'N',
            .lon = 10.2441,
            .lonDirection = 'E',
        },

        .expectedLatitudeHexData = "e5f2ea41",
        .expectedLongitudeHexData = "d5e72341",
    },
    {
        .id = "419a162bbf3b433da2ada37467dc5ce1",
        .inputTestString = "$GNRMC,112738.000,A,7829.5157,S,04601.9302,W,0.00,0.00,090619,,,A*7f\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = -78.4919,
            .latDirection = 'S',
            .lon = -46.0322,
            .lonDirection = 'W',
        },

        .expectedLatitudeHexData = "dafb9cc2",
        .expectedLongitudeHexData = "f90238c2",
    },
    {
        .id = "7d7e6ac7dec44bd693a89be5d5240717",
        .inputTestString = "$GNRMC,112738.000,A,2306.7048,N,06335.2329,W,0.00,0.00,090619,,,A*6e\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = 23.1117,
            .latDirection = 'N',
            .lon = -63.5872,
            .lonDirection = 'W',
        },

        .expectedLatitudeHexData = "c3e4b841",
        .expectedLongitudeHexData = "4b597ec2",
    },
    {
        .id = "9a39e079af1d477e833f8414c512d5eb",
        .inputTestString = "$GNRMC,112738.000,A,5746.3882,S,08247.7003,E,0.00,0.00,090619,,,A*68\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = -57.7731,
            .latDirection = 'S',
            .lon = 82.795,
            .lonDirection = 'E',
        },

        .expectedLatitudeHexData = "a81767c2",
        .expectedLongitudeHexData = "0a97a542",
    },
    {
        .id = "355ee3614a934982b8977aa5edd719bc",
        .inputTestString = "$GNRMC,112738.000,A,8451.8756,N,11732.2710,W,0.00,0.00,090619,,,A*6d\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = 84.8646,
            .latDirection = 'N',
            .lon = -117.5378,
            .lonDirection = 'W',
        },

        .expectedLatitudeHexData = "adbaa942",
        .expectedLongitudeHexData = "5b13ebc2",
    },
    {
        .id = "9e24ca5de89f4f638046431504dd11e0",
        .inputTestString = "$GNRMC,112738.000,A,1712.9989,S,09402.8743,W,0.00,0.00,090619,,,A*75\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = -17.2166,
            .latDirection = 'S',
            .lon = -94.0479,
            .lonDirection = 'W',
        },

        .expectedLatitudeHexData = "99bb89c1",
        .expectedLongitudeHexData = "8618bcc2",
    },
    {
        .id = "853bfbe8229943f1954808c4e5cfb167",
        .inputTestString = "$GNRMC,112738.000,A,7526.7220,N,06604.2393,W,0.00,0.00,090619,,,A*65\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = 75.4454,
            .latDirection = 'N',
            .lon = -66.0707,
            .lonDirection = 'W',
        },

        .expectedLatitudeHexData = "0be49642",
        .expectedLongitudeHexData = "332484c2",
    },
    {
        .id = "79bc3a1e7cf7414286d928eb1fde9b54",
        .inputTestString = "$GNRMC,112738.000,A,1413.1112,N,16442.0676,E,0.00,0.00,090619,,,A*7f\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = 14.2185,
            .latDirection = 'N',
            .lon = 164.7011,
            .lonDirection = 'E',
        },

        .expectedLatitudeHexData = "fa7e6341",
        .expectedLongitudeHexData = "7bb32443",
    },
    {
        .id = "24aaa06427774a6c9f63b3240981a4ae",
        .inputTestString = "$GNRMC,112738.000,A,3731.8327,N,05222.9520,E,0.00,0.00,090619,,,A*78\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = 37.5305,
            .latDirection = 'N',
            .lon = 52.3825,
            .lonDirection = 'E',
        },

        .expectedLatitudeHexData = "3b1f1642",
        .expectedLongitudeHexData = "ae875142",
    },
    {
        .id = "9cdd62ee22434da9b09d46d3c33df82e",
        .inputTestString = "$GNRMC,112738.000,A,3944.7480,S,09510.7835,W,0.00,0.00,090619,,,A*73\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = -39.7458,
            .latDirection = 'S',
            .lon = -95.1797,
            .lonDirection = 'W',
        },

        .expectedLatitudeHexData = "b3fb1ec2",
        .expectedLongitudeHexData = "025cbec2",
    },
    {
        .id = "58c501266af44047b8b15c8425192fd6",
        .inputTestString = "$GNRMC,112738.000,A,3602.2817,S,06453.0356,E,0.00,0.00,090619,,,A*6b\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = -36.038,
            .latDirection = 'S',
            .lon = 64.8839,
            .lonDirection = 'E',
        },

        .expectedLatitudeHexData = "e92601c2",
        .expectedLongitudeHexData = "8fc48142",
    },
    {
        .id = "8858fe6f0e664b29acb330ed29c216d0",
        .inputTestString = "$GNRMC,112738.000,A,4126.7870,S,12436.4819,E,0.00,0.00,090619,,,A*6b\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = -41.4465,
            .latDirection = 'S',
            .lon = 124.608,
            .lonDirection = 'E',
        },

        .expectedLatitudeHexData = "37c925c2",
        .expectedLongitudeHexData = "4c37f942",
    },
    {
        .id = "8a3bcf18f081403baf8baaef1756e166",
        .inputTestString = "$GNRMC,112738.000,A,7532.9311,N,12806.2897,W,0.00,0.00,090619,,,A*6b\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = 75.5489,
            .latDirection = 'N',
            .lon = -128.1048,
            .lonDirection = 'W',
        },

        .expectedLatitudeHexData = "09199742",
        .expectedLongitudeHexData = "d41a00c3",
    },
    {
        .id = "1e3f05dc85094bbbb3ed8e421c52bcd5",
        .inputTestString = "$GNRMC,112738.000,A,7956.9582,S,15225.4846,E,0.00,0.00,090619,,,A*60\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = -79.9493,
            .latDirection = 'S',
            .lon = 152.4247,
            .lonDirection = 'E',
        },

        .expectedLatitudeHexData = "0be69fc2",
        .expectedLongitudeHexData = "b96c1843",
    },
    {
        .id = "8f291916bc7e4b25831856417cc146c1",
        .inputTestString = "$GNRMC,112738.000,A,6530.4248,N,15006.7905,W,0.00,0.00,090619,,,A*68\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = 65.5071,
            .latDirection = 'N',
            .lon = -150.1132,
            .lonDirection = 'W',
        },

        .expectedLatitudeHexData = "a3038342",
        .expectedLongitudeHexData = "fb1c16c3",
    },
    {
        .id = "d5c0e583ae874850a88c2906ba894d9f",
        .inputTestString = "$GNRMC,112738.000,A,3929.4992,N,09537.7106,E,0.00,0.00,090619,,,A*76\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = 39.4917,
            .latDirection = 'N',
            .lon = 95.6285,
            .lonDirection = 'E',
        },

        .expectedLatitudeHexData = "08f71d42",
        .expectedLongitudeHexData = "cb41bf42",
    },
    {
        .id = "f6b69ef6344943e9b1a8426bae9277ab",
        .inputTestString = "$GNRMC,112738.000,A,2144.0715,S,08633.9020,E,0.00,0.00,090619,,,A*61\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = -21.7345,
            .latDirection = 'S',
            .lon = 86.565,
            .lonDirection = 'E',
        },

        .expectedLatitudeHexData = "420eadc1",
        .expectedLongitudeHexData = "4821ad42",
    },
    {
        .id = "e96da16107bc4d8b90a5df81a8fe8d83",
        .inputTestString = "$GNRMC,112738.000,A,8048.0377,N,09306.8573,E,0.00,0.00,090619,,,A*7b\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = 80.8006,
            .latDirection = 'N',
            .lon = 93.1143,
            .lonDirection = 'E',
        },

        .expectedLatitudeHexData = "e899a142",
        .expectedLongitudeHexData = "863aba42",
    },
    {
        .id = "e7ecaeb58a61450fb79d97fa38b13aa9",
        .inputTestString = "$GNRMC,112738.000,A,6255.8369,N,04255.1656,E,0.00,0.00,090619,,,A*7b\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = 62.9306,
            .latDirection = 'N',
            .lon = 42.9194,
            .lonDirection = 'E',
        },

        .expectedLatitudeHexData = "efb87b42",
        .expectedLongitudeHexData = "77ad2b42",
    },
    {
        .id = "0b09726ba4a740ab9dff66087f4b9dfd",
        .inputTestString = "$GNRMC,112738.000,A,3458.0273,S,11144.6727,W,0.00,0.00,090619,,,A*7f\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = -34.9671,
            .latDirection = 'S',
            .lon = -111.7445,
            .lonDirection = 'W',
        },

        .expectedLatitudeHexData = "4fde0bc2",
        .expectedLongitudeHexData = "2f7ddfc2",
    },
    {
        .id = "ebebf832f3c54b41aed4e787e88ca38d",
        .inputTestString = "$GNRMC,112738.000,A,5359.3465,N,09718.5756,W,0.00,0.00,090619,,,A*63\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = 53.9891,
            .latDirection = 'N',
            .lon = -97.3096,
            .lonDirection = 'W',
        },

        .expectedLatitudeHexData = "d7f45742",
        .expectedLongitudeHexData = "849ec2c2",
    },
    {
        .id = "b299fcd33d014e89938ad1c5f0889240",
        .inputTestString = "$GNRMC,112738.000,A,1919.1645,N,14835.8319,W,0.00,0.00,090619,,,A*65\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = 19.3194,
            .latDirection = 'N',
            .lon = -148.5972,
            .lonDirection = 'W',
        },

        .expectedLatitudeHexData = "228e9a41",
        .expectedLongitudeHexData = "e29814c3",
    },
    {
        .id = "5b8a0cb531664fa1b9e876a337aaf6ac",
        .inputTestString = "$GNRMC,112738.000,A,6908.9955,N,13134.6060,E,0.00,0.00,090619,,,A*7a\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = 69.1499,
            .latDirection = 'N',
            .lon = 131.5768,
            .lonDirection = 'E',
        },

        .expectedLatitudeHexData = "0c4c8a42",
        .expectedLongitudeHexData = "a9930343",
    },
    {
        .id = "25f0ba9ff6e54223a7a9fa13c5641288",
        .inputTestString = "$GNRMC,112738.000,A,7626.2926,N,11048.1956,W,0.00,0.00,090619,,,A*66\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = 76.4382,
            .latDirection = 'N',
            .lon = -110.8033,
            .lonDirection = 'W',
        },

        .expectedLatitudeHexData = "5c0e9842",
        .expectedLongitudeHexData = "4a9bddc2",
    },
    {
        .id = "b971d0b65d10498daf9047b6e99936c3",
        .inputTestString = "$GNRMC,112738.000,A,4853.5130,N,08501.5440,W,0.00,0.00,090619,,,A*6f\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = 48.8919,
            .latDirection = 'N',
            .lon = -85.0257,
            .lonDirection = 'W',
        },

        .expectedLatitudeHexData = "4e914342",
        .expectedLongitudeHexData = "290daac2",
    },
    {
        .id = "65af2be5e5f64bd8a5c8fe0b8d5ba890",
        .inputTestString = "$GNRMC,112738.000,A,6423.1665,S,01708.5038,E,0.00,0.00,090619,,,A*63\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = -64.3861,
            .latDirection = 'S',
            .lon = 17.1417,
            .lonDirection = 'E',
        },

        .expectedLatitudeHexData = "afc508c2",
        .expectedLongitudeHexData = "34228941",
    },
    {
        .id = "f6eb9fc7f56743daa632a4d546838a6b",
        .inputTestString = "$GNRMC,112738.000,A,1014.5108,N,07815.6496,E,0.00,0.00,090619,,,A*77\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = 10.2418,
            .latDirection = 'N',
            .lon = 78.2608,
            .lonDirection = 'E',
        },

        .expectedLatitudeHexData = "6ade2341",
        .expectedLongitudeHexData = "88859c42",
    },
    {
        .id = "45d8590ff17d47bfabe79d52ee9dce9f",
        .inputTestString = "$GNRMC,112738.000,A,7357.2388,N,04309.7575,W,0.00,0.00,090619,,,A*62\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = 73.954,
            .latDirection = 'N',
            .lon = -43.1626,
            .lonDirection = 'W',
        },

        .expectedLatitudeHexData = "73e89342",
        .expectedLongitudeHexData = "81a62cc2",
    },
    {
        .id = "024ae2e8b32d4550a1a4a61560d7f62a",
        .inputTestString = "$GNRMC,112738.000,A,8159.8146,S,07920.7861,E,0.00,0.00,090619,,,A*6e\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = -81.9969,
            .latDirection = 'S',
            .lon = 79.3464,
            .lonDirection = 'E',
        },

        .expectedLatitudeHexData = "6afea3c2",
        .expectedLongitudeHexData = "5bb19e42",
    },
    {
        .id = "0a2aac73ab724d439b845dd4058931c1",
        .inputTestString = "$GNRMC,112738.000,A,4450.4591,N,12757.4631,E,0.00,0.00,090619,,,A*73\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = 44.841,
            .latDirection = 'N',
            .lon = 127.9577,
            .lonDirection = 'E',
        },

        .expectedLatitudeHexData = "2f5d3342",
        .expectedLongitudeHexData = "58eaff42",
    },
    {
        .id = "548187c54dc5452db6be93c095558d74",
        .inputTestString = "$GNRMC,112738.000,A,1201.2110,N,02806.6534,W,0.00,0.00,090619,,,A*63\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = 12.0202,
            .latDirection = 'N',
            .lon = -28.1109,
            .lonDirection = 'W',
        },

        .expectedLatitudeHexData = "bd520441",
        .expectedLongitudeHexData = "02e30ec1",
    },
    {
        .id = "a73530c599104447af7cba1d0bb2c4bc",
        .inputTestString = "$GNRMC,112738.000,A,8436.5556,S,10033.9912,E,0.00,0.00,090619,,,A*6c\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = -84.6093,
            .latDirection = 'S',
            .lon = 100.5665,
            .lonDirection = 'E',
        },

        .expectedLatitudeHexData = "f637a9c2",
        .expectedLongitudeHexData = "0c22c942",
    },
    {
        .id = "638738bb2f61456eb81b794b360a8b71",
        .inputTestString = "$GNRMC,112738.000,A,5637.8463,N,12755.4654,W,0.00,0.00,090619,,,A*62\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = 56.6308,
            .latDirection = 'N',
            .lon = -127.9244,
            .lonDirection = 'W',
        },

        .expectedLatitudeHexData = "0f856242",
        .expectedLongitudeHexData = "4bd9ffc2",
    },
    {
        .id = "7cb08da70abf409f9b7392051990cf41",
        .inputTestString = "$GNRMC,112738.000,A,5829.5811,S,01239.1660,E,0.00,0.00,090619,,,A*67\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = -58.493,
            .latDirection = 'S',
            .lon = 12.6528,
            .lonDirection = 'E',
        },

        .expectedLatitudeHexData = "d5f869c2",
        .expectedLongitudeHexData = "de714a41",
    },
    {
        .id = "d013f31c239a4b79a55cd9056dc16d2f",
        .inputTestString = "$GNRMC,112738.000,A,5610.2999,N,15935.9454,W,0.00,0.00,090619,,,A*65\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = 56.1717,
            .latDirection = 'N',
            .lon = -159.5991,
            .lonDirection = 'W',
        },

        .expectedLatitudeHexData = "d2af0642",
        .expectedLongitudeHexData = "5f991fc3",
    },
    {
        .id = "453a3f48ca874534af579c25d5d40dd4",
        .inputTestString = "$GNRMC,112738.000,A,4521.0990,S,08158.8831,E,0.00,0.00,090619,,,A*60\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = -45.3517,
            .latDirection = 'S',
            .lon = 81.9814,
            .lonDirection = 'E',
        },

        .expectedLatitudeHexData = "246835c2",
        .expectedLongitudeHexData = "7af6a342",
    },
    {
        .id = "14c717de2d5746979a8b04dfad30919f",
        .inputTestString = "$GNRMC,112738.000,A,1450.8191,S,10351.0164,E,0.00,0.00,090619,,,A*60\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = -14.847,
            .latDirection = 'S',
            .lon = 103.8503,
            .lonDirection = 'E',
        },

        .expectedLatitudeHexData = "058d6dc1",
        .expectedLongitudeHexData = "5bb3cf42",
    },
    {
        .id = "12fe4e246ad442ff9523a5644b5f9574",
        .inputTestString = "$GNRMC,112738.000,A,5653.6131,N,13251.5826,W,0.00,0.00,090619,,,A*66\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = 56.8936,
            .latDirection = 'N',
            .lon = -132.8597,
            .lonDirection = 'W',
        },

        .expectedLatitudeHexData = "0c936342",
        .expectedLongitudeHexData = "15dc04c3",
    },
    //
    // Failure Tests
    //
    {
        .id = "failure_1: reading never starts",
        .inputTestString = "GNRMC,112738.000,A,1024.8696,S,11338.0173,E,0.00,0.00,090619,,,A*6f\r\n",
        .expectedReadingStartIndication = false,
        .expectedReadingCompleteIndication = false,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,
    },
    {
        .id = "failure_2: reading never ends due to missing end char",
        .inputTestString = "$GNRMC,112738.000,A,1024.8696,S,11338.0173,E,0.00,0.00,090619,,,A*6f",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = false,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,
    },
    {
        .id = "failure_3: reading never ends due to exceeding maximum allowed length",
        .inputTestString = "$GNRMC,112738.000,A,1024.8696,S,11338.0173,E,0.00,0.00,090619,,,______________________________________________________________________________________________________________________________________________________________________________________________________________________________A*6f\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = false,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_MessageDidntEnd,
    },
    {
        .id = "failure_4: sentence not long enough error",
        .inputTestString = "$GNRM*6f\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_ParseError_SentenceNotLongEnough,
    },
    {
        .id = "failure_5: checksum not found error",
        .inputTestString = "$GNRMC,112738.000,A,2616.8042,S,02627.9844,W,0.00,0.00,090619,,,A7b\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_ParseError_ChecksumNotFound,
    },
    {
        .id = "failure_6: checksum not long enough error",
        .inputTestString = "$GNRMC,112738.000,A,7756.0664,N,15441.3672,E,0.00,0.00,090619,,,A*7\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_ParseError_ChecksumNotCorrectLength,
    },
    {
        .id = "failure_7: checksum not correct length error",
        .inputTestString = "$GNRMC,112738.000,A,7756.0664,N,15441.3672,E,0.00,0.00,090619,,,A*\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_ParseError_ChecksumNotCorrectLength,
    },
    {
        .id = "failure_8: checksum not correct length error",
        .inputTestString = "$GNRMC,112738.000,A,7756.0664,N,15441.3672,E,0.00,0.00,090619,,,A*444\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_ParseError_ChecksumNotCorrectLength,
    },
    {
        .id = "failure_9: checksum incorrect error",
        .inputTestString = "$GNRMC,112738.000,A,7756.0664,N,15441.3672,E,0.00,0.00,090619,,,A*4b\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_ParseError_ChecksumIncorrect,
    },
    {
        .id = "failure_9: checksum incorrect error",
        .inputTestString = "$GNRMC,112738.000,A,7756.0664,N,15441.3672,E,0.00,0.00,030619,,,A*7b\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_ParseError_ChecksumIncorrect,
    },
    {
        .id = "failure_10: talker decoding error",
        .inputTestString = "$GNRMC112738.000A2044.9182S12756.2106W0.000.00090619A*74\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_ParseError_TalkerDecoding,
    },
    {
        .id = "failure_11: talker decoding error",
        .inputTestString = "$GNRMC112738.000,A,2044.9182,S,12756.2106,W,0.00,0.00,090619,,,A*58\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_ParseError_TalkerDecoding,
    },
    {
        .id = "failure_12: talker decoding error",
        .inputTestString = "$GNRM,112738.000,A,8001.6791,S,08505.8932,E,0.00,0.00,090619,,,A*2f\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_ParseError_TalkerDecoding,
    },
    {
        .id = "failure_13: talker decoding error",
        .inputTestString = "$GNRMDC,112738.000,A,8001.6791,S,08505.8932,E,0.00,0.00,090619,,,A*28\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_ParseError_TalkerDecoding,
    },
    {
        .id = "failure_14: process gps reading error",
        .inputTestString = "$GNRMC,A*38\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_BlankReading,
            .lat = 0,
            .latDirection = '_',
            .lon = 0,
            .lonDirection = '_',
        },
    },
    {
        .id = "failure_15: process gps reading error",
        .inputTestString = "$GNRMC,,,,,,,,,,,,A*14\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_BlankReading,
            .lat = 0,
            .latDirection = '_',
            .lon = 0,
            .lonDirection = '_',
        },
    },
};

void test_function_make_gps(void)
{

    for (int caseIdx = 0; caseIdx < sizeof(cases) / sizeof(*cases); caseIdx++)
    {
        printf("Test ID: %s\n", cases[caseIdx].id);
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
                                      "Reading Complete Indication");
        TEST_ASSERT_EQUAL_INT_MESSAGE(cases[caseIdx].expectedPostReadingNMEASentenceErr,
                                      nmeaSentence.errorCode,
                                      "Post NMEA Sentence Reading Error");
        // if reading is not expected to start or complete - go to next test case from here
        if (!(cases[caseIdx].expectedReadingStartIndication && cases[caseIdx].expectedReadingCompleteIndication))
        {
            continue;
        }

        parseNMEASentence(&nmeaSentence);
        TEST_ASSERT_EQUAL_INT_MESSAGE(cases[caseIdx].expectedPostParse_NMEASentenceErr,
                                      nmeaSentence.errorCode,
                                      "Post Parse NMEA Sentence Error");
        // if a parse error is expected - go to next test case from here
        if (cases[caseIdx].expectedPostParse_NMEASentenceErr != NMEASentenceErr_NoError)
        {
            continue;
        }
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