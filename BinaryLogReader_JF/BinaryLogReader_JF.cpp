#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include "BinaryLogReader_JF.h"


using namespace std;

 
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

