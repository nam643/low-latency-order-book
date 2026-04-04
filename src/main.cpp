#include <iostream>
#include "../include/core/MatchingEngine.hpp"
#include "../include/core/Order.hpp"

int main(){
    MatchingEngine engine;

    Order sell1(1, Side::Sell, OrderType::Limit, 101, 10, 1);
    Order buy1(2, Side::Buy, OrderType::Limit, 101, 6, 2);

    ExecutionReport report1 = engine.processAddOrder(sell1);
    std::cout << "Add sell1: " << report1.message << "\n";

    ExecutionReport report2 = engine.processAddOrder(buy1);
    std::cout << "Add buy1: " << report2.message << "\n";

    if (report2.hasTrades()) {
        std::cout << "Trades:\n";
        for (const auto& trade : report2.trades) {
            std::cout << trade.toString() << "\n";
        }
    } else {
        std::cout << "No trades generated.\n";
    }

    std::cout << "\nFinal Order Book:\n";
    std::cout << engine.getOrderBook().toString();

    return 0;
}