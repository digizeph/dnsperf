//
// Created by Mingwei Zhang on 11/12/16.
//

#ifndef DNSPERF_DNSPERFDATABASE_H
#define DNSPERF_DNSPERFDATABASE_H

#include <mysql++.h>
using namespace std;
using namespace mysqlpp;

class DnsPerfDatabase {

private:
    Connection * conn;
public:
    DnsPerfDatabase();

};


#endif //DNSPERF_DNSPERFDATABASE_H
