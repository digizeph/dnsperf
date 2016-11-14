#include <list>
#include <thread>
#include "DnsQuery.h"
#include "DnsPerfDatabase.h"
#include "Utils.h"
#include "DnsPerf.h"

using namespace std;


DnsPerf::DnsPerf(){
}

/**
 * Read statistics from the database.
 */
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

/**
 * Send DNS queries and log the results to database.
 */
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

/**
 * Parse commandline arguments.
 *
 * @param argc number of arguments
 * @param argv list of arguments
 */
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

/**
 * Multi-threading function for periodical DNS queries
 *
 * @param interval  interval in seconds
 * @param count number of rounds to query
 */
void DnsPerf::operator()(int interval, int count = -1)
{
    if (count > 0) {
        // If count is greater than 0, query count times.
        count--;
        this->sendQueries();

        // sleep interval seconds before run another query.
        while (count > 0) {
            std::this_thread::sleep_for(std::chrono::seconds(interval));
            this->sendQueries();
            count--;
        }
    } else if (count == 0) {
        // don't do anything if count = 0
        return;
    } else {
        // if count < 0, run indefinitely
        while (true) {
            this->sendQueries();
            std::this_thread::sleep_for(std::chrono::milliseconds(interval));
        }
    }
}

/**
 * Main entry function for DNS query.
 */
void DnsPerf::start()
{

    if(this->checkResult){
        // Run database check first if specified.
        cout << "********"<<endl<<"DNS performance statistics"<<endl<<"*********"<<endl<<endl;
        this->getStats();
    }
    if(this->callQuery){
        // Run DNS queries if specified.
        cout << "********"<<endl<<"DNS Queries Start"<<endl<<"*********"<<endl<<endl;
        thread runThread((*this), this->interval, this->count);
        runThread.join();
    }
}


/**
 * The main function for dnsperf.
 */
int main(int argc, char *argv[])
{
    DnsPerf *perf = new DnsPerf();

    perf->parseArguments(argc,argv);
    perf->start();
}

