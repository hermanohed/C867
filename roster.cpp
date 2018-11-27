#include <iostream>
#include <sstream>
#include "degree.h"
#include "roster.h"
#include "networkStudent.h"
#include "securityStudent.h"
#include "softwareStudent.h"

using namespace std;
int main() {
	Roster classRoster;

	const string studentData[] = {
"A1,John,Smith,John1989@gmail.com,20,30,35,40,SECURITY",
"A2,Suzan,Erickson,Erickson_1990@gmailcom,19,50,30,40,NETWORK",
"A3,Jack,Napoli,The_lawyer99yahoo.com,19,20,40,33,SOFTWARE",
"A4,Erin,Black,Erin.black@comcast.net,22,50,58,40,SECURITY",
	};

	cout << "Scripting and Programming - Applications - C867"<< endl;
	cout << "Written in C++"<< endl;
	
	
	
	for (int i = 0; i < currentRosterSize; i++) {
		string input = studentData[i];
		istringstream ss(input);
		string token;
		string position[9];

		int s = 0;
		while (getline(ss, token, ',')) {
			position[s] = token;
			s += 1;
		}

		Degree theDegree;
		if (position[8] == "NETWORK") {
			theDegree = NETWORKING;
		}
		else if (position[8] == "SECURITY") {
			theDegree = SECURITY;
		}
		else(position[8] == "SOFTWARE") {
			theDegree = SOFTWARE;
		}
		
		classRoster.add(position[0], position[1], position[2], position[3], std::stoi(position[4]), std::stoi(position[5]), std::stoi(position[6]), std::stoi(position[7]), theDegree);
	}

	classRoster.printAll();
	cout << "\n";
	classRoster.printInvalidEmails();
	cout << "\n";
	for (int i = 0; i < currentRosterSize; i++) {
		classRoster.printAverageDaysInCourse(classRoster.studentData[i]->getStudId());
	}
	cout << "\n";
	classRoster.printByDegreeProgram(NETWORKING);
	cout << "\n";
	classRoster.remove("A5");

	return 0;
}

void Roster::add(string studId, string firstName, string lastName, string emailAddress, int studAge, int daysInCourse1, int daysInCourse2, int daysInCourse3, Degree degree) {
	int dIc[3];
	dIc[0] = daysInCourse1;
	dIc[1] = daysInCourse2;
	dIc[2] = daysInCourse3;
	if (degree == NETWORKING) {
			classRosterArray[currentRosterIndex] = new NetworkStudent(studId, firstName, lastName, emailAddress, studAge, dIc, degree);
		}
		else if (degree == SECURITY) {
			classRosterArray[currentRosterIndex] = new SecurityStudent(studId, firstName, lastName, emailAddress, studAge, dIc, degree);
		}
		else {
			classRosterArray[currentRosterIndex] = new SoftwareStudent(studId, firstName, lastName, emailAddress, studAge, dIc, degree);
		}
		currentRosterIndex++;
}

void Roster::remove(string studentID) {
	bool studentFound = false;
	for (int i = 0; i < currentRosterSize; ++i) {
		if (studentFound) {
			if (classRosterArray[i]->getStudId() == studentID) {
				studentFound = true;
				classRosterArray[i] = nullptr;
			}
		}
		else {
			classRosterArray[i - 1] = classRosterArray[i];
		}
	}
	if (studentFound == false) {
		cout << "Student ID " << studentID << " not found!";
	}
	else {
		currentRosterSize--;
	}
}

void Roster::printAll() {
	for (int i = 0; i < currentRosterSize; ++i) {
		classRosterArray[i]->print();
	}
}


void Roster::printAverageDaysInCourse(string studentID) {
	float avg = 0;
	int highest = 3;
	if (classRosterArray[currentRosterIndex] != nullptr && classRosterArray[currentRosterIndex]->getStudId() == studentID) {
		int *daysInCourse = classRosterArray[currentRosterIndex]->getDaysInCourse(); 
		for (int x = 0; x < highest; ++x) {
			avg += daysInCourse[x];
		}
		cout << "The average number of days in the courses for student " << classRosterArray[currentRosterIndex]->getStudId() << " is " << (avg / highest) << ".";
	}
}

void Roster::printInvalidEmails() {
	for (int i = 0; i < currentRosterSize; ++i) {
		string emailAddress = classRosterArray[i]->getEmailAddress();
		bool validEmail = false;
		size_t found = emailAddress.find("@");
		if (found != string::npos) {
			found = emailAddress.find(".");
			if (found != string::npos) {
				found = emailAddress.find(" ");
				if (found == string::npos) {
					validEmail = true;
				}
			}
		}
		if (validEmail == false) {
			cout << "Email address " << emailAddress<< " is not valid.";
		}
	}
}

void Roster::printByDegreeProgram(Degree degreeProgram) {
	for (int i = 0; i < currentRosterSize; ++i) {
		if (classRosterArray[i]->getDegree() == degreeProgram) {
			classRosterArray[i]->print();
		}
	}
}
Roster::~Roster() {
	for (int i = 0; i < currentRosterSize; ++i) {
		delete classRosterArray[i];
	}
}

Student ** Roster::getClassRosterArray()
{
	return classRosterArray;
}




//E.Create a Roster class (roster.cpp) by doing the following :

//1.  Create an array of pointers, classRosterArray, to hold the data provided in the studentData table.

//2.  Create a student object for each  student in the data table by using the subclasses NetworkStudent, SecurityStudent, and SoftwareStudent, and populate classRosterArray.

	//a.Apply pointer operations when parsing each  set of data identified in the studentData table.

	//b.Add each student object to classRosterArray.

