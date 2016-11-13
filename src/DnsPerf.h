//
// Created by Mingwei Zhang on 11/13/16.
//

#ifndef DNSPERF_DNSPERF_H
#define DNSPERF_DNSPERF_H


class DnsPerf {

private:

    bool callQuery = false, checkResult = false;
    int interval = 2, count = 1;

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


    Utils *utils;
    DnsPerfDatabase *db;
    DnsQuery *q;

public:
    DnsPerf();
    void getStats();
    void sendQueries();
    void parseArguments(int, char * []);
    void start();
    void operator()(int, int);

};

#endif //DNSPERF_DNSPERF_H
