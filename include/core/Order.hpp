#pragma once

#include "common/Types.hpp"

class Order {
public:
    OrderId id;
    Side side;
    OrderType type;
    Price price;
    Quantity quantity;
    Quantity remainingQuantity;
    Timestamp timestamp;

    Order(OrderId id,
      Side side,
      OrderType type,
      Price price,
      Quantity quantity,
      Timestamp timestamp);

    bool isFilled() const; //is our stock empty
    bool isMarketOrder() const;
    bool isLimitOrder() const;
    void fill(Quantity qty); //trade a quantity
    void modifyPrice(Price newPrice);
    void modifyQuantity(Quantity newQty);
};