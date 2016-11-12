#include <list>
#include "Timer.h"
using namespace std;

const char * domains[] = {
    "google.com",
    "facebook.com",
    "youtube.com",
    "yahoo.com",
    "live.com",
    "wikipedia.org",
    "baidu.com",
    "blogger.com",
    "msn.com",
    "qq.com"
};


void sendQueries(){
    cout<<"Start sending DNS queries!\n";
    for(int i = 0; i < 10; i++){
        cout<<domains[i]<<endl;
    }
    cout<<"Finished DNS queries!\n";
}

/**
 * The main function for dnsperf.
 *
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char *argv[])  
{
    //testTimer();
    Timer timer;
    //timer.timer_start(&testTimer, 1000);

    thread test(timer, &sendQueries, 1000);


    test.join();
    //while(true);
}

