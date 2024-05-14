#include "delim.h"
#include <string>

using namespace std;

DelimFieldBuffer::DelimFieldBuffer(char delim)
    :VariableLengthBuffer()
{
    Init(delim);
}

int DelimFieldBuffer::Init(char delim)
{
    Initalized = true;
    Clear();
    if (delim == -1) 
    {
        Delim = DefaultDelim;
    }
    else
    {
        Delim = delim;
    }
    return true;
}

void DelimFieldBuffer::Clear()
{
    VariableLengthBuffer::Clear();
}


// using string
int DelimFieldBuffer::Pack(const string& field)
{
    int len = field.size();
    Buffer.append(field);
    Buffer.push_back(Delim);
    NextByte += len + 1;
    BufferSize = NextByte;
    return len;
}

int DelimFieldBuffer::Unpack(string& field)
{
    int len = -1;
    int start = NextByte;
    for (int i = start; i < BufferSize; i++)
    {
        if (Buffer[i] == Delim)
        {
            len = i - start;
            break;            
        }
    }

    if (len == -1) return -1;//delimeter not found
    NextByte += len + 1;
    if(NextByte > BufferSize) return -1;

    // unpack연산
    field.assign(&Buffer[start], len);
    return len;
}

void DelimFieldBuffer::Print(ostream& stream) const
{
    VariableLengthBuffer::Print(stream);
    stream << " Delimiter '" << Delim << "'" << endl;
}

void DelimFieldBuffer::SetDefaultDelim(char Delim)
{
    DefaultDelim = Delim;
}

char DelimFieldBuffer::DefaultDelim = '|';