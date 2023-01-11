/********************************************************************************* 
* Nicholas Chu, nchu5
* 2022 Spring CSE101 PA7
* Dictionary.cpp
* Contains the implementation of the Dictionary ADT.
*********************************************************************************/

#include<iostream> // Standard library
#include<string> // Enables usage of string datatype
#include<stdexcept> // Used for handling standard errors
#include<ctype.h>
#include<math.h>

#include "Dictionary.h" // List header

using namespace std;

//Constructors
Dictionary::Node::Node(keyType k, valType v){
    key = k;
    val = v;
    parent = nullptr;
    left = nullptr;
    right = nullptr;
}


// Helper Functions (Optional) ---------------------------------------------

// inOrderString()
// Appends a string representation of the tree rooted at R to string s. The
// string appended consists of: "key : value \n" for each key-value pair in
// tree R, arranged in order by keys.
void Dictionary::inOrderString(std::string& s, Node* R) const{
    if (R != nil && R != nullptr){
        inOrderString(s, R->left);
        string entry = R->key + " : " + std::to_string(R->val) + "\n";
        s += entry;
        inOrderString(s, R->right); 
    }
}

// preOrderString()
// Appends a string representation of the tree rooted at R to s. The appended
// string consists of keys only, separated by "\n", with the order determined
// by a pre-order tree walk.
void Dictionary::preOrderString(std::string& s, Node* R) const{
    if (R != nil && R != nullptr){
        s += R->key + "\n";
        
        preOrderString(s, R->left);
        preOrderString(s, R->right); 
    }
}

// preOrderCopy()
// Recursively inserts a deep copy of the subtree rooted at R into this 
// Dictionary. Recursion terminates at N.
void Dictionary::preOrderCopy(Node* R, Node* N){

    if (R != N && R != nullptr){
       setValue(R->key, R->val);
       preOrderCopy(R->left, N);
       preOrderCopy(R->right, N);
    }
    
}

// postOrderDelete()
// Deletes all Nodes in the subtree rooted at R, sets R to nil.
void Dictionary::postOrderDelete(Node* R){
    if (R != nil && R != nullptr){
        postOrderDelete(R->left);
        postOrderDelete(R->right);
        delete R;
        num_pairs -= 1;
        //R = nil;
    }
}

// search()
// Searches the subtree rooted at R for a Node with key==k. Returns
// the address of the Node if it exists, returns nil otherwise.
Dictionary::Node* Dictionary::search(Node* R, keyType k) const{
    if (R == nil || R == nullptr || R->key == k){
        return R;
    } else if (k < R->key){
        return search(R->left, k);
    } else {
        return search(R->right, k);
    }
}

// findMin()
// If the subtree rooted at R is not empty, returns a pointer to the 
// leftmost Node in that subtree, otherwise returns nil.
Dictionary::Node* Dictionary::findMin(Node* R){
    if (R == nil || R == nullptr){
        return nil;
    }
    
    while (R->left != nil && R->left != nullptr){   
        R = R->left;
    }

    return R;
}

// findMax()
// If the subtree rooted at R is not empty, returns a pointer to the 
// rightmost Node in that subtree, otherwise returns nil.
Dictionary::Node* Dictionary::findMax(Node* R){
    // The extra checks like R->key == "\0" is just to check if it is not nil
    // and should be changed dpeening on what the keyType is changed to
    // what nil is planned on being set to
    // This was done just because I needed to a get around nil new
    // nil pointers when using copy

    if (R == nil || R == nullptr){
        return nil;
    }
    while (R->right != nil && R->right != nullptr){
        R = R->right;
    }
    return R;
}

// findNext()
// If N does not point to the rightmost Node, returns a pointer to the
// Node after N in an in-order tree walk.  If N points to the rightmost 
// Node, or is nil, returns nil. 
Dictionary::Node* Dictionary::findNext(Node* N){
    if (N->right != nil && N->right != nullptr){
        return findMin(N->right);
    }
    Node* p = N->parent;
    while ((p != nil && p != nullptr) && N == p->right){
        N = p;
        p = p->parent;
    }
    return p;
}

// findPrev()
// If N does not point to the leftmost Node, returns a pointer to the
// Node before N in an in-order tree walk.  If N points to the leftmost 
// Node, or is nil, returns nil.
Dictionary::Node* Dictionary::findPrev(Node* N){
    if (N->left != nil && N->left != nullptr){
        return findMax(N->left);
    }
    Node* p = N->parent;
    while ((p != nil && p != nullptr) && N == p->left){
        N = p;
        p = p->parent;
    }
    return p;
}

// Used to transplant nodes in remove
void Dictionary::transplant(Node *u, Node *v){
    if (u->parent == nil || u->parent == nullptr){
        root = v;
    } else if (u == u->parent->left){
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }
    if (v != nil || v != nullptr){
        v->parent = u->parent;
    }
}

// Class Constructors & Destructors ----------------------------------------
   
// Creates new Dictionary in the empty state. 
Dictionary::Dictionary(){
    nil = new Node("\0", -1); //nil is the sentinel node and is just set with arbitrary values
    root = nullptr;
    current = nullptr;
    num_pairs = 0;
}

// Copy constructor.
Dictionary::Dictionary(const Dictionary& D){
    //Copies over some of the starting stuff
    nil = new Node("\0", -1);
    nil->parent = nil;
    nil->right = nil;
    nil->left = nil;
    root = nil;
    num_pairs = 0;
    
    //Now preorder copies the rest of the dictionary
    preOrderCopy(D.root, D.nil);
    current = nil;
}

// Destructor
Dictionary::~Dictionary(){
    clear();
    delete nil;
}

// Access functions --------------------------------------------------------

// size()
// Returns the size of this Dictionary.
int Dictionary::size() const{
    return num_pairs;
}

// contains()
// Returns true if there exists a pair such that key==k, and returns false
// otherwise.
bool Dictionary::contains(keyType k) const{
    Node* N = root;
    // Checking iteratively, not using current to keep track
    // or having node to track in parameter
    while ((N != nil && N != nullptr) && k != N->key){
        if (k < N->key){
            N = N->left;
        } else {
            N = N->right;
        }
    }
    // Checks to see if final Node is not null and has the same key
    if (N != nil && N != nullptr){
        if (N->key == k){
            return true;
        }
    }
    return false;
}

// getValue()
// Returns a reference to the value corresponding to key k.
// Pre: contains(k)
valType& Dictionary::getValue(keyType k) const{
    if (contains(k) == false){
        string s = "Dictionary: getValue(): key \"" + k + "\"does not exist";
        throw std::logic_error(s);
    }
    Node *N = root;
    // Another iteratiive loop but this time just returning 
    while ((N != nil && N != nullptr) && k != N->key){
        if (k < N->key){
            N = N->left;
        } else {
            N = N->right;
        }
    }
    return N->val;
}

// hasCurrent()
// Returns true if the current iterator is defined, and returns false 
// otherwise.
bool Dictionary::hasCurrent() const{
    if (current != nullptr && current != nil){
        return true;
    }
    return false;
}

// currentKey()
// Returns the current key.
// Pre: hasCurrent() 
keyType Dictionary::currentKey() const{
    if (hasCurrent() != true){
        throw std::logic_error("Dictionary: currentKey(): current undefined");
    }
    return current->key;
}

// currentVal()
// Returns a reference to the current value.
// Pre: hasCurrent()
valType& Dictionary::currentVal() const{
    if (hasCurrent() != true){
        throw std::logic_error("Dictionary: currentKey(): current undefined");
    }
    return current->val;
}


// Manipulation procedures -------------------------------------------------

// clear()
// Resets this Dictionary to the empty state, containing no pairs.
void Dictionary::clear(){
    // Using post order traversal and deleting the nodes
    postOrderDelete(root);
    root = nil;
    current = nil;
    num_pairs = 0;
}

// setValue()
// If a pair with key==k exists, overwrites the corresponding value with v, 
// otherwise inserts the new pair (k, v).
void Dictionary::setValue(keyType k, valType v){   
    Node* y = nil;
    Node* x = root;
    // Going through the tree until the spot to insert is found
    while (x != nil && x != nullptr){
        y = x;
        if (k < x->key){
            x = x->left;
        } else if (k > x->key){
            x = x->right;
        } else if (k == x->key){
            x->val = v;       
            return;
        }
    }

    // Creating new node and inserting it    
    Node* N = new Node(k, v);
    N->left = nil;
    N->right = nil;
    N->parent = y;
    if (y == nil || y == nullptr){
        root = N;
    } else if (k < y->key){
        y->left = N;
    } else {       
        y->right = N;
    }
    num_pairs += 1;
}

// remove()
// Deletes the pair for which key==k. If that pair is current, then current
// becomes undefined.
// Pre: contains(k).
void Dictionary::remove(keyType k){
    // Precondition
    if (contains(k) == false){
        string s = "Dictionary: getValue(): key \"" + k + "\"does not exist";
        throw std::logic_error(s);
    }
    // If the key matches the current then just set current to nil/undefined
    // Also sets N, which is what will be deleted

    Node* N = nil;
    if (current->key == k){
        N = current;
        current = nil;
    } else {
        N = search(root, k);
    }

    // Actual deletion
    if (N->left == nil || N->left == nullptr){
        transplant(N, N->right);
        delete N;
        num_pairs -= 1;
    } else if (N->right == nullptr || N->right == nil){
        transplant(N, N->left);
        delete N;
        num_pairs -= 1;
    } else {
        Node* min = findMin(N->right);
        if (min->parent != N){
            transplant(min, min->right);
            min->right = N->right;
            min->right->parent = min;
        }

        // Tansplant N and min
        transplant(N, min);
        min->left = N->left;
        min->left->parent = min;
        delete N;
        num_pairs -= 1;       
    }

}

// begin()
// If non-empty, places current iterator at the first (key, value) pair
// (as defined by the order operator < on keys), otherwise does nothing. 
void Dictionary::begin(){
    if (num_pairs > 0){
        current = findMin(root);
    }
}

// end()
// If non-empty, places current iterator at the last (key, value) pair
// (as defined by the order operator < on keys), otherwise does nothing. 
void Dictionary::end(){
    if (num_pairs > 0){
        current = findMax(root);
    }
}

// next()
// If the current iterator is not at the last pair, advances current 
// to the next pair (as defined by the order operator < on keys). If 
// the current iterator is at the last pair, makes current undefined.
// Pre: hasCurrent()
void Dictionary::next(){
    // FIX ME LATER
    if (hasCurrent() == true){
        current = findNext(current);
    }
    
}

// prev()
// If the current iterator is not at the first pair, moves current to  
// the previous pair (as defined by the order operator < on keys). If 
// the current iterator is at the first pair, makes current undefined.
// Pre: hasCurrent()
void Dictionary::prev(){
    if (hasCurrent() == true){
        current = findPrev(current);
    }
}

// Other Functions ---------------------------------------------------------

// to_string()
// Returns a string representation of this Dictionary. Consecutive (key, value)
// pairs are separated by a newline "\n" character, and the items key and value 
// are separated by the sequence space-colon-space " : ". The pairs are arranged 
// in order, as defined by the order operator <.
std::string Dictionary::to_string() const{
    string s = "";
    inOrderString(s, root);
    return s;
}

// pre_string()
// Returns a string consisting of all keys in this Dictionary. Consecutive
// keys are separated by newline "\n" characters. The key order is given
// by a pre-order tree walk.
std::string Dictionary::pre_string() const{
    string s = "";
    preOrderString(s, root);
    return s;
}

// equals()
// Returns true if and only if this Dictionary contains the same (key, value)
// pairs as Dictionary D.
bool Dictionary::equals(const Dictionary& D) const{

    if ( num_pairs != D.num_pairs){
        
        //cout << "Not the smae numnber of pairs" << endl;
        
        return false;
    }
    string s1 = this->to_string();
    string s2 = D.to_string();


    //cout << "s1: "   << endl << s1 << endl;
    //cout << "s2: " << endl << s2 << endl;

    if (s1.compare(s2) == 0){
        return true;
    } else {
        return false;
    }
}


// Overloaded Operators ----------------------------------------------------
   
// operator<<()
// Inserts string representation of Dictionary D into stream, as defined by
// member function to_string().
std::ostream& operator<<( std::ostream& stream, Dictionary& D ){
    return stream << D.to_string();
}

// operator==()
// Returns true if and only if Dictionary A equals Dictionary B, as defined
// by member function equals(). 
bool operator==( const Dictionary& A, const Dictionary& B ){
    if (A.equals(B) == true){
        return true;
    }
    return false;
}

// operator=()
// Overwrites the state of this Dictionary with state of D, and returns a
// reference to this Dictionary.
Dictionary& Dictionary::operator=( const Dictionary& D ){
    if (this != &D){
        Dictionary T = D;
        
        std::swap(nil, T.nil);
        std::swap(root, T.root); 
        std::swap(current, T.current); 
        std::swap(num_pairs, T.num_pairs);
    }
    return *this;
}
