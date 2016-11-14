//
// Created by Mingwei Zhang on 11/13/16.
//

#ifndef DNSPERF_UTILS_H
#define DNSPERF_UTILS_H
#include <algorithm>
#include "DnsPerfDatabase.h"
#include "DnsQuery.h"

/**
 * Unitity functions class
 */
class Utils {

public:
    void printRecordStats(record_stat **);  // print statistics results
    void printQueryStats(query_stat **);    // print raw query performance results
    std::string random_string(size_t);      // generate random string for domain prefix.
};


#endif //DNSPERF_UTILS_H
