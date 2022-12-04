#include <iostream>

template <class T>
class Chain;

template <class T>
class ChainNode {
    friend class Chain<T>;
    friend class ChainIterator<T>;
    private:
        T data;
        ChainNode <T> *link;
};

template <class T>
class Chain {
    friend class ChainIterator<T>;
    public:
        Chain() {first=0;}; //constructor initializing first = 0
        
        // operations
    private:
        ChainNode <T> *first;
};

template <class T>
class ChainIterator {
    public: 

};