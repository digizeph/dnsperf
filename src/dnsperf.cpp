#include <list>
#include "Timer.h"
#include "DnsQuery.h"
#include "DnsPerfDatabase.h"

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

// http://stackoverflow.com/a/12468109/768793
std::string random_string(size_t length) {
    struct timeval time;
    gettimeofday(&time,NULL);
    srand((time.tv_sec * 1000) + (time.tv_usec / 1000));

    auto randchar = []() -> char {
        const char charset[] =
                "0123456789"
                        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                        "abcdefghijklmnopqrstuvwxyz";
        const size_t max_index = (sizeof(charset) - 1);
        return charset[rand() % max_index];
    };
    std::string str(length, 0);
    std::generate_n(str.begin(), length, randchar);
    return str;
}


void sendQueries(){
    DnsQuery q;
    DnsPerfDatabase db;

    cout<<"Start sending DNS queries!\n";


    query_stat **stats = (query_stat **) malloc(10 * sizeof(query_stat *));
    const char *rndStr = random_string(10).c_str(); // random string appended to the domain
    for(int i = 0; i < 10; i++){
        char buffer[50];
        sprintf(buffer, "%s.%s", rndStr , domains[i]);
        stats[i] = q.queryDomain(buffer, false);
    }

    for (int i = 0; i < 10; i++) {
        cout << stats[i]->start.count() << "\t";
        cout << stats[i]->lapse.count() << "\t";
        cout << stats[i]->domain << "\n";
    }
    cout << endl;

    for (int i = 0; i < 10; i++) {
        free(stats[i]);
    }
    free(stats);

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

    thread test(timer, &sendQueries, 1000, 4);


    test.join();
    //while(true);
}

