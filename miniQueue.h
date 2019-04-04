//
// Created by Stephen Stranahan on 2019-02-19.
//

#pragma once
#include<iostream>
using namespace std;

const int SIZE = 36;

template <typename T>
class miniQueue
{
private:
    T arr[SIZE];
    int first, last, count;
public:
    miniQueue() : first(0), last(0), count(0) { }
    void push(const T& val);
    void pop();
    T& front();
    T& back();
    void display();
    int size();
    bool empty();
};

template<typename T>
void miniQueue<T>::push(const T &val)
{
    if (count == SIZE)
        throw overflow_error("FULL");

    arr[last] = val;
    count++;
    last = (last + 1) % SIZE;   // ??
}

template<typename T>
void miniQueue<T>::pop()
{
    if (empty())
        throw underflow_error("EMPTY");

    count--;
    first = (first + 1) % SIZE;
}

template<typename T>
T &miniQueue<T>::front()
{
    return arr[first];
}

template<typename T>
T &miniQueue<T>::back()
{
    return arr[(last - 1 + SIZE) % SIZE];
}

template<typename T>
void miniQueue<T>::display()
{
    if (count == 0)
        throw underflow_error("EMPTY");

    for (int i = first; i < first + count; i++)
        cout << arr [i % SIZE] << "\t";

    cout << endl;
}

template<typename T>
int miniQueue<T>::size()
{
    return count;
}

template<typename T>
bool miniQueue<T>::empty()
{
    return count == 0;
}

