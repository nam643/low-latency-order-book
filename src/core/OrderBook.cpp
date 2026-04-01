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

//matching order
bool OrderBook::canMatch(const Order& incoming) const{
    if(incoming.side == Side::Buy){
        if(asks_.empty()) return false;
        if(incoming.type == OrderType::Limit) return true;
        return asks_.begin()->first <= incoming.price;
    }
}