#include "../../include/io/SnapshotWriter.hpp"
#include <fstream>
#include <stdexcept>

void SnapshotWriter::writeBookSnapshot(const OrderBook& book, const std::string& filename) const{
    std::ofstream out(filename);
    if(!out.is_open()){
        throw std::runtime_error("Could not open file for writing: " + filename);
    }

    out<<book.toString();
}

void SnapshotWriter::writeTrades(const std::vector<Trade>& trades, const std::string& filename) const{
    std::ofstream out(filename);
    if(!out.is_open()){
        throw std::runtime_error("Could not open file for writing: " + filename);
    }

    for(const auto& trade : trades){
        out<<trade.toString()<<"\n";
    }
}

void SnapshotWriter::appendTrade(const Trade& trade, const std::string& filename) const{
    std::ofstream out(filename,std::ios::app);
    if(!out.is_open()){
        throw std::runtime_error("Could not open file for appending: " + filename);
    }

    out<<trade.toString()<<"\n";
}