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

    return false;
}

bool OrderBook::cancelOrder(OrderId id){
    auto indexIt = orderIndex_.find(id);
    if(indexIt == orderIndex_.end()) return false;

    const OrderLocation& loc = indexIt->second;

    if(loc.side == Side::Buy){
        auto levelIt = bids_.find(loc.price);
        if(levelIt == bids_.end()) return false;

        levelIt->second.getOrders().erase(loc.orderIt);
        levelIt->second.updateTotalQuantity();

        if(levelIt->second.empty()){
            bids_.erase(levelIt);
        }
    }
    else if(loc.side == Side::Sell){
        auto levelIt = asks_.find(loc.price);
        if(levelIt == asks_.end()) return false;

        levelIt->second.getOrders().erase(loc.orderIt);
        levelIt->second.updateTotalQuantity();

        if(levelIt->second.empty()){
            asks_.erase(levelIt);
        }
    }
    else{
        return false;
    }

    orderIndex_.erase(indexIt);
    return true;
}

bool OrderBook::modifyOrder(OrderId id, Price newPrice, Quantity newQty, Timestamp newTimestamp){
    auto indexIt = orderIndex_.find(id);
    if(indexIt == orderIndex_.end()) return false;

    if(newQty <= 0) return false;
    
    const OrderLocation& loc = indexIt->second;

    Order oldOrder = *(loc.orderIt);

    if(!cancelOrder(id)) return false;

    oldOrder.price = newPrice;
    oldOrder.quantity = newQty;
    oldOrder.remainingQuantity = newQty;
    oldOrder.timestamp = newTimestamp;

    return addOrder(oldOrder);
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

    return false;
}

Price OrderBook::getBestOpposingPrice(Side incomingSide) const{
    if(incomingSide == Side::Buy){
        return getBestAsk();
    }
    else if(incomingSide == Side::Sell){
        return getBestBid();
    }

    throw std::invalid_argument("Invalid incoming side");
}

PriceLevel& OrderBook::getBestOpposingLevel(Side incomingSide){
    if(incomingSide == Side::Buy){
        if(asks_.empty()){
            throw std::invalid_argument("No opposing ask level");
        }

        return asks_.begin()->second;
    }
    else if(incomingSide == Side::Sell){
        if(bids_.empty()){
            throw std::invalid_argument("No opposing bid level");
        }

        return bids_.begin()->second;
    }

    throw std::invalid_argument("Invalid incoming side");
}

const PriceLevel& OrderBook::getBestOpposingLevel(Side incomingSide) const{
    if(incomingSide == Side::Buy){
        if(asks_.empty()){
            throw std::invalid_argument("No opposing ask level");
        }

        return asks_.begin()->second;
    }
    else if(incomingSide == Side::Sell){
        if(bids_.empty()){
            throw std::invalid_argument("No opposing bid level");
        }

        return bids_.begin()->second;
    }

    throw std::invalid_argument("Invalid incoming side");
}