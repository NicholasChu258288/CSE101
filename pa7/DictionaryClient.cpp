//-----------------------------------------------------------------------------
// DictionaryClient.cpp
// A test client for the Dictionary ADT
//-----------------------------------------------------------------------------
#include<iostream>
#include<string>
#include<stdexcept>
#include"Dictionary.h"

using namespace std;

int main(){
   Dictionary A;
   Dictionary B;

   if (A.size() != 0)
      cout << "Failed test" << endl;
   cout << "Passed" << endl;
    return 0;
}