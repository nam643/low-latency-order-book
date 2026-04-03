#include <vector>
#include <string>
#include <iostream>
#include "Event.hpp"

class EventReader{
public:
    explicit EventReader(const std::string& filename);

    bool hasNext() const;
    Event next();
    std::vector<Event> readAll();
};