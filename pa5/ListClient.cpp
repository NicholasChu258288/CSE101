/********************************************************************************* 
* Nicholas Chu, nchu5
* 2022 Spring CSE101 PA5
* ListClient.cpp
* Test Harness for List.cpp
*********************************************************************************/

#include<iostream>
#include<string>
#include<stdexcept>

#include"List.h"

using namespace std;

int main(){
    /*
    List A;

    // Code testing insert after
    A.insertAfter(1);
    A.insertAfter(5);
    A.insertAfter(6);
    A.moveFront();
    A.insertAfter(2);
    printf("Moving Next\n");
    A.moveNext();
    A.insertAfter(5);

    printf("Moved back and inserting\n");
    
    A.moveBack();
    A.insertAfter(7);
    
    printf("After inserting everyting:\n");
    printf("Before %d\n", A.peekPrev());
    printf("After: %d\n", A.peekNext());

    printf("Position: %d\n", A.position()); 
    printf("Length: %d\n", A.length());

    A.moveNext();
    printf("Now moving again\n");

    printf("Last: %d\n", A.position()); 
    printf("Length: %d\n", A.length());
    printf("Prev: %d\n", A.peekPrev());
    printf("Next: %d\n", A.peekNext());

    
    A.movePrev();
    A.insertAfter(16);
    
    A.movePrev();
    A.insertAfter(89);
    


    printf("Converting to string then printing\n");
    cout << "A = " << A << endl;
    */
    
    /*
    List B;

    // Code testing insert after
    B.insertBefore(1);
    cout << "B = " << B << endl;
    B.insertBefore(5);
    B.insertBefore(6);
    B.moveFront();
    B.insertBefore(2);
    printf("Moving Next\n");
    B.moveNext();
    B.insertBefore(5);
    cout << "B = " << B << endl;
    
    printf("Moved back and inserting\n");
    
    B.moveBack();
    B.insertBefore(7);
    
    printf("After inserting everyting:\n");
    printf("Before %d\n", B.peekPrev());
    

    printf("Position: %d\n", B.position()); 
    printf("Length: %d\n", B.length());

    
    printf("Now moving again\n");

    printf("Last: %d\n", B.position()); 
    printf("Length: %d\n", B.length());

    
    B.movePrev();
    B.insertBefore(16);
    
    B.movePrev();
    B.insertBefore(89);
    


    printf("Converting to string then printing\n");
    cout << "B = " << B << endl;
    

    B.moveBack();
    printf("moved to back\n");
    B.movePrev();
    printf("move again, now at node %d at position %d\n", B.peekNext(), B.position());
    
    B.eraseAfter();

    B.movePrev();
    B.movePrev();

    B.eraseAfter();

    B.moveFront();
    B.eraseAfter();

    printf("Erasin after\n");
    cout << "B = " << B << endl;
    
    printf("Finding 5: Position at when found %d\n", B.findNext(5));
    printf("Position: %d\n", B.position());

    printf("Cleared\n");

    B.clear();

    printf("Position: %d\n", B.position()); 
    printf("Length: %d\n", B.length());

    cout << "B = " << B << endl;

    printf("Inserting after\n");

    printf("Position: %d\n", B.position()); 
    printf("Length: %d\n", B.length());

    B.insertAfter(33);

    printf("Position: %d\n", B.position()); 
    printf("Length: %d\n", B.length());

    cout << "B = " << B << endl;

    printf("Now erasing before\n");

    B.moveNext();

    printf("Position: %d\n", B.position()); 
    printf("Length: %d\n", B.length());

   
    B.eraseBefore();

    printf("Finished delete\n");
    
    cout << "B = " << B << endl;

    B.insertAfter(6);
    B.moveFront();
    B.moveNext();
    B.insertBefore(2); 
    B.insertAfter(1);
    cout << "B = " << B << endl;
    B.insertBefore(5);
    B.insertAfter(89);
    B.back();
    B.insertBefore(888);
    cout << "B = " << B << endl;
    printf("Finding 888: Position at when found %d\n", B.findNext(888));
    printf("Position: %d\n", B.position());
    printf("Finding 889: Position at when found %d\n", B.findNext(889));
    printf("Position: %d\n", B.position());
    printf("Finding 1: Position at when found %d\n", B.findNext(1));
    printf("Position: %d\n", B.position());

    printf("Finding 6: Position at when found %d\n", B.findNext(6));
    printf("Position: %d\n", B.position());

    printf("You have reached the end\n");

    printf("Finding 6: Position wehn found was %d\n", B.findPrev(6));
    printf("Position %d\n", B.position());

    printf("Finding 888: Position wehn found was %d\n", B.findPrev(888));
    printf("Position %d\n", B.position());

    printf("Finding 1: Position wehn found was %d\n", B.findPrev(1));
    printf("Position %d\n", B.position());
    cout << "B = " << B << endl;
    */
   /*
   int i, n=10;
   List A, B, C, D;

   for(i=1; i<=n; i++){
      A.insertAfter(i);
      B.insertAfter(11-i);
      C.insertBefore(i);
      D.insertBefore(11-i);
   }

   cout << endl;
   cout << "A = " << A << endl;
   cout << "A.position() = " << A.position() << endl;
   cout << "B = " << B << endl;
   cout << "B.position() = " << B.position() << endl;
   cout << "C = " << C << endl;
   cout << "C.position() = " << C.position() << endl;
   cout << "D = " << D << endl;
   cout << "D.position() = " << D.position() << endl;
   cout << endl;

   A.moveBack();
   B.moveBack();
   C.moveFront();
   D.moveFront();

   cout << "A = " << A << endl;
   cout << "A.position() = " << A.position() << endl;
   cout << "B = " << B << endl;
   cout << "B.position() = " << B.position() << endl;
   cout << "C = " << C << endl;
   cout << "C.position() = " << C.position() << endl;
   cout << "D = " << D << endl;
   cout << "D.position() = " << D.position() << endl;

   cout << endl << "B: ";
   for(i=1; i<=7; i++){
      cout << B.movePrev() << " ";
   }
   cout << endl << "B.position() = " << B.position() << endl;
   
   cout << endl << "C: ";
   for(i=1; i<=7; i++){
      cout << C.moveNext() << " ";
   }
   cout << endl << "C.position() = " << C.position() << endl;

   cout << endl;
   cout << "A==B is " << (A==B?"true":"false") << endl;
   cout << "B==C is " << (B==C?"true":"false") << endl;
   cout << "C==D is " << (C==D?"true":"false") << endl;
   cout << "D==A is " << (D==A?"true":"false") << endl;
   cout << endl;

   cout << B.findNext(5) << endl;
   cout << B << endl;
   B.eraseBefore();
   B.eraseAfter();
   cout << B << endl;
   cout << B.position() << endl;
   cout << B.findPrev(2) << endl;
   B.eraseBefore();
   B.eraseAfter();
   cout << B << endl;
   cout << B.position() << endl; 
   cout << B.findNext(20) << endl; 
   cout << B.position() << endl;
   cout << B.findPrev(20) << endl;
   cout << B.position() << endl;
   cout << endl;

   for( i=10; i>=1; i--){
      A.insertAfter(i);
      A.movePrev();
   }
   cout << "A = " << A << endl;
   for( i=1; i<=15; i++){
      A.moveNext();
   }
   cout << A.position() << endl;
   
   A.cleanup();

   cout << "A = " << A << endl;
   cout << A.position() << endl;

   cout << endl;
   List E = A;
   cout << "E==A is " << (E==A?"true":"false") << endl;

   cout << endl;

   List F = A.concat(B);
   cout << "F = " << F << endl;
   cout << "length: " << F.length() << endl;
   cout << "front: " << F.front() << endl;
   cout << "back: " << F.back() << endl;
   cout << "position:  " << F.position() << endl;
   for( i=1; i<=7; i++){
      cout << "peekNext: " << F.peekNext() << endl;
      F.insertBefore(-i);
      cout << F.moveNext() << endl; 
   }
   cout << "F = " << F << endl;

   cout << endl;

   cout << "test exceptions: " << endl;
   cout << "A = " << A << endl;
   A.moveFront();
   try{
      A.peekPrev();
   }catch( std::range_error& e ){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   try{
      A.movePrev();
   }catch( std::range_error& e ){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   try{
      A.setBefore(5);
   }catch( std::range_error& e ){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   try{
      A.eraseBefore();
   }catch( std::range_error& e ){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   A.moveBack();
   try{
      A.peekNext();
   }catch( std::range_error& e ){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   try{
      A.moveNext();
   }catch( std::range_error& e ){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   try{
      A.setAfter(5);
   }catch( std::range_error& e ){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   try{
      A.eraseAfter();
   }catch( std::range_error& e ){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   A.clear();
   try{
      A.front();
   }catch( std::length_error& e ){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   try{
      A.back();
   }catch( std::length_error& e ){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }

   cout << endl;
   */
   /*
   List A;
   List B;
   A.insertBefore(1);
    A.insertBefore(2);
    A.insertBefore(2);
    A.insertBefore(1);
    A.insertBefore(2);
    A.insertBefore(3);
    A.insertBefore(1);
    A.findPrev(3);
    cout << "A = " << A << endl;
    cout << A.position() << endl;
    cout << A.peekPrev() << "    " << A.peekNext() << endl;
    A.cleanup();
    printf("got out of cleanup\n");
    cout << "A after cleanup = " << A << endl;
    cout << A.position() << endl;
    if (A.position() != 2)
      printf("Fails test 1\n");
   

    B.insertBefore(1);
    B.insertBefore(2);
    B.insertBefore(2);
    B.insertBefore(1);
    B.insertBefore(2);
    B.insertBefore(3);
    B.insertBefore(1);
    B.findPrev(3);
    cout << "B = " << B << endl;
    B.movePrev();
    cout << B.position() << endl;
    cout << B.peekPrev() << "    " << B.peekNext() << endl;
    B.cleanup();
    cout << "B = " << B << endl;
    cout << B.position() << endl;
    if (B.position() != 2)
      printf("Fails test 2\n");
   */

   // MoveNext_value : issue might be in erase
   /*
   List A;
   A.insertAfter(77);
    A.insertAfter(55);
    A.insertAfter(1);
    A.insertAfter(34);
    A.insertAfter(1);
    A.insertAfter(77);
    A.insertAfter(77);
    A.insertAfter(34);
    cout << "A = " << A << endl;
    cout << A.position() << endl;
    if (A.findNext(99) != -1)
      return 1;
    if (A.position() != A.length())
      return 2;

    A.moveFront();
    if (A.findNext(1) != 4)
      return 3;
    if (A.findNext(1) != 6)
      return 4;
    if (A.findNext(1) != -1)
      return 5;

    A.moveFront();
    A.cleanup();
    if (A.findNext(1) != 3)
      return 6;
    if (A.findNext(1) != -1)
      return 7;
 `*/ 
   /*
   List A;
   A.insertAfter(77);
    A.insertAfter(55);
    A.insertAfter(1);
    A.insertAfter(34);
    A.insertAfter(1);
    A.insertAfter(77);
    A.insertAfter(77);
    A.insertAfter(34);
    cout << "A = " << A << endl;
    cout << A.position() << endl;
    //cout << A.peekPrev() << "    " << A.peekNext() << endl;
    if (A.findNext(99) != -1)
      printf("Failed test 1\n");
    printf("Passed Test 1\n");
    if (A.position() != A.length())
      printf("Failed test 2\n");
   printf("Passed Test 2\n");

    A.moveFront();
    if (A.findNext(1) != 4)
      printf("Failed test 3\n");
   printf("Passed Test 3\n");
    if (A.findNext(1) != 6)
      printf("Failed test 4\n");
   printf("Passed Test 4\n");
    if (A.findNext(1) != -1)
      printf("Failed test 5\n");
   printf("Passed Test 5\n");

    A.moveFront();
    cout << "A = " << A << endl;
    A.cleanup();
    cout << "A = " << A << endl;
    cout << A.position() << endl;
    cout << A.front() << endl;
    //cout << "Looking next" << A.peekNext() << endl;
    if (A.findNext(1) != 3)
      printf("Failed test 6\n");
    printf("Passed Test 6\n");
    if (A.findNext(1) != -1)
      printf("Failed test 5\n");
    printf("Passed Test 5\n");
    */
    List A;
    A.insertBefore(34);
    A.insertBefore(77);
    A.insertBefore(77);
    A.insertBefore(1);
    A.insertBefore(34);
    A.insertBefore(1);
    A.insertBefore(55);
    A.insertBefore(77);
    if (A.findPrev(99) != -1)
      printf("Failed test 1\n");
    printf("Passed Test 1\n");
    if (A.position() != 0)
      printf("Failed test 2\n");
    printf("Passed Test 2\n");

    A.moveBack();
    if (A.findPrev(1) != 5)
      printf("Failed test 3\n");
    printf("Passed Test 3\n");
    if (A.findPrev(1) != 3)
      printf("Failed test 4\n");
    printf("Passed Test 4\n");
    if (A.findPrev(1) != -1)
      printf("Failed test 5\n");
    printf("Passed Test 5\n");

    A.moveBack();
    cout << "A = " << A << endl;
    cout << A.position() << endl;
    A.cleanup();
    cout << "A = " << A << endl;
    cout << A.position() << endl;

    cout << A.back() << endl;
    cout << A.peekPrev() << endl;
    
    if (A.findPrev(1) != 2)
      printf("Failed test 6\n");
    printf("Passed Test 6\n");
    if (A.findPrev(1) != -1)
      printf("Failed test 7\n");
    printf("Passed Test 7\n");

   return( EXIT_SUCCESS );
}