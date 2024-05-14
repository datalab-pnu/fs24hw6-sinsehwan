#include "varlen.h"
#include <string>
#include <iostream>

using namespace std;

VariableLengthBuffer::VariableLengthBuffer()
    : IOBuffer()
{
    Init();  
}

void VariableLengthBuffer::Clear()
{
    IOBuffer::Clear();
}

int VariableLengthBuffer::Read(istream& stream)
{
    if (stream.fail()) return -1;
    int recaddr = stream.tellg();
    Clear();
    unsigned short bufferSize;
    stream.read((char*)&bufferSize, sizeof(bufferSize));
    if(!stream.good()) {stream.clear(); return -1;}
    BufferSize = bufferSize;
    char* temp = new char[BufferSize]; // char* -> string
    stream.read(temp, BufferSize);
    string data(temp, BufferSize);
    Buffer = data;
    if(!stream.good()) {stream.clear(); return -1;}
    return recaddr;
}

int VariableLengthBuffer::Write(ostream& stream) const
{
    int recaddr = stream.tellp(); // 현재 sp값 저장
    unsigned short bufferSize = Buffer.size();
    stream.write((char *)&bufferSize, sizeof(bufferSize)); // write bufferSize
    if(!stream) return -1;
    stream.write(Buffer.c_str(), Buffer.size());
    if (!stream.good()) return -1;
    return recaddr;
}

void VariableLengthBuffer::Print(ostream& stream) const
{
    IOBuffer::Print(stream);
}

int VariableLengthBuffer::Init()
{
    Clear();
    return true;
}