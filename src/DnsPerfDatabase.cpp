//
// Created by Mingwei Zhang on 11/12/16.
//

#include "DnsPerfDatabase.h"
using namespace std;
using namespace mysqlpp;

DnsPerfDatabase::DnsPerfDatabase() {
    try {
        conn = new Connection(false);
        conn->connect("dnsperf", "ht2.mwzhang.com", "dnsperf_user", "P7lw12JMa0sqpWyg");
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
