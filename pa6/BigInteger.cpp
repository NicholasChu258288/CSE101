/********************************************************************************* 
* Nicholas Chu, nchu5
* 2022 Spring CSE101 PA6
* BigInteger.cpp
* Contains the implementation of the List ADT.
*********************************************************************************/

#include<iostream> // Standard library
#include<string> // Enables usage of string datatype
#include<stdexcept> // Used for handling standard errors
#include<ctype.h>
#include<math.h>

#include "BigInteger.h" // List header

using namespace std;


// Basically controls how many digits are stored in each node.
int power = 9;              // Power should be between 0-9 inclusive, how many digits
long base = pow(10, power); // 10^power, max value not inclusive of what each data can be set to

// For final submission power should be set to 9, the base would be 1 billion

// Class Constructors & Destructors ----------------------------------------

// Constructing new default BigInteger
BigInteger::BigInteger(){
    signum = 0;
    digits = List();
}

// Construct new BigInteger based on string
BigInteger::BigInteger(std::string s){
    // When the string is empty
    if (s.length() == 0){
        throw std::invalid_argument("BigInteger: Constructor: empty string");
    }

    // When string is only just a sign
    if (isdigit(s.at(0)) == 0){
        if (s.length() == 1){
            throw std::invalid_argument("BigInteger: Constructor: non-numeric string");
        }
        if (s.at(0) != '-' && s.at(0) != '+'){
            throw std::invalid_argument("BigInteger: Constructor: non-numeric string");
        }
    }

    for (int i = 1; i < (int)s.length(); i++){
        if (isdigit(s.at(i)) == 0){
            throw std::invalid_argument("BigInteger: Constructor: non-numeric string");
        }
    }

    int y = 0;
    if (isdigit(s.at(0)) == 0){
        if (s.at(0) == '-'){
            signum = -1;
        }
        if (s.at(0) == '+'){
            signum = 1;
        }
        y += 1;
    } else {
        signum = 1;
    }
    string data = ""; // Data that will hold what is read and put into the string
    for (int x = s.length()-1; x >= y; x--){
        data = s.at(x) + data;
        if ((int)data.length() == power){
            digits.insertAfter(std::stol(data));
            data = "";  
        }
    }

    if (data.length() != 0){
        digits.insertAfter(std::stol(data));
    }

    // Deleting any left over leading 0's
    digits.moveFront();
    while (digits.peekNext() == 0){
        digits.eraseAfter();
    }
}

// Copies a BigInteger N
BigInteger::BigInteger(const BigInteger& N){
    signum = N.signum;
    digits = N.digits;
}

// Access functions --------------------------------------------------------

// Returns the sign of the big integer, 1 and -1 for positive and negative and 0 if 0 
int BigInteger::sign() const{
    return signum;
}

int BigInteger::compare(const BigInteger& N) const{
    // If the are the same
    if (signum == N.signum && digits == N.digits){
        return 0;
    }
    // When signs are different
    if (signum < N.sign()){
        return -1;
    }
    if (signum > N.sign()){
        return 1;
    }
    // When signs are the same
    //When comparing two negative integers
    if (signum == -1 && N.sign() == -1){
        // Both negatives but different sizes
        if (digits.length() > N.digits.length()){
            return -1;
        }
        if (digits.length() < N.digits.length()){
            return 1;
        }
        // Creating copies of lists to iterate through
        List thisDigits = digits;
        List NDigits = N.digits;
        thisDigits.moveFront();
        NDigits.moveFront();
        while (thisDigits.position() < thisDigits.length()){
            ListElement thisData = thisDigits.moveNext();
            ListElement NData = NDigits.moveNext();
            if (thisData < NData){
                return 1;
            }
            if (thisData > NData){
                return -1;
            }
        }
    }
    //When comapring two postive integers
    if (signum == 1 && signum == 1){
        if (digits.length() > N.digits.length()){
            return 1;
        }
        if (digits.length() < N.digits.length()){
            return -1;
        }
        // Creating copies of lists to iterate through
        List thisDigits = digits;
        List NDigits = N.digits;
        thisDigits.moveFront();
        NDigits.moveFront();
        while (thisDigits.position() < thisDigits.length()){
            ListElement thisData = thisDigits.moveNext();
            ListElement NData = NDigits.moveNext();
            if (thisData < NData){
                return -1;
            }
            if (thisData > NData){
                return 1;
            }
        }
    }
    return 0;
}

// Manipulation procedures -------------------------------------------------
// Returns a BigInteger representing the sum of this and N.
void BigInteger::makeZero(){
    signum = 0;    
    digits.clear();
}

// If this BigInteger is zero, does nothing, otherwise reverses the sign of 
// this BigInteger positive <--> negative. 
void BigInteger::negate(){
    if (signum != 0){
        signum *= -1;
    }
    return;
}

// Helper functions --------------------------------------------------------
// negateList()
// Changes the sign of each integer in List L. Used by sub().
void negateList(List& L){
    L.moveFront();
    while (L.position() < L.length()){
        ListElement data = L.moveNext() * -1;
        L.setBefore(data);
    }
    L.moveFront();
}

// sumList()
// Overwrites the state of S with A + sgn*B (considered as vectors).
// Used by both sum() and sub().
void sumList(List& S, List A, List B, int sgn){
    A.moveFront();
    B.moveFront();
    if (A.length() != B.length()){
        if (A.length() > B.length()){
            while (A.length() != B.length()){
                B.insertBefore(0);
            }
        }
        if (A.length() < B.length()){
            while (A.length() != B.length()){
                A.insertBefore(0);
            }
        }
    }
    A.moveFront();
    B.moveFront();
    S.clear();
    S.moveBack();
    //Adding the Lists into S
    while (A.position() < A.length()){
        ListElement dataA = A.moveNext();
        ListElement dataB = B.moveNext();
        S.insertBefore(dataA + sgn * dataB);
    }
}
// normalizeList()
// Performs carries from right to left (least to most significant
// digits), then returns the sign of the resulting integer. Used
// by add(), sub() and mult(). List should be positive.
int normalizeList(List& L){
    // First checks if List is not empty
    int sign = 0;
    if (L.length() == 0){
        return sign;
    }

    L.moveFront();

    // Removing all leading zeros from the list
    
    ListElement z = L.moveNext();
    while (z == 0 && L.position() < L.length()){
        L.eraseBefore();
        z = L.moveNext();
        
    }
    
    L.moveFront();
    if (L.length() == 0){
        return sign;
    }

    if (L.front() > 0){
        sign = 1;
    }
    if (L.front() < 0){
        negateList(L);
        sign = -1;
    }
    L.moveBack();
    

    ListElement carryout = 0;
    while (L.position() > 1){
        ListElement carryout = 0;
        ListElement data = L.movePrev();

        if (data >= base){
            carryout = data/base;
            data -= carryout*base;
        }

        if (data < 0){
            carryout = data/base - 1;
            data += (-1)*carryout*base;
        }        
 
        L.setAfter(data);
        ListElement nextData = L.peekPrev();
        L.setBefore(nextData + carryout);
    }
    carryout = 0;
    ListElement data = L.movePrev();
    if (data >= base){
        carryout = data/base;
        data -= carryout*base;
    }

    if (data < 0){
        carryout = data/base - 1;
        data += (-1)*carryout*base;
    }  
    L.setAfter(data);
    if (carryout != 0){
        L.insertAfter(carryout);
    }
    
    L.moveFront();
    return sign;
}
// shiftList()
// Prepends p zero digits to L, multiplying L by base^p. Used by mult(), after getting products and adding.
void shiftList(List& L, int p){
    // Then just going through the List of digits
    // Converts List first to string then adds specified number 0's to the end
    L.moveBack();
    for (int i = 0; i < p; i++){
        L.insertBefore(0);
    }
    L.moveFront();

}
// scalarMultList()
// Multiplies L (considered as a vector) by m. Used by mult().
void scalarMultList(List& L, ListElement m){
    L.moveFront();
    while (L.position() < L.length()){
        ListElement data = L.peekNext();
        L.setAfter(data*m);
        L.moveNext();
    }
    L.moveFront();
}

// BigInteger Arithmetic operations ----------------------------------------
BigInteger BigInteger::add(const BigInteger& N) const{
    List A = digits;
    int sigA = signum;
    int sigB = N.signum;
    List B = N.digits;
    A.moveFront(); 
    B.moveFront();
    // Making both lists the same size 
    if (A.length() != B.length()){
        if (A.length() > B.length()){
            while (A.length() != B.length()){
                B.insertBefore(0);
            }
        }
        if (A.length() < B.length()){
            while (A.length() != B.length()){
                A.insertBefore(0);
            }
        }
    }
    // Negating if needed before adding the contents of both lists
    if (sigA == -1){
        negateList(A);
    }
    if (sigB == -1){
        negateList(B);
    }
    
    A.moveFront();
    B.moveFront();
    // Getting sum of both Lists
    List S; 
    sumList(S, A, B, 1);

   // Creating BigInteger to return
    BigInteger I;
    I.signum = normalizeList(S);
    // After normalizing then set signum, list, then return
    
    I.digits = S;   
    return I;
}

BigInteger BigInteger::sub(const BigInteger& N) const{
    List A = digits;
    int sigA = signum;
    List B = N.digits;
    int sigB = N.signum;

    if (A.length() != B.length()){
       if (A.length() > B.length()){
            while (A.length() != B.length()){
                B.insertBefore(0);
            }
        }
        if (A.length() < B.length()){
            while (A.length() != B.length()){
                A.insertBefore(0);
            }
        } 
    }  
    if (sigA == -1){
        negateList(A);
    }
    if (sigB == -1){
        negateList(B);
    }
    List S;
    sumList(S, A, B, -1);

    BigInteger I;
    I.signum = normalizeList(S);
    I.digits = S;
    return I;
}

BigInteger BigInteger::mult(const BigInteger& N) const{
    // Original Lists, A is this and B is N
    List A = digits;
    int sigA= signum;

    List B = N.digits;
    int sigB = N.signum;
    
    if (sigA == -1){
        negateList(A);
    }
    if (sigB == -1){
        negateList(B);
    }
    
    B.moveBack();

    // Temperary Lists when adding during multiplication 
    List C = A; 

    // Big Integer to be returned
    BigInteger I;
    List R;
    int shift = 0;
    while (B.position() > 0){
        C = A;
        shiftList(C, shift);
        ListElement scal = B.movePrev();
        scalarMultList(C, scal);
        List T = R;  
        sumList(R, T, C, 1);
        shift += 1;
    }

    I.signum = normalizeList(R);
    I.digits = R;
    
    return I;
}


std::string BigInteger::to_string(){
    // Assigning signs based on signum

    std::string s = "";
    if (signum == -1){
        s += "-";
    }
    if (signum == 0){
        s = "0";
        return s;
    }
    // Then just going through the List of digits
    digits.moveFront();
    while (digits.position() < digits.length()){
        long data = digits.moveNext();
        string d = std::to_string(data);

        // Fills in zeros, when not at first eleemnt of List
        while ((int)d.length() < power && digits.position() != 1){
            d = '0' + d;
        }
        
        s += d;
    }
    digits.moveFront();
    
    return s;
}

// Overriden Operators -----------------------------------------------------
std::ostream& operator<<( std::ostream& stream, BigInteger N ){
    return stream << N.to_string();
}
bool operator==( const BigInteger& A, const BigInteger& B){
    if (A.compare(B) == 0){
        return true;
    }
    return false;
}
bool operator<( const BigInteger& A, const BigInteger& B){
    if (A.compare(B) == -1){
        return true;
    }
    return false;
}
bool operator<=( const BigInteger& A, const BigInteger& B){
    if (A.compare(B) == -1 || A.compare(B) == 0){
        return true;
    }
    return false;
}
bool operator>( const BigInteger& A, const BigInteger& B){
    if (A.compare(B) == 1){
        return true;
    }
    return false;
}
bool operator>=( const BigInteger& A, const BigInteger& B){
    if (A.compare(B) == 1 || A.compare(B) == 0){
        return true;
    }
    return false;
}
BigInteger operator+( const BigInteger& A, const BigInteger& B){
    BigInteger C = A.add(B);
    return C;
}
BigInteger operator+=(BigInteger& A, const BigInteger& B){
    A = A.add(B);
    return A;
}
BigInteger operator-( const BigInteger& A, const BigInteger& B){
    BigInteger C = A.sub(B); 
    return C;
}
BigInteger operator-=( BigInteger& A, const BigInteger& B){
    A = A.sub(B);
    return A;
}
BigInteger operator*( const BigInteger& A, const BigInteger& B){
    BigInteger C = A.mult(B);
    return C;
}
BigInteger operator*=( BigInteger& A, const BigInteger& B){
    A = A.mult(B);
    return A;
}