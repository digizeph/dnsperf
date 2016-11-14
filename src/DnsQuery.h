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

/**
 * Struct to hold DNS query performance information
 */
struct query_stat {
    bool success = false;   // query status
    long long int start;    // timestamp of starting time: UNIX time in millisecond
    long long int lapse;    // finish time - start time
    char domain[50];        // domain name
};


class DnsQuery {

public:
    DnsQuery(); // constructor
    query_stat *queryDomain(const char [], char[], bool);   // query function
};


#endif //DNSPERF_DNSQUERY_H
