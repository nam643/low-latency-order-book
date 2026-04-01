#include <vector>
#include <string>
#include <iostream>

class LatencyTracker{
private:
    std::vector<long long> samplesNs_;
public:
    void record(long long nanoseconds);
    double averageNs() const;
    double medianNs() const;
    double p95Ns() const; //return the 95th percentile latency in ns
    double p99Ns() const; //return the 95th percentile latency in ns
    long long minNs() const;
    long long maxNs() const;
    void reset();
    std::string summary() const;
};