#include "../../include/core/OrderBook.hpp"
#include <stdexcept>

bool OrderBook::hasOrder(OrderId id) const{
    return (orderIndex_.find(id) != orderIndex_.end());
}
bool OrderBook::empty(Side side) const{
    if(side == Side::Buy) return bids_.empty();
    return asks_.empty();
}

//get best bid/ask by price
Price OrderBook::getBestBid() const{
    if(bids_.empty()){
        throw std::out_of_range("There are no bids yet");
    }
    return bids_.begin()->first;
}
Price OrderBook::getBestAsk() const{
    if(asks_.empty()){
        throw std::out_of_range("There are no asks yet");
    }
    return asks_.begin()->first;
}

//get best bid/ask by PriceLevel
const PriceLevel* OrderBook::getBestBidLevel() const{
    if(bids_.empty()){
        return nullptr;
    }
    return &bids_.begin()->second;
}
const PriceLevel* OrderBook::getBestAskLevel() const{
    if(asks_.empty()){
        return nullptr;
    }
    return &asks_.begin()->second;
}

//Order management
bool OrderBook::addOrder(const Order& order){
    //no stored order OR no amount of order
    if(hasOrder(order.id)) return false;
    if(order.quantity <= 0) return false;

    if(order.side == Side::Buy){
        //find if the price level already exists
        auto levelIt = bids_.find(order.price);
        if(levelIt == bids_.end()){
            bids_.emplace(order.price, PriceLevel(order.price));
            levelIt = bids_.find(order.price);
        }

        levelIt->second.addOrder(order);

        auto orderIt = levelIt->second.getOrders().end();
        --orderIt;


        //orderIt is used for fast searching, in case we want to remove it
        orderIndex_[order.id] = {order.side, order.price, orderIt};

        return true;
    }
    else if(order.side == Side::Sell){
        //find if the price level already exists
        auto levelIt = asks_.find(order.price);
        if(levelIt == asks_.end()){
            asks_.emplace(order.price, PriceLevel(order.price));
            levelIt = asks_.find(order.price);
        }

        levelIt->second.addOrder(order);

        auto orderIt = levelIt->second.getOrders().end();
        --orderIt;


        //orderIt is used for fast searching, in case we want to remove it
        orderIndex_[order.id] = {order.side, order.price, orderIt};
        return true;
    }
}

//matching order
bool OrderBook::canMatch(const Order& incoming) const{
    if(incoming.side == Side::Buy){
        if(asks_.empty()) return false;
        if(incoming.type == OrderType::Limit) return true;
        //to make profit
        //only buy when the asked price is lower
        return asks_.begin()->first <= incoming.price;
    }
    if(incoming.side == Side::Sell){
        if(bids_.empty()) return false;
        if(incoming.type == OrderType::Limit) return true;
        //to make profit
        //only sell when the bids price is larger
        return bids_.begin()->first >= incoming.price;
    }
}
