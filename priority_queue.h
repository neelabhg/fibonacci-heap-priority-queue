/**
 * @file priority_queue.h
 */

#ifndef _PQUEUE_H_
#define _PQUEUE_H_

/**
 * Implements the max priority queue ADT.
 *
 * The implementation is up to you, but you must complete all the given
 *  public functions. You will need to add some member variables and private
 *  helper functions.
 */

#include <list>
#include <vector>

template <class T>
class PriorityQueue
{
    public:
        /**
         * Constructor: creates an empty priority queue.
         */
        PriorityQueue() : highestPriority(rootList.end()), numElems(0) { /* Nothing */ }
        
        /**
         * Copy Constructor : creates a copy of the parameter PriorityQueue
         * @param source the source PriorityQueue
         */
        PriorityQueue(const PriorityQueue<T> & source);
        
        /**
         * Destructor : frees the memory associated with the Fibonacci Heap
         */
        ~PriorityQueue();

        /**
         * Inserts the given value into the queue.
         *
         * @param value The value to be inserted.
         */
        void insert(const T & value);

        /**
         * Removes the highest value (and its associated data) from the
         *  queue.
         *
         * @return A copy of the removed (maximum) element
         */
        T pop();

        /**
         * Returns the highest value from the queue. Does NOT remove it.
         *
         * @return A copy of the minimum element
         */
        const T & top() const;

        /**
         * Determines if the queue is empty. Should be O(1).
         *
         * @return A boolean value indicating whether the queue is
         *  empty.
         */
        bool isEmpty() const;

    private:
        /**
         * The private heapNode class.
         * Represents a single node of the Fibonacci Heap.
         */
        class heapNode
        {
            public:

            /**
             * Constructor : constructs a heapNode with the value val.
             * 
             * @param val The value to initialize the node with
             */
            heapNode(const T & val) : value(val) { /* Nothing */ }
            
            /**
             * The value of template type T stored in the node.
             */
            T value;
            
            /**
             * Function to return the degree of the heapNode
             * (the number of children the node has).
             * 
             * @return the degree of this heapNode
             */
            int degree() { return children.size(); }
            
            /**
             * A list containing pointers to the children of this heapNode.
             */
            std::list<heapNode *> children;
        };
        
        /*
         * Private member functions
         */
        
        /**
         * Private function to abstract the comparision of priorities of elements.
         * The result is that the Max Priority Queue can be converted to a Min Priority Queue by just changing the
         * comparision operator in this function.
         * 
         * @param x The first operand
         * @param y The second operand
         * @return a boolean value indicating whether x has a higher priority (is greater) than y
         */
        bool higherPriority(const T & x, const T & y) const { return x > y; }
        
        /**
         * Private helper function for the copy constructor.
         * Recursively copies all the heapNodes in the Fibonacci Heap.
         * @param currNode the current node in recursion, of the destination
         * @param sourceCurrNode the current node in recursion, of the source
         */
        void copy(heapNode * & currNode, heapNode * const & sourceCurrNode);
        
        /**
         * Private helper function for the destructor.
         * Recursively destroys all heapNodes in the Fibonacci Heap.
         * @param currNode the current node in recursion
         */
        void clear(heapNode * & currNode);
        
        /**
         * Private helper function for the public pop() function.
         * It is this function which basically implements the Fibonacci Heap.
         * After removal of the highest priority element, it updates the highestPriority data member,
         * and merges the binomial heaps of the same degree.
         * 
         * The algorithm is adapted from the pseudocode given in the following tutorial:
         * http://compgeom.cs.uiuc.edu/~jeffe/teaching/algorithms/notes/xl-fiboheap.pdf
         */
        void consolidate();

        /*
         * Private member data
         */
        
        /**
         * An STL list containing the root nodes of the binomial heaps,
         * hence forming a collection of trees, which is a Fibonacci Heap.
         */
        std::list<heapNode *> rootList;
        
        /**
         * A list iterator to the element in the root list with the highest priority.
         */
        typename std::list<heapNode *>::iterator highestPriority;
        
        /**
         * The number of elements in the Priority Queue.
         * This number is used to determine the size of the degree vector
         * in the consolidate() function.
         */
        size_t numElems;
};

#include "priority_queue.cpp"
#endif
