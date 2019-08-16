import random
import math
from numpy import float32
from string import Template

template = Template('''{
        .inputTestString = "$$GNRMC,112738.000,A,2608.9935,S,02808.1064,E,0.00,0.00,090619,,,A*6F\\r\\n",
        .expectedReadingStartIndication = true,
        .expectedReadingCompleteIndication = true,
        .expectedPostReadingNMEASentenceErr = NMEASentenceErr_NoError,

        .expectedPostParse_NMEASentenceErr = NMEASentenceErr_NoError,
        .expectedNMEATalkerIdentifier = "GN",
        .expectedNMEASentenceIdentifier = "RMC",

        .expectedGPSReading = (gpsReading){
            .error = NMEASentenceErr_processGPSNMEASentence_NoError,
            .lat = $signedLatitude,
            .latDirection = '$latDirection',
            .lon = $signedLongitude,
            .lonDirection = '$lonDirection',
        },
},''')

if __name__ == '__main__':
    for i in range(1):
        # random latitude
        latDirection = random.choice([('N', 1), ('S', -1)])
        latitudeValue = float32(random.uniform(10, 89))

        latitudeFractionalParts = str(
            round(math.modf(latitudeValue)[0]*60, 4)).split('.')
        latitudeDegreePart = str(int(math.modf(latitudeValue)[1]))
        print('0'*(2-len(latitudeDegreePart))+latitudeDegreePart+'0' *
              (2-len(latitudeFractionalParts[0]))+latitudeFractionalParts[0]+'.'+'0'*(4-len(latitudeFractionalParts[1]))+latitudeFractionalParts[1])

        signedLatitude = float32(latDirection[1]*random.uniform(10, 89))
        latHexBytes = ['00' if b == 0 else hex(b).strip(
            '0x') for b in signedLatitude.tobytes('C')]
        latHexValue = ''.join(
            b if len(b) == 2 else '0' + b for b in latHexBytes)

        # random longitude
        lonDirection = random.choice([('E', 1), ('W', -1)])
        signedLongitude = float32(lonDirection[1]*random.uniform(10, 179))
        lonHexBytes = ['00' if b == 0 else hex(b).strip(
            '0x') for b in signedLongitude.tobytes('C')]
        lonHexValue = ''.join(
            b if len(b) == 2 else '0' + b for b in lonHexBytes)
        # print(template.substitute({
        #     'signedLatitude': signedLatitude,
        #     'latDirection': latDirection[0],
        #     'signedLongitude': signedLongitude,
        #     'lonDirection': lonDirection[0],
        # }))
