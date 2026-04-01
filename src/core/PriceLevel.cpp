//bucket for orders with one price level
#include <stdexcept>
#include "../../include/core/PriceLevel.hpp"

PriceLevel::PriceLevel(Price price):price_(price),totalQuantity_(0){}

//GETTER
Price PriceLevel::getPrice() const{
    return price_;
}

Quantity PriceLevel::getTotalQuantity() const{
    return totalQuantity_;
}

bool PriceLevel::empty() const{
    return orders_.empty();
}

std::size_t PriceLevel::orderCount() const{
    return orders_.size();
}

//METHODS
void PriceLevel::addOrder(const Order& order){
    if(order.price != price_){
        throw std::invalid_argument("This price does not belong to this price level");
    }
    orders_.push_back(order);
    totalQuantity_ += order.remainingQuantity;
}

void PriceLevel::removeFrontOrder(){
    if(orders_.empty()){
        throw std::invalid_argument("There are no orders");
    }
    totalQuantity_ -= orders_.front().remainingQuantity;
    orders_.pop_front();
}

void PriceLevel::removeOrderById(OrderId id){
    bool found = false;
    for(auto it = orders_.begin(); it!=orders_.end();it++){
        if(it->id == id){
            totalQuantity_ -= it->remainingQuantity;
            orders_.erase(it);
            found = true;
            break;
        }
    }

    if(!found){
        throw std::invalid_argument("The order id is not found");
    }
}


Order& PriceLevel::frontOrder(){
    //In the same price level, who came first get to sell first, that's why we care about front order
    if(orders_.empty()){
        throw std::invalid_argument("The orders are currently empty");
    }

    return orders_.front();
}
const Order& PriceLevel::frontOrder() const{
    if(orders_.empty()){
        throw std::invalid_argument("The orders are currently empty");
    }

    return orders_.front();
}

std::list<Order>& PriceLevel::getOrders(){
    return orders_;
}
const std::list<Order>& PriceLevel::getOrders() const{
    return orders_;
}

void PriceLevel::updateTotalQuantity(){
    totalQuantity_ = 0;
    for (const auto& order : orders_) {
        totalQuantity_ += order.remainingQuantity;
    }
}