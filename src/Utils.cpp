//
// Created by Mingwei Zhang on 11/13/16.
//

#include "Utils.h"
#include "DnsPerf.h"

// http://stackoverflow.com/a/12468109/768793
std::string Utils::random_string(size_t length) {
    struct timeval time;
    gettimeofday(&time,NULL);
    srand((time.tv_sec * 1000) + (time.tv_usec / 1000));

    auto randchar = []() -> char {
        const char charset[] =
                "0123456789"
                        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                        "abcdefghijklmnopqrstuvwxyz";
        const size_t max_index = (sizeof(charset) - 1);
        return charset[rand() % max_index];
    };
    std::string str(length, 0);
    std::generate_n(str.begin(), length, randchar);
    return str;
}

void Utils::printRecordStats(record_stat ** stats){

    cout << std::left
         << std::setw(15) << "domain"   << "\t"
         << std::setw(15) << "average (ms)"  << "\t"
         << std::setw(15) << "stddev (ms)"   << "\t"
         << std::setw(10) << "count"    << "\t"
         << std::setw(20) << "first timestamp (UTC)"    << "\t"
         << std::setw(20) << "last timestamp (UTC)"     << endl;

    cout << std::left
         << std::setw(15) << "----"  << "\t"
         << std::setw(15) << "----"  << "\t"
         << std::setw(15) << "----"  << "\t"
         << std::setw(10) << "----"  << "\t"
         << std::setw(20) << "----"  << "\t"
         << std::setw(20) << "----"  << endl;

    for(int i=0;i<10;i++) {
        char first[20], last[20];

        time_t t1 = stats[i]->first / 1000;
        struct tm *tm1 = gmtime(&t1);
        strftime(first, sizeof(first), "%Y-%m-%d %H:%M:%S", tm1);

        time_t t2 = stats[i]->last / 1000;
        struct tm *tm2 = gmtime(&t2);
        strftime(last, sizeof(last), "%Y-%m-%d %H:%M:%S", tm2);

        cout << std::left
             << std::setw(15) << stats[i]->domain << "\t"
             << std::setw(15) << stats[i]->average << "\t"
             << std::setw(15) << stats[i]->stddev << "\t"
             << std::setw(10) << stats[i]->count << "\t"
             << std::setw(20) << first << "\t"
             << std::setw(20) << last << endl;
    }

    cout << endl;
}

void Utils::printQueryStats(query_stat ** stats) {
    cout << std::left
         << std::setw(15) << "domain"   << "\t"
         << std::setw(10) << "status"    << "\t"
         << std::setw(20) << "timestamp (UTC)"    << "\t"
         << std::setw(10) << "time lapse (ms)"     << endl;
    cout << std::left
         << std::setw(15) << "----" << "\t"
         << std::setw(10) << "----" << "\t"
         << std::setw(20) << "----" << "\t"
         << std::setw(10) << "----" << endl;
    for (int i = 0; i < 10; i++) {
        char start[20];
        time_t t1 = stats[i]->start / 1000;
        struct tm *tm1 = gmtime(&t1);
        strftime(start, sizeof(start), "%Y-%m-%d %H:%M:%S", tm1);

        cout << std::left
             << std::setw(15) << stats[i]->domain   << "\t"
             << std::setw(10) << stats[i]->success  << "\t"
             << std::setw(20) << start              << "\t"
             << std::setw(10) << stats[i]->lapse << endl;
    }
    cout << endl;
}
