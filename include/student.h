#ifndef STD
#define STD

#include <iostream>
#include <string>
#include <istream>
#include "delim.h"

using namespace std;

class Date
{
	private:
		int month = 0;
		int date = 0;
	public:
		Date() = default;
		Date(int m, int d) : month(m), date(d) {}

		void setMonth(int m){ month = m; }
		int getMonth(){ return month; }
		int getMonth() const { return month; }

		void setDate(int d){ date = d; }
		int getDate(){ return date; }
		int getDate() const { return date; }

		friend ostream& operator<<(ostream& ostr, const Date& d){
			ostr << d.getMonth() << '|' << d.getDate() << '|';
			return ostr;
		}

		friend istream& operator>>(istream& istr, Date& d){
			string month, day;
			getline(istr, month, '|');
			getline(istr, day, '|');
			//istr >> d.month >> d.date;
			d.setMonth(stoi(month));
			d.setDate(stoi(day));
			return istr;
		}
};

class Student
{
	private:
		int id = 0;
		string name = "";
		string address = "";
		Date firstDate;
		int completedCreditHours = 0;
	public:
		Student() = default;
		Student(int i, string n, string a, Date f, int c);

		void setID(int i) { id  = i; }
		int getID() { return id; }
		int getID() const { return id; }

		void setName(string n){ name = n; }
		string getName() { return name; }
		string getName() const { return name; }

		void setAddress(string a){ address = a; }
		string getAddress(){ return address; }
		string getAddress() const { return address; }

		void setFirstDate(int month, int date){ 
			firstDate.setMonth(month);
			firstDate.setDate(date);
		}
		Date getFirstDate() { return firstDate; }
		Date getFirstDate() const { return firstDate; }

		void setCch(int c) {completedCreditHours = c;}
		int getCch() { return completedCreditHours; }
		int getCch() const { return completedCreditHours; }

		Student& operator=(const Student& rvalue);
		// << 오버로딩
		friend ostream& operator<<(ostream& ostr, const Student& s);
		// >> 오버로딩
		friend istream& operator>>(istream& istr, Student& s);

		int Pack(IOBuffer&) const;
		int Unpack(IOBuffer&);
		void Print(ostream&) const;

		char * Key () const; // return key of object
};

#endif