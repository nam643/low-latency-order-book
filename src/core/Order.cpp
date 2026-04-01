#include <stdexcept>
#include "../../include/core/Order.hpp"

Order :: Order(
    OrderId id,
    Side side,
    OrderType type,
    Price price,
    Quantity quantity,
    Timestamp timestamp
) : 
id(id),
side(side),
type(type),
price(price),
quantity(quantity),
remainingQuantity(quantity),
timestamp(timestamp){}

bool Order::isFilled() const{
    return remainingQuantity == 0;
}

bool Order::isMarketOrder() const{
    return type == OrderType::Market;
}

bool Order::isLimitOrder() const{
    return type == OrderType::Limit;
}


void Order::fill(Quantity qty){
    if(qty > remainingQuantity){
        throw std::invalid_argument("Fill quantity exceeds remaining quantity");
    }
    remainingQuantity -= qty;
}

void Order::modifyPrice(Price newPrice){
    price = newPrice;
}

void Order::modifyQuantity(Quantity newQty){
    quantity = newQty;
    remainingQuantity = newQty;
}