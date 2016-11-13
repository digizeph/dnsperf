#include <list>
#include <thread>
#include <algorithm>
#include "DnsQuery.h"
#include "DnsPerfDatabase.h"
#include "Utils.h"
#include "DnsPerf.h"

using namespace std;


DnsPerf::DnsPerf(){
}

void DnsPerf::getStats(){
    record_stat ** stats = (record_stat **) malloc (10 * sizeof(char*));

    for(int i=0;i<10;i++) {
        stats[i] = db->getRecordStats(this->domains[i]);

    }
    utils->printRecordStats(stats);

    for(int i=0;i<10;i++) {
        free(stats[i]);
    }
    free(stats);
}

void DnsPerf::sendQueries(){

    query_stat **stats = (query_stat **) malloc(10 * sizeof(query_stat *));
    const char *rndStr = utils -> random_string(10).c_str(); // random string appended to the domain

    // query for results.
    for(int i = 0; i < 10; i++){
        char buffer[50];
        sprintf(buffer, "%s.%s", rndStr , domains[i]);
        stats[i] = q->queryDomain(rndStr, domains[i], false);
    }

    // insert query results to database
    for (int i = 0; i < 10; i++) {
        if(stats[i]->success==true){
            db->insertRecord(stats[i]);
        }
    }

    utils->printQueryStats(stats);

    for (int i = 0; i < 10; i++) {
        free(stats[i]);
    }
    free(stats);

}

void DnsPerf::parseArguments(int argc, char * argv[]) {

    if(argc<=1){
        fprintf(stderr, "usage\n -r : check results\n -q : run queries\n"
                " -c : number of queries to run (-1 for forever run)\n -i : interval seconds between each run");
        abort();
    }

    int opt;
    while ((opt = getopt(argc, argv, "i:c:qr")) != EOF)
        switch (opt) {
            case 'r':
                checkResult = true;
                break;
            case 'q':
                callQuery = true;
                break;
            case 'c':
                count = atoi(optarg);
                break;
            case 'i':
                interval = atoi(optarg);
                if (interval<0){
                    fprintf(stderr, "Interval must be greater than 0!");
                    abort();
                }
                break;
            case '?':
                fprintf(stderr, "usage\n -r : check results\n -q : run queries\n"
                        " -c : number of queries to run (-1 for forever run)\n -i : interval seconds between each run");
            default:
                fprintf(stderr, "usage\n -r : check results\n -q : run queries\n"
                        " -c : number of queries to run (-1 for forever run)\n -i : interval seconds between each run");
                cout << endl;
                abort();
        }

    db = new DnsPerfDatabase();
    q = new DnsQuery();
    utils = new Utils();
}

void DnsPerf::operator()(int interval, int count = -1)
{
    if (count > 0) {
        count--;
        this->sendQueries();
        while (count > 0) {
            std::this_thread::sleep_for(std::chrono::seconds(interval));
            this->sendQueries();
            count--;
        }
    } else if (count == 0) {
        return;
    } else {
        while (true) {
            this->sendQueries();
            std::this_thread::sleep_for(std::chrono::milliseconds(interval));
        }
    }
}

void DnsPerf::start()
{
    //testTimer();

    if(this->checkResult){
        cout << "********"<<endl<<"DNS performance statistics"<<endl<<"*********"<<endl<<endl;
        this->getStats();
    }
    if(this->callQuery){
        cout << "********"<<endl<<"DNS Queries Start"<<endl<<"*********"<<endl<<endl;
        thread runThread((*this), this->interval, this->count);
        runThread.join();
    }
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
    DnsPerf *perf = new DnsPerf();

    perf->parseArguments(argc,argv);
    perf->start();
}

