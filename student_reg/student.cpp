#include "student.h"
#include <string>
#include <istream>
#include <sstream>
#include <cstring>

Student::Student(int i, string n, string a, Date f, int c)
 : id(i), name(n), address(a), firstDate(f), completedCreditHours(c)
{}

Student& Student::operator=(const Student& rvalue)
{
	if(this != &rvalue)
	{
		id = rvalue.getID();
		name = rvalue.getName();
		address = rvalue.getAddress();
		firstDate.setDate(rvalue.getFirstDate().getDate());
		firstDate.setMonth(rvalue.getFirstDate().getMonth());
	}

	return *this;
}

ostream& operator<<(ostream& ostr, const Student& s)
{
	ostr << s.getID() << '|';
	ostr << s.getName() << '|';
	ostr << s.getAddress() << '|';
	// Date클래스도 <<연산자 오버로딩 완료
	ostr << s.getFirstDate() << '|';
	ostr << s.getCch() << '|';
	return ostr;
}
		

istream& operator>>(istream& istr, Student& s)
{	
	//printf("id : ");
	string id, h;
	getline(istr, id, '|');
	s.id = stoi(id);
	getline(istr, s.name, '|');
	getline(istr, s.address, '|');
	istr >> s.firstDate;
	getline(istr, h, '|');
	s.completedCreditHours = stoi(h);
	return istr;
}

int Student::Pack(IOBuffer& Buffer) const
{
	int numBytes;
	string temp;
	Buffer.Clear();
	temp = to_string(id);
	numBytes = Buffer.Pack(temp);
	if(numBytes == -1) return false;
	numBytes = Buffer.Pack(name);
	if(numBytes == -1) return false;
	numBytes = Buffer.Pack(address);
	if(numBytes == -1) return false;
	temp = to_string(firstDate.getMonth());
	numBytes = Buffer.Pack(temp);
	if(numBytes == -1) return false;
	temp = to_string(firstDate.getDate());
	numBytes = Buffer.Pack(temp);
	if(numBytes == -1) return false;
	temp = to_string(completedCreditHours);
	numBytes = Buffer.Pack(temp);
	if(numBytes == -1) return false;

	return true;
}

int Student::Unpack(IOBuffer& Buffer)
{
	//멤버 요소 초기화
	int numBytes;
	string temp;
	numBytes = Buffer.Unpack(temp);
	if(numBytes == -1) return false;
	id = stoi(temp);
	numBytes = Buffer.Unpack(name);
	if(numBytes == -1) return false;
	numBytes = Buffer.Unpack(address);
	if(numBytes == -1) return false;
	numBytes = Buffer.Unpack(temp);
	firstDate.setMonth(stoi(temp));
	if(numBytes == -1) return false;
	numBytes = Buffer.Unpack(temp);
	firstDate.setDate(stoi(temp));
	if(numBytes == -1) return false;
	numBytes = Buffer.Unpack(temp);
	completedCreditHours = stoi(temp);
	if(numBytes == -1) return false;

	return true;
}

char * Student::Key () const
{// produce key as concatenation of Label and IdNum
	//ostrstream key;   // this is replaced
	ostringstream key;	// again replaced
	key << id << ends;
	//string temp = key.str();
	//return key.str();
	return strdup(key.str().c_str());	
}

void Student::Print(ostream& ost) const{
	ost << this;
}