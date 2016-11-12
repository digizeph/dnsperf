//
// Created by Mingwei Zhang on 11/12/16.
//

#ifndef DNSPERF_DNSQUERY_H
#define DNSPERF_DNSQUERY_H

#include <ldns/ldns.h>
#include <list>
#include <string>
#include <chrono>

using namespace std::chrono;


using namespace std;

struct query_stat {
    bool success = false;   // query status
    milliseconds start;
    milliseconds lapse; // finish time - start time
    char domain[50];

};

/*
milliseconds ms = duration_cast< milliseconds >(
        system_clock::now().time_since_epoch()
);
 */


class DnsQuery {
private:

public:
    DnsQuery();

    query_stat *queryDomain(const char[], bool);

};


#endif //DNSPERF_DNSQUERY_H
