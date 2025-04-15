#ifndef WORDLIST_H
#define WORDLIST_H

#include<iostream>
using namespace std;

struct WordListNode {
    string data;
    WordListNode *next;
};

class WordList {
    WordListNode *start = 0;
public:
    WordListNode* getStart(){
        return start;
    }
    void add(string w){ // Will add in alphabetic order
        if(!start){ // could also be if(start != NULL)
            start = new WordListNode;
            start->data = w; // -> because start is a WordListNode*.  If it was a WordListNode, we'd use . instead
            // start->data is the same as (*start).data
            start->next = 0; // Could also say start->next = NULL;
            return;
        }
        WordListNode *place = start, *last = 0;
        while(place && place->data < w){
            last = place;
            place = place->next;
        }
        WordListNode *new_one = new WordListNode;
        new_one->data = w;
//      WordListNode new_one; // Don't do this!  It'll make a new WordListNode in the stack frame for this method call!
        new_one->next = place;
        if(last)
            last->next = new_one;
        else
            start = new_one;
    }
    void print(){
        WordListNode *place = start;
        cout << "[";
        while(place){
            cout << place->data << ", ";
            place = place->next;
        }
        cout << "\b\b]\n";
    }
    ~WordList(){
        WordListNode *place = start, *last;
        while(place){
            last = place;
            place = place->next;
            delete last;
        }
    }
    string operator[](size_t index) {
        WordListNode *place = start;
        while(index-- && place->next) // Returns the last item if there are less than index items
            place = place->next;
        return place->data;
    }
    operator string() {
        WordListNode *place = start;
        string retval = "";
        retval += "[";
        while(place){
            retval +=  place->data + ", ";
            place = place->next;
        }
        retval +=  "\b\b]";
        return retval;
    }
    WordListNode* find(string toFind){
        WordListNode* place = start;
        while(place){
            if(place->data == toFind)
                return place;
            place = place->next;
        }
        return 0;
    }
};

ostream& operator << (ostream& out, WordList& wl){
    return out << (string)wl;
}

#endif