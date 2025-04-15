#include<iostream>
#include<string>

#include "compact_queue.h"

using namespace std;

int main()
{
    compact_queue<string> test_queue(6);
    test_queue.enqueue("Pullman");
    test_queue.enqueue("Othello");
    test_queue.enqueue("Vantage");
    test_queue.enqueue("Ellensburg");
    test_queue.enqueue("Seattle");

    test_queue.enqueue("Olympia");
    test_queue.enqueue("Centralia");
    test_queue.enqueue("Vancouver");
    test_queue.enqueue("Portland");
    test_queue.enqueue("Salem");

    test_queue.printQueue(cout);
}