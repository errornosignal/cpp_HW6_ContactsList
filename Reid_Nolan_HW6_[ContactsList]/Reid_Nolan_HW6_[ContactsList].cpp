//Reid_Nolan_HW6_[ContactsList].cpp : Defines the entry point for the console application.
//**************************************************************************************//
//Author: Reid S. Nolan                                                                 //
//Date: 03/28/2017                                                                      //
//C++ program for managing a list of contacts (names, addresses, emails, etc.).         //
//                                                                                      //
//For optimal output format visualization, set the console window                       //
//size to 200x50(W x H) and screen buffer size to 200x6025(W x H)                       //
//**************************************************************************************//

#include "stdafx.h"
#include "Contact.h"
#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iterator>


using namespace std;

//display messages to user
void displayProgramHeader();
void displayProgramSubHeader(const string mDATA_FILE);
void displayMainMenu(const string mDATA_FILE);
void displayBirthdayLookup();
void displayListOfMonths();
void displayNoRecordsFound();
void displayMatchCount(const int matchCount);

//record removal
void deleteConfirm(vector<vector<string>> &mainList, const string toMatch, const int columnTosearch, const int mNUM_COLS);
void vecDelete(vector<vector<string>> &vecToDelete);
void vecDelete(vector<string> &vecToDelete);

//input prompts
string makeASelection();
string ageToSearchPrompt(const int mAGE_MIN, const int mAGE_MAX);
string firstNamePrompt();
string lastNamePrompt();
string cityPrompt();
string selectMonth();
string yearToSearchPrompt(const int mYEAR_MIN, const int mYEAR_MAX);
string deleteMatchingPrompt();
string areYouReallySurePrompt();

//get data from system or user
string getCurrentDate();
string getConsoleInputString(const string prompt);
int getConsoleInputInt(const string prompt);

//relational
bool is_digits(const string &s1);

int main()
{
	//create 2-d vector for rows and columns
	vector<vector<string>> mainList;

	//declare and initialize local variables
	const string mDATA_FILE = "FakeNames.csv";
	int programRunCount = 0;

	//display program header
	displayProgramHeader();
	//display current sub-header
	displayProgramSubHeader(mDATA_FILE);

	//loop until user opts to quit
	while (true)
	{
		//declare and initialize local variables
		//initialize new class object
		Contact contact;
		const int mNUM_COLS = 12;
		const int mLAST_COL = 11;
		const int mFIRST_ROW = 0;
		int contactsCount = 0;
		int matchCount = 0;
		fstream inFile;

		//display main menu
		displayMainMenu(mDATA_FILE);

		//loop until valid input is entered
		bool mainMenuChoiceGood = false;
		while (!mainMenuChoiceGood)		//loop for main menu options
		{
			//create vector for valid input values
			vector<string> validMainInput{ "0", "1", "2", "3", "4", "5", "6", "7", "8" };

			//declare and initialize local variables
			string toMatch = "";

			//set console input to local variable
			string menuChoice = getConsoleInputString(makeASelection());

			//validate input
			if (find(begin(validMainInput), end(validMainInput), menuChoice) != end(validMainInput))
			{
				//set boolean to true to exit loop
				mainMenuChoiceGood = true;
			}
			else
			{
				//do nothing
			}

			//Find contact(s) by first name
			if (menuChoice == "1" && mainList.size() > 0)
			{
				//declare and initialize local variable
				const int mFIRST_NAME_COLUMN = 3;

				//set console input to local variable
				toMatch = getConsoleInputString(firstNamePrompt());

				//display matches
				Contact::displayMatches(mainList, toMatch, mFIRST_NAME_COLUMN, mNUM_COLS, matchCount, mFIRST_ROW);

				//display match statistics
				displayMatchCount(matchCount);

				//if matches exist, prompt with option to delete
				if (matchCount > 0)
				{
					//delete matching records after confirmation
					deleteConfirm(mainList, toMatch, mFIRST_NAME_COLUMN, mNUM_COLS);
				}
				else
				{
					//do nothing
				}
			}
			//Find contact(s) by last name
			else if (menuChoice == "2" && mainList.size() > 0)
			{
				//declare and initialize local variable
				const int mLAST_NAME_COLUMN = 5;

				//set console input to local variable
				toMatch = getConsoleInputString(lastNamePrompt());

				//display matches
				Contact::displayMatches(mainList, toMatch, mLAST_NAME_COLUMN, mNUM_COLS, matchCount, mFIRST_ROW);

				//display match statistics
				displayMatchCount(matchCount);

				//if matches exist, prompt with option to delete
				if (matchCount > 0)
				{
					//delete matching records after confirmation
					deleteConfirm(mainList, toMatch, mLAST_NAME_COLUMN, mNUM_COLS);
				}
				else
				{
					//do nothing
				}
			}
			//Find contact(s) by city of residence
			else if (menuChoice == "3" && mainList.size() > 0)
			{
				//declare and initialize local variable
				const int mCITY_COLUMN = 7;

				//set console input to local variable
				toMatch = getConsoleInputString(cityPrompt());

				//display matches
				Contact::displayMatches(mainList, toMatch, mCITY_COLUMN, mNUM_COLS, matchCount, mFIRST_ROW);

				//display match statistics
				displayMatchCount(matchCount);

				//if matches exist, prompt with option to delete
				if (matchCount > 0)
				{
					//delete matching records after confirmation
					deleteConfirm(mainList, toMatch, mCITY_COLUMN, mNUM_COLS);
				}
				else
				{
					//do nothing
				}
			}
			//Find contact(s) by age (down to the day, based on current system time)
			else if (menuChoice == "4" && mainList.size() > 0)
			{
				//copy current date into string
				string dateString = getCurrentDate();

				//loop until valid input is entered
				bool ageGood = false;
				while (!ageGood)
				{
					//declare and initialize local variables
					const int mAGE_MIN = 15;
					const int mAGE_MAX = 85;

					//set console input to local variable
					int age = getConsoleInputInt(ageToSearchPrompt(mAGE_MIN, mAGE_MAX));

					//perform string comparison to find match
					if (age >= mAGE_MIN && age <= mAGE_MAX)
					{
						//type conversions, breaking strings, and getting matches
						Contact::birthdayPreMatchWork(dateString, age, mainList, mNUM_COLS, mFIRST_ROW, mLAST_COL, matchCount, ageGood);

						//display match statistics
						displayMatchCount(matchCount);
					}
					else
					{
						//do nothing
					}
				}
			}
			//Find contact(s) by birthday month or year
			else if (menuChoice == "5" && mainList.size() > 0)
			{
				//display sub-menu options options
				displayBirthdayLookup();

				string birthdayMenuChoice = "";

				//loop until valid input is entered
				bool birthdayMenuGood = false;
				while (!birthdayMenuGood)
				{
					//set console input to local variable
					birthdayMenuChoice = getConsoleInputString(makeASelection());

					//validate input is in range
					if (birthdayMenuChoice == "1" || birthdayMenuChoice == "2")
					{
						//set boolean to true to exit loop
						birthdayMenuGood = true;
					}
					else
					{
						//do nothing
					}
				}
				//select input month option
				if (birthdayMenuChoice == "1")
				{
					//declare and initialize local variables
					string monthSelection = "";
					int monthMenuCounter = 0;

					//create vector for valid input values
					vector<string> validMonthInput{ "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12" };

					//display list of months
					displayListOfMonths();

					//loop until valid input is entered
					bool monthMenuChoiceGood = false;
					while (!monthMenuChoiceGood)
					{
						//set console input to local variable
						monthSelection = getConsoleInputString(selectMonth());

						//validate input
						if (find(begin(validMonthInput), end(validMonthInput), monthSelection) != end(validMonthInput))
						{
							//set boolean to true to exit loop
							monthMenuChoiceGood = true;
						}
						else
						{
							//do nothing
						}
					}

					//display coulumn header
					Contact::displayColumnHeader(mainList, mNUM_COLS, mFIRST_ROW);

					////display record(s) with birthdays in selected month
					Contact::matchMonths(monthSelection, mainList, mLAST_COL, mNUM_COLS, matchCount);

					//display match statistics
					displayMatchCount(matchCount);

					//erase all vector elements from vector
					vecDelete(validMonthInput);
				}
				//select inpput year option
				if (birthdayMenuChoice == "2")
				{
					//declare and initialize local variables
					const int mYEAR_MIN = 1900;
					const int mYEAR_MAX = 2000;

					//loop until valid input
					bool menuGood = false;
					while (!menuGood)
					{
						//set console input to local variable
						int yearToSearch = getConsoleInputInt(yearToSearchPrompt(mYEAR_MIN, mYEAR_MAX));
						//convert integer input to sting
						string yearToSearchString = to_string(yearToSearch);

						//validate input is withinbounds
						if (yearToSearch >= mYEAR_MIN && yearToSearch <= mYEAR_MAX)
						{
							//display column header
							Contact::displayColumnHeader(mainList, mNUM_COLS, mFIRST_ROW);

							//loop through rows
							for (size_t i = 0; i < mainList.size(); i++)
							{
								//get last four of date string in last column
								string birthYearString = mainList[i][mLAST_COL].substr(mainList[i][mLAST_COL].length() - 4);

								//set match condition
								if (birthYearString == yearToSearchString)
								{
									//loop through columns in row (display matching record)										
									Contact::outputRows(mainList, mNUM_COLS, i);
									//increment match counter
									matchCount++;
								}
							}
							//set boolean to true to exit loop
							menuGood = true;
						}
						else
						{
							//do nothing
						}
					}
					//display match statistics
					displayMatchCount(matchCount);
				}				
				else
				{
					//do nothing
				}				
			}
			//Display all contacts
			else if (menuChoice == "6" && mainList.size() > 0)
			{
				//display column header
				Contact::displayColumnHeader(mainList, mNUM_COLS, mFIRST_ROW);
				//display records
				Contact::outputAllRecords(mainList, mNUM_COLS);
				//display number of records output
				cout << endl << "Records displayed: " << (mainList.size() - 1) << endl << endl;
			}
			//DELETE ALL CONTACTS
			else if (menuChoice == "7" && mainList.size() > 0)
			{
				//declare and initialize local variables
				const int mDELETE_ALL = 999;

				//display DELETE_ALL warning message
				cout << endl << "!!!WARNING!!!" << endl;
				cout << "All records will be deleted from memory." << endl << endl;

				//delete matching records after confirmation
				deleteConfirm(mainList, toMatch, mDELETE_ALL, mNUM_COLS);
			}
			//Load contacts from...
			else if (menuChoice == "8")
			{
				//if records already exist in memory
				if (mainList.size() > 0)
				{
					//declare and initialize local variables
					int reloadConfCount = 0;

					//display overwrite waring message
					cout << endl << "!!!WARNING!!!" << endl;
					cout << "All records will be restored from " << mDATA_FILE << endl;
					cout << "This will overwrite any recent changes that may have been made." << endl << endl;

					//loop until valid input is entered
					bool reloadConfGood = false;
					while (!reloadConfGood)
					{
						//set console input to local variable
						string reloadConf = getConsoleInputString(areYouReallySurePrompt());

						//verify input is in range
						if (reloadConf == "y" || reloadConf == "Y")
						{
							//erase all elements from vector
							vecDelete(mainList);
							//reload all records
							Contact::loadRecords(contact, mainList, mDATA_FILE, inFile, contactsCount);
							//set boolean to true to exit loop
							reloadConfGood = true;
						}
						else if (reloadConf == "n" || reloadConf == "N")
						{
							//display no records loaded message
							cout << endl << "No records have been loaded." << endl << endl;
							//set boolean to true to exit loop
							reloadConfGood = true;
						}
						else
						{
							//do nothing
						}
					}
				}
				//if no records already exist in memory
				else if (mainList.size() == 0)
				{
					//load records from file
					Contact::loadRecords(contact, mainList, mDATA_FILE, inFile, contactsCount);
				}
				else
				{
					//do nothing
				}
			}
			//Exit ContactsList
			else if (menuChoice == "0")
			{
				//erase all vector elements from vector
				vecDelete(mainList);
				vecDelete(validMainInput);

				//display exit status message
				Contact::displayExit();
			}
			//display no records found message if no records are currently in memory(mainList vector)
			else if (mainList.size() == 0)
			{
				//display message for no matching record(s)
				displayNoRecordsFound();
			}
			else
			{
				//do nothing
			}
			//erase all vector elements from vector
			vecDelete(validMainInput);
		}
		//increment program run count
		programRunCount++;
	}
	return 0;
}

void displayProgramHeader()
{
	//display program header
	cout << "//Reid_Nolan_HW6_[ContactsList].cpp : Defines the entry point for the console application." << endl;
	cout << "//**************************************************************************************//" << endl;
	cout << "//Author: Reid S. Nolan                                                                 //" << endl;
	cout << "//Date: 03/28/2017                                                                      //" << endl;
	cout << "//C++ program for managing a list of contacts (names, addresses, emails, etc.).         //" << endl;
	cout << "//                                                                                      //" << endl;
	cout << "//For optimal output format visualization, set the console window                       //" << endl;
	cout << "//size to 200x50(W x H) and screen buffer size to 200x6025(W x H)                       //" << endl;
	cout << "//**************************************************************************************//" << endl;
}

void displayProgramSubHeader(string mDATA_FILE)
{
	cout << endl;
	cout << "Today's date: " << getCurrentDate() << endl << endl;

	cout << "*** No contact records currently loaded into memory. ***" << endl;
	cout << "*** Please select option 8 to load from " << mDATA_FILE << " before beginning. ***" << endl << endl;
}

void displayMainMenu(const string mDATA_FILE)
{
	//display main menu
	cout << "---------------Main Menu---------------" << endl;
	cout << "1. Find contact(s) by first name." << endl;
	cout << "2. Find contact(s) by last name." << endl;
	cout << "3. Find contact(s) by city of residence." << endl;
	cout << "4. *BONUS* Find contact(s) by age." << endl;
	cout << "5. *BONUS* Find contact(s) by birthday month or year." << endl;
	cout << "6. Display all contacts." << endl;
	cout << "7. !!!DELETE ALL CONTACTS!!!" << endl;
	cout << "8. Load contacts from " << mDATA_FILE << " into memory." << endl;
	cout << "0. Exit ContactsList." << endl;
}

void displayBirthdayLookup()
{
	//display birthday lookup menu
	cout << endl;
	cout << "-----Birthday Lookup-----" << endl;
	cout << "1. Search birthdays by month." << endl;
	cout << "2. Search birthdays by year." << endl;
}

void displayListOfMonths()
{
	//display list of months menu
	cout << endl;
	cout << " 1. January" << endl;
	cout << " 2. February" << endl;
	cout << " 3. March" << endl;
	cout << " 4. April" << endl;
	cout << " 5. May" << endl;
	cout << " 6. June" << endl;
	cout << " 7. July" << endl;
	cout << " 8. August" << endl;
	cout << " 9. September" << endl;
	cout << "10. October" << endl;
	cout << "11. November" << endl;
	cout << "12. December" << endl;
}

void displayNoRecordsFound()
{
	//display no records found message
	cout << endl << "No records could be found." << endl << endl;
}

void displayMatchCount(const int matchCount)
{
	//display count of matching values
	cout << endl << "Matching record(s) found: " << matchCount << endl << endl;
}

void deleteConfirm(vector<vector<string>> &mainList, const string toMatch, const int columnTosearch, const int mNUM_COLS)
{
	//declare and initialize local variables
	string deleteConfirm = "";
	int deletionCounter = 0;

	//loop until input is good
	bool deleteConfirmGood = false;
	while (!deleteConfirmGood)
	{
		if (columnTosearch == 999) //for DELETE_ALL
		{
			//set console input to local variable
			deleteConfirm = getConsoleInputString(areYouReallySurePrompt());
		}
		else
		{
			//set console input to local variable
			deleteConfirm = getConsoleInputString(deleteMatchingPrompt());
		}

		if (deleteConfirm == "y" || deleteConfirm == "Y")
		{
			if (columnTosearch == 999) //for DELETE_ALL
			{
				//remove vector
				vecDelete(mainList);

				//display deletion confirmation message
				cout << endl << "All records have been deleted." << endl << endl;
			}
			else
			{
				//create vector and store indicies of matching vector elements to delete 
				vector<int> indices;
				for (size_t i = 0; i < mainList.size(); i++)
				{
					//condition check
					if (mainList[i].size() >= 1 && mainList[i][columnTosearch] == toMatch)
					{
						//add indices of matching elements to vector
						indices.push_back(i);
					}
					else
					{
						//do nothing
					}
				}

				//delete vector elements backwards (avoids offset issues)
				for (size_t i = indices.size(); i-- > 0; deletionCounter++)
				{
					mainList.erase(mainList.begin() + indices[i]);
				}

				//display deletion confirmation message
				cout << endl << "Matching records deleted: " << deletionCounter << endl << endl;
			}

			//set boolean to true to exit loop
			deleteConfirmGood = true;
		}
		else if (deleteConfirm == "n" || deleteConfirm == "N")
		{
			//display no deletion perfomed confirmation message
			cout << endl << "No records have been deleted." << endl << endl;
			;
			//set boolean to true to exit loop
			deleteConfirmGood = true;
		}
		else
		{
			//do nothing
		}
	}
}

void vecDelete(vector<vector<string>> &vecToDelete)
{
	//erase all vector elements from vector
	vecToDelete.erase(vecToDelete.begin(), vecToDelete.end());
	vector<vector<string>>().swap(vecToDelete);
}

void vecDelete(vector<string> &vecToDelete)
{
	//erase all vector elements from vector
	vecToDelete.erase(vecToDelete.begin(), vecToDelete.end());
	vector<string>().swap(vecToDelete);
}

string makeASelection()
{
	//display promt to enter selection
	return "Make a selection> ";
}

string ageToSearchPrompt(const int mAGE_MIN, const int mAGE_MAX)
{
	//declare and initialize local variables
	string s1 = "Enter age to search(";
	string s2 = to_string(mAGE_MIN);
	string s3 = "-";
	string s4 = to_string(mAGE_MAX);
	string s5 = ")> ";
	string s6 = s1 + s2 + s3 + s4 + s5;

	//display prompt for age to search
	return s6;
}

string firstNamePrompt()
{
	//display prompt for first name to search
	return "Enter first name to search> ";
}

string lastNamePrompt()
{
	//display prompt for last name to search
	return "Enter last name to search> ";
}

string cityPrompt()
{
	//display prompt for city to search 
	return "Enter city to search> ";
}

string selectMonth()
{
	return "Select month to search> ";
}

string yearToSearchPrompt(const int mYEAR_MIN, const int mYEAR_MAX)
{
	//declare and initialize local variables
	string s1 = "Enter year to search(";
	string s2 = to_string(mYEAR_MIN);
	string s3 = "-";
	string s4 = to_string(mYEAR_MAX);
	string s5 = ")> ";
	string s6 = s1 + s2 + s3 + s4 + s5;

	//display prompt for year to search
	return s6;
}

string deleteMatchingPrompt()
{
	//display prompt to delete matchin record(s)
	return "Delete corresponding record(s)?(y/n)> ";
}

string areYouReallySurePrompt()
{
	//display prompt to confirm deletion af all records
	return "This action cannot be undone. Continue(y/n)> ";
}

string getCurrentDate()
{
	//declare and initialize local variables
	const int mMAX_CHARS = 12;

	//get current formatted date
	//create tm struct for time
	struct tm newtime;
	//typedefs
	time_t rawtime;
	errno_t err;
	//create buffer for formatting
	char timeBuffer[mMAX_CHARS];

	//get time and format output as MM/DD/YYYY
	time(&rawtime);
	//set error status
	err = localtime_s(&newtime, &rawtime);
	//format time string in buffer
	strftime(timeBuffer, mMAX_CHARS, "%m/%d/%Y", &newtime);

	//return formatted date
	return timeBuffer;
}

string getConsoleInputString(const string prompt)
{
	//declare and initialize local variables
	string s1 = "";

	//loop until input is good
	bool inputGood = false;
	while (!inputGood)
	{
		//prompt for input
		cout << prompt;
		//read input from console
		getline(cin, s1);

		if (s1.length() == 0)
		{
			//do nothing
		}
		else
		{
			//set boolean to true to leave while loop
			inputGood = true;
		}
	}
	//return validated input
	return s1;
}

int getConsoleInputInt(const string prompt)
{
	//declare and initialize local variables
	const int mMAX_DIGITS = 4;
	int integer = 0;
	string s1 = "";

	//loop until input is good
	bool inputGood = false;
	while (!inputGood)
	{
		//prompt for input
		cout << prompt;
		//read input from console
		getline(cin, s1);

		//verify value represented by string does not exceed max int value
		if (s1.length() > 0 && s1.length() <= mMAX_DIGITS && is_digits(s1))
		{
			//type conversion from string to int
			integer = stoi(s1);
			//set boolean to true to leave while loop
			inputGood = true;
		}
		else
		{
			//do nothing
		}
	}
	//return validated input
	return integer;
}

bool is_digits(const string &s1)
{
	//check if string is all digits
	return all_of(s1.begin(), s1.end(), ::isdigit);
}