/********************************************************************************* 
* Nicholas Chu, nchu5
* 2022 Spring CSE101 PA8
* WordFrequency.cpp
* Reads an imput file and then outputs a dictionary of all the words from the input
* file and their frequencies
*********************************************************************************/

#include<iostream>
#include<string>
#include<stdexcept>
#include<iostream>
#include<fstream>

#include "Dictionary.h"

using namespace std;

int main(int argc, char** argv){
    
    ifstream in;
    ofstream out;

    if( argc != 3 ){
      cerr << "Usage: " << argv[0] << " <input file> <output file>" << endl;
      return(EXIT_FAILURE);
   }

   // open files for reading and writing 
   in.open(argv[1]);
   if( !in.is_open() ){
      cerr << "Unable to open file " << argv[1] << " for reading" << endl;
      return(EXIT_FAILURE);
   }

   out.open(argv[2]);
   if( !out.is_open() ){
      cerr << "Unable to open file " << argv[2] << " for writing" << endl;
      return(EXIT_FAILURE);
   }

   
   size_t begin, end, len;
   string line;
   string token;


   size_t tBegin, tEnd, tLen;
   string buffer;
   string word;

   string space = " ";
   string delim = " \t\\\"\',<.>/?;:[{]}|`~!@#$%^&*()-_=+0123456789";

   Dictionary D;
   

    while( getline(in, line) ){

      len = line.length();

      begin = min(line.find_first_not_of(space, 0), len);
      end   = min(line.find_first_of(space, begin), len);
      token = line.substr(begin, end-begin);
      
      while( token!="" ){

         word = "";
         
         tLen = token.length();

         tBegin = min(token.find_first_not_of(delim, 0), tLen);
         tEnd = min(token.find_first_of(delim, tBegin), tLen);
         buffer = token.substr(tBegin, tEnd-tBegin);

         while (buffer!=""){
            word += buffer;
            
            tBegin = min(token.find_first_not_of(delim, tEnd+1), tLen);
            tEnd = min(token.find_first_of(delim, tBegin), tLen);
            buffer = token.substr(tBegin, tEnd-tBegin);
         }

         for (int i = 0; i < (int)word.length(); i++){
            word[i] = tolower(word[i]);
         }

         if (word != ""){
            if (D.contains(word) == true){
                int count = D.getValue(word) + 1;
                D.setValue(word, count);
            } else {
               D.setValue(word, 1);
            }
         }

         // getting next token
         begin = min(line.find_first_not_of(space, end+1), len);
         end   = min(line.find_first_of(space, begin), len);
         token = line.substr(begin, end-begin);
      }

   }

   out << D;

    // close files 
   in.close();
   out.close();

   return(EXIT_SUCCESS);


}