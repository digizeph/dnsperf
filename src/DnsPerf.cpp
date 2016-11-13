#include <list>
#include <algorithm>
#include "Timer.h"
#include "DnsQuery.h"
#include "DnsPerfDatabase.h"
#include "Utils.h"
#include "DnsPerf.h"

#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>

using namespace std;


DnsPerf::DnsPerf(){
    db = new DnsPerfDatabase();
    q = new DnsQuery();
    utils = new Utils();
}

void DnsPerf::getStats(){
    record_stat ** stats = (record_stat **) malloc (10 * sizeof(char*));

    for(int i=0;i<10;i++) {
        stats[i] = db->getRecordStats(domains[i]);

    }
    utils->printRecordStats(stats);

    for(int i=0;i<10;i++) {
        free(stats[i]);
    }
    free(stats);
}

void DnsPerf::sendQueries(){

    cout<<"Start sending DNS queries!\n";


    query_stat **stats = (query_stat **) malloc(10 * sizeof(query_stat *));
    const char *rndStr = utils -> random_string(10).c_str(); // random string appended to the domain
    for(int i = 0; i < 10; i++){
        char buffer[50];
        sprintf(buffer, "%s.%s", rndStr , domains[i]);
        stats[i] = q->queryDomain(rndStr, domains[i], false);
    }

    for (int i = 0; i < 10; i++) {
        if(stats[i]->success==true){
            int id = (int) db->insertRecord(stats[i]);
            cout << id << "\t";
            cout << stats[i]->start.count() << "\t";
            cout << stats[i]->lapse.count() << "\t";
            cout << stats[i]->domain << "\n";
        }
    }
    cout << endl;

    for (int i = 0; i < 10; i++) {
        free(stats[i]);
    }
    free(stats);

    cout<<"Finished DNS queries!\n";
}

void DnsPerf::parseArguments(int argc, char * argv[]) {

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
                break;
            case '?':
                fprintf(stderr, "usuage is \n -a : for enabling a \n -b : for enabling b \n -c: <value> ");
            default:
                cout << endl;
                abort();
        }
}

void DnsPerf::start()
{
    //testTimer();
    Timer timer;
    //timer.timer_start(&testTimer, 1000);

    //thread test(timer, &sendQueries, 1000, 10);
    //thread test(timer, &getStats, 1000, 1);
    //test.join();

    if(this->checkResult)
        this->getStats();
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

