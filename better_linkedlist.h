#ifndef BETTER_LINKEDLIST_H
#define BETTER_LINKEDLIST_H

#include<iostream>

template<class T>
class list {
    struct ll_node { // efficiency if a vec3:  12 bytes of data to every 8 bytes of pointer, 12/20 or 60%
        T contents;
        ll_node *next;
    };

    class sl_iterator {
        ll_node *place;
    public:
        sl_iterator(ll_node *p) : place(p) {}
        sl_iterator& operator++(){
            place = place->next;
            return *this;
        }
        bool operator!=(const sl_iterator &other) const {
            return place != other.place;
        }
        T& operator*(){
            return place->contents;
        }
    };

    ll_node *start = 0, *last = 0; // The end points to the last item
public:
    list() {
        std::cout << "default constructor called\n";
    }
    list(list &other){
        std::cout << "copy constructor called\n";
        size_t pos = 0;
        for(auto i : other)
            insert(i, pos++);
    }
    void push(T new_item){ //  O(1)
        ll_node *new_node = new ll_node;
        new_node->contents = new_item;
        new_node->next = start;
        if(start == 0)
            last = new_node;
        start = new_node;
    }
    bool empty(){
        return start == 0;
    }
    T pop(){ // O(1)
        T result = start->contents;
        ll_node *tofree = start;
        start = start->next;
        delete tofree;
        // Was that the last item?  Might need to adjust the end pointer
        if(!start)
            last = 0;
        return result;
    }
    void enqueue(T new_item){ // O(1)
        // What if the list was empty before and therefore the end pointer is null?
        ll_node *new_node = new ll_node;
        new_node->contents = new_item;
        new_node->next = 0;
        if(last)
            last->next = new_node;
        else
            start = new_node;
        last = new_node;
    }
    T dequeue(){ // O(1)
        return pop();
    }
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
    T& operator[](size_t idx){ // O(n)
        ll_node *spot = start;
        for(; idx; idx--)
            spot = spot->next;
        return spot->contents;
    }
    sl_iterator begin() {
        return sl_iterator(start);
    }
    sl_iterator end() {
        return sl_iterator(0);
    }
    ~list(){
        std::cout << "Destructor was called\n";
        while(start)
            pop();
    }
};

template<class T>
std::ostream& operator<<(std::ostream& out, list<T> &lst){
    out << "[";
    for(auto i : lst)
        out << i << ", ";
    out << "\b\b]";
    return out;
}

#endif