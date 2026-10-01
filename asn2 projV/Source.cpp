
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;


#define PRE_RELEASE


// Holds the information for one student
struct STUDENT_DATA
{
	string firstName;
	string lastName;
#ifdef PRE_RELEASE
	string email;   // only exists in the pre-release build
#endif
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
	// Tell the user which source code is running
#ifdef PRE_RELEASE
	cout << "Running PRE-RELEASE source code" << endl;
#else
	cout << "Running STANDARD source code" << endl;
#endif

	vector<STUDENT_DATA> students;

	// ---- Read the names (standard functionality) ----
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

	// ---- Read the emails (pre-release functionality only) ----
#ifdef PRE_RELEASE
	ifstream emailFile("StudentData_Emails.txt");
	if (!emailFile.is_open())
	{
		cout << "ERROR: could not open StudentData_Emails.txt" << endl;
		return 1;
	}

	// Each line looks like:  LastName, FirstName,email
	while (getline(emailFile, line))
	{
		size_t firstComma = line.find(',');
		size_t secondComma = (firstComma == string::npos) ? string::npos : line.find(',', firstComma + 1);
		if (secondComma == string::npos) continue;   // skip blank/malformed lines

		string last = Trim(line.substr(0, firstComma));
		string first = Trim(line.substr(firstComma + 1, secondComma - firstComma - 1));
		string email = Trim(line.substr(secondComma + 1));

		// Attach the email to the matching student
		for (STUDENT_DATA& s : students)
		{
			if (s.lastName == last && s.firstName == first)
			{
				s.email = email;
				break;
			}
		}
	}
	emailFile.close();
#endif

	
#ifdef _DEBUG
	cout << "DEBUG: loaded " << students.size() << " students" << endl;
	for (const STUDENT_DATA& s : students)
	{
		cout << s.firstName << " " << s.lastName;
#ifdef PRE_RELEASE
		cout << " - " << s.email;
#endif
		cout << endl;
	}
#endif

	return 0;
}