//
// Created by Mingwei Zhang on 11/12/16.
//

#include "DnsPerfDatabase.h"
using namespace std;
using namespace mysqlpp;

DnsPerfDatabase::DnsPerfDatabase() {
    try {

        conn.connect("dnsperf", "ht2.mwzhang.com", "dnsperf_user", "P7lw12JMa0sqpWyg");
        //Query query = conn->query();
        cout << "Database connection succeeded!"<<endl<<endl;
    } catch (BadQuery er) { // handle any connection or
        // query errors that may come up
        cerr << "Error: " << er.what() << endl;
    } catch (const BadConversion& er) {
        // Handle bad conversions
        cerr << "Conversion error: " << er.what() << endl <<
             "\tretrieved data size: " << er.retrieved <<
             ", actual size: " << er.actual_size << endl;
    } catch (const Exception& er) {
        // Catch-all for any other MySQL++ exceptions
        cerr << "Error: " << er.what() << endl;
    }
}

/**
 * Insert single record into the database.
 *
 * @param stats query_stat record
 */
ulonglong DnsPerfDatabase::insertRecord(query_stat* stat) {
    Query query = conn.query();
    query << "INSERT INTO records VALUES (NULL, "
          <<stat->start.count()<<", "
          <<stat->lapse.count()<<", '"
          <<stat->domain<<"');";
    SimpleResult result = query.execute();
    //cout<< "record inserted "<<result.insert_id()<<endl;
    return result.insert_id();
}

record_stat *DnsPerfDatabase::getRecordStats(const char domain[]) {
    record_stat * stat = new record_stat;

    // select stddev(t_lapse),avg(t_lapse) from records where domain='blogger.com'

    Query query = conn.query();
    query <<"SELECT AVG(t_lapse),STDDEV(t_lapse),count(*) from records where domain='"
          << domain <<"';";
    if (StoreQueryResult res = query.store()) {
        mysqlpp::StoreQueryResult::const_iterator it;
        for (it = res.begin(); it != res.end(); ++it) {
            mysqlpp::Row row = *it;

            stat->average=row[0];
            stat->stddev = row[1];
            stat->count = row[2];
        }
    }
    else {
        cerr << "Failed to get item list: " << query.error() << endl;
    }

    query.reset();

    query << "select ( select t_start from records where domain='"<< domain <<"' order by id limit 1) as 'first',"
          << "( select t_start from records where domain='"<<domain<<"' order by id desc limit 1) as 'last';";


    if (StoreQueryResult res = query.store()) {
        mysqlpp::StoreQueryResult::const_iterator it;
        for (it = res.begin(); it != res.end(); ++it) {
            mysqlpp::Row row = *it;

            stat->first = row[0];
            stat->last = row[1];
        }
    }
    else {
        cerr << "Failed to get item list: " << query.error() << endl;
    }

    return stat;
}
