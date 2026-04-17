#include <cassert>
#include <iostream>
#include "../include/core/MatchingEngine.hpp"
#include "../include/core/Order.hpp"

void testCancelExistingOrder() {
    MatchingEngine engine;

    Order buy1(1, Side::Buy, OrderType::Limit, 100, 8, 1);
    engine.processAddOrder(buy1);

    ExecutionReport report = engine.processCancelOrder(1);

    assert(report.accepted);
    assert(report.message == "Order cancelled successfully");
    assert(engine.getOrderBook().empty(Side::Buy));
}

void testCancelMissingOrder() {
    MatchingEngine engine;

    ExecutionReport report = engine.processCancelOrder(999);

    assert(!report.accepted);
    assert(report.message == "Order not found");
}

void testModifyExistingOrder() {
    MatchingEngine engine;

    Order buy1(1, Side::Buy, OrderType::Limit, 100, 8, 1);
    engine.processAddOrder(buy1);

    ExecutionReport report = engine.processModifyOrder(1, 102, 5);

    assert(report.accepted);
    assert(report.message == "Order modified successfully");

    const OrderBook& book = engine.getOrderBook();
    assert(!book.empty(Side::Buy));
    assert(book.getBestBid() == 102);
    assert(book.getBestBidLevel() != nullptr);
    assert(book.getBestBidLevel()->getTotalQuantity() == 5);
}

void testModifyMissingOrder() {
    MatchingEngine engine;

    ExecutionReport report = engine.processModifyOrder(999, 101, 4);

    assert(!report.accepted);
    assert(report.message == "Order modification failed");
}

void testModifyMovesPriceLevel() {
    MatchingEngine engine;

    Order buy1(1, Side::Buy, OrderType::Limit, 100, 8, 1);
    Order buy2(2, Side::Buy, OrderType::Limit, 99, 6, 2);

    engine.processAddOrder(buy1);
    engine.processAddOrder(buy2);

    ExecutionReport report = engine.processModifyOrder(1, 103, 5);

    assert(report.accepted);

    const OrderBook& book = engine.getOrderBook();
    assert(book.getBestBid() == 103);
    assert(book.getBestBidLevel() != nullptr);
    assert(book.getBestBidLevel()->getTotalQuantity() == 5);

    auto bidDepth = book.getBidDepth(5);
    assert(bidDepth.size() == 2);
    assert(bidDepth[0].first == 103);
    assert(bidDepth[0].second == 5);
    assert(bidDepth[1].first == 99);
    assert(bidDepth[1].second == 6);
}

int main() {
    testCancelExistingOrder();
    testCancelMissingOrder();
    testModifyExistingOrder();
    testModifyMissingOrder();
    testModifyMovesPriceLevel();

    std::cout << "All cancel/modify tests passed.\n";
    return 0;
}