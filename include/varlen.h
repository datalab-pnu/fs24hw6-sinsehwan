#ifndef VARLEN
#define VARLEN

#include "ioBuffer.h"

class VariableLengthBuffer: public IOBuffer
{
public:
    VariableLengthBuffer();
    int Init();
    void Clear();

    int Read(istream &);
    int Write(ostream &) const;
    int SizeOfBuffer() const; // return current size of buffer
    void Print(ostream &) const;
};

#endif