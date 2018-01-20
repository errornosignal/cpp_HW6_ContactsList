//Reid_Nolan_HW6_[ContactsList]
//Contact.h
//***********************************************************************************************//
//Author: Reid S. Nolan
//Date: 03/28/2017
//Contact Class Header File
//Class for returning specific values from input file for Reid_Nolan_HW6_[ContactsList].cpp
//***********************************************************************************************//

#pragma once
#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

class Contact
{
private:
	//declare class variables
	string Number;
	string Gender;
	string Title;
	string FirstName;
	string MiddleName;
	string LastName;
	string Address;
	string City;
	string State;
	string Zip;
	string Email;
	string DOB;

public:
	Contact();
	~Contact();

	//setters
	void setNumber(string nextValue);
	void setGender(string nextValue);
	void setTitle(string nextValue);
	void setFirstName(string nextValue);
	void setMiddleName(string nextValue);
	void setLastName(string nextValue);
	void setAddress(string nextValue);
	void setCity(string nextValue);
	void setState(string nextValue);
	void setZip(string nextValue);
	void setEmail(string nextValue);
	void setDOB(string nextValue);

	//getters
	string getNumber();
	string getGender();
	string getTitle();
	string getFirstName();
	string getMiddleName();
	string getLastName();
	string getAddress();
	string getCity();
	string getState();
	string getZip();
	string getEmail();
	string getDOB();

	//load records into vectors
	static void Contact::loadRecords(Contact contact, vector<vector<string>> &mainList, const string mDATA_FILE, fstream &inFile, int &contactsCount);

	//status messages
	static void Contact::displayLoadingRecords(const string mDATA_FILE);
	static void Contact::displayNoInputFile(const string mDATA_FILE);
	static void Contact::displayContactsCount(const int contactsCount);
	static void Contact::displayExit();

	//matching & displaying data
	static void Contact::displayColumnHeader(vector<vector<string>> &mainList, const int mNUM_COLS, const int i);
	static void Contact::outputRows(vector<vector<string>> &mainList, const int mNUM_COLS, const int i);
	static void Contact::displayMatches(vector<vector<string>> &mainList, const string toMatch, const int columnTosearch, const int mNUM_COLS, int &matchCount, const int i);
	static void Contact::birthdayPreMatchWork(string dateString, int age, vector<vector<string>> &mainList, const int mNUM_COLS, const int mFIRST_ROW, const int mLAST_COL, int &matchCount, bool &ageGood);
	static void Contact::matchMonths(string monthSelection, vector<vector<string>> &mainList, const int mLAST_COL, const int mNUM_COLS, int &matchCount);
	static void Contact::outputAllRecords(vector<vector<string>> &mainList, const int mNUM_COLS);

	//relational
	static bool Contact::defineSortOrder(const vector<string>& vector1, const vector<string>& vector2);
};