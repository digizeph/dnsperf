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
        cout << "Connection succeeded!"<<endl;
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
