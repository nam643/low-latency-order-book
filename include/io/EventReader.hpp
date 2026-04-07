#pragma once

#include <vector>
#include <string>
#include "Event.hpp"
#include "CSVParser.hpp"

class EventReader{
private:
    std::vector<Event> events_;
    std::size_t currentIndex_;
public:
    explicit EventReader(const std::string& filename);

    bool hasNext() const;
    Event next();
    std::vector<Event> readAll() const;
};