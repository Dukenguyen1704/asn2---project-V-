

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

// Holds the name information for one student
struct STUDENT_DATA
{
	string firstName;
	string lastName;
};

// Removes leading/trailing spaces, tabs and carriage returns from a string
static string Trim(const string& s)
{
	const string whitespace = " \t\r\n";
	size_t start = s.find_first_not_of(whitespace);
	if (start == string::npos) return "";
	size_t end = s.find_last_not_of(whitespace);
	return s.substr(start, end - start + 1);
}

int main()
{
	vector<STUDENT_DATA> students;

	ifstream inFile("StudentData.txt");
	if (!inFile.is_open())
	{
		cout << "ERROR: could not open StudentData.txt" << endl;
		return 1;
	}

	// Each line looks like:  LastName, FirstName
	string line;
	while (getline(inFile, line))
	{
		size_t comma = line.find(',');
		if (comma == string::npos) continue;   // skip blank/malformed lines

		STUDENT_DATA student;
		student.lastName = Trim(line.substr(0, comma));
		student.firstName = Trim(line.substr(comma + 1));
		students.push_back(student);
	}
	inFile.close();

	// _DEBUG is defined automatically by Visual Studio in the Debug configuration only,
	// so this printing code is not even compiled into a Release build.
#ifdef _DEBUG
	cout << "DEBUG: loaded " << students.size() << " students" << endl;
	for (const STUDENT_DATA& s : students)
	{
		cout << s.firstName << " " << s.lastName << endl;
	}
#endif

	return 0;
}