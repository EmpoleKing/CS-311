#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <algorithm>
#include <stdexcept>

template<class T>
class linkedList
{
    struct linkedListNode {
        T stringData;
        linkedListNode *nextPlace;
    };

    public: class sl_iterator
    {
        linkedListNode *nextPlace;
        public:
            sl_iterator(linkedListNode *p) : nextPlace(p) {}

            sl_iterator& operator++()
            {
                nextPlace = nextPlace -> nextPlace;
                return *this;
            }

            bool operator!=(const sl_iterator &other) const
            {
                return nextPlace != other.nextPlace;
            }

            T& operator*() const
            {
                return nextPlace -> stringData;
            }
    };

    linkedListNode *startingIndex = 0;

    public:
        linkedList()
        {
            std::cout << "Default constructor called\n";
        }

        void push(T new_item)
        {
            linkedListNode *new_node = new linkedListNode;
            new_node -> stringData = new_item;
            new_node -> nextPlace = startingIndex;
            startingIndex = new_node;
        }

        void insert(T new_item, size_t idx)
        {
            if(!idx)
            {
                push(new_item);
                return;
            }

            linkedListNode *spot = startingIndex;

            for(; idx - 1; idx--)
                spot = spot->nextPlace;

            linkedListNode *new_node = new linkedListNode;
            new_node->stringData = new_item;
            new_node->nextPlace = spot->nextPlace;
            spot->nextPlace = new_node;
        }

        // I just ripped reverseWordList straight out of my Project1.
        void reverseWordList()
        {
            // Initializing all of our necessary indexes
            linkedListNode *previousIndex = nullptr;
            linkedListNode *currentIndex = startingIndex;
            linkedListNode *nextIndex = nullptr;

            while (currentIndex != nullptr)
            {
                // Set nextIndex to temporary placeholder
                nextIndex = currentIndex -> nextPlace;

                // Sets previous index to be the linked currentIndex->nextPlace value instead
                currentIndex -> nextPlace = previousIndex;

                previousIndex = currentIndex;

                currentIndex = nextIndex;
            }

            // Final index of currentIndex gets set as our startingIndex index, so the reversal is complete
            startingIndex = previousIndex;
        }

        sl_iterator begin() const
        {
            return sl_iterator(startingIndex);
        }

        sl_iterator end() const
        {
            return sl_iterator(0);
        }

        // I modified this to not use pop, as I noticed that it took FOREVER to actually exit out of the program.
        // This goes through each list index to delete the nodes until we find a nullptr.
        ~linkedList()
        {
            std::cout << "Destructor was called\n";
            linkedListNode *current = startingIndex;
            while (current)
            {
                linkedListNode *toFree = current;
                current = current -> nextPlace;
                delete toFree;
            }
        }
};

template<class T>
void loadDictionary(linkedList<T>& dictionary, const std::string& fileName)
{
    std::ifstream file(fileName);
    std::string word;

    // If we can't open the file, throw an error.
    if (!file.is_open())
    {
        throw std::runtime_error("Error opening dictionary file: " + fileName);
        return;
    }

    while (file >> word)
    {
        dictionary.push(word);
    }

    // Reversing the dictionary. Didn't really see a change in the speed, so maybe my implementation is incorrect?
    dictionary.reverseWordList();

    file.close();
}

template<class T>
bool spellCheck(const linkedList<T>& dictionary, const std::string& wordToCheck)
{
    // Function removing punctuation from from the input string
    auto removePunctuation = [](std::string& str) {
        str.erase(std::remove_if(str.begin(), str.end(), ::ispunct), str.end());
    };

    // Convert wordToCheck to lowercase and remove punctuation
    std::string wordLower = wordToCheck;
    std::transform(wordLower.begin(), wordLower.end(), wordLower.begin(), ::tolower);
    removePunctuation(wordLower);

    // Iterates through the dictionary
    for (typename linkedList<T>::sl_iterator it = dictionary.begin(); it != dictionary.end(); ++it)
    {
        // Puts each dictionary word into lowercase and removes any punctuation found
        std::string dictionaryWord = *it;
        std::transform(dictionaryWord.begin(), dictionaryWord.end(), dictionaryWord.begin(), ::tolower);
        removePunctuation(dictionaryWord);

        // Check if the current word matches the word to check
        if (dictionaryWord == wordLower)
        {
            // If the word is found, return true
            return true;
        }
    }
    // If the word is not found, return false
    return false;
}

template<class T>
std::ostream& operator<<(std::ostream& out, linkedList<T> &list)
{
    out << "[";
    for(auto idx : list)
        out << idx << ", ";
    out << "\b\b]";
    return out;
}

using namespace std;
int main()
{
    // Variables we need for loading the dictionary and checking
    linkedList<string> dictionary;
    string wordInput;

    // If we fail to load the dictionary, throw an exception
    try
    {
        loadDictionary<string>(dictionary, "american-english.txt");
    }
    catch(const std::exception& e)
    {
        cerr << e.what() << '\n';
    }

    // Prompting the user to enter a word and assign that to wordInput
    cout << "Please enter a word to spellcheck: \n";
    cin >> wordInput;

    // The actual spell-checking, if spelled incorrectly, we provide a message to the user to tell them.
    if (spellCheck<string>(dictionary, wordInput))
    {
        cout << "Word correctly spelled, thanks.\n";
    }
    else
    {
        cout << "Incorrect word spelling detected.\n";
    }

    // One thing I did notice is that it takes forever for the code to actually exit

    return 0;
}

