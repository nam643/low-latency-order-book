#include "../../include/core/ExecutionReport.hpp"

void ExecutionReport::addTrade(const Trade& trade){
    trades.push_back(trade);
}

void ExecutionReport::setAccepted(bool value){
    accepted = value;
}

void ExecutionReport::setMessage(const std::string& msg){
    message = msg;
}

bool ExecutionReport::hasTrades() const{
    return !trades.empty();
}