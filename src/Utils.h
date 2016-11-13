//
// Created by Mingwei Zhang on 11/13/16.
//

#ifndef DNSPERF_UTILS_H
#define DNSPERF_UTILS_H
#include <algorithm>
#include "DnsPerfDatabase.h"
#include "DnsQuery.h"

class Utils {

public:
    void printRecordStats(record_stat **);
    void printQueryStats(query_stat **);
    std::string random_string(size_t);
};


#endif //DNSPERF_UTILS_H
