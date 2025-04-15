#include<iostream>
#include "compacted_linkedlist.h"
using namespace std;

int main(){
    compacted_list<int> intlist;
    for(int i = 0; i < 205; i++)
        intlist.push(i);
    cout << intlist << endl;

    cout << "The 10th item is:  " << intlist[9] << endl;
    // cout << "The 10th item is:  " << intlist[999] << endl; // This will segfault
    for(int i = 0; i < 10; i++)
        cout << intlist.pop() << endl;

    intlist.enqueue(500);
    intlist.enqueue(501);
    intlist.enqueue(502);
    cout << intlist << endl;

    return 0;
}