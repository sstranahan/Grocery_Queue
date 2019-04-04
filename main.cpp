// CPS 272 - MP5 - GROCERY STORE QUEUE
// STEPHEN STRANAHAN - PROF. KHALED MANSOUR - 2/19/2019

// This program will simulate the checkout line at a grocery store using a queue and objects of a class called customer.
// The arrival time of each consecutive customer will be randomized using a constant as the upper limit (4) so as to be easily updated.
// Additionally, the checkout time of each customer will be randomized using a constant as the upper limit. (4)
// The maximum number of people who were in line at once will be reported after the simulation is run,
// as will be the maximum number of minutes that a customer waited in line. The number of minutes waited
// by each customer is stored in a data member of the Customer class. Since queues do not allow
// direct access, after each minute the entire queue of customers will be emptied, waitTime incremented, copied into
// a temporary queue, and back into the original queue. Thank you!

#include <iostream>
#include<ctime>
#include<fstream>
#include"Customer.h"
#include"miniQueue.h"

using namespace std;

const int MAX_ARRIVAL_INTERVAL = 4;             // Const variable for the maximum number of minutes between arrival of customers
const int MAX_SERVICE_INTERVAL = 4;             // Const variable for the maximum number of minutes to complete the service
const int MINUTES_TO_RUN = 120;                 // Const variable for the number of minutes to run the simulation

void printHeader(ofstream& fout);

unsigned int arrivalRandom()
{
    return (rand() % MAX_ARRIVAL_INTERVAL) + 1;         // Will generate a random int between 1 and 4 (inclusive)
}

unsigned int serviceRandom()
{
    return (rand() % MAX_SERVICE_INTERVAL) + 1;
}

int main()
{
    ofstream fout("Output.txt");
    printHeader(fout);

    srand(time(NULL));

    unsigned int maxCustInQueue = 0;
    unsigned int maxWaitTime = 0;

    unsigned int totalTimer = 0;
    unsigned int timer = 0;
    unsigned int first = arrivalRandom();   // Time until the first customer arrives
    unsigned int serviceTime = 0;
    unsigned int next = 0;

    miniQueue<Customer> queue1;

    fout << "First customer will arrive at minute: " << first << endl;
    fout << endl;

    while (timer != first)      // Progresses the clock until first customer arrives
    {
        timer++;
        totalTimer++;
    }
        Customer cst;
        queue1.push(cst);
        serviceTime = serviceRandom();      // Establishes how long service will take
        fout << "(Minute: " << totalTimer << ") *** Serving first customer. Time to complete: " << serviceTime << " minutes." << endl;
        timer = 0;
        next = arrivalRandom();             // Establishes when the next customer will arrive

    while (totalTimer != MINUTES_TO_RUN)       // Loop for total simulation time
    {
        if(timer == next)       // If the timer has reached the time for arrival of the next customer
        {
            fout << "(Minute: " << totalTimer << ") *** Next customer arrived." << endl;
            Customer cst;
            queue1.push(cst);       // Pushes a customer into the queue

            if (queue1.size() > maxCustInQueue)         // After adding a customer to the queue, if the queue size is the largest it has been, stores its size to the maxCustInQueue counter
                maxCustInQueue = queue1.size();

            timer = 0;
            next = arrivalRandom();     // Sets the arrival time of the next customer
        }

        if(serviceTime == 0)            // When the current service is complete - will pop a customer off the queue, update the maxWaitTime counter when appropriate, and calculate the next service time
        {
            if (queue1.front().getWaitTime() > maxWaitTime)     // Increments the maxWaitTime counter when the customer in front of the queue has had the longest wait time
                maxWaitTime = queue1.front().getWaitTime();

            if (queue1.size() > 0)      // Prevents undefined behavior
                queue1.pop();

            serviceTime = serviceRandom();
            fout << "(Minute: " << totalTimer << ") *** Checkout complete. Next customer service time: " << serviceTime << " minutes." << endl;
            continue;       // So the service counter isn't decremented before checking for the arrival of next customer
        }

        timer++;            // Advances the counters for each minute
        totalTimer++;
        if (!queue1.empty())        // Will only start counting down the service timer when there is actually a customer to be serviced
            serviceTime--;

        miniQueue<Customer> tmp;

        while (!queue1.empty())     // Stores each customer in the queue in a temp customer object, increments its waitTime counter, and pushes it into the temp queue
        {                           // Have to do it this way since the objects in a queue cannot be directly accessed.
            Customer c;
            c = queue1.front();
            c.incrementWaitTime();
            queue1.pop();
            tmp.push(c);
        }

        while (!tmp.empty())        // Removes each customer from the temp queue and pushes it back into the original queue
        {
            Customer c;
            c = tmp.front();
            tmp.pop();
            queue1.push(c);
        }
    }

    fout << endl;           // Prints the totals after the simulation is complete
    fout << "*******************************************************************************************" << endl;
    fout << "Simulation complete: " << MINUTES_TO_RUN << " minutes elapsed. " << queue1.size() << " customers remained in line." << endl;
    fout << "The maximum number of customers in line was: " << maxCustInQueue << " and the longest individual wait time was: " << maxWaitTime << " minutes." << endl;

    return 0;
}

// Thanks!!

void printHeader(ofstream& fout)        // Prints introductory header
{
    fout << "CPS 272 - MACHINE PROBLEM 5 - QUEUES - GROCERY STORE CHECKOUT SIMULATION" << endl;
    fout << "STEPHEN STRANAHAN - PROF. KHALED MANSOUR - 02/21/2019" << endl;
    fout << "************************************************************************" << endl;
    fout << endl;
}
