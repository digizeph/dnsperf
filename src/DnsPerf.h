//
// Created by Mingwei Zhang on 11/13/16.
//

#ifndef DNSPERF_DNSPERF_H
#define DNSPERF_DNSPERF_H


class DnsPerf {

private:

    // whether to check database or call queries
    bool callQuery = false, checkResult = false;

    // default interval and round count
    int interval = 2, count = 1;

    /**
     * Pre-registered domains.
     */
    char * domains[10] = {
            (char *) "google.com",
            (char *) "facebook.com",
            (char *) "youtube.com",
            (char *) "yahoo.com",
            (char *) "live.com",
            (char *) "wikipedia.org",
            (char *) "baidu.com",
            (char *) "blogger.com",
            (char *) "msn.com",
            (char *) "qq.com"
    };


    Utils *utils;           // utilities
    DnsPerfDatabase *db;    // database tool
    DnsQuery *q;            // dns query tool

public:
    DnsPerf();  // constructor
    void getStats();    // get statistics
    void sendQueries(); // send DNS queries
    void parseArguments(int, char *[]);    // parse commandline arguments
    void start();  // main entry function
    void operator()(int, int);  // timed-run function

};

#endif //DNSPERF_DNSPERF_H
