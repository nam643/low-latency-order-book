#pragma once

#include <vector>
#include <string>
#include "../../include/core/MatchingEngine.hpp"
#include "../../include/io/Event.hpp"
#include "../../include/analytics/LatencyTracker.hpp"

class BenchmarkRunner{
private:
    MatchingEngine engine_;
    LatencyTracker tracker_;

    std::vector<Event> generateSyntheticEvents(std::size_t numOrders) const;
    void benchmarkEvents(const std::vector<Event>& events);

public:
    void runFileBenchmark(const std::string& filename);
    void runSyntheticBenchmark(std::size_t numOrders);
    void printSummary() const;
};