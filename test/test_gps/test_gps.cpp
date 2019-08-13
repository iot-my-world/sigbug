// #include <NMEASentence.h>
#include <unity.h>

// void setUp(void) {
// // set stuff up here
// }

// void tearDown(void) {
// // clean stuff up here
// }

void test_function_make_gps(void)
{
    TEST_ASSERT_EQUAL(32, 32);
}

int main(int argc, char **argv)
{
    UNITY_BEGIN();
    RUN_TEST(test_function_make_gps);
    UNITY_END();

    return 0;
}