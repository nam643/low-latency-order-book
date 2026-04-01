#include<iostream>
#include<string>
#include<vector>
#include "core/OrderBook.hpp"
#include "core/Trade.hpp"

class SnapshotWriter{
public:
    void writeBookSnapShot(const OrderBook& book, const std::string& filename) const;
    void writeTrades(const std::vector<Trade>& trades, const std::string& filename) const;
    void appendTrade(const Trade& trade, const std::string& filename) const;
};