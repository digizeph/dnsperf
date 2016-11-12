all:
	g++ -std=c++11 Timer.h Timer.cpp dnsperf.cpp DnsQuery.h DnsQuery.cpp -lldns -lpthread -o dnsperf

run:
	./dnsperf

clean:
	rm -f dnsperf *.gch
