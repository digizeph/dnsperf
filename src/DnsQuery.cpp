//
// Created by Mingwei Zhang on 11/12/16.
//

#include "DnsQuery.h"

DnsQuery::DnsQuery() {

}

int DnsQuery::queryDomain(char * domainStr) {

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
    domain = ldns_dname_new_frm_str(domainStr);
    if (!domain) {
        return -1;
    }

    /* create a new resolver from /etc/resolv.conf */
    s = ldns_resolver_new_frm_file(&res, NULL);

    if (s != LDNS_STATUS_OK) {
        exit(EXIT_FAILURE);
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
        exit(EXIT_FAILURE);
    } else {
        /* retrieve the NS records from the answer section of that
         * packet
         */
        ns = ldns_pkt_rr_list_by_type(p,
                                      LDNS_RR_TYPE_NS,
                                      LDNS_SECTION_ANSWER);
        if (!ns) {
            fprintf(stderr,
                    " *** invalid answer name %s after NS query for %s\n",
                    domainStr, domainStr);
            ldns_pkt_free(p);
            ldns_resolver_deep_free(res);
            return -1;
        } else {
            /* NOTE: printing is optional */
            ldns_rr_list_sort(ns);
            ldns_rr_list_print(stdout, ns);
            ldns_rr_list_deep_free(ns);
        }
    }
    ldns_pkt_free(p);
    ldns_resolver_deep_free(res);

    return 0;
}

