/********************************************************************************* 
* Nicholas Chu, nchu5
* 2022 Spring CSE101 PA6
* Arithmetic.cpp
* Takes two large integers from an input file and performs various operations on
* them, which is then printed to an outfile.
*********************************************************************************/

#include<iostream>
#include<string>
#include<stdexcept>
#include<iostream>
#include<fstream>
#include"BigInteger.h"

using namespace std;

int main(int argc, char** argv){
	if (argc != 3){
		cerr << "Usage: ./Arithmatic <infile> <outfile>" << endl;
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

	string bigInt;
	// Uses first as A
	getline(infile, bigInt);
	BigInteger A = BigInteger(bigInt);

	//Skip because newline
	getline(infile, bigInt);

	// Uses second as B
	getline(infile, bigInt);
	BigInteger B = BigInteger(bigInt);

	outfile << A << endl << endl;
	outfile << B << endl << endl;
	outfile << A+B << endl << endl;
	outfile << A-B << endl << endl;
	outfile << A-A << endl << endl;
	

	BigInteger three = BigInteger("3");
	BigInteger two = BigInteger("2");
	outfile << three*A - two*B << endl << endl;
	
	outfile << A*B << endl << endl;

	BigInteger ASquared = A*A;
	outfile << ASquared << endl << endl;
	
	BigInteger BSquared = B*B;
	outfile << BSquared << endl << endl;

	BigInteger nine = BigInteger("9");
	BigInteger sixteen = BigInteger("16");
	outfile << nine*ASquared*ASquared + sixteen*BSquared*BSquared*B << endl;

	infile.close();
	outfile.close();

	return(EXIT_SUCCESS);
}