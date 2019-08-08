g++ -std=c++11 -stdlib=libc++  test.cpp main.cpp -lgtest -lpthread -o test
./test
rm test