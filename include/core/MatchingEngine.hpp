#pragma once
#include "OrderBook.hpp"
#include "ExecutionReport.hpp"
#include "Trade.hpp"
#include "../io/Event.hpp"

class MatchingEngine{
private:
    OrderBook book_;
    Timestamp sequence_;

    ExecutionReport matchIncomingOrder(Order incoming);
    void matchBuyOrder(Order& incoming, ExecutionReport& report);
    void matchSellOrder(Order& incoming, ExecutionReport& report);

    bool shouldMatch(const Order& incoming) const;
    Price determineExecutionPrice(const Order& resting, const Order& incoming) const;

    Trade createTrade(
        const Order& incoming,
        const Order& resting,
        Quantity qty,
        Price price,
        Timestamp ts
    );
public:
    MatchingEngine();
    ExecutionReport processAddOrder(const Order& incoming);
    ExecutionReport processCancelOrder(OrderId id);
    ExecutionReport processModifyOrder(OrderId id, Price newPrice, Quantity newQty);
    ExecutionReport processEvent(const Event& event);
    
    const OrderBook& getOrderBook() const;
    OrderBook& getOrderBook();

    void reset();
};