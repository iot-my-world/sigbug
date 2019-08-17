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
        .id = "6597874fd60347a89a329e67e551be7c",
        .inputTestString = "$GNRMC,112738.000,A,8313.6166,S,07840.7790,W,0.00,0.00,090619,,,A*7a\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = -83.2269,
            .latDirection = 'S',
            .lon = -78.6796,
            .lonDirection = 'W',
        },
    },
    {
        .id = "d2f0d45ad90142eab722e03c1d439571",
        .inputTestString = "$GNRMC,112738.000,A,2147.2297,N,12913.1818,E,0.00,0.00,090619,,,A*7f\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = 21.7872,
            .latDirection = 'N',
            .lon = 129.2197,
            .lonDirection = 'E',
        },
    },
    {
        .id = "6c05cd937a8d4e59afc15b4b3826f26c",
        .inputTestString = "$GNRMC,112738.000,A,2042.3298,N,05225.0408,E,0.00,0.00,090619,,,A*71\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = 20.7055,
            .latDirection = 'N',
            .lon = 52.4173,
            .lonDirection = 'E',
        },
    },
    {
        .id = "b80cde938d4b46089fd70618c57b73ce",
        .inputTestString = "$GNRMC,112738.000,A,4624.7499,S,03415.1570,E,0.00,0.00,090619,,,A*63\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = -46.4125,
            .latDirection = 'S',
            .lon = 34.2526,
            .lonDirection = 'E',
        },
    },
    {
        .id = "0973ef0cd3dd41b7b65c297f7730bec5",
        .inputTestString = "$GNRMC,112738.000,A,4235.7552,S,05415.5159,W,0.00,0.00,090619,,,A*7e\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = -42.5959,
            .latDirection = 'S',
            .lon = -54.2586,
            .lonDirection = 'W',
        },
    },
    {
        .id = "d4ad5cb5b97548309cfa74cd85311861",
        .inputTestString = "$GNRMC,112738.000,A,3402.5802,S,01510.7315,E,0.00,0.00,090619,,,A*6b\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = -34.043,
            .latDirection = 'S',
            .lon = 15.1789,
            .lonDirection = 'E',
        },
    },
    {
        .id = "8eae7044c4c441da9ad0d63dc98e8654",
        .inputTestString = "$GNRMC,112738.000,A,1123.3709,S,14937.2913,W,0.00,0.00,090619,,,A*7b\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = -11.3895,
            .latDirection = 'S',
            .lon = -149.6215,
            .lonDirection = 'W',
        },
    },
    {
        .id = "e927de1d1b474fd582ac9fea3d3160e5",
        .inputTestString = "$GNRMC,112738.000,A,1008.8120,S,03310.7007,W,0.00,0.00,090619,,,A*75\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = -10.1469,
            .latDirection = 'S',
            .lon = -33.1783,
            .lonDirection = 'W',
        },
    },
    {
        .id = "93300bedc24e4b238d8f18861d51ec9b",
        .inputTestString = "$GNRMC,112738.000,A,4803.5680,S,05858.8217,W,0.00,0.00,090619,,,A*7e\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = -48.0595,
            .latDirection = 'S',
            .lon = -58.9804,
            .lonDirection = 'W',
        },
    },
    {
        .id = "383089f958fa4874b57dade07ec3a157",
        .inputTestString = "$GNRMC,112738.000,A,6046.5374,S,08655.1527,W,0.00,0.00,090619,,,A*78\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = -60.7756,
            .latDirection = 'S',
            .lon = -86.9192,
            .lonDirection = 'W',
        },
    },
    {
        .id = "c800ae899df9401b989e3ee1650d53a5",
        .inputTestString = "$GNRMC,112738.000,A,6850.2034,S,01603.5756,W,0.00,0.00,090619,,,A*7d\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = -68.8367,
            .latDirection = 'S',
            .lon = -16.0596,
            .lonDirection = 'W',
        },
    },
    {
        .id = "a1239af75efa4cfa83557b7bc2dd46a2",
        .inputTestString = "$GNRMC,112738.000,A,4643.9989,N,15626.0843,W,0.00,0.00,090619,,,A*66\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = 46.7333,
            .latDirection = 'N',
            .lon = -156.4347,
            .lonDirection = 'W',
        },
    },
    {
        .id = "1e8ed08096da40fb96d43dd6133922d0",
        .inputTestString = "$GNRMC,112738.000,A,2258.4821,N,06159.4571,E,0.00,0.00,090619,,,A*77\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = 22.9747,
            .latDirection = 'N',
            .lon = 61.991,
            .lonDirection = 'E',
        },
    },
    {
        .id = "f61a1d1271d64c448e7dc01257323bd9",
        .inputTestString = "$GNRMC,112738.000,A,7809.4363,S,07646.5720,W,0.00,0.00,090619,,,A*71\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = -78.1573,
            .latDirection = 'S',
            .lon = -76.7762,
            .lonDirection = 'W',
        },
    },
    {
        .id = "a93ce9761f56483bb67d52819a8f451d",
        .inputTestString = "$GNRMC,112738.000,A,5722.9823,S,02658.6264,W,0.00,0.00,090619,,,A*7b\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = -57.383,
            .latDirection = 'S',
            .lon = -26.9771,
            .lonDirection = 'W',
        },
    },
    {
        .id = "ca0c1bf6c64d42ff91a7d645578fcba4",
        .inputTestString = "$GNRMC,112738.000,A,4425.1482,S,02950.6005,E,0.00,0.00,090619,,,A*61\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = -44.4191,
            .latDirection = 'S',
            .lon = 29.8433,
            .lonDirection = 'E',
        },
    },
    {
        .id = "4d1e4ef2ea3a45b48f5f702168f624de",
        .inputTestString = "$GNRMC,112738.000,A,5210.4922,S,16224.5425,W,0.00,0.00,090619,,,A*78\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = -52.1749,
            .latDirection = 'S',
            .lon = -162.409,
            .lonDirection = 'W',
        },
    },
    {
        .id = "9899553bd7d5416f950cfa4ba6071e16",
        .inputTestString = "$GNRMC,112738.000,A,4814.8423,N,02549.6661,E,0.00,0.00,090619,,,A*70\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = 48.2474,
            .latDirection = 'N',
            .lon = 25.8278,
            .lonDirection = 'E',
        },
    },
    {
        .id = "040493f07b5c4b9a83077e6c0bfaee8c",
        .inputTestString = "$GNRMC,112738.000,A,5648.1583,N,01940.5510,E,0.00,0.00,090619,,,A*74\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = 56.8026,
            .latDirection = 'N',
            .lon = 19.6758,
            .lonDirection = 'E',
        },
    },
    {
        .id = "7b68b8772ae54e4e810096f55a07e4c6",
        .inputTestString = "$GNRMC,112738.000,A,4939.7904,S,09400.5406,W,0.00,0.00,090619,,,A*71\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = -49.6632,
            .latDirection = 'S',
            .lon = -94.009,
            .lonDirection = 'W',
        },
    },
    {
        .id = "8fc01e29bc1f404a88dd713c34f4453b",
        .inputTestString = "$GNRMC,112738.000,A,3329.8924,S,11332.2879,W,0.00,0.00,090619,,,A*7c\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = -33.4982,
            .latDirection = 'S',
            .lon = -113.5381,
            .lonDirection = 'W',
        },
    },
    {
        .id = "2aaea08738814fdabdcf8fcac58cf0ad",
        .inputTestString = "$GNRMC,112738.000,A,7221.8985,S,05833.7539,E,0.00,0.00,090619,,,A*6b\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = -72.365,
            .latDirection = 'S',
            .lon = 58.5626,
            .lonDirection = 'E',
        },
    },
    {
        .id = "36994209f18c4bbd90c5c4e284f86010",
        .inputTestString = "$GNRMC,112738.000,A,6629.0533,S,15550.1434,W,0.00,0.00,090619,,,A*7e\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = -66.4842,
            .latDirection = 'S',
            .lon = -155.8357,
            .lonDirection = 'W',
        },
    },
    {
        .id = "9a138089af604500964670c87d88712b",
        .inputTestString = "$GNRMC,112738.000,A,1234.4001,S,12409.3741,W,0.00,0.00,090619,,,A*78\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = -12.5733,
            .latDirection = 'S',
            .lon = -124.1562,
            .lonDirection = 'W',
        },
    },
    {
        .id = "d528605eee4a45f0b2e8f80d6bd92529",
        .inputTestString = "$GNRMC,112738.000,A,3320.6653,S,12201.5504,E,0.00,0.00,090619,,,A*64\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = -33.3444,
            .latDirection = 'S',
            .lon = 122.0258,
            .lonDirection = 'E',
        },
    },
    {
        .id = "67cf1202573b46108ffab0c2e0636f95",
        .inputTestString = "$GNRMC,112738.000,A,5038.6094,N,08144.1481,W,0.00,0.00,090619,,,A*6b\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = 50.6435,
            .latDirection = 'N',
            .lon = -81.7358,
            .lonDirection = 'W',
        },
    },
    {
        .id = "bf9da234fafd4bf89a803320b7b74d8a",
        .inputTestString = "$GNRMC,112738.000,A,7814.1756,S,06714.1257,W,0.00,0.00,090619,,,A*7c\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = -78.2363,
            .latDirection = 'S',
            .lon = -67.2354,
            .lonDirection = 'W',
        },
    },
    {
        .id = "c7f123508e3e49b09b73ec3627a4aa8b",
        .inputTestString = "$GNRMC,112738.000,A,8131.5344,N,05244.6038,W,0.00,0.00,090619,,,A*6c\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = 81.5256,
            .latDirection = 'N',
            .lon = -52.7434,
            .lonDirection = 'W',
        },
    },
    {
        .id = "75f764508cd14bce942e8b3a655ab656",
        .inputTestString = "$GNRMC,112738.000,A,4332.7903,N,07758.0600,W,0.00,0.00,090619,,,A*6b\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = 43.5465,
            .latDirection = 'N',
            .lon = -77.9677,
            .lonDirection = 'W',
        },
    },
    {
        .id = "db02dc96ecde4bd08260ec0a06e0081b",
        .inputTestString = "$GNRMC,112738.000,A,6951.8820,S,07013.0573,W,0.00,0.00,090619,,,A*7b\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = -69.8647,
            .latDirection = 'S',
            .lon = -70.2176,
            .lonDirection = 'W',
        },
    },
    {
        .id = "3727df6578594f8cb402e8541c8eafff",
        .inputTestString = "$GNRMC,112738.000,A,7535.6158,S,06723.8165,E,0.00,0.00,090619,,,A*60\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = -75.5936,
            .latDirection = 'S',
            .lon = 67.3969,
            .lonDirection = 'E',
        },
    },
    {
        .id = "2e4c256dda86409eb05a94212699338b",
        .inputTestString = "$GNRMC,112738.000,A,5236.1345,N,13352.4597,W,0.00,0.00,090619,,,A*63\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = 52.6022,
            .latDirection = 'N',
            .lon = -133.8743,
            .lonDirection = 'W',
        },
    },
    {
        .id = "e5f09b0f94d0490c9f2dbd6304223ec7",
        .inputTestString = "$GNRMC,112738.000,A,4017.0494,N,11017.3254,W,0.00,0.00,090619,,,A*66\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = 40.2842,
            .latDirection = 'N',
            .lon = -110.2888,
            .lonDirection = 'W',
        },
    },
    {
        .id = "4154ae6cfc6d459388841dca09629f6e",
        .inputTestString = "$GNRMC,112738.000,A,2639.8668,S,05651.7914,E,0.00,0.00,090619,,,A*66\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = -26.6644,
            .latDirection = 'S',
            .lon = 56.8632,
            .lonDirection = 'E',
        },
    },
    {
        .id = "df7b96abb4da4825aeb3633b6f68654f",
        .inputTestString = "$GNRMC,112738.000,A,1705.0977,N,16152.0642,W,0.00,0.00,090619,,,A*60\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = 17.085,
            .latDirection = 'N',
            .lon = -161.8677,
            .lonDirection = 'W',
        },
    },
    {
        .id = "ad2dd54519634ecc9eb4d77fe208dafc",
        .inputTestString = "$GNRMC,112738.000,A,3138.5400,S,12908.6234,E,0.00,0.00,090619,,,A*6d\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = -31.6423,
            .latDirection = 'S',
            .lon = 129.1437,
            .lonDirection = 'E',
        },
    },
    {
        .id = "81af40e3706d4048b3441def138893d8",
        .inputTestString = "$GNRMC,112738.000,A,6614.1902,S,05337.2954,E,0.00,0.00,090619,,,A*63\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = -66.2365,
            .latDirection = 'S',
            .lon = 53.6216,
            .lonDirection = 'E',
        },
    },
    {
        .id = "7dde13a2182a4b6baa98b9008fc776e2",
        .inputTestString = "$GNRMC,112738.000,A,2715.9440,S,15927.8979,E,0.00,0.00,090619,,,A*6b\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = -27.2657,
            .latDirection = 'S',
            .lon = 159.465,
            .lonDirection = 'E',
        },
    },
    {
        .id = "fd84378653054f11b959760e347b0487",
        .inputTestString = "$GNRMC,112738.000,A,8849.3597,N,11615.5205,E,0.00,0.00,090619,,,A*7c\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = 88.8227,
            .latDirection = 'N',
            .lon = 116.2587,
            .lonDirection = 'E',
        },
    },
    {
        .id = "bee85b9f0406485baa3708babce1c25d",
        .inputTestString = "$GNRMC,112738.000,A,2848.0299,S,10434.2664,E,0.00,0.00,090619,,,A*64\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = -28.8005,
            .latDirection = 'S',
            .lon = 104.5711,
            .lonDirection = 'E',
        },
    },
    {
        .id = "6806c51b961d4a0f9e4945eb84448950",
        .inputTestString = "$GNRMC,112738.000,A,5438.2432,S,08555.9209,E,0.00,0.00,090619,,,A*66\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = -54.6374,
            .latDirection = 'S',
            .lon = 85.932,
            .lonDirection = 'E',
        },
    },
    {
        .id = "71070193c24741b1b5abc6154293a162",
        .inputTestString = "$GNRMC,112738.000,A,1810.1077,N,14645.8945,W,0.00,0.00,090619,,,A*60\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = 18.1685,
            .latDirection = 'N',
            .lon = -146.7649,
            .lonDirection = 'W',
        },
    },
    {
        .id = "ca8dcef41a8944cb9d989bcd3854ad37",
        .inputTestString = "$GNRMC,112738.000,A,3829.7530,N,04643.8245,W,0.00,0.00,090619,,,A*64\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = 38.4959,
            .latDirection = 'N',
            .lon = -46.7304,
            .lonDirection = 'W',
        },
    },
    {
        .id = "9a6e718fa4db4f13991ebcff77786b8e",
        .inputTestString = "$GNRMC,112738.000,A,2303.7151,S,11519.8779,E,0.00,0.00,090619,,,A*68\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = -23.0619,
            .latDirection = 'S',
            .lon = 115.3313,
            .lonDirection = 'E',
        },
    },
    {
        .id = "44127b86db7c49adab339153e0c26600",
        .inputTestString = "$GNRMC,112738.000,A,5635.0171,S,01820.5329,E,0.00,0.00,090619,,,A*60\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = -56.5836,
            .latDirection = 'S',
            .lon = 18.3422,
            .lonDirection = 'E',
        },
    },
    {
        .id = "d3b3aa91ddad41479abae87e0e60465d",
        .inputTestString = "$GNRMC,112738.000,A,2044.9182,S,12756.2106,W,0.00,0.00,090619,,,A*74\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = -20.7486,
            .latDirection = 'S',
            .lon = -127.9368,
            .lonDirection = 'W',
        },
    },
    {
        .id = "0976c430155d4371aa0e4214f88c4683",
        .inputTestString = "$GNRMC,112738.000,A,7756.0664,N,15441.3672,E,0.00,0.00,090619,,,A*7b\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = 77.9344,
            .latDirection = 'N',
            .lon = 154.6895,
            .lonDirection = 'E',
        },
    },
    {
        .id = "b72f150f79494b6897f70d7b5599c149",
        .inputTestString = "$GNRMC,112738.000,A,3841.7570,S,06555.8902,E,0.00,0.00,090619,,,A*6f\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = -38.6959,
            .latDirection = 'S',
            .lon = 65.9315,
            .lonDirection = 'E',
        },
    },
    {
        .id = "4c3c1154632d4a8b97d5749fffaa0d28",
        .inputTestString = "$GNRMC,112738.000,A,8001.6791,S,08505.8932,E,0.00,0.00,090619,,,A*6c\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = -80.028,
            .latDirection = 'S',
            .lon = 85.0982,
            .lonDirection = 'E',
        },
    },
    {
        .id = "6363e9c842ba4ad5a5396084afb6a87f",
        .inputTestString = "$GNRMC,112738.000,A,2616.8042,S,02627.9844,W,0.00,0.00,090619,,,A*7b\r\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = -26.2801,
            .latDirection = 'S',
            .lon = -26.4664,
            .lonDirection = 'W',
        },
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