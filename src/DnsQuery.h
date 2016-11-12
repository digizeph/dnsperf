//
// Created by Mingwei Zhang on 11/12/16.
//

#ifndef DNSPERF_DNSQUERY_H
#define DNSPERF_DNSQUERY_H

#include <ldns/ldns.h>
#include <list>
#include <string>

using namespace std;


class DnsQuery {
private:

public:
    DnsQuery();
    int queryDomain(char[]);

};


#endif //DNSPERF_DNSQUERY_H
