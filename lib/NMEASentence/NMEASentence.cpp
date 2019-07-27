#include <NMEASentence.h>

//
// Constructors and Destructor
//
NMEASentence::NMEASentence(void)
{
    // initialise processing variables
    _readingStarted = false;
    _readingComplete = false;
}

NMEASentence::~NMEASentence(void)
{
    // clear memory occupied by string
    _string.Free();
}

//
// Getters and Setters
//
String NMEASentence::string(void)
{
    return _string;
}
bool NMEASentence::readingStarted(void)
{
    return _readingStarted;
}

bool NMEASentence::readingComplete(void)
{
    return _readingComplete;
}

//
// Other Methods
//
void NMEASentence::reset(void)
{
    _string.Clear();
    _readingStarted = false;
    _readingComplete = false;
}

void NMEASentence::readChar(char c)
{
    // if reading is already complete, do not do anything
    // the sentence needs to be reset before more reading can take place
    if (_readingComplete)
    {
        return;
    }

    if (_readingStarted)
    {
        // if reading has already started
        // add the new character to the sentence string
        _string += c;

        // check if this is the end of the sentence
        if (c == '\n')
        {
            _readingComplete = true;
        }
    }
    else
    {
        // otherwise reading has not yet started,
        // if this is the sentence start character...
        if (c == '$')
        {
            // ...mark that reading has started
            _readingStarted = true;
            _string += c;
        }
        // ...otherwise do nothing
    }
}