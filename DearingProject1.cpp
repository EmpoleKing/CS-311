/* Starting code for CS311 Project 1:  Linked Lists
 * This will be explained in more detail in class on September 2
 * The WordList class stores words, as many of them as the user would like.
 * Due Monday, February 12
 */
#include<iostream>
using namespace std;

struct ListNode
{
    string inputString;
    ListNode* stringIndex;
};

class WordList
{
        ListNode *startingIndex = 0;
public:
        void add(string stringValue)
        {
            ListNode *toAdd = new ListNode;
            toAdd -> inputString = stringValue;
            toAdd -> stringIndex = 0;

            if(contains(stringValue))
                return;

            if(!startingIndex)
            {
                startingIndex = toAdd;
                return;
            }

            ListNode *place = startingIndex;
            ListNode *last = 0;

            while(place && place->inputString < toAdd->inputString)
            {
                last = place;
                place = place -> stringIndex;
            }

            if(last)
                last -> stringIndex = toAdd;

            if(!last)
                startingIndex = toAdd;

            toAdd -> stringIndex = place;
        }

        void removeWord(string stringValue)
        {
            // Initialize our current index as the starting index, and
            // previousIndex as a null pointer value for better memory usage.
            ListNode *currentIndex = startingIndex;
            ListNode *previousIndex = nullptr;

            while (currentIndex != nullptr)
            {
                if (currentIndex -> inputString == stringValue)
                {
                    if (previousIndex)
                    {
                        previousIndex -> stringIndex = currentIndex -> stringIndex;
                    }
                    else
                    {
                        startingIndex = currentIndex -> stringIndex;
                    }

                    delete currentIndex;
                    return;
                }

                previousIndex = currentIndex;
                currentIndex = currentIndex -> stringIndex;
            }
        }

        void print()
        {
            ListNode *currentIndex = startingIndex;
            cout << "[";
            while(currentIndex)
            {
                cout << currentIndex -> inputString << ", ";
                currentIndex = currentIndex -> stringIndex;
            }
            cout << "\b\b]\n";
        }

        void reverseWordList()
        {
            // Initializing all of our necessary indexes
            ListNode *previousIndex = nullptr;
            ListNode *currentIndex = startingIndex;
            ListNode *stringIndex = nullptr;

            while (currentIndex != nullptr)
            {
                // Set stringIndex to temporary placeholder
                stringIndex = currentIndex -> stringIndex;

                // Sets previous index to be the linked currentIndex -> stringIndex value instead
                currentIndex -> stringIndex = previousIndex;

                previousIndex = currentIndex;

                currentIndex = stringIndex;
            }

            // Final index of currentIndex gets set as our starting index, so the reversal is complete
            startingIndex = previousIndex;
        }

        bool contains (string stringValue)
        {
            // Initializing starting index as our current one
            ListNode *currentIndex = startingIndex;
            while(currentIndex)
            {
                // if our input string for the add() function matches the inputString of our currentIndex,
                // return true so we don't add the stringValue
                if (currentIndex -> inputString == stringValue)
                {
                    return true;
                }

                currentIndex = currentIndex -> stringIndex;
            }
            return false;
        }

        int findWordIndex (string stringValue)
        {
            int wordIndex = 0;

            ListNode *currentIndex = startingIndex;

            while (currentIndex)
            {
                if (currentIndex -> inputString == stringValue)
                {
                    cout << stringValue << " is located at index " << wordIndex << endl;
                    return wordIndex;
                }
                currentIndex = currentIndex -> stringIndex;
                wordIndex++;
            }
            return -1;
        }

        int findLength()
        {
            int index = 0;
            // Initializing starting index as our current one
            ListNode *currentIndex = startingIndex;

            // Incrementing our index so we iterate through the list to get our length
            while (currentIndex)
            {
                index++;
                currentIndex = currentIndex -> stringIndex;
            }

            return index;
        };

        ~WordList()
        {
            ListNode *currentIndex = startingIndex, *stringIndex;
            while(currentIndex)
            {
                stringIndex = currentIndex->stringIndex;
                delete currentIndex;
                currentIndex = stringIndex;
            }
        }
};

int main(){
    WordList names;

    names.add("Gandalf");
    names.add("Frodo");
    names.add("Sam");
    names.add("Aragorn");
    names.add("Boromir");
    names.add("Pippin");
    names.add("Gimli");
    names.add("Legolas");
    names.add("Merry");

    names.print();

    names.add("Merry");

    // Print a second time to verify that Merry was not added to the list a second time
    names.print();

    names.removeWord("Legolas");

    int length = names.findLength();

    cout << "Length of list is: " << length << endl;

    // Outputting word index of specific name
    names.findWordIndex("Gimli");

    names.reverseWordList();

    // Printing to make sure it reverses correctly
    names.print();

}

/*
    Noticed a consistency issue with my syntax, fixed and re-submitted.
*/

/*
 * Starting with the code above add these features (20% of grade each).  Add test code for each, to make sure they work.
 *  1.  If a word is already in the list, don't add a second copy of it
 *  2.  Add a remove method, which takes a word and removes it from the list.  Don't leak memory!
 *  3.  Add a length method, which returns the length of the list
 *  4.  Add a find method, which finds the index of an item, and returns -1 if it is not in the list.  Remember to put in test code for both cases.
 *  5.  Add a reverse method, which will reverse the order of the list.  Once the list is reversed, it should stay reversed even when new words are added.  Keep a private boolean property called "reversed" which will track whether the list is currently reversed or not, and modify the add method so that it uses this property to figure out where to put new inputString.
 *
 *  Test code here can be either interactive or not, but compiling and running the program should provide a convincing demonstration that your linked list ADT works.  Keep all inputString members private in the WordList class.
 */