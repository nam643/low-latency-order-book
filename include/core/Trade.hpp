#include "common/Types.hpp"
#include <iostream>

class Trade {
public:
    OrderId buyOrderId;
    OrderId sellOrderId;
    Price executionPrice;
    Quantity quantity;
    Timestamp timestamp;

    Trade(OrderId buyId,
      OrderId sellId,
      Price price,
      Quantity qty,
      Timestamp ts);

    std::string toString() const;
};