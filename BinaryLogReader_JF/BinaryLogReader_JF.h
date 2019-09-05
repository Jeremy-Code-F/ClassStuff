#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<fstream>

using namespace std;

 
//Constant ints to hold the 'length' of the fields in the binary file
const int SECTOR = 1, CUSTOMER_ID = 8, CUSTOMER_NAME = 15, DATE = 12, READ_NUMBER_LENGTH = 10, TOTAL = 7, AVERAGE = 7, FULL_SECTOR = 10;

//Declares the Print Report function in LogReader_JF to use it in main
void PrintReport();

/*Water Record class to hold each record in the Water_Log.dat file*/
class WaterRecord {
public:
	int dayOfMonth;
	int Month;
	int Year;
	char Sector[SECTOR];
	char Customer_Id[CUSTOMER_ID];
	char Customer_Name[CUSTOMER_NAME];
	double MonthOneGallons;
	double MonthTwoGallons;
	double MonthThreeGallons;
};


/*BinaryLogReader class to hold our reading functions*/
class BinaryLogReader
{
private: 
	

public: 
	string GetFullSector(char letter);
	static string GetFullTest(char letter);
	vector<WaterRecord>  displayLogFile_binary();
	 
	//Declare an fstream object for our binary file
	fstream fileWaterRecord;
	string fileName;

	BinaryLogReader() { fileName = "Water_Log.dat"; }

};


