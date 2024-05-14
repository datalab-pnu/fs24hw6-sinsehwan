#ifndef INDFILE_H
#define INDFILE_H

#include "recfile.h"
#include "tindbuff.h"
#include <strstream>
#include <cstring>
#include <iostream>

using namespace std;


// template class to support direct read and write of records
// The template parameter RecType must support the following
//	int Pack (BufferType &); pack record into buffer
//	int Unpack (BufferType &); unpack record from buffer

template <class RecType>
class TextIndexedFile
{
public:
	int Read (RecType & record); // read next record
	int Read (char * key, RecType & record); // read by key
	int Append (const RecType & record);
	int Update (char * oldKey, const RecType & record);
	int Create (char * name, ios_base::openmode mode=ios::in|ios::out);
	//int Create (char * name, int mode=ios::in|ios::out);
	int Open (char * name, ios_base::openmode mode=ios::in|ios::out);
	//int Open (char * name, int mode=ios::in|ios::out);
	int Close ();
	TextIndexedFile (IOBuffer & buffer, int keySize, int maxKeys = 100); 
	~TextIndexedFile (); // close and delete
protected:
	TextIndex Index;
	BufferFile IndexFile;
	TextIndexBuffer IndexBuffer;
	RecordFile<RecType> DataFile;
	char * FileName; // base file name for file
	int SetFileName(char * fileName,
		char *& dataFileName, char *& indexFileName);
};


#endif
