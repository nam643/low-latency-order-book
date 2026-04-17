/*
add order to bid side
add order to ask side
best bid / best ask
cancel order
modify order
bid depth / ask depth
canMatch() logic
*/

#include <cassert>
#include <iostream>
#include "../include/core/OrderBook.hpp"
#include "../include/core/Order.hpp"

void testAddBidOrder() {
    OrderBook book;
    Order buy1(1, Side::Buy, OrderType::Limit, 100, 10, 1);

    bool added = book.addOrder(buy1);

    assert(added);
    assert(!book.empty(Side::Buy));
    assert(book.getBestBid() == 100);
    assert(book.getBestBidLevel() != nullptr);
    assert(book.getBestBidLevel()->getTotalQuantity() == 10);
}

void testAddAskOrder() {
    OrderBook book;
    Order sell1(1, Side::Sell, OrderType::Limit, 101, 8, 1);

    bool added = book.addOrder(sell1);

    assert(added);
    assert(!book.empty(Side::Sell));
    assert(book.getBestAsk() == 101);
    assert(book.getBestAskLevel() != nullptr);
    assert(book.getBestAskLevel()->getTotalQuantity() == 8);
}

void testCancelOrder() {
    OrderBook book;
    Order buy1(1, Side::Buy, OrderType::Limit, 100, 10, 1);

    book.addOrder(buy1);
    bool cancelled = book.cancelOrder(1);

    assert(cancelled);
    assert(book.empty(Side::Buy));
    assert(!book.hasOrder(1));
}

void testModifyOrder() {
    OrderBook book;
    Order buy1(1, Side::Buy, OrderType::Limit, 100, 10, 1);

    book.addOrder(buy1);
    bool modified = book.modifyOrder(1, 102, 5, 2);

    assert(modified);
    assert(book.getBestBid() == 102);
    assert(book.getBestBidLevel() != nullptr);
    assert(book.getBestBidLevel()->getTotalQuantity() == 5);
}

void testBidDepth() {
    OrderBook book;

    book.addOrder(Order(1, Side::Buy, OrderType::Limit, 100, 10, 1));
    book.addOrder(Order(2, Side::Buy, OrderType::Limit, 99, 5, 2));
    book.addOrder(Order(3, Side::Buy, OrderType::Limit, 98, 7, 3));

    auto depth = book.getBidDepth(2);

    assert(depth.size() == 2);
    assert(depth[0].first == 100);
    assert(depth[0].second == 10);
    assert(depth[1].first == 99);
    assert(depth[1].second == 5);
}

void testAskDepth() {
    OrderBook book;

    book.addOrder(Order(1, Side::Sell, OrderType::Limit, 101, 10, 1));
    book.addOrder(Order(2, Side::Sell, OrderType::Limit, 102, 5, 2));
    book.addOrder(Order(3, Side::Sell, OrderType::Limit, 103, 7, 3));

    auto depth = book.getAskDepth(2);

    assert(depth.size() == 2);
    assert(depth[0].first == 101);
    assert(depth[0].second == 10);
    assert(depth[1].first == 102);
    assert(depth[1].second == 5);
}

void testCanMatchBuy() {
    OrderBook book;

    book.addOrder(Order(1, Side::Sell, OrderType::Limit, 101, 10, 1));

    Order buy1(2, Side::Buy, OrderType::Limit, 101, 5, 2);
    Order buy2(3, Side::Buy, OrderType::Limit, 100, 5, 3);

    assert(book.canMatch(buy1));
    assert(!book.canMatch(buy2));
}

void testCanMatchSell() {
    OrderBook book;

    book.addOrder(Order(1, Side::Buy, OrderType::Limit, 100, 10, 1));

    Order sell1(2, Side::Sell, OrderType::Limit, 100, 5, 2);
    Order sell2(3, Side::Sell, OrderType::Limit, 101, 5, 3);

    assert(book.canMatch(sell1));
    assert(!book.canMatch(sell2));
}

int main() {
    testAddBidOrder();
    testAddAskOrder();
    testCancelOrder();
    testModifyOrder();
    testBidDepth();
    testAskDepth();
    testCanMatchBuy();
    testCanMatchSell();

    std::cout << "All OrderBook tests passed.\n";
    return 0;
}