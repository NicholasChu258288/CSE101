/********************************************************************************* 
* Nicholas Chu, nchu5
* 2022 Spring CSE101 PA6
* List.cpp
* Contains the implementation of the List ADT.
*********************************************************************************/


#include<iostream> // Standard library
#include<string> // Enables usage of string datatype
#include<stdexcept> // Used for handling standard errors

#include "List.h" // List header

using namespace std;


// Class Constructors & Destructors ----------------------------------------

// Private Constructor
// Node constructor
List::Node::Node(ListElement x){
    data = x;
    next = nullptr;
    prev = nullptr;
}

// Class Constructors & Destructors for List
List::List(){
    frontDummy = nullptr;
    backDummy = nullptr;
    beforeCursor = nullptr;
    afterCursor = nullptr;
    pos_cursor = 0;
    num_elements = 0;
}

List::List(const List& L){
    frontDummy = nullptr;
    backDummy = nullptr;
    beforeCursor = nullptr;
    afterCursor = nullptr;
    pos_cursor = 0;
    num_elements = 0;
    
    Node *N = L.frontDummy;
    while (N != nullptr){
	    this->insertBefore(N->data);
	    N = N->next;
    }
   this->moveFront();
}

// Destructor
List::~List(){
    clear();
}


// Access functions --------------------------------------------------------

// Returns length (number of elements) of list
int List::length() const{
    return(num_elements);
}

// Returns data stored in first node of the linked list
ListElement List::front() const{
    if (length() <= 0){
        throw std::length_error("List: front(): empty list");
    }
    return(frontDummy->data);
}

// Returns data stored in last node of the linked list
ListElement List::back() const{
    if (length() <= 0){
        throw std::length_error("List: back(): empty list");
    }
    return(backDummy->data);
}

// Returns the position of the cursor
int List::position() const{
    return (pos_cursor);
}

ListElement List::peekNext() const{
    if (position() >= length()){
        throw std::range_error("List: peekNext(): cursor at back");
    }
    return(afterCursor->data);
}

ListElement List::peekPrev() const{
    if (position() <= 0){
        throw std::range_error("List: peekPrev(): cursor at front");
    }
    return(beforeCursor->data);
}

// Manipulation procedures -------------------------------------------------

void List::clear(){
    Node* N = frontDummy;
    Node *n = N;
    // Going through List and clearing all Nodes
    while (N != nullptr){
        n = N;
        N = N->next;
        delete n;
        num_elements -= 1;
    }

    // Resetting it list attributed back to default
    pos_cursor = 0;
    frontDummy = nullptr;
    backDummy = nullptr;
    beforeCursor = nullptr;
    afterCursor = nullptr;
}

void List::moveFront(){
    pos_cursor = 0;
    afterCursor = frontDummy;
    beforeCursor = frontDummy;
}

void List::moveBack(){
    pos_cursor = length();
    afterCursor = backDummy;
    beforeCursor = backDummy;
}

ListElement List::moveNext(){
    // Precondition
    if (position() >= length()){
        throw std::range_error("List: moveNext(): cursor at back");
    }
    // Incriments pos_cursor then adjusts the nodes that surround it
    Node *n = afterCursor;
    pos_cursor += 1;
    beforeCursor = n;
    if (pos_cursor == length()){
        afterCursor = backDummy;
    } else {
        afterCursor = n->next;
    }
    return n->data;
}

ListElement List::movePrev(){
    // Precondition
    if (position() <= 0){
        throw std::range_error("List: movePrev(): cursor at front");
    }

    Node *n = beforeCursor;
    pos_cursor -= 1;
    afterCursor = n;
    if (pos_cursor == 0){
        beforeCursor = frontDummy;
    } else {
        beforeCursor = n->prev;
    }
    
    return n->data;
}


void List::insertAfter(ListElement x){
    // New node to insert
    Node* n = new Node(x);
    n->next = afterCursor;
    n->prev = beforeCursor;

    // When inserting while cursor is at the front of the list
    if (position() == 0){
        frontDummy = n;
        frontDummy->prev = nullptr;
        beforeCursor = frontDummy;
        if (length() > 0){
            // When the List is empty
            afterCursor->prev = n;
        }
    }

    // When inserting while cursor is at the back of the list
    if (position() == length()){
        backDummy = n;
        backDummy->next = nullptr;
        if (length() > 0){
            beforeCursor->next = n;
        }
        
    }

    // When inserting between nodes
    if (position() > 0 && position() < length()){
        beforeCursor->next = n;
        afterCursor->prev = n;
    }
    // Just changes after cursor, since before cursor should not be affected
    afterCursor = n;
    num_elements += 1;
}

void List::insertBefore(ListElement x){
    // New node to insert
    Node *n = new Node(x);
    n->next = afterCursor;
    n->prev = beforeCursor;

    if (position() == 0){
        frontDummy = n;
        frontDummy->prev = nullptr;
        beforeCursor = frontDummy;
        if (length() > 0){
            afterCursor->prev = n;
        }
    }

    if (position() == length()){
        backDummy = n;
        backDummy->next = nullptr;
        if (length() > 0){
            beforeCursor->next = n;
        }
    }

    if (position() > 0 && position() < length()){
        beforeCursor->next = n;
        afterCursor->prev = n;
    }

    beforeCursor = n;

    // Since inserting before will change the number of elements and thus current cusor location
    pos_cursor += 1;
    num_elements += 1;
}


void List::setAfter(ListElement x){
    if (position() >= length()){
        throw std::range_error("List: setAfter(): cursor at back");
    }
    afterCursor->data = x;
}

void List::setBefore(ListElement x){
    if (position() <= 0){
        throw std::range_error("List: setBefore(): cursor at front");
    }
    beforeCursor->data = x;
}

void List::eraseAfter(){
    if (position() >= length()){
        throw std::range_error("List: eraseAfter(): cursor at back");
    }
    Node *n = afterCursor;
    afterCursor = afterCursor->next;

    if (position() == 0){
        frontDummy = afterCursor;
        if (frontDummy != nullptr){
            frontDummy->prev = nullptr;
        }
    }

    if (position() == length()-1){
      backDummy = beforeCursor;
      if (backDummy != nullptr){
        backDummy->next = nullptr; 
      }
    }

    if (position() > 0 && position() < length()-1){
        beforeCursor->next = afterCursor;
        afterCursor->prev = beforeCursor;
    }

    delete n;
    num_elements -= 1;
}

void List::eraseBefore(){
    if (position() <= 0){
        throw std::range_error("List: eraseBefore(): cursor at front");
    }

    Node *n = beforeCursor;
    beforeCursor = beforeCursor->prev;

    if (position() == 1){  
        frontDummy = afterCursor;
        if (frontDummy != nullptr){
            frontDummy->prev = nullptr;
        }
    }

    if (position() == length()){
        backDummy = beforeCursor;
        if (backDummy != nullptr){
            backDummy->next = nullptr;
        }
    }

    if (position() > 1 && position() < length()){
        beforeCursor->next = afterCursor;
        afterCursor->prev = beforeCursor;
    }

    delete n;
    num_elements -= 1;
    pos_cursor -= 1;
}

// Other Functions ---------------------------------------------------------

int List::findNext(ListElement x){

    //Goes through list to find matching
    while (position() < length()){
        if (moveNext() == x){
            return pos_cursor;
        }
    }
    
    // When nothing is found
    return -1;
}

int List::findPrev(ListElement x){

    while (position() > 0){
        ListElement data = movePrev();
        
        if (data == x){
            return position();
        }
    }
    return -1;

}

// Removes any extra reoeating elements.
void List::cleanup(){
    
    Node* N = frontDummy;
    Node* n = N;
    Node* t = n;
    int p = 1;

    int p2 = p;

    while (N != nullptr){
	    p++;
        p2 = p;
        ListElement data = N->data;
	    n = N->next;    
	    while (n != nullptr){
		    t = n->next;
		    if (n->data == data){
			    if (p2 <= position()){
				    pos_cursor -= 1;
                    
			    }
			    if (t != nullptr){
				    t->prev = n->prev;
			    }
				n->prev->next = t;
			    

			    delete n;
			    num_elements -= 1;
                p2--;
		    }
		    n = t;
            p2++;
	    }
	    N = N->next;
    }

    N = frontDummy;  
    int i = 1;
    afterCursor = nullptr;
    beforeCursor = nullptr;

    if (position() == 0){
        beforeCursor = N;
        afterCursor = N;
    }

    while (N != nullptr){
        if (position() == i){
            beforeCursor = N;
            afterCursor = N->next;
        }

        if (N->next == nullptr){
            backDummy = N;
        }

	    N = N->next;
	    i++;
    }
}

List List::concat(const List& L) const{   
    List C;
    Node* N = this->frontDummy;
    Node *M = L.frontDummy;

    while (N != nullptr){
        C.insertBefore(N->data);
        N = N->next;
    }

    while (M != nullptr){
        C.insertBefore(M->data);
        M = M->next;
    }
    C.moveFront();

    return C;

}

std::string List::to_string() const{
    
    Node* N = nullptr;
    std::string s = "(";

    for (N = frontDummy; N != nullptr; N = N->next){
        s += std::to_string(N->data);
        if (N->next != nullptr){
            s += ", ";
        }
    }

    s += ")";
    return s;
}

bool List::equals(const List& R) const{
    bool eq = false;
    Node* N = nullptr;
    Node* M = nullptr;

    eq = (this->num_elements == R.num_elements);
    N = this->frontDummy;
    M = R.frontDummy;
    while (eq && N!=nullptr){
        eq = (N->data == M->data);
        N = N->next;
        M = M->next;
    }

    return eq;
}

 // Overriden Operators -----------------------------------------------------
// Returns string representaation of List L
std::ostream& operator<<(std::ostream& stream, const List& L ){
    return stream << L.List::to_string();
}
// Returns true if Lists A and B are equal or else it returns false 
bool operator==( const List& A, const List& B ){
    return A.List::equals(B);
}

// Used for overwriteing state of List L, the returns a reference to
// this List
List& List::operator=( const List& L ){
    if ( this != &L){
        List tmp = L;

        std::swap(frontDummy, tmp.frontDummy);
        std::swap(backDummy, tmp.backDummy);
        std::swap(beforeCursor, tmp.beforeCursor);
        std::swap(afterCursor, tmp.afterCursor);
        std::swap(pos_cursor, tmp.pos_cursor);
        std::swap(num_elements, tmp.num_elements);
    }

    return *this;
}
