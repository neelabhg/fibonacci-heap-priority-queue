#include "priority_queue.h"

template <class T>
PriorityQueue<T>::PriorityQueue(const PriorityQueue<T> & source) : numElems(source.numElems)
{
    typename std::list<heapNode *>::const_iterator it;
    for (it = source.rootList.begin(); it != source.rootList.end(); it++)
    {
        heapNode * rootNode;
        copy(rootNode, *it);
        rootList.push_back(rootNode);
    }
    
    // Update highestPriority
    highestPriority = rootList.begin();
    typename std::list<heapNode *>::iterator it2;
    for (it2 = rootList.begin(); it2 != rootList.end(); it2++)
    {
        if (higherPriority((*it2)->value, (*highestPriority)->value))
        {
            highestPriority = it2;
        }
    }
}

template <class T>
void PriorityQueue<T>::copy(heapNode * & currNode, heapNode * const & sourceCurrNode)
{
    currNode = new heapNode(sourceCurrNode->value);
    if (!sourceCurrNode->children.empty())
    {
        typename std::list<heapNode *>::const_iterator it;
        for (it = sourceCurrNode->children.begin(); it != sourceCurrNode->children.end(); it++)
        {
            heapNode * child;
            copy(child, *it);
            currNode->children.push_back(child);
        }
    }
}

template <class T>
PriorityQueue<T>::~PriorityQueue()
{
    typename std::list<heapNode *>::iterator it;
    for (it = rootList.begin(); it != rootList.end(); it++)
    {
        clear(*it);
    }
}

template <class T>
void PriorityQueue<T>::clear(heapNode * & currNode)
{
    if (!currNode->children.empty())
    {
        typename std::list<heapNode *>::iterator it;
        for (it = currNode->children.begin(); it != currNode->children.end(); it++)
        {
            clear(*it);
        }
    }
    delete currNode;
    currNode = NULL;
}

template <class T>
void PriorityQueue<T>::insert(const T & value)
{
    heapNode * newNode = new heapNode(value);
    rootList.push_back(newNode);
    if (highestPriority == rootList.end() || higherPriority(value, (*highestPriority)->value)) {
        highestPriority = --rootList.end();
    }
    numElems++;
}

template <class T>
T PriorityQueue<T>::pop()
{
    if (isEmpty()) return T();

    // Meld children into root list
    rootList.splice(rootList.end(), (*highestPriority)->children);

    // Delete highest priority element
    T retVal = (*highestPriority)->value;
    delete *highestPriority;
    highestPriority = rootList.erase(highestPriority);

    // Consolidate trees and update highest priority
    consolidate();

    numElems--;

    return retVal;
}

template <class T>
const T & PriorityQueue<T>::top() const
{
    return (*highestPriority)->value;
}

template <class T>
bool PriorityQueue<T>::isEmpty() const
{
    return rootList.empty();
}

template <class T>
void PriorityQueue<T>::consolidate()
{
    highestPriority = rootList.begin();
    std::vector<typename std::list<heapNode *>::iterator> B(numElems, rootList.end());

    typename std::list<heapNode *>::iterator it;
    for (it = rootList.begin(); it != rootList.end(); ++it)
    {
        if (higherPriority((*it)->value, (*highestPriority)->value))
            highestPriority = it;

        typename std::list<heapNode *>::iterator v = it;
        while (B[(*v)->degree()] != rootList.end())
        {
            typename std::list<heapNode *>::iterator w = B[(*v)->degree()];
            if (v == w) break;
            B[(*v)->degree()] = rootList.end();
            if (higherPriority((*w)->value, (*v)->value))
            {
                std::swap(v, w);
            }
            ((*v)->children).push_back(*w);
            if (highestPriority == w) highestPriority = v;
            w = rootList.erase(w);
        }
        it = v;
        B[(*v)->degree()] = v;
    }
}
