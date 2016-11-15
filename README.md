# dnsperf

**dnsperf** is a C++-based DNS performance checker and logger. It checks the 
statistics of the DNS requests round trip time for the top-10 Alexa domains.

## usage

`./dnsperf [-r -q -c C -i I]`

Options:

* r: check performance results
* q: send queries (default just send one round to all domains)
* c: number of rounds of queries to send
    * `-c -1` allows dnsperf to run indefinitely 
* i: interval between each round of queries in seconds

## output and screenshots

### 1. check results only

`./dnsperf -r` checks the results for previous queries and print out the following statistics:
* domain name
* average query response time in milliseconds
* standard deviation
* total count of queries to far
* timestamp for the first query (in UTC)
* timestamp for the last query (in UTC)


![dnsperf -r](https://i.imgur.com/3svAz84.png)

### 2. query once

`./dnsperf -q` will query the domains once and commit the results into the database.
The fields in the database include:
* domain
* query status: 0 - failed; 1 - succeeded
* timestamp of the query (in UTC)
* time lapsed for the query (response time) in milliseconds

![dnsperf -q](https://i.imgur.com/3F08Gz9.png)

### 3. query multiple times

User can provider number of queries they want to run by using `-c` option.
The following screen shot shows a execution with 3 rounds of queries, `./dnsperf -q -c 3`.

User can also specify the frequency of queries by using `-i` option to set 
inter-query time intervals in seconds. 
The following command will query 10 rounds with 5 seconds interval: `./dnsperf -q -c 10 -i 5`

![dnsperf -q -c 3](https://i.imgur.com/jxfjnHu.png)



## supported platforms

The dnsperf is developed on MacOS Sierra, and tested on both MacOS and Ubuntu 16.04.

## dependencies

The dnsperf requires the following development libraries:

* [mysql++](http://tangentsoft.net/mysql++/)
* [ldns](http://www.nlnetlabs.nl/projects/ldns/)

It also requires [cmake](https://cmake.org/) for building the software.

## build

Check out the source code, and run the following commands in the source code folder:

```
mkdir build; cd build
cmake -B. -H..
make
```

## limitations

This code is highly experimental and have the following limitations:

* it connects to my personal database and may not be perfectly available;
* it currently does not support change of query targets;
* the build procedure can be tricky depending on the platform.

## author

Mingwei Zhang: 
* https://mwzhang.com
* mingwei@mwzhang.com
