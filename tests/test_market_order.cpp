#include <cassert>
#include <iostream>
#include "../include/core/MatchingEngine.hpp"
#include "../include/core/Order.hpp"

void testMarketBuyConsumesAsks() {
    MatchingEngine engine;

    Order sell1(1, Side::Sell, OrderType::Limit, 101, 5, 1);
    Order sell2(2, Side::Sell, OrderType::Limit, 102, 4, 2);
    Order buyMarket(3, Side::Buy, OrderType::Market, 0, 7, 3);

    engine.processAddOrder(sell1);
    engine.processAddOrder(sell2);
    ExecutionReport report = engine.processAddOrder(buyMarket);

    assert(report.accepted);
    assert(report.trades.size() == 2);

    assert(report.trades[0].buyOrderId == 3);
    assert(report.trades[0].sellOrderId == 1);
    assert(report.trades[0].executionPrice == 101);
    assert(report.trades[0].quantity == 5);

    assert(report.trades[1].buyOrderId == 3);
    assert(report.trades[1].sellOrderId == 2);
    assert(report.trades[1].executionPrice == 102);
    assert(report.trades[1].quantity == 2);

    const OrderBook& book = engine.getOrderBook();
    assert(!book.empty(Side::Sell));
    assert(book.getBestAsk() == 102);
    assert(book.getBestAskLevel() != nullptr);
    assert(book.getBestAskLevel()->getTotalQuantity() == 2);
}

void testMarketSellConsumesBids() {
    MatchingEngine engine;

    Order buy1(1, Side::Buy, OrderType::Limit, 100, 6, 1);
    Order buy2(2, Side::Buy, OrderType::Limit, 99, 5, 2);
    Order sellMarket(3, Side::Sell, OrderType::Market, 0, 8, 3);

    engine.processAddOrder(buy1);
    engine.processAddOrder(buy2);
    ExecutionReport report = engine.processAddOrder(sellMarket);

    assert(report.accepted);
    assert(report.trades.size() == 2);

    assert(report.trades[0].buyOrderId == 1);
    assert(report.trades[0].sellOrderId == 3);
    assert(report.trades[0].executionPrice == 100);
    assert(report.trades[0].quantity == 6);

    assert(report.trades[1].buyOrderId == 2);
    assert(report.trades[1].sellOrderId == 3);
    assert(report.trades[1].executionPrice == 99);
    assert(report.trades[1].quantity == 2);

    const OrderBook& book = engine.getOrderBook();
    assert(!book.empty(Side::Buy));
    assert(book.getBestBid() == 99);
    assert(book.getBestBidLevel() != nullptr);
    assert(book.getBestBidLevel()->getTotalQuantity() == 3);
}

void testLeftoverMarketOrderDoesNotRest() {
    MatchingEngine engine;

    Order sell1(1, Side::Sell, OrderType::Limit, 101, 4, 1);
    Order buyMarket(2, Side::Buy, OrderType::Market, 0, 10, 2);

    engine.processAddOrder(sell1);
    ExecutionReport report = engine.processAddOrder(buyMarket);

    assert(report.accepted);
    assert(report.trades.size() == 1);

    assert(report.trades[0].buyOrderId == 2);
    assert(report.trades[0].sellOrderId == 1);
    assert(report.trades[0].executionPrice == 101);
    assert(report.trades[0].quantity == 4);

    const OrderBook& book = engine.getOrderBook();
    assert(book.empty(Side::Sell));
    assert(book.empty(Side::Buy));
}
int main() {
    testMarketBuyConsumesAsks();
    testMarketSellConsumesBids();
    testLeftoverMarketOrderDoesNotRest();

    std::cout << "All market order tests passed.\n";
    return 0;
}