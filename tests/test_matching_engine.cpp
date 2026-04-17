#include <cassert>
#include <iostream>
#include "../include/core/MatchingEngine.hpp"
#include "../include/core/Order.hpp"

void testPartialFill() {
    MatchingEngine engine;

    Order sell1(1, Side::Sell, OrderType::Limit, 101, 10, 1);
    Order buy1(2, Side::Buy, OrderType::Limit, 101, 6, 2);

    engine.processAddOrder(sell1);
    ExecutionReport report = engine.processAddOrder(buy1);

    assert(report.accepted);
    assert(report.trades.size() == 1);
    assert(report.trades[0].buyOrderId == 2);
    assert(report.trades[0].sellOrderId == 1);
    assert(report.trades[0].executionPrice == 101);
    assert(report.trades[0].quantity == 6);

    const OrderBook& book = engine.getOrderBook();
    assert(!book.empty(Side::Sell));
    assert(book.getBestAsk() == 101);
    assert(book.getBestAskLevel() != nullptr);
    assert(book.getBestAskLevel()->getTotalQuantity() == 4);
}

void testFIFOAtSamePrice() {
    MatchingEngine engine;

    Order sell1(1, Side::Sell, OrderType::Limit, 101, 5, 1);
    Order sell2(2, Side::Sell, OrderType::Limit, 101, 5, 2);
    Order buy1(3, Side::Buy, OrderType::Limit, 101, 6, 3);

    engine.processAddOrder(sell1);
    engine.processAddOrder(sell2);
    ExecutionReport report = engine.processAddOrder(buy1);

    assert(report.accepted);
    assert(report.trades.size() == 2);

    assert(report.trades[0].sellOrderId == 1);
    assert(report.trades[0].quantity == 5);

    assert(report.trades[1].sellOrderId == 2);
    assert(report.trades[1].quantity == 1);

    const OrderBook& book = engine.getOrderBook();
    assert(book.getBestAskLevel() != nullptr);
    assert(book.getBestAskLevel()->getTotalQuantity() == 4);
}

void testCancelOrder() {
    MatchingEngine engine;

    Order buy1(1, Side::Buy, OrderType::Limit, 100, 8, 1);
    engine.processAddOrder(buy1);

    ExecutionReport cancelReport = engine.processCancelOrder(1);

    assert(cancelReport.accepted);
    assert(engine.getOrderBook().empty(Side::Buy));
}

void testModifyOrder() {
    MatchingEngine engine;

    Order buy1(1, Side::Buy, OrderType::Limit, 100, 8, 1);
    engine.processAddOrder(buy1);

    ExecutionReport modifyReport = engine.processModifyOrder(1, 102, 5);

    assert(modifyReport.accepted);
    assert(engine.getOrderBook().getBestBid() == 102);
    assert(engine.getOrderBook().getBestBidLevel() != nullptr);
    assert(engine.getOrderBook().getBestBidLevel()->getTotalQuantity() == 5);
}

int main() {
    testPartialFill();
    testFIFOAtSamePrice();
    testCancelOrder();
    testModifyOrder();

    std::cout << "All matching engine tests passed.\n";
    return 0;
}