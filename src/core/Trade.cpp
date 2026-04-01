#include <string>
#include <iostream>
#include <format>
#include "../../include/core/Trade.hpp"

Trade::Trade(
    OrderId buyId,
    OrderId sellId,
    Price price,
    Quantity qty,
    Timestamp ts
):
buyOrderId(buyId),
sellOrderId(sellId),
executionPrice(price),
quantity(qty),
timestamp(ts){}

std::string Trade::toString() const {
    return "BUY=" + std::to_string(buyOrderId) +
           " SELL=" + std::to_string(sellOrderId) +
           " PRICE=" + std::to_string(executionPrice) +
           " QTY=" + std::to_string(quantity) +
           " TS=" + std::to_string(timestamp);
}