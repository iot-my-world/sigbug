#include <NMEASentence.h>

//
// Constructors and Destructor
//
NMEASentence::NMEASentence(void)
{
    // initialise processing variables
    _readingStarted = false;
    _readingComplete = false;

    // initialise error code
    _errorCode = NMEASentenceErr_NoError;
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

char NMEASentence::errorCode(void)
{
    return _errorCode;
}

//
// Other Methods
//
void NMEASentence::reset(void)
{
    _string.Clear();
    _readingStarted = false;
    _readingComplete = false;
    _errorCode = NMEASentenceErr_NoError;
}

void NMEASentence::readChar(char c)
{
    if (_readingComplete)
    {
        // if reading is already complete, do not do anything
        // the sentence needs to be reset before more reading can take place
        return;
    }

    if (_readingStarted)
    {
        // if reading has already started

        // check that there is space left in the string
        if (!_string.SpaceLeft())
        {
            // if there is no space left at this point,
            // then we have run out of space while the
            // message is being read and so the message didn't
            // end in the alloted memory of 75 bytes
            _errorCode = NMEASentenceErr_MessageDidntEnd;
            return;
        }

        // add the new character to the sentence string
        _string += c;

        if (c == '\n')
        {
            // mark if this is the end of the sentence
            _readingComplete = true;

            // parse the read sentence
            _parse();
        }
    }
    else
    {
        // otherwise reading has not yet started,
        // check for the start string character
        if (c == '$')
        {
            // check that there is space left in the string
            if (!_string.SpaceLeft())
            {
                // if there is no space in the string at this point
                // then the reading cannot start
                _errorCode = NMEASentenceErr_StringOutOfMemory;
                return;
            }

            // if this is the sentence start character
            // mark that reading has started
            _readingStarted = true;

            // add new character to string
            _string += c;
        }
    }
}

void NMEASentence::_parse(void)
{
    // check for minimum length
    if (_string.len() < 11)
    {
        _errorCode = NMEASentenceErr_ParseError;
        return;
    }
}