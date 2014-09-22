#include <iostream>
#include <string>
#include <cstdlib>
#include <algorithm>
#include "priority_queue.h"
using namespace std;

void testRandom(const int SZ)
{
    PriorityQueue<size_t> queue;
    srand(225);
    vector<size_t> vals;
    for(size_t i = 0; i < SZ; ++i)
        vals.push_back(i);
        
    std::random_shuffle(vals.begin(), vals.end());
    for(size_t i = 0; i < SZ; ++i)
        queue.insert(vals[i]);
    
    for(size_t i = 0; i < SZ; ++i)
    {
        cout << "pop: " << queue.pop() << endl;
    }
}

void testDupes()
{
    PriorityQueue<int> queue;
    
    for(size_t i = 0; i < 20; ++i)
    {
        queue.insert(2);
    }
    
    while (!queue.isEmpty())
    {
        cout << "pop: " << queue.pop() << endl;
    }
}

int main(int argc, char* argv[])
{
    testDupes();
        
    return 0;
}
