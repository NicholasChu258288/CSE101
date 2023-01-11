/********************************************************************************* 
* Nicholas Chu, nchu5
* 2022 Spring CSE101 PA8
* Order.cpp
* Reads an input file and save each  of the lines into a dictionary, where the key
* is the contents of the line and the value is the line number. It then prints the
* resulting dictionary in order to a specified outfile.
*********************************************************************************/

#include<iostream>
#include<string>
#include<stdexcept>
#include<iostream>
#include<fstream>
#include "Dictionary.h"

using namespace std;

int main(int argc, char** argv){
    if (argc != 3){
		cerr << "Usage: ./Order <infile> <outfile>" << endl;
		return(EXIT_FAILURE);
	}

    ifstream infile;
    ofstream outfile;

    infile.open(argv[1]);
    if (!infile.is_open()){
        cerr << "Unable to open file " << argv[1] << " for reading" << endl;
      	return(EXIT_FAILURE);
    }

    outfile.open(argv[2]);
	if (!outfile.is_open()){
		cerr << "Unable to open file " << argv[2] << " for reading" << endl;
      	return(EXIT_FAILURE);
	}

	string s;
	int line_count = 1;
	Dictionary D;

	while (getline(infile, s)){
		D.setValue(s, line_count);
		line_count += 1;
	}
    
	outfile << D << endl;

	outfile << D.pre_string();

    infile.close();
	outfile.close();

	return(EXIT_SUCCESS);
}
