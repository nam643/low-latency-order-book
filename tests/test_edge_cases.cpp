#include <cassert>
#include <iostream>
#include <stdexcept>
#include "../include/core/MatchingEngine.hpp"
#include "../include/core/Order.hpp"

void testDuplicateOrderIdRejected() {
    MatchingEngine engine;

    Order buy1(1, Side::Buy, OrderType::Limit, 100, 5, 1);
    Order buyDuplicate(1, Side::Buy, OrderType::Limit, 101, 7, 2);

    ExecutionReport report1 = engine.processAddOrder(buy1);
    ExecutionReport report2 = engine.processAddOrder(buyDuplicate);

    assert(report1.accepted);
    assert(!report2.accepted);

    const OrderBook& book = engine.getOrderBook();
    assert(book.getBestBid() == 100);
    assert(book.getBestBidLevel() != nullptr);
    assert(book.getBestBidLevel()->getTotalQuantity() == 5);
}

void testZeroQuantityRejected() {
    MatchingEngine engine;

    Order badOrder(1, Side::Buy, OrderType::Limit, 100, 0, 1);
    ExecutionReport report = engine.processAddOrder(badOrder);

    assert(!report.accepted);
    assert(engine.getOrderBook().empty(Side::Buy));
    assert(engine.getOrderBook().empty(Side::Sell));
}

void testCancelOnEmptyBookFails() {
    MatchingEngine engine;

    ExecutionReport report = engine.processCancelOrder(123);
    assert(!report.accepted);
    assert(report.message == "Order not found");
}

void testModifyOnEmptyBookFails() {
    MatchingEngine engine;

    ExecutionReport report = engine.processModifyOrder(123, 101, 5);
    assert(!report.accepted);
    assert(report.message == "Order modification failed");
}

void testMarketOrderOnEmptyBookDoesNotRest() {
    MatchingEngine engine;

    Order marketBuy(1, Side::Buy, OrderType::Market, 0, 10, 1);
    ExecutionReport report = engine.processAddOrder(marketBuy);

    assert(report.accepted);
    assert(report.trades.empty());
    assert(engine.getOrderBook().empty(Side::Buy));
    assert(engine.getOrderBook().empty(Side::Sell));
}

void testBestBidThrowsWhenEmpty() {
    MatchingEngine engine;

    bool threw = false;
    try {
        engine.getOrderBook().getBestBid();
    } catch (const std::out_of_range&) {
        threw = true;
    }

    assert(threw);
}

void testBestAskThrowsWhenEmpty() {
    MatchingEngine engine;

    bool threw = false;
    try {
        engine.getOrderBook().getBestAsk();
    } catch (const std::out_of_range&) {
        threw = true;
    }

    assert(threw);
}

int main() {
    testDuplicateOrderIdRejected();
    testZeroQuantityRejected();
    testCancelOnEmptyBookFails();
    testModifyOnEmptyBookFails();
    testMarketOrderOnEmptyBookDoesNotRest();
    testBestBidThrowsWhenEmpty();
    testBestAskThrowsWhenEmpty();

    std::cout << "All edge case tests passed.\n";
    return 0;
}