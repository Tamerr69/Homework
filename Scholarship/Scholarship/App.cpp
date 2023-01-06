#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>

using namespace std;

class Student
{
public:
	Student() { }; //ÏÎÄĞÀÇÁÈĞÀÙ ÑÅ

	Student(int grade, string facultyNumber) //ÅÊÑÏËÈÖÈÒÅÍ  
	{
		this->grade = grade;
		this->facultyNumber = facultyNumber;
	};

	int getGrade() //×ÅÒÅÍÅ ÍÀ ×ËÅÍÎÂÅÒÅ
	{
		return this->grade;
	};

	string getFacultyNumber() // ×ÅÒÅÍÅ ÍÀ ×ËÅÍÎÂÅÒÅ
	{
		return this->facultyNumber; 
	};

	bool operator < (const Student& student) const // II.4 ÇÀ ÑĞÀÂÍÅÍÈÅ < ÏÎ ÈÇÁÎĞ
	{
		return this->facultyNumber.compare(student.facultyNumber) < 0;
	};

	bool operator == (const Student& student) const  // II.5 ÇÀ ÅÊÂÈÂÀËÅÍÒÍÎÑÒ == 
	{
		return this->facultyNumber.compare(student.facultyNumber) == 0;
	};

	friend ostream& operator << (ostream& output, const Student& student) // II.6 ÏĞÅÄÅÔÈÍÈĞÀ ÏÎÒÎÊÎÂ OPERATOR<<
	{
		output << student.facultyNumber << " " << student.grade;
		return output;
	};

	friend istream& operator >> (istream& input, Student& student) // II.7 ÏĞÅÄÅÔÈÍÈĞÀ ÏÎÒÎÊÎÂ OPERATOR>>
	{
		input >> student.facultyNumber >> student.grade;
		return input;
	};

private:
	int grade;
	string facultyNumber;
};

class Scholarship  // 3.I Aáñòğàêòåí êëàñ Ñòèïåíäèÿ: 
{
public:
	virtual set<Student> extractStudentsForScholarship(const set<Student>& report, int lowerGrade, int upperGrade) const = 0;
};

class Protocol : public Scholarship
{
public:
	Protocol(string fileName) // III.1	ÅÊÑÏËÈÖÈÒÅÍ ÏÎ ÈÌÅ ÍÀ ÔÀÉË Ñ ÄÀÍÍÈ - ÈÇÊËŞ×ÅÍÈÅ
	{
		ifstream inputFile(fileName);
		if (!inputFile.fail())
		{
			inputFile >> *this;
			inputFile.close();
		}
		else {
			throw runtime_error("Failed to open file " + fileName);
		}
	};

	string getSpecialy()  // III.3  ÇÀ ×ÅÒÅÍÅ ÍÀ ÈÌÅÒÎ ÍÀ ÑÏÅÖÈÀËÍÎÑÒÒÀ		
	{	
		return this->specialty;			
	}

	set<Student> createStudentSet() // III.5  ÔÓÍÊÖÈß ÇÀ ÑÚÇÄÀÂÀÍÅ È ÂĞÚÙÀÍÅ ÍÀ ÌÍÎÆÅÑÒÂÎ ÎÒ ÑÒÓÄÅÍÒÈ Ñ ĞÅÇÓËÒÀÒÈÒÅ ÈÌ ÎÒ ÑÅÌÅÑÒÚĞÀ
	{
		set<Student> toReturn(this->students.begin(), this->students.end());
		return toReturn;
	};

	virtual set<Student> extractStudentsForScholarship(const set<Student>& report, int lowerGrade, int upperGrade) const // III.4  ÈÌÏËÅÌÅÍÒÈĞÀÍÅ ÍÀ ÂÈĞÒÓÀËÍÀ ÔÓÍÊÖÈß
	{
		set<Student> toReturn;
		for (Student student : report) {
			if (student.getGrade() >= lowerGrade && student.getGrade() <= upperGrade) {
				toReturn.insert(student);
			}
		}
		return toReturn;
	};

	bool operator < (const Protocol& protocol) const // III.6 : ÇÀ ÑĞÀÂÍÅÍÈÅ < ÏÎ ÈÇÁÎĞ
	{
		return this->specialty.compare(protocol.specialty) < 0;
	};

	bool operator == (const Protocol& protocol) const // III.7: ÇÀ ÅÊÂÈÂÀËÅÍÒÍÎÑÒ == 
	{
		return this->specialty.compare(protocol.specialty) == 0 && this->students == protocol.students; 
	};

	friend ostream& operator << (ostream& output, const Protocol& protocol) // III.8 : ÏĞÅÄÅÔÈÍÈĞÀ ÏÎÒÎÊÎÂ OPERATOR<<(ÈÇÂÅÆÄÀ Â ÓÊÀÇÀÍ ÈÇÕÎÄÅÍ ÏÎÒÎÊ) 
	{
		output << protocol.specialty << endl;
		for (Student student : protocol.students) {
			output << student << " ";
		}
		return output;
	};

	friend istream& operator >> (istream& input, Protocol& protocol) // III.	9 : ÏĞÅÄÅÔÈÍÈĞÀ ÏÎÒÎÊÎÂ OPERATOR>>(×ÅÒÅ ÎÒ ÓÊÀÇÀÍ ÂÕÎÄÅÍ ÏÎÒÎÊ) 
	{
		getline(input, protocol.specialty);
		Student student;
		while (input >> student) {
			protocol.students.push_back(student);
		}
		return input;
	};

private:
	string specialty;
	vector<Student> students;
};

void print(const set<Student> students)
{
	cout << endl;
	for (Student student : students)
	{
		cout << student << endl;
	}
}

void main()
{
	Protocol kst = Protocol("test_file.txt");
	set<Student> studentsKst = kst.createStudentSet();
	set<Student> kstStudentsX = kst.extractStudentsForScholarship(studentsKst, 4, 5);

	Protocol sit = Protocol("test_file2.txt");
	set<Student> studentsSit = sit.createStudentSet();
	set<Student> sitStudentsX = sit.extractStudentsForScholarship(studentsSit, 3, 4);

	cout << kst << endl << endl;
	cout << sit << endl;

	print(studentsKst);
	print(studentsSit);

	print(kstStudentsX);
	print(sitStudentsX);			

	try {
		new Protocol("nonexistent_file.txt"); // ÎÁĞÀÁÎÒÂÀÍÅ ÍÀ ÈÇÊËŞ×ÅÍÈÅ
	}
	catch (const runtime_error& e) {
		cout << endl << "Error occured: " << e.what() << endl;
	}
}