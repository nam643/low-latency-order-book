#pragma once

#include <vector>
#include <string>
#include "Trade.hpp"

class ExecutionReport {
public:
    std::vector<Trade> trades;
    bool accepted = false;
    std::string message = "";

    void addTrade(const Trade& trade);
    void setAccepted(bool value);
    void setMessage(const std::string& msg);
    bool hasTrades() const;
};