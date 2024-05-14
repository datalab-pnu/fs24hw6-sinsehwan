#include "indfile.h"
//#include "student.h"
//#include "courseRegistration.h"

// template method bodies
template <class RecType>
int TextIndexedFile<RecType>::Read (RecType & record)
{	
	int result = DataFile . Read (record, -1);
	return result;

}

template <class RecType>
int TextIndexedFile<RecType>::Read (char * key, RecType & record)
{
	int ref = Index.Search(key);
	if (ref < 0) return -1;
	int result = DataFile . Read (record, ref);
	return result;
}


template <class RecType>
int TextIndexedFile<RecType>::Append (const RecType & record)
{
	char * key = record.Key();
	int ref = Index.Search(key);
	if (ref != -1) // key already in file
		return -1;
	ref = DataFile . Append(record);
	int result = Index . Insert (key, ref);
	return ref;
}

// Update is left as an exercise. 
//	It requires BufferFile::Update, and BufferFile::Delete
template <class RecType>
int TextIndexedFile<RecType>::Update (char * oldKey, const RecType & record)
{	return -1;}

// generate names for the data file and the index file
template <class RecType>
int TextIndexedFile<RecType>::SetFileName(char * fileName,
	char *& dataFileName, char *& indexFileName)
{
	if (FileName != 0) // object is already attached to a file
		return 0;
	// set FileName member
	FileName = strdup(fileName);
	// generate real file names
	ostrstream dataName, indexName;
	dataName << FileName <<".dat"<<ends;
	indexName<< FileName<<".ind"<<ends;
	dataFileName = strdup(dataName . str());
	indexFileName = strdup(indexName . str());
	return 1;
}



// use fileName.dat and fileName.ind
template <class RecType>
int TextIndexedFile<RecType>::Create (char * fileName, ios_base::openmode mode)
//int TextIndexedFile<RecType>::Create (char * fileName, int mode)
{
	int result;
	char * dataFileName, * indexFileName;
	result = SetFileName(fileName, dataFileName, indexFileName);
	cout <<"file names "<<dataFileName<<" "<<indexFileName<<endl;
	if (result == -1) return 0;
	result = DataFile.Create(dataFileName, mode);
	if (!result)
	{
		FileName = 0; // remove connection
		return 0;
	}
	result = IndexFile.Create(indexFileName, ios::out|ios::in);
	if (!result)
	{
		DataFile.Close(); // close the data file
		FileName = 0; // remove connection
		return 0;
	}
	return 1;
}

// open data and index file and read index file
template <class RecType>
int TextIndexedFile<RecType>::Open (char * fileName, ios_base::openmode mode)
//int TextIndexedFile<RecType>::Open (char * fileName, int mode)
{
	int result;
	char * dataFileName, * indexFileName;
	result = SetFileName (fileName, dataFileName, indexFileName);
	if (!result) return 0;
	// open files
	result = DataFile.Open (dataFileName, mode);
	if (!result)
	{
		FileName = 0; // remove connection
		return 0;
	}
	result = IndexFile.Open (indexFileName, ios::out);
	if (!result)
	{
		DataFile . Close(); // close the data file
		FileName = 0; // remove connection
		return 0;
	}
	// read index into memory
	result = IndexFile . Read ();
	if (result != -1)
	{
		result = IndexBuffer . Unpack (Index);
		if (result != -1) return 1;
	}
	// read or unpack failed!
	DataFile.Close();
	IndexFile.Close();
	FileName = 0;
	return 0;
}


template <class RecType>
int TextIndexedFile<RecType>::Close()
{	int result;
	if (!FileName) return 0; // already closed!
	DataFile.Close();
	IndexFile.Rewind();
	IndexBuffer.Pack(Index);
	result = IndexFile.Write ();
	cout <<"result of index write: "<<result<<endl;
	IndexFile.Close ();
	FileName = 0;
	return 1;
}

template <class RecType>
TextIndexedFile<RecType>::TextIndexedFile (IOBuffer & buffer,
		int keySize, int maxKeys)
	:DataFile(buffer), Index (maxKeys), 
	IndexFile(IndexBuffer), IndexBuffer(keySize, maxKeys)
{
	FileName = 0;
}

template <class RecType>
TextIndexedFile<RecType>::~TextIndexedFile ()
{	Close(); }


// for template separate compile
template class TextIndexedFile<CourseRegistration>;
template class TextIndexedFile<Student>;