#include "../../include/analytics/LatencyTracker.hpp"
#include <algorithm>
#include <numeric>
#include <sstream>

#include "../../include/analytics/LatencyTracker.hpp"
#include <algorithm>
#include <numeric>
#include <sstream>

void LatencyTracker::record(long long nanoseconds){
    samplesNs_.push_back(nanoseconds);
}

double LatencyTracker::averageNs() const{
    if(samplesNs_.empty()) return 0.0;

    long long total = std::accumulate(samplesNs_.begin(), samplesNs_.end(), 0LL);
    return static_cast<double>(total) / samplesNs_.size();
}

double LatencyTracker::medianNs() const{
    if(samplesNs_.empty()) return 0.0;

    std::vector<long long> sorted = samplesNs_;
    std::sort(sorted.begin(), sorted.end());

    std::size_t n = sorted.size();
    if(n % 2 == 1){
        return static_cast<double>(sorted[n / 2]);
    } else {
        return (sorted[n / 2 - 1] + sorted[n / 2]) / 2.0;
    }
}

double LatencyTracker::p95Ns() const{
    if(samplesNs_.empty()) return 0.0;

    std::vector<long long> sorted = samplesNs_;
    std::sort(sorted.begin(), sorted.end());

    std::size_t index = static_cast<std::size_t>(0.95 * (sorted.size() - 1));
    return static_cast<double>(sorted[index]);
}

double LatencyTracker::p99Ns() const{
    if(samplesNs_.empty()) return 0.0;

    std::vector<long long> sorted = samplesNs_;
    std::sort(sorted.begin(), sorted.end());

    std::size_t index = static_cast<std::size_t>(0.99 * (sorted.size() - 1));
    return static_cast<double>(sorted[index]);
}

long long LatencyTracker::minNs() const{
    if(samplesNs_.empty()) return 0;
    return *std::min_element(samplesNs_.begin(), samplesNs_.end());
}

long long LatencyTracker::maxNs() const{
    if(samplesNs_.empty()) return 0;
    return *std::max_element(samplesNs_.begin(), samplesNs_.end());
}

void LatencyTracker::reset(){
    samplesNs_.clear();
}

std::string LatencyTracker::summary() const{
    std::ostringstream out;
    out << "count=" << samplesNs_.size()
        << ", avg_ns=" << averageNs()
        << ", median_ns=" << medianNs()
        << ", p95_ns=" << p95Ns()
        << ", p99_ns=" << p99Ns()
        << ", min_ns=" << minNs()
        << ", max_ns=" << maxNs();
    return out.str();
}