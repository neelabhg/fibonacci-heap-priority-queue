#include <iostream>
#include <ctime>
#include <cstdlib>
#include <sstream>
#include <fstream>
#include "priority_queue.h"
using namespace std;

void plot_insert_vector(int n)
{
    PriorityQueue<int> queue;
    // create a pqueue of size n
    for (int i = 0; i < n; i++)
    {
        queue.insert(rand());
    }
    // now measure time for an insertion into a pqueue of size n
    clock_t t = clock();
    queue.insert(rand());
    t = clock() - t;
    double seconds = (double)t/CLOCKS_PER_SEC;
    cout << seconds << endl;
}

void plot_insert(int n)
{
    vector< PriorityQueue<int> > queueVector(100);
    // create a vector of pqueues of size n
    for (int i = 0; i < queueVector.size(); i++)
    {
        for (int j = 0; j < n; j++)
        {
            queueVector[i].insert(rand());
        }
    }
    // now measure time for an insertion into all pqueues
    clock_t t = clock();
    for (int i = 0; i < queueVector.size(); i++)
    {
        queueVector[i].insert(rand());
    }
    t = clock() - t;
    double seconds = (double)t/CLOCKS_PER_SEC;
    // now average the time by the number of queues
    cout << seconds << endl;
}

void time_pop(int num_readings, int step, int size_limit, stringstream & outstr)
{
    PriorityQueue<int> queue;
    int num_elems = 0;
    
    for (int i = 0; i < num_readings && num_elems < size_limit; i++)
    {
        clock_t t = clock();
        queue.pop();
        t = clock() - t;
        double seconds = (double)t/CLOCKS_PER_SEC;
        outstr << num_elems << " " << seconds << endl;
        num_elems--;
        for (int j = 0; j < step+1; j++)
        {
            queue.insert(rand());
            num_elems++;
        }
    }
}

void write_pop_data(string filename)
{
    ofstream file;
    file.open(filename.c_str());
    file << "" << endl;
    stringstream ss;
    time_pop(1000, 10000, 10000000, ss);
    file << ss.str();
    file.close();
}

void amortized_pop(int n)
{
    PriorityQueue<int> queue;
    // create a pqueue of size n
    for (int i = 0; i < n; i++)
    {
        queue.insert(rand());
    }
    // now measure time for an insertion into a pqueue of size n
    clock_t t = clock();
    for (int i = 0; i < n; i++)
    {
        queue.pop();
    }
    t = clock() - t;
    double seconds = (double)t/CLOCKS_PER_SEC;
    cout << seconds << endl;
}

int main(int argc, char* argv[])
{
    srand(time(NULL));
    
    write_pop_data("pop.txt");
    
    return 0;
}
