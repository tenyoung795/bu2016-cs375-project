#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <sstream>

enum load_factor {NONE, LOW, MEDIUM, HIGH, EXTREME};
void initialization(int argc, char *argv[], int &num_of_Frames, 
  load_factor &load, std::string &outfile);
bool isNumeric(std::string input);
void toUpper(std::string &input);
bool openOutfile(std::string, std::ofstream &outfile);
bool closeOutfile(std::ofstream &outfile);
void writeInstructions(std::ofstream &outfile, load_factor &load, 
  int &num_of_frames);
