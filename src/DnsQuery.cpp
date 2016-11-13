//
// Created by Mingwei Zhang on 11/12/16.
//

#include "DnsQuery.h"

DnsQuery::DnsQuery() {

}

query_stat *DnsQuery::queryDomain(const char prefix[], char domainStr[], bool display) {

    char queryDomain[50];
    sprintf(queryDomain, "%s.%s", prefix , domainStr);

    query_stat *stat = (query_stat *) malloc(sizeof(query_stat));

    milliseconds t_start, t_end;

    t_start = duration_cast<milliseconds>(
            system_clock::now().time_since_epoch()
    );

    ldns_resolver *res;
    ldns_rdf *domain;
    ldns_pkt *p;
    ldns_rr_list *ns;
    ldns_status s;

    p = NULL;
    ns = NULL;
    domain = NULL;
    res = NULL;

    /* create a rdf from the command line arg */
    domain = ldns_dname_new_frm_str(queryDomain);
    if (!domain) {
        return stat;
    }

    /* create a new resolver from /etc/resolv.conf */
    s = ldns_resolver_new_frm_file(&res, NULL);

    if (s != LDNS_STATUS_OK) {
        //exit(EXIT_FAILURE);
        return stat;
    }

    /* use the resolver to send a query for the mx
     * records of the domain given on the command line
     */
    p = ldns_resolver_query(res,
                            domain,
                            LDNS_RR_TYPE_NS,
                            LDNS_RR_CLASS_IN,
                            LDNS_RD);

    ldns_rdf_deep_free(domain);

    if (!p)  {
        //exit(EXIT_FAILURE);
        return stat;
    } else {
        /* retrieve the NS records from the answer section of that
         * packet
         */
        ns = ldns_pkt_rr_list_by_type(p,
                                      LDNS_RR_TYPE_NS,
                                      LDNS_SECTION_ANSWER);
        t_end = duration_cast<milliseconds>(
                system_clock::now().time_since_epoch()
        );
        if (display) {
            if (!ns) {
                fprintf(stdout,
                        " *** invalid answer name %s after NS query for %s\n",
                        domainStr, domainStr);
            } else {
                /* NOTE: printing is optional */
                ldns_rr_list_sort(ns);
                ldns_rr_list_print(stdout, ns);
                ldns_rr_list_deep_free(ns);
            }
        }
    }
    ldns_pkt_free(p);
    ldns_resolver_deep_free(res);

    stat->success = true;
    sprintf(stat->domain, "%s", domainStr);
    stat->start = t_start.count();
    stat->lapse = t_end.count() - t_start.count();


    return stat;
}

