#include "../../include/io/CSVParser.hpp"
#include <sstream>
#include <fstream>
#include <stdexcept>

std::vector<std::string> CSVParser::split(const std::string& line, char delimiter) const{
    std::vector<std::string> tokens;
    std::stringstream ss(line);
    std::string token;

    while(std::getline(ss,token,delimiter)){
        tokens.push_back(token);
    }

    return tokens;
}

Side CSVParser::parseSide(const std::string& token) const{
    if(token == "BUY") return Side::Buy;
    if(token == "SELL") return Side::Sell;
    throw std::invalid_argument("Invalid side token: " + token);
}

OrderType CSVParser::parseOrderType(const std::string& token) const{
    if(token == "LIMIT") return OrderType::Limit;
    if(token == "MARKET") return OrderType::Market;
    throw std::invalid_argument("Invalid order type token: " + token);
}

EventType CSVParser::parseEventType(const std::string& token) const{
    if(token == "ADD") return EventType::Add;
    if(token == "CANCEL") return EventType::Cancel;
    if(token == "MODIFY") return EventType::Modify;

    throw std::invalid_argument("Invalid event type token: " + token);
}

//ADD,timestamp,orderId,side,orderType,price,quantity
//CANCEL,timestamp,orderId
//MODIFY,timestamp,orderId,price,quantity
Event CSVParser::parseLine(const std::string& line) const{
    std::vector<std::string> tokens = split(line,',');

    if(tokens.empty()){
        throw std::invalid_argument("Empty CSV File");
    }

    Event event{};
    event.type = parseEventType(tokens[0]);

    if(event.isAdd()){
        if(tokens.size() != 7){
            throw std::invalid_argument("Invalid ADD event format");
        }

        event.timestamp = std::stoull(tokens[1]);
        event.orderId = std::stoull(tokens[2]);
        event.side = parseSide(tokens[3]);
        event.orderType = parseOrderType(tokens[4]);
        event.price = std::stoull(tokens[5]);
        event.quantity = std::stoull(tokens[6]);
    }
    else if(event.isCancel()){
        if(tokens.size() != 3){
            throw std::invalid_argument("Invalid CANCEL event format");
        }

        event.timestamp = std::stoull(tokens[1]);
        event.orderId = std::stoull(tokens[2]);
    }
    else if(event.isModify()){
        if(tokens.size() != 5){
            throw std::invalid_argument("Invalid MODIFY event formula");
        }

        event.timestamp = std::stoull(tokens[1]);
        event.orderId = std::stoull(tokens[2]);
        event.price = std::stoull(tokens[3]);
        event.price = std::stoull(tokens[4]);
    }

    return event;
}

std::vector<Event> CSVParser::parseFile(const std::string& filename) const{
    std::vector<Event> events;
    std::ifstream file(filename);

    if(!file.is_open()){
        throw std::runtime_error("Could not open the file: " + filename);
    }

    std::string line;
    while(std::getline(file,line)){
        if(line.empty()) continue;
        events.push_back(parseLine(line));
    }

    return events;
}