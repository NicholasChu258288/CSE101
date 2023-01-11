/********************************************************************************* 
* Nicholas Chu, nchu5
* 2022 Spring CSE101 PA5
* List.cpp
* Shuffles 
*********************************************************************************/

#include<iostream>
#include<string>
#include<iomanip>

#include"List.h"

using namespace std;

void shuffle(List& D){
    List deck1;
    List deck2;
    int size = D.length();
    int split = D.length() / 2;
    int data;
    
    D.moveFront();
    while (D.position() < split){
        data = D.moveNext();
        deck1.insertBefore(data);
    }

    while (D.position() < D.length()){
        data = D.moveNext();
        deck2.insertBefore(data);
    }

    deck1.moveFront();
    deck2.moveFront();

    D.clear();
    for (int i = 1; i < size+1; i++){
        if (i%2 == 0){
            int cursorData = deck1.moveNext();
            D.insertBefore(cursorData);
        } else {
            int cursorData = deck2.moveNext();
            D.insertBefore(cursorData);
        }
    }
    D.moveBack();
}

int main(int argc, char** argv){
    if (argc != 2){
        cout << "./Shuffle <int x>" << endl;
        return -1;
    }

    int maxDeckSize = atoi(argv[1]);

    if (maxDeckSize == 0){
        cout << "Use a deck size higher that 0." << endl;
        return -1;
    }
    
    cout << "deck size       shuffle count" << endl;
    cout << "------------------------------" << endl;
    List D; // Deck being shuffled
    List Og; // Original deck before shuffling
    for (int deckSize = 1; deckSize < maxDeckSize+1; deckSize++){
        for (int i = D.length(); i < deckSize; i++){
            D.insertBefore(i);
            Og.insertBefore(i);
        }

        shuffle(D);
        int shuffleCount = 1;
        
        while (!(D == Og)){
            shuffleCount += 1;
            shuffle(D);
        }

        cout << left << setw(15) << deckSize;
        cout << left << setw(15) << shuffleCount << endl; 
    }
    return 1;
}
