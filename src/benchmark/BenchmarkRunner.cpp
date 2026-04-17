#include "../../include/benchmark/BenchmarkRunner.hpp"
#include "../../include/io/EventReader.hpp"
#include "../../include/core/MatchingEngine.hpp"
#include "../../include/analytics/LatencyTracker.hpp"

#include <chrono>
#include <iostream>
#include <stdexcept>

std::vector<Event> BenchmarkRunner::generateSyntheticEvents(std::size_t numOrders) const{
    std::vector<Event> events;
    events.reserve(numOrders);

    for(std::size_t i = 0;i<numOrders;i++){
        Event event{};

        event.type = EventType::Add;
        event.timestamp = static_cast<Timestamp>(i+1);
        event.orderId = static_cast<OrderId>(i+1);

        if(i%2==0){
            event.side = Side::Buy;
            event.price = 100 + (i%5);
        }
        else{
            event.side = Side::Sell;
            event.price = 101 + (i%5);
        }

        event.orderType = OrderType::Limit;
        event.quantity = 10 + (i%10);

        events.push_back(event);
    }

    return events;
}

void BenchmarkRunner::benchmarkEvents(const std::vector<Event>& events){
    engine_.reset();
    tracker_.reset();

    for(const auto& event : events){
        auto start = std::chrono::high_resolution_clock::now();

        engine_.processEvent(event);

        auto end = std::chrono::high_resolution_clock::now();
        auto ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

        tracker_.record(ns);
    }
}

void BenchmarkRunner::runFileBenchmark(const std::string& filename){
    EventReader reader(filename);
    std::vector<Event> events = reader.readAll();
    benchmarkEvents(events);
}

void BenchmarkRunner::runSyntheticBenchmark(std::size_t numOrders){
    std::vector<Event> events = generateSyntheticEvents(numOrders);
    benchmarkEvents(events);
}

void BenchmarkRunner::printSummary() const{
    std::cout << tracker_.summary() << "\n";
}