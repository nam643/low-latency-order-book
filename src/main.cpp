#include <iostream>
#include <vector>
#include "../include/core/MatchingEngine.hpp"
#include "../include/io/EventReader.hpp"
#include "../include/io/SnapshotWriter.hpp"
#include "../include/benchmark/BenchmarkRunner.hpp"

int main() {
    //-----------------TEST CSV FILE--------------------
    // try {
    //     MatchingEngine engine;
    //     EventReader reader("events.csv");
    //     SnapshotWriter writer;

    //     std::vector<Trade> allTrades;

    //     while (reader.hasNext()) {
    //         Event event = reader.next();
    //         ExecutionReport report = engine.processEvent(event);

    //         std::cout << report.message << "\n";

    //         for (const auto& trade : report.trades) {
    //             allTrades.push_back(trade);
    //             std::cout << trade.toString() << "\n";
    //         }
    //     }

    //     writer.writeBookSnapshot(engine.getOrderBook(), "final_book.txt");
    //     writer.writeTrades(allTrades, "trades.txt");

    //     std::cout << "\nFinal Order Book:\n";
    //     std::cout << engine.getOrderBook().toString();

    //     std::cout << "\nSnapshot written to final_book.txt\n";
    //     std::cout << "Trades written to trades.txt\n";
    // }
    // catch (const std::exception& ex) {
    //     std::cerr << "Error: " << ex.what() << "\n";
    //     return 1;
    // }


    //---------------TEST BENCHMARK----------------------
    BenchmarkRunner runner;

    runner.runSyntheticBenchmark(10000);
    runner.printSummary();

    return 0;
}