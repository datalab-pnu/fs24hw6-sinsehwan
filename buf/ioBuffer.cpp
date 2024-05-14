#include "ioBuffer.h"
#include <cstring>

IOBuffer::IOBuffer() 
    : Initalized(false), BufferSize(0), NextByte(0), Packing(false)
{}

int IOBuffer::Init()
{
    Initalized = false;
    Buffer = "";
    BufferSize = 0;
    Clear();
    return 1;
}

int IOBuffer::DRead(istream & stream, int recref)
// read specified record
{
	stream.seekg(recref, ios::beg);
	if (stream.tellg() != recref) return -1;
	return Read (stream);
}

int IOBuffer::DWrite (ostream & stream, int recref) const
// write specified record
{
	stream.seekp(recref, ios::beg);
	if (stream.tellp() != recref) return -1;
	return Write (stream);
}

static const char * headerStr = "IOBuffer";
static const int headerSize = strlen(headerStr);

int IOBuffer::ReadHeader(istream & stream) 
{
	char str[headerSize+1];
	stream.seekg(0, ios::beg);
	stream.read(str, headerSize);
	if (!stream. good() ) return -1;
	if (strncmp(str, headerStr, headerSize)==0) return headerSize;
	else return -1;
}

int IOBuffer::WriteHeader(ostream & stream) const
{
	stream.seekp(0, ios::beg);
	stream.write(headerStr, headerSize);
	if (! stream.good() ) return -1;
	return headerSize;
}


void IOBuffer::Clear()
{
    NextByte = 0;
    Buffer = "";
    Packing = true;
}

void IOBuffer::Print(ostream& stream) const
{
    stream << "BufferSize " << BufferSize;
}