import random
from numpy import float32
from functions.functions import generate_test_case


if __name__ == '__main__':
    for i in range(10):
        # random latitude
        latDirection = random.choice([('N', 1.00), ('S', -1.00)])
        latitudeValue = float32(random.uniform(10, 89))

        # random longitude
        lonDirection = random.choice([('E', 1.00), ('W', -1.00)])
        longitudeValue = float32(random.uniform(10, 170))

        print(generate_test_case(latitudeValue,
                                 latDirection, longitudeValue, lonDirection))
