//
// Created by Mingwei Zhang on 11/12/16.
//

#ifndef DNSPERF_DNSPERFDATABASE_H
#define DNSPERF_DNSPERFDATABASE_H

#include <mysql++.h>
#include "DnsQuery.h"

using namespace std;
using namespace mysqlpp;

struct record_stat{
    float average;
    float stddev;
    int count;
    long long int first;
    long long int last;
};

class DnsPerfDatabase {

private:
    Connection conn;
public:
    DnsPerfDatabase();
    ulonglong insertRecord(query_stat*);
    record_stat * getRecordStats(const char []);
};


#endif //DNSPERF_DNSPERFDATABASE_H
