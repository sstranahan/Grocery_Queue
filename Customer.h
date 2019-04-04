//
// Created by Stephen Stranahan on 2019-02-21.
//

#pragma once
using namespace std;

// Customer class only has one data member - the wait time in minutes that each customer waited in line
// 2 Functions - one to increment the waitTime and one to get it

class Customer
{
private:
    unsigned int waitTime;
public:
    Customer() { waitTime = 0; }
    void incrementWaitTime()
    {
        waitTime++;
    }
    unsigned int getWaitTime()
    {
        return waitTime;
    }
};



