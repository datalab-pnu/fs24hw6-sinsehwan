#ifndef DELIM
#define DELIM

#include <iostream>
#include <string>
#include "varlen.h"

using namespace std;

class DelimFieldBuffer: public VariableLengthBuffer
{
public:
    DelimFieldBuffer(char delim = -1);
    DelimFieldBuffer(const DelimFieldBuffer& buffer); //복사 생성자

    void Clear();
    int Init(char delim = 0);

    int Pack(const string& field);
    int Unpack(string& field);

    void Print(ostream&) const;
    static void SetDefaultDelim(char delim);
protected:
    char Delim;
    static char DefaultDelim;
};


#endif