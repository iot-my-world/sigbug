#ifndef String_h
#define String_h

class String
{
private:
    char *_array;
    int _used;
    int _reservedSize;

public:
    //
    // Constructors and Destructor
    //
    String(int initialSize);
    ~String();

    void Free(void);
    void Clear(void);

    void operator+=(char a);

    char *Value(void);
};

#endif