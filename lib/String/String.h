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

    void Add(char a);
    void Free(void);
    void Clear(void);

    char *Value(void);
};

#endif