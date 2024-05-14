// maketxtindxfile.cpp

// Headeers for template index
#include "textind.h"
#include "delim.h"
#include "buffile.h"
#include "student.h"
#include "courseRegistration.h"
#include "fixfld.h"
#include "indfile.h"
#include "./index/indfile.cpp"  // for template method body
#include <iostream>


using namespace std;
/*
// make an indexed file from a recording file
int ReadIndexRecordingFile (char* myfile, TextIndexedFile<Student> & indexFile)
{
	Student fileRec; 
	Student indRec;
	int recaddr, result;
	DelimFieldBuffer Buffer; // create a buffer
	BufferFile RecFile(Buffer); 

	// open recordFile using the filename
	result = RecFile . Open (myfile,ios::in);
	if (!result)
	{
		cout << "Unable to open file "<<myfile<<endl;
		return 0;
	}
	while (1) // loop until the read fails
	{
		recaddr = RecFile . Read (); // read next record
		if (recaddr < 0) break;
		fileRec. Unpack (Buffer);
		cout <<"\nLooking for record with key:"
			<<fileRec.Key()<<endl;
		result=indexFile . Read(fileRec.Key(),indRec);
		if (result<0) cout <<"record not found";
		else indRec.Print(cout);
	}

}
*/

void set_circum1(vector<Student>& students, vector<CourseRegistration>& courses, TextIndexedFile<Student>& indexFile)
{
	students.clear();
	courses.clear();
    // student data setting
    for(int i = 0; i < 15; i++)
    {
        string name = "student" + to_string(i);
        string address = "address" + to_string(i);
        Date date(i + 1, i + 5);
        int cchours = i + 10;

        Student s(i, name, address, date, cchours);
        students.push_back(s);
    }

    // course data setting
    for(int i = 0; i < 10; i++)
    {
        int cID = i + 100;
        int ch = (i % 4) + 1;
        CourseRegistration c(cID, ch);
        courses.push_back(c);
    }

    string grade[5] = {"A+", "A0", "B0", "C+", "F"};
    // register course
    for(int i = 0; i < students.size(); i++)
    {
        int ci = i % courses.size();
        courses[ci].addStudent(students[i]);
        courses[ci].setCourseGrade(students[i].getID(), grade[(i*3)%5]);

        courses[(ci + 2) % 10].addStudent(students[i]);
        courses[(ci + 2) % 10].setCourseGrade(students[i].getID(), grade[(i*2)%5]);

        courses[(ci + 4) % 10].addStudent(students[i]);
        courses[(ci + 4) % 10].setCourseGrade(students[i].getID(), grade[(i*4)%5]);
    }
    
	int recaddr;

	for (int i= 0; i<10; i++)
	{

		recaddr = indexFile.Append(students[i]);
		cout <<"Recording R["<<i<<"] at recaddr "<<recaddr<<" is added to TextIndexFile"<<endl;
	}
}

void set_circum2(vector<Student>& students, vector<CourseRegistration>& courses, TextIndexedFile<CourseRegistration>& indexFile)
{
	students.clear();
	courses.clear();
    // student data setting
    for(int i = 0; i < 15; i++)
    {
        string name = "student" + to_string(i);
        string address = "address" + to_string(i);
        Date date(i + 1, i + 5);
        int cchours = i + 10;

        Student s(i, name, address, date, cchours);
        students.push_back(s);
    }

    // course data setting
    for(int i = 0; i < 10; i++)
    {
        int cID = i + 100;
        int ch = (i % 4) + 1;
        CourseRegistration c(cID, ch);
        courses.push_back(c);
    }

    string grade[5] = {"A+", "A0", "B0", "C+", "F"};
    // register course
    for(int i = 0; i < students.size(); i++)
    {
        int ci = i % courses.size();
        courses[ci].addStudent(students[i]);
        courses[ci].setCourseGrade(students[i].getID(), grade[(i*3)%5]);

        courses[(ci + 2) % 10].addStudent(students[i]);
        courses[(ci + 2) % 10].setCourseGrade(students[i].getID(), grade[(i*2)%5]);

        courses[(ci + 4) % 10].addStudent(students[i]);
        courses[(ci + 4) % 10].setCourseGrade(students[i].getID(), grade[(i*4)%5]);
    }
    
	int recaddr;

	for (int i= 0; i<10; i++)
	{

		recaddr = indexFile.Append(courses[i]);
		cout <<"Recording R["<<i<<"] at recaddr "<<recaddr<<" is added to TextIndexFile"<<endl;
	}
}	


int main (int argv, char ** argc)
{
	// create Record file.
	
	//char *recIdxFileName = "recindex.dat";
	//CreateRecordingFile(recFileName);
	char *strRecording = "recording";
	char *myfile="recording.dat";
	int result;

	TextIndex RecIndex (10);
	DelimFieldBuffer Buffer; // create a buffer
	TextIndexedFile<Student> IndFile (Buffer, 12, 10);
	result = IndFile . Create(strRecording);
	if (!result) 
	{
		cout<<"Unable to create indfile "<<result<<endl;
		return 0;
	}	

	// student data
    vector<Student> students;

    // course data
    vector<CourseRegistration> courses;

	set_circum1(students, courses, IndFile);
	
	// student index 검색
	Student indRec;
	cout<<"Search Test1"<<endl;
	char* key1 = "1";
	result=IndFile.Read(key1,indRec);
	if (result<0) cout <<"record not found"<<endl;
	else cout << indRec << endl;//indRec.Print(cout);
	cout<<"Search Test2"<<endl;
	char* key2 = "2";
	result=IndFile.Read(key2,indRec);
	if (result<0) cout <<"record not found";
	else cout << indRec << endl;//indRec.Print(cout);
	
	IndFile.Close();

	// courseRegistration index 검색
	TextIndex RecIndex2 (10);
	DelimFieldBuffer Buffer2; // create a buffer
	TextIndexedFile<CourseRegistration> IndFile2 (Buffer2, 12, 10);
	result = IndFile2 . Create(strRecording);

	set_circum2(students, courses, IndFile2);

	if (!result) 
	{
		cout<<"Unable to create indfile "<<result<<endl;
		return 0;
	}	

	// courseRegistration index 검색
	CourseRegistration indRec2;
	cout<<"Search Test1"<<endl;
	char* key3 = "103";
	result=IndFile2.Read(key3,indRec2);
	if (result<0) cout <<"record not found"<<endl;
	else cout << indRec2 << endl;
	cout<<"Search Test2"<<endl;
	char* key4 = "101";
	result=IndFile2.Read(key4,indRec2);
	if (result<0) cout <<"record not found";
	else cout << indRec2 << endl;
	IndFile2.Close();
	return -1;
}

