#include <String.h>
#include <stdlib.h>

//
// Constructors and Destructor
//
String::String(int reservedSize)
{
    _array = (char *)malloc(reservedSize * sizeof(char));
    _array[0] = '\0';
    _used = 0;
    _reservedSize = reservedSize;
};

String::~String(){

};

void String::Add(char a)
{
    if (_used == _reservedSize)
    {
        return;
    }
    _array[_used] = a;
    _array[_used + 1] = '\0';
    _used++;
};

void String::Free(void)
{
    free(_array);
    _array = NULL;
    _used = 0;
};

void String::Clear(void)
{
    Free();
    _array = (char *)malloc(_reservedSize * sizeof(char));
    _array[0] = '\0';
    _used = 0;
};

char *String::Value(void)
{
    return _array;
};