#ifndef COMPACTED_LINKEDLIST_H
#define COMPACTED_LINKEDLIST_H

#include<iostream>

template<class T>
class compacted_list {
    struct ll_node {
        T contents[100];
        ll_node *next;
        unsigned start, end;
    };

    class sl_iterator {
        ll_node *place;
        unsigned place_idx;
    public:
        sl_iterator(ll_node *p, unsigned startpoint) : place(p), place_idx(startpoint) {}
        sl_iterator& operator++(){
            place_idx++;
            if(place_idx >= place->end){
                place = place->next;
                if(place)
                    place_idx = place->start;
                else
                    place_idx = 0;
            }
            return *this;
        }
        bool operator!=(const sl_iterator &other) const {
            return place != other.place || place_idx != other.place_idx;
        }
        T& operator*(){
            return place->contents[place_idx];
        }
    };

    ll_node *start = 0, *last = 0; // The end points to the last item
public:
    compacted_list() {
        std::cout << "default constructor called\n";
    }
/*
    list(list &other){
        std::cout << "copy constructor called\n";
        size_t pos = 0;
        for(auto i : other)
            insert(i, pos++);
    }
*/
    void push(T new_item){ //  O(1)
        // We know we have to add a new node
        if(!start || start->start == 0){
            ll_node *new_node = new ll_node;
            // Since we're putting this at the front, start data at the back of this new node
            new_node->start = 100;
            new_node->end = 100;
            new_node->contents[--new_node->start] = new_item;
            new_node->next = start;
            if(start == 0)
                last = new_node;
            start = new_node;
        } else { // we can just put it in the existing head node
            start->contents[--start->start] = new_item;
        }
    }
    bool empty(){
        return start == 0;
    }
    T pop(){ // O(1)
        T result = start->contents[start->start];
        start->start++;
        if(start->start == start->end){
            ll_node *tofree = start;
            start = start->next;
            delete tofree;
            // Was that the last item?  Might need to adjust the end pointer
            if(!start)
                last = 0;
        }
        return result;
    }
    void enqueue(T new_item){ // O(1)
        if(!last){ // There's nothing in the list!
            push(new_item);
            return;
        }
        // Is there room at the end of the last node?
        if(last->end < 100){
            last->contents[last->end] = new_item;
            last->end++;
            return;
        }
        ll_node *new_node = new ll_node;
        new_node->contents[0] = new_item;
        new_node->next = 0;
        last->next = new_node;
        last = new_node;
        last->start = 0;
        last->end = 1;
    }
    T dequeue(){ // O(1)
        return pop();
    }
/*
    void insert(T new_item, size_t idx){
        if(!idx){
            push(new_item);
            return;
        }
        ll_node *spot = start;
        for(; idx - 1; idx--)
            spot = spot->next;
        ll_node *new_node = new ll_node;
        new_node->contents = new_item;
        new_node->next = spot->next;
        spot->next = new_node;
        if(spot == last)
            last = new_node;
    }
    void remove(size_t idx){
        if(!idx) {
            pop();
            return;
        }
        ll_node *spot = start;
        for(; idx - 1; idx--)
            spot = spot->next;
        ll_node *tofree = spot->next;
        if(spot->next == last)
            last = spot;
        spot->next = spot->next->next;
        delete tofree;
    }
*/
    T& operator[](size_t idx){ // O(n)
        ll_node *spot = start;
        size_t spot_beginning_index = 0;
        unsigned items = (spot->end - spot->start);
        while(idx > spot_beginning_index + items){ // What if idx is actually after the list?  Exception?
            spot_beginning_index += items;
            spot = spot->next;
            items = (spot->end - spot->start);
        }
        return spot->contents[idx - spot_beginning_index];
    }
    sl_iterator begin() {
        return sl_iterator(start, start->start);
    }
    sl_iterator end() {
        return sl_iterator(0, 0);
    }/*
    ~list(){
        std::cout << "Destructor was called\n";
        while(start)
            pop();
    }*/
};

template<class T>
std::ostream& operator<<(std::ostream& out, compacted_list<T> &lst){
    out << "[";
    for(auto i = lst.begin(); i != lst.end(); ++i)
        out << *i << ", ";
/*
    for(auto i : lst)
        out << i << ", ";
*/
    out << "\b\b]";
    return out;
}

#endif