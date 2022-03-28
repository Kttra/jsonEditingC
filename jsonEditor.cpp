#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include "json.hpp"

/*
    A program that showcases the use of the json.hpp library.

    This is a basic program that shows how to read and write
    data to json files.
*/

using json = nlohmann::json;

int main() {
    //---------------------First Json File Example----------------------------
    //Open json file
	std::ifstream file;
	file.open("sample.json"); //Example of using a directory D:\\Users\\Username\\Desktop\\sample.json
	//Create a jsonObject
	nlohmann::json jsonObject;
	if(file.is_open()){
		file >> jsonObject;
	}

	//Add a new entry at the 3rd index
	jsonObject[3]["id"] = 103;
	jsonObject[3]["sorc"] = "1.2.3.4";
	jsonObject[3]["dest"] = "5.4.3.2";
	jsonObject[3]["srvc"] = "tcp/5070";
	jsonObject[3]["desc"] = "Data Center C";

	//Close the file
    file.close();

    //Output a new json file with the edits we made
	std::ofstream file2("sampleEdited.json");
	std::cout << jsonObject.dump(2);

	//Output our new jsonobject to the console
	file2 << std::setw(4) << jsonObject;

    //Close the file
    file2.close();

	//---------------------Second Json File Example----------------------------
    //Add in a separator to make it easier to split the two json files in the console
    std::cout << std::endl << std::endl << std::endl;
    std::cout << "------------------------------------" << std::endl << std::endl;

    //Open json file
	std::ifstream file3;
	file3.open("sample2.json");

	//Create a jsonObject
	nlohmann::json jsonObject2;
	if(file3.is_open()){
		file3 >> jsonObject2;
	}

    //Editing a current entry
    jsonObject2["Marco"]["Age"] = 19;
    jsonObject2["Marco"]["Lap Time"] = "2:11";
    jsonObject2["Marco"]["Best Time"] = "1:32";

    //Creating a json array and adding it to the json object
    json json_array = {"Saturday", "Sunday"};
    jsonObject2["Marco"]["Days Participated"] = json_array;
    jsonObject2["Marco"]["Days Participated"].push_back("Tuesday");

	//Close the file
    file3.close();

    //Output a new json file with the edits we made
	std::ofstream file4("sample2Edited.json");
	std::cout << jsonObject2.dump(2);

	//Output our new jsonobject to the console
	file4 << std::setw(4) << jsonObject2;

	//Close the file
    file4.close();

	//Wait for input from user before ending the program
	std::string nothing;
	std::cout << std::endl << std::endl << "Press enter to end the program...";
	getline(std::cin, nothing);

	return 0;
}
