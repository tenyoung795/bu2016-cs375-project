#include "testGen.h"

int main(int argc, char *argv[])
{
int num_of_frames;
std::string output_name;
std::ofstream output;
std::string input;
/*
	try{
		initialization(argc, argv, num_of_frames, load, output_name);
		openOutfile(output_name, output);
		writeInstructions(output, load, num_of_frames);
		closeOutfile(output);
	} catch (int a) {
		exit(1);	
	}
*/
	while(input != "EXIT") {
	std::cin >> input;
	toUpper(input);
	}
	return 0;
}


/*
void initialization(int argc, char *argv[], int &num_of_frames, load_factor &load, std::string &out) 
{ 
	if (argc == 1) {
                std::cout << "\tUse option -u for user commands\n"
                  << std::endl;
                throw 0;
        } else if (argc <= 4) {
                for (int i = 1; i < argc; i++) {
                        if (strcmp(argv[i], "-u") == 0) {
                                std::cout << "./testGen \n\t<frames-of-memory>"
                                  " [NONE | LOW | MEDIUM | HIGH | EXTREME] "
				  "<output-file> expected\n"
				  << std::endl;
                                throw 0;
                        }
                        if (i == 1) {
                                if(isNumeric(argv[i])){
                                        num_of_frames = atoi(argv[i]);
					if (num_of_frames == 0) {
						std::cerr << "ERROR: num-of-frames can't = 0"
						  << std::endl;
						throw(1);
					}
                                } else {
                                  std::cerr << "ERROR: Non-numeric frame size\n"
                                    << std::endl;
                                  throw 1;
                                }
                        }
			if (i == 2) {
				std::string temp = argv[i];
				toUpper(temp);
				if (temp == "NONE")
					load = NONE;
				else if (temp == "LOW")	
					load = LOW;
				else if (temp == "MEDIUM")
					load = MEDIUM;
				else if (temp == "HIGH")
					load = HIGH;
				else if (temp == "EXTREME")
					load = EXTREME;
				else {
				std::cerr << "ERROR: INCORRECT LOAD FACTOR INPUT" 
				  << std::endl; 
				throw 1;
				}
			}
                        if (i == 3) {
				out = argv[i];
                        }
                }
        } else {
                std::cerr << "ERROR: Incorrect format. See '-u'\n"
                  << std::endl;
                throw 1;
        }
}
*/
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
