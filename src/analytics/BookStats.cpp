#include <iostream>
#include <string>
#include <vector>

#include "../../include/common/Types.hpp"
#include "../../include/core/OrderBook.hpp"


class BookStats{
public:
    static Price midPrice(const OrderBook& book);
    static Price spread(const OrderBook& book);
    static Quantity totalBidVolume(const OrderBook& book, std::size_t depth);
    static Quantity totalAskVolume(const OrderBook& book, std::size_t depth);
    static double imbalance(const OrderBook& book, std::size_t depth);
};