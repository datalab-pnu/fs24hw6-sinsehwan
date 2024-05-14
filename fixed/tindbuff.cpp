// tindbuff.cpp
#include "tindbuff.h"


// buffer fields consist of 
//    numKeys, actual number of keys
//    Keys [maxKeys] key fields size = maxKeys * keySize
//    RecAddrs [maxKeys] record address fields size = maxKeys*sizeof(int)
TextIndexBuffer::TextIndexBuffer (int keySize, int maxKeys, 
								  int extraFields, int extraSpace)
: FixedFieldBuffer (1+2*maxKeys+extraFields, 
		sizeof(int)+maxKeys*keySize+maxKeys*sizeof(int) + extraSpace)
{
	MaxKeys = maxKeys;
	KeySize = keySize;
	AddField (sizeof(int));
	for (int i = 0; i < maxKeys; i++)
	{
		AddField (KeySize);
		AddField (sizeof(int));
	}
	Dummy = new char[keySize+1];
}

int TextIndexBuffer::Pack (const TextIndex & index)
{
	int result;
	Clear ();
	string temp = to_string(index.NumKeys);
	result = FixedFieldBuffer::Pack (temp);
	for (int i = 0; i < index.NumKeys; i++)
	{// note only pack the actual keys and recaddrs
		temp = string(index.Keys[i]);
		result = result && FixedFieldBuffer::Pack (temp);
		temp = to_string(index.RecAddrs[i]);
		result = result && FixedFieldBuffer::Pack (temp);
	}
	for (int j = 0; j<index.MaxKeys-index.NumKeys; j++)
	{// pack dummy values for other fields
		result = result && FixedFieldBuffer::Pack (Dummy);
		result = result && FixedFieldBuffer::Pack (Dummy);
	}
	return result;
}

int TextIndexBuffer::Unpack	(TextIndex & index) 
{
	int result;
	string temp;
	result = FixedFieldBuffer::Unpack (temp);
	index.NumKeys = stoi(temp);
	for (int i = 0; i < index.NumKeys; i++)
	{// note only pack the actual keys and recaddrs
		index.Keys[i] = new char[KeySize]; // just to be safe
		result = result && FixedFieldBuffer::Unpack (temp);
		index.Keys[i] = strdup(temp.c_str());
		result = result && FixedFieldBuffer::Unpack (temp);
		index.RecAddrs[i] = stoi(temp);
	}
	for (int j = 0; j<index.MaxKeys-index.NumKeys; j++)
	{// pack dummy values for other fields
		result = result && FixedFieldBuffer::Unpack (temp);
		Dummy = strdup(temp.c_str());
		result = result && FixedFieldBuffer::Unpack (temp);
		Dummy = strdup(temp.c_str());
	}
	return result;
}

void TextIndexBuffer:: Print (ostream & stream) const
{
	stream <<"TextIndexBuffer: KeySize "<<KeySize
		<<" MaxKeys "<<MaxKeys<<endl;
	FixedFieldBuffer :: Print (stream);
}

