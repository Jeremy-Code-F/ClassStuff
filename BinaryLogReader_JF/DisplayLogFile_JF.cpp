

#include<iostream>
#include<string>
#include<iomanip>
#include<vector>
#include"BinaryLogReader_JF.h"

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


//Implementing the GetFullTest function
/*This function gets passed a letter when reading the binary file's sector and turns it into the full word
ie. N = North, S = South*/
string BinaryLogReader::GetFullTest(char letter) {
	//'Switch' statement to determine the sector
	if (letter == 'N') {
		return "North";
	}
	else if (letter == 'S') {
		return "South";
	}
	else if (letter == 'W') {
		return "West";
	}
	else if (letter == 'E') {
		return "East";
	}
	return "Error not a valid Sector letter";
}


/*Prints the report out from our binary log file*/
void PrintReport() {

	//Vector to hold all records from .dat file
	vector<WaterRecord> records;

	//Read the binary file and put all water records into our Vector
	BinaryLogReader *brr = new BinaryLogReader();
	records = brr->displayLogFile_binary();


	/*Prints our column headers out based on the const int for length for each element
	These constant ints are all declared at the top adjust these there*/
	cout << left << setw(CUSTOMER_NAME) << setfill(' ') << "NAME";
	cout << left << setw(CUSTOMER_ID) << setfill(' ') << "ID";
	cout << left << setw(DATE) << setfill(' ') << "DATE";
	cout << left << setw(FULL_SECTOR) << setfill(' ') << "SECTOR";
	cout << left << setw(READ_NUMBER_LENGTH) << setfill(' ') << "MONTH_1";
	cout << left << setw(READ_NUMBER_LENGTH) << setfill(' ') << "MONTH_2";
	cout << left << setw(READ_NUMBER_LENGTH) << setfill(' ') << "MONTH_3";
	cout << left << setw(READ_NUMBER_LENGTH) << setfill(' ') << "TOTAL";
	cout << left << setw(READ_NUMBER_LENGTH) << setfill(' ') << "AVERAGE" << endl;


	//Prints each Water Record values to the screen
	for (int i = 0; i < records.size(); i++) {
		cout << left << setw(CUSTOMER_NAME) << setfill(' ') << records[i].Customer_Name;
		cout << left << setw(CUSTOMER_ID) << setfill(' ') << records[i].Customer_Id;
		cout << left << setw(DATE) << setfill(' ') << to_string(records[i].Month) + "/" + to_string(records[i].dayOfMonth) + "/" + to_string(records[i].Year);
		cout << left << setw(FULL_SECTOR) << setfill(' ') << BinaryLogReader::GetFullTest(records[i].Sector[0]);//gets sector[0] to get just 'N' or 'S'
		cout << left << setw(READ_NUMBER_LENGTH) << setfill(' ') << records[i].MonthOneGallons;
		cout << left << setw(READ_NUMBER_LENGTH) << setfill(' ') << records[i].MonthTwoGallons;
		cout << left << setw(READ_NUMBER_LENGTH) << setfill(' ') << records[i].MonthThreeGallons;
		cout << left << setw(READ_NUMBER_LENGTH) << setfill(' ') << records[i].MonthOneGallons + records[i].MonthTwoGallons + records[i].MonthThreeGallons;
		cout << left << setw(READ_NUMBER_LENGTH) << setfill(' ') << (records[i].MonthOneGallons + records[i].MonthTwoGallons + records[i].MonthThreeGallons) / 3 << endl;
	}

	
}

/*This function gets passed a letter when reading the binary file's sector and turns it into the full word
ie. N = North, S = South*/
string BinaryLogReader::GetFullSector(char letter) {
	//'Switch' statement to determine the sector
	if (letter == 'N') {
		return "North";
	}
	else if (letter == 'S') {
		return "South";
	}
	else if (letter == 'W') {
		return "West";
	}
	else if (letter == 'E') {
		return "East";
	}
	return "Error not a valid Sector letter";
}


vector<WaterRecord> BinaryLogReader::displayLogFile_binary() {


	//Water Record object to hold our record once it's read
	fstream file;
	vector<WaterRecord> records;

	//Open our .dat file
	file.open("Water_Log.dat", ios::in | ios::binary);

	//Makes sure the file is able to be opened
	if (file.is_open()) {
		WaterRecord record;



		//Reads a line from the file and reinterprets it to a char array based on size of WaterRecord
		file.read(reinterpret_cast<char *>(&record), sizeof(record));

		//While we didn't read the end of the file here
		while (!file.eof()) {

			//push current record into vector
			records.push_back(record);

			//Read the next line from the binary file
			file.read(reinterpret_cast<char *>(&record), sizeof(record));

		}
	}
	//If the file was unable to be opened then return false
	else {
		file.close();
		return records;

	}
	//Return true if everything else worked out
	//Close the file 
	file.close();
	return records;
}