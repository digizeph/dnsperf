#include "timer.h"
#include <iostream>
using namespace std;

void testTimer(){
    cout<<"Hello world!\n";
}

int main(int argc, char *argv[])  
{
    //testTimer();
    Timer timer;
    //timer.timer_start(&testTimer, 1000);

    thread test(timer, &testTimer, 1000);


    test.join();
    //while(true);
}

