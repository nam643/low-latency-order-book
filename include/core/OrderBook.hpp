#pragma once


#include<map>
#include<unordered_map>
#include<common/Types.hpp>
#include "core/PriceLevel.hpp"
#include "core/Order.hpp"
#include <vector>
#include <string>

class OrderBook{
private:
    std::map<Price,PriceLevel, std::greater<Price>> bids_; 
    std::map<Price,PriceLevel, std::less<Price>> asks_;

    struct OrderLocation{
        Side side;
        Price price;
        std::list<Order>::iterator orderIt;
    };

    std::unordered_map<OrderId, OrderLocation> orderIndex_;

public:
    //book query
    bool hasOrder(OrderId id) const;
    bool empty(Side side) const;

    Price getBestBid() const;
    Price getBestAsk() const;

    const PriceLevel* getBestBidLevel() const;
    const PriceLevel* getBestAskLevel() const;

    //order management
    bool addOrder(const Order& order);
    bool cancelOrder(OrderId id);
    bool modifyOrder(OrderId id, Price newPrice, Quantity newQty, Timestamp newTimestamp);

    //matching order
    bool canMatch(const Order& incoming) const;
    Price getBestOpposingPrice(Side incomingSide) const;
    PriceLevel& getBestOpposingLevel(Side incomingSide);
    const PriceLevel& getBestOpposingLevel(Side incomingSide) const;

    //add and remove
    void addToBidBook(const Order& order);
    void addToAskBook(const Order& order);

    void removeOrderFromIndex(OrderId id);
    void removeEmptyPriceLevel(Side side, Price price);

    std::vector<std::pair<Price,Quantity>> getBidDepth(std::size_t levels) const;
    std::vector<std::pair<Price,Quantity>> getAskDepth(std::size_t levels) const;

    //Snapshot/dispalay

    std::string toString(std::size_t depth = 5) const;
    void printTopOfBook() const;
};