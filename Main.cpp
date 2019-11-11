//EA Job Fair
//Description: Parse through two text files with 1.student info from job fair and 2.employer info from job fair. Then display statistics from data
//Author: Joshua Williams
//Version: 1.1
//Date: October 2, 2018
//Last Revision: October 26, 2018
//Designed and Compiled in C++ 11 using Visual Studio 2017 Community

#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <iomanip>

using namespace std;

int ReadStudentFile(void);
int ReadEmployerFile(void);
bool iequals(const string& a, const string& b);

int main() {
	ReadStudentFile();
	ReadEmployerFile();

	//Keep Console Window from closing by waiting for an input;
	string tmp;
	cout << "\n\nEnter any key to exit...";
	cin >> tmp;

	return 0;
}

int ReadStudentFile(void) {
	unsigned int filesize = 0;	//num of students
	unsigned int index = 0;
	char inputchar = 0;
	string info;
	int CurrentYear;
	int PreRegDate;
	cout << "What Year is it?: ";
	cin >> CurrentYear;

	cout << endl << "What day of the month did pre-registration end? (integer): ";
	cin >> PreRegDate;
	//string StudentFile;
	//cout << "Enter Student Textfile Name: ";
	//cin >> StudentFile;

	ifstream myfile;	//initialize read-in filestream
	myfile.open("C:/Users/conncoll/Desktop/IO/eoc_attending.json");

	//check if file opened correctly
	if (myfile.is_open() == 0) {
		cout << "\nCould not find file in: " << "C: / Users / conncoll / Desktop / IO / eoc_attending.json" << endl << "Enter any character to continue to employers... ";
		cin >> info;
		return 1;
	}

	//read through file once to find how many students
	while (inputchar != ']') {
		myfile >> noskipws >> inputchar;
		if (inputchar == '}') {
			filesize++;
		}
	}
	myfile.close();

	cout << "\nTotal Number of Students: " << filesize;

	//allocate pointers the correct size for storing info from text file
	string* RNumbers = new string[filesize];
	string* FirstNames = new string[filesize];
	string* LastNames = new string[filesize];
	string* Majors = new string[filesize];
	string* Graduations = new string[filesize];
	string* CheckInTimes = new string[filesize];

	string identifier;

	//re-open file to store info from it
	myfile.open("C:/Users/conncoll/Desktop/IO/eoc_attending.json");
	myfile >> noskipws >> inputchar;	//shift over by one character in file

	//while we're not at the end of the txt file
	while (inputchar != ']') {
		//read until the next ' " ' to figure out what the identifier is
		if (inputchar == '"') {
			getline(myfile, identifier, '"');
		}
		else if (inputchar == ':') {	//read stuff between ' " ' and ' " ' apply it to respective identifier array
			myfile >> noskipws >> inputchar;	//skip over first ' " '

			//cout << "\ninput char before actual info: " << inputchar << endl;

			//if we didn't skip over a ' " ' and read an ' n ' in null
			if (inputchar == 'n') {
				getline(myfile, info, 'l');
			}
			//otherwise, read more and store the text in a specific array based on identifier
			else if (identifier == "RNumber") {
				getline(myfile, RNumbers[index], '"');
				//cout << "\n\nRNumbers[" << index << "] = " << RNumbers[index];
			}
			else if (identifier == "FirstName") {
				getline(myfile, FirstNames[index], '"');
				//cout << "\nFirstNames[" << index << "] = " << FirstNames[index];
			}
			else if (identifier == "LastName") {
				getline(myfile, LastNames[index], '"');
				//cout << "\nLastNames[" << index << "] = " << LastNames[index];
			}
			else if (identifier == "Major") {
				getline(myfile, Majors[index], '"');
				//cout << "\nMajors[" << index << "] = " << Majors[index];
			}
			else if (identifier == "Graduation") {
				getline(myfile, Graduations[index], '"');
				//cout << "\nGraduations[" << index << "] = " << Graduations[index];
			}
			else if (identifier == "CheckInTime") {
				getline(myfile, info, '-');	//don't care about year
				getline(myfile, info, '-');	//don't care about month
				getline(myfile, CheckInTimes[index], 'T');	//read in what day of the month
				getline(myfile, info, '"');	//don't care about what time
				//cout << "\nCheckInTimes[" << index << "] = " << CheckInTimes[index];
			}
		}
		else if (inputchar == '}') {
			index++;	//go to next student in arrays
		}

		myfile >> noskipws >> inputchar;	//read in next character, re-analyze
	}

	myfile.close();	//close file when done

	//variables for storing stats
	//Majors
	int sum_ElecE = 0;
	int sum_CompE = 0;
	int sum_CompSci = 0;
	int sum_MechE = 0;
	int sum_ChemE = 0;
	int sum_CivE = 0;
	int sum_IndE = 0;
	int sum_PetrE = 0;
	int sum_EnvE = 0;
	int sum_ConstrE = 0;
	int sum_OtherE = 0;

	//Graduation Dates
	int* GradDates = new int[11]();
	
	/*int sum_Fall2018 = 0;
	int sum_Spring2019 = 0;
	int sum_Fall2019 = 0;
	int sum_Spring2020 = 0;
	int sum_Fall2020 = 0;
	int sum_Spring2021 = 0;
	int sum_Fall2021 = 0;
	int sum_Spring2022 = 0;
	int sum_Fall2022 = 0;
	int sum_Spring2023 = 0;
	int sum_Fall2023 = 0;
	int sum_OtherGraduations = 0;*/

	//Pre-Registered
	int sum_PreReg = 0;

	//index through arrays and sum info for each
	for (unsigned int i = 0; i < index; i++) {
		//Add up majors
		if (Majors[i] == "Electrical Engineering") sum_ElecE++;
		else if (Majors[i] == "Computer Engineering") sum_CompE++;
		else if (Majors[i] == "Computer Science") sum_CompSci++;
		else if (Majors[i] == "Mechanical Engineering") sum_MechE++;
		else if (Majors[i] == "Chemical Engineering") sum_ChemE++;
		else if (Majors[i] == "Civil Engineering") sum_CivE++;
		else if (Majors[i] == "Industrial Engineering") sum_IndE++;
		else if (Majors[i] == "Petroleum Engineering") sum_PetrE++;
		else if (Majors[i] == "Environmental Engineering") sum_EnvE++;
		else if (Majors[i] == "Construction Engineering") sum_ConstrE++;
		else sum_OtherE++;

		//Add up Graduation Dates
		if (Graduations[i] == "Spring " + to_string(CurrentYear)) GradDates[0]++;
		else if (Graduations[i] == "Fall " + to_string(CurrentYear)) GradDates[1]++;
		else if (Graduations[i] == "Spring " + to_string(CurrentYear + 1)) GradDates[2]++;
		else if (Graduations[i] == "Fall " + to_string(CurrentYear + 1)) GradDates[3]++;
		else if (Graduations[i] == "Spring " + to_string(CurrentYear + 2)) GradDates[4]++;
		else if (Graduations[i] == "Fall " + to_string(CurrentYear + 2)) GradDates[5]++;
		else if (Graduations[i] == "Spring " + to_string(CurrentYear + 3)) GradDates[6]++;
		else if (Graduations[i] == "Fall " + to_string(CurrentYear + 3)) GradDates[7]++;
		else if (Graduations[i] == "Spring " + to_string(CurrentYear + 4)) GradDates[8]++;
		else if (Graduations[i] == "Fall " + to_string(CurrentYear + 4)) GradDates[9]++;
		else GradDates[10]++;
		//Add Up Students Who Pre-Registered
		if (stoi(CheckInTimes[i]) <= PreRegDate) sum_PreReg++;
	}

	//Display Stats
	cout << "\nNumber of Students Who Pre-registered: " << sum_PreReg;

	cout << "\n\nNumber of Students by Major: ";
	cout << "\nElectrical Engineers : " << sum_ElecE;
	cout << "\nComputer Engineers: " << sum_CompE;
	cout << "\nComputer Science: " << sum_CompSci;
	cout << "\nMechanical Engineers: " << sum_MechE;
	cout << "\nChemical Engineers: " << sum_ChemE;
	cout << "\nCivil Engineers: " << sum_CivE;
	cout << "\nIndustrial Engineers: " << sum_IndE;
	cout << "\nPetroleum Engineers: " << sum_PetrE;
	cout << "\nEnvironmental Engineers: " << sum_EnvE;
	cout << "\nConstruction Engineers: " << sum_ConstrE;
	cout << "\nOther: " << sum_OtherE;

	string FallSpring[2] = { "Spring", "Fall" };
	bool iterator = 0;
	cout << "\n\nNumber of Students by Grad Date:" << endl;
	for (int i = 0; i < 10; i++)
	{
		cout << left << FallSpring[iterator] << CurrentYear + (i/2)<< ": " << GradDates[i] << endl;
		
		iterator=!iterator;
	}

	//De-allocate pointers
	delete[] RNumbers;
	delete[] FirstNames;
	delete[] LastNames;
	delete[] Majors;
	delete[] Graduations;
	delete[] CheckInTimes;

	return 0;
}

int ReadEmployerFile(void) {
	unsigned int filesize = 0;	//num of employers
	unsigned int index = 0;
	char inputchar = 0;
	string identifier;
	string info;
	string tmp;

	//string EmployerFile;
	//cout << "\n\nEnter employer textfile name: ";
	//cin >> EmployerFile;

	ifstream myfile;	//initialize read-in filestream
	myfile.open("C:/Users/conncoll/Desktop/IO/eoc_employers.json");

	//check if file opened correctly
	if (myfile.is_open() == 0) {
		cout << "Could not find file in: " << "C: / Users / conncoll / Desktop / IO / eoc_employers.json";
		cin >> info;	//keep window from closing
		return 1;
	}

	//read through file once to find how many people
	while (inputchar != ']') {
		myfile >> noskipws >> inputchar;
		if (inputchar == '}') {
			filesize++;
		}
	}
	myfile.close();

	

	int numCompanies = 0;	//number of companies seen so far
	bool SeenCompany = 0;
	string* Companies = new string[filesize];	//array of companies present
	int* CompanyNumbers = new int[filesize]();	//array of numbers corresponding to num of representatives for each company (initialized to zeroes)
	myfile.open("C:/Users/conncoll/Desktop/IO/eoc_employers.json");
	myfile >> noskipws >> inputchar;

	//read through file and grab which companies are present
	while(!myfile.eof())
	{
		myfile >> noskipws >> inputchar;	//read next character
		//cout << "\ninputchar: " << inputchar;
		//if data is present
		if (inputchar == '"')
		{
			//read until the next ' " ' to figure out what the identifier is
			getline(myfile, identifier, '"'); //identifier
			getline(myfile, info, ',');	//read data specific to each identifier

			//delete all punctuation (and spaces) from info specific to each identifier
			char UnwantedChars[4] = { ',','"',':',' '};
			for (int i = 0; i < 4; i++)
			{
				int UnusedChar = info.find(UnwantedChars[i]);
				while (UnusedChar >= 0)
				{
					info.erase(UnusedChar, 1);
					UnusedChar = info.find(UnwantedChars[i]);	//delete any quotes or commas
				}
			}

			if (identifier == "Organization")	//if we just read what company, see if we've seen someone else from this company
			{
				//cout << endl << identifier << ": ";
				//cout << info;

				for (int i = 0; i < numCompanies; i++)	//reading through all the companies we have stored so far
				{
					if (iequals(Companies[i],info))	//if there's a match
					{
						CompanyNumbers[i]++;	//add one to the num of representatives
						SeenCompany = 1;		//mark that we've seen this company before
						i = numCompanies;	//breaks out of for loop
					}
				}

				//if we went through the whole list of employers and didn't find a match, add this company to the end of the list
				if (!SeenCompany)
				{
					Companies[numCompanies] = info;
					CompanyNumbers[numCompanies]++;
					numCompanies++;
				}
				SeenCompany = 0;
			}
		}
		else if (inputchar == 'n')
		{
			getline(myfile, info, ',');
		}
		
	}
	
	cout << "\n\nNumber of Companies: " << numCompanies;
	cout << "\nTotal number of recruiters: " << filesize << endl;

	for (int i = 0; i < numCompanies; i++) 
	{
		cout << left << setw(32) << Companies[i] << setw(32) << CompanyNumbers[i] << endl;
	}
	return 0;
}

//function for comparing strings case-insensitively
bool iequals(const string& a, const string& b)
{
	return std::equal(a.begin(), a.end(),
		b.begin(), b.end(),
		[](char a, char b) {
		return tolower(a) == tolower(b);
	});
}