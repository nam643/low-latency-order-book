#include <vector>
#include <string>
#include <iostream>
#include "../io/Event.hpp"

class BenchmarkRunner{
private:
    std::vector<Event> generateSyntheticEvents(std::size_t numOrders) const;
    void benchmarkEvents(const std::vector<Event>& events);
public:
    void runFileBenchmark(const std::string& filename);
    void runSyntheticBenchmark(std::size_t numOrders);
    void printSummary() const;
};