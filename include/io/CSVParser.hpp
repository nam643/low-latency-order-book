//Reads a CSV row and turns it into an Event
#include "io/Event.hpp"
#include <vector>
#include <string>

class CSVParser{
public:
    Event parseLine(const std::string& line) const;
    std::vector<Event> parseFile(const std::string& filename) const;

    std::vector<std::string> split(const std::string& line, char delimiter) const;
    Side parseSide(const std::string& token) const;
    OrderType parseOrderType(const std::string& token) const;
    EventType parseEventType(const std::string& token) const;
private:
    std::vector<std::string> split(const std::string& line, char delimeter) const;
    Side parseSide(const std::string& token) const;
    OrderType parseOrderType(const std::string& token) const;
    EventType parseEventType(const std::string& token) const;
};