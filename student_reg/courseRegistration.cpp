#include "courseRegistration.h"
#include <sstream>
#include <string>
#include <cstring>

void CourseRegistration::addStudent(Student s)
{
    studentID.push_back(s.getID());
    courseGrade.push_back("F");
}

void CourseRegistration::addStudent(int sID, string grade)
{
    studentID.push_back(sID);
    courseGrade.push_back(grade);
}

void CourseRegistration::setCourseGrade(int sID, string grade)
{
    int index = 0;
    for(index = 0; index < studentID.size(); index++)
    {
        if(studentID[index] == sID)
            break;
    }
    courseGrade[index] = grade;
}

ostream& operator<<(ostream& ostr, const CourseRegistration& c)
{
    ostr << c.getCourseID() << '|'; 
    ostr << c.getStudentID().size() << '|';
    for(int i = 0; i < c.getStudentID().size(); i++)
    {
        ostr << c.getStudentID()[i] << '|';
        ostr << c.getCourseGrade()[i] << '|';
    }

    ostr << c.getCreditHours() << '|';
    return ostr;
}

istream& operator>>(istream& istr, CourseRegistration& c)
{
    string temp;
    int id = 0;
    int studentNum = 0;
    int creditHours = 0;

    // 입력 받을때마다 스트림 상태 체크
    // 과목 id
    getline(istr, temp, '|');
    id = stoi(temp);
    c.setCourseID(id);
    /////

    // 학생 수
    getline(istr, temp, '|');
    studentNum = stoi(temp);

    c.getStudentID().clear();
    c.getCourseGrade().clear();

    // 학생 정보
    for(int i = 0; i < studentNum; i++)
    {
        int sID;
        string grade;

        getline(istr, temp, '|');
        sID = stoi(temp);

        getline(istr, grade, '|');

        c.addStudent(sID, grade);
    }

    // 수업 시수
    getline(istr, temp, '|');
    creditHours = stoi(temp);
    c.setCreditHours(creditHours);

    return istr;
}

int CourseRegistration::Pack(IOBuffer& Buffer) const
{
	int numBytes;
	string temp;
	Buffer.Clear();
	temp = to_string(courseID);
	numBytes = Buffer.Pack(temp);
	if(numBytes == -1) return false;
    // student list size
    temp = to_string(studentID.size());
	numBytes = Buffer.Pack(temp);
	if(numBytes == -1) return false;
    for(int i = 0; i < studentID.size(); i++)
    {
        temp = to_string(studentID[i]);
        numBytes = Buffer.Pack(temp);
        if(numBytes == -1) return false;
        numBytes = Buffer.Pack(courseGrade[i]);
        if(numBytes == -1) return false;
    }
    temp = to_string(creditHours);
	numBytes = Buffer.Pack(temp);

	return true;
}

int CourseRegistration::Unpack(IOBuffer& Buffer)
{
	//멤버 요소 초기화
    clear();
	int numBytes;
	string temp;
	numBytes = Buffer.Unpack(temp);
	if(numBytes == -1) return false;
	courseID = stoi(temp);

	numBytes = Buffer.Unpack(temp);
    if(numBytes == -1) return false;
    int size = stoi(temp);

    for(int i = 0; i < size; i++)
    {
        numBytes = Buffer.Unpack(temp);
        if(numBytes == -1) return false;
        studentID.push_back(stoi(temp));

        numBytes = Buffer.Unpack(temp);
        if(numBytes == -1) return false;
        courseGrade.push_back(temp);
    }


	numBytes = Buffer.Unpack(temp);
	if(numBytes == -1) return false;
	creditHours = stoi(temp);

	return true;
}

void CourseRegistration::clear()
{
    studentID.clear();
    courseGrade.clear();
}

char * CourseRegistration::Key () const
{// produce key as concatenation of Label and IdNum
	//ostrstream key;   // this is replaced
	ostringstream key;	// again replaced
	key << courseID << ends;
	//string temp = key.str();
	//return key.str();
	return strdup(key.str().c_str());	
}