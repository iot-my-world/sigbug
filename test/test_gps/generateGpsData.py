import random
import math
from numpy import float32
from string import Template

nmeaSentenceTemplate = Template(
    "$$GNRMC,112738.000,A,$latitudeNMEA,$latDirection,$longitudeNMEA,$lonDirection,0.00,0.00,090619,,,A")

testCaseTemplate = Template('''{
        .inputTestString = "$nmeaSentence\\r\\n",
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


def calculate_checksum(value):
    checksum = 0
    for c in value:
        checksum ^= ord(c)
    checksum = hex(checksum).strip('0x')
    return checksum if len(checksum) == 2 else '0'*(2 - len(checksum)) + checksum


def generate_test_case(latitude, latitude_direction, longitude, longitude_direction):
    # process latitude
    latitude_fractional_parts = str(
        round(math.modf(latitude)[0] * 60.00, 4)).split('.')
    latitude_degree_part = str(int(math.modf(latitude)[1]))
    latitude_nmea = '0' * (2 - len(latitude_degree_part)) + latitude_degree_part + '0' * (2 - len(
        latitude_fractional_parts[0])) + latitude_fractional_parts[0] + '.' + latitude_fractional_parts[1] + '0' * (4 - len(latitude_fractional_parts[1]))
    signed_latitude = float32(round(latitude_direction[1] * (float32(float(latitude_nmea[:latitude_nmea.find(
        '.') - 2])) + float32(float(latitude_nmea[latitude_nmea.find('.') - 2:])) / 60.00), 4))
    lat_hex_bytes = ['00' if b == 0 else hex(b).strip(
        '0x') for b in signed_latitude.tobytes('C')]
    lat_hex_value = ''.join(
        b if len(b) == 2 else '0' + b for b in lat_hex_bytes)

    # random longitude
    longitude_fractional_parts = str(
        round(math.modf(longitude)[0] * 60.00, 4)).split('.')
    longitude_degree_part = str(int(math.modf(longitude)[1]))
    longitude_nmea = '0' * (3 - len(longitude_degree_part)) + longitude_degree_part + '0' * (2 - len(
        longitude_fractional_parts[0])) + longitude_fractional_parts[0] + '.' + longitude_fractional_parts[1] + '0' * (4 - len(longitude_fractional_parts[1]))
    signed_longitude = float32(round(longitude_direction[1] * (float32(float(longitude_nmea[:longitude_nmea.find(
        '.') - 2])) + float32(float(longitude_nmea[longitude_nmea.find('.') - 2:])) / 60.00), 4))
    lon_hex_bytes = ['00' if b == 0 else hex(b).strip(
        '0x') for b in signed_longitude.tobytes('C')]
    lon_hex_value = ''.join(
        b if len(b) == 2 else '0' + b for b in lon_hex_bytes)

    # create sentence
    nmea_sentence = nmeaSentenceTemplate.substitute({
        'latitudeNMEA': latitude_nmea,
        'latDirection': latitude_direction[0],

        'longitudeNMEA': longitude_nmea,
        'lonDirection': longitude_direction[0],
    })

    return testCaseTemplate.substitute({
        'nmeaSentence': nmea_sentence + "*" + calculate_checksum(nmea_sentence[1:]),
        'latDirection': latitude_direction[0],
        'signedLatitude': signed_latitude,

        'lonDirection': longitude_direction[0],
        'signedLongitude': signed_longitude,
    })


if __name__ == '__main__':
    # test = "$GNRMC,112738.000,A,2608.9935,S,02808.1064,E,0.00,0.00,090619,,,A*6F"
    # checkSection = test[1:test.find('*')]
    # print(calculate_checksum(checkSection))
    # print(generate_test_case(26.1499, ('S', -1.00), 28.1351, ('E', 1.00)))

    for i in range(10):
        # random latitude
        latDirection = random.choice([('N', 1.00), ('S', -1.00)])
        latitudeValue = float32(random.uniform(10, 89))

        # random longitude
        lonDirection = random.choice([('E', 1.00), ('W', -1.00)])
        longitudeValue = float32(random.uniform(10, 170))

        print(generate_test_case(latitudeValue,
                                 latDirection, longitudeValue, lonDirection))
