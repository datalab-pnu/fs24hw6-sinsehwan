#ifndef IO_BUFFER
#define IO_BUFFER
#include <iostream>
#include <string>

using namespace std;


class IOBuffer
{
public:
    IOBuffer();
    virtual void Clear(); // buffer clear
    int Init();

    virtual int Read(istream &) = 0; // read buffer
    virtual int Write(ostream &) const = 0;

    virtual int Pack(const string& field) = 0;
    virtual int Unpack(string& field) = 0;

    // these are the direct access read and write operations
	virtual int DRead(istream &, int recref); // read specified record
	virtual int DWrite(ostream &, int recref) const; // write specified record

	// these header operations return the number of bytes in the header
	virtual int ReadHeader(istream &); // write a buffer to the stream
	virtual int WriteHeader(ostream &) const; // write a buffer to the stream    

    virtual void Print(ostream &) const;

protected:
    bool Initalized;
    string Buffer;
    int BufferSize; // size of packed fileds
    int NextByte; // index of next byte to be unpacked/packed
    bool Packing; // true-> packing, false-> unpacking
};

#endif