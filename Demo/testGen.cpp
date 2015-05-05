#include "testGen.h"
#include "../robinHoodHash.h"


/**main
	This program is to allow an easy demo
	of all the functionality of the round robin probe
	with underlying sparse array data structure
**/
int main(int argc, char *argv[])
{
int num_of_frames;
std::string output_name;
std::ofstream output;
std::string input1;
std::string input2;
std::string temp;
	if(argc == 1) {
		std::cout << "\tType in '-u' for usage string" 
		  << std::endl;
	}
	cs375::robinHoodHash<std::string> hashObj;
	
	// Start of user interface 
	std::cout << "\tType 'exit' to exit" << 
	  "\n\tType 'insert' <key> to insert " <<
	  "\n\tType 'delete' <key> to delete" << 
	  "\n\tType 'find' <key> to find index" << 
	  "\n\tType 'size' to get the current size" << 
	  "\n\tType 'tsize' to get the table size" << 
	  "\n\tType 'help' to see this again" << 
	  std::endl;
	// Loops to receive user input
	while(1) {
		std::getline(std::cin, temp);
		std::stringstream stream;
		stream << temp;
		stream >> input1 >> input2;
		std::string temp2 = input1;
		toUpper(temp2);
		//Forces exit from ui 
		if (temp2 == "EXIT"){
			exit(0);
		}
		else if (temp2 == "HELP") {
			std::cout << "\tType 'exit' to exit" << 
	  		  "\n\tType 'insert' <key> to insert " <<
	  		  "\n\tType 'find' <key> to find index" << 
	  		  "\n\tType 'size' to get the current size" << 
			  "\n\tType 'tsize' to get the table size" << 
	  		  "\n\tType 'delete' <key> to delete" << 
			  "\n\tType 'help' to see this again" << 
	  		  std::endl;
		}	
		//Insertiion code
		else if (input1 == "insert" && hashObj.searchKey(input2)) {
			std::cout << "\t->Currently already in hash table"
			  <<std::endl;
		}
		else if(input1 == "insert"){
			if(hashObj.insertKey(input2)) {
				std::cout <<"\t->'" <<  input2 <<
				  "' successfully inserted "
				  << std::endl;
			} else {
				std::cout << "\t->Input failed" 
				  << std::endl;
			}
		}
		//Deletion code
		else if (input1 == "delete" && !hashObj.searchKey(input2)) {
			std::cout << "\t->'" << input2 << "' not int table" <<
			  std::endl;
		}
		else if(input1 == "delete"){
			if(hashObj.deleteKey(input2)) {
				std::cout << "\t->" <<  input2 <<
				  " successfully deleted "
				  << std::endl;
			}
			
		}
		//Find code
		else if (input1 == "find" && hashObj.searchKey(input2)) {
			std::cout << "\t->'" << input2 << "' is in " <<
			  hashObj.searchKeyIndex(input2) << 
			  std::endl;
		}
		else if(input1 == "find"){
			std::cout << "\t->" <<  input2 <<
				  " is not in the hashtable "
				  << std::endl;
		}
		//Side code
		else if (input1 == "size") {
			std::cout << "\t->'" << hashObj.size() <<
			  std::endl;
		}
		//Table side code
		else if (input1 == "tsize") {
			std::cout << "\t->'" << hashObj.tSize() <<
			  std::endl;
		}
		else {
		
			std::cerr << "\t->ERROR:That is not a valid input " << std::endl;
		}
	}
	return 0;
}


bool openOutfile(std::string output_name, std::ofstream &outfile)
{
	if (output_name != "") {
		outfile.open(output_name);
		return 1;
	} else {
		std::cerr << "openOutfile(): Invalid input\n" << std::endl;
		throw(1);
	}
	return 0;
}

bool closeOutfile(std::ofstream &outfile)
{
	outfile.close();
	return 1;
}

bool isNumeric(std::string input)
{
        for (unsigned i = 0; i < input.length(); i++) {
                if ( input[i] < 48 && input[i] > 57)
                        return false;
        }
        return true;
}

void toUpper(std::string &input)
{
	std::locale loc;
	for (std::string::size_type i = 0; i < input.length(); i++) 
		input[i] = std::toupper(input[i],loc);

}
