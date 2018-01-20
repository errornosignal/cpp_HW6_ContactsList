//Reid_Nolan_HW6_[ContactsList]
//Contact.cpp
//***********************************************************************************************//
//Author: Reid S. Nolan
//Date: 03/28/2017
//Contact Class Source File
//Class for returning specific values from input file for Reid_Nolan_HW6_[ContactsList].cpp
//***********************************************************************************************//

#include "stdafx.h"
#include "Contact.h"

//constructors
Contact::Contact()
{
	//initialize class variables
	Number = "";
	Gender = "";
	Title = "";
	FirstName = "";
	MiddleName = "";
	LastName = "";
	Address = "";
	City = "";
	State = "";
	Zip = "";
	Email = "";
	DOB = "";
}

//destructors
Contact::~Contact()
{
}

//setters
void Contact::setNumber(string nextValue)
{
	Number = nextValue;
}

void Contact::setGender(string nextValue)
{
	Gender = nextValue;
}

void Contact::setTitle(string nextValue)
{
	Title = nextValue;
}

void Contact::setFirstName(string nextValue)
{
	FirstName = nextValue;
}

void Contact::setMiddleName(string nextValue)
{
	MiddleName = nextValue;
}

void Contact::setLastName(string nextValue)
{
	LastName = nextValue;
}

void Contact::setAddress(string nextValue)
{
	Address = nextValue;
}

void Contact::setCity(string nextValue)
{
	City = nextValue;
}

void Contact::setState(string nextValue)
{
	State = nextValue;
}

void Contact::setZip(string nextValue)
{
	Zip = nextValue;
}

void Contact::setEmail(string nextValue)
{
	Email = nextValue;
}

void Contact::setDOB(string nextValue)
{
	DOB = nextValue;
}

//getters
string Contact::getNumber()
{
	return Number;
}

string Contact::getGender()
{
	return Gender;
}

string Contact::getTitle()
{
	return Title;
}

string Contact::getFirstName()
{
	return FirstName;
}

string Contact::getMiddleName()
{
	return MiddleName;
}

string Contact::getLastName()
{
	return LastName;
}

string Contact::getAddress()
{
	return Address;
}

string Contact::getCity()
{
	return City;
}

string Contact::getState()
{
	return State;
}

string Contact::getZip()
{
	return Zip;
}

string Contact::getEmail()
{
	return Email;
}

string Contact::getDOB()
{
	return DOB;
}

//load records into vectors
void Contact::loadRecords(Contact contact, vector<vector<string>> &mainList, const string mDATA_FILE, fstream &inFile, int &contactsCount)
{
	//open input file
	inFile.open(mDATA_FILE);

	//notify and terminate if input file cannot be opened
	while (!inFile)
	{
		//display error and exit message
		displayNoInputFile(mDATA_FILE);
		displayExit();
		//wait for user to continue before terminating
		system("pause");
		//terminate program
		exit(1);
	}

	//loop while input file is open
	while (inFile)
	{
		string Row = "";

		//display loading contacts message
		displayLoadingRecords(mDATA_FILE);

		//create sub-vector for each row of values
		vector<string>newRow;

		//loop for reading from file and appending rows to vector
		while (getline(inFile, Row))
		{
			//declare and initialize local variables			
			stringstream ss(Row);
			string cell = "";			

			//get comma seperated values for each row and add to sub-vector			
			for (int i = 0; (getline(ss, cell, ',')); i++) //use Contact Class to set and get cell values
			{
				if (i == 0)			//set and get value in first columm (number)
				{
					contact.setNumber(cell);
					newRow.push_back(contact.getNumber());
				}
				else if (i == 1)	//set and get value in second columm (gender)
				{
					contact.setGender(cell);
					newRow.push_back(contact.getGender());
				}
				else if (i == 2)	//set and get value in third columm (title)
				{
					contact.setTitle(cell);
					newRow.push_back(contact.getTitle());
				}
				else if (i == 3)	//set and get value in fourth columm (first name)
				{
					contact.setFirstName(cell);
					newRow.push_back(contact.getFirstName());
				}
				else if (i == 4)	//set and get value in fifth columm (middle initial)
				{
					contact.setMiddleName(cell);
					newRow.push_back(contact.getMiddleName());
				}
				else if (i == 5)	//set and get value in sixth columm (last name)
				{
					contact.setLastName(cell);
					newRow.push_back(contact.getLastName());
				}
				else if (i == 6)	//set and get value in seventh columm (address)
				{
					//remove double-quotes from protected string
					cell.erase(remove(cell.begin(), cell.end(), '\"'), cell.end());

					contact.setAddress(cell);
					newRow.push_back(contact.getAddress());
				}
				else if (i == 7)	//set and get value in eighth columm (city)
				{
					//remove double-quotes from protected string
					cell.erase(remove(cell.begin(), cell.end(), '\"'), cell.end());

					contact.setCity(cell);
					newRow.push_back(contact.getCity());
				}
				else if (i == 8)	//set and get value in ninth columm (state)
				{
					contact.setState(cell);
					newRow.push_back(contact.getState());
				}
				else if (i == 9)	//set and get value in tenth column (zip)
				{
					contact.setZip(cell);
					newRow.push_back(contact.getZip());
				}
				else if (i == 10)	//set and get value in eleventh columm (email)
				{
					contact.setEmail(cell);
					newRow.push_back(contact.getEmail());
				}
				else if (i == 11)	//set and get value in twelfth columm (date of birth)
				{
					contact.setDOB(cell);
					newRow.push_back(contact.getDOB());
				}
				else
				{
					//do nothing
				}				
			}
			//add sub-vector to main vector(append row)
			mainList.push_back(newRow);

			//erase all vector elements from vector
			newRow.erase(newRow.begin(), newRow.end());
			vector<string>().swap(newRow);

			//increment contacts counter
			contactsCount++;
		}		
	}

	//close input file after reading into memory
	inFile.close();	

	//compare by lastname, firstname, middlename, and number, in that order (+1 excludes first row, assuming column headers)		
	sort(mainList.begin() + 1, mainList.end(), defineSortOrder);

	//display number of records processed
	displayContactsCount(contactsCount);
}

void Contact::matchMonths(string monthSelection, vector<vector<string>> &mainList, const int mLAST_COL, const int mNUM_COLS, int &matchCount)
{
	if (monthSelection.length() == 1)
	{
		monthSelection.insert(1, "/");
	}
	else
	{
		//do nothing
	}

	//loop through rows
	for (size_t i = 0; i < mainList.size(); i++)
	{
		if (mainList[i][mLAST_COL].substr(0, 2) == monthSelection)
		{
			//loop through columns
			outputRows(mainList, mNUM_COLS, i);
			//increment match counter
			matchCount++;
		}
		else
		{
			//do nothing
		}
	}
}

//status messages
void Contact::displayLoadingRecords(const string mDATA_FILE)
{
	//display input file opened confirmation message
	cout << endl << "Please wait. Loading records from " << mDATA_FILE << " into memory..." << endl;
}

void Contact::displayNoInputFile(const string mDATA_FILE)
{
	//display no input file message
	cout << "Error! Input file could not be opened." << endl;
	cout << "Ensure that " << mDATA_FILE << " has been placed in the current working directory" << endl;
	cout << "     and is not open in another program." << endl;
}

void Contact::displayContactsCount(const int contactsCount)
{
	//display number of records processed (excludes first row of input file, assumes column headers)
	cout << "Records successfully loaded into memory: " << contactsCount - 1 << endl << endl;
}

void Contact::displayExit()
{
	//display exiting program status message
	cout << "exiting program..." << endl;
	system("pause");
	exit(1);
}

//displaying data
void Contact::displayColumnHeader(vector<vector<string>> &mainList, const int mNUM_COLS, const int mFIRST_ROW)
{
	//output rows
	cout << endl;
	outputRows(mainList, mNUM_COLS, mFIRST_ROW);

	//format second line, spacer between column headers and record values, for tabular format
	cout << "| ------ |"; //number
	cout << " ------ ";	//gender
	cout << "| ----- |"; //title
	cout << " ----------- "; //firstname
	cout << "| ------------- |"; //middle initial
	cout << " ------------- "; //last name
	cout << "| ------------------------------ |"; // address
	cout << " ---------------------- |"; // city
	cout << " ----- "; // state
	cout << "| ------- |"; // zip
	cout << " ---------------------------------- "; //email
	cout << "| ---------- |" << endl; //date of birth
}

void Contact::outputRows(vector<vector<string>> &mainList, const int mNUM_COLS, const int i)
{
	//loop through columns
	for (int j = 0; j < mNUM_COLS; j++)
	{
		//format record fields for output
		if (j == 0) //number
		{
			cout << "| " << setw(6) << mainList[i][j] << " | ";
		}
		else if (j == 1) //gender
		{
			cout << setw(6) << mainList[i][j] << " | ";
		}
		else if (j == 2) //title
		{
			cout << setw(5) << mainList[i][j] << " | ";
		}
		else if (j == 3) //first name
		{
			cout << setw(11) << mainList[i][j] << " | ";
		}
		else if (j == 4) //middle initial
		{
			cout << setw(13) << mainList[i][j] << " | ";
		}
		else if (j == 5) //last name
		{
			cout << setw(13) << mainList[i][j] << " | ";
		}
		else if (j == 6) //address
		{
			cout << setw(30) << mainList[i][j] << " | ";
		}
		else if (j == 7) //city
		{
			cout << setw(22) << mainList[i][j] << " | ";
		}
		else if (j == 8) //state
		{
			cout << setw(5) << mainList[i][j] << " | ";
		}
		else if (j == 9) //zip
		{
			cout << setw(7) << mainList[i][j] << " | ";
		}
		else if (j == 10) //email
		{
			cout << setw(34) << mainList[i][j] << " | ";
		}
		else if (j == 11) // date of birth
		{
			cout << setw(10) << mainList[i][j] << " |";
		}
		else
		{
			//do nothing
		}
	}
	cout << endl;
}

void Contact::displayMatches(vector<vector<string>> &mainList, const string toMatch, const int columnTosearch, const int mNUM_COLS, int &matchCount, const int i)
{
	//display column header
	displayColumnHeader(mainList, mNUM_COLS, i);

	//loop through rows
	for (size_t i = 0; i < mainList.size(); i++)
	{
		//copy vector contencts to string for comparison
		string s1 = mainList[i][columnTosearch];

		//compare search value to record values
		if (s1 == toMatch)
		{
			//outpuit rows
			outputRows(mainList, mNUM_COLS, i);
			//increment match counter
			matchCount++;
		}
		else
		{
			//do nothing
		}
	}
}

void Contact::birthdayPreMatchWork(string dateString, int age, vector<vector<string>> &mainList, const int mNUM_COLS, const int mFIRST_ROW, const int mLAST_COL, int &matchCount, bool &ageGood)
{
	//declare and initialize local variables							
	int yearStringAsInt = 0;
	int yearToFind = 0;
	int yearToFind_minusOne = 0;
	string yearToFind_String = "";
	string yearToFind_minusOne_String = "";
	string dayToFind_String = "";
	string monthToFind_String = "";

	//perform type conversions to allow comparison of fields
	yearStringAsInt = stoi(dateString.substr(dateString.length() - 4));
	yearToFind = yearStringAsInt - age;
	yearToFind_minusOne = yearStringAsInt - age - 1;
	yearToFind_String = to_string(yearToFind);
	yearToFind_minusOne_String = to_string(yearToFind_minusOne);

	//get date string substrings for day and month
	monthToFind_String = dateString.substr(0, 2);
	dayToFind_String = dateString.substr(3, 2);

	//display coulumn header
	displayColumnHeader(mainList, mNUM_COLS, mFIRST_ROW);

	//loop through rows
	for (size_t i = 0; i < mainList.size(); i++)
	{
		//declare and initialize local variables
		const string mDELIMITER = "/";
		string birthYear = "";
		string birthMonth = "";
		string birthDay = "";
		string temp = "";

		//set last 4 of string in date of birth cell, (YYYY), to local variable
		birthYear = mainList[i][mLAST_COL].substr(mainList[i][mLAST_COL].length() - 4);

		//specify iterator at start of string
		auto start = mainList[i][mLAST_COL].begin();
		//get position of first occurrence of delimiter
		size_t finish = mainList[i][mLAST_COL].find(mDELIMITER);

		//start to break string into seperate month, day, and year values
		if (finish != mainList[i][mLAST_COL].npos)
		{
			//get month (MM) portion of string
			birthMonth = mainList[i][mLAST_COL].substr(0, finish);
			//copy remaining portion of string into placeholder
			temp = mainList[i][mLAST_COL].substr(finish + 1);

			//add leading zero if single digit month (ex. M/DD/YYY)
			if (birthMonth.length() == 1)
			{
				birthMonth.insert(0, "0");
			}
			else
			{
				//do nothing
			}
		}
		else
		{
			//do nothing
		}

		//specify iterator at start of string
		start = temp.begin();
		//get position of first occurrence of delimiter
		finish = temp.find(mDELIMITER);

		//continue breaking string into seperate month, day, and year values
		if (finish != temp.npos)
		{
			//get day (DD) portion of string
			birthDay = temp.substr(0, finish);
			//copy remaining portion of string into placeholder
			temp = temp.substr(finish + 1);

			//add leading zero if single digit day (ex. MM/D/YYYY)
			if (birthDay.length() == 1)
			{
				birthDay.insert(0, "0");
			}
			else
			{
				//do nothing
			}
		}
		else
		{
			//do nothing
		}

		//specify iterator at start of string
		start = temp.begin();
		//get position of first occurrence of delimiter
		finish = temp.find(mDELIMITER);

		//finish breaking string into seperate month, day, and year values
		if (finish != temp.npos)
		{
			//get year (YYYY) portion of string
			birthYear = temp.substr(finish + 1);
		}
		else
		{
			//do nothing
		}

		//compare search values to record value
		if (birthYear == yearToFind_String || birthYear == yearToFind_minusOne_String)
		{
			if (birthYear == yearToFind_minusOne_String)
			{
				if (birthMonth >= monthToFind_String)
				{
					if (birthDay >= dayToFind_String)
					{
						//loop through columns in row (display matching record)
						outputRows(mainList, mNUM_COLS, i);
						//increment match counter
						matchCount++;
					}
					else
					{
						//do nothing
					}
				}
				else
				{
					//do nothing
				}
			}
			else if (birthMonth <= monthToFind_String && birthDay <= dayToFind_String)
			{
				//loop through columns in row (display matching record)										
				outputRows(mainList, mNUM_COLS, i);
				//increment match counter
				matchCount++;
			}
			else
			{
				//do nothing
			}
		}
		else
		{
			//do nothing
		}
		//set boolean to true to exit loop
		ageGood = true;
	}
}

void Contact::outputAllRecords(vector<vector<string>> &mainList, const int mNUM_COLS)
{
	//loop through rows, excluding first row (assumes column headers)
	for (size_t i = 1; i < mainList.size(); i++)
	{
		//output rows
		outputRows(mainList, mNUM_COLS, i);
	}
}

//relational
bool Contact::defineSortOrder(const vector<string>& vector1, const vector<string>& vector2)
{
	//for sorting values
	//Number = 0 | Gender = 1 | Title = 2 | FirstName = 3 | MiddleName = 4 | LastName = 5 | Address = 6 | City = 7 | State = 8 | Zip = 9 | Email = 10 | DOB = 11 |

	//compare by lastname, firstname, middlename, and number, in that order
	return vector1[5] + vector1[3] + vector1[4] + vector1[0] < vector2[5] + vector2[3] + vector2[4] + vector2[0];
}