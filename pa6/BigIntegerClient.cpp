//-----------------------------------------------------------------------------
//  BigIntegerClient.cpp 
//  A test client for the BigInteger ADT
//-----------------------------------------------------------------------------
#include<iostream>
#include<string>
#include<stdexcept>
#include"BigInteger.h"

using namespace std;

int main(){
   
    BigInteger A = BigInteger("+13378008135");
    A.makeZero();
    cout << "Fin Make zero" << endl;
    if (A.sign() != 0)
      return 1;

   cout << "A" << A << endl;

    BigInteger B = BigInteger();
    cout << "B" << B << endl;
    if (!(A == B))
      return 2;
    
   
   cout << "Passed all" << endl;

    return 0;
}
