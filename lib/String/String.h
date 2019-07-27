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

    //
    // Other Methods
    //
    /*
        Free() frees memory occupied by the character array of
        the string object. This is intended to be used in the
        destruction of a string object.
     */
    void Free(void);
    /*
        Clear() reinitialises the string object to a blank
        string.
     */
    void Clear(void);
    /*
        SpaceLeft() returns true if there is still space left
        for more characters in the character array of the string
        object.
     */
    bool SpaceLeft(void);

    /*
        len() returns the length of the string, not
        including the terminating '\\0' character.
     */
    int len(void);

    void operator+=(char a);

    char *Value(void);
};

#endif