//
// Created by Mingwei Zhang on 11/12/16.
//

#ifndef DNSPERF_DNSPERFDATABASE_H
#define DNSPERF_DNSPERFDATABASE_H

#include <mysql++.h>
#include "DnsQuery.h"

using namespace std;
using namespace mysqlpp;

/**
 * statistics struct
 */
struct record_stat{
    char *domain;  // domain name
    float average;  // average query time
    float stddev;   // statndar deviation
    int count;      // number of records
    long long int first;    // timestamp of the first query
    long long int last;     // timestamp of the last query
};

class DnsPerfDatabase {

private:
    Connection conn;    // Database connection object
public:
    DnsPerfDatabase();  // constructor
    ulonglong insertRecord(query_stat *);    // insert entry
    record_stat *getRecordStats(char []);  // gather statistics
};


#endif //DNSPERF_DNSPERFDATABASE_H
